#pragma once
#include "core/reflection/reflection.h"
#include "yr/parse/parser.h"
#include "yr/component/ini_component.h"
#include "scripting/common/script_function.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include <cstring>
#include <unordered_map>

CLASS(IniComponent, IniSection = "GAS")
struct AbilitySystemGlobals
{
    PROPERTY()
    std::vector<AttributeSetDefine*> DefaultAttributeSets;

    PROPERTY()
    GameplayTag ActivateFailCanActivateAbilityTag; // [GAS] ActivateFailCanActivateAbilityTag=Ability.ActivateFail

    /** Curve tables loaded from [CurveTable.XXX] INI sections, keyed by table name.
     *  Each curve maps ability level (int32) → value (float).
     *  Uses unordered_map since StringName has std::hash but no operator<. */
    std::unordered_map<StringName, std::map<int32, float>> CurveTables;

    void AfterLoadIni(IniReader& parser, const char* pSection, const char* pKey)
    {
        CCINIClass* pIni = parser.GetIni();
        if (!pIni) return;

        for (auto* pSec = pIni->Sections.First(); pSec && pSec->IsValid(); pSec = pSec->Next())
        {
            const char* sectionName = pSec->Name;
            if (!sectionName) continue;

            // Match sections starting with "CurveTable."
            if (strncmp(sectionName, "CurveTable.", 11) != 0) continue;

            StringName tableName(sectionName + 11); // skip "CurveTable." prefix
            if (tableName.IsEmpty()) continue;

            std::map<int32, float> curve;
            int keyCount = pIni->GetKeyCount(sectionName);
            for (int i = 0; i < keyCount; i++)
            {
                const char* keyName = pIni->GetKeyName(sectionName, i);
                if (!keyName) continue;

                int32 level = atoi(keyName);
                float value = static_cast<float>(pIni->ReadDouble(sectionName, keyName, 0.0));
                curve[level] = value;
            }

            if (!curve.empty())
            {
                CurveTables[tableName] = std::move(curve);
            }
        }
    }
};

CLASS(BindJs)
struct GameplayAbilityCreator : public ScriptFunction<GameplayAbility*(GameplayAbilityDefine* define, AbilitySystemComponent* component)>
{
    FUNCTION()
    GameplayAbilityCreator(std::function<GameplayAbility*(GameplayAbilityDefine*, AbilitySystemComponent*)> func) : ScriptFunction(func) { }
};

CLASS(BindJs)
struct AttributeSetCreator : public ScriptFunction<AttributeSet*(AttributeSetDefine* define, AbilitySystemComponent* component)>
{
    FUNCTION()
    AttributeSetCreator(std::function<AttributeSet*(AttributeSetDefine*, AbilitySystemComponent*)> func) : ScriptFunction(func) { }
};

CLASS(BindJs)
class GameplayAbilitySystem
{
public:
    static void Tick();

	PROPERTY()
    static StringName ScriptFunctionCategoryAbility;
	PROPERTY()
    static StringName ScriptFunctionCategoryAttributeSet;

    static GameplayAbility* CreateAbility(const StringName& name, GameplayAbilityDefine* define, AbilitySystemComponent* component);
    static AttributeSet* CreateAttributeSet(const StringName& name, AttributeSetDefine* define, AbilitySystemComponent* component);

    /** Access the global GameplayCueManager singleton */
    static struct GameplayCueManager* GetCueManager();

    FUNCTION()
    static inline AbilitySystemComponent* GetAbilitySystemComponent(entt::entity entity) {
        return gEntt->try_get<AbilitySystemComponent>(entity);
    }
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

    // Parser for FScalableFloat: supports simple float format for backward compatibility
    // with existing INI keys that use bare float values (e.g. Period=2.0)
    template<>
    struct Parser<FScalableFloat>
    {
        static bool Read(std::string_view str, FScalableFloat& result)
        {
            float value = 0.0f;
            if (::Parser<float>::Read(str, value))
            {
                result.Value = value;
                return true;
            }
            return false;
        }
    };

    // Parser for GameplayTagQuery: comma-separated tag list creates an AnyTagsMatch query
    template<>
    struct Parser<GameplayTagQuery>
    {
        static bool Read(std::string_view str, GameplayTagQuery& result)
        {
            GameplayTagContainer tempContainer;
            if (::Parser<GameplayTagContainer>::Read(str, tempContainer))
            {
                result = GameplayTagQuery::MakeQuery_MatchAnyTagsMatch(tempContainer);
                return true;
            }
            return false;
        }
    };
}

template<>
inline bool IniComponentLoader::Load(IniReader& parser, const char* pSection, const char* pKey, AttributeSetDefine& value)
{
    std::vector<StringName> attributes;
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
