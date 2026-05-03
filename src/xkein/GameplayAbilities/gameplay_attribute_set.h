#pragma once
#include "core/reflection/reflection.h"
#include "yr/serialization/serialization.h"
#include "yr/parse/parser.h"
 
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

/** Describes a GameplayAttributeData inside an attribute set */
class AttributeSet;

CLASS(BindJs)
struct GameplayAttribute
{
    GameplayAttribute();

    PROPERTY()
    std::string_view AttributeName;
    PROPERTY()
    std::string_view AttributeOwner;

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
    std::vector<GameplayAttribute> Attributes;
};

CLASS(BindJs)
class AttributeSet
{
public:
    /** Find a GameplayAttributeData by GameplayAttribute pointer, returns nullptr if not found */
    GameplayAttributeData* FindAttributeData(const GameplayAttribute* Attribute);
    const GameplayAttributeData* FindAttributeData(const GameplayAttribute* Attribute) const;

    /** Register a new attribute data entry by GameplayAttribute pointer */
    GameplayAttributeData& AddAttributeData(const GameplayAttribute* Attribute, float BaseValue = 0.0f);

    /** Resolve an attribute descriptor in this set by name/owner. */
    const GameplayAttribute* FindAttribute(std::string_view AttributeName, std::string_view AttributeOwner = {}) const;

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

