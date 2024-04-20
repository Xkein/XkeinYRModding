#include "transform_utils.h"
#include "yr/utils/yr_entity_dispatch.h"

#include <TechnoClass.h>
#include <FootClass.h>


struct GetTransformOperation
{
    template<class T>
    void operator()(T)
    {
        result = false;
    }
    void operator()(TechnoClass* yrObject)
    {

    }

    bool result {true};
};

bool GetTransformFromYr(AbstractClass* yrObject, Transform& transform)
{
    GetTransformOperation op;
    YrEntityDispatch::Dispatch<DispatchTypes<TechnoClass>>(op, yrObject);
    return op.result;
}

bool ApplyTransformToYr(AbstractClass* yrObject, const Transform& transform)
{
    return false;
}
