#include "yr/patch/patch.h"
#include "runtime/logger/logger.h"
#include <asmjit/asmjit.h>
#include <Zydis/Zydis.h>
#include <memory>

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
    ApplyModulePatch(GetModuleHandle("YrExtCore.dll"));
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

void ApplySyringePatch(syringe_patch_data* data)
{
	if (data->hookFunc == nullptr || data->hookAddr == 0)
		return;
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
    assembly.call(data->hookFunc);
    assembly.add(x86::esp, 0xC);
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
    std::vector<byte> originalCode(data->hookSize);
    memcpy(originalCode.data(), hookAddress, data->hookSize);
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
    // jump back
    assembly.jmp(data->hookAddr + data->hookSize);
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
    // override hook address
    DWORD protect_flag;
    VirtualProtect(hookAddress, data->hookSize, PAGE_EXECUTE_READWRITE, &protect_flag);
    code.copyFlattenedData(hookAddress, data->hookSize);
    VirtualProtect(hookAddress, data->hookSize, protect_flag, NULL);
    FlushInstructionCache(GetCurrentProcess(), hookAddress, data->hookSize);
	// check hook race
	for (byte originalByte : originalCode)
	{
		switch (originalByte)
		{
		case 0xE9:
		case 0xE8:
			gLogger->warn("Hook {} seems to be conflicted with other hooks!", hookAddress);
			break;
		}
	}
	
}

void ApplyModulePatch(HANDLE hInstance)
{
    auto pHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(((PIMAGE_DOS_HEADER)hInstance)->e_lfanew + (long)hInstance);

    for (int i = 0; i < pHeader->FileHeader.NumberOfSections; i++)
    {
        auto sct_hdr = IMAGE_FIRST_SECTION(pHeader) + i;

        if (strncmp(SYRINGE_PATCH_SECTION_NAME, (char*)sct_hdr->Name, 8) == 0)
        {
            auto data = (syringe_patch_data*)((DWORD)hInstance + sct_hdr->VirtualAddress);
            auto size = sct_hdr->Misc.VirtualSize / sizeof(syringe_patch_data);

            for (size_t idx = 0; idx < size; idx++)
            {
                ApplySyringePatch(&data[idx]);
            }
        }
    }
}
