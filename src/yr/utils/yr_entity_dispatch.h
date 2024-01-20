#pragma once

#include "yr/entity.h"

#include <Helpers/Cast.h>

template<class... _Types>
struct DispatchTypes
{};

template<class T, class... _Types>
struct DispatchTypes<T, _Types...>
{
    using Type = T;
    using Next = DispatchTypes<_Types...>;

    static constexpr bool hasNext = sizeof...(_Types) > 0;
};

class YrEntityDispatch
{
    template<class Operation, class DispatchTypes>
    inline static void DispatchInternal(Operation& op, YrEntity yrEntity)
    {
        using T = DispatchTypes::Type;

        if (auto yrTechno = abstract_cast<T*>(yrEntity.yrObject))
        {
            op(yrTechno);
        }

        if constexpr (DispatchTypes::hasNext)
        {
            DispatchInternal<Operation, typename DispatchTypes::Next>(op, yrEntity);
        }
    }

public:
    template<class DispatchTypes, class Operation>
    inline static void Dispatch(Operation& op, YrEntity yrEntity)
    {
        DispatchInternal<Operation, DispatchTypes>(op, yrEntity);
    }
};

