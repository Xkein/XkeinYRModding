#include "gameplay_attribute_set.h"

GameplayAttribute::GameplayAttribute() {}

float GameplayAttribute::GetNumericValue(const AttributeSet* Set) const
{
    if (!Set) return 0.0f;
    const auto* Data = Set->FindAttributeData(this);
    return Data ? Data->GetCurrentValue() : 0.0f;
}

float GameplayAttribute::GetNumericValueBase(const AttributeSet* Set) const
{
    if (!Set) return 0.0f;
    const auto* Data = Set->FindAttributeData(this);
    return Data ? Data->GetBaseValue() : 0.0f;
}

void GameplayAttribute::SetNumericValueBase(AttributeSet* Set, float NewBaseValue) const
{
    if (!Set) return;
    auto* Data = Set->FindAttributeData(this);
    if (Data) Data->SetBaseValue(NewBaseValue);
}

void GameplayAttribute::SetNumericValue(AttributeSet* Set, float NewValue) const
{
    if (!Set) return;
    auto* Data = Set->FindAttributeData(this);
    if (Data) Data->SetCurrentValue(NewValue);
}

GameplayAttributeData* AttributeSet::FindAttributeData(const GameplayAttribute* Attribute)
{
    if (!Attribute) return nullptr;
    auto It = AttributeDataMap.find(Attribute);
    return (It != AttributeDataMap.end()) ? &It->second : nullptr;
}

const GameplayAttributeData* AttributeSet::FindAttributeData(const GameplayAttribute* Attribute) const
{
    if (!Attribute) return nullptr;
    auto It = AttributeDataMap.find(Attribute);
    return (It != AttributeDataMap.end()) ? &It->second : nullptr;
}

GameplayAttributeData& AttributeSet::AddAttributeData(const GameplayAttribute* Attribute, float BaseValue)
{
    if (!Attribute)
    {
        static GameplayAttributeData emptyData;
        return emptyData;
    }
    auto [It, Inserted] = AttributeDataMap.emplace(Attribute, GameplayAttributeData(BaseValue));
    return It->second;
}

const GameplayAttribute* AttributeSet::FindAttribute(std::string_view AttributeName, std::string_view AttributeOwner) const
{
    for (const auto& [Attribute, Data] : AttributeDataMap)
    {
        if (Attribute->AttributeName != AttributeName) continue;
        if (!AttributeOwner.empty() && Attribute->AttributeOwner != AttributeOwner) continue;
        return Attribute;
    }
    return nullptr;
}

AttributeMetaData::AttributeMetaData()
    : BaseValue(0.0f), MinValue(0.0f), MaxValue(1.0f), CanStack(false)
{}
