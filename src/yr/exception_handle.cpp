#include "yr_hook.h"
#include "runtime/logger/logger.h"
#include "debug_util.h"

SYRINGE_PATCH(0x4C8FE0, Exception_Handler, 9)
{
	GET(LPEXCEPTION_POINTERS, pExs, EDX);
    std::string* stackTrace = nullptr;
    ExceptionFilterGetInfo(pExs, stackTrace);
    gLogger->error("[Fatal Error!] stack trace : {}", *stackTrace);
    gLogger->flush();
    delete stackTrace;
    return 0;
}