#include "xkein/GameplayAbilities/custom_attribute_set.h"

CustomAttributeSet::CustomAttributeSet() : AttributeSet()
{
}

CustomAttributeSet* CustomAttributeSet::CreateCustomAttributeSet()
{
    return new CustomAttributeSet();
}
