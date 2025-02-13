/// <reference path = "../index.d.ts"/>
declare module "YRpp" {
class TintStruct
{
    m_Red : number;
    m_Green : number;
    m_Blue : number;
}
class RandomStruct
{
    m_Min : number;
    m_Max : number;
}
class LTRBStruct
{
    m_Left : number;
    m_Top : number;
    m_Right : number;
    m_Bottom : number;
}
class RateTimer
{
    Start(rate_0 : number) : void;
    m_Rate : number;
}
class FacingClass
{
    SetDesired(facing_0 : any) : boolean;
    SetCurrent(facing_0 : any) : boolean;
    Desired() : any;
    Current() : any;
    IsRotating() : boolean;
    IsRotatingCCW() : boolean;
    IsRotatingCW() : boolean;
    Difference() : any;
    SetROT(rate_0 : number) : void;
    m_DesiredFacing : any;
    m_StartFacing : any;
    m_RotationTimer : CDTimerClass;
    m_ROT : any;
}
class TechnoClass
    extends RadioClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    Limbo() : boolean;
    IsUnitFactory() : boolean;
    IsCloakable() : boolean;
    CanScatter() : boolean;
    BelongsToATeam() : boolean;
    ShouldSelfHealOneStep() : boolean;
    IsVoxel() : boolean;
    vt_entry_29C() : boolean;
    IsReadyToCloak() : boolean;
    ShouldNotBeCloaked() : boolean;
    TurretFacing(pBuffer_0 : any) : any;
    IsArmed() : boolean;
    vt_entry_2B0() : boolean;
    GetStoragePercentage() : number;
    GetPipFillLevel() : number;
    GetRefund() : number;
    GetThreatValue() : number;
    IsInSameZoneAs(pTarget_0 : AbstractClass) : boolean;
    vt_entry_2C8(dwUnk_0 : number, dwUnk2_1 : number) : number;
    IsInSameZoneAsCoords(coord_0 : any) : boolean;
    GetCrewCount() : number;
    GetAntiAirValue() : number;
    GetAntiArmorValue() : number;
    GetAntiInfantryValue() : number;
    GotHijacked() : void;
    SelectWeapon(pTarget_0 : AbstractClass) : number;
    SelectNavalTargeting(pTarget_0 : AbstractClass) : number;
    GetZAdjustment() : number;
    GetZGradient() : any;
    GetLastFlightMapCoords() : any;
    SetLastFlightMapCoords(coord_0 : any) : void;
    vt_entry_2FC(Buffer_0 : any, dwUnk2_1 : number, dwUnk3_2 : number) : any;
    vt_entry_300(Buffer_0 : any, dwUnk2_1 : number) : any;
    vt_entry_304(dwUnk_0 : number, dwUnk2_1 : number) : number;
    GetRealFacing(pBuffer_0 : any) : any;
    GetCrew() : InfantryTypeClass;
    vt_entry_310() : boolean;
    CanDeploySlashUnload() : boolean;
    GetROF(nWeapon_0 : number) : number;
    GetGuardRange(dwUnk_0 : number) : number;
    vt_entry_320() : boolean;
    IsRadarVisible(pOutDetection_0 : number) : boolean;
    IsSensorVisibleToPlayer() : boolean;
    IsSensorVisibleToHouse(House_0 : HouseClass) : boolean;
    IsEngineer() : boolean;
    ProceedToNextPlanningWaypoint() : void;
    ScanForTiberium(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : number;
    EnterGrinder() : boolean;
    EnterBioReactor() : boolean;
    EnterTankBunker() : boolean;
    EnterBattleBunker() : boolean;
    GarrisonStructure() : boolean;
    IsPowerOnline() : boolean;
    QueueVoice(idxVoc_0 : number) : void;
    VoiceEnter() : number;
    VoiceHarvest() : number;
    VoiceSelect() : number;
    VoiceCapture() : number;
    VoiceMove() : number;
    VoiceDeploy() : number;
    VoiceAttack(pTarget_0 : ObjectClass) : number;
    ClickedEvent(event_0 : any) : boolean;
    ClickedMission(Mission_0 : any, pTarget_1 : ObjectClass, TargetCell_2 : CellClass, NearestTargetCellICanEnter_3 : CellClass) : boolean;
    IsUnderEMP() : boolean;
    IsParalyzed() : boolean;
    CanCheer() : boolean;
    Cheer(Force_0 : boolean) : void;
    GetDefaultSpeed() : number;
    DecreaseAmmo() : void;
    AddPassenger(pPassenger_0 : FootClass) : void;
    CanDisguiseAs(pTarget_0 : AbstractClass) : boolean;
    TargetAndEstimateDamage(dwUnk_0 : number, dwUnk2_1 : number) : boolean;
    Stun() : void;
    TriggersCellInset(pTarget_0 : AbstractClass) : boolean;
    IsCloseEnough(pTarget_0 : AbstractClass, idxWeapon_1 : number) : boolean;
    IsCloseEnoughToAttack(pTarget_0 : AbstractClass) : boolean;
    IsCloseEnoughToAttackCoords(Coords_0 : any) : boolean;
    vt_entry_3B4(dwUnk_0 : number) : number;
    Destroyed(Killer_0 : ObjectClass) : void;
    GetFireErrorWithoutRange(pTarget_0 : AbstractClass, nWeaponIndex_1 : number) : any;
    GetFireError(pTarget_0 : AbstractClass, nWeaponIndex_1 : number, ignoreRange_2 : boolean) : any;
    SelectAutoTarget(TargetFlags_0 : any, CurrentThreat_1 : number, OnlyTargetHouseEnemy_2 : boolean) : CellClass;
    SetTarget(pTarget_0 : AbstractClass) : void;
    Fire(pTarget_0 : AbstractClass, nWeaponIndex_1 : number) : BulletClass;
    Guard() : void;
    SetOwningHouse(pHouse_0 : HouseClass, announce_1 : boolean) : boolean;
    vt_entry_3D8(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : void;
    Crash(Killer_0 : ObjectClass) : boolean;
    IsAreaFire() : boolean;
    IsNotSprayAttack() : number;
    vt_entry_3E8() : number;
    IsNotSprayAttack2() : number;
    GetDeployWeapon() : WeaponStruct;
    GetTurretWeapon() : WeaponStruct;
    GetWeapon(nWeaponIndex_0 : number) : WeaponStruct;
    HasTurret() : boolean;
    CanOccupyFire() : boolean;
    GetOccupyRangeBonus() : number;
    GetOccupantCount() : number;
    OnFinishRepair() : void;
    UpdateCloak(bUnk_0 : boolean) : void;
    CreateGap() : void;
    DestroyGap() : void;
    vt_entry_41C() : void;
    Sensed() : void;
    Reload() : void;
    vt_entry_428() : void;
    GetAttackCoordinates(pCrd_0 : any) : any;
    IsNotWarpingIn() : boolean;
    vt_entry_434(dwUnk_0 : number) : boolean;
    DrawActionLines(Force_0 : boolean, dwUnk2_1 : number) : void;
    GetDisguiseFlags(existingFlags_0 : number) : number;
    IsClearlyVisibleTo(House_0 : HouseClass) : boolean;
    DrawVoxel(Voxel_0 : any, dwUnk2_1 : number, Facing_2 : number, VoxelIndex_3 : any, Rect_4 : any, Location_5 : any, Matrix_6 : any, Intensity_7 : number, dwUnk9_8 : number, dwUnk10_9 : number) : void;
    vt_entry_448(dwUnk_0 : number, dwUnk2_1 : number) : void;
    DrawHealthBar(pLocation_0 : any, pBounds_1 : any, bUnk3_2 : boolean) : void;
    DrawPipScalePips(pLocation_0 : any, pOriginalLocation_1 : any, pBounds_2 : any) : void;
    DrawVeterancyPips(pLocation_0 : any, pBounds_1 : any) : void;
    DrawExtraInfo(location_0 : any, originalLocation_1 : any, bounds_2 : any) : void;
    Uncloak(bPlaySound_0 : boolean) : void;
    Cloak(bPlaySound_0 : boolean) : void;
    vt_entry_464(dwUnk_0 : number) : number;
    UpdateRefinerySmokeSystems() : void;
    DisguiseAs(pTarget_0 : AbstractClass) : number;
    ClearDisguise() : void;
    IsItTimeForIdleActionYet() : boolean;
    UpdateIdleAction() : boolean;
    vt_entry_47C(dwUnk_0 : number) : void;
    SetDestination(pDest_0 : AbstractClass, bUnk_1 : boolean) : void;
    EnterIdleMode(initial_0 : boolean, unused_1 : boolean) : boolean;
    UpdateSight(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number, dwUnk5_4 : number) : void;
    vt_entry_48C(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number) : void;
    ForceCreate(coord_0 : any, dwUnk_1 : number) : boolean;
    RadarTrackingStart() : void;
    RadarTrackingStop() : void;
    RadarTrackingFlash() : void;
    RadarTrackingUpdate(bUnk_0 : boolean) : void;
    vt_entry_4A4(dwUnk_0 : number) : void;
    vt_entry_4A8() : void;
    vt_entry_4AC() : boolean;
    vt_entry_4B0() : boolean;
    vt_entry_4B4() : number;
    vt_entry_4B8(pCrd_0 : any) : any;
    CanUseWaypoint() : boolean;
    CanAttackOnTheMove() : boolean;
    vt_entry_4C4() : boolean;
    vt_entry_4C8() : boolean;
    vt_entry_4CC() : void;
    vt_entry_4D0() : boolean;
    StartReloading() : void;
    ShouldSuppress(coords_0 : any) : boolean;
    get_ID() : string;
    TimeToBuild() : number;
    IsMindControlled() : boolean;
    CanBePermaMindControlled() : boolean;
    CreateLaser(pTarget_0 : ObjectClass, idxWeapon_1 : number, pWeapon_2 : WeaponTypeClass, Coords_3 : any) : LaserDrawClass;
    UpdateThreatInCell(Cell_0 : CellClass) : void;
    CanAutoTargetObject(targetFlags_0 : any, canTargetWhatAmI_1 : number, wantedDistance_2 : number, pTarget_3 : TechnoClass, pThreatPosed_4 : number, dwUnk_5 : number, pSourceCoords_6 : any) : boolean;
    TryAutoTargetObject(targetFlags_0 : any, canTargetWhatAmI_1 : number, pCoords_2 : any, dwUnk1_3 : number, dwUnk2_4 : number, pThreatPosed_5 : number, dwUnk3_6 : number) : boolean;
    Reactivate() : void;
    Deactivate() : void;
    EnteredOpenTopped(pWho_0 : TechnoClass) : void;
    ExitedOpenTopped(pWho_0 : TechnoClass) : void;
    MarkPassengersAsExited() : void;
    SetCurrentWeaponStage(idx_0 : number) : void;
    SetFocus(pFocus_0 : AbstractClass) : void;
    DrawVoxelShadow(vxl_0 : any, shadow_index_1 : number, vxl_index_key_2 : any, shadow_cache_3 : any, bound_4 : any, a3_5 : any, matrix_6 : any, again_7 : boolean, surface_8 : any, shadow_point_9 : any) : void;
    DrawObject(pSHP_0 : any, nFrame_1 : number, pLocation_2 : any, pBounds_3 : any, _4 : number, _5 : number, nZAdjust_6 : number, eZGradientDescIdx_7 : any, _8 : number, nBrightness_9 : number, TintColor_10 : number, pZShape_11 : any, nZFrame_12 : number, nZOffsetX_13 : number, nZOffsetY_14 : number, _15 : number) : void;
    sub_70DE00(State_0 : number) : number;
    ClearPlanningTokens(pEvent_0 : any) : number;
    SetTargetForPassengers(pTarget_0 : AbstractClass) : void;
    KillPassengers(pSource_0 : TechnoClass) : void;
    GetOriginalOwner() : HouseClass;
    FireDeathWeapon(additionalDamage_0 : number) : void;
    HasAbility(ability_0 : any) : boolean;
    ClearSidebarTabObject() : void;
    GetDrawer() : any;
    GetEffectTintIntensity(currentIntensity_0 : number) : number;
    GetInvulnerabilityTintIntensity(currentIntensity_0 : number) : number;
    GetAirstrikeTintIntensity(currentIntensity_0 : number) : number;
    CombatDamage(nWeaponIndex_0 : number) : number;
    GetPrimaryWeapon() : WeaponStruct;
    GetIonCannonValue(difficulty_0 : any) : number;
    GetIonCannonValue(difficulty_0 : any, maxHealth_1 : number) : number;
    TurretFacing() : any;
    GetRealFacing() : any;
    BaseIsAttacked(pEnemy_0 : TechnoClass) : void;
    s_AbsDerivateID : any;
    s_Array : any;
    m_Flashing : FlashData;
    m___Flashing : number;
    m_Animation : StageClass;
    m___Animation : number;
    m_Passengers : PassengersClass;
    m___Passengers : number;
    m_Transporter : TechnoClass;
    m_unknown_int_120 : number;
    m_CurrentTurretNumber : number;
    m_unknown_int_128 : number;
    m_BehindAnim : AnimClass;
    m_DeployAnim : AnimClass;
    m_InAir : boolean;
    m_CurrentWeaponNumber : number;
    m_CurrentRanking : any;
    m_CurrentGattlingStage : number;
    m_GattlingValue : number;
    m_TurretAnimFrame : number;
    m_InitialOwner : HouseClass;
    m_Veterancy : VeterancyStruct;
    m___Veterancy : number;
    m_ArmorMultiplier : number;
    m_FirepowerMultiplier : number;
    m_IdleActionTimer : CDTimerClass;
    m___IdleActionTimer : number;
    m_RadarFlashTimer : CDTimerClass;
    m___RadarFlashTimer : number;
    m_TargetingTimer : CDTimerClass;
    m___TargetingTimer : number;
    m_IronCurtainTimer : CDTimerClass;
    m___IronCurtainTimer : number;
    m_IronTintTimer : CDTimerClass;
    m___IronTintTimer : number;
    m_IronTintStage : number;
    m_AirstrikeTimer : CDTimerClass;
    m___AirstrikeTimer : number;
    m_AirstrikeTintTimer : CDTimerClass;
    m___AirstrikeTintTimer : number;
    m_AirstrikeTintStage : number;
    m_ForceShielded : number;
    m_Deactivated : boolean;
    m_DrainTarget : TechnoClass;
    m_DrainingMe : TechnoClass;
    m_DrainAnim : AnimClass;
    m_Disguised : boolean;
    m_DisguiseCreationFrame : number;
    m_InfantryBlinkTimer : CDTimerClass;
    m___InfantryBlinkTimer : number;
    m_DisguiseBlinkTimer : CDTimerClass;
    m___DisguiseBlinkTimer : number;
    m_UnlimboingInfantry : boolean;
    m_ReloadTimer : CDTimerClass;
    m___ReloadTimer : number;
    m_unknown_208 : number;
    m_unknown_20C : number;
    m_DisplayProductionTo : any;
    m___DisplayProductionTo : number;
    m_Group : number;
    m_Focus : AbstractClass;
    m_Owner : HouseClass;
    m_CloakState : any;
    m_CloakProgress : StageClass;
    m___CloakProgress : number;
    m_CloakDelayTimer : CDTimerClass;
    m___CloakDelayTimer : number;
    m_WarpFactor : number;
    m_unknown_bool_250 : boolean;
    m_LastSightCoords : any;
    m_LastSightRange : number;
    m_LastSightHeight : number;
    m_GapSuperCharged : boolean;
    m_GeneratingGap : boolean;
    m_GapRadius : number;
    m_BeingWarpedOut : boolean;
    m_WarpingOut : boolean;
    m_unknown_bool_272 : boolean;
    m_unused_273 : number;
    m_TemporalImUsing : TemporalClass;
    m_TemporalTargetingMe : TemporalClass;
    m_IsImmobilized : boolean;
    m_unknown_280 : number;
    m_ChronoLockRemaining : number;
    m_ChronoDestCoords : any;
    m_Airstrike : AirstrikeClass;
    m_Berzerk : boolean;
    m_BerzerkDurationLeft : number;
    m_SprayOffsetIndex : number;
    m_Uncrushable : boolean;
    m_DirectRockerLinkedUnit : FootClass;
    m_LocomotorTarget : FootClass;
    m_LocomotorSource : FootClass;
    m_Target : AbstractClass;
    m_LastTarget : AbstractClass;
    m_CaptureManager : CaptureManagerClass;
    m_MindControlledBy : TechnoClass;
    m_MindControlledByAUnit : boolean;
    m_MindControlRingAnim : AnimClass;
    m_MindControlledByHouse : HouseClass;
    m_SpawnManager : SpawnManagerClass;
    m_SpawnOwner : TechnoClass;
    m_SlaveManager : SlaveManagerClass;
    m_SlaveOwner : TechnoClass;
    m_OriginallyOwnedByHouse : HouseClass;
    m_BunkerLinkedItem : TechnoClass;
    m_PitchAngle : number;
    m_DiskLaserTimer : CDTimerClass;
    m___DiskLaserTimer : number;
    m_ROF : number;
    m_Ammo : number;
    m_Value : number;
    m_FireParticleSystem : ParticleSystemClass;
    m_SparkParticleSystem : ParticleSystemClass;
    m_NaturalParticleSystem : ParticleSystemClass;
    m_DamageParticleSystem : ParticleSystemClass;
    m_RailgunParticleSystem : ParticleSystemClass;
    m_unk1ParticleSystem : ParticleSystemClass;
    m_unk2ParticleSystem : ParticleSystemClass;
    m_FiringParticleSystem : ParticleSystemClass;
    m_Wave : WaveClass;
    m_AngleRotatedSideways : number;
    m_AngleRotatedForwards : number;
    m_RockingSidewaysPerFrame : number;
    m_RockingForwardsPerFrame : number;
    m_HijackerInfantryType : number;
    m_Tiberium : StorageClass;
    m___Tiberium : number;
    m_unknown_34C : number;
    m_UnloadTimer : TransitionTimer;
    m___UnloadTimer : number;
    m_BarrelFacing : FacingClass;
    m___BarrelFacing : number;
    m_PrimaryFacing : FacingClass;
    m___PrimaryFacing : number;
    m_SecondaryFacing : FacingClass;
    m___SecondaryFacing : number;
    m_CurrentBurstIndex : number;
    m_TargetLaserTimer : CDTimerClass;
    m___TargetLaserTimer : number;
    m_unknown_short_3C8 : number;
    m_unknown_3CA : number;
    m_CountedAsOwned : boolean;
    m_IsSinking : boolean;
    m_WasSinkingAlready : boolean;
    m_unknown_bool_3CF : boolean;
    m_unknown_bool_3D0 : boolean;
    m_HasBeenAttacked : boolean;
    m_Cloakable : boolean;
    m_IsPrimaryFactory : boolean;
    m_Spawned : boolean;
    m_IsInPlayfield : boolean;
    m_TurretRecoil : RecoilData;
    m___TurretRecoil : number;
    m_BarrelRecoil : RecoilData;
    m___BarrelRecoil : number;
    m_unknown_bool_418 : boolean;
    m_unknown_bool_419 : boolean;
    m_IsOwnedByCurrentPlayer : boolean;
    m_DiscoveredByCurrentPlayer : boolean;
    m_DiscoveredByComputer : boolean;
    m_unknown_bool_41D : boolean;
    m_unknown_bool_41E : boolean;
    m_unknown_bool_41F : boolean;
    m_SightIncrease : number;
    m_RecruitableA : boolean;
    m_RecruitableB : boolean;
    m_IsRadarTracked : boolean;
    m_IsOnCarryall : boolean;
    m_IsCrashing : boolean;
    m_WasCrashingAlready : boolean;
    m_IsBeingManipulated : boolean;
    m_BeingManipulatedBy : TechnoClass;
    m_ChronoWarpedByHouse : HouseClass;
    m_unknown_bool_430 : boolean;
    m_IsMouseHovering : boolean;
    m_unknown_bool_432 : boolean;
    m_OldTeam : TeamClass;
    m_CountedAsOwnedSpecial : boolean;
    m_Absorbed : boolean;
    m_unknown_bool_43A : boolean;
    m_unknown_43C : number;
    m_CurrentTargetThreatValues : any;
    m___CurrentTargetThreatValues : number;
    m_CurrentTargets : any;
    m___CurrentTargets : number;
    m_AttackedTargets : any;
    m___AttackedTargets : number;
    m_Audio3 : any;
    m___Audio3 : number;
    m_unknown_BOOL_49C : number;
    m_TurretIsRotating : number;
    m_Audio4 : any;
    m___Audio4 : number;
    m_unknown_bool_4B8 : boolean;
    m_unknown_4BC : number;
    m_Audio5 : any;
    m___Audio5 : number;
    m_unknown_bool_4D4 : boolean;
    m_unknown_4D8 : number;
    m_Audio6 : any;
    m___Audio6 : number;
    m_QueuedVoiceIndex : number;
    m_unknown_4F4 : number;
    m_unknown_bool_4F8 : boolean;
    m_unknown_4FC : number;
    m_unknown_500 : TechnoClass;
    m_EMPLockRemaining : number;
    m_ThreatPosed : number;
    m_ShouldLoseTargetNow : number;
    m_FiringRadBeam : RadBeam;
    m_PlanningToken : PlanningTokenClass;
    m_Disguise : ObjectTypeClass;
    m_DisguisedAsHouse : HouseClass;
}
class HouseClass
    extends AbstractClass
{
    EnumConnectionPoints(ppEnum_0 : any) : number;
    FindConnectionPoint(riid_0 : any, ppCP_1 : any) : number;
    Apparent_Category_Quantity(category_0 : any) : number;
    Apparent_Category_Power(category_0 : any) : number;
    Apparent_Base_Center() : any;
    Is_Powered() : boolean;
    ID_Number() : number;
    Name() : any;
    Get_Application() : any;
    Available_Money() : number;
    Available_Storage() : number;
    Power_Output() : number;
    Power_Drain() : number;
    Category_Quantity(category_0 : any) : number;
    Category_Power(category_0 : any) : number;
    Base_Center() : any;
    Fire_Sale() : number;
    All_To_Hunt() : number;
    QueryInterface(iid_0 : any, ppvObject_1 : void) : number;
    AddRef() : number;
    Release() : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    IsAlliedWith(idxHouse_0 : number) : boolean;
    IsAlliedWith(pHouse_0 : HouseClass) : boolean;
    IsAlliedWith(pObject_0 : ObjectClass) : boolean;
    IsAlliedWith(pAbstract_0 : AbstractClass) : boolean;
    MakeAlly(iHouse_0 : number, bAnnounce_1 : boolean) : void;
    MakeAlly(pWho_0 : HouseClass, bAnnounce_1 : boolean) : void;
    MakeEnemy(pWho_0 : HouseClass, bAnnounce_1 : boolean) : void;
    AdjustThreats() : void;
    UpdateAngerNodes(nScoreAdd_0 : number, pHouse_1 : HouseClass) : void;
    AllyAIHouses() : void;
    SDDTORAllAndTriggers() : void;
    AcceptDefeat() : void;
    DestroyAll() : void;
    DestroyAllBuildings() : void;
    DestroyAllNonBuildingsNonNaval() : void;
    DestroyAllNonBuildingsNaval() : void;
    RespawnStartingBuildings() : void;
    RespawnStartingForces() : void;
    Win(bSavourSomething_0 : boolean) : number;
    Lose(bSavourSomething_0 : boolean) : number;
    RegisterJustBuilt(pTechno_0 : TechnoClass) : void;
    CanAlly(pOther_0 : HouseClass) : boolean;
    CanOverpower(pTarget_0 : TechnoClass) : boolean;
    LostPoweredCenter(pTechnoType_0 : TechnoTypeClass) : void;
    GainedPoweredCenter(pTechnoType_0 : TechnoTypeClass) : void;
    DoInfantrySelfHeal() : boolean;
    GetInfSelfHealStep() : number;
    DoUnitsSelfHeal() : boolean;
    GetUnitSelfHealStep() : number;
    UpdatePower() : void;
    CreatePowerOutage(duration_0 : number) : void;
    GetPowerPercentage() : number;
    HasFullPower() : boolean;
    HasLowPower() : boolean;
    CreateRadarOutage(duration_0 : number) : void;
    ReshroudMap() : void;
    Cheer() : void;
    BuildingUnderAttack(pBld_0 : BuildingClass) : void;
    TakeMoney(amount_0 : number) : void;
    GiveMoney(amount_0 : number) : void;
    CanTransactMoney(amount_0 : number) : boolean;
    TransactMoney(amount_0 : number) : void;
    GiveTiberium(amount_0 : number, type_1 : number) : void;
    UpdateAllSilos(prevStorage_0 : number, prevTotalStorage_1 : number) : void;
    GetStoragePercentage() : number;
    AcquiredThreatNode() : void;
    static Index_IsMP(idx_0 : number) : boolean;
    static FindByCountryIndex(HouseType_0 : number) : HouseClass;
    static FindByIndex(idxHouse_0 : number) : HouseClass;
    static FindIndexByName(name_0 : string) : number;
    static GetPlayerAtFromString(name_0 : string) : number;
    static IsPlayerAtType(at_0 : number) : boolean;
    static FindByPlayerAt(at_0 : number) : HouseClass;
    static FindByCountryName(name_0 : string) : HouseClass;
    static FindNeutral() : HouseClass;
    static FindSpecial() : HouseClass;
    static FindBySideIndex(index_0 : number) : HouseClass;
    static FindBySideName(name_0 : string) : HouseClass;
    static FindCivilianSide() : HouseClass;
    static LoadFromINIList(pINI_0 : CCINIClass) : void;
    GetSpawnPosition() : number;
    GetPlanningWaypointAt(coords_0 : any) : WaypointClass;
    GetPlanningWaypointProperties(wpt_0 : WaypointClass, idxPath_1 : number, idxWP_2 : number) : boolean;
    EnsurePlanningPathExists(idx_0 : number) : void;
    Update_FactoriesQueues(factoryOf_0 : any, isNaval_1 : boolean, buildCat_2 : any) : void;
    GetFactoryProducing(pItem_0 : TechnoTypeClass) : FactoryClass;
    FirstBuildableFromArray(items_0 : any) : BuildingTypeClass;
    AllPrerequisitesAvailable(pItem_0 : TechnoTypeClass, vectorBuildings_1 : any, vectorLength_2 : number) : boolean;
    IsControlledByHuman() : boolean;
    IsControlledByCurrentPlayer() : boolean;
    SendSpyPlanes(AircraftTypeIdx_0 : number, AircraftAmount_1 : number, SetMission_2 : any, Target_3 : AbstractClass, Destination_4 : ObjectClass) : void;
    RegisterGain(pTechno_0 : TechnoClass, ownerChange_1 : boolean) : void;
    RegisterLoss(pTechno_0 : TechnoClass, keepTiberium_1 : boolean) : void;
    FindBuildingOfType(idx_0 : number, sector_1 : number) : BuildingClass;
    PsiWarn(pTarget_0 : CellClass, Bullet_1 : BulletClass, AnimName_2 : string) : AnimClass;
    Fire_LightningStorm(pSuper_0 : SuperClass) : boolean;
    Fire_ParaDrop(pSuper_0 : SuperClass) : boolean;
    Fire_PsyDom(pSuper_0 : SuperClass) : boolean;
    Fire_GenMutator(pSuper_0 : SuperClass) : boolean;
    IonSensitivesShouldBeOffline() : boolean;
    get_ID() : string;
    FindSuperWeaponIndex(type_0 : any) : number;
    FindSuperWeapon(type_0 : any) : SuperClass;
    CountOwnedNow(pItem_0 : TechnoTypeClass) : number;
    CountOwnedNow(pItem_0 : BuildingTypeClass) : number;
    CountOwnedNow(pItem_0 : AircraftTypeClass) : number;
    CountOwnedNow(pItem_0 : InfantryTypeClass) : number;
    CountOwnedNow(pItem_0 : UnitTypeClass) : number;
    CountOwnedAndPresent(pItem_0 : TechnoTypeClass) : number;
    CountOwnedAndPresent(pItem_0 : BuildingTypeClass) : number;
    CountOwnedAndPresent(pItem_0 : AircraftTypeClass) : number;
    CountOwnedAndPresent(pItem_0 : InfantryTypeClass) : number;
    CountOwnedAndPresent(pItem_0 : UnitTypeClass) : number;
    CountOwnedEver(pItem_0 : TechnoTypeClass) : number;
    CountOwnedEver(pItem_0 : BuildingTypeClass) : number;
    CountOwnedEver(pItem_0 : AircraftTypeClass) : number;
    CountOwnedEver(pItem_0 : InfantryTypeClass) : number;
    CountOwnedEver(pItem_0 : UnitTypeClass) : number;
    HasFromSecretLab(pItem_0 : TechnoTypeClass) : boolean;
    HasAllStolenTech(pItem_0 : TechnoTypeClass) : boolean;
    HasFactoryForObject(pItem_0 : TechnoTypeClass) : boolean;
    CanExpectToBuild(pItem_0 : TechnoTypeClass) : boolean;
    CanExpectToBuild(pItem_0 : TechnoTypeClass, idxParent_1 : number) : boolean;
    InOwners(pItem_0 : TechnoTypeClass) : boolean;
    InRequiredHouses(pItem_0 : TechnoTypeClass) : boolean;
    InForbiddenHouses(pItem_0 : TechnoTypeClass) : boolean;
    CanBuild(pItem_0 : TechnoTypeClass, buildLimitOnly_1 : boolean, allowIfInProduction_2 : boolean) : any;
    AI_BaseConstructionUpdate() : number;
    AI_VehicleConstructionUpdate() : number;
    AI_TryFireSW() : void;
    Fire_SW(idx_0 : number, coords_1 : any) : boolean;
    PickTargetByType(outBuffer_0 : any, targetType_1 : any) : any;
    PickTargetByType(targetType_0 : any) : any;
    PickIonCannonTarget(outBuffer_0 : any) : any;
    PickIonCannonTarget() : any;
    IsIonCannonEligibleTarget(pTechno_0 : TechnoClass) : boolean;
    UpdateFlagCoords(NewCarrier_0 : UnitClass, dwUnk_1 : number) : void;
    DroppedFlag(Where_0 : any, Who_1 : UnitClass) : void;
    PickedUpFlag(Who_0 : UnitClass, dwUnk_1 : number) : number;
    GetPrimaryFactory(absID_0 : any, naval_1 : boolean, buildCat_2 : any) : FactoryClass;
    SetPrimaryFactory(pFactory_0 : FactoryClass, absID_1 : any, naval_2 : boolean, buildCat_3 : any) : void;
    GetBaseCenter() : any;
    GetAIDifficultyIndex() : number;
    IsNeutral() : boolean;
    IsCurrentPlayer() : boolean;
    IsObserver() : boolean;
    static IsCurrentPlayerObserver() : boolean;
    CalculateCostMultipliers() : number;
    ForceEnd() : void;
    RemoveTracking(pTechno_0 : TechnoClass) : void;
    AddTracking(pTechno_0 : TechnoClass) : void;
    GetWeedStoragePercentage() : number;
    s_AbsID : any;
    s_Array : any;
    s_CurrentPlayer : any;
    s_Observer : any;
    m_ArrayIndex : number;
    m_Type : HouseTypeClass;
    m_RelatedTags : any;
    m___RelatedTags : number;
    m_ConYards : any;
    m___ConYards : number;
    m_Buildings : any;
    m___Buildings : number;
    m_UnitRepairStations : any;
    m___UnitRepairStations : number;
    m_Grinders : any;
    m___Grinders : number;
    m_Absorbers : any;
    m___Absorbers : number;
    m_Bunkers : any;
    m___Bunkers : number;
    m_Occupiables : any;
    m___Occupiables : number;
    m_CloningVats : any;
    m___CloningVats : number;
    m_SecretLabs : any;
    m___SecretLabs : number;
    m_PsychicDetectionBuildings : any;
    m___PsychicDetectionBuildings : number;
    m_FactoryPlants : any;
    m___FactoryPlants : number;
    m_CountResourceGatherers : number;
    m_CountResourceDestinations : number;
    m_CountWarfactories : number;
    m_InfantrySelfHeal : number;
    m_UnitsSelfHeal : number;
    m_StartingUnits : any;
    m___StartingUnits : number;
    m_AIDifficulty : any;
    m_FirepowerMultiplier : number;
    m_GroundspeedMultiplier : number;
    m_AirspeedMultiplier : number;
    m_ArmorMultiplier : number;
    m_ROFMultiplier : number;
    m_CostMultiplier : number;
    m_BuildTimeMultiplier : number;
    m_RepairDelay : number;
    m_BuildDelay : number;
    m_IQLevel : number;
    m_TechLevel : number;
    m_AltAllies : any;
    m_StartingCredits : number;
    m_StartingEdge : any;
    m_AIState_1E4 : number;
    m_SideIndex : number;
    m_IsHumanPlayer : boolean;
    m_IsInPlayerControl : boolean;
    m_Production : boolean;
    m_AutocreateAllowed : boolean;
    m_NodeLogic_1F0 : boolean;
    m_ShipYardConst_1F1 : boolean;
    m_AITriggersActive : boolean;
    m_AutoBaseBuilding : boolean;
    m_DiscoveredByPlayer : boolean;
    m_Defeated : boolean;
    m_IsGameOver : boolean;
    m_IsWinner : boolean;
    m_IsLoser : boolean;
    m_CiviliansEvacuated : boolean;
    m_FirestormActive : boolean;
    m_HasThreatNode : boolean;
    m_RecheckTechTree : boolean;
    m_IPAddress : number;
    m_TournamentTeamID : number;
    m_LostConnection : boolean;
    m_SelectedPathIndex : number;
    m_PlanningPaths : WaypointPathClass;
    m_Visionary : number;
    m_MapIsClear : boolean;
    m_IsTiberiumShort : boolean;
    m_HasBeenSpied : boolean;
    m_HasBeenThieved : boolean;
    m_Repairing : boolean;
    m_IsBuiltSomething : boolean;
    m_IsResigner : boolean;
    m_IsGiverUpper : boolean;
    m_AllToHunt : boolean;
    m_IsParanoid : boolean;
    m_IsToLook : boolean;
    m_IQLevel2 : number;
    m_AIMode : any;
    m_Supers : any;
    m___Supers : number;
    m_LastBuiltBuildingType : number;
    m_LastBuiltInfantryType : number;
    m_LastBuiltAircraftType : number;
    m_LastBuiltVehicleType : number;
    m_AllowWinBlocks : number;
    m_RepairTimer : CDTimerClass;
    m___RepairTimer : number;
    m_AlertTimer : CDTimerClass;
    m___AlertTimer : number;
    m_BorrowedTime : CDTimerClass;
    m___BorrowedTime : number;
    m_PowerBlackoutTimer : CDTimerClass;
    m___PowerBlackoutTimer : number;
    m_RadarBlackoutTimer : CDTimerClass;
    m___RadarBlackoutTimer : number;
    m_Side2TechInfiltrated : boolean;
    m_Side1TechInfiltrated : boolean;
    m_Side0TechInfiltrated : boolean;
    m_BarracksInfiltrated : boolean;
    m_WarFactoryInfiltrated : boolean;
    m_InfantryAltOwner : number;
    m_UnitAltOwner : number;
    m_AircraftAltOwner : number;
    m_BuildingAltOwner : number;
    m_AirportDocks : number;
    m_PoweredUnitCenters : number;
    m_CreditsSpent : number;
    m_HarvestedCredits : number;
    m_StolenBuildingsCredits : number;
    m_OwnedUnits : number;
    m_OwnedNavy : number;
    m_OwnedBuildings : number;
    m_OwnedInfantry : number;
    m_OwnedAircraft : number;
    m_OwnedTiberium : StorageClass;
    m___OwnedTiberium : number;
    m_Balance : number;
    m_TotalStorage : number;
    m_OwnedWeed : StorageClass;
    m___OwnedWeed : number;
    m_unknown_324 : number;
    m_BuiltAircraftTypes : UnitTrackerClass;
    m___BuiltAircraftTypes : number;
    m_BuiltInfantryTypes : UnitTrackerClass;
    m___BuiltInfantryTypes : number;
    m_BuiltUnitTypes : UnitTrackerClass;
    m___BuiltUnitTypes : number;
    m_BuiltBuildingTypes : UnitTrackerClass;
    m___BuiltBuildingTypes : number;
    m_KilledAircraftTypes : UnitTrackerClass;
    m___KilledAircraftTypes : number;
    m_KilledInfantryTypes : UnitTrackerClass;
    m___KilledInfantryTypes : number;
    m_KilledUnitTypes : UnitTrackerClass;
    m___KilledUnitTypes : number;
    m_KilledBuildingTypes : UnitTrackerClass;
    m___KilledBuildingTypes : number;
    m_CapturedBuildings : UnitTrackerClass;
    m___CapturedBuildings : number;
    m_CollectedCrates : UnitTrackerClass;
    m___CollectedCrates : number;
    m_NumAirpads : number;
    m_NumBarracks : number;
    m_NumWarFactories : number;
    m_NumConYards : number;
    m_NumShipyards : number;
    m_NumOrePurifiers : number;
    m_CostInfantryMult : number;
    m_CostUnitsMult : number;
    m_CostAircraftMult : number;
    m_CostBuildingsMult : number;
    m_CostDefensesMult : number;
    m_PowerOutput : number;
    m_PowerDrain : number;
    m_Primary_ForAircraft : FactoryClass;
    m_Primary_ForInfantry : FactoryClass;
    m_Primary_ForVehicles : FactoryClass;
    m_Primary_ForShips : FactoryClass;
    m_Primary_ForBuildings : FactoryClass;
    m_Primary_Unused1 : FactoryClass;
    m_Primary_Unused2 : FactoryClass;
    m_Primary_Unused3 : FactoryClass;
    m_Primary_ForDefenses : FactoryClass;
    m_AircraftType_53D0 : number;
    m_InfantryType_53D1 : number;
    m_VehicleType_53D2 : number;
    m_ShipType_53D3 : number;
    m_BuildingType_53D4 : number;
    m_unknown_53D5 : number;
    m_unknown_53D6 : number;
    m_unknown_53D7 : number;
    m_DefenseType_53D8 : number;
    m_unknown_53D9 : number;
    m_unknown_53DA : number;
    m_unknown_53DB : number;
    m_OurFlagCarrier : UnitClass;
    m_OurFlagCoords : any;
    m_KilledUnitsOfHouses : number;
    m_TotalKilledUnits : number;
    m_KilledBuildingsOfHouses : number;
    m_TotalKilledBuildings : number;
    m_WhoLastHurtMe : number;
    m_BaseSpawnCell : any;
    m_BaseCenter : any;
    m_Radius : number;
    m_ZoneInfos : ZoneInfoStruct;
    m___ZoneInfos : number;
    m_LATime : number;
    m_LAEnemy : number;
    m_ToCapture : number;
    m_RadarVisibleTo : any;
    m_SiloMoney : number;
    m_PreferredTargetType : any;
    m_PreferredTargetCell : any;
    m_PreferredDefensiveCell : any;
    m_PreferredDefensiveCell2 : any;
    m_PreferredDefensiveCellStartTime : number;
    m_OwnedBuildingTypes : any;
    m___OwnedBuildingTypes : number;
    m_OwnedUnitTypes : any;
    m___OwnedUnitTypes : number;
    m_OwnedInfantryTypes : any;
    m___OwnedInfantryTypes : number;
    m_OwnedAircraftTypes : any;
    m___OwnedAircraftTypes : number;
    m_ActiveBuildingTypes : any;
    m___ActiveBuildingTypes : number;
    m_ActiveUnitTypes : any;
    m___ActiveUnitTypes : number;
    m_ActiveInfantryTypes : any;
    m___ActiveInfantryTypes : number;
    m_ActiveAircraftTypes : any;
    m___ActiveAircraftTypes : number;
    m_FactoryProducedBuildingTypes : any;
    m___FactoryProducedBuildingTypes : number;
    m_FactoryProducedUnitTypes : any;
    m___FactoryProducedUnitTypes : number;
    m_FactoryProducedInfantryTypes : any;
    m___FactoryProducedInfantryTypes : number;
    m_FactoryProducedAircraftTypes : any;
    m___FactoryProducedAircraftTypes : number;
    m_AttackTimer : CDTimerClass;
    m___AttackTimer : number;
    m_InitialAttackDelay : number;
    m_EnemyHouseIndex : number;
    m_AngerNodes : any;
    m___AngerNodes : number;
    m_ScoutNodes : any;
    m___ScoutNodes : number;
    m_AITimer : CDTimerClass;
    m___AITimer : number;
    m_Unknown_Timer_5640 : CDTimerClass;
    m___Unknown_Timer_5640 : number;
    m_ProducingBuildingTypeIndex : number;
    m_ProducingUnitTypeIndex : number;
    m_ProducingInfantryTypeIndex : number;
    m_ProducingAircraftTypeIndex : number;
    m_RatioAITriggerTeam : number;
    m_RatioTeamAircraft : number;
    m_RatioTeamInfantry : number;
    m_RatioTeamBuildings : number;
    m_BaseDefenseTeamCount : number;
    m_DropshipData : DropshipStruct;
    m___DropshipData : number;
    m_CurrentDropshipIndex : number;
    m_HasCloakingRanges : number;
    m_Color : any;
    m_LaserColor : any;
    m_Base : BaseClass;
    m_RecheckPower : boolean;
    m_RecheckRadar : boolean;
    m_SpySatActive : boolean;
    m_IsBeingDrained : boolean;
    m_Edge : any;
    m_EMPTarget : any;
    m_NukeTarget : any;
    m_Allies : any;
    m_DamageDelayTimer : CDTimerClass;
    m___DamageDelayTimer : number;
    m_TeamDelayTimer : CDTimerClass;
    m___TeamDelayTimer : number;
    m_TriggerDelayTimer : CDTimerClass;
    m___TriggerDelayTimer : number;
    m_SpeakAttackDelayTimer : CDTimerClass;
    m___SpeakAttackDelayTimer : number;
    m_SpeakPowerDelayTimer : CDTimerClass;
    m___SpeakPowerDelayTimer : number;
    m_SpeakMoneyDelayTimer : CDTimerClass;
    m___SpeakMoneyDelayTimer : number;
    m_SpeakMaxedDelayTimer : CDTimerClass;
    m___SpeakMaxedDelayTimer : number;
    m_AIGeneral : any;
    m_ThreatPosedEstimates : number;
    m_PlainName : number;
    m_UINameString : number;
    m_UIName : any;
    m_ColorSchemeIndex : number;
    m_StartingPoint : number;
    m_StartingCell : any;
    m_StartingAllies : any;
    m_unknown_16060 : number;
    m_WaypointPath : any;
    m___WaypointPath : number;
    m_unknown_1607C : number;
    m_unknown_16080 : number;
    m_unknown_16084 : number;
    m_unused_16088 : number;
    m_unused_16090 : number;
    m_padding_16098 : number;
    m_PredictionEnemyArmor : number;
    m_PredictionEnemyAir : number;
    m_PredictionEnemyInfantry : number;
    m_TotalOwnedInfantryCost : number;
    m_TotalOwnedVehicleCost : number;
    m_TotalOwnedAircraftCost : number;
    m_unknown_power_160B4 : number;
}
class StorageClass
{
    GetAmount(index_0 : number) : number;
    GetTotalAmount() : number;
    AddAmount(amount_0 : number, index_1 : number) : number;
    RemoveAmount(amount_0 : number, index_1 : number) : number;
    GetTotalValue() : number;
    m_Tiberium1 : number;
    m_Tiberium2 : number;
    m_Tiberium3 : number;
    m_Tiberium4 : number;
}
class AbstractClass
{
    GetClassNameA() : string;
    static GetClassNameA(abs_0 : any) : string;
    QueryInterface(iid_0 : any, ppvObject_1 : void) : number;
    AddRef() : number;
    Release() : number;
    GetClassID(pClassID_0 : any) : number;
    IsDirty() : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetSizeMax(pcbSize_0 : any) : number;
    What_Am_I() : any;
    Fetch_ID() : number;
    Create_ID() : void;
    INoticeSink_Unknown(dwUnknown_0 : number) : boolean;
    INoticeSource_Unknown() : void;
    Init() : void;
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    ComputeCRC(crc_0 : any) : void;
    GetOwningHouseIndex() : number;
    GetOwningHouse() : HouseClass;
    GetArrayIndex() : number;
    IsDead() : boolean;
    GetCoords(pCrd_0 : any) : any;
    GetDestination(pCrd_0 : any, pDocker_1 : TechnoClass) : any;
    IsOnFloor() : boolean;
    IsInAir() : boolean;
    GetCenterCoords(pCrd_0 : any) : any;
    Update() : void;
    static AnnounceExpiredPointer(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    static RemoveAllInactive() : void;
    AnnounceExpiredPointer(removed_0 : boolean) : void;
    GetCoords() : any;
    GetDestination(pDocker_0 : TechnoClass) : any;
    GetCenterCoords() : any;
    GetTargetDirection(pDir_0 : any, pTarget_1 : AbstractClass) : any;
    GetTargetDirection(pTarget_0 : AbstractClass) : any;
    s_AbsID : any;
    s_Array : any;
    s_TargetIndex : any;
    m_UniqueID : number;
    m_AbstractFlags : any;
    m_unknown_18 : number;
    m_RefCount : number;
    m_Dirty : boolean;
}
class ObjectClass
    extends AbstractClass
{
    Load(pStm_0 : any) : number;
    IsOnFloor() : boolean;
    IsInAir() : boolean;
    AnimPointerExpired(pAnim_0 : AnimClass) : void;
    IsSelectable() : boolean;
    VisualCharacter(SpecificOwner_0 : number, WhoIsAsking_1 : HouseClass) : any;
    GetImage() : any;
    MouseOverCell(pCell_0 : any, checkFog_1 : boolean, ignoreForce_2 : boolean) : any;
    MouseOverObject(pObject_0 : ObjectClass, ignoreForce_1 : boolean) : any;
    InWhichLayer() : any;
    IsSurfaced() : boolean;
    IsStrange() : boolean;
    GetTechnoType() : TechnoTypeClass;
    GetType() : ObjectTypeClass;
    GetTypeOwners() : number;
    GetUIName() : any;
    CanBeRepaired() : boolean;
    CanBeSold() : boolean;
    IsActive() : boolean;
    IsControllable() : boolean;
    GetTargetCoords(pCrd_0 : any) : any;
    GetDockCoords(pCrd_0 : any, docker_1 : TechnoClass) : any;
    GetRenderCoords(pCrd_0 : any) : any;
    GetFLH(pDest_0 : any, idxWeapon_1 : number, BaseCoords_2 : any) : any;
    GetExitCoords(pCrd_0 : any, dwUnk_1 : number) : any;
    GetYSort() : number;
    IsOnBridge(pDocker_0 : TechnoClass) : boolean;
    IsStandingStill() : boolean;
    IsDisguised() : boolean;
    IsDisguisedAs(target_0 : HouseClass) : boolean;
    GetDisguise(DisguisedAgainstAllies_0 : boolean) : ObjectTypeClass;
    GetDisguiseHouse(DisguisedAgainstAllies_0 : boolean) : HouseClass;
    Limbo() : boolean;
    Unlimbo(Crd_0 : any, dFaceDir_1 : any) : boolean;
    Disappear(permanently_0 : boolean) : void;
    RegisterDestruction(Destroyer_0 : TechnoClass) : void;
    RegisterKill(Destroyer_0 : HouseClass) : void;
    SpawnParachuted(coords_0 : any) : boolean;
    DropAsBomb() : void;
    MarkAllOccupationBits(coords_0 : any) : void;
    UnmarkAllOccupationBits(coords_0 : any) : void;
    UnInit() : void;
    Reveal() : void;
    KickOutUnit(pTechno_0 : TechnoClass, Cell_1 : any) : any;
    DrawIfVisible(pBounds_0 : any, EvenIfCloaked_1 : boolean, dwUnk3_2 : number) : boolean;
    GetFoundationData(includeBib_0 : boolean) : any;
    DrawBehind(pLocation_0 : any, pBounds_1 : any) : void;
    DrawExtras(pLocation_0 : any, pBounds_1 : any) : void;
    DrawIt(pLocation_0 : any, pBounds_1 : any) : void;
    DrawAgain(location_0 : any, bounds_1 : any) : void;
    Undiscover() : void;
    See(dwUnk_0 : number, dwUnk2_1 : number) : void;
    Mark(value_0 : any) : boolean;
    GetDimensions(pRect_0 : any) : any;
    GetRenderDimensions(pRect_0 : any) : any;
    DrawRadialIndicator(dwUnk_0 : number) : void;
    MarkForRedraw() : void;
    CanBeSelected() : boolean;
    CanBeSelectedNow() : boolean;
    CellClickedAction(action_0 : any, pCell_1 : any, pCell1_2 : any, bUnk_3 : boolean) : boolean;
    ObjectClickedAction(action_0 : any, pTarget_1 : ObjectClass, bUnk_2 : boolean) : boolean;
    Flash(Duration_0 : number) : void;
    Select() : boolean;
    Deselect() : void;
    IronCurtain(nDuration_0 : number, pSource_1 : HouseClass, ForceShield_2 : boolean) : any;
    StopAirstrikeTimer() : void;
    StartAirstrikeTimer(Duration_0 : number) : void;
    IsIronCurtained() : boolean;
    IsCloseEnough3D(dwUnk_0 : number, dwUnk2_1 : number) : boolean;
    GetWeaponRange(idxWeapon_0 : number) : number;
    ReceiveDamage(pDamage_0 : number, DistanceFromEpicenter_1 : number, pWH_2 : WarheadTypeClass, Attacker_3 : ObjectClass, IgnoreDefenses_4 : boolean, PreventPassengerEscape_5 : boolean, pAttackingHouse_6 : HouseClass) : any;
    Destroy() : void;
    Scatter(crd_0 : any, ignoreMission_1 : boolean, ignoreDestination_2 : boolean) : void;
    Ignite() : boolean;
    Extinguish() : void;
    GetPointsValue() : number;
    GetCurrentMission() : any;
    RestoreMission(mission_0 : any) : void;
    UpdatePosition(dwUnk_0 : number) : void;
    FindFactory(allowOccupied_0 : boolean, requirePower_1 : boolean) : BuildingClass;
    ReceiveCommand(pSender_0 : TechnoClass, command_1 : any, pInOut_2 : AbstractClass) : any;
    DiscoveredBy(pHouse_0 : HouseClass) : boolean;
    SetRepairState(state_0 : number) : void;
    Sell(dwUnk_0 : number) : void;
    AssignPlanningPath(idxPath_0 : number, idxWP_1 : number) : void;
    MoveToDirection(facing_0 : any) : void;
    IsCellOccupied(pDestCell_0 : CellClass, facing_1 : any, level_2 : number, pSourceCell_3 : CellClass, alt_4 : boolean) : any;
    vt_entry_1B0(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number, dwUnk5_4 : number) : number;
    SetLocation(crd_0 : any) : void;
    GetMapCoords(pUCell_0 : any) : any;
    GetCell() : CellClass;
    GetMapCoordsAgain(pUCell_0 : any) : any;
    GetCellAgain() : CellClass;
    GetHeight() : number;
    SetHeight(dwUnk_0 : number) : void;
    GetZ() : number;
    IsBeingWarpedOut() : boolean;
    IsWarpingIn() : boolean;
    IsWarpingSomethingOut() : boolean;
    IsNotWarping() : boolean;
    GetRemapColour() : any;
    static DrawALinkTo(src_X_0 : number, src_Y_1 : number, src_Z_2 : number, dst_X_3 : number, dst_Y_4 : number, dst_Z_5 : number, color_6 : any) : void;
    DistanceFrom(that_0 : AbstractClass) : number;
    GetHealthPercentage() : number;
    SetHealthPercentage(percentage_0 : number) : void;
    IsRedHP() : boolean;
    IsYellowHP() : boolean;
    IsGreenHP() : boolean;
    GetHealthStatus() : any;
    AttachTrigger(pTag_0 : TagClass) : boolean;
    BecomeUntargetable() : void;
    ReplaceTag(pTag_0 : TagClass) : void;
    GetCellLevel() : number;
    GetMapCoords() : any;
    GetMapCoordsAgain() : any;
    GetTargetCoords() : any;
    GetRenderCoords() : any;
    GetFLH(idxWeapon_0 : number, base_1 : any) : any;
    s_AbsDerivateID : any;
    s_CurrentObjects : any;
    m_unknown_24 : number;
    m_unknown_28 : number;
    m_FallRate : number;
    m_NextObject : ObjectClass;
    m_AttachedTag : TagClass;
    m_AttachedBomb : BombClass;
    m_AmbientSoundController : any;
    m___AmbientSoundController : number;
    m_CustomSoundController : any;
    m___CustomSoundController : number;
    m_CustomSound : number;
    m_BombVisible : boolean;
    m_Health : number;
    m_EstimatedHealth : number;
    m_IsOnMap : boolean;
    m_unknown_78 : number;
    m_unknown_7C : number;
    m_NeedsRedraw : boolean;
    m_InLimbo : boolean;
    m_InOpenToppedTransport : boolean;
    m_IsSelected : boolean;
    m_HasParachute : boolean;
    m_Parachute : AnimClass;
    m_OnBridge : boolean;
    m_IsFallingDown : boolean;
    m_WasFallingDown : boolean;
    m_IsABomb : boolean;
    m_IsAlive : boolean;
    m_LastLayer : any;
    m_IsInLogic : boolean;
    m_IsVisible : boolean;
    m_Location : any;
    m_LineTrailer : LineTrail;
}
class AnimClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    PointerExpired(pAbstract_0 : AbstractClass, detachFromAll_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    AnimExtras() : number;
    GetEnd() : number;
    SetOwnerObject(pOwner_0 : ObjectClass) : void;
    Pause() : void;
    Unpause() : void;
    s_AbsID : any;
    s_Array : any;
    m_Animation : StageClass;
    m___Animation : number;
    m_Type : AnimTypeClass;
    m_OwnerObject : ObjectClass;
    m_unknown_D0 : number;
    m_LightConvert : any;
    m_LightConvertIndex : number;
    m_PaletteName : number;
    m_TintColor : number;
    m_ZAdjust : number;
    m_YSortAdjust : number;
    m_FlamingGuyCoords : any;
    m_FlamingGuyRetries : number;
    m_IsBuildingAnim : boolean;
    m_UnderTemporal : boolean;
    m_Paused : boolean;
    m_Unpaused : boolean;
    m_PausedAnimFrame : number;
    m_Reverse : boolean;
    m_unknown_124 : number;
    m_Bounce : BounceClass;
    m___Bounce : number;
    m_TranslucencyLevel : number;
    m_TimeToDie : boolean;
    m_AttachedBullet : BulletClass;
    m_Owner : HouseClass;
    m_LoopDelay : number;
    m_Accum : number;
    m_AnimFlags : any;
    m_HasExtras : boolean;
    m_RemainingIterations : number;
    m_unknown_196 : number;
    m_unknown_197 : number;
    m_IsPlaying : boolean;
    m_IsFogged : boolean;
    m_FlamingGuyExpire : boolean;
    m_UnableToContinue : boolean;
    m_SkipProcessOnce : boolean;
    m_Invisible : boolean;
    m_PowerOff : boolean;
    m_Audio3 : any;
    m___Audio3 : number;
    m_Audio4 : any;
    m___Audio4 : number;
}
class AnimTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : AnimTypeClass;
    static FindOrAllocate(pID_0 : string) : AnimTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    LoadImageA() : any;
    Load2DArt() : void;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_MiddleFrameIndex : number;
    m_MiddleFrameWidth : number;
    m_MiddleFrameHeight : number;
    m_unknown_2A4 : number;
    m_Damage : number;
    m_Rate : number;
    m_Start : number;
    m_LoopStart : number;
    m_LoopEnd : number;
    m_End : number;
    m_LoopCount : number;
    m_Next : AnimTypeClass;
    m_SpawnsParticle : number;
    m_NumParticles : number;
    m_DetailLevel : number;
    m_TranslucencyDetailLevel : number;
    m_RandomLoopDelay : RandomStruct;
    m_RandomRate : RandomStruct;
    m_Translucency : number;
    m_Spawns : AnimTypeClass;
    m_SpawnCount : number;
    m_Report : number;
    m_StopSound : number;
    m_BounceAnim : AnimTypeClass;
    m_ExpireAnim : AnimTypeClass;
    m_TrailerAnim : AnimTypeClass;
    m_TrailerSeperation : number;
    m_Elasticity : number;
    m_MinZVel : number;
    m_unknown_double_320 : number;
    m_MaxXYVel : number;
    m_Warhead : WarheadTypeClass;
    m_DamageRadius : number;
    m_TiberiumSpawnType : OverlayTypeClass;
    m_TiberiumSpreadRadius : number;
    m_YSortAdjust : number;
    m_YDrawOffset : number;
    m_ZAdjust : number;
    m_MakeInfantry : number;
    m_RunningFrames : number;
    m_IsFlamingGuy : boolean;
    m_IsVeins : boolean;
    m_IsMeteor : boolean;
    m_TiberiumChainReaction : boolean;
    m_IsTiberium : boolean;
    m_HideIfNoOre : boolean;
    m_Bouncer : boolean;
    m_Tiled : boolean;
    m_ShouldUseCellDrawer : boolean;
    m_UseNormalLight : boolean;
    m_DemandLoad : boolean;
    m_FreeLoad : boolean;
    m_IsAnimatedTiberium : boolean;
    m_AltPalette : boolean;
    m_Normalized : boolean;
    m_Layer : any;
    m_DoubleThick : boolean;
    m_Flat : boolean;
    m_Translucent : boolean;
    m_Scorch : boolean;
    m_Flamer : boolean;
    m_Crater : boolean;
    m_ForceBigCraters : boolean;
    m_Sticky : boolean;
    m_PingPong : boolean;
    m_Reverse : boolean;
    m_Shadow : boolean;
    m_PsiWarning : boolean;
    m_ShouldFogRemove : boolean;
}
class ObjectTypeClass
    extends AbstractTypeClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetSizeMax(pcbSize_0 : any) : number;
    vt_entry_6C(pDest_0 : any, pSrc_1 : any) : any;
    GetOwners() : number;
    GetPipMax() : number;
    vt_entry_78(dwUnk_0 : number) : void;
    Dimension2(pDest_0 : any) : void;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    GetActualCost(pHouse_0 : HouseClass) : number;
    GetBuildSpeed() : number;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    GetFoundationData(IncludeBib_0 : boolean) : any;
    FindFactory(allowOccupied_0 : boolean, requirePower_1 : boolean, requireCanBuild_2 : boolean, pHouse_3 : HouseClass) : BuildingClass;
    GetCameo() : any;
    GetImage() : any;
    static IsBuildCat5(abstractID_0 : any, idx_1 : number) : boolean;
    static GetTechnoType(abstractID_0 : any, idx_1 : number) : TechnoTypeClass;
    LoadVoxel() : void;
    m_RadialColor : any;
    m_unused_9B : number;
    m_Armor : any;
    m_Strength : number;
    m_Image : any;
    m_ImageAllocated : boolean;
    m_AlphaImage : any;
    m_MainVoxel : any;
    m_TurretVoxel : any;
    m_BarrelVoxel : any;
    m_ChargerTurrets : any;
    m_ChargerBarrels : any;
    m_NoSpawnAlt : boolean;
    m_MaxDimension : number;
    m_CrushSound : number;
    m_AmbientSound : number;
    m_ImageFile : number;
    m_AlternateArcticArt : boolean;
    m_ArcticArtInUse : boolean;
    m_AlphaImageFile : number;
    m_Theater : boolean;
    m_Crushable : boolean;
    m_Bombable : boolean;
    m_RadarInvisible : boolean;
    m_Selectable : boolean;
    m_LegalTarget : boolean;
    m_Insignificant : boolean;
    m_Immune : boolean;
    m_IsLogic : boolean;
    m_AllowCellContent : boolean;
    m_Voxel : boolean;
    m_NewTheater : boolean;
    m_HasRadialIndicator : boolean;
    m_IgnoresFirestorm : boolean;
    m_UseLineTrail : boolean;
    m_LineTrailColor : any;
    m_LineTrailColorDecrement : number;
    m_VoxelMainCache : any;
    m_VoxelTurretWeaponCache : any;
    m_VoxelShadowCache : any;
    m_VoxelTurretBarrelCache : any;
}
class AbstractTypeClass
    extends AbstractClass
{
    LoadTheaterSpecificArt(th_type_0 : any) : void;
    LoadFromINI(pINI_0 : CCINIClass) : boolean;
    SaveToINI(pINI_0 : CCINIClass) : boolean;
    get_ID() : string;
    s_AbsID : any;
    s_Array : any;
    m_ID : number;
    m_UINameLabel : number;
    m_UIName : any;
    m_Name : number;
}
class CCINIClass
    extends INIClass
{
    static LoadINIFile(pFileName_0 : string) : CCINIClass;
    static UnloadINIFile(pINI_0 : CCINIClass) : void;
    ReadCCFile(pCCFile_0 : any, bDigest_1 : boolean, bLoadComments_2 : boolean) : CCINIClass;
    WriteCCFile(pCCFile_0 : any, bDigest_1 : boolean) : void;
    ReadStringtableEntry(pSection_0 : string, pKey_1 : string, pBuffer_2 : any, szBufferSize_3 : any) : number;
    ReadStringtableEntry(pSection_0 : string, pKey_1 : string, pBuffer_2 : any) : number;
    GetCRC() : number;
    s_RulesHash : any;
    s_ArtHash : any;
    s_AIHash : any;
    s_INI_Rules : any;
    s_INI_AI : any;
    s_INI_Art : any;
    s_INI_UIMD : any;
    s_INI_RA2MD : any;
    m_Digested : boolean;
    m_Digest : number;
}
class INIClass
{
    Reset() : void;
    Clear(s1_0 : string, s2_1 : string) : void;
    GetSection(pSection_0 : string) : any;
    GetKeyCount(pSection_0 : string) : number;
    GetKeyName(pSection_0 : string, nKeyIndex_1 : number) : string;
    ReadString(pSection_0 : string, pKey_1 : string, pDefault_2 : string, pBuffer_3 : string, szBufferSize_4 : any) : number;
    GetString(pSection_0 : string, pKey_1 : string, pBuffer_2 : string, szBufferSize_3 : any) : number;
    WriteString(pSection_0 : string, pKey_1 : string, pString_2 : string) : boolean;
    ReadUnicodeString(pSection_0 : string, pKey_1 : string, pDefault_2 : any, pBuffer_3 : any, szBufferSize_4 : any) : number;
    WriteUnicodeString(pSection_0 : string, pKey_1 : string, pString_2 : any) : boolean;
    ReadBool(pSection_0 : string, pKey_1 : string, bDefault_2 : boolean) : boolean;
    GetBool(pSection_0 : string, pKey_1 : string, bValue_2 : boolean) : void;
    WriteBool(pSection_0 : string, pKey_1 : string, bValue_2 : boolean) : boolean;
    ReadInteger(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    GetInteger(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    WriteInteger(pSection_0 : string, pKey_1 : string, nValue_2 : number, bHex_3 : boolean) : boolean;
    ReadDouble(pSection_0 : string, pKey_1 : string, dDefault_2 : number) : number;
    GetDouble(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    WriteDouble(pSection_0 : string, pKey_1 : string, dValue_2 : number) : boolean;
    ReadRate(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    GetRate(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    WriteRate(pSection_0 : string, pKey_1 : string, nValue_2 : number) : boolean;
    Read2Integers(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    ReadPoint2D(ret_0 : any, pSection_1 : string, pKey_2 : string, defValue_3 : any) : any;
    GetPoint2D(pSection_0 : string, pKey_1 : string, value_2 : any) : void;
    Write2Integers(pSection_0 : string, pKey_1 : string, pValues_2 : number) : boolean;
    Read3Integers(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    ReadPoint3D(ret_0 : any, pSection_1 : string, pKey_2 : string, defValue_3 : any) : any;
    GetPoint3D(pSection_0 : string, pKey_1 : string, value_2 : any) : void;
    Read3Bytes(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    Write3Bytes(pSection_0 : string, pKey_1 : string, pValues_2 : number) : boolean;
    Exists(pSection_0 : string, pKey_1 : string) : boolean;
    ReadTime(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    WriteTime(pSection_0 : string, pKey_1 : string, nValue_2 : number) : boolean;
    ReadPip(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadPipScale(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadCategory(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadColorString(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadFoundation(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadMovementZone(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadSpeedType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadSWAction(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadSWType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadVoxName(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadFactory(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadBuildCat(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadHouseTypesList(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadHousesList(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadArmorType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadLandType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadHouseType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadSide(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadMovie(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadTheater(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadTheme(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadEdge(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadPowerup(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadLayer(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadVHPScan(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    ReadColor(pBuffer_0 : any, pSection_1 : string, pKey_2 : string, defValue_3 : any) : any;
    ReadColor(pSection_0 : number, pKey_1 : number, defValue_2 : any) : any;
    GetColor(pSection_0 : number, pKey_1 : number, value_2 : any) : void;
    WriteColor(pSection_0 : number, pKey_1 : number, color_2 : any) : boolean;
    ReadUUBlock(pSection_0 : number, pBuffer_1 : void, length_2 : any) : any;
    WriteUUBlock(pSection_0 : number, pBuffer_1 : void, length_2 : any) : boolean;
    ReadAbilities(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    GetTechnoType(pSection_0 : string, pKey_1 : string) : TechnoTypeClass;
    ReadString(pSection_0 : string, pKey_1 : string, pDefault_2 : string, pBuffer_3 : number) : number;
    GetString(pSection_0 : string, pKey_1 : string, pBuffer_2 : number) : number;
    ReadUnicodeString(pSection_0 : string, pKey_1 : string, pDefault_2 : any, pBuffer_3 : any) : number;
    static GetPrerequisites(pBuffer_0 : any, pINI_1 : INIClass, pSection_2 : string, pKey_3 : string, Defaults_4 : any) : any;
    static IsBlank(pValue_0 : string) : boolean;
    m_CurrentSectionName : string;
    m_CurrentSection : any;
    m_Sections : any;
    m___Sections : number;
    m_SectionIndex : any;
    m___SectionIndex : number;
    m_LineComments : any;
}
class TechnoTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : TechnoTypeClass;
    static FindIndex(pID_0 : string) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetSizeMax(pcbSize_0 : any) : number;
    CanUseWaypoint() : boolean;
    CanAttackMove() : boolean;
    CanCreateHere(mapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    GetCost() : number;
    GetRepairStepCost() : number;
    GetRepairStep() : number;
    GetRefund(pHouse_0 : HouseClass, bUnk_1 : boolean) : number;
    GetFlightLevel() : number;
    static GetByTypeAndIndex(abs_0 : any, index_1 : number) : TechnoTypeClass;
    HasMultipleTurrets() : boolean;
    GetParticleSysOffset(pBuffer_0 : any) : any;
    GetParticleSysOffset() : any;
    InOwners(bitHouseType_0 : number) : boolean;
    InRequiredHouses(bitHouseType_0 : number) : boolean;
    InForbiddenHouses(bitHouseType_0 : number) : boolean;
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    s_Array : any;
    s_MaxWeapons : any;
    m_WalkRate : number;
    m_IdleRate : number;
    m_VeteranAbilities : AbilitiesStruct;
    m_EliteAbilities : AbilitiesStruct;
    m_SpecialThreatValue : number;
    m_MyEffectivenessCoefficient : number;
    m_TargetEffectivenessCoefficient : number;
    m_TargetSpecialThreatCoefficient : number;
    m_TargetStrengthCoefficient : number;
    m_TargetDistanceCoefficient : number;
    m_ThreatAvoidanceCoefficient : number;
    m_SlowdownDistance : number;
    m_align_2FC : number;
    m_unknown_double_300 : number;
    m_AccelerationFactor : number;
    m_CloakingSpeed : number;
    m_DebrisTypes : any;
    m_DebrisMaximums : any;
    m_Locomotor : any;
    m_align_35C : number;
    m_VoxelScaleX : number;
    m_VoxelScaleY : number;
    m_Weight : number;
    m_PhysicalSize : number;
    m_Size : number;
    m_SizeLimit : number;
    m_HoverAttack : boolean;
    m_VHPScan : number;
    m_unknown_int_398 : number;
    m_align_39C : number;
    m_RollAngle : number;
    m_PitchSpeed : number;
    m_PitchAngle : number;
    m_BuildLimit : number;
    m_Category : any;
    m_unknown_3C0 : number;
    m_align_3C4 : number;
    m_DeployTime : number;
    m_FireAngle : number;
    m_PipScale : any;
    m_PipsDrawForAll : boolean;
    m_LeptonMindControlOffset : number;
    m_PixelSelectionBracketDelta : number;
    m_PipWrap : number;
    m_Dock : any;
    m_DeploysInto : BuildingTypeClass;
    m_UndeploysInto : UnitTypeClass;
    m_PowersUnit : UnitTypeClass;
    m_PoweredUnit : boolean;
    m_VoiceSelect : any;
    m_VoiceSelectEnslaved : any;
    m_VoiceSelectDeactivated : any;
    m_VoiceMove : any;
    m_VoiceAttack : any;
    m_VoiceSpecialAttack : any;
    m_VoiceDie : any;
    m_VoiceFeedback : any;
    m_MoveSound : any;
    m_DieSound : any;
    m_AuxSound1 : number;
    m_AuxSound2 : number;
    m_CreateSound : number;
    m_DamageSound : number;
    m_ImpactWaterSound : number;
    m_ImpactLandSound : number;
    m_CrashingSound : number;
    m_SinkingSound : number;
    m_VoiceFalling : number;
    m_VoiceCrashing : number;
    m_VoiceSinking : number;
    m_VoiceEnter : number;
    m_VoiceCapture : number;
    m_TurretRotateSound : number;
    m_EnterTransportSound : number;
    m_LeaveTransportSound : number;
    m_DeploySound : number;
    m_UndeploySound : number;
    m_ChronoInSound : number;
    m_ChronoOutSound : number;
    m_VoiceHarvest : number;
    m_VoicePrimaryWeaponAttack : number;
    m_VoicePrimaryEliteWeaponAttack : number;
    m_VoiceSecondaryWeaponAttack : number;
    m_VoiceSecondaryEliteWeaponAttack : number;
    m_VoiceDeploy : number;
    m_VoiceUndeploy : number;
    m_EnterGrinderSound : number;
    m_LeaveGrinderSound : number;
    m_EnterBioReactorSound : number;
    m_LeaveBioReactorSound : number;
    m_ActivateSound : number;
    m_DeactivateSound : number;
    m_MindClearedSound : number;
    m_MovementZone : any;
    m_GuardRange : number;
    m_MinDebris : number;
    m_MaxDebris : number;
    m_DebrisAnims : any;
    m_Passengers : number;
    m_OpenTopped : boolean;
    m_Sight : number;
    m_ResourceGatherer : boolean;
    m_ResourceDestination : boolean;
    m_RevealToAll : boolean;
    m_Drainable : boolean;
    m_SensorsSight : number;
    m_DetectDisguiseRange : number;
    m_BombSight : number;
    m_LeadershipRating : number;
    m_NavalTargeting : any;
    m_LandTargeting : any;
    m_BuildTimeMultiplier : number;
    m_MindControlRingOffset : number;
    m_Cost : number;
    m_Soylent : number;
    m_FlightLevel : number;
    m_AirstrikeTeam : number;
    m_EliteAirstrikeTeam : number;
    m_AirstrikeTeamType : AircraftTypeClass;
    m_EliteAirstrikeTeamType : AircraftTypeClass;
    m_AirstrikeRechargeTime : number;
    m_EliteAirstrikeRechargeTime : number;
    m_TechLevel : number;
    m_Prerequisite : any;
    m_PrerequisiteOverride : any;
    m_ThreatPosed : number;
    m_Points : number;
    m_Speed : number;
    m_SpeedType : any;
    m_InitialAmmo : number;
    m_Ammo : number;
    m_IFVMode : number;
    m_AirRangeBonus : number;
    m_BerserkFriendly : boolean;
    m_SprayAttack : boolean;
    m_Pushy : boolean;
    m_Natural : boolean;
    m_Unnatural : boolean;
    m_CloseRange : boolean;
    m_Reload : number;
    m_EmptyReload : number;
    m_ReloadIncrement : number;
    m_RadialFireSegments : number;
    m_DeployFireWeapon : number;
    m_DeployFire : boolean;
    m_DeployToLand : boolean;
    m_MobileFire : boolean;
    m_OpportunityFire : boolean;
    m_DistributedFire : boolean;
    m_DamageReducesReadiness : boolean;
    m_ReadinessReductionMultiplier : number;
    m_UnloadingClass : UnitTypeClass;
    m_DeployingAnim : AnimTypeClass;
    m_AttackFriendlies : boolean;
    m_AttackCursorOnFriendlies : boolean;
    m_UndeployDelay : number;
    m_PreventAttackMove : boolean;
    m_OwnerFlags : number;
    m_AIBasePlanningSide : number;
    m_StupidHunt : boolean;
    m_AllowedToStartInMultiplayer : boolean;
    m_CameoFile : number;
    m_Cameo : any;
    m_CameoAllocated : boolean;
    m_AltCameoFile : number;
    m_AltCameo : any;
    m_AltCameoAllocated : boolean;
    m_RotCount : number;
    m_ROT : number;
    m_TurretOffset : number;
    m_CanBeHidden : boolean;
    m_Points2 : number;
    m_Explosion : any;
    m_DestroyAnim : any;
    m_NaturalParticleSystem : ParticleSystemTypeClass;
    m_NaturalParticleSystemLocation : any;
    m_RefinerySmokeParticleSystem : ParticleSystemTypeClass;
    m_DamageParticleSystems : any;
    m_DestroyParticleSystems : any;
    m_DamageSmokeOffset : any;
    m_DamSmkOffScrnRel : boolean;
    m_DestroySmokeOffset : any;
    m_RefinerySmokeOffsetOne : any;
    m_RefinerySmokeOffsetTwo : any;
    m_RefinerySmokeOffsetThree : any;
    m_RefinerySmokeOffsetFour : any;
    m_ShadowIndex : number;
    m_Storage : number;
    m_TurretNotExportedOnGround : boolean;
    m_Gunner : boolean;
    m_HasTurretTooltips : boolean;
    m_TurretCount : number;
    m_WeaponCount : number;
    m_IsChargeTurret : boolean;
    m_TurretWeapon : number;
    m_AlternativeFLH : any;
    m_Weapon : WeaponStruct;
    m_ClearAllWeapons : boolean;
    m_EliteWeapon : WeaponStruct;
    m_TypeImmune : boolean;
    m_MoveToShroud : boolean;
    m_Trainable : boolean;
    m_DamageSparks : boolean;
    m_TargetLaser : boolean;
    m_ImmuneToVeins : boolean;
    m_TiberiumHeal : boolean;
    m_CloakStop : boolean;
    m_IsTrain : boolean;
    m_IsDropship : boolean;
    m_ToProtect : boolean;
    m_Disableable : boolean;
    m_Unbuildable : boolean;
    m_DoubleOwned : boolean;
    m_Invisible : boolean;
    m_RadarVisible : boolean;
    m_HasPrimary : boolean;
    m_Sensors : boolean;
    m_Nominal : boolean;
    m_DontScore : boolean;
    m_DamageSelf : boolean;
    m_Turret : boolean;
    m_TurretRecoil : boolean;
    m_TurretAnimData : TurretControl;
    m_unknown_bool_CB4 : boolean;
    m_BarrelAnimData : TurretControl;
    m_unknown_bool_CC8 : boolean;
    m_Repairable : boolean;
    m_Crewed : boolean;
    m_Naval : boolean;
    m_Remapable : boolean;
    m_Cloakable : boolean;
    m_GapGenerator : boolean;
    m_GapRadiusInCells : number;
    m_SuperGapRadiusInCells : number;
    m_Teleporter : boolean;
    m_IsGattling : boolean;
    m_WeaponStages : number;
    m_WeaponStage : number;
    m_EliteStage : number;
    m_RateUp : number;
    m_RateDown : number;
    m_SelfHealing : boolean;
    m_Explodes : boolean;
    m_DeathWeapon : WeaponTypeClass;
    m_DeathWeaponDamageModifier : number;
    m_NoAutoFire : boolean;
    m_TurretSpins : boolean;
    m_TiltCrashJumpjet : boolean;
    m_Normalized : boolean;
    m_ManualReload : boolean;
    m_VisibleLoad : boolean;
    m_LightningRod : boolean;
    m_HunterSeeker : boolean;
    m_Crusher : boolean;
    m_OmniCrusher : boolean;
    m_OmniCrushResistant : boolean;
    m_TiltsWhenCrushes : boolean;
    m_IsSubterranean : boolean;
    m_AutoCrush : boolean;
    m_Bunkerable : boolean;
    m_CanDisguise : boolean;
    m_PermaDisguise : boolean;
    m_DetectDisguise : boolean;
    m_DisguiseWhenStill : boolean;
    m_CanApproachTarget : boolean;
    m_CanRecalcApproachTarget : boolean;
    m_ImmuneToPsionics : boolean;
    m_ImmuneToPsionicWeapons : boolean;
    m_ImmuneToRadiation : boolean;
    m_Parasiteable : boolean;
    m_DefaultToGuardArea : boolean;
    m_Warpable : boolean;
    m_ImmuneToPoison : boolean;
    m_ReselectIfLimboed : boolean;
    m_RejoinTeamIfLimboed : boolean;
    m_Slaved : boolean;
    m_Enslaves : InfantryTypeClass;
    m_SlavesNumber : number;
    m_SlaveRegenRate : number;
    m_SlaveReloadRate : number;
    m_OpenTransportWeapon : number;
    m_Spawned : boolean;
    m_Spawns : AircraftTypeClass;
    m_SpawnsNumber : number;
    m_SpawnRegenRate : number;
    m_SpawnReloadRate : number;
    m_MissileSpawn : boolean;
    m_Underwater : boolean;
    m_BalloonHover : boolean;
    m_SuppressionThreshold : number;
    m_JumpjetTurnRate : number;
    m_JumpjetSpeed : number;
    m_JumpjetClimb : number;
    m_JumpjetCrash : number;
    m_JumpjetHeight : number;
    m_JumpjetAccel : number;
    m_JumpjetWobbles : number;
    m_JumpjetNoWobbles : boolean;
    m_JumpjetDeviation : number;
    m_JumpJet : boolean;
    m_Crashable : boolean;
    m_ConsideredAircraft : boolean;
    m_Organic : boolean;
    m_NoShadow : boolean;
    m_CanPassiveAquire : boolean;
    m_CanRetaliate : boolean;
    m_RequiresStolenThirdTech : boolean;
    m_RequiresStolenSovietTech : boolean;
    m_RequiresStolenAlliedTech : boolean;
    m_RequiredHouses : number;
    m_ForbiddenHouses : number;
    m_SecretHouses : number;
    m_UseBuffer : boolean;
    m_SecondSpawnOffset : any;
    m_IsSelectableCombatant : boolean;
    m_Accelerates : boolean;
    m_DisableVoxelCache : boolean;
    m_DisableShadowCache : boolean;
    m_ZFudgeCliff : number;
    m_ZFudgeColumn : number;
    m_ZFudgeTunnel : number;
    m_ZFudgeBridge : number;
    m_PaletteFile : number;
    m_Palette : any;
    m_align_DF4 : number;
}
class WeaponStruct
{
    m_WeaponType : WeaponTypeClass;
    m_FLH : any;
    m_BarrelLength : number;
    m_BarrelThickness : number;
    m_TurretLocked : boolean;
}
class WeaponTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : WeaponTypeClass;
    static FindOrAllocate(pID_0 : string) : WeaponTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    CalculateSpeed() : void;
    s_AbsID : any;
    s_Array : any;
    m_AmbientDamage : number;
    m_Burst : number;
    m_Projectile : BulletTypeClass;
    m_Damage : number;
    m_Speed : number;
    m_Warhead : WarheadTypeClass;
    m_ROF : number;
    m_Range : number;
    m_MinimumRange : number;
    m_Report : any;
    m___Report : number;
    m_DownReport : any;
    m___DownReport : number;
    m_Anim : any;
    m___Anim : number;
    m_OccupantAnim : AnimTypeClass;
    m_AssaultAnim : AnimTypeClass;
    m_OpenToppedAnim : AnimTypeClass;
    m_AttachedParticleSystem : ParticleSystemTypeClass;
    m_LaserInnerColor : any;
    m_LaserOuterColor : any;
    m_LaserOuterSpread : any;
    m_UseFireParticles : boolean;
    m_UseSparkParticles : boolean;
    m_OmniFire : boolean;
    m_DistributedWeaponFire : boolean;
    m_IsRailgun : boolean;
    m_Lobber : boolean;
    m_Bright : boolean;
    m_IsSonic : boolean;
    m_Spawner : boolean;
    m_LimboLaunch : boolean;
    m_DecloakToFire : boolean;
    m_CellRangefinding : boolean;
    m_FireOnce : boolean;
    m_NeverUse : boolean;
    m_RevealOnFire : boolean;
    m_TerrainFire : boolean;
    m_SabotageCursor : boolean;
    m_MigAttackCursor : boolean;
    m_DisguiseFireOnly : boolean;
    m_DisguiseFakeBlinkTime : number;
    m_InfiniteMindControl : boolean;
    m_FireWhileMoving : boolean;
    m_DrainWeapon : boolean;
    m_FireInTransport : boolean;
    m_Suicide : boolean;
    m_TurboBoost : boolean;
    m_Supress : boolean;
    m_Camera : boolean;
    m_Charges : boolean;
    m_IsLaser : boolean;
    m_DiskLaser : boolean;
    m_IsLine : boolean;
    m_IsBigLaser : boolean;
    m_IsHouseColor : boolean;
    m_LaserDuration : number;
    m_IonSensitive : boolean;
    m_AreaFire : boolean;
    m_IsElectricBolt : boolean;
    m_DrawBoltAsLaser : boolean;
    m_IsAlternateColor : boolean;
    m_IsRadBeam : boolean;
    m_IsRadEruption : boolean;
    m_RadLevel : number;
    m_IsMagBeam : boolean;
}
class BulletTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : BulletTypeClass;
    static FindOrAllocate(pID_0 : string) : BulletTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    Rotates() : boolean;
    SetScaledSpawnDelay(delay_0 : number) : void;
    CreateBullet(Target_0 : AbstractClass, Owner_1 : TechnoClass, Damage_2 : number, WH_3 : WarheadTypeClass, Speed_4 : number, Bright_5 : boolean) : BulletClass;
    s_AbsID : any;
    s_Array : any;
    m_Airburst : boolean;
    m_Floater : boolean;
    m_SubjectToCliffs : boolean;
    m_SubjectToElevation : boolean;
    m_SubjectToWalls : boolean;
    m_VeryHigh : boolean;
    m_Shadow : boolean;
    m_Arcing : boolean;
    m_Dropping : boolean;
    m_Level : boolean;
    m_Inviso : boolean;
    m_Proximity : boolean;
    m_Ranged : boolean;
    m_NoRotate : boolean;
    m_Inaccurate : boolean;
    m_FlakScatter : boolean;
    m_AA : boolean;
    m_AG : boolean;
    m_Degenerates : boolean;
    m_Bouncy : boolean;
    m_AnimPalette : boolean;
    m_FirersPalette : boolean;
    m_Cluster : number;
    m_AirburstWeapon : WeaponTypeClass;
    m_ShrapnelWeapon : WeaponTypeClass;
    m_ShrapnelCount : number;
    m_DetonationAltitude : number;
    m_Vertical : boolean;
    m_Elasticity : number;
    m_Acceleration : number;
    m_Color : any;
    m_Trailer : AnimTypeClass;
    m_ROT : number;
    m_CourseLockDuration : number;
    m_SpawnDelay : number;
    m_ScaledSpawnDelay : number;
    m_Scalable : boolean;
    m_Arm : number;
    m_AnimLow : number;
    m_AnimHigh : number;
    m_AnimRate : number;
    m_Flat : boolean;
}
class BulletClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    GetAnimFrame() : number;
    SetTarget(pTarget_0 : AbstractClass) : void;
    MoveTo(where_0 : any, velocity_1 : any) : boolean;
    Construct(pType_0 : BulletTypeClass, pTarget_1 : AbstractClass, pOwner_2 : TechnoClass, damage_3 : number, pWarhead_4 : WarheadTypeClass, speed_5 : number, bright_6 : boolean) : void;
    Explode(destroy_0 : boolean) : void;
    Detonate(coords_0 : any) : void;
    Shrapnel() : void;
    static ApplyRadiationToCell(cell_0 : any, radius_1 : number, amount_2 : number) : void;
    LoseTarget() : void;
    IsHoming() : boolean;
    SetWeaponType(weapon_0 : WeaponTypeClass) : void;
    GetWeaponType() : WeaponTypeClass;
    InitScalable() : void;
    NukeMaker() : void;
    GetTargetCoords() : any;
    s_AbsID : any;
    s_Array : any;
    s_ScalableBullets : any;
    m_Type : BulletTypeClass;
    m_Owner : TechnoClass;
    m_unknown_B4 : boolean;
    m_Data : BulletData;
    m_Bright : boolean;
    m_unknown_E4 : number;
    m_Velocity : any;
    m_unknown_100 : number;
    m_unknown_104 : boolean;
    m_unknown_108 : number;
    m_Target : AbstractClass;
    m_Speed : number;
    m_InheritedColor : number;
    m_unknown_118 : number;
    m_unknown_11C : number;
    m_unknown_120 : number;
    m_WH : WarheadTypeClass;
    m_AnimFrame : number;
    m_AnimRateCounter : number;
    m_WeaponType : WeaponTypeClass;
    m_SourceCoords : any;
    m_TargetCoords : any;
    m_LastMapCoords : any;
    m_DamageMultiplier : number;
    m_NextAnim : AnimClass;
    m_SpawnNextAnim : boolean;
    m_Range : number;
}
class RadioClass
    extends MissionClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    SendToFirstLink(command_0 : any) : any;
    SendCommand(command_0 : any, pRecipient_1 : TechnoClass) : any;
    SendCommandWithData(command_0 : any, pInOut_1 : AbstractClass, pRecipient_2 : TechnoClass) : any;
    SendToEachLink(command_0 : any) : void;
    GetNthLink(idx_0 : number) : TechnoClass;
    ContainsLink(pLink_0 : TechnoClass) : boolean;
    FindLinkIndex(pLink_0 : TechnoClass) : number;
    HasFreeLink() : boolean;
    HasFreeLink(pIgnore_0 : TechnoClass) : boolean;
    HasAnyLink() : boolean;
    SetLinkCount(count_0 : number) : void;
    m_LastCommands : any;
    m_RadioLinks : any;
    m___RadioLinks : number;
}
class MissionClass
    extends ObjectClass
{
    QueueMission(mission_0 : any, start_mission_1 : boolean) : boolean;
    NextMission() : boolean;
    ForceMission(mission_0 : any) : void;
    Override_Mission(mission_0 : any, target_1 : AbstractClass, destination_2 : AbstractClass) : void;
    Mission_Revert() : boolean;
    MissionIsOverriden() : boolean;
    ReadyToNextMission() : boolean;
    Mission_Sleep() : number;
    Mission_Harmless() : number;
    Mission_Ambush() : number;
    Mission_Attack() : number;
    Mission_Capture() : number;
    Mission_Eaten() : number;
    Mission_Guard() : number;
    Mission_AreaGuard() : number;
    Mission_Harvest() : number;
    Mission_Hunt() : number;
    Mission_Move() : number;
    Mission_Retreat() : number;
    Mission_Return() : number;
    Mission_Stop() : number;
    Mission_Unload() : number;
    Mission_Enter() : number;
    Mission_Construction() : number;
    Mission_Selling() : number;
    Mission_Repair() : number;
    Mission_Missile() : number;
    Mission_Open() : number;
    Mission_Rescue() : number;
    Mission_Patrol() : number;
    Mission_ParaDropApproach() : number;
    Mission_ParaDropOverfly() : number;
    Mission_Wait() : number;
    Mission_SpyPlaneApproach() : number;
    Mission_SpyPlaneOverfly() : number;
    m_CurrentMission : any;
    m_SuspendedMission : any;
    m_QueuedMission : any;
    m_unknown_bool_B8 : boolean;
    m_MissionStatus : number;
    m_CurrentMissionStartTime : number;
    m_unknown_C4 : number;
    m_UpdateTimer : CDTimerClass;
    m___UpdateTimer : number;
}
class InfantryTypeClass
    extends TechnoTypeClass
{
    static Find(pID_0 : string) : InfantryTypeClass;
    static FindOrAllocate(pID_0 : string) : InfantryTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_ArrayIndex : number;
    m_Pip : any;
    m_OccupyPip : any;
    m_OccupyWeapon : WeaponStruct;
    m_EliteOccupyWeapon : WeaponStruct;
    m_Sequence : any;
    m_FireUp : number;
    m_FireProne : number;
    m_SecondaryFire : number;
    m_SecondaryProne : number;
    m_DeadBodies : any;
    m_DeathAnims : any;
    m_VoiceComment : any;
    m_EnterWaterSound : number;
    m_LeaveWaterSound : number;
    m_Cyborg : boolean;
    m_NotHuman : boolean;
    m_Ivan : boolean;
    m_DirectionDistance : number;
    m_Occupier : boolean;
    m_Assaulter : boolean;
    m_HarvestRate : number;
    m_Fearless : boolean;
    m_Crawls : boolean;
    m_Infiltrate : boolean;
    m_Fraidycat : boolean;
    m_TiberiumProof : boolean;
    m_Civilian : boolean;
    m_C4 : boolean;
    m_Engineer : boolean;
    m_Agent : boolean;
    m_Thief : boolean;
    m_VehicleThief : boolean;
    m_Doggie : boolean;
    m_Deployer : boolean;
    m_DeployedCrushable : boolean;
    m_UseOwnName : boolean;
    m_JumpJetTurn : boolean;
}
class CellClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    FindTechnoNearestTo(offsetPixel_0 : any, alt_1 : boolean, pExcludeThis_2 : TechnoClass) : TechnoClass;
    FindObjectOfType(abs_0 : any, alt_1 : boolean) : ObjectClass;
    GetBuilding() : BuildingClass;
    GetUnit(alt_0 : boolean) : UnitClass;
    GetInfantry(alt_0 : boolean) : InfantryClass;
    GetAircraft(alt_0 : boolean) : AircraftClass;
    GetTerrain(alt_0 : boolean) : TerrainClass;
    GetSomeObject(coords_0 : any, alt_1 : boolean) : ObjectClass;
    SetWallOwner() : void;
    IncreaseShroudCounter() : void;
    ReduceShroudCounter() : void;
    IsShrouded() : boolean;
    Unshroud() : void;
    ShapeRect(pRet_0 : any) : any;
    IsFogged() : boolean;
    FogCell() : void;
    CleanFog() : void;
    ClearFoggedObjects() : void;
    SetupLAT() : void;
    RecalcAttributes(cellLevel_0 : number) : void;
    BlowUpBridge() : void;
    CanThisExistHere(SpeedType_0 : any, pObject_1 : BuildingTypeClass, pOwner_2 : HouseClass) : boolean;
    ScatterContent(crd_0 : any, ignoreMission_1 : boolean, ignoreDestination_2 : boolean, alt_3 : boolean) : void;
    GetNeighbourCell(facing_0 : any) : CellClass;
    UpdateThreat(SourceHouse_0 : number, ThreatLevel_1 : number) : void;
    CollectCrate(pCollector_0 : FootClass) : void;
    ProcessColourComponents(arg0_0 : number, pIntensity_1 : number, pAmbient_2 : number, a5_3 : number, a6_4 : number, tintR_5 : number, tintG_6 : number, tintB_7 : number) : void;
    GetTunnel() : any;
    GetContainingRect(dest_0 : any) : any;
    GetUIName() : any;
    ConnectsToOverlay(idxOverlay_0 : number, direction_1 : number) : boolean;
    GetContainedTiberiumIndex() : number;
    GetContainedTiberiumValue() : number;
    SpreadTiberium(forced_0 : boolean) : boolean;
    IncreaseTiberium(idxTiberium_0 : number, amount_1 : number) : boolean;
    ReduceTiberium(amount_0 : number) : void;
    CanTiberiumGerminate(tib_0 : TiberiumClass) : boolean;
    SetMapCoords(coords_0 : any) : void;
    GetFloorHeight(subcoords_0 : any) : number;
    GetCellCoords(pOutBuffer_0 : any) : any;
    GetCellCoords() : any;
    ActivateVeins() : void;
    CloakGen_InclHouse(idx_0 : number) : boolean;
    CloakGen_AddHouse(idx_0 : number) : void;
    CloakGen_RemHouse(idx_0 : number) : void;
    DrawObjectsCloaked(OwnerHouseIdx_0 : number) : boolean;
    Sensors_InclHouse(idx_0 : number) : boolean;
    Sensors_AddOfHouse(idx_0 : number) : void;
    Sensors_RemOfHouse(idx_0 : number) : void;
    DisguiseSensors_InclHouse(idx_0 : number) : boolean;
    DisguiseSensors_AddOfHouse(idx_0 : number) : void;
    DisguiseSensors_RemOfHouse(idx_0 : number) : void;
    SetRadSite(pRad_0 : RadSiteClass) : void;
    GetRadSite() : RadSiteClass;
    IsRadiated() : boolean;
    GetRadLevel() : number;
    RadLevel_Increase(amount_0 : number) : void;
    RadLevel_Decrease(amount_0 : number) : void;
    ContainsBridge() : boolean;
    ContainsBridgeEx() : boolean;
    GetContent() : ObjectClass;
    GetLevel() : number;
    Tile_Is_Tunnel() : boolean;
    Tile_Is_Water() : boolean;
    Tile_Is_Blank() : boolean;
    Tile_Is_Ramp() : boolean;
    Tile_Is_Cliff() : boolean;
    Tile_Is_Shore() : boolean;
    Tile_Is_Wet() : boolean;
    Tile_Is_MiscPave() : boolean;
    Tile_Is_Pave() : boolean;
    Tile_Is_DirtRoad() : boolean;
    Tile_Is_PavedRoad() : boolean;
    Tile_Is_PavedRoadEnd() : boolean;
    Tile_Is_PavedRoadSlope() : boolean;
    Tile_Is_Median() : boolean;
    Tile_Is_Bridge() : boolean;
    Tile_Is_WoodBridge() : boolean;
    Tile_Is_ClearToSandLAT() : boolean;
    Tile_Is_Green() : boolean;
    Tile_Is_NotWater() : boolean;
    Tile_Is_DestroyableCliff() : boolean;
    static Cell2Coord(cell_0 : any, z_1 : number) : any;
    static Coord2Cell(crd_0 : any) : any;
    FixHeight(crd_0 : any) : any;
    GetCoordsWithBridge() : any;
    MarkForRedraw() : void;
    ChainReaction() : void;
    FindInfantrySubposition(pOutBuffer_0 : any, coords_1 : any, ignoreContents_2 : boolean, alt_3 : boolean, useCellCoords_4 : boolean) : any;
    FindInfantrySubposition(coords_0 : any, ignoreContents_1 : boolean, alt_2 : boolean, useCellCoords_3 : boolean) : any;
    TryAssignJumpjet(pObject_0 : FootClass) : boolean;
    AddContent(Content_0 : ObjectClass, onBridge_1 : boolean) : void;
    RemoveContent(pContent_0 : ObjectClass, onBridge_1 : boolean) : void;
    ReplaceTag(pTag_0 : TagClass) : void;
    UpdateCellLighting() : void;
    CalculateLightSourceLighting(nIntensity_0 : number, nAmbient_1 : number, Red1_2 : number, Green1_3 : number, Blue1_4 : number, Red2_5 : number, Green2_6 : number, Blue2_7 : number) : void;
    InitLightConvert(pDrawer_0 : any, nIntensity_1 : number, nAmbient_2 : number, Red1_3 : number, Green1_4 : number, Blue1_5 : number) : void;
    DrawOverlay(Location_0 : any, Bound_1 : any) : void;
    DrawOverlayShadow(Location_0 : any, Bound_1 : any) : void;
    IsClearToMove(speedType_0 : any, ignoreInfantry_1 : boolean, ignoreVehicles_2 : boolean, zone_3 : number, movementZone_4 : any, level_5 : number, isBridge_6 : boolean) : boolean;
    s_AbsID : any;
    s_BridgeLevels : number;
    s_BridgeHeight : number;
    m_MapCoords : any;
    m_FoggedObjects : any;
    m_BridgeOwnerCell : CellClass;
    m_unknown_30 : number;
    m_LightConvert : any;
    m_IsoTileTypeIndex : number;
    m_AttachedTag : TagClass;
    m_Rubble : BuildingTypeClass;
    m_OverlayTypeIndex : number;
    m_SmudgeTypeIndex : number;
    m_Passability : any;
    m_WallOwnerIndex : number;
    m_InfantryOwnerIndex : number;
    m_AltInfantryOwnerIndex : number;
    m_unknown_5C : number;
    m_unknown_60 : number;
    m_RedrawFrame : number;
    m_InViewportRect : any;
    m_CloakedByHouses : number;
    m_BaseSpacerOfHouses : number;
    m_Jumpjet : FootClass;
    m_FirstObject : ObjectClass;
    m_AltObject : ObjectClass;
    m_LandType : any;
    m_RadLevel : number;
    m_RadSite : RadSiteClass;
    m_PixelFX : any;
    m_OccupyHeightsCoveringMe : number;
    m_Intensity : number;
    m_Ambient : number;
    m_Intensity_Normal : number;
    m_Intensity_Terrain : number;
    m_Color1_Blue : number;
    m_Color2_Red : number;
    m_Color2_Green : number;
    m_Color2_Blue : number;
    m_TubeIndex : number;
    m_unknown_118 : number;
    m_IsIceGrowthAllowed : number;
    m_Height : number;
    m_Level : number;
    m_SlopeIndex : number;
    m_unknown_11D : number;
    m_OverlayData : number;
    m_SmudgeData : number;
    m_Visibility : number;
    m_Foggedness : number;
    m_BlockedNeighbours : number;
    m_OccupationFlags : number;
    m_AltOccupationFlags : number;
    m_AltFlags : any;
    m_ShroudCounter : number;
    m_GapsCoveringThisCell : number;
    m_VisibilityChanged : boolean;
    m_unknown_13C : number;
    m_Flags : any;
}
class BuildingClass
    extends TechnoClass
{
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    Destroyed(Killer_0 : ObjectClass) : void;
    ForceCreate(coord_0 : any, dwUnk_1 : number) : boolean;
    FindExitCell(dwUnk_0 : number, dwUnk2_1 : number) : any;
    DistanceToDockingCoord(pObj_0 : ObjectClass) : number;
    Place(captured_0 : boolean) : void;
    UpdateConstructionOptions() : void;
    Draw(point_0 : any, rect_1 : any) : void;
    FireAngleTo(pObject_0 : ObjectClass) : any;
    Destory(dwUnused_0 : number, pTechno_1 : TechnoClass, NoSurvivor_2 : boolean, cell_3 : any) : void;
    TogglePrimaryFactory() : boolean;
    SensorArrayActivate(cell_0 : any) : void;
    SensorArrayDeactivate(cell_0 : any) : void;
    DisguiseDetectorActivate(cell_0 : any) : void;
    DisguiseDetectorDeactivate(cell_0 : any) : void;
    AlwaysZero() : number;
    UpdateAnimations() : void;
    GetCurrentFrame() : number;
    IsAllFogged() : boolean;
    SetRallypoint(pTarget_0 : any, bPlayEVA_1 : boolean) : void;
    FreezeInFog(pFoggedArray_0 : any, pCell_1 : CellClass, Visible_2 : boolean) : void;
    GoOnline() : void;
    GoOffline() : void;
    GetPowerOutput() : number;
    GetPowerDrain() : number;
    GetFWFlags() : number;
    CreateEndPost(arg_0 : boolean) : void;
    UnloadBunker() : void;
    ClearBunker() : void;
    EmptyBunker() : void;
    AfterDestruction() : void;
    DestroyNthAnim(Slot_0 : any) : void;
    PlayNthAnim(Slot_0 : any, effectDelay_1 : number) : void;
    PlayAnim(animName_0 : string, Slot_1 : any, Damaged_2 : boolean, Garrisoned_3 : boolean, effectDelay_4 : number) : void;
    ToggleDamagedAnims(isDamaged_0 : boolean) : void;
    DisableStuff() : void;
    EnableStuff() : void;
    DisableTemporal() : void;
    EnableTemporal() : void;
    FirstActiveSWIdx() : number;
    GetShapeNumber() : number;
    BeginMode(bType_0 : any) : void;
    SecondActiveSWIdx() : number;
    FireLaser(Coords_0 : any) : void;
    IsBeingDrained() : boolean;
    UpdateBunker() : boolean;
    KillOccupants(pAssaulter_0 : TechnoClass) : void;
    MakeTraversable() : boolean;
    CheckFog() : boolean;
    GetVoxelBarrelOffsetMatrix(ret_0 : any) : any;
    IsTraversable() : boolean;
    DrawInfoTipAndSpiedSelection(pLocation_0 : any, pRect_1 : any) : number;
    HasSuperWeapon(index_0 : number) : boolean;
    GetSecretProduction() : TechnoTypeClass;
    GetAnim(slot_0 : any) : AnimClass;
    GetAnim(slot_0 : any) : AnimClass;
    GetAnimState(slot_0 : any) : boolean;
    GetAnimState(slot_0 : any) : boolean;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_Type : BuildingTypeClass;
    m_Factory : FactoryClass;
    m_C4Timer : CDTimerClass;
    m_BState : number;
    m_QueueBState : number;
    m_OwnerCountryIndex : number;
    m_C4AppliedBy : InfantryClass;
    m_unknown_544 : number;
    m_FirestormAnim : AnimClass;
    m_PsiWarnAnim : AnimClass;
    m_unknown_timer_550 : CDTimerClass;
    m_Anims : AnimClass;
    m_AnimStates : boolean;
    m_DamageFireAnims : AnimClass;
    m_RequiresDamageFires : boolean;
    m_Upgrades : BuildingTypeClass;
    m_FiringSWType : number;
    m_unknown_5FC : number;
    m_Spotlight : BuildingLightClass;
    m_GateTimer : RateTimer;
    m_LightSource : LightSourceClass;
    m_LaserFenceFrame : number;
    m_FirestormWallFrame : number;
    m_RepairProgress : StageClass;
    m_unknown_rect_63C : any;
    m_unknown_coord_64C : any;
    m_unknown_int_658 : number;
    m_unknown_65C : number;
    m_HasPower : boolean;
    m_IsOverpowered : boolean;
    m_RegisteredAsPoweredUnitSource : boolean;
    m_SupportingPrisms : number;
    m_HasExtraPowerBonus : boolean;
    m_HasExtraPowerDrain : boolean;
    m_Overpowerers : any;
    m_Occupants : any;
    m_FiringOccupantIndex : number;
    m_Audio7 : any;
    m_Audio8 : any;
    m_WasOnline : boolean;
    m_ShowRealName : boolean;
    m_BeingProduced : boolean;
    m_ShouldRebuild : boolean;
    m_HasEngineer : boolean;
    m_CashProductionTimer : CDTimerClass;
    m_AI_Sellable : boolean;
    m_IsReadyToCommence : boolean;
    m_NeedsRepairs : boolean;
    m_C4Applied : boolean;
    m_NoCrew : boolean;
    m_unknown_bool_6E1 : boolean;
    m_unknown_bool_6E2 : boolean;
    m_HasBeenCaptured : boolean;
    m_ActuallyPlacedOnMap : boolean;
    m_unknown_bool_6E5 : boolean;
    m_IsDamaged : boolean;
    m_IsFogged : boolean;
    m_IsBeingRepaired : boolean;
    m_HasBuildUp : boolean;
    m_StuffEnabled : boolean;
    m_HasCloakingData : number;
    m_CloakRadius : number;
    m_Translucency : number;
    m_StorageFilledSlots : number;
    m_SecretProduction : TechnoTypeClass;
    m_ColorAdd : any;
    m_unknown_int_6FC : number;
    m_unknown_short_700 : number;
    m_UpgradeLevel : number;
    m_GateStage : number;
    m_PrismStage : any;
    m_PrismTargetCoords : any;
    m_DelayBeforeFiring : number;
    m_BunkerState : number;
}
class BuildingTypeClass
    extends TechnoTypeClass
{
    static Find(pID_0 : string) : BuildingTypeClass;
    static FindOrAllocate(pID_0 : string) : BuildingTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    LoadBuildup() : any;
    ClearBuildUp() : void;
    IsVehicle() : boolean;
    GetFoundationWidth() : number;
    GetFoundationHeight(bIncludeBib_0 : boolean) : number;
    CanPlaceHere(cell_0 : any, owner_1 : HouseClass) : boolean;
    HasSuperWeapon(index_0 : number) : boolean;
    HasSuperWeapon() : boolean;
    CanTogglePower() : boolean;
    GetBuildingAnim(slot_0 : any) : BuildingAnimStruct;
    GetBuildingAnim(slot_0 : any) : BuildingAnimStruct;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_ArrayIndex : number;
    m_FoundationData : any;
    m_Buildup : any;
    m_BuildupLoaded : boolean;
    m_BuildCat : any;
    m_HalfDamageSmokeLocation1 : any;
    m_HalfDamageSmokeLocation2 : any;
    m_align_E24 : number;
    m_GateCloseDelay : number;
    m_LightVisibility : number;
    m_LightIntensity : number;
    m_LightRedTint : number;
    m_LightGreenTint : number;
    m_LightBlueTint : number;
    m_PrimaryFirePixelOffset : any;
    m_SecondaryFirePixelOffset : any;
    m_ToOverlay : OverlayTypeClass;
    m_ToTile : number;
    m_BuildupFile : number;
    m_BuildupSound : number;
    m_PackupSound : number;
    m_CreateUnitSound : number;
    m_UnitEnterSound : number;
    m_UnitExitSound : number;
    m_WorkingSound : number;
    m_NotWorkingSound : number;
    m_PowersUpBuilding : number;
    m_FreeUnit : UnitTypeClass;
    m_SecretInfantry : InfantryTypeClass;
    m_SecretUnit : UnitTypeClass;
    m_SecretBuilding : BuildingTypeClass;
    m_field_EB0 : number;
    m_Adjacent : number;
    m_Factory : any;
    m_TargetCoordOffset : any;
    m_ExitCoord : any;
    m_FoundationOutside : any;
    m_field_ED8 : number;
    m_DeployFacing : number;
    m_PowerBonus : number;
    m_PowerDrain : number;
    m_ExtraPowerBonus : number;
    m_ExtraPowerDrain : number;
    m_Foundation : any;
    m_Height : number;
    m_OccupyHeight : number;
    m_MidPoint : number;
    m_DoorStages : number;
    m_BuildingAnimFrame : BuildingAnimFrameStruct;
    m_BuildingAnim : BuildingAnimStruct;
    m_Upgrades : number;
    m_DeployingAnim : any;
    m_DeployingAnimLoaded : boolean;
    m_UnderDoorAnim : any;
    m_UnderDoorAnimLoaded : boolean;
    m_Rubble : any;
    m_RubbleLoaded : boolean;
    m_RoofDeployingAnim : any;
    m_RoofDeployingAnimLoaded : boolean;
    m_UnderRoofDoorAnim : any;
    m_UnderRoofDoorAnimLoaded : boolean;
    m_DoorAnim : any;
    m_SpecialZOverlay : any;
    m_SpecialZOverlayZAdjust : number;
    m_BibShape : any;
    m_BibShapeLoaded : boolean;
    m_NormalZAdjust : number;
    m_AntiAirValue : number;
    m_AntiArmorValue : number;
    m_AntiInfantryValue : number;
    m_ZShapePointMove : any;
    m_unknown_1538 : number;
    m_unknown_153C : number;
    m_unknown_1540 : number;
    m_unknown_1544 : number;
    m_ExtraLight : number;
    m_TogglePower : boolean;
    m_HasSpotlight : boolean;
    m_IsTemple : boolean;
    m_IsPlug : boolean;
    m_HoverPad : boolean;
    m_BaseNormal : boolean;
    m_EligibileForAllyBuilding : boolean;
    m_EligibleForDelayKill : boolean;
    m_NeedsEngineer : boolean;
    m_CaptureEvaEvent : number;
    m_ProduceCashStartup : number;
    m_ProduceCashAmount : number;
    m_ProduceCashDelay : number;
    m_InfantryGainSelfHeal : number;
    m_UnitsGainSelfHeal : number;
    m_RefinerySmokeFrames : number;
    m_Bib : boolean;
    m_Wall : boolean;
    m_Capturable : boolean;
    m_Powered : boolean;
    m_PoweredSpecial : boolean;
    m_Overpowerable : boolean;
    m_Spyable : boolean;
    m_CanC4 : boolean;
    m_WantsExtraSpace : boolean;
    m_Unsellable : boolean;
    m_ClickRepairable : boolean;
    m_CanBeOccupied : boolean;
    m_CanOccupyFire : boolean;
    m_MaxNumberOccupants : number;
    m_ShowOccupantPips : boolean;
    m_MuzzleFlash : any;
    m_DamageFireOffset : any;
    m_QueueingCell : any;
    m_NumberImpassableRows : number;
    m_RemoveOccupy : any;
    m_AddOccupy : any;
    m_Radar : boolean;
    m_SpySat : boolean;
    m_ChargeAnim : boolean;
    m_IsAnimDelayedFire : boolean;
    m_SiloDamage : boolean;
    m_UnitRepair : boolean;
    m_UnitReload : boolean;
    m_Bunker : boolean;
    m_Cloning : boolean;
    m_Grinding : boolean;
    m_UnitAbsorb : boolean;
    m_InfantryAbsorb : boolean;
    m_SecretLab : boolean;
    m_DoubleThick : boolean;
    m_Flat : boolean;
    m_DockUnload : boolean;
    m_Recoilless : boolean;
    m_HasStupidGuardMode : boolean;
    m_BridgeRepairHut : boolean;
    m_Gate : boolean;
    m_SAM : boolean;
    m_ConstructionYard : boolean;
    m_NukeSilo : boolean;
    m_Refinery : boolean;
    m_Weeder : boolean;
    m_WeaponsFactory : boolean;
    m_LaserFencePost : boolean;
    m_LaserFence : boolean;
    m_FirestormWall : boolean;
    m_Hospital : boolean;
    m_Armory : boolean;
    m_EMPulseCannon : boolean;
    m_TickTank : boolean;
    m_TurretAnimIsVoxel : boolean;
    m_BarrelAnimIsVoxel : boolean;
    m_CloakGenerator : boolean;
    m_SensorArray : boolean;
    m_ICBMLauncher : boolean;
    m_Artillary : boolean;
    m_Helipad : boolean;
    m_OrePurifier : boolean;
    m_FactoryPlant : boolean;
    m_InfantryCostBonus : number;
    m_UnitsCostBonus : number;
    m_AircraftCostBonus : number;
    m_BuildingsCostBonus : number;
    m_DefensesCostBonus : number;
    m_GDIBarracks : boolean;
    m_NODBarracks : boolean;
    m_YuriBarracks : boolean;
    m_ChargedAnimTime : number;
    m_DelayedFireDelay : number;
    m_SuperWeapon : number;
    m_SuperWeapon2 : number;
    m_GateStages : number;
    m_PowersUpToLevel : number;
    m_DamagedDoor : boolean;
    m_InvisibleInGame : boolean;
    m_TerrainPalette : boolean;
    m_PlaceAnywhere : boolean;
    m_ExtraDamageStage : boolean;
    m_AIBuildThis : boolean;
    m_IsBaseDefense : boolean;
    m_CloakRadiusInCells : number;
    m_ConcentricRadialIndicator : boolean;
    m_PsychicDetectionRadius : number;
    m_BarrelStartPitch : number;
    m_VoxelBarrelFile : number;
    m_VoxelBarrelOffsetToPitchPivotPoint : any;
    m_VoxelBarrelOffsetToRotatePivotPoint : any;
    m_VoxelBarrelOffsetToBuildingPivotPoint : any;
    m_VoxelBarrelOffsetToBarrelEnd : any;
    m_DemandLoad : boolean;
    m_DemandLoadBuildup : boolean;
    m_FreeBuildup : boolean;
    m_IsThreatRatingNode : boolean;
    m_PrimaryFireDualOffset : boolean;
    m_ProtectWithWall : boolean;
    m_CanHideThings : boolean;
    m_CrateBeneath : boolean;
    m_LeaveRubble : boolean;
    m_CrateBeneathIsMoney : boolean;
    m_TheaterSpecificID : number;
    m_NumberOfDocks : number;
    m_DockingOffsets : any;
}
class BuildingAnimStruct
{
    m_Anim : number;
    m_Damaged : number;
    m_Garrisoned : number;
    m_Position : any;
    m_ZAdjust : number;
    m_YSort : number;
    m_Powered : boolean;
    m_PoweredLight : boolean;
    m_PoweredEffect : boolean;
    m_PoweredSpecial : boolean;
}
class OverlayTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : OverlayTypeClass;
    static FindOrAllocate(pID_0 : string) : OverlayTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    vt_entry_6C(pDest_0 : any, pSrc_1 : any) : any;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    Draw(pClientCoords_0 : any, pClipRect_1 : any, nFrame_2 : number) : void;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_LandType : any;
    m_CellAnim : AnimTypeClass;
    m_DamageLevels : number;
    m_Strength : number;
    m_Wall : boolean;
    m_Tiberium : boolean;
    m_Crate : boolean;
    m_CrateTrigger : boolean;
    m_NoUseTileLandType : boolean;
    m_IsVeinholeMonster : boolean;
    m_IsVeins : boolean;
    m_ImageLoaded : boolean;
    m_Explodes : boolean;
    m_ChainReaction : boolean;
    m_Overrides : boolean;
    m_DrawFlat : boolean;
    m_IsRubble : boolean;
    m_IsARock : boolean;
    m_RadarColor : any;
}
class UnitTypeClass
    extends TechnoTypeClass
{
    static Find(pID_0 : string) : UnitTypeClass;
    static FindOrAllocate(pID_0 : string) : UnitTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_ArrayIndex : number;
    m_MovementRestrictedTo : any;
    m_HalfDamageSmokeLocation : any;
    m_Passive : boolean;
    m_CrateGoodie : boolean;
    m_Harvester : boolean;
    m_Weeder : boolean;
    m_unknown_E10 : boolean;
    m_HasTurret : boolean;
    m_DeployToFire : boolean;
    m_IsSimpleDeployer : boolean;
    m_IsTilter : boolean;
    m_UseTurretShadow : boolean;
    m_TooBigToFitUnderBridge : boolean;
    m_CanBeach : boolean;
    m_SmallVisceroid : boolean;
    m_LargeVisceroid : boolean;
    m_CarriesCrate : boolean;
    m_NonVehicle : boolean;
    m_StandingFrames : number;
    m_DeathFrames : number;
    m_DeathFrameRate : number;
    m_StartStandFrame : number;
    m_StartWalkFrame : number;
    m_StartFiringFrame : number;
    m_StartDeathFrame : number;
    m_MaxDeathCounter : number;
    m_Facings : number;
    m_FiringSyncFrame0 : number;
    m_FiringSyncFrame1 : number;
    m_BurstDelay0 : number;
    m_BurstDelay1 : number;
    m_BurstDelay2 : number;
    m_BurstDelay3 : number;
    m_AltImage : any;
    m_WalkFrames : number;
    m_FiringFrames : number;
    m_AltImageFile : number;
}
class BuildingAnimFrameStruct
{
    m_dwUnknown : number;
    m_FrameCount : number;
    m_FrameDuration : number;
}
class FactoryClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    HasProgressChanged() : boolean;
    DemandProduction(pType_0 : TechnoTypeClass, pOwner_1 : HouseClass, shouldQueue_2 : boolean) : boolean;
    SetObject(pObject_0 : TechnoClass) : void;
    Suspend(manual_0 : boolean) : boolean;
    Unsuspend(manual_0 : boolean) : boolean;
    GetBuildTimeFrames() : number;
    AbandonProduction() : boolean;
    GetProgress() : number;
    IsDone() : boolean;
    GetCostPerStep() : number;
    CompletedProduction() : boolean;
    StartProduction() : void;
    RemoveOneFromQueue(pItem_0 : TechnoTypeClass) : boolean;
    CountTotal(pType_0 : TechnoTypeClass) : number;
    IsQueued(pType_0 : TechnoTypeClass) : boolean;
    static FindByOwnerAndProduct(pHouse_0 : HouseClass, pItem_1 : TechnoTypeClass) : FactoryClass;
    s_AbsID : any;
    s_Array : any;
    m_Production : StageClass;
    m_QueuedObjects : any;
    m_Object : TechnoClass;
    m_OnHold : boolean;
    m_IsDifferent : boolean;
    m_Balance : number;
    m_OriginalBalance : number;
    m_SpecialItem : number;
    m_Owner : HouseClass;
    m_IsSuspended : boolean;
    m_IsManual : boolean;
}
class StageClass
{
    Start(rate_0 : number) : void;
    Start(rate_0 : number, step_1 : number) : void;
    Update() : boolean;
    m_Value : number;
    m_HasChanged : boolean;
    m_Timer : CDTimerClass;
    m_Rate : number;
    m_Step : number;
}
class InfantryClass
    extends FootClass
{
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    IsDeployed() : boolean;
    PlayAnim(index_0 : any, force_1 : boolean, randomStartFrame_2 : boolean) : boolean;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_Type : InfantryTypeClass;
    m_SequenceAnim : any;
    m_unknown_Timer_6C8 : CDTimerClass;
    m_PanicDurationLeft : number;
    m_PermanentBerzerk : boolean;
    m_Technician : boolean;
    m_unknown_bool_6DA : boolean;
    m_Crawling : boolean;
    m_unknown_bool_6DC : boolean;
    m_unknown_bool_6DD : boolean;
    m_unknown_6E0 : number;
    m_ShouldDeploy : boolean;
    m_unknown_int_6E8 : number;
}
class FootClass
    extends TechnoClass
{
    Destroyed(Killer_0 : ObjectClass) : void;
    ForceCreate(coord_0 : any, dwUnk_1 : number) : boolean;
    ReceiveGunner(Gunner_0 : FootClass) : void;
    RemoveGunner(Gunner_0 : FootClass) : void;
    IsLeavingMap() : boolean;
    vt_entry_4E0() : boolean;
    CanDeployNow() : boolean;
    AddSensorsAt(cell_0 : any) : void;
    RemoveSensorsAt(cell_0 : any) : void;
    vt_entry_4F0(pCrd_0 : any) : any;
    vt_entry_4F4() : void;
    vt_entry_4F8() : boolean;
    MoveTo(pCrd_0 : any) : boolean;
    StopMoving() : boolean;
    vt_entry_504() : boolean;
    ChronoWarpTo(pDest_0 : any) : boolean;
    Draw_A_SHP(SHP_0 : any, idxFacing_1 : number, Coords_2 : any, Rectangle_3 : any, dwUnk5_4 : number, dwUnk6_5 : number, dwUnk7_6 : number, ZGradient_7 : any, dwUnk9_8 : number, extraLight_9 : number, dwUnk11_10 : number, dwUnk12_11 : number, dwUnk13_12 : number, dwUnk14_13 : number, dwUnk15_14 : number, dwUnk16_15 : number) : void;
    Draw_A_VXL(VXL_0 : any, HVAFrameIndex_1 : number, Flags_2 : number, Cache_3 : any, Rectangle_4 : any, CenterPoint_5 : any, Matrix_6 : any, dwUnk8_7 : number, DrawFlags_8 : number, dwUnk10_9 : number) : void;
    GoBerzerk() : void;
    Panic() : void;
    UnPanic() : void;
    PlayIdleAnim(nIdleAnimNumber_0 : number) : void;
    vt_entry_524() : number;
    vt_entry_528(bList_0 : any, dwUnk2_1 : number, dwUnk3_2 : number) : number;
    vt_entry_52C(bType_0 : BuildingTypeClass, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number) : BuildingClass;
    vt_entry_530(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : number;
    vt_entry_534(dwUnk_0 : number, dwUnk2_1 : number) : void;
    GetCurrentSpeed() : number;
    vt_entry_53C(dwUnk_0 : number) : number;
    vt_entry_540(dwUnk_0 : number) : void;
    SetSpeedPercentage(percentage_0 : number) : void;
    vt_entry_548() : void;
    vt_entry_54C() : void;
    vt_entry_550(dwUnk_0 : number) : boolean;
    CanBeRecruited(ByWhom_0 : HouseClass) : boolean;
    CreateWakes(coords_0 : any) : void;
    Jumpjet_LocationClear() : boolean;
    Jumpjet_OccupyCell(Cell_0 : any) : void;
    FootClass_ImbueLocomotor(target_0 : FootClass, clsid_1 : any) : void;
    UpdatePassengerCoords() : void;
    AbortMotion() : void;
    UpdatePathfinding(unkCell_0 : any, unkCell2_1 : any, unk3_2 : number) : boolean;
    RemoveFirstPassenger() : FootClass;
    RemovePassenger(pPassenger_0 : FootClass) : FootClass;
    EnterAsPassenger(pPassenger_0 : FootClass) : void;
    ClearNavQueue() : void;
    MoveToTiberium(radius_0 : number, scanClose_1 : boolean) : boolean;
    MoveToWeed(radius_0 : number) : boolean;
    s_AbsDerivateID : any;
    s_Array : any;
    m_PlanningPathIdx : number;
    m_WaypointNearbyAccessibleCellDelta : any;
    m_WaypointCell : any;
    m_unknown_52C : number;
    m_unknown_530 : number;
    m_unknown_534 : number;
    m_WalkedFramesSoFar : number;
    m_unknown_bool_53C : boolean;
    m_unknown_540 : number;
    m_Audio7 : any;
    m___Audio7 : number;
    m_CurrentMapCoords : any;
    m_LastMapCoords : any;
    m_LastFlightMapCoords : any;
    m_CurrentJumpjetMapCoords : any;
    m_unknown_coords_568 : any;
    m_SpeedPercentage : number;
    m_SpeedMultiplier : number;
    m_unknown_abstract_array_588 : any;
    m___unknown_abstract_array_588 : number;
    m_unknown_5A0 : AbstractClass;
    m_Destination : AbstractClass;
    m_LastDestination : AbstractClass;
    m_NavQueue : any;
    m___NavQueue : number;
    m_unknown_int_5C4 : number;
    m_unknown_5C8 : number;
    m_unknown_5CC : number;
    m_unknown_5D0 : number;
    m_unknown_bool_5D1 : boolean;
    m_Team : TeamClass;
    m_NextTeamMember : FootClass;
    m_unknown_5DC : number;
    m_PathDirections : number;
    m_PathDelayTimer : CDTimerClass;
    m___PathDelayTimer : number;
    m_unknown_int_64C : number;
    m_unknown_timer_650 : CDTimerClass;
    m___unknown_timer_650 : number;
    m_SightTimer : CDTimerClass;
    m___SightTimer : number;
    m_BlockagePathTimer : CDTimerClass;
    m___BlockagePathTimer : number;
    m_Locomotor : any;
    m___Locomotor : number;
    m_unknown_point3d_678 : any;
    m_TubeIndex : number;
    m_unknown_bool_685 : boolean;
    m_WaypointIndex : number;
    m_unknown_bool_687 : boolean;
    m_unknown_bool_688 : boolean;
    m_IsInitiated : boolean;
    m_ShouldScanForTarget : boolean;
    m_unknown_bool_68B : boolean;
    m_IsDeploying : boolean;
    m_IsFiring : boolean;
    m_unknown_bool_68E : boolean;
    m_ShouldEnterAbsorber : boolean;
    m_ShouldEnterOccupiable : boolean;
    m_ShouldGarrisonStructure : boolean;
    m_ParasiteEatingMe : FootClass;
    m_unknown_698 : number;
    m_ParasiteImUsing : ParasiteClass;
    m_ParalysisTimer : CDTimerClass;
    m___ParalysisTimer : number;
    m_unknown_bool_6AC : boolean;
    m_IsAttackedByLocomotor : boolean;
    m_IsLetGoByLocomotor : boolean;
    m_unknown_bool_6AF : boolean;
    m_unknown_bool_6B0 : boolean;
    m_unknown_bool_6B1 : boolean;
    m_unknown_bool_6B2 : boolean;
    m_unknown_bool_6B3 : boolean;
    m_unknown_bool_6B4 : boolean;
    m_unknown_bool_6B5 : boolean;
    m_FrozenStill : boolean;
    m_unknown_bool_6B7 : boolean;
    m_unknown_bool_6B8 : boolean;
}
class TeamClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetTaskForceMissingMemberTypes(dest_0 : any) : void;
    LiberateMember(pFoot_0 : FootClass, idx_1 : number, count_2 : number) : void;
    AddMember(pFoot_0 : FootClass, bForce_1 : boolean) : boolean;
    AssignMissionTarget(pTarget_0 : AbstractClass) : void;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_Array : any;
    m_Type : TeamTypeClass;
    m_CurrentScript : ScriptClass;
    m_Owner : HouseClass;
    m_Target : HouseClass;
    m_SpawnCell : CellClass;
    m_ClosestMember : FootClass;
    m_QueuedFocus : AbstractClass;
    m_Focus : AbstractClass;
    m_unknown_44 : number;
    m_TotalObjects : number;
    m_TotalThreatValue : number;
    m_CreationFrame : number;
    m_FirstUnit : FootClass;
    m_GuardAreaTimer : CDTimerClass;
    m_SuspendTimer : CDTimerClass;
    m_Tag : TagClass;
    m_IsTransient : boolean;
    m_NeedsReGrouping : boolean;
    m_GuardSlowerIsNotUnderStrength : boolean;
    m_IsForcedActive : boolean;
    m_IsHasBeen : boolean;
    m_IsFullStrength : boolean;
    m_IsUnderStrength : boolean;
    m_IsReforming : boolean;
    m_IsLagging : boolean;
    m_NeedsToDisappear : boolean;
    m_JustDisappeared : boolean;
    m_IsMoving : boolean;
    m_StepCompleted : boolean;
    m_TargetNotAssigned : boolean;
    m_IsLeavingMap : boolean;
    m_IsSuspended : boolean;
    m_AchievedGreatSuccess : boolean;
    m_CountObjects : number;
}
class TeamTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : TeamTypeClass;
    static FindOrAllocate(pID_0 : string) : TeamTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    static LoadFromINIList(pINI_0 : CCINIClass, IsGlobal_1 : boolean) : boolean;
    CreateTeam(pHouse_0 : HouseClass) : TeamClass;
    DestroyAllInstances() : void;
    GetGroup() : number;
    GetWaypoint(buffer_0 : any) : any;
    GetTransportWaypoint(buffer_0 : any) : any;
    CanRecruitUnit(pUnit_0 : FootClass, pOwner_1 : HouseClass) : boolean;
    FlashAllInstances(Duration_0 : number) : void;
    FindFirstInstance() : TeamClass;
    ProcessTaskForce() : void;
    static ProcessAllTaskforces() : void;
    GetHouse() : HouseClass;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_Group : number;
    m_VeteranLevel : number;
    m_Loadable : boolean;
    m_Full : boolean;
    m_Annoyance : boolean;
    m_GuardSlower : boolean;
    m_Recruiter : boolean;
    m_Autocreate : boolean;
    m_Prebuild : boolean;
    m_Reinforce : boolean;
    m_Whiner : boolean;
    m_Aggressive : boolean;
    m_LooseRecruit : boolean;
    m_Suicide : boolean;
    m_Droppod : boolean;
    m_UseTransportOrigin : boolean;
    m_DropshipLoadout : boolean;
    m_OnTransOnly : boolean;
    m_Priority : number;
    m_Max : number;
    m_field_BC : number;
    m_MindControlDecision : number;
    m_Owner : HouseClass;
    m_idxHouse : number;
    m_TechLevel : number;
    m_Tag : TagClass;
    m_Waypoint : number;
    m_TransportWaypoint : number;
    m_cntInstances : number;
    m_ScriptType : ScriptTypeClass;
    m_TaskForce : TaskForceClass;
    m_IsGlobal : number;
    m_field_EC : number;
    m_field_F0 : boolean;
    m_field_F1 : boolean;
    m_AvoidThreats : boolean;
    m_IonImmune : boolean;
    m_TransportsReturnOnUnload : boolean;
    m_AreTeamMembersRecruitable : boolean;
    m_IsBaseDefense : boolean;
    m_OnlyTargetHouseEnemy : boolean;
}
class TagClass
    extends AbstractClass
{
    static GetInstance(pType_0 : TagTypeClass) : TagClass;
    static DeleteAll() : void;
    static NotifyGlobalChanged(idxGlobal_0 : number) : void;
    static NotifyLocalChanged(idxLocal_0 : number) : void;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    ComputeCRC(crc_0 : any) : void;
    HasCrossesHorizontalLineEvent() : boolean;
    HasCrossesVerticalLineEvent() : boolean;
    HasZoneEntryByEvent() : boolean;
    HasAllowWinAction() : boolean;
    GlobalChanged(idxGlobal_0 : number) : void;
    LocalChanged(idxLocal_0 : number) : void;
    IsOnlyInstanceOfType() : boolean;
    RaiseEvent(event_0 : any, pTagOwner_1 : ObjectClass, location_2 : any, forceAllOccured_3 : boolean, pSource_4 : TechnoClass) : boolean;
    ShouldReplace() : boolean;
    Destroy() : void;
    HasBeenDestroyed() : boolean;
    AddTrigger(pTrigger_0 : TriggerClass) : void;
    RemoveTrigger(pTrigger_0 : TriggerClass) : boolean;
    ContainsTrigger(pTrigger_0 : TriggerClass) : boolean;
    s_AbsID : any;
    s_Array : any;
    m_Type : TagTypeClass;
    m_FirstTrigger : TriggerClass;
    m_InstanceCount : number;
    m_DefaultCoords : any;
    m_Destroyed : boolean;
    m_IsExecuting : boolean;
}
class TagTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : TagTypeClass;
    static FindOrAllocate(pID_0 : string) : TagTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    ComputeCRC(crc_0 : any) : void;
    GetArrayIndex() : number;
    LoadFromINI(pINI_0 : CCINIClass) : boolean;
    SaveToINI(pINI_0 : CCINIClass) : boolean;
    static LoadFromINIList(pINI_0 : CCINIClass) : void;
    static SaveToINIList(pINI_0 : CCINIClass) : void;
    static FindByNameOrID(pName_0 : string) : TagTypeClass;
    GetFlags() : any;
    HasAllowWinAction() : boolean;
    HasCrossesHorizontalLineEvent() : boolean;
    HasCrossesVerticalLineEvent() : boolean;
    HasZoneEntryByEvent() : boolean;
    AddTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    RemoveTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    ContainsTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_Persistence : any;
    m_FirstTrigger : TriggerTypeClass;
}
class TriggerTypeClass
{
}
class TriggerClass
    extends AbstractClass
{
    static GetInstance(pType_0 : TriggerTypeClass) : TriggerClass;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    ComputeCRC(crc_0 : any) : void;
    HasCrossesHorizontalLineEvent() : boolean;
    HasCrossesVerticalLineEvent() : boolean;
    HasZoneEntryByEvent() : boolean;
    HasAllowWinAction() : boolean;
    HasGlobalSetOrClearedEvent(idxGlobal_0 : number) : boolean;
    NotifyGlobalChanged(idxGlobal_0 : number) : void;
    NotifyLocalChanged(idxLocal_0 : number) : void;
    ResetTimers() : void;
    MarkEventAsOccured(idx_0 : number) : void;
    MarkEventAsNotOccured(idx_0 : number) : void;
    HasEventOccured(idx_0 : number) : boolean;
    Destroy() : void;
    HasBeenDestroyed() : boolean;
    SetHouse(pHouse_0 : HouseClass) : void;
    GetHouse() : HouseClass;
    Enable() : void;
    Disable() : void;
    RegisterEvent(event_0 : any, pObject_1 : ObjectClass, forceFire_2 : boolean, persistent_3 : boolean, pSource_4 : TechnoClass) : boolean;
    FireActions(pObj_0 : ObjectClass, location_1 : any) : boolean;
    s_AbsID : any;
    s_Array : any;
    m_Type : TriggerTypeClass;
    m_NextTrigger : TriggerClass;
    m_House : HouseClass;
    m_Destroyed : boolean;
    m_Timer : CDTimerClass;
    m_OccuredEvents : number;
    m_Enabled : boolean;
}
class ScriptTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : ScriptTypeClass;
    static FindOrAllocate(pID_0 : string) : ScriptTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    static LoadFromINIList(pINI_0 : CCINIClass, IsGlobal_1 : boolean) : boolean;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_IsGlobal : boolean;
    m_ActionsCount : number;
    m_ScriptActions : ScriptActionNode;
}
class ScriptActionNode
{
    m_Action : number;
    m_Argument : number;
}
class TaskForceClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : TaskForceClass;
    static FindOrAllocate(pID_0 : string) : TaskForceClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_Array : any;
    m_Group : number;
    m_CountEntries : number;
    m_IsGlobal : boolean;
    m_Entries : TaskForceEntryStruct;
}
class TaskForceEntryStruct
{
    m_Amount : number;
    m_Type : TechnoTypeClass;
}
class ScriptClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    GetCurrentAction(buffer_0 : ScriptActionNode) : ScriptActionNode;
    GetNextAction(buffer_0 : ScriptActionNode) : ScriptActionNode;
    ClearMission() : boolean;
    SetMission(nLine_0 : number) : boolean;
    NextMission() : boolean;
    HasNextMission() : boolean;
    s_AbsID : any;
    m_Type : ScriptTypeClass;
    m_field_28 : number;
    m_CurrentMission : number;
}
class ParasiteClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    UpdateSquid() : void;
    UpdateGrapple() : boolean;
    ExitUnit() : void;
    CanInfect(pTarget_0 : FootClass) : boolean;
    TryInfect(pTarget_0 : FootClass) : void;
    CanExistOnVictimCell() : boolean;
    s_AbsID : any;
    s_Array : any;
    m_Owner : FootClass;
    m_Victim : FootClass;
    m_SuppressionTimer : CDTimerClass;
    m_DamageDeliveryTimer : CDTimerClass;
    m_GrappleAnim : AnimClass;
    m_GrappleState : any;
    m_GrappleAnimFrame : number;
    m_GrappleAnimDelay : number;
    m_GrappleAnimGotInvalid : boolean;
}
class BuildingLightClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SetBehaviour(mode_0 : any) : void;
    s_AbsID : any;
    s_Array : any;
    m_Speed : number;
    m_field_B8 : any;
    m_field_C4 : any;
    m_Acceleration : number;
    m_Direction : boolean;
    m_BehaviourMode : any;
    m_FollowingObject : ObjectClass;
    m_OwnerObject : TechnoClass;
}
class LightSourceClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    Activate(dwZero_0 : number) : void;
    Deactivate(dwZero_0 : number) : void;
    ChangeLevels(nIntensity_0 : number, Tint_1 : TintStruct, mode_2 : number) : void;
    static UpdateLightConverts(value_0 : number) : void;
    s_AbsID : any;
    m_LightIntensity : number;
    m_LightTint : TintStruct;
    m_DetailLevel : number;
    m_Location : any;
    m_LightVisibility : number;
    m_Activated : boolean;
}
class UnitClass
    extends FootClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    MouseOverCell(pCell_0 : any, checkFog_1 : boolean, ignoreForce_2 : boolean) : any;
    MouseOverObject(pObject_0 : ObjectClass, ignoreForce_1 : boolean) : any;
    MarkAllOccupationBits(coords_0 : any) : void;
    UnmarkAllOccupationBits(coords_0 : any) : void;
    DrawAsVXL(Coords_0 : any, BoundingRect_1 : any, Brightness_2 : number, Tint_3 : number) : void;
    DrawAsSHP(Coords_0 : any, BoundingRect_1 : any, Brightness_2 : number, Tint_3 : number) : void;
    DrawObject(pSurface_0 : any, Coords_1 : any, CacheRect_2 : any, Brightness_3 : number, Tint_4 : number) : void;
    IsDeactivated() : boolean;
    UpdateTube() : void;
    UpdateRotation() : void;
    UpdateEdgeOfWorld() : void;
    UpdateFiring() : void;
    UpdateVisceroid() : void;
    UpdateDisguise() : void;
    Explode() : void;
    GotoClearSpot() : boolean;
    TryToDeploy() : boolean;
    Deploy() : void;
    Undeploy() : void;
    Harvesting() : boolean;
    FlagAttach(nHouseIdx_0 : number) : boolean;
    FlagRemove() : boolean;
    APCCloseDoor() : void;
    APCOpenDoor() : void;
    static ReadINI(pINI_0 : CCINIClass) : void;
    static WriteINI(pINI_0 : CCINIClass) : void;
    ShouldCrashIt(pTarget_0 : TechnoClass) : boolean;
    AssignDestination_7447B0(pTarget_0 : AbstractClass) : AbstractClass;
    AStarAttempt(cell1_0 : any, cell2_1 : any) : boolean;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_unknown_int_6C0 : number;
    m_Type : UnitTypeClass;
    m_FollowerCar : UnitClass;
    m_FlagHouseIndex : number;
    m_HasFollowerCar : boolean;
    m_Unloading : boolean;
    m_IsHarvesting : boolean;
    m_TerrainPalette : boolean;
    m_unknown_int_6D4 : number;
    m_DeathFrameCounter : number;
    m_ElectricBolt : EBolt;
    m_Deployed : boolean;
    m_Deploying : boolean;
    m_Undeploying : boolean;
    m_NonPassengerCount : number;
    m_ToolTipText : any;
}
class EBolt
{
    SetOwner(pOwner_0 : UnitClass, idxWeapon_1 : number) : void;
    ClearOwner() : void;
    GetSourceCoords(outBuffer_0 : any) : any;
    GetSourceCoords() : any;
    Fire(P1_0 : any, P2_1 : any, arg18_2 : number) : void;
    s_Array : any;
    m_Point1 : any;
    m_Point2 : any;
    m_unknown_18 : number;
    m_Random : number;
    m_Owner : TechnoClass;
    m_WeaponSlot : number;
    m_Lifetime : number;
    m_AlternateColor : boolean;
}
class AircraftClass
    extends FootClass
{
    Landing_Altitude() : number;
    Landing_Direction() : number;
    Is_Loaded() : number;
    Is_Strafe() : number;
    Is_Fighter() : number;
    Is_Locked() : number;
    QueryInterface(iid_0 : any, ppvObject_1 : void) : number;
    AddRef() : number;
    Release() : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_Type : AircraftTypeClass;
    m_unknown_bool_6C8 : boolean;
    m_HasPassengers : boolean;
    m_IsKamikaze : boolean;
    m_DockNowHeadingTo : BuildingClass;
    m_unknown_bool_6D0 : boolean;
    m_unknown_bool_6D1 : boolean;
    m_unknown_bool_6D2 : boolean;
    m_unknown_char_6D3 : number;
    m_unknown_bool_6D4 : boolean;
    m_unknown_bool_6D5 : boolean;
}
class AircraftTypeClass
    extends TechnoTypeClass
{
    static Find(pID_0 : string) : AircraftTypeClass;
    static FindOrAllocate(pID_0 : string) : AircraftTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_ArrayIndex : number;
    m_Carryall : boolean;
    m_Trailer : AnimTypeClass;
    m_SpawnDelay : number;
    m_Rotors : boolean;
    m_CustomRotor : boolean;
    m_Landable : boolean;
    m_FlyBy : boolean;
    m_FlyBack : boolean;
    m_AirportBound : boolean;
    m_Fighter : boolean;
}
class TerrainClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_Array : any;
    m_Animation : StageClass;
    m_Type : TerrainTypeClass;
    m_IsBurning : boolean;
    m_IsCrumbling : boolean;
    m_unknown_rect_D0 : any;
}
class TerrainTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : TerrainTypeClass;
    static FindOrAllocate(pID_0 : string) : TerrainTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_Foundation : number;
    m_RadarColor : any;
    m_AnimationRate : number;
    m_AnimationProbability : number;
    m_TemperateOccupationBits : number;
    m_SnowOccupationBits : number;
    m_WaterBound : boolean;
    m_SpawnsTiberium : boolean;
    m_IsFlammable : boolean;
    m_IsAnimated : boolean;
    m_IsVeinhole : boolean;
    m_FoundationData : any;
}
class TiberiumClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : TiberiumClass;
    static FindOrAllocate(pID_0 : string) : TiberiumClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetSizeMax(pcbSize_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    RegisterForGrowth(cell_0 : any) : void;
    static FindIndex(idxOverlayType_0 : number) : number;
    static Find(idxOverlayType_0 : number) : TiberiumClass;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_Spread : number;
    m_SpreadPercentage : number;
    m_Growth : number;
    m_GrowthPercentage : number;
    m_Value : number;
    m_Power : number;
    m_Color : number;
    m_Debris : any;
    m___Debris : number;
    m_Image : OverlayTypeClass;
    m_NumFrames : number;
    m_NumImages : number;
    m_field_EC : number;
    m_SpreadLogic : TiberiumLogic;
    m___SpreadLogic : number;
    m_GrowthLogic : TiberiumLogic;
    m___GrowthLogic : number;
}
class TiberiumLogic
{
    Construct(nCount_0 : number) : void;
    Destruct() : void;
    m_Count : number;
    m_Queue : any;
    m_CellIndexesWithTiberium : boolean;
    m_Nodes : any;
    m_Timer : CDTimerClass;
}
class RadSiteClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    Activate() : void;
    Deactivate() : void;
    Radiate() : void;
    DecreaseRadiation() : void;
    DecreaseLight() : void;
    Add(nRadLevel_0 : number) : void;
    GetRadLevel() : number;
    GetRadLevelAt(pCell_0 : any) : number;
    SetRadLevel(nRadLevel_0 : number) : void;
    SetBaseCell(pCell_0 : any) : void;
    GetSpread() : void;
    SetSpread(nCells_0 : number) : void;
    GetEffectPercentage() : number;
    s_AbsID : any;
    s_Array : any;
    m_LightSource : LightSourceClass;
    m_RadLevelTimer : CDTimerClass;
    m___RadLevelTimer : number;
    m_RadLightTimer : CDTimerClass;
    m___RadLightTimer : number;
    m_BaseCell : any;
    m_Spread : number;
    m_SpreadInLeptons : number;
    m_RadLevel : number;
    m_LevelSteps : number;
    m_Intensity : number;
    m_Tint : TintStruct;
    m_IntensitySteps : number;
    m_IntensityDecrement : number;
    m_RadDuration : number;
    m_RadTimeLeft : number;
}
class RGBClass
{
    Adjust(ratio_0 : number, rgb_1 : RGBClass) : void;
    Difference(rgb_0 : RGBClass) : number;
    ToInt() : number;
    s_White : any;
    s_RedShiftLeft : any;
    s_RedShiftRight : any;
    s_GreenShiftLeft : any;
    s_GreenShiftRight : any;
    s_BlueShiftLeft : any;
    s_BlueShiftRight : any;
    m_Red : number;
    m_Green : number;
    m_Blue : number;
}
class LaserDrawClass
{
    m_Progress : StageClass;
    m___Progress : number;
    m_Thickness : number;
    m_IsHouseColor : boolean;
    m_IsSupported : boolean;
    m_Source : any;
    m_Target : any;
    m_ZAdjust : number;
    m_field_40 : number;
    m_InnerColor : any;
    m_OuterColor : any;
    m_OuterSpread : any;
    m_Duration : number;
    m_Blinks : boolean;
    m_BlinkState : boolean;
    m_Fades : boolean;
    m_StartIntensity : number;
    m_EndIntensity : number;
}
class FlashData
{
    Update() : boolean;
    m_DurationRemaining : number;
    m_FlashingNow : boolean;
}
class PassengersClass
{
    AddPassenger(pPassenger_0 : FootClass) : void;
    GetFirstPassenger() : FootClass;
    RemoveFirstPassenger() : FootClass;
    GetTotalSize() : number;
    IndexOf(candidate_0 : FootClass) : number;
    m_NumPassengers : number;
    m_FirstPassenger : FootClass;
}
class VeterancyStruct
{
    Add(ownerCost_0 : number, victimCost_1 : number) : void;
    Add(value_0 : number) : void;
    GetRemainingLevel() : any;
    IsNegative() : boolean;
    IsRookie() : boolean;
    IsVeteran() : boolean;
    IsElite() : boolean;
    Reset() : void;
    SetRookie(notReally_0 : boolean) : void;
    SetVeteran(yesReally_0 : boolean) : void;
    SetElite(yesReally_0 : boolean) : void;
    m_Veterancy : number;
}
class TemporalClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    Fire(pTarget_0 : TechnoClass) : void;
    CanWarpTarget(pTarget_0 : TechnoClass) : boolean;
    GetWarpPerStep(nHelperCount_0 : number) : number;
    LetGo() : void;
    JustLetGo() : void;
    Detach() : void;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    m_Owner : TechnoClass;
    m_Target : TechnoClass;
    m_LifeTimer : CDTimerClass;
    m_unknown_pointer_38 : void;
    m_SourceSW : SuperClass;
    m_NextTemporal : TemporalClass;
    m_PrevTemporal : TemporalClass;
    m_WarpRemaining : number;
    m_WarpPerStep : number;
}
class SuperClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    CreateChronoAnim(coords_0 : any) : void;
    Reset() : void;
    SetOnHold(onHold_0 : boolean) : boolean;
    Grant(oneTime_0 : boolean, announce_1 : boolean, onHold_2 : boolean) : boolean;
    Lose() : boolean;
    IsPowered() : boolean;
    Launch(cell_0 : any, isPlayer_1 : boolean) : void;
    CanFire() : number;
    SetReadiness(ready_0 : boolean) : void;
    StopPreclickAnim(isPlayer_0 : boolean) : number;
    ClickFire(isPlayer_0 : boolean, cell_1 : any) : number;
    HasChargeProgressed(isPlayer_0 : boolean) : boolean;
    AnimStage() : number;
    SetCharge(percentage_0 : number) : void;
    GetRechargeTime() : number;
    SetRechargeTime(time_0 : number) : void;
    ResetRechargeTime() : void;
    NameReadiness() : any;
    ShouldDrawProgress() : boolean;
    ShouldFlashTab() : boolean;
    s_AbsID : any;
    s_AbsVTable : number;
    s_Array : any;
    s_ShowTimers : any;
    m_CustomChargeTime : number;
    m_Type : SuperWeaponTypeClass;
    m_Owner : HouseClass;
    m_RechargeTimer : CDTimerClass;
    m_BlinkState : boolean;
    m_BlinkTimer : any;
    m_SpecialSoundDuration : number;
    m_SpecialSoundLocation : any;
    m_CanHold : boolean;
    m_ChronoMapCoords : any;
    m_Animation : AnimClass;
    m_AnimationGotInvalid : boolean;
    m_IsPresent : boolean;
    m_IsOneTime : boolean;
    m_IsReady : boolean;
    m_IsSuspended : boolean;
    m_ReadyFrame : number;
    m_CameoChargeState : number;
    m_ChargeDrainState : any;
}
class SuperWeaponTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : SuperWeaponTypeClass;
    static FindOrAllocate(pID_0 : string) : SuperWeaponTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    MouseOverObject(cell_0 : any, pObjBelowMouse_1 : ObjectClass) : any;
    static FindFirstOfAction(Action_0 : any) : SuperWeaponTypeClass;
    s_AbsID : any;
    s_Array : any;
    m_ArrayIndex : number;
    m_WeaponType : WeaponTypeClass;
    m_RechargeVoice : number;
    m_ChargingVoice : number;
    m_ImpatientVoice : number;
    m_SuspendVoice : number;
    m_RechargeTime : number;
    m_Type : any;
    m_SidebarImage : any;
    m_Action : any;
    m_SpecialSound : number;
    m_StartSound : number;
    m_AuxBuilding : BuildingTypeClass;
    m_SidebarImageFile : number;
    m_UseChargeDrain : boolean;
    m_IsPowered : boolean;
    m_DisableableFromShell : boolean;
    m_FlashSidebarTabFrames : number;
    m_AIDefendAgainst : boolean;
    m_PreClick : boolean;
    m_PostClick : boolean;
    m_PreDependent : number;
    m_ShowTimer : boolean;
    m_ManualControl : boolean;
    m_Range : number;
    m_LineMultiplier : number;
}
class AirstrikeClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    StartMission(pTarget_0 : ObjectClass) : void;
    s_AbsID : any;
    m_AirstrikeTeam : number;
    m_EliteAirstrikeTeam : number;
    m_AirstrikeTeamTypeIndex : number;
    m_EliteAirstrikeTeamTypeIndex : number;
    m_unknown_34 : number;
    m_unknown_38 : number;
    m_IsOnMission : boolean;
    m_unknown_bool_3D : boolean;
    m_TeamDissolveFrame : number;
    m_AirstrikeRechargeTime : number;
    m_EliteAirstrikeRechargeTime : number;
    m_Owner : TechnoClass;
    m_Target : ObjectClass;
    m_AirstrikeTeamType : AircraftTypeClass;
    m_EliteAirstrikeTeamType : AircraftTypeClass;
    m_FirstObject : FootClass;
}
class CaptureManagerClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    CaptureUnit(pUnit_0 : TechnoClass) : boolean;
    FreeUnit(pUnit_0 : TechnoClass) : boolean;
    FreeAll() : void;
    NumControlNodes() : number;
    CanCapture(Target_0 : TechnoClass) : boolean;
    CannotControlAnyMore() : boolean;
    IsControllingSomething() : boolean;
    IsOverloading(wasDamageApplied_0 : boolean) : boolean;
    HandleOverload() : void;
    NeedsToDrawLinks() : boolean;
    DrawLinks() : boolean;
    DecideUnitFate(Unit_0 : TechnoClass) : void;
    GetOriginalOwner(Unit_0 : TechnoClass) : HouseClass;
    s_AbsID : any;
    s_Array : any;
    m_ControlNodes : any;
    m_MaxControlNodes : number;
    m_InfiniteMindControl : boolean;
    m_OverloadDeathSoundPlayed : boolean;
    m_OverloadPipState : number;
    m_Owner : TechnoClass;
    m_OverloadDamageDelay : number;
}
class ControlNode
{
    m_Unit : TechnoClass;
    m_OriginalOwner : HouseClass;
    m_LinkDrawTimer : CDTimerClass;
    m___LinkDrawTimer : number;
}
class SpawnManagerClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    KillNodes() : void;
    SetTarget(pTarget_0 : AbstractClass) : void;
    UpdateTarget() : boolean;
    ResetTarget() : void;
    CountAliveSpawns() : number;
    CountDockedSpawns() : number;
    CountLaunchingSpawns() : number;
    UnlinkPointer() : void;
    s_AbsID : any;
    s_Array : any;
    m_Owner : TechnoClass;
    m_SpawnType : AircraftTypeClass;
    m_SpawnCount : number;
    m_RegenRate : number;
    m_ReloadRate : number;
    m_SpawnedNodes : any;
    m_UpdateTimer : CDTimerClass;
    m_SpawnTimer : CDTimerClass;
    m_Target : AbstractClass;
    m_NewTarget : AbstractClass;
    m_Status : any;
}
class SpawnControl
{
    m_Unit : AircraftClass;
    m_Status : any;
    m_SpawnTimer : CDTimerClass;
    m_IsSpawnMissile : number;
}
class SlaveManagerClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SetOwner(NewOwner_0 : TechnoClass) : void;
    CreateSlave(Node_0 : any) : void;
    LostSlave(Slave_0 : InfantryClass) : void;
    Deploy2() : void;
    Killed(Killer_0 : TechnoClass, ForcedOwnerHouse_1 : HouseClass) : void;
    ShouldWakeUpNow() : boolean;
    ZeroOutSlaves() : void;
    SuspendWork() : void;
    ResumeWork() : void;
    s_AbsID : any;
    s_Array : any;
    m_Owner : TechnoClass;
    m_SlaveType : InfantryTypeClass;
    m_SlaveCount : number;
    m_RegenRate : number;
    m_ReloadRate : number;
    m_SlaveNodes : any;
    m_RespawnTimer : CDTimerClass;
    m_State : any;
    m_LastScanFrame : number;
}
class ParticleSystemClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_Array : any;
    m_Type : ParticleSystemTypeClass;
    m_SpawnDistanceToOwner : any;
    m_Particles : any;
    m___Particles : number;
    m_TargetCoords : any;
    m_Owner : ObjectClass;
    m_Target : AbstractClass;
    m_SpawnFrames : number;
    m_Lifetime : number;
    m_SparkSpawnFrames : number;
    m_SpotlightRadius : number;
    m_TimeToDie : boolean;
    m_unknown_bool_F9 : boolean;
    m_OwnerHouse : HouseClass;
}
class ParticleSystemTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : ParticleSystemTypeClass;
    static FindOrAllocate(pID_0 : string) : ParticleSystemTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(mcoords_0 : any, owner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_Array : any;
    m_HoldsWhat : number;
    m_Spawns : boolean;
    m_SpawnFrames : number;
    m_Slowdown : number;
    m_ParticleCap : number;
    m_SpawnRadius : number;
    m_SpawnCutoff : number;
    m_SpawnTranslucencyCutoff : number;
    m_BehavesLike : any;
    m_Lifetime : number;
    m_SpawnDirection : any;
    m_ParticlesPerCoord : number;
    m_SpiralDeltaPerCoord : number;
    m_SpiralRadius : number;
    m_PositionPerturbationCoefficient : number;
    m_MovementPerturbationCoefficient : number;
    m_VelocityPerturbationCoefficient : number;
    m_SpawnSparkPercentage : number;
    m_SparkSpawnFrames : number;
    m_LightSize : number;
    m_LaserColor : any;
    m_Laser : boolean;
    m_OneFrameLight : boolean;
}
class ParticleClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    vt_entry_1E8() : number;
    s_AbsID : any;
    s_Array : any;
    m_Type : ParticleTypeClass;
    m_unknown_B0 : number;
    m_unknown_B1 : number;
    m_unknown_B2 : number;
    m_unknown_B4 : number;
    m_unknown_B8 : number;
    m_unknown_BC : number;
    m_Velocity : any;
    m_unknown_CC : number;
    m_unknown_double_D0 : number;
    m_unknown_D8 : number;
    m_unknown_DC : number;
    m_unknown_E0 : number;
    m_Speed : number;
    m_unknown_coords_E8 : any;
    m_unknown_coords_F4 : any;
    m_unknown_coords_100 : any;
    m_unknown_vector3d_10C : any;
    m_unknown_vector3d_118 : any;
    m_ParticleSystem : ParticleSystemClass;
    m_RemainingEC : number;
    m_RemainingDC : number;
    m_StateAIAdvance : number;
    m_unknown_12D : number;
    m_StartStateAI : number;
    m_Translucency : number;
    m_unknown_130 : number;
    m_unknown_131 : number;
}
class ParticleTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : ParticleTypeClass;
    static FindOrAllocate(pID_0 : string) : ParticleTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(mcoords_0 : any, owner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_Array : any;
    m_NextParticleOffset : any;
    m_XVelocity : number;
    m_YVelocity : number;
    m_MinZVelocity : number;
    m_ZVelocityRange : number;
    m_ColorSpeed : number;
    m_ColorList : any;
    m_StartColor1 : any;
    m_StartColor2 : any;
    m_MaxDC : number;
    m_MaxEC : number;
    m_Warhead : WarheadTypeClass;
    m_Damage : number;
    m_StartFrame : number;
    m_NumLoopFrames : number;
    m_Translucency : number;
    m_WindEffect : number;
    m_Velocity : number;
    m_Deacc : number;
    m_Radius : number;
    m_DeleteOnStateLimit : boolean;
    m_EndStateAI : number;
    m_StartStateAI : number;
    m_StateAIAdvance : number;
    m_FinalDamageState : number;
    m_Translucent25State : number;
    m_Translucent50State : number;
    m_Normalized : boolean;
    m_NextParticle : ParticleTypeClass;
    m_BehavesLike : any;
}
class WarheadTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : WarheadTypeClass;
    static FindOrAllocate(pID_0 : string) : WarheadTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    s_AbsID : any;
    s_Array : any;
    m_Deform : number;
    m_Verses : number;
    m_ProneDamage : number;
    m_DeformTreshold : number;
    m_AnimList : any;
    m_InfDeath : any;
    m_CellSpread : number;
    m_CellInset : number;
    m_PercentAtMax : number;
    m_CausesDelayKill : boolean;
    m_DelayKillFrames : number;
    m_DelayKillAtMax : number;
    m_CombatLightSize : number;
    m_Particle : ParticleTypeClass;
    m_Wall : boolean;
    m_WallAbsoluteDestroyer : boolean;
    m_PenetratesBunker : boolean;
    m_Wood : boolean;
    m_Tiberium : boolean;
    m_unknown_bool_149 : boolean;
    m_Sparky : boolean;
    m_Sonic : boolean;
    m_Fire : boolean;
    m_Conventional : boolean;
    m_Rocker : boolean;
    m_DirectRocker : boolean;
    m_Bright : boolean;
    m_CLDisableRed : boolean;
    m_CLDisableGreen : boolean;
    m_CLDisableBlue : boolean;
    m_EMEffect : boolean;
    m_MindControl : boolean;
    m_Poison : boolean;
    m_IvanBomb : boolean;
    m_ElectricAssault : boolean;
    m_Parasite : boolean;
    m_Temporal : boolean;
    m_IsLocomotor : boolean;
    m_Locomotor : any;
    m_Airstrike : boolean;
    m_Psychedelic : boolean;
    m_BombDisarm : boolean;
    m_Paralyzes : number;
    m_Culling : boolean;
    m_MakesDisguise : boolean;
    m_NukeMaker : boolean;
    m_Radiation : boolean;
    m_PsychicDamage : boolean;
    m_AffectsAllies : boolean;
    m_Bullets : boolean;
    m_Veinhole : boolean;
    m_ShakeXlo : number;
    m_ShakeXhi : number;
    m_ShakeYlo : number;
    m_ShakeYhi : number;
    m_DebrisTypes : any;
    m_DebrisMaximums : any;
    m_MaxDebris : number;
    m_MinDebris : number;
}
class VoxelAnimTypeClass
    extends ObjectTypeClass
{
    static Find(pID_0 : string) : VoxelAnimTypeClass;
    static FindOrAllocate(pID_0 : string) : VoxelAnimTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    s_AbsID : any;
    s_Array : any;
    m_Normalized : boolean;
    m_Translucent : boolean;
    m_SourceShared : boolean;
    m_VoxelIndex : number;
    m_Duration : number;
    m_Elasticity : number;
    m_MinAngularVelocity : number;
    m_MaxAngularVelocity : number;
    m_MinZVel : number;
    m_MaxZVel : number;
    m_MaxXYVel : number;
    m_IsMeteor : boolean;
    m_Spawns : VoxelAnimTypeClass;
    m_SpawnCount : number;
    m_StartSound : number;
    m_StopSound : number;
    m_BounceAnim : AnimTypeClass;
    m_ExpireAnim : AnimTypeClass;
    m_TrailerAnim : AnimTypeClass;
    m_Damage : number;
    m_DamageRadius : number;
    m_Warhead : WarheadTypeClass;
    m_AttachedSystem : ParticleSystemTypeClass;
    m_IsTiberium : boolean;
}
class WaveClass
    extends ObjectClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    Draw_Magnetic(xyzFrom_0 : any, xyzTo_1 : any) : void;
    Draw_NonMagnetic(xyzFrom_0 : any, xyzTo_1 : any) : void;
    Update_Wave() : void;
    DamageArea(location_0 : any) : void;
    s_AbsID : any;
    s_Array : any;
    m_Target : TechnoClass;
    m_Type : any;
    m_someCoords : any;
    m_field_BC : number;
    m_field_C0 : number;
    m_field_C4 : number;
    m_field_C8 : number;
    m_field_CC : number;
    m_field_D0 : number;
    m_field_D4 : number;
    m_field_D8 : number;
    m_field_DC : number;
    m_field_E0 : number;
    m_field_E4 : number;
    m_field_E8 : number;
    m_field_EC : number;
    m_field_F0 : number;
    m_field_F4 : number;
    m_field_F8 : number;
    m_field_FC : number;
    m_field_100 : number;
    m_field_104 : number;
    m_field_108 : number;
    m_field_10C : number;
    m_field_110 : number;
    m_field_114 : number;
    m_field_118 : number;
    m_field_11C : number;
    m_field_120 : number;
    m_field_124 : number;
    m_field_128 : number;
    m_field_12C : number;
    m_field_12D : number;
    m_field_12E : number;
    m_field_12F : number;
    m_WaveIntensity : number;
    m_field_134 : number;
    m_field_138 : number;
    m_field_13C : number;
    m_field_140 : number;
    m_field_144 : number;
    m_field_148 : number;
    m_field_14C : number;
    m_field_150 : number;
    m_field_154 : number;
    m_field_158 : number;
    m_field_15C : number;
    m_field_160 : number;
    m_field_164 : number;
    m_field_168 : number;
    m_field_16C : number;
    m_field_170 : number;
    m_field_174 : number;
    m_field_178 : number;
    m_field_17C : number;
    m_field_180 : number;
    m_field_184 : number;
    m_field_188 : number;
    m_field_18C : number;
    m_field_190 : number;
    m_field_194 : number;
    m_field_198 : number;
    m_field_19C : number;
    m_field_1A0 : number;
    m_field_1A4 : number;
    m_field_1A8 : number;
    m_field_1AC : number;
    m_field_1B0 : number;
    m_field_1B4 : number;
    m_field_1B8 : number;
    m_field_1BC : number;
    m_field_1C0 : number;
    m_field_1C4 : number;
    m_field_1C8 : number;
    m_field_1CC : number;
    m_LaserIntensity : number;
    m_Owner : TechnoClass;
    m_Facing : FacingClass;
    m_Cells : any;
    m_unknown_208 : number;
}
class TransitionTimer
{
    AreStates11() : boolean;
    AreStates10() : boolean;
    AreStates01() : boolean;
    AreStates00() : boolean;
    IsTimerFinished() : boolean;
    StartTimer11(time_0 : number) : void;
    StartTimer10(time_0 : number) : void;
    Update() : void;
    PercentageDone() : number;
    SetToDone() : void;
    m_Rate1 : number;
    m_ActionTimer : CDTimerClass;
    m_Rate2 : number;
    m_State1 : boolean;
    m_State2 : boolean;
}
class RecoilData
{
    Update() : void;
    Fire() : void;
    m_Turret : TurretControl;
    m_TravelPerFrame : number;
    m_TravelSoFar : number;
    m_State : any;
    m_TravelFramesLeft : number;
}
class TurretControl
{
    m_Travel : number;
    m_CompressFrames : number;
    m_RecoverFrames : number;
    m_HoldFrames : number;
}
class RadBeam
{
    static Allocate(mode_0 : any) : RadBeam;
    SetColor(color_0 : any) : void;
    SetCoordsSource(loc_0 : any) : void;
    SetCoordsTarget(loc_0 : any) : void;
    s_Array : any;
    m_unknown_0 : number;
    m_Owner : TechnoClass;
    m_unknown_8 : number;
    m_unknown_C : number;
    m_Type : any;
    m_unknown_14 : number;
    m_unknown_18 : number;
    m_Color : any;
    m_SourceLocation : any;
    m_TargetLocation : any;
    m_Period : number;
    m_Amplitude : number;
    m_unknown_48 : number;
    m_unknown_50 : number;
    m_unknown_54 : number;
    m_unknown_58 : number;
    m_unknown_5C : number;
    m_unknown_60 : number;
    m_unknown_64 : number;
    m_unknown_68 : number;
    m_AnotherLocation : any;
    m_unknown_7C : number;
    m_unknown_80 : number;
    m_unknown_88 : number;
    m_unknown_8C : number;
    m_AndAnotherLocation : any;
    m_unknown_9C : number;
    m_unknown_A0 : number;
    m_unknown_A4 : number;
    m_unknown_A8 : number;
    m_unknown_AC : number;
    m_unknown_B0 : number;
    m_unknown_B4 : number;
    m_unknown_B8 : number;
    m_unknown_C0 : number;
    m_unknown_C4 : number;
}
class PlanningTokenClass
{
    s_Array : any;
    m_OwnerUnit : TechnoClass;
    m_PlanningNodes : any;
    m_field_1C : boolean;
    m_field_1D : boolean;
    m_unknown_20_88 : number;
    m___unknown_20_88 : number;
    m_field_8C : number;
    m_ClosedLoopNodeCount : number;
    m_StepsToClosedLoop : number;
    m_field_98 : boolean;
    m_field_99 : boolean;
}
class PlanningNodeClass
{
    s_Unknown1 : any;
    s_Unknown2 : any;
    s_Unknown3 : any;
    s_PlanningModeActive : any;
    m_PlanningMembers : any;
    m_field_18 : number;
    m_field_1C : boolean;
    m_PlanningBranches : any;
}
class PlanningMemberClass
{
    m_Owner : TechnoClass;
    m_Packet : number;
    m_field_8 : number;
    m_field_C : number;
}
class PlanningBranchClass
{
}
class BulletData
{
    m_UnknownTimer : CDTimerClass;
    m_ArmTimer : CDTimerClass;
    m_Location : any;
    m_Distance : number;
}
class AbilitiesStruct
{
    m_FASTER : boolean;
    m_STRONGER : boolean;
    m_FIREPOWER : boolean;
    m_SCATTER : boolean;
    m_ROF : boolean;
    m_SIGHT : boolean;
    m_CLOAK : boolean;
    m_TIBERIUM_PROOF : boolean;
    m_VEIN_PROOF : boolean;
    m_SELF_HEAL : boolean;
    m_EXPLODES : boolean;
    m_RADAR_INVISIBLE : boolean;
    m_SENSORS : boolean;
    m_FEARLESS : boolean;
    m_C4 : boolean;
    m_TIBERIUM_HEAL : boolean;
    m_GUARD_AREA : boolean;
    m_CRUSHER : boolean;
}
class BounceClass
{
    Initialize(coords_0 : any, elasticity_1 : number, gravity_2 : number, maxVelocity_3 : number, velocity_4 : any, angularVelocity_5 : number) : void;
    GetCoords(pBuffer_0 : any) : any;
    GetCoords() : any;
    GetDrawingMatrix(pBuffer_0 : any) : any;
    GetDrawingMatrix() : any;
    Update() : any;
    m_Elasticity : number;
    m_Gravity : number;
    m_MaxVelocity : number;
    m_Coords : any;
    m_Velocity : any;
    m_CurrentAngle : any;
    m_AngularVelocity : any;
}
class BombClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    Detonate() : void;
    Disarm() : void;
    IsDeathBomb() : number;
    GetCurrentFlickerFrame() : number;
    TimeToExplode() : boolean;
    s_AbsID : any;
    m_Owner : TechnoClass;
    m_OwnerHouse : HouseClass;
    m_Target : ObjectClass;
    m_DeathBomb : number;
    m_PlantingFrame : number;
    m_DetonationFrame : number;
    m_Audio : any;
    m_TickSound : number;
    m_ShouldPlayTickingSound : number;
    m_Harmless : boolean;
}
class LineTrail
{
    SetDecrement(val_0 : number) : void;
    static DeleteAll() : void;
    s_Array : any;
    m_Color : any;
    m_Owner : ObjectClass;
    m_Decrement : number;
    m_ActiveSlot : number;
    m_Trails : LineTrailNode;
}
class LineTrailNode
{
    m_Position : any;
    m_Value : number;
}
class WaypointClass
{
    m_Coords : any;
    m_unknown : number;
}
class HouseTypeClass
    extends AbstractTypeClass
{
    static Find(pID_0 : string) : HouseTypeClass;
    static FindOrAllocate(pID_0 : string) : HouseTypeClass;
    static FindIndex(pID_0 : string) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    FindParentCountry() : HouseTypeClass;
    FindParentCountryIndex() : number;
    static FindIndexOfName(name_0 : string) : number;
    s_AbsID : any;
    s_Array : any;
    m_ParentCountry : any;
    m_ArrayIndex : number;
    m_ArrayIndex2 : number;
    m_SideIndex : number;
    m_ColorSchemeIndex : number;
    m_FirepowerMult : number;
    m_GroundspeedMult : number;
    m_AirspeedMult : number;
    m_ArmorMult : number;
    m_ROFMult : number;
    m_CostMult : number;
    m_BuildtimeMult : number;
    m_ArmorInfantryMult : number;
    m_ArmorUnitsMult : number;
    m_ArmorAircraftMult : number;
    m_ArmorBuildingsMult : number;
    m_ArmorDefensesMult : number;
    m_CostInfantryMult : number;
    m_CostUnitsMult : number;
    m_CostAircraftMult : number;
    m_CostBuildingsMult : number;
    m_CostDefensesMult : number;
    m_SpeedInfantryMult : number;
    m_SpeedUnitsMult : number;
    m_SpeedAircraftMult : number;
    m_BuildtimeInfantryMult : number;
    m_BuildtimeUnitsMult : number;
    m_BuildtimeAircraftMult : number;
    m_BuildtimeBuildingsMult : number;
    m_BuildtimeDefensesMult : number;
    m_IncomeMult : number;
    m_VeteranInfantry : any;
    m_VeteranUnits : any;
    m_VeteranAircraft : any;
    m_Suffix : number;
    m_Prefix : number;
    m_Multiplay : boolean;
    m_MultiplayPassive : boolean;
    m_WallOwner : boolean;
    m_SmartAI : boolean;
}
class StartingTechnoStruct
{
    m_Unit : TechnoTypeClass;
    m_Cell : any;
}
class WaypointPathClass
    extends AbstractClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    GetWaypoint(idx_0 : number) : WaypointClass;
    GetWaypointAfter(idx_0 : number) : WaypointClass;
    WaypointExistsAt(wpt_0 : WaypointClass) : boolean;
    s_AbsID : any;
    m_CurrentWaypointIndex : number;
    m_Waypoints : any;
}
class UnitTrackerClass
{
    IncrementUnitCount(nUnit_0 : number) : void;
    DecrementUnitCount(nUnit_0 : number) : void;
    PopulateUnitCount(nCount_0 : number) : void;
    GetUnitCount() : number;
    GetArray() : number;
    ClearUnitCount() : void;
    ToNetworkFormat() : void;
    ToPCFormat() : void;
    m_UnitTotals : number;
    m_UnitCount : number;
    m_InNetworkFormat : number;
}
class ZoneInfoStruct
{
    m_Aircraft : number;
    m_Armor : number;
    m_Infantry : number;
}
class AngerStruct
{
    m_House : HouseClass;
    m_AngerLevel : number;
}
class ScoutStruct
{
    m_House : HouseClass;
    m_IsPreferred : boolean;
}
class DropshipStruct
{
    m_Timer : CDTimerClass;
    m___Timer : number;
    m_unknown_C : number;
    m_Count : number;
    m_Types : TechnoTypeClass;
    m_TotalCost : number;
}
class BaseClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any) : number;
    ComputeCRC(crc_0 : any) : void;
    FailedToPlaceNode(Node_0 : BaseNodeClass) : number;
    m_BaseNodes : any;
    m___BaseNodes : number;
    m_PercentBuilt : number;
    m_Cells_24 : any;
    m___Cells_24 : number;
    m_Cells_38 : any;
    m___Cells_38 : number;
    m_Center : any;
    m_Owner : HouseClass;
}
class BaseNodeClass
{
    m_BuildingTypeIndex : number;
    m_MapCoords : any;
    m_Placed : boolean;
    m_Attempts : number;
}
class Randomizer
{
    Random() : number;
    RandomRanged(nMin_0 : number, nMax_1 : number) : number;
    RandomDouble() : number;
    s_Global : any;
    m_unknown_00 : boolean;
    m_Next1 : number;
    m_Next2 : number;
    m_Table : number;
}
class LinkClass
{
    GetNext() : LinkClass;
    GetPrev() : LinkClass;
    Add(another_0 : LinkClass) : LinkClass;
    AddTail(another_0 : LinkClass) : LinkClass;
    AddHead(another_0 : LinkClass) : LinkClass;
    HeadOfList(another_0 : LinkClass) : LinkClass;
    TailOfList(another_0 : LinkClass) : LinkClass;
    Zap() : void;
    Remove() : LinkClass;
    m_Next : LinkClass;
    m_Previous : LinkClass;
}
class GadgetClass
    extends LinkClass
{
    GetNext() : GadgetClass;
    GetPrev() : GadgetClass;
    Zap() : void;
    Remove() : GadgetClass;
    Input() : number;
    DrawAll(bForced_0 : boolean) : void;
    DeleteList() : void;
    ExtractGadget(nID_0 : number) : GadgetClass;
    MarkListToRedraw() : void;
    Disable() : void;
    Enable() : void;
    GetID() : number;
    MarkRedraw() : void;
    PeerToPeer(Flags_0 : number, pKey_1 : number, pSendTo_2 : GadgetClass) : void;
    SetFocus() : void;
    KillFocus() : void;
    IsFocused() : boolean;
    IsListToRedraw() : boolean;
    IsToRedraw() : boolean;
    SetPosition(X_0 : number, Y_1 : number) : void;
    SetDimension(Width_0 : number, Height_1 : number) : void;
    Draw(bForced_0 : boolean) : boolean;
    OnMouseEnter() : void;
    OnMouseLeave() : void;
    StickyProcess(Flags_0 : any) : void;
    Action(Flags_0 : any, pKey_1 : number, Modifier_2 : any) : boolean;
    Clicked(pKey_0 : number, Flags_1 : any, X_2 : number, Y_3 : number, Modifier_4 : any) : boolean;
    ExtractGadgetAt(X_0 : number, Y_1 : number) : GadgetClass;
    static GetColorScheme() : number;
    m_X : number;
    m_Y : number;
    m_Width : number;
    m_Height : number;
    m_NeedsRedraw : boolean;
    m_IsSticky : boolean;
    m_Disabled : boolean;
    m_Flags : any;
}
class DifficultyStruct
{
    m_Firepower : number;
    m_GroundSpeed : number;
    m_AirSpeed : number;
    m_Armor : number;
    m_ROF : number;
    m_Cost : number;
    m_BuildTime : number;
    m_RepairDelay : number;
    m_BuildDelay : number;
    m_BuildSlowdown : boolean;
    m_DestroyWalls : boolean;
    m_ContentScan : boolean;
}
class RulesClass
{
    Init(pINI_0 : CCINIClass) : void;
    Read_File(pINI_0 : CCINIClass) : void;
    Read_SpecialWeapons(pINI_0 : CCINIClass) : void;
    Read_AudioVisual(pINI_0 : CCINIClass) : void;
    Read_CrateRules(pINI_0 : CCINIClass) : void;
    Read_CombatDamage(pINI_0 : CCINIClass) : void;
    Read_Radiation(pINI_0 : CCINIClass) : void;
    Read_ElevationModel(pINI_0 : CCINIClass) : void;
    Read_WallModel(pINI_0 : CCINIClass) : void;
    Read_Difficulty(pINI_0 : CCINIClass) : void;
    Read_Colors(pINI_0 : CCINIClass) : void;
    Read_ColorAdd(pINI_0 : CCINIClass) : void;
    Read_General(pINI_0 : CCINIClass) : void;
    Read_MultiplayerDialogSettings(pINI_0 : CCINIClass) : void;
    Read_Maximums(pINI_0 : CCINIClass) : void;
    Read_InfantryTypes(pINI_0 : CCINIClass) : void;
    Read_Countries(pINI_0 : CCINIClass) : void;
    Read_VehicleTypes(pINI_0 : CCINIClass) : void;
    Read_AircraftTypes(pINI_0 : CCINIClass) : void;
    Read_Sides(pINI_0 : CCINIClass) : void;
    Read_SuperWeaponTypes(pINI_0 : CCINIClass) : void;
    Read_BuildingTypes(pINI_0 : CCINIClass) : void;
    Read_TerrainTypes(pINI_0 : CCINIClass) : void;
    Read_Teams_obsolete(pINI_0 : CCINIClass) : void;
    Read_SmudgeTypes(pINI_0 : CCINIClass) : void;
    Read_OverlayTypes(pINI_0 : CCINIClass) : void;
    Read_Animations(pINI_0 : CCINIClass) : void;
    Read_VoxelAnims(pINI_0 : CCINIClass) : void;
    Read_Warheads(pINI_0 : CCINIClass) : void;
    Read_Particles(pINI_0 : CCINIClass) : void;
    Read_ParticleSystems(pINI_0 : CCINIClass) : void;
    Read_AI(pINI_0 : CCINIClass) : void;
    Read_Powerups(pINI_0 : CCINIClass) : void;
    Read_LandCharacteristics(pINI_0 : CCINIClass) : void;
    Read_IQ(pINI_0 : CCINIClass) : void;
    Read_JumpjetControls(pINI_0 : CCINIClass) : void;
    Read_Difficulties(pINI_0 : CCINIClass) : void;
    Read_Movies(pINI_0 : CCINIClass) : void;
    Read_AdvancedCommandBar(pINI_0 : CCINIClass) : void;
    PointerGotInvalid(pInvalid_0 : AbstractClass, removed_1 : boolean) : void;
    s_Instance : any;
    m_DetailMinFrameRateNormal : number;
    m_DetailMinFrameRateMovie : number;
    m_DetailBufferZoneWidth : number;
    m_AmmoCrateDamage : number;
    m_LargeVisceroid : UnitTypeClass;
    m_SmallVisceroid : UnitTypeClass;
    m_AttackingAircraftSightRange : number;
    m_TunnelSpeed : number;
    m_TiberiumHeal : number;
    m_SelfHealInfantryFrames : number;
    m_SelfHealInfantryAmount : number;
    m_SelfHealUnitFrames : number;
    m_SelfHealUnitAmount : number;
    m_FreeMCV : boolean;
    m_BerzerkAllowed : boolean;
    m_PoseDir : number;
    m_DeployDir : number;
    m_DropPodPuff : AnimTypeClass;
    m_WaypointAnimationSpeed : number;
    m_BarrelExplode : AnimTypeClass;
    m_BarrelDebris : any;
    m_BarrelParticle : ParticleSystemTypeClass;
    m_RadarEventColorSpeed : number;
    m_RadarEventMinRadius : number;
    m_RadarEventSpeed : number;
    m_RadarEventRotationSpeed : number;
    m_FlashFrameTime : number;
    m_RadarCombatFlashTime : number;
    m_MaxWaypointPathLength : number;
    m_Wake : AnimTypeClass;
    m_NukeTakeOff : AnimTypeClass;
    m_InfantryExplode : AnimTypeClass;
    m_FlamingInfantry : AnimTypeClass;
    m_InfantryHeadPop : AnimTypeClass;
    m_InfantryNuked : AnimTypeClass;
    m_InfantryVirus : AnimTypeClass;
    m_InfantryBrute : AnimTypeClass;
    m_InfantryMutate : AnimTypeClass;
    m_Behind : AnimTypeClass;
    m_AITriggerSuccessWeightDelta : number;
    m_AITriggerFailureWeightDelta : number;
    m_AITriggerTrackRecordCoefficient : number;
    m_VeinholeMonsterStrength : number;
    m_MaxVeinholeGrowth : number;
    m_VeinholeGrowthRate : number;
    m_VeinholeShrinkRate : number;
    m_VeinAttack : AnimTypeClass;
    m_VeinDamage : number;
    m_MaximumQueuedObjects : number;
    m_AircraftFogReveal : number;
    m_WoodCrateImg : OverlayTypeClass;
    m_CrateImg : OverlayTypeClass;
    m_WaterCrateImg : OverlayTypeClass;
    m_DropPod : any;
    m_DeadBodies : any;
    m_MetallicDebris : any;
    m_BridgeExplosions : any;
    m_DigSound : number;
    m_CreateUnitSound : number;
    m_CreateInfantrySound : number;
    m_CreateAircraftSound : number;
    m_BaseUnderAttackSound : number;
    m_GUIMainButtonSound : number;
    m_GUIBuildSound : number;
    m_GUITabSound : number;
    m_GUIOpenSound : number;
    m_GUICloseSound : number;
    m_GUIMoveOutSound : number;
    m_GUIMoveInSound : number;
    m_GUIComboOpenSound : number;
    m_GUIComboCloseSound : number;
    m_GUICheckboxSound : number;
    m_ScoreAnimSound : number;
    m_IFVTransformSound : number;
    m_PsychicSensorDetectSound : number;
    m_BuildingGarrisonedSound : number;
    m_BuildingAbandonedSound : number;
    m_BuildingRepairedSound : number;
    m_CheerSound : number;
    m_PlaceBeaconSound : number;
    m_DefaultChronoSound : number;
    m_StartPlanningModeSound : number;
    m_AddPlanningModeCommandSound : number;
    m_ExecutePlanSound : number;
    m_EndPlanningModeSound : number;
    m_CrateMoneySound : number;
    m_CrateRevealSound : number;
    m_CrateFireSound : number;
    m_CrateArmourSound : number;
    m_CrateSpeedSound : number;
    m_CrateUnitSound : number;
    m_CratePromoteSound : number;
    m_ImpactWaterSound : number;
    m_ImpactLandSound : number;
    m_SinkingSound : number;
    m_BombTickingSound : number;
    m_BombAttachSound : number;
    m_YuriMindControlSound : number;
    m_ChronoInSound : number;
    m_ChronoOutSound : number;
    m_SpySatActivationSound : number;
    m_SpySatDeactivationSound : number;
    m_UpgradeVeteranSound : number;
    m_UpgradeEliteSound : number;
    m_VoiceIFVRepair : number;
    m_SlavesFreeSound : number;
    m_SlaveMinerDeploySound : number;
    m_SlaveMinerUndeploySound : number;
    m_BunkerWallsUpSound : number;
    m_BunkerWallsDownSound : number;
    m_RepairBridgeSound : number;
    m_PsychicDominatorActivateSound : number;
    m_GeneticMutatorActivateSound : number;
    m_PsychicRevealActivateSound : number;
    m_MasterMindOverloadDeathSound : number;
    m_AirstrikeAbortSound : number;
    m_AirstrikeAttackVoice : number;
    m_MindClearedSound : number;
    m_EnterGrinderSound : number;
    m_LeaveGrinderSound : number;
    m_EnterBioReactorSound : number;
    m_LeaveBioReactorSound : number;
    m_ActivateSound : number;
    m_DeactivateSound : number;
    m_SpyPlaneCamera : number;
    m_LetsDoTheTimeWarpOutAgain : number;
    m_LetsDoTheTimeWarpInAgain : number;
    m_DiskLaserChargeUp : number;
    m_SpyPlaneCameraFrames : number;
    m_Dig : AnimTypeClass;
    m_IonBlast : AnimTypeClass;
    m_IonBeam : AnimTypeClass;
    m_DamageFireTypes : any;
    m_WeatherConClouds : any;
    m_WeatherConBolts : any;
    m_WeatherConBoltExplosion : AnimTypeClass;
    m_DominatorWarhead : WarheadTypeClass;
    m_DominatorFirstAnim : AnimTypeClass;
    m_DominatorSecondAnim : AnimTypeClass;
    m_DominatorFireAtPercentage : number;
    m_DominatorCaptureRange : number;
    m_DominatorDamage : number;
    m_MindControlAttackLineFrames : number;
    m_DrainMoneyFrameDelay : number;
    m_DrainMoneyAmount : number;
    m_DrainAnimationType : AnimTypeClass;
    m_ControlledAnimationType : AnimTypeClass;
    m_PermaControlledAnimationType : AnimTypeClass;
    m_ChronoBlast : AnimTypeClass;
    m_ChronoBlastDest : AnimTypeClass;
    m_ChronoPlacement : AnimTypeClass;
    m_ChronoBeam : AnimTypeClass;
    m_WarpIn : AnimTypeClass;
    m_WarpOut : AnimTypeClass;
    m_WarpAway : AnimTypeClass;
    m_ChronoSparkle1 : AnimTypeClass;
    m_IronCurtainInvokeAnim : AnimTypeClass;
    m_ForceShieldInvokeAnim : AnimTypeClass;
    m_WeaponNullifyAnim : AnimTypeClass;
    m_AtmosphereEntry : AnimTypeClass;
    m_PrerequisitePower : any;
    m_PrerequisiteFactory : any;
    m_PrerequisiteBarracks : any;
    m_PrerequisiteRadar : any;
    m_PrerequisiteTech : any;
    m_PrerequisiteProc : any;
    m_PrerequisiteProcAlternate : UnitTypeClass;
    m_GateUp : number;
    m_GateDown : number;
    m_TurnRate : number;
    m_Speed : number;
    m_Climb : number;
    m_CruiseHeight : number;
    m_Acceleration : number;
    m_WobblesPerSecond : number;
    m_WobbleDeviation : number;
    m_RadarEventSuppressionDistances : any;
    m_RadarEventVisibilityDurations : any;
    m_RadarEventDurations : any;
    m_IonCannonDamage : number;
    m_RailgunDamageRadius : number;
    m_PrismType : BuildingTypeClass;
    m_PrismSupportModifier : number;
    m_PrismSupportMax : number;
    m_PrismSupportDelay : number;
    m_PrismSupportDuration : number;
    m_PrismSupportHeight : number;
    m_V3Rocket : any;
    m_DMisl : any;
    m_CMisl : any;
    m_ParadropRadius : number;
    m_ZoomInFactor : number;
    m_ConditionRedSparkingProbability : number;
    m_ConditionYellowSparkingProbability : number;
    m_TiberiumExplosionDamage : number;
    m_TiberiumStrength : number;
    m_MinLowPowerProductionSpeed : number;
    m_MaxLowPowerProductionSpeed : number;
    m_LowPowerPenaltyModifier : number;
    m_MultipleFactory : number;
    m_MaximumCheerRate : number;
    m_TreeFlammability : number;
    m_MissileSpeedVar : number;
    m_MissileROTVar : number;
    m_MissileSafetyAltitude : number;
    m_DropPodWeapon : WeaponTypeClass;
    m_DropPodHeight : number;
    m_DropPodSpeed : number;
    m_DropPodAngle : number;
    m_ScrollMultiplier : number;
    m_CrewEscape : number;
    m_ShakeScreen : number;
    m_HoverHeight : number;
    m_HoverBob : number;
    m_HoverBoost : number;
    m_HoverAcceleration : number;
    m_HoverBrake : number;
    m_HoverDampen : number;
    m_PlacementDelay : number;
    m_ExplosiveVoxelDebris : any;
    m_TireVoxelDebris : VoxelAnimTypeClass;
    m_ScrapVoxelDebris : VoxelAnimTypeClass;
    m_BridgeVoxelMax : number;
    m_CloakingStages : number;
    m_RevealTriggerRadius : number;
    m_ShipSinkingWeight : number;
    m_IceCrackingWeight : number;
    m_IceBreakingWeight : number;
    m_IceCrackSounds : any;
    m_CliffBackImpassability : number;
    m_VeteranRatio : number;
    m_VeteranCombat : number;
    m_VeteranSpeed : number;
    m_VeteranSight : number;
    m_VeteranArmor : number;
    m_VeteranROF : number;
    m_VeteranCap : number;
    m_CloakSound : number;
    m_SellSound : number;
    m_GameClosed : number;
    m_IncomingMessage : number;
    m_SystemError : number;
    m_OptionsChanged : number;
    m_GameForming : number;
    m_PlayerLeft : number;
    m_PlayerJoined : number;
    m_MessageCharTyped : number;
    m_Construction : number;
    m_CreditTicks : any;
    m_BuildingDieSound : number;
    m_BuildingSlam : number;
    m_RadarOn : number;
    m_RadarOff : number;
    m_MovieOn : number;
    m_MovieOff : number;
    m_ScoldSound : number;
    m_TeslaCharge : number;
    m_TeslaZap : number;
    m_GenericClick : number;
    m_GenericBeep : number;
    m_BuildingDamageSound : number;
    m_HealCrateSound : number;
    m_ChuteSound : number;
    m_StopSound : number;
    m_GuardSound : number;
    m_ScatterSound : number;
    m_DeploySound : number;
    m_StormSound : number;
    m_LightningSounds : any;
    m_ShellButtonSlideSound : number;
    m_WallBuildSpeedCoefficient : number;
    m_ChargeToDrainRatio : number;
    m_TrackedUphill : number;
    m_TrackedDownhill : number;
    m_WheeledUphill : number;
    m_WheeledDownhill : number;
    m_SpotlightMovementRadius : number;
    m_SpotlightLocationRadius : number;
    m_SpotlightSpeed : number;
    m_SpotlightAcceleration : number;
    m_SpotlightAngle : number;
    m_SpotlightRadius : number;
    m_WindDirection : number;
    m_CameraRange : number;
    m_FlightLevel : number;
    m_ParachuteMaxFallRate : number;
    m_NoParachuteMaxFallRate : number;
    m_BuildingDrop : number;
    m_Scorches : any;
    m_Scorches1 : any;
    m_Scorches2 : any;
    m_Scorches3 : any;
    m_Scorches4 : any;
    m_RepairBay : any;
    m_GDIGateOne : BuildingTypeClass;
    m_GDIGateTwo : BuildingTypeClass;
    m_NodGateOne : BuildingTypeClass;
    m_NodGateTwo : BuildingTypeClass;
    m_WallTower : BuildingTypeClass;
    m_Shipyard : any;
    m_GDIPowerPlant : BuildingTypeClass;
    m_NodRegularPower : BuildingTypeClass;
    m_NodAdvancedPower : BuildingTypeClass;
    m_ThirdPowerPlant : BuildingTypeClass;
    m_BuildConst : any;
    m_BuildPower : any;
    m_BuildRefinery : any;
    m_BuildBarracks : any;
    m_BuildTech : any;
    m_BuildWeapons : any;
    m_AlliedBaseDefenses : any;
    m_SovietBaseDefenses : any;
    m_ThirdBaseDefenses : any;
    m_AIForcePredictionFudge : any;
    m_BuildDefense : any;
    m_BuildPDefense : any;
    m_BuildAA : any;
    m_BuildHelipad : any;
    m_BuildRadar : any;
    m_ConcreteWalls : any;
    m_NSGates : any;
    m_EWGates : any;
    m_BuildNavalYard : any;
    m_BuildDummy : any;
    m_NeutralTechBuildings : any;
    m_GDIWallDefense : number;
    m_GDIWallDefenseCoefficient : number;
    m_NodBaseDefenseCoefficient : number;
    m_GDIBaseDefenseCoefficient : number;
    m_ComputerBaseDefenseResponse : number;
    m_MaximumBaseDefenseValue : number;
    m_BaseUnit : any;
    m_HarvesterUnit : any;
    m_PadAircraft : any;
    m_OnFire : any;
    m_TreeFire : any;
    m_Smoke : AnimTypeClass;
    m_Smoke_ : AnimTypeClass;
    m_MoveFlash : AnimTypeClass;
    m_BombParachute : AnimTypeClass;
    m_Parachute : AnimTypeClass;
    m_SplashList : any;
    m_SmallFire : AnimTypeClass;
    m_LargeFire : AnimTypeClass;
    m_Paratrooper : InfantryTypeClass;
    m_EliteFlashTimer : number;
    m_ChronoDelay : number;
    m_ChronoReinfDelay : number;
    m_ChronoDistanceFactor : number;
    m_ChronoTrigger : boolean;
    m_ChronoMinimumDelay : number;
    m_ChronoRangeMinimum : number;
    m_AmerParaDropInf : any;
    m_AmerParaDropNum : any;
    m_AllyParaDropInf : any;
    m_AllyParaDropNum : any;
    m_SovParaDropInf : any;
    m_SovParaDropNum : any;
    m_YuriParaDropInf : any;
    m_YuriParaDropNum : any;
    m_AnimToInfantry : any;
    m_SecretInfantry : any;
    m_SecretUnits : any;
    m_SecretBuildings : any;
    m_SecretSum : number;
    m_AlliedDisguise : InfantryTypeClass;
    m_SovietDisguise : InfantryTypeClass;
    m_ThirdDisguise : InfantryTypeClass;
    m_SpyPowerBlackout : number;
    m_SpyMoneyStealPercent : number;
    m_AttackCursorOnDisguise : boolean;
    m_AIMinorSuperReadyPercent : number;
    m_AISafeDistance : number;
    m_HarvesterTooFarDistance : number;
    m_ChronoHarvTooFarDistance : number;
    m_AlliedBaseDefenseCounts : any;
    m_SovietBaseDefenseCounts : any;
    m_ThirdBaseDefenseCounts : any;
    m_AIPickWallDefensePercent : any;
    m_AIRestrictReplaceTime : number;
    m_ThreatPerOccupant : number;
    m_ApproachTargetResetMultiplier : number;
    m_CampaignMoneyDeltaEasy : number;
    m_CampaignMoneyDeltaHard : number;
    m_GuardAreaTargetingDelay : number;
    m_NormalTargetingDelay : number;
    m_AINavalYardAdjacency : number;
    m_DisabledDisguiseDetectionPercent : any;
    m_AIAutoDeployFrameDelay : any;
    m_MaximumBuildingPlacementFailures : number;
    m_AICaptureNormal : any;
    m_AICaptureWounded : any;
    m_AICaptureLowPower : any;
    m_AICaptureLowMoney : any;
    m_AICaptureLowMoneyMark : number;
    m_AICaptureWoundedMark : number;
    m_AISuperDefenseProbability : any;
    m_AISuperDefenseFrames : number;
    m_AISuperDefenseDistance : number;
    m_OverloadCount : any;
    m_OverloadDamage : any;
    m_OverloadFrames : any;
    m_PurifierBonus : number;
    m_OccupyDamageMultiplier : number;
    m_OccupyROFMultiplier : number;
    m_OccupyWeaponRange : number;
    m_BunkerDamageMultiplier : number;
    m_BunkerROFMultiplier : number;
    m_BunkerWeaponRangeBonus : number;
    m_OpenToppedDamageMultiplier : number;
    m_OpenToppedRangeBonus : number;
    m_OpenToppedWarpDistance : number;
    m_FallingDamageMultiplier : number;
    m_CurrentStrengthDamage : boolean;
    m_Technician : InfantryTypeClass;
    m_Engineer : InfantryTypeClass;
    m_Pilot : InfantryTypeClass;
    m_AlliedCrew : InfantryTypeClass;
    m_SovietCrew : InfantryTypeClass;
    m_ThirdCrew : InfantryTypeClass;
    m_FlameDamage : WarheadTypeClass;
    m_FlameDamage2 : WarheadTypeClass;
    m_NukeWarhead : WarheadTypeClass;
    m_NukeProjectile : BulletTypeClass;
    m_NukeDown : BulletTypeClass;
    m_MutateWarhead : WarheadTypeClass;
    m_MutateExplosionWarhead : WarheadTypeClass;
    m_EMPulseWarhead : WarheadTypeClass;
    m_EMPulseProjectile : WarheadTypeClass;
    m_C4Warhead : WarheadTypeClass;
    m_CrushWarhead : WarheadTypeClass;
    m_V3Warhead : WarheadTypeClass;
    m_DMislWarhead : WarheadTypeClass;
    m_V3EliteWarhead : WarheadTypeClass;
    m_DMislEliteWarhead : WarheadTypeClass;
    m_CMislWarhead : WarheadTypeClass;
    m_CMislEliteWarhead : WarheadTypeClass;
    m_IvanWarhead : WarheadTypeClass;
    m_IvanDamage : number;
    m_IvanTimedDelay : number;
    m_CanDetonateTimeBomb : boolean;
    m_CanDetonateDeathBomb : boolean;
    m_IvanIconFlickerRate : number;
    m_DeathWeapon : WeaponTypeClass;
    m_BOMBCURS_SHP : any;
    m_CHRONOSK_SHP : any;
    m_IronCurtainDuration : number;
    m_PsychicRevealRadius : number;
    m_IonCannonWarhead : WarheadTypeClass;
    m_VeinholeTypeClass : TerrainTypeClass;
    m_DefaultMirageDisguises : any;
    m_InfantryBlinkDisguiseTime : number;
    m_DefaultLargeGreySmokeSystem : ParticleSystemTypeClass;
    m_DefaultSmallGreySmokeSystem : ParticleSystemTypeClass;
    m_DefaultSparkSystem : ParticleSystemTypeClass;
    m_DefaultLargeRedSmokeSystem : ParticleSystemTypeClass;
    m_DefaultSmallRedSmokeSystem : ParticleSystemTypeClass;
    m_DefaultDebrisSmokeSystem : ParticleSystemTypeClass;
    m_DefaultFireStreamSystem : ParticleSystemTypeClass;
    m_DefaultTestParticleSystem : ParticleSystemTypeClass;
    m_DefaultRepairParticleSystem : ParticleSystemTypeClass;
    m_MyEffectivenessCoefficientDefault : number;
    m_TargetEffectivenessCoefficientDefault : number;
    m_TargetSpecialThreatCoefficientDefault : number;
    m_TargetStrengthCoefficientDefault : number;
    m_TargetDistanceCoefficientDefault : number;
    m_DumbMyEffectivenessCoefficient : number;
    m_DumbTargetEffectivenessCoefficient : number;
    m_DumbTargetSpecialThreatCoefficient : number;
    m_DumbTargetStrengthCoefficient : number;
    m_DumbTargetDistanceCoefficient : number;
    m_EnemyHouseThreatBonus : number;
    m_TurboBoost : number;
    m_AttackInterval : number;
    m_AttackDelay : number;
    m_PowerEmergency : number;
    m_AirstripRatio : number;
    m_AirstripLimit : number;
    m_HelipadRatio : number;
    m_HelipadLimit : number;
    m_TeslaRatio : number;
    m_TeslaLimit : number;
    m_AARatio : number;
    m_AALimit : number;
    m_DefenseRatio : number;
    m_DefenseLimit : number;
    m_WarRatio : number;
    m_WarLimit : number;
    m_BarracksRatio : number;
    m_BarracksLimit : number;
    m_RefineryLimit : number;
    m_RefineryRatio : number;
    m_BaseSizeAdd : number;
    m_PowerSurplus : number;
    m_InfantryReserve : number;
    m_InfantryBaseMult : number;
    m_SoloCrateMoney : number;
    m_TreeStrength : number;
    m_UnitCrateType : UnitTypeClass;
    m_PatrolScan : number;
    m_TeamDelays : any;
    m_AIHateDelays : any;
    m_DissolveUnfilledTeamDelay : number;
    m_AIIonCannonConYardValue : any;
    m_AIIonCannonWarFactoryValue : any;
    m_AIIonCannonPowerValue : any;
    m_AIIonCannonTechCenterValue : any;
    m_AIIonCannonEngineerValue : any;
    m_AIIonCannonThiefValue : any;
    m_AIIonCannonHarvesterValue : any;
    m_AIIonCannonMCVValue : any;
    m_AIIonCannonAPCValue : any;
    m_AIIonCannonBaseDefenseValue : any;
    m_AIIonCannonPlugValue : any;
    m_AIIonCannonHelipadValue : any;
    m_AIIonCannonTempleValue : any;
    m_AIAlternateProductionCreditCutoff : number;
    m_MultiplayerAICM : any;
    m_AIVirtualPurifiers : any;
    m_AISlaveMinerNumber : any;
    m_HarvestersPerRefinery : any;
    m_AIExtraRefineries : any;
    m_MinimumAIDefensiveTeams : any;
    m_MaximumAIDefensiveTeams : any;
    m_TotalAITeamCap : any;
    m_AIUseTurbineUpgradeProbability : number;
    m_FillEarliestTeamProbability : any;
    m_CloakDelay : number;
    m_GameSpeedBias : number;
    m_BaseBias : number;
    m_ExpSpread : number;
    m_FireSupress : number;
    m_MaxIQLevels : number;
    m_SuperWeapons : number;
    m_Production : number;
    m_GuardArea : number;
    m_RepairSell : number;
    m_AutoCrush : number;
    m_Scatter : number;
    m_ContentScan : number;
    m_Aircraft : number;
    m_Harvester : number;
    m_SellBack : number;
    m_AIBaseSpacing : number;
    m_SilverCrate : any;
    m_WoodCrate : any;
    m_WaterCrate : any;
    m_CrateMinimum : number;
    m_CrateMaximum : number;
    m_unknown_int_1478 : number;
    m_DropZoneAnim : AnimTypeClass;
    m_MinMoney : number;
    m_Money : number;
    m_MaxMoney : number;
    m_MoneyIncrement : number;
    m_MinUnitCount : number;
    m_UnitCount : number;
    m_MaxUnitCount : number;
    m_TechLevel : number;
    m_GameSpeed : number;
    m_AIDifficultyStruct : number;
    m_AIPlayers : number;
    m_BridgeDestruction : boolean;
    m_ShadowGrow : boolean;
    m_Shroud : boolean;
    m_Bases : boolean;
    m_TiberiumGrows : boolean;
    m_Crates : boolean;
    m_CaptureTheFlag : boolean;
    m_HarvesterTruce : boolean;
    m_MultiEngineer : boolean;
    m_AlliesAllowed : boolean;
    m_ShortGame : boolean;
    m_FogOfWar : boolean;
    m_MCVRedeploys : boolean;
    m_SuperWeaponsAllowed : boolean;
    m_BuildOffAlly : boolean;
    m_AllyChangeAllowed : boolean;
    m_DropZoneRadius : number;
    m_MessageDelay : number;
    m_SavourDelay : number;
    m_Players : number;
    m_BaseDefenseDelay : number;
    m_SuspendPriority : number;
    m_SuspendDelay : number;
    m_SurvivorRate : number;
    m_AlliedSurvivorDivisor : number;
    m_SovietSurvivorDivisor : number;
    m_ThirdSurvivorDivisor : number;
    m_ReloadRate : number;
    m_AutocreateTime : number;
    m_BuildupTime : number;
    m_HarvesterLoadRate : number;
    m_HarvesterDumpRate : number;
    m_AtomDamage : number;
    m_Easy : DifficultyStruct;
    m_Normal : DifficultyStruct;
    m_Difficult : DifficultyStruct;
    m_align_1628 : number;
    m_GrowthRate : number;
    m_ShroudRate : number;
    m_FogRate : number;
    m_IceGrowthRate : number;
    m_VeinGrowthRate : number;
    m_IceSolidifyFrameTime : number;
    m_AmbientChangeRate : number;
    m_AmbientChangeStep : number;
    m_CrateRegen : number;
    m_TimerWarning : number;
    m_TiberiumTransmogrify : number;
    m_unknown_double_1690 : number;
    m_unknown_double_1698 : number;
    m_unknown_double_16A0 : number;
    m_SpeakDelay : number;
    m_DamageDelay : number;
    m_Gravity : number;
    m_LeptonsPerSightIncrease : number;
    m_Incoming : number;
    m_MinDamage : number;
    m_MaxDamage : number;
    m_RepairStep : number;
    m_RepairPercent : number;
    m_IRepairStep : number;
    m_RepairRate : number;
    m_URepairRate : number;
    m_IRepairRate : number;
    m_unknown_double_16F8 : number;
    m_ConditionYellow : number;
    m_ConditionRed : number;
    m_IdleActionFrequency : number;
    m_CloseEnough : number;
    m_Stray : number;
    m_RelaxedStray : number;
    m_GuardModeStray : number;
    m_Crush : number;
    m_CrateRadius : number;
    m_HomingScatter : number;
    m_BallisticScatter : number;
    m_RefundPercent : number;
    m_BridgeStrength : number;
    m_BuildSpeed : number;
    m_C4Delay : number;
    m_CreditReserve : number;
    m_PathDelay : number;
    m_BlockagePathDelay : number;
    m_MovieTime : number;
    m_TiberiumShortScan : number;
    m_TiberiumLongScan : number;
    m_SlaveMinerShortScan : number;
    m_SlaveMinerSlaveScan : number;
    m_SlaveMinerLongScan : number;
    m_SlaveMinerScanCorrection : number;
    m_SlaveMinerKickFrameDelay : number;
    m_LightningDeferment : number;
    m_LightningDamage : number;
    m_LightningStormDuration : number;
    m_LightningHitDelay : number;
    m_LightningScatterDelay : number;
    m_LightningCellSpread : number;
    m_LightningSeparation : number;
    m_LightningPrintText : boolean;
    m_LightningWarhead : WarheadTypeClass;
    m_ForceShieldRadius : number;
    m_ForceShieldDuration : number;
    m_ForceShieldBlackoutDuration : number;
    m_ForceShieldPlayFadeSoundTime : number;
    m_MutateExplosion : boolean;
    m_CollapseChance : number;
    m_WeedCapacity : number;
    m_ExtraUnitLight : number;
    m_ExtraInfantryLight : number;
    m_ExtraAircraftLight : number;
    m_Paranoid : boolean;
    m_CurleyShuffle : boolean;
    m_BlendedFog : boolean;
    m_CompEasyBonus : boolean;
    m_FineDiffControl : boolean;
    m_TiberiumExplosive : boolean;
    m_EnemyHealth : boolean;
    m_AllyReveal : boolean;
    m_SeparateAircraft : boolean;
    m_TreeTargeting : boolean;
    m_NamedCivilians : boolean;
    m_PlayerAutoCrush : boolean;
    m_PlayerReturnFire : boolean;
    m_PlayerScatter : boolean;
    m_RevealByHeight : boolean;
    m_AllowShroudedSubteranneanMoves : boolean;
    m_ShroudGrow : boolean;
    m_NodAIBuildsWalls : boolean;
    m_AIBuildsWalls : boolean;
    m_UseMinDefenseRule : boolean;
    m_EMPulseSparkles : AnimTypeClass;
    m_EngineerCaptureLevel : number;
    m_EngineerCaptureLevel_ : number;
    m_TalkBubbleTime : number;
    m_RadDurationMultiple : number;
    m_RadApplicationDelay : number;
    m_RadLevelMax : number;
    m_RadLevelDelay : number;
    m_RadLightDelay : number;
    m_RadLevelFactor : number;
    m_RadLightFactor : number;
    m_RadTintFactor : number;
    m_RadColor : any;
    m_RadSiteWarhead : WarheadTypeClass;
    m_ElevationIncrement : number;
    m_ElevationIncrementBonus : number;
    m_ElevationBonusCap : number;
    m_AlliedWallTransparency : boolean;
    m_WallPenetratorThreshold : number;
    m_LocalRadarColor : any;
    m_LineTrailColorOverride : any;
    m_ChronoBeamColor : any;
    m_MagnaBeamColor : any;
    m_OreTwinkleChance : number;
    m_OreTwinkle : AnimTypeClass;
    m_ColorAdd : any;
    m_LaserTargetColor : number;
    m_IronCurtainColor : number;
    m_BerserkColor : number;
    m_ForceShieldColor : number;
    m_DirectRockingCoefficient : number;
    m_FallBackCoefficient : number;
}
class LightingStruct
{
    m_Tint : TintStruct;
    m_Ground : number;
    m_Level : number;
}
class ScenarioFlags
{
    m_bit00 : boolean;
    m_bit01 : boolean;
    m_bit02 : boolean;
    m_bit03 : boolean;
    m_CTFMode : boolean;
    m_Inert : boolean;
    m_TiberiumGrows : boolean;
    m_TiberiumSpreads : boolean;
    m_MCVDeploy : boolean;
    m_InitialVeteran : boolean;
    m_FixedAlliance : boolean;
    m_HarvesterImmune : boolean;
    m_FogOfWar : boolean;
    m_bit13 : boolean;
    m_TiberiumExplosive : boolean;
    m_DestroyableBridges : boolean;
    m_Meteorites : boolean;
    m_IonStorms : boolean;
    m_Visceroids : boolean;
    m_bit19 : boolean;
    m_bit20 : boolean;
    m_bit21 : boolean;
    m_bit22 : boolean;
    m_bit23 : boolean;
    m_bit24 : boolean;
    m_bit25 : boolean;
    m_bit26 : boolean;
    m_bit27 : boolean;
    m_bit28 : boolean;
    m_bit29 : boolean;
    m_bit30 : boolean;
    m_bit31 : boolean;
}
class ScenarioClass
{
    static UpdateCellLighting() : void;
    static UpdateLighting() : void;
    static UpdateHashPalLighting(R_0 : number, G_1 : number, B_2 : number, tint_3 : boolean) : void;
    static ScenarioLighting(r_0 : number, g_1 : number, b_2 : number) : void;
    static RecalcLighting(R_0 : number, G_1 : number, B_2 : number, tint_3 : boolean) : void;
    static SaveGame(FileName_0 : string, Description_1 : any, BarGraph_2 : boolean) : boolean;
    static LoadGame(FileName_0 : string) : boolean;
    static StartScenario(FileName_0 : string, Briefing_1 : boolean, CampaignIndex_2 : number) : boolean;
    static AssignHouses() : void;
    ReadStartPoints(ini_0 : INIClass) : void;
    IsDefinedWaypoint(idx_0 : number) : boolean;
    GetWaypointCoords(dest_0 : any, idx_1 : number) : any;
    GetWaypointCoords(idx_0 : number) : any;
    s_Instance : any;
    s_NewINIFormat : any;
    s_LastTheater : any;
    m_SpecialFlags : ScenarioFlags;
    m_NextScenario : number;
    m_AltNextScenario : number;
    m_HomeCell : number;
    m_AltHomeCell : number;
    m_UniqueID : number;
    m_Random : Randomizer;
    m_Difficulty1 : number;
    m_Difficulty2 : number;
    m_ElapsedTimer : CDTimerClass;
    m_PauseTimer : CDTimerClass;
    m_unknown_62C : number;
    m_IsGamePaused : boolean;
    m_Waypoints : any;
    m_StartX : number;
    m_StartY : number;
    m_Width : number;
    m_Height : number;
    m_NumberStartingPoints : number;
    m_StartingPoints : any;
    m_HouseIndices : number;
    m_HouseHomeCells : any;
    m_TeamsPresent : boolean;
    m_NumCoopHumanStartSpots : number;
    m_MissionTimer : CDTimerClass;
    m_MissionTimerTextCSF : any;
    m_MissionTimerText : number;
    m_ShroudRegrowTimer : CDTimerClass;
    m_FogTimer : CDTimerClass;
    m_IceTimer : CDTimerClass;
    m_unknown_timer_123c : CDTimerClass;
    m_AmbientTimer : CDTimerClass;
    m_TechLevel : number;
    m_Theater : any;
    m_FileName : number;
    m_Name : any;
    m_UIName : number;
    m_UINameLoaded : any;
    m_Intro : string;
    m_Brief : string;
    m_Win : string;
    m_Lose : string;
    m_Action : string;
    m_PostScore : string;
    m_PreMapSelect : string;
    m_Briefing : any;
    m_BriefingCSF : number;
    m_ThemeIndex : number;
    m_HumanPlayerHouseTypeIndex : number;
    m_CarryOverMoney : number;
    m_CarryOverCap : number;
    m_Percent : number;
    m_GlobalVariables : any;
    m_LocalVariables : any;
    m_View1 : any;
    m_View2 : any;
    m_View3 : any;
    m_View4 : any;
    m_unknown_34A0 : number;
    m_FreeRadar : boolean;
    m_TrainCrate : boolean;
    m_TiberiumGrowthEnabled : boolean;
    m_VeinGrowthEnabled : boolean;
    m_IceGrowthEnabled : boolean;
    m_BridgeDestroyed : boolean;
    m_VariablesChanged : boolean;
    m_AmbientChanged : boolean;
    m_EndOfGame : boolean;
    m_TimerInherit : boolean;
    m_SkipScore : boolean;
    m_OneTimeOnly : boolean;
    m_SkipMapSelect : boolean;
    m_TruckCrate : boolean;
    m_FillSilos : boolean;
    m_TiberiumDeathToVisceroid : boolean;
    m_IgnoreGlobalAITriggers : boolean;
    m_unknown_bool_34B5 : boolean;
    m_unknown_bool_34B6 : boolean;
    m_unknown_bool_34B7 : boolean;
    m_PlayerSideIndex : number;
    m_MultiplayerOnly : boolean;
    m_IsRandom : boolean;
    m_PickedUpAnyCrate : boolean;
    m_unknown_timer_34C0 : CDTimerClass;
    m_CampaignIndex : number;
    m_StartingDropships : number;
    m_AllowableUnits : any;
    m_AllowableUnitMaximums : any;
    m_DropshipUnitCounts : any;
    m_AmbientOriginal : number;
    m_AmbientCurrent : number;
    m_AmbientTarget : number;
    m_NormalLighting : LightingStruct;
    m_IonAmbient : number;
    m_IonLighting : LightingStruct;
    m_NukeAmbient : number;
    m_NukeLighting : LightingStruct;
    m_NukeAmbientChangeRate : number;
    m_DominatorAmbient : number;
    m_DominatorLighting : LightingStruct;
    m_DominatorAmbientChangeRate : number;
    m_unknown_3598 : number;
    m_InitTime : number;
    m_Stage : number;
    m_UserInputLocked : boolean;
    m_unknown_35A3 : boolean;
    m_ParTimeEasy : number;
    m_ParTimeMedium : number;
    m_ParTimeDifficult : number;
    m_UnderParTitle : number;
    m_UnderParMessage : number;
    m_OverParTitle : number;
    m_OverParMessage : number;
    m_LSLoadMessage : number;
    m_LSBrief : number;
    m_LS640BriefLocX : number;
    m_LS640BriefLocY : number;
    m_LS800BriefLocX : number;
    m_LS800BriefLocY : number;
    m_LS640BkgdName : number;
    m_LS800BkgdName : number;
    m_LS800BkgdPal : number;
}
class OverlayClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    static GetTiberiumType(overlayTypeIndex_0 : number) : number;
    s_AbsID : any;
    s_Array : any;
    m_Type : OverlayTypeClass;
}
class GScreenClass
{
    static DoBlit(mouseCaptured_0 : boolean, surface_1 : any, rect_2 : any) : void;
    QueryInterface(iid_0 : any, ppvObject_1 : void) : number;
    AddRef() : number;
    Release() : number;
    One_Time() : void;
    Init() : void;
    Init_Clear() : void;
    Init_IO() : void;
    GetInputAndUpdate(outKeyCode_0 : number, outMouseX_1 : number, outMouseY_2 : number) : void;
    Update(keyCode_0 : number, mouseCoords_1 : any) : void;
    SetButtons(pGadget_0 : GadgetClass) : boolean;
    AddButton(pGadget_0 : GadgetClass) : boolean;
    RemoveButton(pGadget_0 : GadgetClass) : boolean;
    MarkNeedsRedraw(dwUnk_0 : number) : void;
    DrawOnTop() : void;
    Draw(dwUnk_0 : number) : void;
    vt_entry_44() : void;
    SetCursor(idxCursor_0 : any, miniMap_1 : boolean) : boolean;
    UpdateCursor(idxCursor_0 : any, miniMap_1 : boolean) : boolean;
    RestoreCursor() : boolean;
    UpdateCursorMinimapState(miniMap_0 : boolean) : void;
    Render() : void;
    s_Instance : any;
    m_ScreenShakeX : number;
    m_ScreenShakeY : number;
    m_Bitfield : number;
}
class Crate
{
    m_CrateTimer : CDTimerClass;
    m_Location : any;
}
class LayerClass
{
    AddObject(pObject_0 : ObjectClass, sorted_1 : boolean) : boolean;
    RemoveAll() : void;
    vt_entry_24() : void;
    Load(pStm_0 : any) : void;
    Save(pStm_0 : any) : void;
    Sort() : void;
}
class LogicClass
    extends LayerClass
{
    AddObject(pObject_0 : ObjectClass, sorted_1 : boolean) : boolean;
    PointerGotInvalid(pInvalid_0 : AbstractClass, removed_1 : boolean) : void;
    RemoveObject(pObject_0 : ObjectClass) : void;
    Update() : void;
}
class MapClass
    extends GScreenClass
{
    static GetLayer(lyr_0 : any) : LayerClass;
    Is_Visible(cell_0 : any) : number;
    AllocateCells() : void;
    DestructCells() : void;
    ConstructCells() : void;
    PointerGotInvalid(ptr_0 : AbstractClass, bUnk_1 : boolean) : void;
    DraggingInProgress() : boolean;
    UpdateCrates() : void;
    CreateEmptyMap(mapRect_0 : any, reuse_1 : boolean, nLevel_2 : number, bUnk2_3 : boolean) : void;
    SetVisibleRect(mapRect_0 : any) : void;
    TryGetCellAt(MapCoords_0 : any) : CellClass;
    TryGetCellAt(Crd_0 : any) : CellClass;
    GetCellAt(MapCoords_0 : any) : CellClass;
    GetCellAt(Crd_0 : any) : CellClass;
    GetTargetCell(location_0 : any) : CellClass;
    CellExists(MapCoords_0 : any) : boolean;
    GetThreatPosed(cell_0 : any, pHouse_1 : HouseClass) : number;
    IsLocationShrouded(crd_0 : any) : boolean;
    static GetCellIndex(MapCoords_0 : any) : number;
    static GetRandomCoordsNear(outBuffer_0 : any, coords_1 : any, distance_2 : number, center_3 : boolean) : any;
    static GetRandomCoordsNear(coords_0 : any, distance_1 : number, center_2 : boolean) : any;
    static PickInfantrySublocation(outBuffer_0 : any, coords_1 : any, ignoreContents_2 : boolean) : any;
    static PickInfantrySublocation(coords_0 : any, ignoreContents_1 : boolean) : any;
    static UnselectAll() : void;
    CenterMap() : void;
    CellIteratorReset() : void;
    CellIteratorNext() : CellClass;
    GetMovementZoneType(MapCoords_0 : any, movementZone_1 : any, isBridge_2 : boolean) : number;
    static DamageArea(Coords_0 : any, Damage_1 : number, SourceObject_2 : TechnoClass, WH_3 : WarheadTypeClass, AffectsTiberium_4 : boolean, SourceHouse_5 : HouseClass) : any;
    static SelectDamageAnimation(Damage_0 : number, WH_1 : WarheadTypeClass, LandType_2 : any, coords_3 : any) : AnimTypeClass;
    static FlashbangWarheadAt(Damage_0 : number, WH_1 : WarheadTypeClass, coords_2 : any, Force_3 : boolean, CLDisableFlags_4 : any) : void;
    static GetTotalDamage(damage_0 : number, pWarhead_1 : WarheadTypeClass, armor_2 : any, distance_3 : number) : number;
    GetCellFloorHeight(crd_0 : any) : number;
    PickCellOnEdge(buffer_0 : any, Edge_1 : any, CurrentLocation_2 : any, Fallback_3 : any, SpeedType_4 : any, ValidateReachability_5 : boolean, MovZone_6 : any) : any;
    PickCellOnEdge(Edge_0 : any, CurrentLocation_1 : any, Fallback_2 : any, SpeedType_3 : any, ValidateReachability_4 : boolean, MovZone_5 : any) : any;
    Update_Pathfinding_1() : void;
    Update_Pathfinding_2(where_0 : any) : void;
    NearByLocation(outBuffer_0 : any, position_1 : any, SpeedType_2 : any, a5_3 : number, MovementZone_4 : any, alt_5 : boolean, SpaceSizeX_6 : number, SpaceSizeY_7 : number, disallowOverlay_8 : boolean, a11_9 : boolean, requireBurrowable_10 : boolean, allowBridge_11 : boolean, closeTo_12 : any, a15_13 : boolean, buildable_14 : boolean) : any;
    NearByLocation(position_0 : any, SpeedType_1 : any, a5_2 : number, MovementZone_3 : any, alt_4 : boolean, SpaceSizeX_5 : number, SpaceSizeY_6 : number, disallowOverlay_7 : boolean, a11_8 : boolean, requireBurrowable_9 : boolean, allowBridge_10 : boolean, closeTo_11 : any, a15_12 : boolean, buildable_13 : boolean) : any;
    AddContentAt(coords_0 : any, Content_1 : TechnoClass) : void;
    RemoveContentAt(coords_0 : any, Content_1 : TechnoClass) : void;
    IsWithinUsableArea(cell_0 : any, checkLevel_1 : boolean) : boolean;
    IsWithinUsableArea(pCell_0 : CellClass, checkLevel_1 : boolean) : boolean;
    IsWithinUsableArea(coords_0 : any) : boolean;
    CoordinatesLegal(cell_0 : any) : boolean;
    IsLinkedBridgeDestroyed(cell_0 : any) : boolean;
    PlacePowerupCrate(cell_0 : any, type_1 : any) : boolean;
    FindFirstFirestorm(pOutBuffer_0 : any, start_1 : any, end_2 : any, pHouse_3 : HouseClass) : any;
    FindFirstFirestorm(start_0 : any, end_1 : any, pHouse_2 : HouseClass) : any;
    RevealArea1(Coords_0 : any, Radius_1 : number, OwnerHouse_2 : HouseClass, arg4_3 : any, RevealByHeight_4 : number, arg6_5 : number, arg7_6 : number, arg8_7 : number) : void;
    RevealArea2(Coords_0 : any, Radius_1 : number, OwnerHouse_2 : HouseClass, arg4_3 : number, RevealByHeight_4 : number, arg6_5 : number, arg7_6 : number, arg8_7 : number) : void;
    RevealArea3(Coords_0 : any, Height_1 : number, Radius_2 : number, SkipReveal_3 : boolean) : void;
    Reveal(pHouse_0 : HouseClass) : void;
    Reshroud(pHouse_0 : HouseClass) : void;
    GetZPos(Coords_0 : any) : number;
    sub_657CE0() : void;
    RedrawSidebar(mode_0 : number) : void;
    NextObject(pCurrentObject_0 : ObjectClass) : ObjectClass;
    SetTogglePowerMode(mode_0 : number) : void;
    SetPlaceBeaconMode(mode_0 : number) : void;
    SetSellMode(mode_0 : number) : void;
    SetWaypointMode(mode_0 : number, somebool_1 : boolean) : void;
    SetRepairMode(mode_0 : number) : void;
    DestroyCliff(Cell_0 : CellClass) : void;
    IsLocationFogged(coord_0 : any) : boolean;
    RevealCheck(pCell_0 : CellClass, pHouse_1 : HouseClass, bUnk_2 : boolean) : void;
    MakeTraversable(pVisitor_0 : ObjectClass, cell_1 : any) : boolean;
    BuildingToFirestormWall(cell_0 : any, pHouse_1 : HouseClass, pBldType_2 : BuildingTypeClass) : void;
    BuildingToWall(cell_0 : any, pHouse_1 : HouseClass, pBldType_2 : BuildingTypeClass) : void;
    RecalculateZones(cell_0 : any) : void;
    ResetZones(cell_0 : any) : void;
    RecalculateSubZones(cell_0 : any) : void;
    s_Instance : any;
    s_InvalidCell : any;
    s_MaxCells : number;
    s_Logics : any;
    s_ObjectsInLayers : any;
    s_MovementAdjustArray : any;
    m_unknown_10 : number;
    m_unknown_pointer_14 : void;
    m_MovementZones : void;
    m_somecount_4C : number;
    m_ZoneConnections : any;
    m_LevelAndPassability : any;
    m_ValidMapCellCount : number;
    m_LevelAndPassabilityStruct2pointer_70 : any;
    m_unknown_74 : number;
    m_unknown_78 : number;
    m_unknown_7C : number;
    m_unknown_80 : number;
    m_SubzoneTracking1 : any;
    m_SubzoneTracking2 : any;
    m_SubzoneTracking3 : any;
    m_CellStructs1 : any;
    m_MapRect : any;
    m_VisibleRect : any;
    m_CellIterator_NextX : number;
    m_CellIterator_NextY : number;
    m_CellIterator_CurrentY : number;
    m_CellIterator_NextCell : CellClass;
    m_ZoneIterator_X : number;
    m_ZoneIterator_Y : number;
    m_MapCoordBounds : LTRBStruct;
    m_TotalValue : number;
    m_Cells : any;
    m_MaxLevel : number;
    m_MaxWidth : number;
    m_MaxHeight : number;
    m_MaxNumCells : number;
    m_Crates : Crate;
    m_Redraws : number;
    m_TaggedCells : any;
}
class DisplayClass
    extends MapClass
{
    ProcessClickCoords(src_0 : any, XYdst_1 : any, XYZdst_2 : any, Target_3 : ObjectClass, a5_4 : number, a6_5 : number) : boolean;
    SetActiveFoundation(Coords_0 : any) : void;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any) : number;
    LoadFromINI(pINI_0 : CCINIClass) : void;
    GetToolTip(nDlgID_0 : number) : any;
    CloseWindow() : void;
    vt_entry_8C() : void;
    MapCell(pMapCoord_0 : any, pHouse_1 : HouseClass) : boolean;
    RevealFogShroud(pMapCoord_0 : any, pHouse_1 : HouseClass, bIncreaseShroudCounter_2 : boolean) : boolean;
    MapCellFoggedness(pMapCoord_0 : any, pHouse_1 : HouseClass) : boolean;
    MapCellVisibility(pMapCoord_0 : any, pHouse_1 : HouseClass) : boolean;
    GetLastMouseCursor() : any;
    ScrollMap(dwUnk1_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : boolean;
    Set_View_Dimensions(rect_0 : any) : void;
    vt_entry_AC(dwUnk_0 : number) : void;
    vt_entry_B0(dwUnk_0 : number) : void;
    vt_entry_B4(pPoint_0 : any) : void;
    ConvertAction(cell_0 : any, bShrouded_1 : boolean, pObject_2 : ObjectClass, action_3 : any, dwUnk_4 : boolean) : boolean;
    LeftMouseButtonDown(point_0 : any) : void;
    LeftMouseButtonUp(coords_0 : any, cell_1 : any, pObject_2 : ObjectClass, action_3 : any, dwUnk2_4 : number) : void;
    RightMouseButtonUp(dwUnk_0 : number) : void;
    DecideAction(cell_0 : any, pObject_1 : ObjectClass, dwUnk_2 : number) : any;
    FoundationBoundsSize(outBuffer_0 : any, pFoundationData_1 : any) : any;
    FoundationBoundsSize(pFoundationData_0 : any) : any;
    MarkFoundation(BaseCell_0 : any, Mark_1 : boolean) : void;
    Submit(pObject_0 : ObjectClass) : void;
    Remove(pObject_0 : ObjectClass) : void;
    s_Instance : any;
    m_CurrentFoundation_CenterCell : any;
    m_CurrentFoundation_TopLeftOffset : any;
    m_CurrentFoundation_Data : any;
    m_unknown_1180 : boolean;
    m_unknown_1181 : boolean;
    m_CurrentFoundationCopy_CenterCell : any;
    m_CurrentFoundationCopy_TopLeftOffset : any;
    m_CurrentFoundationCopy_Data : any;
    m_unknown_1190 : number;
    m_unknown_1194 : number;
    m_unknown_1198 : number;
    m_FollowObject : boolean;
    m_ObjectToFollow : ObjectClass;
    m_CurrentBuilding : ObjectClass;
    m_CurrentBuildingType : ObjectTypeClass;
    m_unknown_11AC : number;
    m_RepairMode : boolean;
    m_SellMode : boolean;
    m_PowerToggleMode : boolean;
    m_PlanningMode : boolean;
    m_PlaceBeaconMode : boolean;
    m_CurrentSWTypeIndex : number;
    m_unknown_11BC : number;
    m_unknown_11C0 : number;
    m_unknown_11C4 : number;
    m_unknown_11C8 : number;
    m_unknown_bool_11CC : boolean;
    m_unknown_bool_11CD : boolean;
    m_unknown_bool_11CE : boolean;
    m_DraggingRectangle : boolean;
    m_unknown_bool_11D0 : boolean;
    m_unknown_bool_11D1 : boolean;
    m_unknown_11D4 : number;
    m_unknown_11D8 : number;
    m_unknown_11DC : number;
    m_unknown_11E0 : number;
}
enum DirType {
    North = 0,
    NorthEast = 32,
    East = 64,
    SouthEast = 96,
    South = -128,
    SouthWest = -96,
    West = -64,
    NorthWest = -32,
    Max = -1,
}
enum AbstractFlags {
    None = 0,
    Techno = 1,
    Object = 2,
    Foot = 4,
}
enum AbstractType {
    None = 0,
    Unit = 1,
    Aircraft = 2,
    AircraftType = 3,
    Anim = 4,
    AnimType = 5,
    Building = 6,
    BuildingType = 7,
    Bullet = 8,
    BulletType = 9,
    Campaign = 10,
    Cell = 11,
    Factory = 12,
    House = 13,
    HouseType = 14,
    Infantry = 15,
    InfantryType = 16,
    Isotile = 17,
    IsotileType = 18,
    BuildingLight = 19,
    Overlay = 20,
    OverlayType = 21,
    Particle = 22,
    ParticleType = 23,
    ParticleSystem = 24,
    ParticleSystemType = 25,
    Script = 26,
    ScriptType = 27,
    Side = 28,
    Smudge = 29,
    SmudgeType = 30,
    Special = 31,
    SuperWeaponType = 32,
    TaskForce = 33,
    Team = 34,
    TeamType = 35,
    Terrain = 36,
    TerrainType = 37,
    Trigger = 38,
    TriggerType = 39,
    UnitType = 40,
    VoxelAnim = 41,
    VoxelAnimType = 42,
    Wave = 43,
    Tag = 44,
    TagType = 45,
    Tiberium = 46,
    Action = 47,
    Event = 48,
    WeaponType = 49,
    WarheadType = 50,
    Waypoint = 51,
    Abstract = 52,
    Tube = 53,
    LightSource = 54,
    EMPulse = 55,
    TacticalMap = 56,
    Super = 57,
    AITrigger = 58,
    AITriggerType = 59,
    Neuron = 60,
    FoggedObject = 61,
    AlphaShape = 62,
    VeinholeMonster = 63,
    NavyType = 64,
    SpawnManager = 65,
    CaptureManager = 66,
    Parasite = 67,
    Bomb = 68,
    RadSite = 69,
    Temporal = 70,
    Airstrike = 71,
    SlaveManager = 72,
    DiskLaser = 73,
}
enum RecordFlag {
    Write = 1,
    Read = 2,
    Attract = 4,
}
enum Action {
    None = 0,
    Move = 1,
    NoMove = 2,
    Enter = 3,
    Self_Deploy = 4,
    Attack = 5,
    Harvest = 6,
    Select = 7,
    ToggleSelect = 8,
    Capture = 9,
    Eaten = 10,
    Repair = 11,
    Sell = 12,
    SellUnit = 13,
    NoSell = 14,
    NoRepair = 15,
    Sabotage = 16,
    Tote = 17,
    DontUse2 = 18,
    DontUse3 = 19,
    Nuke = 20,
    DontUse4 = 21,
    DontUse5 = 22,
    DontUse6 = 23,
    DontUse7 = 24,
    DontUse8 = 25,
    GuardArea = 26,
    Heal = 27,
    Damage = 28,
    GRepair = 29,
    NoDeploy = 30,
    NoEnter = 31,
    NoGRepair = 32,
    TogglePower = 33,
    NoTogglePower = 34,
    EnterTunnel = 35,
    NoEnterTunnel = 36,
    IronCurtain = 37,
    LightningStorm = 38,
    ChronoSphere = 39,
    ChronoWarp = 40,
    ParaDrop = 41,
    PlaceWaypoint = 42,
    TibSunBug = 43,
    EnterWaypointMode = 44,
    FollowWaypoint = 45,
    SelectWaypoint = 46,
    LoopWaypointPath = 47,
    DragWaypoint = 48,
    AttackWaypoint = 49,
    EnterWaypoint = 50,
    PatrolWaypoint = 51,
    AreaAttack = 52,
    IvanBomb = 53,
    NoIvanBomb = 54,
    Detonate = 55,
    DetonateAll = 56,
    DisarmBomb = 57,
    SelectNode = 58,
    AttackSupport = 59,
    PlaceBeacon = 60,
    SelectBeacon = 61,
    AttackMoveNav = 62,
    AttackMoveTar = 63,
    Demolish = 64,
    AmerParaDrop = 65,
    PsychicDominator = 66,
    SpyPlane = 67,
    GeneticConverter = 68,
    ForceShield = 69,
    NoForceShield = 70,
    Airstrike = 71,
    PsychicReveal = 72,
}
enum Ability {
    Faster = 0,
    Stronger = 1,
    Firepower = 2,
    Scatter = 3,
    ROF = 4,
    Sight = 5,
    Cloak = 6,
    TiberiumProof = 7,
    VeinProof = 8,
    SelfHeal = 9,
    Explodes = 10,
    RadarInvisible = 11,
    Sensors = 12,
    Fearless = 13,
    C4 = 14,
    TiberiumHeal = 15,
    GuardArea = 16,
    Crusher = 17,
}
enum AIDifficulty {
    Hard = 0,
    Normal = 1,
    Easy = 2,
}
enum TextPrintType {
    LASTPOINT = 0,
    LASTSHADOW = 0,
    Point6 = 1,
    Point8 = 2,
    Point3 = 3,
    Led = 4,
    Vcr = 5,
    Point6Grad = 6,
    Map = 7,
    Metal12 = 8,
    Efnt = 9,
    Type = 10,
    Score = 11,
    Fonts = 15,
    NoShadow = 16,
    DropShadow = 32,
    FullShadow = 64,
    LightShadow = 128,
    Center = 256,
    Right = 512,
    Background = 1024,
    MediumColor = 4096,
    BrightColor = 8192,
    UseGradPal = 16384,
    UnknownColor = 32768,
    GradAll = 61440,
}
enum TriggerPersistence {
    Volatile = 0,
    SemiPersistant = 1,
    Persistent = 2,
}
enum TriggerEvent {
    None = 0,
    EnteredBy = 1,
    SpiedBy = 2,
    ThievedBy = 3,
    DiscoveredByPlayer = 4,
    HouseDiscovered = 5,
    AttackedByAnybody = 6,
    DestroyedByAnybody = 7,
    AnyEvent = 8,
    DestroyedUnitsAll = 9,
    DestroyedBuildingsAll = 10,
    DestroyedAll = 11,
    CreditsExceed = 12,
    ElapsedTime = 13,
    MissionTimerExpired = 14,
    DestroyedBuildingsNum = 15,
    DestroyedUnitsNum = 16,
    NoFactoriesLeft = 17,
    CiviliansEvacuated = 18,
    BuildBuildingType = 19,
    BuildUnitType = 20,
    BuildInfantryType = 21,
    BuildAircraftType = 22,
    TeamLeavesMap = 23,
    ZoneEntryBy = 24,
    CrossesHorizontalLine = 25,
    CrossesVerticalLine = 26,
    GlobalSet = 27,
    GlobalCleared = 28,
    DestroyedFakesAll = 29,
    LowPower = 30,
    AllBridgesDestroyed = 31,
    BuildingExists = 32,
    SelectedByPlayer = 33,
    ComesNearWaypoint = 34,
    EnemyInSpotlight = 35,
    LocalSet = 36,
    LocalCleared = 37,
    FirstDamaged_combatonly = 38,
    HalfHealth_combatonly = 39,
    QuarterHealth_combatonly = 40,
    FirstDamaged_anysource = 41,
    HalfHealth_anysource = 42,
    QuarterHealth_anysource = 43,
    AttackedByHouse = 44,
    AmbientLightBelow = 45,
    AmbientLightAbove = 46,
    ElapsedScenarioTime = 47,
    DestroyedByAnything = 48,
    PickupCrate = 49,
    PickupCrate_any = 50,
    RandomDelay = 51,
    CreditsBelow = 52,
    SpyAsHouse = 53,
    SpyAsInfantry = 54,
    DestroyedUnitsNaval = 55,
    DestroyedUnitsLand = 56,
    BuildingDoesNotExist = 57,
    PowerFull = 58,
    EnteredOrOverflownBy = 59,
    TechTypeExists = 60,
    TechTypeDoesntExist = 61,
}
enum TriggerAction {
    None = 0,
    Win = 1,
    Lose = 2,
    ProductionBegins = 3,
    CreateTeam = 4,
    DestroyTeam = 5,
    AllToHunt = 6,
    Reinforcement = 7,
    DropZoneFlare = 8,
    FireSale = 9,
    PlayMovie = 10,
    TextTrigger = 11,
    DestroyTrigger = 12,
    AutocreateBegins = 13,
    ChangeHouse = 14,
    AllowWin = 15,
    RevealAllMap = 16,
    RevealAroundWaypoint = 17,
    RevealWaypointZone = 18,
    PlaySoundEffect = 19,
    PlayMusicTheme = 20,
    PlaySpeech = 21,
    ForceTrigger = 22,
    TimerStart = 23,
    TimerStop = 24,
    TimerExtend = 25,
    TimerShorten = 26,
    TimerSet = 27,
    GlobalSet = 28,
    GlobalClear = 29,
    AutoBaseBuilding = 30,
    GrowShroud = 31,
    DestroyAttachedObject = 32,
    AddOneTimeSuperWeapon = 33,
    AddRepeatingSuperWeapon = 34,
    PreferredTarget = 35,
    AllChangeHouse = 36,
    MakeAlly = 37,
    MakeEnemy = 38,
    ChangeZoomLevel = 39,
    ResizePlayerView = 40,
    PlayAnimAt = 41,
    DoExplosionAt = 42,
    CreateVoxelAnim = 43,
    IonStormStart = 44,
    IonStormStop = 45,
    LockInput = 46,
    UnlockInput = 47,
    MoveCameraToWaypoint = 48,
    ZoomIn = 49,
    ZoomOut = 50,
    ReshroudMap = 51,
    ChangeLightBehavior = 52,
    EnableTrigger = 53,
    DisableTrigger = 54,
    CreateRadarEvent = 55,
    LocalSet = 56,
    LocalClear = 57,
    MeteorShower = 58,
    ReduceTiberium = 59,
    SellBuilding = 60,
    TurnOffBuilding = 61,
    TurnOnBuilding = 62,
    Apply100Damage = 63,
    SmallLightFlash = 64,
    MediumLightFlash = 65,
    LargeLightFlash = 66,
    AnnounceWin = 67,
    AnnounceLose = 68,
    ForceEnd = 69,
    DestroyTag = 70,
    SetAmbientStep = 71,
    SetAmbientRate = 72,
    SetAmbientLight = 73,
    AITriggersBegin = 74,
    AITriggersStop = 75,
    RatioOfAITriggerTeams = 76,
    RatioOfTeamAircraft = 77,
    RatioOfTeamInfantry = 78,
    RatioOfTeamUnits = 79,
    ReinforcementAt = 80,
    WakeupSelf = 81,
    WakeupAllSleepers = 82,
    WakeupAllHarmless = 83,
    WakeupGroup = 84,
    VeinGrowth = 85,
    TiberiumGrowth = 86,
    IceGrowth = 87,
    ParticleAnim = 88,
    RemoveParticleAnim = 89,
    LightningStrike = 90,
    GoBerzerk = 91,
    ActivateFirestorm = 92,
    DeactivateFirestorm = 93,
    IonCannonStrike = 94,
    NukeStrike = 95,
    ChemMissileStrike = 96,
    ToggleTrainCargo = 97,
    PlaySoundEffectRandom = 98,
    PlaySoundEffectAtWaypoint = 99,
    PlayIngameMovie = 100,
    ReshroudMapAtWaypoint = 101,
    LightningStormStrike = 102,
    TimerText = 103,
    FlashTeam = 104,
    TalkBubble = 105,
    SetObjectTechLevel = 106,
    ReinforcementByChrono = 107,
    CreateCrate = 108,
    IronCurtain = 109,
    PauseGame = 110,
    EvictOccupiers = 111,
    CenterCameraAtWaypoint = 112,
    MakeHouseCheer = 113,
    SetTabTo = 114,
    FlashCameo = 115,
    StopSounds = 116,
    PlayIngameMovieAndPause = 117,
    ClearAllSmudges = 118,
    DestroyAll = 119,
    DestroyAllBuildings = 120,
    DestroyAllLandUnits = 121,
    DestroyAllNavalUnits = 122,
    MindControlBase = 123,
    RestoreMindControlledBase = 124,
    CreateBuilding = 125,
    RestoreStartingUnits = 126,
    StartChronoScreenEffect = 127,
    TeleportAll = 128,
    SetSuperWeaponCharge = 129,
    RestoreStartingBuildings = 130,
    FlashBuildingsOfType = 131,
    SuperWeaponSetRechargeTime = 132,
    SuperWeaponResetRechargeTime = 133,
    SuperWeaponReset = 134,
    SetPreferredTargetCell = 135,
    ClearPreferredTargetCell = 136,
    SetBaseCenterCell = 137,
    ClearBaseCenterCell = 138,
    BlackoutRadar = 139,
    SetDefensiveTargetCell = 140,
    ClearDefensiveTargetCell = 141,
    RetintRed = 142,
    RetintGreen = 143,
    RetintBlue = 144,
    JumpCameraHome = 145,
}
enum TriggerAttachType {
    Global = 1,
    Object = 2,
    Map = 4,
    House = 8,
    Logic = 16,
}
enum LogicNeedType {
    None = 0,
    Theme = 1,
    Movie = 2,
    Sound = 3,
    Speech = 4,
    Infantry = 5,
    Unit = 6,
    Aircraft = 7,
    Structure = 8,
    Waypoint = 9,
    Number = 10,
    Trigger = 11,
    Team = 12,
    House = 13,
    Time = 14,
    Quarry = 15,
    Bool = 16,
    Special = 17,
    Mission = 18,
    Cell = 19,
    Script = 20,
    Rectangle = 21,
    Global = 22,
    AnimNWaypoint = 23,
    WaypointNWeapon = 24,
    LightBehavior = 25,
    Tag = 26,
    MeteorSize = 27,
    RadarEventNWaypoint = 28,
    Local = 29,
    VelocityNWaypoint = 30,
    ShowerNWaypoint = 31,
    Velocity = 32,
    Float = 33,
    TeamNWaypoint = 34,
    ParticleNWaypoint = 35,
    BuildingNProperty = 36,
    SplitType = 37,
    SoundNWaypoint = 38,
    Text = 39,
    Team2 = 40,
    Anim = 41,
    SpeechBubble = 42,
    NumberNTech = 43,
    CrateNWaypoint = 44,
    BuildingNWaypoint = 45,
    NumberNSuper = 46,
    BuildingNNumber = 47,
}
enum AIMode {
    General = 0,
    LowOnCash = 1,
    BuildBase = 3,
    SellAll = 4,
}
enum AITriggerCondition {
    Pool = -1,
    AIOwns = 0,
    EnemyOwns = 1,
    EnemyYellowPowe = 2,
    EnemyRedPower = 3,
    EnemyCashExceeds = 4,
    IronCharged = 5,
    ChronoCharged = 6,
    NeutralOwns = 7,
}
enum AITriggerHouseType {
    None = 0,
    Single = 1,
    Any = 2,
}
enum Armor {
    None = 0,
    Flak = 1,
    Plate = 2,
    Light = 3,
    Medium = 4,
    Heavy = 5,
    Wood = 6,
    Steel = 7,
    Concrete = 8,
    Special_1 = 9,
    Special_2 = 10,
}
enum SpotlightBehaviour {
    None = 0,
    Sweep = 1,
    Circle = 2,
    Follow = 3,
}
enum SpotlightFlags {
    None = 0,
    NoColor = 1,
    NoRed = 2,
    NoGreen = 4,
    NoBlue = 8,
}
enum BehavesLike {
    Smoke = 0,
    Gas = 1,
    Fire = 2,
    Spark = 3,
    Railgun = 4,
}
enum ParticleSystemHoldsWhat {
    Gas = 0,
    Smoke = 1,
    Fire = 2,
    Spark = 3,
    Railgun = 4,
}
enum BuildCat {
    DontCare = 0,
    Tech = 1,
    Resoure = 2,
    Power = 3,
    Infrastructure = 4,
    Combat = 5,
}
enum BuildingAnimSlot {
    All = -2,
    None = -1,
    Upgrade1 = 0,
    Upgrade2 = 1,
    Upgrade3 = 2,
    Active = 3,
    ActiveTwo = 4,
    ActiveThree = 5,
    ActiveFour = 6,
    PreProduction = 7,
    Production = 8,
    Turret = 9,
    Special = 10,
    SpecialTwo = 11,
    SpecialThree = 12,
    SpecialFour = 13,
    Super = 14,
    SuperTwo = 15,
    SuperThree = 16,
    SuperFour = 17,
    Idle = 18,
    LowPower = 19,
    SuperLowPower = 20,
}
enum Category {
    Invalid = -1,
    Soldier = 0,
    Civilian = 1,
    VIP = 2,
    Recon = 3,
    AFV = 4,
    IFV = 5,
    LRFS = 6,
    Support = 7,
    Transport = 8,
    AirPower = 9,
    AirLift = 10,
}
enum CellFlags {
    Empty = 0,
    CenterRevealed = 1,
    EdgeRevealed = 2,
    IsWaypoint = 4,
    Explored = 8,
    FlagPresent = 16,
    FlagToShroud = 32,
    IsPlot = 64,
    BridgeOwner = 128,
    BridgeHead = 256,
    Unknown_200 = 512,
    BridgeBody = 1024,
    BridgeDir = 2048,
    PixelFX = 4096,
    Unknown_2000 = 8192,
    Unknown_4000 = 16384,
    Veinhole = 32768,
    DrawDarkenIfInAir = 65536,
    AnimAttached = 131072,
    Tube = 262144,
    EMPPresent = 524288,
    HorizontalLineEventTag = 1048576,
    VerticalLineEventTag = 2097152,
    Fogged = 4194304,
    Revealed = 3,
    Bridge = 1280,
}
enum AltCellFlags {
    Unknown_1 = 1,
    ContainsBuilding = 2,
    Unknown_4 = 4,
    Mapped = 8,
    NoFog = 16,
    Unknown_20 = 32,
    Unknown_40 = 64,
    Unknown_80 = 128,
    Unknown_100 = 256,
    Clear = 24,
}
enum PassabilityType {
    Passable = 0,
    Crushable = 1,
    Destroyable = 2,
    Beach = 3,
    Water = 4,
    HasFreeSpots = 5,
    Impassable = 6,
    OutsideMap = 7,
}
enum FacingType {
    North = 0,
    NorthEast = 1,
    East = 2,
    SouthEast = 3,
    South = 4,
    SouthWest = 5,
    West = 6,
    NorthWest = 7,
    Count = 8,
    None = -1,
}
enum CloakState {
    Uncloaked = 0,
    Cloaking = 1,
    Cloaked = 2,
    Uncloaking = 3,
}
enum DamageState {
    Unaffected = 0,
    Unchanged = 1,
    NowYellow = 2,
    NowRed = 3,
    NowDead = 4,
    PostMortem = 5,
}
enum DamageAreaResult {
    Hit = 0,
    Missed = 1,
    Nullified = 2,
}
enum KickOutResult {
    Failed = 0,
    Busy = 1,
    Succeeded = 2,
}
enum CanBuildResult {
    TemporarilyUnbuildable = -1,
    Unbuildable = 0,
    Buildable = 1,
}
enum FireError {
    NONE = -1,
    OK = 0,
    AMMO = 1,
    FACING = 2,
    REARM = 3,
    ROTATING = 4,
    ILLEGAL = 5,
    CANT = 6,
    MOVING = 7,
    RANGE = 8,
    CLOAKED = 9,
    BUSY = 10,
    MUST_DEPLOY = 11,
}
enum HealthState {
    Red = 0,
    Yellow = 1,
    Green = 2,
}
enum Foundation {
    _1x1 = 0,
    _2x1 = 1,
    _1x2 = 2,
    _2x2 = 3,
    _2x3 = 4,
    _3x2 = 5,
    _3x3 = 6,
    _3x5 = 7,
    _4x2 = 8,
    _3x3Refinery = 9,
    _1x3 = 10,
    _3x1 = 11,
    _4x3 = 12,
    _1x4 = 13,
    _1x5 = 14,
    _2x6 = 15,
    _2x5 = 16,
    _5x3 = 17,
    _4x4 = 18,
    _3x4 = 19,
    _6x4 = 20,
    _0x0 = 21,
}
enum GameMode {
    Campaign = 0,
    LAN = 3,
    Internet = 4,
    Skirmish = 5,
}
enum InfDeath {
    None = 0,
    Die1 = 1,
    Die2 = 2,
    Explode = 3,
    Flames = 4,
    Electro = 5,
    HeadPop = 6,
    Nuked = 7,
    Virus = 8,
    Mutate = 9,
    Brute = 10,
}
enum LandType {
    Clear = 0,
    Road = 1,
    Water = 2,
    Rock = 3,
    Wall = 4,
    Tiberium = 5,
    Beach = 6,
    Rough = 7,
    Ice = 8,
    Railroad = 9,
    Tunnel = 10,
    Weeds = 11,
}
enum Layer {
    None = -1,
    Underground = 0,
    Surface = 1,
    Ground = 2,
    Air = 3,
    Top = 4,
}
enum MarkType {
    Up = 0,
    Down = 1,
    Change = 2,
    ChangeRedraw = 3,
    OverlapDown = 4,
    OverlapUp = 5,
}
enum MouseHotSpotX {
    Left = 0,
    Center = 12345,
    Right = 54321,
}
enum MouseHotSpotY {
    Top = 0,
    Middle = 12345,
    Bottom = 54321,
}
enum Mission {
    None = -1,
    Sleep = 0,
    Attack = 1,
    Move = 2,
    QMove = 3,
    Retreat = 4,
    Guard = 5,
    Sticky = 6,
    Enter = 7,
    Capture = 8,
    Eaten = 9,
    Harvest = 10,
    Area_Guard = 11,
    Return = 12,
    Stop = 13,
    Ambush = 14,
    Hunt = 15,
    Unload = 16,
    Sabotage = 17,
    Construction = 18,
    Selling = 19,
    Repair = 20,
    Rescue = 21,
    Missile = 22,
    Harmless = 23,
    Open = 24,
    Patrol = 25,
    ParadropApproach = 26,
    ParadropOverfly = 27,
    Wait = 28,
    AttackMove = 29,
    SpyplaneApproach = 30,
    SpyplaneOverfly = 31,
}
enum MovementZone {
    None = -1,
    Normal = 0,
    Crusher = 1,
    Destroyer = 2,
    AmphibiousDestroyer = 3,
    AmphibiousCrusher = 4,
    Amphibious = 5,
    Subterrannean = 6,
    Infantry = 7,
    InfantryDestroyer = 8,
    Fly = 9,
    Water = 10,
    WaterBeach = 11,
    CrusherAll = 12,
}
enum PipIndex {
    Empty = 0,
    Green = 1,
    Yellow = 2,
    White = 3,
    Red = 4,
    Blue = 5,
    PersonEmpty = 6,
    PersonGreen = 7,
    PersonYellow = 8,
    PersonWhite = 9,
    PersonRed = 10,
    PersonBlue = 11,
    PersonPurple = 12,
}
enum PipScale {
    None = 0,
    Ammo = 1,
    Tiberium = 2,
    Passengers = 3,
    Power = 4,
    MindControl = 5,
}
enum Powerup {
    Money = 0,
    Unit = 1,
    HealBase = 2,
    Cloak = 3,
    Explosion = 4,
    Napalm = 5,
    Squad = 6,
    Darkness = 7,
    Reveal = 8,
    Armor = 9,
    Speed = 10,
    Firepower = 11,
    ICBM = 12,
    Invulnerability = 13,
    Veteran = 14,
    IonStorm = 15,
    Gas = 16,
    Tiberium = 17,
    Pod = 18,
}
enum Prerequisite {
    Proc = -6,
    Tech = -5,
    Radar = -4,
    Barracks = -3,
    Factory = -2,
    Power = -1,
}
enum PrismChargeState {
    Idle = 0,
    Master = 1,
    Slave = 2,
}
enum RadarEventType {
    Combat = 0,
    Noncombat = 1,
    DropZone = 2,
    BaseAttacked = 3,
    HarvesterAttacked = 4,
    EnemySensed = 5,
    UnitProduced = 6,
    UnitLost = 7,
    UnitRepaired = 8,
    BuildingInfiltrated = 9,
    BuildingCaptured = 10,
    BeaconPlaced = 11,
    SuperweaponDetected = 12,
    SuperweaponActivated = 13,
    BridgeRepaired = 14,
    GarrisonAbandoned = 15,
    AllyBaseAttacked = 16,
}
enum PsychicDominatorStatus {
    Inactive = 0,
    FirstAnim = 1,
    Fire = 2,
    SecondAnim = 3,
    Reset = 4,
    Over = 5,
}
enum NukeFlashStatus {
    Inactive = 0,
    FadeIn = 1,
    FadeOut = 2,
}
enum ChargeDrainState {
    None = -1,
    Charging = 0,
    Ready = 1,
    Draining = 2,
}
enum SuperWeaponType {
    Invalid = -1,
    Nuke = 0,
    IronCurtain = 1,
    LightningStorm = 2,
    ChronoSphere = 3,
    ChronoWarp = 4,
    ParaDrop = 5,
    AmerParaDrop = 6,
    PsychicDominator = 7,
    SpyPlane = 8,
    GeneticMutator = 9,
    ForceShield = 10,
    PsychicReveal = 11,
}
enum MouseCursorType {
    Default = 0,
    Move_N = 1,
    Move_NE = 2,
    Move_E = 3,
    Move_SE = 4,
    Move_S = 5,
    Move_SW = 6,
    Move_W = 7,
    Move_NW = 8,
    NoMove_N = 9,
    NoMove_NE = 10,
    NoMove_E = 11,
    NoMove_SE = 12,
    NoMove_S = 13,
    NoMove_SW = 14,
    NoMove_W = 15,
    NoMove_NW = 16,
    Select = 17,
    Move = 18,
    NoMove = 19,
    Attack = 20,
    AttackOutOfRange = 21,
    Protect = 22,
    DesolatorDeploy = 23,
    Cursor_18 = 24,
    Enter = 25,
    NoEnter = 26,
    Deploy = 27,
    NoDeploy = 28,
    Cursor_1D = 29,
    Sell = 30,
    SellUnit = 31,
    NoSell = 32,
    Repair = 33,
    EngineerRepair = 34,
    NoRepair = 35,
    Waypoint = 36,
    Disguise = 37,
    IvanBomb = 38,
    MindControl = 39,
    RemoveSquid = 40,
    Crush = 41,
    SpyTech = 42,
    SpyPower = 43,
    Cursor_2C = 44,
    GIDeploy = 45,
    Cursor_2E = 46,
    ParaDrop = 47,
    Cursor_30 = 48,
    CloseWaypoint = 49,
    LightningStorm = 50,
    Detonate = 51,
    Demolish = 52,
    Nuke = 53,
    Cursor_36 = 54,
    Power = 55,
    Cursor_38 = 56,
    IronCurtain = 57,
    Chronosphere = 58,
    Disarm = 59,
    Disallowed = 60,
    Scroll = 61,
    Scroll_ESW = 62,
    Scroll_SW = 63,
    Scroll_NSW = 64,
    Scroll_NW = 65,
    Scroll_NEW = 66,
    Scroll_NE = 67,
    Scroll_NES = 68,
    Scroll_ES = 69,
    Protect2 = 70,
    AttackOutOfRange2 = 71,
    Cursor_48 = 72,
    InfantryAbsorb = 73,
    NoMindControl = 74,
    Cursor_4B = 75,
    Cursor_4C = 76,
    Cursor_4D = 77,
    Beacon = 78,
    ForceShield = 79,
    NoForceShield = 80,
    GeneticMutator = 81,
    AirStrike = 82,
    PsychicDominator = 83,
    PsychicReveal = 84,
    SpyPlane = 85,
}
enum RadBeamType {
    Temporal = 0,
    RadBeam = 1,
    Eruption = 2,
}
enum Rank {
    Invalid = -1,
    Elite = 0,
    Veteran = 1,
    Rookie = 2,
}
enum Sequence {
    Ready = 0,
    Guard = 1,
    Prone = 2,
    Walk = 3,
    FireUp = 4,
    Down = 5,
    Crawl = 6,
    Up = 7,
    FireProne = 8,
    Idle1 = 9,
    Idle2 = 10,
    Die1 = 11,
    Die2 = 12,
    Die3 = 13,
    Die4 = 14,
    Die5 = 15,
    Tread = 16,
    Swim = 17,
    WetIdle1 = 18,
    WetIdle2 = 19,
    WetDie1 = 20,
    WetDie2 = 21,
    WetAttack = 22,
    Hover = 23,
    Fly = 24,
    Tumble = 25,
    FireFly = 26,
    Deploy = 27,
    Deployed = 28,
    DeployedFire = 29,
    DeployedIdle = 30,
    Undeploy = 31,
    Cheer = 32,
    Paradrop = 33,
    AirDeathStart = 34,
    AirDeathFalling = 35,
    AirDeathFinish = 36,
    Panic = 37,
    Shovel = 38,
    Carry = 39,
    SecondaryFire = 40,
    SecondaryProne = 41,
    Nothing = -1,
}
enum SequenceFacing {
    N = 0,
    NE = 1,
    E = 2,
    SE = 3,
    S = 4,
    SW = 5,
    W = 6,
    NW = 7,
}
enum SpeedType {
    None = -1,
    Foot = 0,
    Track = 1,
    Wheel = 2,
    Hover = 3,
    Winged = 4,
    Float = 5,
    Amphibious = 6,
    FloatBeach = 7,
}
enum TheaterType {
    None = -1,
    Temperate = 0,
    Snow = 1,
    Urban = 2,
    Desert = 3,
    NewUrban = 4,
    Lunar = 5,
}
enum VisualType {
    Normal = 0,
    Indistinct = 1,
    Darken = 2,
    Shadowy = 3,
    Ripple = 4,
    Hidden = 5,
}
enum RadioCommand {
    AnswerInvalid = 0,
    AnswerPositive = 1,
    RequestLink = 2,
    NotifyUnlink = 3,
    unknown_4 = 4,
    unknown_5 = 5,
    unknown_6 = 6,
    NotifyBeginLoad = 7,
    NotifyUnloaded = 8,
    RequestUnload = 9,
    AnswerNegative = 10,
    RequestBeginProduction = 11,
    RequestEndProduction = 12,
    RequestRedraw = 13,
    RequestLoading = 14,
    AnswerLoading = 14,
    QueryCanEnter = 15,
    QueryCanUnload = 16,
    QueryWantEnter = 17,
    RequestMoveTo = 18,
    QueryMoving = 19,
    AnswerAwaiting = 20,
    RequestCompleteEnter = 21,
    RequestDockRefinery = 22,
    AnswerLeave = 23,
    NotifyLeave = 23,
    RequestTether = 24,
    RequestUntether = 25,
    RequestAlternativeTether = 26,
    RequestAlternativeUntether = 27,
    RequestRepair = 28,
    QueryReadiness = 29,
    RequestAttack = 30,
    RequestReload = 31,
    AnswerBlocked = 32,
    QueryDone = 33,
    AnswerDone = 33,
    QueryNeedRepair = 34,
    QueryOnBuilding = 35,
    QueryCanTote = 36,
}
enum EventType {
    Empty = 0,
    PowerOn = 1,
    PowerOff = 2,
    Ally = 3,
    MegaMission = 4,
    MegaMissionF = 5,
    Idle = 6,
    Scatter = 7,
    Destruct = 8,
    Deploy = 9,
    Detonate = 10,
    Place = 11,
    Options = 12,
    GameSpeed = 13,
    Produce = 14,
    Suspend = 15,
    Abandon = 16,
    Primary = 17,
    SpecialPlace = 18,
    Exit = 19,
    Animation = 20,
    Repair = 21,
    Sell = 22,
    SellCell = 23,
    Special = 24,
    FrameSync = 25,
    Message = 26,
    ResponseTime = 27,
    FrameInfo = 28,
    SaveGame = 29,
    Archive = 30,
    AddPlayer = 31,
    Timing = 32,
    ProcessTime = 33,
    PageUser = 34,
    RemovePlayer = 35,
    LatencyFudge = 36,
    MegaFrameInfo = 37,
    PacketTiming = 38,
    AboutToExit = 39,
    FallbackHost = 40,
    AddressChange = 41,
    PlanConnect = 42,
    PlanCommit = 43,
    PlanNodeDelete = 44,
    AllCheer = 45,
    AbandonAll = 46,
    LAST_EVENT = 47,
}
enum SoundPriority {
    Lowest = 0,
    Low = 1,
    Normal = 2,
    High = 3,
    Critical = 4,
}
enum SoundType {
    Normal = 0,
    Violent = 1,
    Movement = 2,
    Quiet = 4,
    Loud = 8,
    Global = 16,
    Screen = 32,
    Local = 64,
    Player = 128,
    NoiseShy = 256,
    GunShy = 512,
    Unshroud = 1024,
    Shroud = 2048,
    Ambient = 4096,
}
enum SoundControl {
    None = 0,
    Loop = 1,
    Random = 2,
    All = 4,
    Predelay = 8,
    Interrupt = 16,
    Attack = 32,
    Decay = 64,
    Ambient = 128,
}
enum VoxType {
    Standard = 0,
    Queue = 1,
    Interrupt = 2,
    QueuedInterrupt = 3,
}
enum VoxPriority {
    Low = 0,
    Normal = 1,
    Important = 2,
    Critical = 3,
}
enum WaveType {
    Sonic = 0,
    BigLaser = 1,
    Laser = 2,
    Magnetron = 3,
}
enum TargetType {
    None = 0,
    Anything = 1,
    Buildings = 2,
    Harvesters = 3,
    Infantry = 4,
    Vehicles = 5,
    Factories = 6,
    BaseDefenses = 7,
    Power = 9,
    Occupiable = 10,
    TechBuildings = 11,
}
enum TargetFlags {
    None = 0,
    unknown_1 = 1,
    unknown_2 = 2,
    Air = 4,
    Infantry = 8,
    Vehicles = 16,
    Buildings = 32,
    Economy = 64,
    Ships = 128,
    Neutral = 256,
    Capture = 512,
    Fakes = 1024,
    Power = 2048,
    Factories = 4096,
    BaseDefense = 8192,
    Friendlies = 16384,
    Occupiable = 32768,
    TechCapture = 65536,
}
enum BlitterFlags {
    None = 0,
    Darken = 1,
    TransLucent25 = 2,
    TransLucent50 = 4,
    TransLucent75 = 6,
    Warp = 8,
    ZRemap = 16,
    Plain = 32,
    bf_040 = 64,
    bf_080 = 128,
    MultiPass = 256,
    Centered = 512,
    bf_400 = 1024,
    Alpha = 2048,
    bf_1000 = 4096,
    Flat = 8192,
    ZRead = 12288,
    ZReadWrite = 16384,
    bf_8000 = 32768,
    Zero = 65536,
    Nonzero = 131072,
}
enum MouseEvent {
    None = 0,
    LeftDown = 1,
    LeftHeld = 2,
    LeftUp = 4,
    Move = 8,
    RightDown = 16,
    RightHeld = 32,
    RightUp = 64,
}
enum Edge {
    None = -1,
    North = 0,
    East = 1,
    South = 2,
    West = 3,
    Air = 4,
}
enum Move {
    OK = 0,
    Cloak = 1,
    MovingBlock = 2,
    ClosedGate = 3,
    FriendlyDestroyable = 4,
    Destroyable = 5,
    Temp = 6,
    No = 7,
}
enum ZGradient {
    None = -1,
    Ground = 0,
    Deg45 = 1,
    Deg90 = 2,
    Deg135 = 3,
}
enum ParasiteState {
    Start = 0,
    Grab = 1,
    PushLeft = 2,
    PushRight = 3,
    Damage = 4,
}
enum WWKey {
    Shift = 256,
    Ctrl = 512,
    Alt = 1024,
    Release = 2048,
    VirtualKey = 4096,
    DoubleClick = 8192,
    Button = 32768,
}
enum AirAttackStatus {
    ValidateAZ = 0,
    PickAttackLocation = 1,
    TakeOff = 2,
    FlyToPosition = 3,
    FireAtTarget = 4,
    FireAtTarget2 = 5,
    FireAtTarget2_Strafe = 6,
    FireAtTarget3_Strafe = 7,
    FireAtTarget4_Strafe = 8,
    FireAtTarget5_Strafe = 9,
    ReturnToBase = 10,
}
enum LandTargetingType {
    Land_OK = 0,
    Land_Not_OK = 1,
    Land_Secondary = 2,
}
enum NavalTargetingType {
    Underwater_Never = 0,
    Underwater_Secondary = 1,
    Underwater_Only = 2,
    Organic_Secondary = 3,
    SEAL_Special = 4,
    Naval_All = 5,
    Naval_None = 6,
    Naval_Primary = 7,
}
enum RGBMode {
    RGB555 = 0,
    RGB556 = 1,
    RGB565 = 2,
    RGB655 = 3,
    Invalid = -1,
}
enum ZoneType {
    None = -1,
    Core = 0,
    North = 1,
    East = 2,
    South = 3,
    West = 4,
}
enum BStateType {
    Construction = 0,
    Idle = 1,
    Active = 2,
    Full = 3,
    Aux1 = 4,
    Aux2 = 5,
    Count = 6,
    None = -1,
}
enum FileAccessMode {
    None = 0,
    Read = 1,
    Write = 2,
    ReadWrite = 3,
}
enum FileSeekMode {
    Set = 0,
    Current = 1,
    End = 2,
}
enum SpawnNodeStatus {
    Idle = 0,
    TakeOff = 1,
    Preparing = 2,
    Attacking = 3,
    Returning = 4,
    Reloading = 6,
    Dead = 7,
}
enum SpawnManagerStatus {
    Idle = 0,
    Launching = 1,
    CoolDown = 2,
}
enum SlaveControlStatus {
    Unknown = 0,
    ScanningForTiberium = 1,
    MovingToTiberium = 2,
    Harvesting = 3,
    BringingItBack = 4,
    Respawning = 5,
    Dead = 6,
}
enum SlaveManagerStatus {
    Ready = 0,
    Scanning = 1,
    Travelling = 2,
    Deploying = 3,
    Working = 4,
    ScanningAgain = 5,
    PackingUp = 6,
}
enum CSFLanguages {
    US = 0,
    UK = 1,
    German = 2,
    French = 3,
    Spanish = 4,
    Italian = 5,
    Japanese = 6,
    Jabberwockie = 7,
    Korean = 8,
    Chinese = 9,
    Unknown = 10,
}
enum KeyModifier {
    None = 0,
    Shift = 1,
    Ctrl = 2,
    Alt = 4,
}
enum GadgetFlag {
    LeftPress = 1,
    LeftHeld = 2,
    LeftRelease = 4,
    LeftUp = 8,
    RightPress = 16,
    RightHeld = 32,
    RightRelease = 64,
    RightUp = 128,
    Keyboard = 256,
}
}
