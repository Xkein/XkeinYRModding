#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include "xkein/GameplayAbilities/gameplay_effect_execution_calculation.h"
#include "xkein/GameplayAbilities/gameplay_mod_magnitude_calculation.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_repeat.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_spawn_actor.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_attribute_change.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_effect_applied.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_event.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_tag.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_effect_removed.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_input.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_target_data.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_static.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_actor.h"
#include "xkein/GameplayAbilities/custom_gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_ability_target_actor.h"
#include "xkein/GameplayAbilities/gameplay_ability_world_reticle.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "xkein/GameplayAbilities/custom_gameplay_ability.h"
#include "xkein/GameplayAbilities/custom_attribute_set.h"

UsingCppType(ActiveGameplayEffectHandle);
UsingCppType(ActiveGameplayEffect);
UsingCppType(ActiveGameplayEffectsContainer);
UsingCppType(AttributeSet);
UsingCppType(CustomAttributeSet);
UsingCppType(CustomGameplayAbility);
UsingCppType(AttributeSetDefine);
UsingCppType(AttributeMetaData);
UsingCppType(AbilityTriggerData);
UsingCppType(AbilitySystemComponent);
UsingCppType(AbilitySystemComponentType);
UsingCppType(GameplayAbility);
UsingCppType(GameplayAbilityDefine);
UsingCppType(GameplayAbilitySystem);
UsingCppType(GameplayAttribute);
UsingCppType(GameplayAttributeData);
UsingCppType(FGameplayEffectRemovalInfo);
UsingCppType(FOnAttributeChangeData);
UsingCppType(GameplayAbilityTargetData);
UsingCppType(GameplayAbilityTargetDataHandle);
UsingCppType(GameplayAbilitySpecDef);
UsingCppType(GameplayEventData);
UsingCppType(GameplayEffect);
UsingCppType(GameplayEffectComponent);
UsingCppType(GameplayCueNotify_Static);
UsingCppType(GameplayCueNotify_Actor);
UsingCppType(GameplayCueParameters);
UsingCppType(GameplayCueNotifyDefine);
UsingCppType(GameplayCueNotifyDefine_Static);
UsingCppType(GameplayCueNotifyDefine_Burst);
UsingCppType(GameplayCueNotifyDefine_Actor);
UsingCppType(GameplayCueNotifyDefine_BurstLatent);
UsingCppType(GameplayCueNotify_Burst);
UsingCppType(GameplayCueNotify_BurstLatent);
UsingCppType(GameplayCueNotify_Looping);
UsingCppType(GameplayCueNotify_BurstEffects);
UsingCppType(GameplayCueNotify_LoopingEffects);
UsingCppType(CustomGameplayCueNotify_Static);
UsingCppType(CustomGameplayCueNotify_BurstLatent);
UsingCppType(CustomGameplayCueNotify_Looping);
UsingCppType(GameplayTag);
UsingCppType(GameplayTagContainer);
UsingCppType(GameplayAbilitySpec);
UsingCppType(GameplayAbilitySpecHandle);
UsingCppType(GameplayAbilityActorInfo);
UsingCppType(GameplayAbilityActivationInfo);
UsingCppType(FAggregator);

UsingStdVector(AttributeSet);
UsingStdVector(AttributeSet*);
UsingStdVector(AttributeSetDefine*);
UsingStdVector(AbilityTriggerData);
UsingStdVector(GameplayTag);
UsingStdVector(GameplayTag*);
UsingStdVector(GameplayAttribute);
UsingStdVector(GameplayAbility);
UsingStdVector(GameplayAbility*);
UsingStdVector(GameplayAbilityDefine*);
UsingStdVector(GameplayAbilitySpec);
UsingStdVector(GameplayAbilitySpecHandle);
UsingStdVector(GameplayEffect);
UsingStdVector(GameplayEffect*);
UsingStdVector(GameplayEffectCue*);
UsingStdVector(GameplayEffectComponent*);
UsingStdVector(GameplayEffectExecutionDefinition);
UsingStdVector(GameplayModifierInfo);
UsingStdVector(GameplayModifierInfo*);
UsingStdVector(FConditionalGameplayEffect);
UsingStdVector(FGameplayEffectExecutionScopedModifierInfo);

