#pragma once
#include "core/reflection/reflection.h"
#include "yr/parse/parser.h"
#include "yr/component/ini_component.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"

CLASS(IniComponent, IniSection = "GAS")
struct AbilitySystemGlobals
{
    PROPERTY()
    std::vector<AttributeSetDefine*> DefaultAttributeSets;
};

#ifndef __HEADER_TOOL__
namespace detail
{
    // Parser for GameplayModifierInfo (format: "AttributeName:Magnitude:ModOp")
    // Example: "Health:10.0:AddBase" or "+Health:10:AddBase"
    template<>
    struct Parser<GameplayModifierInfo>
    {
        static bool Read(std::string_view str, GameplayModifierInfo& result)
        {
            // Parse "AttributeName:Magnitude:ModOp"
            auto firstColon = str.find(':');
            if (firstColon == std::string_view::npos) return false;
            
            auto secondColon = str.find(':', firstColon + 1);
            if (secondColon == std::string_view::npos) return false;
            
            // Extract attribute name (skip leading + or - if present)
            std::string_view attrName = str.substr(0, firstColon);
            if (attrName.size() > 0 && (attrName[0] == '+' || attrName[0] == '-'))
            {
                attrName = attrName.substr(1);
            }
            result.Attribute.AttributeName = attrName;
            
            // Extract magnitude
            std::string_view magStr = str.substr(firstColon + 1, secondColon - firstColon - 1);
            float magValue = 0.0f;
            if (::Parser<float>::Read(magStr, magValue))
            {
                result.ModifierMagnitude.MagnitudeCalculationType = EGameplayEffectMagnitudeCalculation::ScalableFloat;
                result.ModifierMagnitude.ScalableFloatMagnitude = magValue;
            }
            
            // Extract mod operation (uses generic enum parser via ENUM() reflection)
            std::string_view opStr = str.substr(secondColon + 1);
            return ::Parser<EGameplayModOpType>::Read(opStr, result.ModifierOp);
        }
    };
    
    
    template<>
    struct Parser<GameplayTag>
    {
        static bool Read(std::string_view str, GameplayTag& result)
        {
            GameplayTag tag;
            if(::Parser<decltype(result.TagName)>::Read(str, tag.TagName)) {
                if (tag.IsValid()) {
                    result = tag;
                    return true;
                }
            }
            return false;
        }
    };

    template<>
    struct Parser<GameplayTagContainer>
    {
        static bool Read(std::string_view str, GameplayTagContainer& result)
        {
            GameplayTagContainer tag;
            if(::Parser<decltype(result.GameplayTags)>::Read(str, tag.GameplayTags)) {
                if (tag.IsValid()) {
                    result = tag;
                    return true;
                }
            }
            return false;
        }
    };
}

template<>
bool IniComponentLoader::Load(IniReader& parser, const char* pSection, const char* pKey, AttributeSetDefine& value)
{
    std::vector<std::string_view> attributes;
    if (!parser.Read(pSection, pKey, attributes))
    {
        return false;
    }
    value.Attributes.clear();
    for (const auto& attrName : attributes)
    {
        GameplayAttribute attr;
        attr.AttributeOwner = get_pool_string_view(pSection);
        attr.AttributeName = attrName;
        value.Attributes.push_back(attr);
    }
    return true;
}
#endif
