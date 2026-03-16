#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "scripting/javascript/js_events.h"
UsingCppTypeWithRefCache(JsGameEvents);
UsingCppTypeWithRefCache(JsPhysicsEvents);
UsingCppTypeWithRefCache(JsEventOnCtor);
UsingCppTypeWithRefCache(JsEventOnDtor);
UsingCppTypeWithRefCache(JsEvents);
#include "scripting/javascript/js_cpp_helper.h"
UsingCppTypeWithRefCache(JsCppHelper);

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

#include "yr/parse/ini_reader.h"
UsingCppType(IniReader);
UsingReferenceConverter(IniReader);
#include "yr/component/ini_component.h"
UsingCppType(IniComponentLoader);
#include "yr/tool/yr_helper.h"
UsingCppType(YrHelper);
#include "yr/serialization/serialization.h"
UsingCppType(Serialization);

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

#endif