UsingCppType(GameplayAbilityTargetData_SingleTargetHit);
UsingCppType(GameplayAbilityTargetData_ActorArray);
UsingCppType(GameplayAbilityTargetData_LocationInfo);
UsingCppType(AbilityTask_Repeat);
UsingCppType(AbilityTask_SpawnActor);
UsingCppType(AbilityTask_WaitAttributeChange);
UsingCppType(AbilityTask_WaitDelay);
UsingCppType(AbilityTask_WaitGameplayEffectApplied);
UsingCppType(AbilityTask_WaitGameplayEvent);
UsingCppType(AbilityTask_WaitGameplayTagAdded);
UsingCppType(AbilityTask_WaitGameplayTagRemoved);
UsingCppType(AbilityTask_WaitGameplayEffectRemoved);
UsingCppType(AbilityTask_WaitInput);
UsingCppType(AbilityTask_WaitTargetData);
UsingCppType(GameplayAbilityTargetActor);
UsingCppType(GameplayAbilityTargetActor_LineTrace);
UsingCppType(GameplayAbilityTargetActor_Radius);
UsingCppType(GameplayAbilityTargetActor_GroundTrace);
UsingCppType(GameplayAbilityTargetActor_ActorPlacement);
UsingCppType(GameplayAbilityWorldReticle);
UsingCppType(GameplayTagQuery);
UsingCppType(GameplayTagRequirements);
UsingCppType(AbilityTask);
UsingCppType(AbilityTaskCreator);
UsingCppType(GameplayAbilityCreator);
UsingCppType(AttributeSetCreator);
UsingCppType(GameplayEffectSpec);
UsingCppType(GameplayEffectCue);
UsingCppType(FGameplayEffectQuery);
UsingCppType(FScalableFloat);
UsingCppType(GameplayEffectCalculation);
UsingCppType(GameplayEffectExecutionCalculation);
UsingCppType(GameplayEffectExecutionDefinition);
UsingCppType(GameplayEffectContextHandle);
UsingCppType(GameplayEffectContext);
UsingCppType(FGameplayEffectModCallbackData);
UsingCppType(FGameplayModifierEvaluatedData);
UsingCppType(FGameplayEffectExecutionScopedModifierInfo);
UsingCppType(FConditionalGameplayEffect);
UsingCppType(GameplayModMagnitudeCalculation);
UsingCppType(GameplayModifierInfo);
UsingCppType(GameplayEffectModifierMagnitude);
UsingCppType(GameplayEffectAttributeCaptureDefinition);
UsingCppType(FGameplayEffectCustomExecutionParameters);
UsingCppType(FGameplayEffectCustomExecutionOutput);
UsingCppType(AttributeBasedFloat);
UsingCppType(CustomCalculationBasedFloat);
UsingCppType(SetByCallerFloat);
UsingCppType(ScriptFunction<GameplayAbility * (GameplayAbilityDefine * _0, AbilitySystemComponent * _1)>);
UsingCppType(ScriptFunction<AttributeSet * (AttributeSetDefine * _0, AbilitySystemComponent * _1)>);
UsingCppType(ScriptFunction<AbilityTask * (GameplayAbility * _0, AbilitySystemComponent * _1)>);
UsingCppType(ScriptFunction<GameplayCueNotify_Static * ()>);
UsingCppType(ScriptFunction<GameplayCueNotify_Actor * ()>);

UsingStdVector(GameplayEffectAttributeCaptureDefinition);
UsingStdVector(entt::entity);
UsingStdVector(StringName);
UsingStdVector(AnimTypeClass*);

#include "scripting/javascript/js_events.h"
UsingCppTypeWithRefCache(JsGameEvents);
UsingCppTypeWithRefCache(JsPhysicsEvents);
UsingCppTypeWithRefCache(JsEventOnCtor);
UsingCppTypeWithRefCache(JsEventOnDtor);
UsingCppTypeWithRefCache(JsEvents);
#include "scripting/javascript/js_cpp_helper.h"
UsingCppTypeWithRefCache(JsCppHelper);

#include "core/tool/script_function.h"
UsingCppType(ScriptFunctionBase);
UsingCppType(ScriptFunctionRegister);

#include "core/string/string_name.h"
UsingCppType(StringName);

#include "audio/audio.h"
UsingCppType(WwiseSoundBankRef);
#include "audio/audio_component.h"
UsingCppType(AudioSystem);
UsingCppType(AudioComponent);

#include "physics/physics_component.h"
UsingCppType(PhysicsComponent)
UsingCppType(PhysicsTypeComponent)
#include "physics/physics.h"
UsingCppType(PhysicsCollisionAddAndPersistResult);
UsingCppType(PhysicsCollisionRemoveResult);

