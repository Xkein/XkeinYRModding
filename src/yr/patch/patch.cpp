#include "yr/patch/patch.h"
#include "runtime/logger/logger.h"
#include "yr/debug_util.h"
#include <asmjit/asmjit.h>
#include <Zydis/Zydis.h>
#include <memory>

#define ENTRY_POINT_ADDRESS 0x7CD810

void ApplyModulePatch(HANDLE hInstance);

class JitErrorHandler : public asmjit::ErrorHandler
{
public:
    void handleError(asmjit::Error err, const char* message, asmjit::BaseEmitter* origin) override
    {
        gLogger->error("AsmJit ERROR: {}", message);
    }
};

class JitLogger : public asmjit::Logger
{
public:
    asmjit::Error _log(const char* data, size_t size) noexcept override
    {
        gLogger->info("AsmJit: {}", data);
        return asmjit::kErrorOk;
    }
};

asmjit::JitRuntime* gJitRuntime;
JitErrorHandler     gJitErrorHandler;
JitLogger           gJitLogger;

void InitPatch()
{
    gJitRuntime = new asmjit::JitRuntime();
}

void UninitPatch()
{
    delete gJitRuntime;
    gJitRuntime = nullptr;
}

void InitCodeHolder(asmjit::CodeHolder& code)
{
    code.init(gJitRuntime->environment(), gJitRuntime->cpuFeatures());
    code.setErrorHandler(&gJitErrorHandler);
    // code.setLogger(&gJitLogger);
}

void EmbedOriginalCode(asmjit::x86::Assembler& assembly, syringe_patch_data* data, std::vector<byte>& originalCode)
{
    // fix relative jump or call
    if (originalCode[0] == 0xE9 || originalCode[0] == 0xE8)
    {
        DWORD dest = data->hookAddr + 5 + *(DWORD*)(originalCode.data() + 1);
        switch (originalCode[0])
        {
            case 0xE9: // jmp
                assembly.jmp(dest);
                originalCode.erase(originalCode.begin(), originalCode.begin() + 5);
                break;
            case 0xE8: // call
                assembly.call(dest);
                originalCode.erase(originalCode.begin(), originalCode.begin() + 5);
                break;
        }
    }
    assembly.embed(originalCode.data(), originalCode.size());
}

void CheckHookRace(syringe_patch_data* data, std::vector<byte>& originalCode)
{
    void* hookAddress = (void*)data->hookAddr;
    bool maybeConflicted = false;
    // check hook race
    for (byte originalByte : originalCode)
    {
        switch (originalByte)
        {
            case 0xE9:
            case 0xE8:
                maybeConflicted = true;
                break;
        }
        if (maybeConflicted)
            break;
    }
    std::string disassemblyResult;
    if (maybeConflicted) {
        // Initialize decoder context
        ZydisDecoder decoder;
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_STACK_WIDTH_32);
    
        // Initialize formatter. Only required when you actually plan to do instruction
        // formatting ("disassembling"), like we do here
        ZydisFormatter formatter;
        ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

        // Loop over the instructions in our buffer.
        // The runtime-address (instruction pointer) is chosen arbitrary here in order to better
        // visualize relative addressing
        ZyanU64 runtime_address = data->hookAddr;
        ZyanUSize offset = 0;
        const ZyanUSize length = data->hookSize + 4;
        ZydisDecodedInstruction instruction;
        ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
        while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, (void*)(data->hookAddr + offset), length - offset, &instruction, operands)))
        {
            // Format & print the binary instruction structure to human-readable format
            char buffer[256];
            ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
                instruction.operand_count_visible, buffer, sizeof(buffer), runtime_address, ZYAN_NULL);
            disassemblyResult += std::format("\n-- 0x{:08x}  {}", runtime_address, buffer);
    
            offset += instruction.length;
            runtime_address += instruction.length;
        }
    }
    if (disassemblyResult.contains("jmp") || disassemblyResult.contains("call")) {
        gLogger->warn("Hook {} seems to be conflicted with other hooks! disassembly: {}", hookAddress, disassemblyResult);
    }
}

typedef DWORD __cdecl SyringePatchFunc (REGISTERS*);
DWORD __cdecl CallSyringePatchSafe(syringe_patch_data* data, REGISTERS *R)
{
    std::string* stackTrace = nullptr;
    __try
    {
        return reinterpret_cast<SyringePatchFunc*>(data->hookFunc)(R);
    }
    __except (ExceptionFilterGetInfo(GetExceptionInformation(), stackTrace))
    {
        gLogger->error("syringe patch encounter error! hook address: 0x{:08x}", data->hookAddr);
        gLogger->error("stack trace : {}", *stackTrace);
        gLogger->flush();
    }
}

