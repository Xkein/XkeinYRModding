#pragma once
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"

CLASS(BindJs)
class CustomAttributeSet : public AttributeSet
{
public:
    CustomAttributeSet();

    FUNCTION()
    static CustomAttributeSet* CreateCustomAttributeSet();
    
    bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override
    {
        if (OnK2_PreGameplayEffectExecute)
        {
            return OnK2_PreGameplayEffectExecute(&Data);
        }
        return true;
    }

    void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override
    {
        if (OnK2_PostGameplayEffectExecute)
        {
            OnK2_PostGameplayEffectExecute(&Data);
        }
    }

    void PreAttributeChange(const GameplayAttribute& Attribute, float& NewValue) override
    {
        if (OnK2_PreAttributeChange)
        {
            OnK2_PreAttributeChange(Attribute, NewValue);
        }
    }

    void PostAttributeChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) override
    {
        if (OnK2_PostAttributeChange)
        {
            OnK2_PostAttributeChange(Attribute, OldValue, NewValue);
        }
    }

    void PreAttributeBaseChange(const GameplayAttribute& Attribute, float& NewValue) const override
    {
        if (OnK2_PreAttributeBaseChange)
        {
            OnK2_PreAttributeBaseChange(Attribute, NewValue);
        }
    }

    void PostAttributeBaseChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) const override
    {
        if (OnK2_PostAttributeBaseChange)
        {
            OnK2_PostAttributeBaseChange(Attribute, OldValue, NewValue);
        }
    }

    PROPERTY()
    std::function<bool(FGameplayEffectModCallbackData*)> OnK2_PreGameplayEffectExecute;

    PROPERTY()
    std::function<void(const FGameplayEffectModCallbackData*)> OnK2_PostGameplayEffectExecute;

    PROPERTY()
    std::function<void(const GameplayAttribute&, float&)> OnK2_PreAttributeChange;

    PROPERTY()
    std::function<void(const GameplayAttribute&, float, float)> OnK2_PostAttributeChange;

    PROPERTY()
    std::function<void(const GameplayAttribute&, float&)> OnK2_PreAttributeBaseChange;

    PROPERTY()
    std::function<void(const GameplayAttribute&, float, float)> OnK2_PostAttributeBaseChange;
};
