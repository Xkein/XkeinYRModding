#pragma once

#include "yr/yr_event.h"
#include "yr/patch/patch.h"

struct DebugPatchCallInfo
{
    std::vector<syringe_patch_data*> callingList;
    std::vector<syringe_patch_data*> calledList;
};

DebugPatchCallInfo GetDebugPatchCallInfo();

class YrHookDiagnostic
{
public:

};

