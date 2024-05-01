#include "yr/yr_hook_diagnostic.h"

int YrHookDiagnostic::GetHookCallTimes(YrHookEvent* hookEvent)
{
    return hookEvent->_callTimes;
}
