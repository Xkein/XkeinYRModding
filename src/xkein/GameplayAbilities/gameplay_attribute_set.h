#pragma once
#include "core/reflection/reflection.h"
#include "core/string/string_name.h"
#include "yr/serialization/serialization.h"
 
class AttributeSet;
struct FGameplayEffectModCallbackData;

/** Place in an AttributeSet to create an attribute that can be accesed using FGameplayAttribute. It is strongly encouraged to use this instead of raw float attributes */

CLASS(BindJs)
struct GameplayAttributeData
{
	GameplayAttributeData()
		: BaseValue(0.f)
		, CurrentValue(0.f)
	{}

	GameplayAttributeData(float DefaultValue)
		: BaseValue(DefaultValue)
		, CurrentValue(DefaultValue)
	{}

	virtual ~GameplayAttributeData()
	{}

	/** Returns the current value, which includes temporary buffs */
	float GetCurrentValue() const
    {
        return CurrentValue;
    }

	/** Modifies current value, normally only called by ability system or during initialization */
	void SetCurrentValue(float NewValue)
    {
        CurrentValue = NewValue;
    }

	/** Returns the base value which only includes permanent changes */
	float GetBaseValue() const
    {
        return BaseValue;
    }

	/** Modifies the permanent base value, normally only called by ability system or during initialization */
	void SetBaseValue(float NewValue)
    {
        BaseValue = NewValue;
    }

protected:
    GENERATED_BODY(GameplayAttributeData);
    
	PROPERTY()
	float BaseValue;

	PROPERTY()
	float CurrentValue;
};


CLASS(BindJs)
struct GameplayAttribute
{
    GameplayAttribute();

    PROPERTY()
    StringName AttributeName;
    PROPERTY()
    StringName AttributeOwner;

	bool IsValid() const { return !AttributeName.IsEmpty(); }

    /** Get current value from the given attribute set (name lookup) */
    float GetNumericValue(const AttributeSet* Set) const;

    /** Get base value from the given attribute set (name lookup) */
    float GetNumericValueBase(const AttributeSet* Set) const;

    /** Set base value on the given attribute set (name lookup) */
    void SetNumericValueBase(AttributeSet* Set, float NewBaseValue) const;

    /** Set current value on the given attribute set (name lookup) */
    void SetNumericValue(AttributeSet* Set, float NewValue) const;
};

CLASS(BindJs, IniAutoLoad)
struct AttributeSetDefine
{
    PROPERTY()
	StringName AttributeSetCreator;
    PROPERTY()
    std::vector<GameplayAttribute> Attributes;
};

CLASS(BindJs)
class AttributeSet
{
public:
	/** Find a GameplayAttributeData by GameplayAttribute pointer, returns nullptr if not found */
    GameplayAttributeData* FindAttributeData(const GameplayAttribute* Attribute);
    const GameplayAttributeData* FindAttributeData(const GameplayAttribute* Attribute) const;

    /** Get read-only access to the attribute data map */
    const std::map<const GameplayAttribute*, GameplayAttributeData>& GetAttributeDataMap() const { return AttributeDataMap; }

    /** Register a new attribute data entry by GameplayAttribute pointer */
    GameplayAttributeData& AddAttributeData(const GameplayAttribute* Attribute, float BaseValue = 0.0f);

    /** Resolve an attribute descriptor in this set by name/owner. */
    const GameplayAttribute* FindAttribute(StringName AttributeName, StringName AttributeOwner = {}) const;

    /** Called before a gameplay effect executes on an attribute. Return false to skip the modification. */
    virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) { return true; }

    /** Called after a gameplay effect successfully executes on an attribute. */
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {}

    /** Called before any attribute modification (base or current value). NewValue is mutable for clamping. */
    virtual void PreAttributeChange(const GameplayAttribute& Attribute, float& NewValue) {}

    /** Called after any attribute modification (base or current value). OldValue is pre-modification, NewValue is final. */
    virtual void PostAttributeChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) {}

    /** Called before a base value modification. NewValue is mutable for clamping. Const to prevent direct state modification. */
    virtual void PreAttributeBaseChange(const GameplayAttribute& Attribute, float& NewValue) const {}

    /** Called after a base value modification. OldValue is pre-modification, NewValue is final. */
    virtual void PostAttributeBaseChange(const GameplayAttribute& Attribute, float OldValue, float NewValue) const {}

private:
    /** Actual attribute data storage (attribute ptr -> data) */
    std::map<const GameplayAttribute*, GameplayAttributeData> AttributeDataMap;
};


CLASS(BindJs)
class AttributeMetaData
{
public:
    AttributeMetaData();
    
    PROPERTY()
    float BaseValue;
    PROPERTY()
    float MinValue;
    PROPERTY()
    float MaxValue;
    PROPERTY()
    bool CanStack;
};

/** 
 * Simplified Aggregator for evaluating attribute modifiers.
 * In UE, this is a complex system. For frame-sync, we keep it simple.
 */
class GameplayEffectAggregator
{
public:
    /** Evaluate an attribute's final value given base value and active modifiers */
    static float EvaluateAttribute(float BaseValue, float SumAddBase, float SumMultiplyAdditive,
        float SumDivideAdditive, float ProductMultiplyCompound, float SumAddFinal, bool bHasOverride, float OverrideValue)
    {
        if (bHasOverride) return OverrideValue;

        float Result = BaseValue + SumAddBase;
        Result *= (1.0f + SumMultiplyAdditive);
        float DivFactor = (1.0f + SumDivideAdditive);
        if (DivFactor == 0.0f) DivFactor = 1.0f;
        Result /= DivFactor;
        Result *= ProductMultiplyCompound;
        Result += SumAddFinal;
        return Result;
    }
};

// -------------------------------------------------------------------------
// Attribute accessor macros (StringName-based lookup, no FProperty dependency)
// -------------------------------------------------------------------------

/** Creates a static function that returns a GameplayAttribute for the given property.
 *  Uses StringName lookup: AttributeName = #PropertyName, AttributeOwner = #ClassName. */
#define GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    static GameplayAttribute Get##PropertyName##Attribute() \
    { \
        GameplayAttribute Attr; \
        Attr.AttributeName = StringName(#PropertyName); \
        Attr.AttributeOwner = StringName(#ClassName); \
        return Attr; \
    }

/** Creates a simple getter that reads the current value of an attribute. */
#define GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    float Get##PropertyName() const { return PropertyName.GetCurrentValue(); }

/** Creates a simple setter that writes the current value of an attribute. */
#define GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    void Set##PropertyName(float NewVal) { PropertyName.SetCurrentValue(NewVal); }

/** Creates an initializer that writes both base and current values. */
#define GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \
    void Init##PropertyName(float NewVal) \
    { \
        PropertyName.SetBaseValue(NewVal); \
        PropertyName.SetCurrentValue(NewVal); \
    }

/** Combined macro that expands all four accessor macros for a single attribute. */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


CLASS(BindJs)
class CustomAttributeSet : public AttributeSet
{
public:
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
