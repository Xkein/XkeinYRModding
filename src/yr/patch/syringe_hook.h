#pragma once

#include <Syringe.h>
#include <Helpers/Macro.h>

#define SYRINGE_PATCH_SECTION_NAME ".sypat"
#pragma section(SYRINGE_PATCH_SECTION_NAME, read)

namespace SyringePatchData { };
__declspec(align(16)) struct syringe_patch_data {
    unsigned int hookAddr;
    unsigned int hookSize;
    const void * hookFunc;
};

#define decl_patch_data(hook, funcname, size) \
namespace SyringePatchData { \
    __declspec(allocate(SYRINGE_PATCH_SECTION_NAME)) \
    syringe_patch_data _hk__ ## hook ## funcname { hook, size, &funcname }; \
};

#define SYRINGE_PATCH(hook, funcname, size) \
EXPORT_FUNC(funcname); \
decl_patch_data(hook, funcname, size) \
EXPORT_FUNC(funcname)
