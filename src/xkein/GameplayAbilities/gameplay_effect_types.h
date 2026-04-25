#pragma once
#include "core/reflection/reflection.h"

/** Rather a tag was added or removed, used in callbacks */
ENUM()
enum EGameplayTagEventType : int
{
    /** Event only happens when tag is new or completely removed */
    NewOrRemoved,

    /** Event happens any time tag "count" changes */
    AnyCountChange		
};