#include "input/input.h"
UsingCppType(Input);
UsingCppType(gainput::InputMap);
// not implement
UsingCppType(gainput::InputManager);
UsingCppType(gainput::MappedInputListener);
UsingCppType(gainput::DeviceButtonSpec);
MuteFunctionPtr(std::remove_pointer_t<gainput::FilterFunc_T>);

#include "xkein/tool/tools.h"
UsingCppType(XkeinTools);
UsingCppType(QueryVolume);
UsingCppType(QuerySphere);

#include "yr/api/yr_entity.h"
UsingCppType(YrEntityAbstractComponent);

#include "yr/parse/ini_reader.h"
UsingCppType(IniReader);
UsingReferenceConverter(IniReader);
#include "yr/component/ini_component.h"
UsingCppType(IniComponentLoader);
#include "yr/tool/yr_helper.h"
UsingCppType(YrHelper);
#include "yr/serialization/serialization.h"
UsingCppType(Serialization);
#include "yr/network/net_pack.h"
UsingCppType(EventPack<unsigned char[99]>); // EventPack<byte[EventPackMaxDataSize]>
UsingCppType(VariantEventPack);
UsingCppType(NetPackDispatch);

#include "yr/event/input_event.h"
UsingCppType(YrInputBlocker);

#include "yr/yr_all_events.h"
UsingCppType(YrHookEventSystem);
UsingCppType(YrHookContext);

UsingCppType(YrHookOverrideReturn<void>);
UsingCppType(YrHookOverride);
UsingCppType(YrHookOverrideReturn<Action>);
UsingCppType(YrHookOverrideReturn<bool>);
UsingCppType(YrHookOverrideReturn<int>);
UsingCppType(YrHookOverrideReturn<DamageState>);
UsingCppType(YrHookOverrideReturn<Vector3D<int> *>);
UsingCppType(YrHookOverrideReturn<BulletClass *>);
UsingCppType(YrHookOverrideReturn<FireError>);
UsingCppType(YrHookOverrideReturn<long>);

