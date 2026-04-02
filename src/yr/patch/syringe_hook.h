#pragma once

#include <Syringe.h>
#include <Helpers/Macro.h>

#define SYRINGE_PATCH_SECTION_NAME ".sypat"
#pragma section(SYRINGE_PATCH_SECTION_NAME, read)

namespace SyringePatchData { };
#pragma pack(push, 16)
__declspec(align(16)) struct syringe_patch_data {
    unsigned int hookAddr;
    unsigned int hookSize;
    const void * hookFunc;
    const char* category;
    bool unsafe;
};
#pragma pack(pop)

#define decl_patch_data(hook, funcname, size, category, unsafe) \
namespace SyringePatchData { \
    __declspec(allocate(SYRINGE_PATCH_SECTION_NAME)) \
    syringe_patch_data _hk__ ## hook ## funcname { hook, size, &funcname, category, unsafe }; \
    static_assert(size >= 5, "hook override size must be >= 5 !"); \
};

#define __SYRINGE_PATCH_IMPL(hook, funcname, size, category, unsafe) \
EXPORT_FUNC(funcname); \
decl_patch_data(hook, funcname, size, category, unsafe) \
EXPORT_FUNC(funcname)

#define SYRINGE_PATCH(hook, funcname, size) \
__SYRINGE_PATCH_IMPL(hook, funcname##_HOOK_##hook##_##size, size, nullptr, false)

#define SYRINGE_PATCH_WITH_CATEGORY(hook, funcname, size, category) \
__SYRINGE_PATCH_IMPL(hook, funcname##_HOOK_##hook##_##size, size, category, false)

#define SYRINGE_PATCH_UNSAFE(hook, funcname, size) \
__SYRINGE_PATCH_IMPL(hook, funcname##_HOOK_##hook##_##size, size, nullptr, true)