void ApplySyringePatch(syringe_patch_data* data)
{
    using namespace asmjit;
    CodeHolder code;
    InitCodeHolder(code);
    x86::Assembler assembly(&code);

    Label l_origin = assembly.newLabel();
    // call hook function
    assembly.pushad();
    assembly.pushfd();
    assembly.push(data->hookAddr);
    assembly.sub(x86::esp, 4);
    assembly.lea(x86::eax, x86::ptr(x86::esp, 4));
    assembly.push(x86::eax);
    if (data->unsafe) {
        assembly.call(data->hookFunc);
        assembly.add(x86::esp, 0xC);    
    }
    else {
        assembly.push(data);
        assembly.call(&CallSyringePatchSafe);
        assembly.add(x86::esp, 0x10);
    }
    assembly.mov(x86::ptr(x86::esp, -8), x86::eax);
    assembly.popfd();
    assembly.popad();
    assembly.cmp(x86::dword_ptr(x86::esp, -0x2C), 0);
    assembly.jz(l_origin);
    // jump to hook function specified address
    assembly.jmp(x86::ptr(x86::esp, -0x2C));
    // execute original code
    assembly.bind(l_origin);

    void*             hookAddress = (void*)data->hookAddr;
    DWORD             hookSize    = std::max(data->hookSize, 5u);
    std::vector<byte> originalCode(hookSize);
    memcpy(originalCode.data(), hookAddress, hookSize);
    EmbedOriginalCode(assembly, data, originalCode);
    // jump back
    assembly.jmp(data->hookAddr + hookSize);
    // generate code
    const void* fn;
    gJitRuntime->add(&fn, &code);
    // reset generate data
    code.reset();
    InitCodeHolder(code);
    code.attach(&assembly);
    // jump to hook function from hook address
    assembly.jmp(fn);
    code.flatten();
    code.resolveUnresolvedLinks();
    code.relocateToBase(data->hookAddr);
    // check hook race
    CheckHookRace(data, originalCode);
    // override hook address
    DWORD protect_flag;
    VirtualProtect(hookAddress, hookSize, PAGE_EXECUTE_READWRITE, &protect_flag);
    code.copyFlattenedData(hookAddress, hookSize);
    VirtualProtect(hookAddress, hookSize, protect_flag, NULL);
    FlushInstructionCache(GetCurrentProcess(), hookAddress, hookSize);
}

void ApplyModulePatch(HANDLE hInstance)
{
    char moduleName[MAX_PATH] {};
    GetModuleFileName((HMODULE)hInstance, moduleName, sizeof(moduleName));
    gLogger->info("Applying patchs: module = {}", moduleName);
    auto pHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(((PIMAGE_DOS_HEADER)hInstance)->e_lfanew + (long)hInstance);
    int patchCount = 0;
    for (int i = 0; i < pHeader->FileHeader.NumberOfSections; i++)
    {
        auto sct_hdr = IMAGE_FIRST_SECTION(pHeader) + i;

        if (strncmp(SYRINGE_PATCH_SECTION_NAME, (char*)sct_hdr->Name, 8) == 0)
        {
            auto data = (syringe_patch_data*)((DWORD)hInstance + sct_hdr->VirtualAddress);
            auto size = sct_hdr->Misc.VirtualSize / sizeof(syringe_patch_data);

            for (size_t idx = 0; idx < size; idx++)
            {
                syringe_patch_data* curPatch = &data[idx];
                if (curPatch->hookFunc == nullptr || curPatch->hookAddr == 0)
                    continue;
                ApplySyringePatch(curPatch);
                patchCount++;
            }
        }
        else if (std::string_view(moduleName).contains("YrExtCore")) {
            continue;
        }
        else if (strncmp(".syhks00", (char*)sct_hdr->Name, 8) == 0)
        {
            gLogger->info("found real syringe patch section, converting to our syringe patch pattern.");
            auto data = (hookdecl*)((DWORD)hInstance + sct_hdr->VirtualAddress);
            auto size = sct_hdr->Misc.VirtualSize / sizeof(hookdecl);

            for (size_t idx = 0; idx < size; idx++)
            {
                hookdecl* curHook = &data[idx];
                if (curHook->hookName == nullptr || curHook->hookAddr == 0)
                    continue;
                syringe_patch_data* curPatch = new syringe_patch_data;
                curPatch->hookAddr = curHook->hookAddr;
                curPatch->hookSize = curHook->hookSize;
                curPatch->hookFunc = GetProcAddress((HMODULE)hInstance, curHook->hookName);
                if (curPatch->hookFunc == nullptr)
                {
                    gLogger->error("could not get hook function {}", curHook->hookName);
                    delete curPatch;
                    continue;
                }
                
                curPatch->unsafe = false;
                if (curPatch->hookAddr == ENTRY_POINT_ADDRESS) {
                    gLogger->info("found entry point hook {}, directly invoking", curHook->hookName);
                    CallSyringePatchSafe(curPatch, nullptr);
                } else {
                    ApplySyringePatch(curPatch);
                }
                patchCount++;
            }
        }
    }
    gLogger->info("Patchs applied: module = {}, count = {}", moduleName, patchCount);
}

void RemoveModulePatch(HANDLE hInstance)
{
    gLogger->warn("RemoveModulePatch is not implemented yet!");
}