UsingCppType(YrAircraftCtorEvent);
UsingCppType(YrAircraftDtorEvent);
UsingCppType(YrAircraftTypeCtorEvent);
UsingCppType(YrAircraftTypeDtorEvent);
UsingCppType(YrAnimCtorEvent);
UsingCppType(YrAnimDtorEvent);
UsingCppType(YrAnimSaveGameBeginEvent);
UsingCppType(YrAnimSaveGameEndEvent);
UsingCppType(YrAnimLoadGameBeginEvent);
UsingCppType(YrAnimLoadGameEndEvent);
UsingCppType(YrAnimTypeCtorEvent);
UsingCppType(YrAnimTypeDtorEvent);
UsingCppType(YrAnimTypeSaveGameBeginEvent);
UsingCppType(YrAnimTypeSaveGameEndEvent);
UsingCppType(YrAnimTypeLoadGameBeginEvent);
UsingCppType(YrAnimTypeLoadGameEndEvent);
UsingCppType(YrAnimTypeLoadIniEvent);
UsingCppType(YrBuildingCtorEvent);
UsingCppType(YrBuildingDtorEvent);
UsingCppType(YrBuildingTypeCtorEvent);
UsingCppType(YrBuildingTypeDtorEvent);
UsingCppType(YrBulletCtorEvent);
UsingCppType(YrBulletDtorEvent);
UsingCppType(YrBulletSaveGameBeginEvent);
UsingCppType(YrBulletSaveGameEndEvent);
UsingCppType(YrBulletLoadGameBeginEvent);
UsingCppType(YrBulletLoadGameEndEvent);
UsingCppType(YrBulletConstructEvent);
UsingCppType(YrBulletDetonateEvent);
UsingCppType(YrBulletSetTargetEvent);
UsingCppType(YrBulletTypeCtorEvent);
UsingCppType(YrBulletTypeDtorEvent);
UsingCppType(YrBulletTypeSaveGameBeginEvent);
UsingCppType(YrBulletTypeSaveGameEndEvent);
UsingCppType(YrBulletTypeLoadGameBeginEvent);
UsingCppType(YrBulletTypeLoadGameEndEvent);
UsingCppType(YrBulletTypeLoadIniEvent);
UsingCppType(YrLogicBeginUpdateEvent);
UsingCppType(YrLogicEndUpdateEvent);
UsingCppType(YrPointerExpireEvent);
UsingCppType(YrBeginRenderEvent);
UsingCppType(YrEndRenderEvent);
UsingCppType(YrSceneLoadEvent);
UsingCppType(YrSceneEnterEvent);
UsingCppType(YrSceneExitEvent);
UsingCppType(YrRulesLoadBeforeGeneralDataEvent);
UsingCppType(YrRulesLoadBeforeTypeDataEvent);
UsingCppType(YrRulesLoadAfterTypeDataEvent);
UsingCppType(YrSaveGameBeginEvent);
UsingCppType(YrSaveGameEndEvent);
UsingCppType(YrSaveGameBeginStreamEvent);
UsingCppType(YrSaveGameEndStreamEvent);
UsingCppType(YrLoadGameBeginEvent);
UsingCppType(YrLoadGameEndEvent);
UsingCppType(YrLoadGameBeginStreamEvent);
UsingCppType(YrLoadGameEndStreamEvent);
UsingCppType(YrHouseCtorEvent);
UsingCppType(YrHouseDtorEvent);
UsingCppType(YrHouseSaveGameBeginEvent);
UsingCppType(YrHouseSaveGameEndEvent);
UsingCppType(YrHouseLoadGameBeginEvent);
UsingCppType(YrHouseLoadGameEndEvent);
UsingCppType(YrHouseTypeCtorEvent);
UsingCppType(YrHouseTypeDtorEvent);
UsingCppType(YrHouseTypeSaveGameBeginEvent);
UsingCppType(YrHouseTypeSaveGameEndEvent);
UsingCppType(YrHouseTypeLoadGameBeginEvent);
UsingCppType(YrHouseTypeLoadGameEndEvent);
UsingCppType(YrHouseTypeLoadIniEvent);
UsingCppType(YrInfantryCtorEvent);
UsingCppType(YrInfantryDtorEvent);
UsingCppType(YrInfantryTypeCtorEvent);
UsingCppType(YrInfantryTypeDtorEvent);
UsingCppType(YrGadgetInputEvent);
UsingCppType(YrUserInterfaceInputEvent);
UsingCppType(YrKeyboardInputEvent);
UsingCppType(YrDecideActionEvent);
UsingCppType(YrConvertActionEvent);
UsingCppType(YrLeftMouseButtonDownEvent);
UsingCppType(YrLeftMouseButtonUpEvent);
UsingCppType(YrRightMouseButtonUpEvent);
UsingCppType(YrMissionExecuteEvent);
UsingCppType(YrObjectReceiveDamageEvent);
UsingCppType(YrObjectLimboCheckedEvent);
UsingCppType(YrObjectUnlimboCheckedEvent);
UsingCppType(YrObjectMouseOverCellEvent);
UsingCppType(YrObjectMouseOverObjectEvent);
UsingCppType(YrObjectCellClickedActionEvent);
UsingCppType(YrObjectObjectClickedActionEvent);
UsingCppType(YrObjectGetFLHEvent);
UsingCppType(YrSuperCtorEvent);
UsingCppType(YrSuperDtorEvent);
UsingCppType(YrSuperSaveGameBeginEvent);
UsingCppType(YrSuperSaveGameEndEvent);
UsingCppType(YrSuperLoadGameBeginEvent);
UsingCppType(YrSuperLoadGameEndEvent);
UsingCppType(YrSuperLaunchEvent);
UsingCppType(YrSuperWeaponTypeCtorEvent);
UsingCppType(YrSuperWeaponTypeDtorEvent);
UsingCppType(YrSuperWeaponTypeSaveGameBeginEvent);
UsingCppType(YrSuperWeaponTypeSaveGameEndEvent);
UsingCppType(YrSuperWeaponTypeLoadGameBeginEvent);
UsingCppType(YrSuperWeaponTypeLoadGameEndEvent);
UsingCppType(YrSuperWeaponTypeLoadIniEvent);
UsingCppType(YrSuperWeaponTypeMouseOverObjectEvent);
UsingCppType(YrTechnoCtorEvent);
UsingCppType(YrTechnoDtorEvent);
UsingCppType(YrTechnoSaveGameBeginEvent);
UsingCppType(YrTechnoSaveGameEndEvent);
UsingCppType(YrTechnoLoadGameBeginEvent);
UsingCppType(YrTechnoLoadGameEndEvent);
UsingCppType(YrTechnoFireEvent);
UsingCppType(YrTechnoSelectWeaponEvent);
UsingCppType(YrTechnoGetFireErrorEvent);
UsingCppType(YrTechnoSetTargetEvent);
UsingCppType(YrTechnoDestroyedEvent);
UsingCppType(YrTechnoAddPassengerEvent);
UsingCppType(YrTechnoRemovePassengerEvent);
UsingCppType(YrTechnoTypeCtorEvent);
UsingCppType(YrTechnoTypeDtorEvent);
UsingCppType(YrTechnoTypeLoadIniEvent);
UsingCppType(YrTechnoTypeSaveGameBeginEvent);
UsingCppType(YrTechnoTypeSaveGameEndEvent);
UsingCppType(YrTechnoTypeLoadGameBeginEvent);
UsingCppType(YrTechnoTypeLoadGameEndEvent);
UsingCppType(YrTerrainCtorEvent);
UsingCppType(YrTerrainDtorEvent);
UsingCppType(YrTerrainSaveGameBeginEvent);
UsingCppType(YrTerrainSaveGameEndEvent);
UsingCppType(YrTerrainLoadGameBeginEvent);
UsingCppType(YrTerrainLoadGameEndEvent);
UsingCppType(YrTerrainTypeCtorEvent);
UsingCppType(YrTerrainTypeDtorEvent);
UsingCppType(YrTerrainTypeSaveGameBeginEvent);
UsingCppType(YrTerrainTypeSaveGameEndEvent);
UsingCppType(YrTerrainTypeLoadGameBeginEvent);
UsingCppType(YrTerrainTypeLoadGameEndEvent);
UsingCppType(YrTerrainTypeLoadIniEvent);
UsingCppType(YrThemePlayEvent);
UsingCppType(YrThemeStopEvent);
UsingCppType(YrThemeSuspendEvent);
UsingCppType(YrThemeClearEvent);
UsingCppType(YrThemeLoadIniEvent);
UsingCppType(YrTActionExecuteEvent);
UsingCppType(YrUIUpdateEvent);
UsingCppType(YrUnitCtorEvent);
UsingCppType(YrUnitDtorEvent);
UsingCppType(YrUnitTypeCtorEvent);
UsingCppType(YrUnitTypeDtorEvent);
UsingCppType(YrWeaponTypeCtorEvent);
UsingCppType(YrWeaponTypeDtorEvent);
UsingCppType(YrWeaponTypeSaveGameBeginEvent);
UsingCppType(YrWeaponTypeSaveGameEndEvent);
UsingCppType(YrWeaponTypeLoadGameBeginEvent);
UsingCppType(YrWeaponTypeLoadGameEndEvent);
UsingCppType(YrWeaponTypeLoadIniEvent);
UsingCppType(YrWarheadTypeCtorEvent);
UsingCppType(YrWarheadTypeDtorEvent);
UsingCppType(YrWarheadTypeSaveGameBeginEvent);
UsingCppType(YrWarheadTypeSaveGameEndEvent);
UsingCppType(YrWarheadTypeLoadGameBeginEvent);
UsingCppType(YrWarheadTypeLoadGameEndEvent);
UsingCppType(YrWarheadTypeLoadIniEvent);
UsingCppType(YrWndProcEvent);
UsingCppType(YrMainWndProcEvent);
UsingCppType(YrBootEvent);
UsingCppType(YrTerminateEvent);
UsingCppType(YrAfterCreateWindoweEvent);
UsingCppType(YrAfterSetCooperativeLevelEvent);

