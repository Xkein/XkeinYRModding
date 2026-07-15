#pragma once
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "core/tool/delegate.h"

CLASS(BindJs, AutoSavegame, Swizzleable)
class CustomAttributeSet : public AttributeSet
{
public:
    CustomAttributeSet();

    FUNCTION()
    static CustomAttributeSet* Create();
    
    bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override
    {
        if (OnK2_PreGameplayEffectExecute.IsBound())
        {
            return OnK2_PreGameplayEffectExecute.Execute(&Data);
        }
        return true;
    }

    void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override
    {
        if (OnK2_PostGameplayEffectExecute.IsBound())
        {
            OnK2_PostGameplayEffectExecute.Execute(&Data);
        }
    }

    void PreAttributeChange(const GameplayAttribute& Attribute, float& NewValue) override
    {
        if (OnK2_PreAttributeChange.IsBound())
        {
            OnK2_PreAttributeChange.Execute(Attribute, NewValue);
        }
    }

    void PostAttributeChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) override
    {
        if (OnK2_PostAttributeChange.IsBound())
        {
            OnK2_PostAttributeChange.Execute(Attribute, OldValue, NewValue);
        }
    }

    void PreAttributeBaseChange(const GameplayAttribute& Attribute, float& NewValue) const override
    {
        if (OnK2_PreAttributeBaseChange.IsBound())
        {
            OnK2_PreAttributeBaseChange.Execute(Attribute, NewValue);
        }
    }

    void PostAttributeBaseChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) const override
    {
        if (OnK2_PostAttributeBaseChange.IsBound())
        {
            OnK2_PostAttributeBaseChange.Execute(Attribute, OldValue, NewValue);
        }
    }

    PROPERTY(Savegame)
    TDelegate<bool(FGameplayEffectModCallbackData*)> OnK2_PreGameplayEffectExecute;

    PROPERTY(Savegame)
    TDelegate<void(const FGameplayEffectModCallbackData*)> OnK2_PostGameplayEffectExecute;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayAttribute&, float&)> OnK2_PreAttributeChange;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayAttribute&, float, float)> OnK2_PostAttributeChange;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayAttribute&, float&)> OnK2_PreAttributeBaseChange;

    PROPERTY(Savegame)
    TDelegate<void(const GameplayAttribute&, float, float)> OnK2_PostAttributeBaseChange;
};
IMPL_YR_SERIALIZE_SWIZZLE(CustomAttributeSet);