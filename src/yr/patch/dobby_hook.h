#pragma once

#include <dobby.h>
#include <cstdint>

// DobbyHookRegister — unified RAII wrapper for DobbyHook and DobbyInstrument
//
// Two-phase design:
//   Phase 1 (ctor) — stores parameters. Does NOT call Dobby.
//     Safe for DllMain / static init context.
//   Phase 2 (Apply) — actually calls DobbyHook or DobbyInstrument.
//
// Two modes:
//   Replace mode (DobbyHook):
//     static auto MyHook_Origin = nullptr;
//     static DobbyHookRegister _hk(addr, MyHook_Replace, &MyHook_Origin);
//
//   Instrument mode (DobbyInstrument):
//     static DobbyHookRegister _hk(addr, MyInstrument);
//     static void MyInstrument(RegisterContext* ctx, const HookEntryInfo* info);

class DobbyHookRegister {
    void*    address_;
    void*    replace_call_ = nullptr;
    void**   origin_ptr_   = nullptr;
    DBICallTy callback_    = nullptr;
    bool     is_instrument_ = false;
    bool     applied_      = false;

public:
    // Replace mode — wraps DobbyHook
    DobbyHookRegister(void* addr, void* replace, void** origin)
        : address_(addr), replace_call_(replace), origin_ptr_(origin) {}

    // Instrument mode — wraps DobbyInstrument
    DobbyHookRegister(void* addr, DBICallTy cb)
        : address_(addr), callback_(cb), is_instrument_(true) {}

    void Apply() {
        if (!applied_) {
            int ret = is_instrument_
                ? DobbyInstrument(address_, callback_)
                : DobbyHook(address_, replace_call_, origin_ptr_);
            if (ret == 0) applied_ = true;
        }
    }

    void Remove() {
        if (applied_) {
            DobbyDestroy(address_);
            applied_ = false;
        }
    }

    ~DobbyHookRegister() { Remove(); }

    void* address() const { return address_; }
    bool  applied() const { return applied_; }

    DobbyHookRegister(const DobbyHookRegister&) = delete;
    DobbyHookRegister& operator=(const DobbyHookRegister&) = delete;
};

// DOBBY_HOOK — wraps DobbyHook, replace_call matches original function ABI
// Usage:
//   static auto MyHook_Origin = nullptr;
//   DOBBY_HOOK(0x4C6CC8, MyHook);
//   static void __stdcall MyHook(int arg) {
//       ((void(__stdcall*)(int))MyHook_Origin)(arg);
//   }

#define DOBBY_HOOK(hook_addr, func_name) \
    static DobbyHookRegister _hk_##func_name( \
        (void*)(hook_addr), (void*)func_name, (void**)&func_name##_Origin)

// DOBBY_INSTRUMENT — wraps DobbyInstrument, callback receives RegisterContext*
// Usage:
//   DOBBY_INSTRUMENT(0x48D670, MyInstrument);
//   static void MyInstrument(RegisterContext* ctx, const HookEntryInfo* info) {
//       ctx->general.regs.eax = 1;
//   }

#define DOBBY_INSTRUMENT(hook_addr, func_name) \
    static void func_name(RegisterContext*, const HookEntryInfo*); \
    static DobbyHookRegister _hk_##func_name( \
        (void*)(hook_addr), (DBICallTy)func_name)