// ── Delegate bindings ──────────────────────────────────
UsingCppType(FDelegateHandle);

UsingTDelegate(void(GameplayAbilitySpec*));
UsingTDelegate(void());

UsingTDelegateRegistration(void(GameplayAbilitySpec*));
UsingTDelegateRegistration(void());

UsingTMulticastDelegate(void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle));
UsingTMulticastDelegate(void(const GameplayAbility*, const GameplayTagContainer&));
UsingTMulticastDelegate(void(GameplayAbility*));
UsingTMulticastDelegate(void(const GameplayAbilitySpecHandle, GameplayAbility*));
UsingTMulticastDelegate(void(const GameplayAbilitySpec&));
UsingTMulticastDelegate(void(const GameplayEffectSpec&, const ActiveGameplayEffect*));
UsingTMulticastDelegate(void(const GameplayTag&, int32));
UsingTMulticastDelegate(void(ActiveGameplayEffectHandle, int32, int32));
UsingTMulticastDelegate(void(ActiveGameplayEffectHandle, float, float));
UsingTMulticastDelegate(void(ActiveGameplayEffectHandle, bool));
UsingTMulticastDelegate(void(const FGameplayEffectRemovalInfo&));
UsingTMulticastDelegate(void(const FOnAttributeChangeData&));
UsingTMulticastDelegate(void(FAggregator*));

UsingTMulticastDelegateRegistration(void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle));
UsingTMulticastDelegateRegistration(void(const GameplayAbility*, const GameplayTagContainer&));

#endif
