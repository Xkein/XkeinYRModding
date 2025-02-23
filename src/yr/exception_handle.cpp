#include "yr_hook.h"
#include "runtime/logger/logger.h"
#include "debug_util.h"

SYRINGE_PATCH(0x4C8FE0, Exception_Handler, 9)
{
    gLogger->error("Fatal Error!");
	GET(LPEXCEPTION_POINTERS, pExs, EDX);
    std::string* stackTrace = nullptr;
    ExceptionFilterGetInfo(pExs, stackTrace);
    gLogger->error("stack trace : {}", *stackTrace);
    gLogger->flush();
    delete stackTrace;
    return 0;
}