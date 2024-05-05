#pragma once

#include "core/macro.h"
#include <functional>

#define GLOBAL_INVOKE_ON_CTOR(func) RAII_Invoker CONCAT(RAII_Invoker__, __LINE__)(func, true);
#define GLOBAL_INVOKE_ON_DTOR(func) RAII_Invoker CONCAT(RAII_Invoker__, __LINE__)(func, false);
#define GLOBAL_INVOKE_ON_CTOR_DTOR(ctor, dtor) RAII_Invoker CONCAT(RAII_Invoker__, __LINE__)(ctor, dtor);

class RAII_Invoker
{
    std::function<void()> _dtor;

public:
    RAII_Invoker(std::function<void()> func, int isCtor = true)
    {
        if (isCtor)
        {
            func();
        }
        else
        {
            _dtor = std::move(func);
        }
    }
    RAII_Invoker(std::function<void()> ctor, std::function<void()> dtor) : _dtor(std::move(dtor))
    {
        ctor();
    }
    ~RAII_Invoker()
    {
        if (_dtor)
        {
            _dtor();
        }
    }
};
