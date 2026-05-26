#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

class AbilitySystemComponent;

/** Rather a tag was added or removed, used in callbacks */
ENUM()
enum EGameplayTagEventType : int
{
    /** Event only happens when tag is new or completely removed */
    NewOrRemoved,

    /** Event happens any time tag "count" changes */
    AnyCountChange		
};

/** Information about a gameplay effect being removed, passed to removal delegate callbacks */
CLASS()
struct FGameplayEffectRemovalInfo
{
    /** Whether the effect was removed before its natural expiry */
    bool bPrematureRemoval = false;

    /** Stack count at the time of removal */
    int32 StackCount = 0;

    /** Context from when the gameplay effect was applied */
    GameplayEffectContextHandle EffectContext;
};

/** Evaluated modifier data used by calculation classes and delegate callbacks */
CLASS()
struct FGameplayModifierEvaluatedData
{
    PROPERTY()
    GameplayAttribute Attribute;

    PROPERTY()
    EGameplayModOpType ModifierOp = EGameplayModOpType::Additive;

    PROPERTY()
    float Magnitude = 0.0f;

    bool IsValid = false;
};

/** Callback data passed to Pre/PostGameplayEffectExecute on AttributeSets */
struct FGameplayEffectModCallbackData
{
    /** The effect spec being applied (referenced, not copied) */
    const GameplayEffectSpec& EffectSpec;

    /** Evaluated modifier data for the attribute being modified */
    FGameplayModifierEvaluatedData EvaluatedData;

    /** Target ability system component receiving the effect */
    AbilitySystemComponent* Target;

    FGameplayEffectModCallbackData(const GameplayEffectSpec& InEffectSpec,
        const FGameplayModifierEvaluatedData& InEvalData,
        AbilitySystemComponent* InTarget)
        : EffectSpec(InEffectSpec)
        , EvaluatedData(InEvalData)
        , Target(InTarget)
    {}
};
