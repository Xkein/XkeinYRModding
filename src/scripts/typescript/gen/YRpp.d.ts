/// <reference path = "../index.d.ts"/>
declare module "YRpp" {
import { CDTimerClass } from "yr";
class TintStruct
{
    mRed : number;
    mGreen : number;
    mBlue : number;
}
class RandomStruct
{
    mMin : number;
    mMax : number;
}
class LTRBStruct
{
    mLeft : number;
    mTop : number;
    mRight : number;
    mBottom : number;
}
class RateTimer
{
    Start(rate_0 : number) : void;
    mRate : number;
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
    mDesiredFacing : any;
    mStartFacing : any;
    mRotationTimer : CDTimerClass;
    mROT : any;
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
    get_ID() : number;
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
    sAbsDerivateID : any;
    sArray : any;
    mFlashing : FlashData;
    m__Flashing : number;
    mAnimation : StageClass;
    m__Animation : number;
    mPassengers : PassengersClass;
    m__Passengers : number;
    mTransporter : TechnoClass;
    munknown_int_120 : number;
    mCurrentTurretNumber : number;
    munknown_int_128 : number;
    mBehindAnim : AnimClass;
    mDeployAnim : AnimClass;
    mInAir : boolean;
    mCurrentWeaponNumber : number;
    mCurrentRanking : any;
    mCurrentGattlingStage : number;
    mGattlingValue : number;
    mTurretAnimFrame : number;
    mInitialOwner : HouseClass;
    mVeterancy : VeterancyStruct;
    m__Veterancy : number;
    mArmorMultiplier : number;
    mFirepowerMultiplier : number;
    mIdleActionTimer : CDTimerClass;
    m__IdleActionTimer : number;
    mRadarFlashTimer : CDTimerClass;
    m__RadarFlashTimer : number;
    mTargetingTimer : CDTimerClass;
    m__TargetingTimer : number;
    mIronCurtainTimer : CDTimerClass;
    m__IronCurtainTimer : number;
    mIronTintTimer : CDTimerClass;
    m__IronTintTimer : number;
    mIronTintStage : number;
    mAirstrikeTimer : CDTimerClass;
    m__AirstrikeTimer : number;
    mAirstrikeTintTimer : CDTimerClass;
    m__AirstrikeTintTimer : number;
    mAirstrikeTintStage : number;
    mForceShielded : number;
    mDeactivated : boolean;
    mDrainTarget : TechnoClass;
    mDrainingMe : TechnoClass;
    mDrainAnim : AnimClass;
    mDisguised : boolean;
    mDisguiseCreationFrame : number;
    mInfantryBlinkTimer : CDTimerClass;
    m__InfantryBlinkTimer : number;
    mDisguiseBlinkTimer : CDTimerClass;
    m__DisguiseBlinkTimer : number;
    mUnlimboingInfantry : boolean;
    mReloadTimer : CDTimerClass;
    m__ReloadTimer : number;
    munknown_208 : number;
    munknown_20C : number;
    mDisplayProductionTo : any;
    m__DisplayProductionTo : number;
    mGroup : number;
    mFocus : AbstractClass;
    mOwner : HouseClass;
    mCloakState : any;
    mCloakProgress : StageClass;
    m__CloakProgress : number;
    mCloakDelayTimer : CDTimerClass;
    m__CloakDelayTimer : number;
    mWarpFactor : number;
    munknown_bool_250 : boolean;
    mLastSightCoords : any;
    mLastSightRange : number;
    mLastSightHeight : number;
    mGapSuperCharged : boolean;
    mGeneratingGap : boolean;
    mGapRadius : number;
    mBeingWarpedOut : boolean;
    mWarpingOut : boolean;
    munknown_bool_272 : boolean;
    munused_273 : number;
    mTemporalImUsing : TemporalClass;
    mTemporalTargetingMe : TemporalClass;
    mIsImmobilized : boolean;
    munknown_280 : number;
    mChronoLockRemaining : number;
    mChronoDestCoords : any;
    mAirstrike : AirstrikeClass;
    mBerzerk : boolean;
    mBerzerkDurationLeft : number;
    mSprayOffsetIndex : number;
    mUncrushable : boolean;
    mDirectRockerLinkedUnit : FootClass;
    mLocomotorTarget : FootClass;
    mLocomotorSource : FootClass;
    mTarget : AbstractClass;
    mLastTarget : AbstractClass;
    mCaptureManager : CaptureManagerClass;
    mMindControlledBy : TechnoClass;
    mMindControlledByAUnit : boolean;
    mMindControlRingAnim : AnimClass;
    mMindControlledByHouse : HouseClass;
    mSpawnManager : SpawnManagerClass;
    mSpawnOwner : TechnoClass;
    mSlaveManager : SlaveManagerClass;
    mSlaveOwner : TechnoClass;
    mOriginallyOwnedByHouse : HouseClass;
    mBunkerLinkedItem : TechnoClass;
    mPitchAngle : number;
    mDiskLaserTimer : CDTimerClass;
    m__DiskLaserTimer : number;
    mROF : number;
    mAmmo : number;
    mValue : number;
    mFireParticleSystem : ParticleSystemClass;
    mSparkParticleSystem : ParticleSystemClass;
    mNaturalParticleSystem : ParticleSystemClass;
    mDamageParticleSystem : ParticleSystemClass;
    mRailgunParticleSystem : ParticleSystemClass;
    munk1ParticleSystem : ParticleSystemClass;
    munk2ParticleSystem : ParticleSystemClass;
    mFiringParticleSystem : ParticleSystemClass;
    mWave : WaveClass;
    mAngleRotatedSideways : number;
    mAngleRotatedForwards : number;
    mRockingSidewaysPerFrame : number;
    mRockingForwardsPerFrame : number;
    mHijackerInfantryType : number;
    mTiberium : StorageClass;
    m__Tiberium : number;
    munknown_34C : number;
    mUnloadTimer : TransitionTimer;
    m__UnloadTimer : number;
    mBarrelFacing : FacingClass;
    m__BarrelFacing : number;
    mPrimaryFacing : FacingClass;
    m__PrimaryFacing : number;
    mSecondaryFacing : FacingClass;
    m__SecondaryFacing : number;
    mCurrentBurstIndex : number;
    mTargetLaserTimer : CDTimerClass;
    m__TargetLaserTimer : number;
    munknown_short_3C8 : number;
    munknown_3CA : number;
    mCountedAsOwned : boolean;
    mIsSinking : boolean;
    mWasSinkingAlready : boolean;
    munknown_bool_3CF : boolean;
    munknown_bool_3D0 : boolean;
    mHasBeenAttacked : boolean;
    mCloakable : boolean;
    mIsPrimaryFactory : boolean;
    mSpawned : boolean;
    mIsInPlayfield : boolean;
    mTurretRecoil : RecoilData;
    m__TurretRecoil : number;
    mBarrelRecoil : RecoilData;
    m__BarrelRecoil : number;
    munknown_bool_418 : boolean;
    munknown_bool_419 : boolean;
    mIsOwnedByCurrentPlayer : boolean;
    mDiscoveredByCurrentPlayer : boolean;
    mDiscoveredByComputer : boolean;
    munknown_bool_41D : boolean;
    munknown_bool_41E : boolean;
    munknown_bool_41F : boolean;
    mSightIncrease : number;
    mRecruitableA : boolean;
    mRecruitableB : boolean;
    mIsRadarTracked : boolean;
    mIsOnCarryall : boolean;
    mIsCrashing : boolean;
    mWasCrashingAlready : boolean;
    mIsBeingManipulated : boolean;
    mBeingManipulatedBy : TechnoClass;
    mChronoWarpedByHouse : HouseClass;
    munknown_bool_430 : boolean;
    mIsMouseHovering : boolean;
    munknown_bool_432 : boolean;
    mOldTeam : TeamClass;
    mCountedAsOwnedSpecial : boolean;
    mAbsorbed : boolean;
    munknown_bool_43A : boolean;
    munknown_43C : number;
    mCurrentTargetThreatValues : any;
    m__CurrentTargetThreatValues : number;
    mCurrentTargets : any;
    m__CurrentTargets : number;
    mAttackedTargets : any;
    m__AttackedTargets : number;
    mAudio3 : any;
    m__Audio3 : number;
    munknown_BOOL_49C : number;
    mTurretIsRotating : number;
    mAudio4 : any;
    m__Audio4 : number;
    munknown_bool_4B8 : boolean;
    munknown_4BC : number;
    mAudio5 : any;
    m__Audio5 : number;
    munknown_bool_4D4 : boolean;
    munknown_4D8 : number;
    mAudio6 : any;
    m__Audio6 : number;
    mQueuedVoiceIndex : number;
    munknown_4F4 : number;
    munknown_bool_4F8 : boolean;
    munknown_4FC : number;
    munknown_500 : TechnoClass;
    mEMPLockRemaining : number;
    mThreatPosed : number;
    mShouldLoseTargetNow : number;
    mFiringRadBeam : RadBeam;
    mPlanningToken : PlanningTokenClass;
    mDisguise : ObjectTypeClass;
    mDisguisedAsHouse : HouseClass;
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
    Name() : number;
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
    Index_IsMP(idx_0 : number) : boolean;
    FindByCountryIndex(HouseType_0 : number) : HouseClass;
    FindByIndex(idxHouse_0 : number) : HouseClass;
    FindIndexByName(name_0 : number) : number;
    GetPlayerAtFromString(name_0 : number) : number;
    IsPlayerAtType(at_0 : number) : boolean;
    FindByPlayerAt(at_0 : number) : HouseClass;
    FindByCountryName(name_0 : number) : HouseClass;
    FindNeutral() : HouseClass;
    FindSpecial() : HouseClass;
    FindBySideIndex(index_0 : number) : HouseClass;
    FindBySideName(name_0 : number) : HouseClass;
    FindCivilianSide() : HouseClass;
    LoadFromINIList(pINI_0 : any) : void;
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
    get_ID() : number;
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
    IsCurrentPlayerObserver() : boolean;
    CalculateCostMultipliers() : number;
    ForceEnd() : void;
    RemoveTracking(pTechno_0 : TechnoClass) : void;
    AddTracking(pTechno_0 : TechnoClass) : void;
    GetWeedStoragePercentage() : number;
    sAbsID : any;
    sArray : any;
    sCurrentPlayer : any;
    sObserver : any;
    mArrayIndex : number;
    mType : HouseTypeClass;
    mRelatedTags : any;
    m__RelatedTags : number;
    mConYards : any;
    m__ConYards : number;
    mBuildings : any;
    m__Buildings : number;
    mUnitRepairStations : any;
    m__UnitRepairStations : number;
    mGrinders : any;
    m__Grinders : number;
    mAbsorbers : any;
    m__Absorbers : number;
    mBunkers : any;
    m__Bunkers : number;
    mOccupiables : any;
    m__Occupiables : number;
    mCloningVats : any;
    m__CloningVats : number;
    mSecretLabs : any;
    m__SecretLabs : number;
    mPsychicDetectionBuildings : any;
    m__PsychicDetectionBuildings : number;
    mFactoryPlants : any;
    m__FactoryPlants : number;
    mCountResourceGatherers : number;
    mCountResourceDestinations : number;
    mCountWarfactories : number;
    mInfantrySelfHeal : number;
    mUnitsSelfHeal : number;
    mStartingUnits : any;
    m__StartingUnits : number;
    mAIDifficulty : any;
    mFirepowerMultiplier : number;
    mGroundspeedMultiplier : number;
    mAirspeedMultiplier : number;
    mArmorMultiplier : number;
    mROFMultiplier : number;
    mCostMultiplier : number;
    mBuildTimeMultiplier : number;
    mRepairDelay : number;
    mBuildDelay : number;
    mIQLevel : number;
    mTechLevel : number;
    mAltAllies : any;
    mStartingCredits : number;
    mStartingEdge : any;
    mAIState_1E4 : number;
    mSideIndex : number;
    mIsHumanPlayer : boolean;
    mIsInPlayerControl : boolean;
    mProduction : boolean;
    mAutocreateAllowed : boolean;
    mNodeLogic_1F0 : boolean;
    mShipYardConst_1F1 : boolean;
    mAITriggersActive : boolean;
    mAutoBaseBuilding : boolean;
    mDiscoveredByPlayer : boolean;
    mDefeated : boolean;
    mIsGameOver : boolean;
    mIsWinner : boolean;
    mIsLoser : boolean;
    mCiviliansEvacuated : boolean;
    mFirestormActive : boolean;
    mHasThreatNode : boolean;
    mRecheckTechTree : boolean;
    mIPAddress : number;
    mTournamentTeamID : number;
    mLostConnection : boolean;
    mSelectedPathIndex : number;
    mPlanningPaths : WaypointPathClass;
    mVisionary : number;
    mMapIsClear : boolean;
    mIsTiberiumShort : boolean;
    mHasBeenSpied : boolean;
    mHasBeenThieved : boolean;
    mRepairing : boolean;
    mIsBuiltSomething : boolean;
    mIsResigner : boolean;
    mIsGiverUpper : boolean;
    mAllToHunt : boolean;
    mIsParanoid : boolean;
    mIsToLook : boolean;
    mIQLevel2 : number;
    mAIMode : any;
    mSupers : any;
    m__Supers : number;
    mLastBuiltBuildingType : number;
    mLastBuiltInfantryType : number;
    mLastBuiltAircraftType : number;
    mLastBuiltVehicleType : number;
    mAllowWinBlocks : number;
    mRepairTimer : CDTimerClass;
    m__RepairTimer : number;
    mAlertTimer : CDTimerClass;
    m__AlertTimer : number;
    mBorrowedTime : CDTimerClass;
    m__BorrowedTime : number;
    mPowerBlackoutTimer : CDTimerClass;
    m__PowerBlackoutTimer : number;
    mRadarBlackoutTimer : CDTimerClass;
    m__RadarBlackoutTimer : number;
    mSide2TechInfiltrated : boolean;
    mSide1TechInfiltrated : boolean;
    mSide0TechInfiltrated : boolean;
    mBarracksInfiltrated : boolean;
    mWarFactoryInfiltrated : boolean;
    mInfantryAltOwner : number;
    mUnitAltOwner : number;
    mAircraftAltOwner : number;
    mBuildingAltOwner : number;
    mAirportDocks : number;
    mPoweredUnitCenters : number;
    mCreditsSpent : number;
    mHarvestedCredits : number;
    mStolenBuildingsCredits : number;
    mOwnedUnits : number;
    mOwnedNavy : number;
    mOwnedBuildings : number;
    mOwnedInfantry : number;
    mOwnedAircraft : number;
    mOwnedTiberium : StorageClass;
    m__OwnedTiberium : number;
    mBalance : number;
    mTotalStorage : number;
    mOwnedWeed : StorageClass;
    m__OwnedWeed : number;
    munknown_324 : number;
    mBuiltAircraftTypes : UnitTrackerClass;
    m__BuiltAircraftTypes : number;
    mBuiltInfantryTypes : UnitTrackerClass;
    m__BuiltInfantryTypes : number;
    mBuiltUnitTypes : UnitTrackerClass;
    m__BuiltUnitTypes : number;
    mBuiltBuildingTypes : UnitTrackerClass;
    m__BuiltBuildingTypes : number;
    mKilledAircraftTypes : UnitTrackerClass;
    m__KilledAircraftTypes : number;
    mKilledInfantryTypes : UnitTrackerClass;
    m__KilledInfantryTypes : number;
    mKilledUnitTypes : UnitTrackerClass;
    m__KilledUnitTypes : number;
    mKilledBuildingTypes : UnitTrackerClass;
    m__KilledBuildingTypes : number;
    mCapturedBuildings : UnitTrackerClass;
    m__CapturedBuildings : number;
    mCollectedCrates : UnitTrackerClass;
    m__CollectedCrates : number;
    mNumAirpads : number;
    mNumBarracks : number;
    mNumWarFactories : number;
    mNumConYards : number;
    mNumShipyards : number;
    mNumOrePurifiers : number;
    mCostInfantryMult : number;
    mCostUnitsMult : number;
    mCostAircraftMult : number;
    mCostBuildingsMult : number;
    mCostDefensesMult : number;
    mPowerOutput : number;
    mPowerDrain : number;
    mPrimary_ForAircraft : FactoryClass;
    mPrimary_ForInfantry : FactoryClass;
    mPrimary_ForVehicles : FactoryClass;
    mPrimary_ForShips : FactoryClass;
    mPrimary_ForBuildings : FactoryClass;
    mPrimary_Unused1 : FactoryClass;
    mPrimary_Unused2 : FactoryClass;
    mPrimary_Unused3 : FactoryClass;
    mPrimary_ForDefenses : FactoryClass;
    mAircraftType_53D0 : number;
    mInfantryType_53D1 : number;
    mVehicleType_53D2 : number;
    mShipType_53D3 : number;
    mBuildingType_53D4 : number;
    munknown_53D5 : number;
    munknown_53D6 : number;
    munknown_53D7 : number;
    mDefenseType_53D8 : number;
    munknown_53D9 : number;
    munknown_53DA : number;
    munknown_53DB : number;
    mOurFlagCarrier : UnitClass;
    mOurFlagCoords : any;
    mKilledUnitsOfHouses : number;
    mTotalKilledUnits : number;
    mKilledBuildingsOfHouses : number;
    mTotalKilledBuildings : number;
    mWhoLastHurtMe : number;
    mBaseSpawnCell : any;
    mBaseCenter : any;
    mRadius : number;
    mZoneInfos : ZoneInfoStruct;
    m__ZoneInfos : number;
    mLATime : number;
    mLAEnemy : number;
    mToCapture : number;
    mRadarVisibleTo : any;
    mSiloMoney : number;
    mPreferredTargetType : any;
    mPreferredTargetCell : any;
    mPreferredDefensiveCell : any;
    mPreferredDefensiveCell2 : any;
    mPreferredDefensiveCellStartTime : number;
    mOwnedBuildingTypes : any;
    m__OwnedBuildingTypes : number;
    mOwnedUnitTypes : any;
    m__OwnedUnitTypes : number;
    mOwnedInfantryTypes : any;
    m__OwnedInfantryTypes : number;
    mOwnedAircraftTypes : any;
    m__OwnedAircraftTypes : number;
    mActiveBuildingTypes : any;
    m__ActiveBuildingTypes : number;
    mActiveUnitTypes : any;
    m__ActiveUnitTypes : number;
    mActiveInfantryTypes : any;
    m__ActiveInfantryTypes : number;
    mActiveAircraftTypes : any;
    m__ActiveAircraftTypes : number;
    mFactoryProducedBuildingTypes : any;
    m__FactoryProducedBuildingTypes : number;
    mFactoryProducedUnitTypes : any;
    m__FactoryProducedUnitTypes : number;
    mFactoryProducedInfantryTypes : any;
    m__FactoryProducedInfantryTypes : number;
    mFactoryProducedAircraftTypes : any;
    m__FactoryProducedAircraftTypes : number;
    mAttackTimer : CDTimerClass;
    m__AttackTimer : number;
    mInitialAttackDelay : number;
    mEnemyHouseIndex : number;
    mAngerNodes : any;
    m__AngerNodes : number;
    mScoutNodes : any;
    m__ScoutNodes : number;
    mAITimer : CDTimerClass;
    m__AITimer : number;
    mUnknown_Timer_5640 : CDTimerClass;
    m__Unknown_Timer_5640 : number;
    mProducingBuildingTypeIndex : number;
    mProducingUnitTypeIndex : number;
    mProducingInfantryTypeIndex : number;
    mProducingAircraftTypeIndex : number;
    mRatioAITriggerTeam : number;
    mRatioTeamAircraft : number;
    mRatioTeamInfantry : number;
    mRatioTeamBuildings : number;
    mBaseDefenseTeamCount : number;
    mDropshipData : DropshipStruct;
    m__DropshipData : number;
    mCurrentDropshipIndex : number;
    mHasCloakingRanges : number;
    mColor : any;
    mLaserColor : any;
    mBase : BaseClass;
    mRecheckPower : boolean;
    mRecheckRadar : boolean;
    mSpySatActive : boolean;
    mIsBeingDrained : boolean;
    mEdge : any;
    mEMPTarget : any;
    mNukeTarget : any;
    mAllies : any;
    mDamageDelayTimer : CDTimerClass;
    m__DamageDelayTimer : number;
    mTeamDelayTimer : CDTimerClass;
    m__TeamDelayTimer : number;
    mTriggerDelayTimer : CDTimerClass;
    m__TriggerDelayTimer : number;
    mSpeakAttackDelayTimer : CDTimerClass;
    m__SpeakAttackDelayTimer : number;
    mSpeakPowerDelayTimer : CDTimerClass;
    m__SpeakPowerDelayTimer : number;
    mSpeakMoneyDelayTimer : CDTimerClass;
    m__SpeakMoneyDelayTimer : number;
    mSpeakMaxedDelayTimer : CDTimerClass;
    m__SpeakMaxedDelayTimer : number;
    mAIGeneral : any;
    mThreatPosedEstimates : number;
    mPlainName : number;
    mUINameString : number;
    mUIName : number;
    mColorSchemeIndex : number;
    mStartingPoint : number;
    mStartingCell : any;
    mStartingAllies : any;
    munknown_16060 : number;
    mWaypointPath : any;
    m__WaypointPath : number;
    munknown_1607C : number;
    munknown_16080 : number;
    munknown_16084 : number;
    munused_16088 : number;
    munused_16090 : number;
    mpadding_16098 : number;
    mPredictionEnemyArmor : number;
    mPredictionEnemyAir : number;
    mPredictionEnemyInfantry : number;
    mTotalOwnedInfantryCost : number;
    mTotalOwnedVehicleCost : number;
    mTotalOwnedAircraftCost : number;
    munknown_power_160B4 : number;
}
class StorageClass
{
    GetAmount(index_0 : number) : number;
    GetTotalAmount() : number;
    AddAmount(amount_0 : number, index_1 : number) : number;
    RemoveAmount(amount_0 : number, index_1 : number) : number;
    GetTotalValue() : number;
    mTiberium1 : number;
    mTiberium2 : number;
    mTiberium3 : number;
    mTiberium4 : number;
}
class AbstractClass
{
    GetClassNameA() : number;
    GetClassNameA(abs_0 : any) : number;
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
    AnnounceExpiredPointer(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    RemoveAllInactive() : void;
    AnnounceExpiredPointer(removed_0 : boolean) : void;
    GetCoords() : any;
    GetDestination(pDocker_0 : TechnoClass) : any;
    GetCenterCoords() : any;
    GetTargetDirection(pDir_0 : any, pTarget_1 : AbstractClass) : any;
    GetTargetDirection(pTarget_0 : AbstractClass) : any;
    sAbsID : any;
    sArray : any;
    sTargetIndex : any;
    mUniqueID : number;
    mAbstractFlags : any;
    munknown_18 : number;
    mRefCount : number;
    mDirty : boolean;
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
    GetUIName() : number;
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
    DrawALinkTo(src_X_0 : number, src_Y_1 : number, src_Z_2 : number, dst_X_3 : number, dst_Y_4 : number, dst_Z_5 : number, color_6 : any) : void;
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
    sAbsDerivateID : any;
    sCurrentObjects : any;
    munknown_24 : number;
    munknown_28 : number;
    mFallRate : number;
    mNextObject : ObjectClass;
    mAttachedTag : TagClass;
    mAttachedBomb : BombClass;
    mAmbientSoundController : any;
    m__AmbientSoundController : number;
    mCustomSoundController : any;
    m__CustomSoundController : number;
    mCustomSound : number;
    mBombVisible : boolean;
    mHealth : number;
    mEstimatedHealth : number;
    mIsOnMap : boolean;
    munknown_78 : number;
    munknown_7C : number;
    mNeedsRedraw : boolean;
    mInLimbo : boolean;
    mInOpenToppedTransport : boolean;
    mIsSelected : boolean;
    mHasParachute : boolean;
    mParachute : AnimClass;
    mOnBridge : boolean;
    mIsFallingDown : boolean;
    mWasFallingDown : boolean;
    mIsABomb : boolean;
    mIsAlive : boolean;
    mLastLayer : any;
    mIsInLogic : boolean;
    mIsVisible : boolean;
    mLocation : any;
    mLineTrailer : LineTrail;
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
    sAbsID : any;
    sArray : any;
    mAnimation : StageClass;
    m__Animation : number;
    mType : AnimTypeClass;
    mOwnerObject : ObjectClass;
    munknown_D0 : number;
    mLightConvert : any;
    mLightConvertIndex : number;
    mPaletteName : number;
    mTintColor : number;
    mZAdjust : number;
    mYSortAdjust : number;
    mFlamingGuyCoords : any;
    mFlamingGuyRetries : number;
    mIsBuildingAnim : boolean;
    mUnderTemporal : boolean;
    mPaused : boolean;
    mUnpaused : boolean;
    mPausedAnimFrame : number;
    mReverse : boolean;
    munknown_124 : number;
    mBounce : BounceClass;
    m__Bounce : number;
    mTranslucencyLevel : number;
    mTimeToDie : boolean;
    mAttachedBullet : BulletClass;
    mOwner : HouseClass;
    mLoopDelay : number;
    mAccum : number;
    mAnimFlags : any;
    mHasExtras : boolean;
    mRemainingIterations : number;
    munknown_196 : number;
    munknown_197 : number;
    mIsPlaying : boolean;
    mIsFogged : boolean;
    mFlamingGuyExpire : boolean;
    mUnableToContinue : boolean;
    mSkipProcessOnce : boolean;
    mInvisible : boolean;
    mPowerOff : boolean;
    mAudio3 : any;
    m__Audio3 : number;
    mAudio4 : any;
    m__Audio4 : number;
}
class AnimTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : AnimTypeClass;
    FindOrAllocate(pID_0 : number) : AnimTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    LoadImageA() : any;
    Load2DArt() : void;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mMiddleFrameIndex : number;
    mMiddleFrameWidth : number;
    mMiddleFrameHeight : number;
    munknown_2A4 : number;
    mDamage : number;
    mRate : number;
    mStart : number;
    mLoopStart : number;
    mLoopEnd : number;
    mEnd : number;
    mLoopCount : number;
    mNext : AnimTypeClass;
    mSpawnsParticle : number;
    mNumParticles : number;
    mDetailLevel : number;
    mTranslucencyDetailLevel : number;
    mRandomLoopDelay : RandomStruct;
    mRandomRate : RandomStruct;
    mTranslucency : number;
    mSpawns : AnimTypeClass;
    mSpawnCount : number;
    mReport : number;
    mStopSound : number;
    mBounceAnim : AnimTypeClass;
    mExpireAnim : AnimTypeClass;
    mTrailerAnim : AnimTypeClass;
    mTrailerSeperation : number;
    mElasticity : number;
    mMinZVel : number;
    munknown_double_320 : number;
    mMaxXYVel : number;
    mWarhead : WarheadTypeClass;
    mDamageRadius : number;
    mTiberiumSpawnType : OverlayTypeClass;
    mTiberiumSpreadRadius : number;
    mYSortAdjust : number;
    mYDrawOffset : number;
    mZAdjust : number;
    mMakeInfantry : number;
    mRunningFrames : number;
    mIsFlamingGuy : boolean;
    mIsVeins : boolean;
    mIsMeteor : boolean;
    mTiberiumChainReaction : boolean;
    mIsTiberium : boolean;
    mHideIfNoOre : boolean;
    mBouncer : boolean;
    mTiled : boolean;
    mShouldUseCellDrawer : boolean;
    mUseNormalLight : boolean;
    mDemandLoad : boolean;
    mFreeLoad : boolean;
    mIsAnimatedTiberium : boolean;
    mAltPalette : boolean;
    mNormalized : boolean;
    mLayer : any;
    mDoubleThick : boolean;
    mFlat : boolean;
    mTranslucent : boolean;
    mScorch : boolean;
    mFlamer : boolean;
    mCrater : boolean;
    mForceBigCraters : boolean;
    mSticky : boolean;
    mPingPong : boolean;
    mReverse : boolean;
    mShadow : boolean;
    mPsiWarning : boolean;
    mShouldFogRemove : boolean;
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
    IsBuildCat5(abstractID_0 : any, idx_1 : number) : boolean;
    GetTechnoType(abstractID_0 : any, idx_1 : number) : TechnoTypeClass;
    LoadVoxel() : void;
    mRadialColor : any;
    munused_9B : number;
    mArmor : any;
    mStrength : number;
    mImage : any;
    mImageAllocated : boolean;
    mAlphaImage : any;
    mMainVoxel : any;
    mTurretVoxel : any;
    mBarrelVoxel : any;
    mChargerTurrets : any;
    mChargerBarrels : any;
    mNoSpawnAlt : boolean;
    mMaxDimension : number;
    mCrushSound : number;
    mAmbientSound : number;
    mImageFile : number;
    mAlternateArcticArt : boolean;
    mArcticArtInUse : boolean;
    mAlphaImageFile : number;
    mTheater : boolean;
    mCrushable : boolean;
    mBombable : boolean;
    mRadarInvisible : boolean;
    mSelectable : boolean;
    mLegalTarget : boolean;
    mInsignificant : boolean;
    mImmune : boolean;
    mIsLogic : boolean;
    mAllowCellContent : boolean;
    mVoxel : boolean;
    mNewTheater : boolean;
    mHasRadialIndicator : boolean;
    mIgnoresFirestorm : boolean;
    mUseLineTrail : boolean;
    mLineTrailColor : any;
    mLineTrailColorDecrement : number;
    mVoxelMainCache : any;
    mVoxelTurretWeaponCache : any;
    mVoxelShadowCache : any;
    mVoxelTurretBarrelCache : any;
}
class AbstractTypeClass
    extends AbstractClass
{
    LoadTheaterSpecificArt(th_type_0 : any) : void;
    LoadFromINI(pINI_0 : any) : boolean;
    SaveToINI(pINI_0 : any) : boolean;
    get_ID() : number;
    sAbsID : any;
    sArray : any;
    mID : number;
    mUINameLabel : number;
    mUIName : number;
    mName : number;
}
class TechnoTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : TechnoTypeClass;
    FindIndex(pID_0 : number) : number;
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
    GetByTypeAndIndex(abs_0 : any, index_1 : number) : TechnoTypeClass;
    HasMultipleTurrets() : boolean;
    GetParticleSysOffset(pBuffer_0 : any) : any;
    GetParticleSysOffset() : any;
    InOwners(bitHouseType_0 : number) : boolean;
    InRequiredHouses(bitHouseType_0 : number) : boolean;
    InForbiddenHouses(bitHouseType_0 : number) : boolean;
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    sArray : any;
    sMaxWeapons : any;
    mWalkRate : number;
    mIdleRate : number;
    mVeteranAbilities : AbilitiesStruct;
    mEliteAbilities : AbilitiesStruct;
    mSpecialThreatValue : number;
    mMyEffectivenessCoefficient : number;
    mTargetEffectivenessCoefficient : number;
    mTargetSpecialThreatCoefficient : number;
    mTargetStrengthCoefficient : number;
    mTargetDistanceCoefficient : number;
    mThreatAvoidanceCoefficient : number;
    mSlowdownDistance : number;
    malign_2FC : number;
    munknown_double_300 : number;
    mAccelerationFactor : number;
    mCloakingSpeed : number;
    mDebrisTypes : any;
    mDebrisMaximums : any;
    mLocomotor : any;
    malign_35C : number;
    mVoxelScaleX : number;
    mVoxelScaleY : number;
    mWeight : number;
    mPhysicalSize : number;
    mSize : number;
    mSizeLimit : number;
    mHoverAttack : boolean;
    mVHPScan : number;
    munknown_int_398 : number;
    malign_39C : number;
    mRollAngle : number;
    mPitchSpeed : number;
    mPitchAngle : number;
    mBuildLimit : number;
    mCategory : any;
    munknown_3C0 : number;
    malign_3C4 : number;
    mDeployTime : number;
    mFireAngle : number;
    mPipScale : any;
    mPipsDrawForAll : boolean;
    mLeptonMindControlOffset : number;
    mPixelSelectionBracketDelta : number;
    mPipWrap : number;
    mDock : any;
    mDeploysInto : BuildingTypeClass;
    mUndeploysInto : UnitTypeClass;
    mPowersUnit : UnitTypeClass;
    mPoweredUnit : boolean;
    mVoiceSelect : any;
    mVoiceSelectEnslaved : any;
    mVoiceSelectDeactivated : any;
    mVoiceMove : any;
    mVoiceAttack : any;
    mVoiceSpecialAttack : any;
    mVoiceDie : any;
    mVoiceFeedback : any;
    mMoveSound : any;
    mDieSound : any;
    mAuxSound1 : number;
    mAuxSound2 : number;
    mCreateSound : number;
    mDamageSound : number;
    mImpactWaterSound : number;
    mImpactLandSound : number;
    mCrashingSound : number;
    mSinkingSound : number;
    mVoiceFalling : number;
    mVoiceCrashing : number;
    mVoiceSinking : number;
    mVoiceEnter : number;
    mVoiceCapture : number;
    mTurretRotateSound : number;
    mEnterTransportSound : number;
    mLeaveTransportSound : number;
    mDeploySound : number;
    mUndeploySound : number;
    mChronoInSound : number;
    mChronoOutSound : number;
    mVoiceHarvest : number;
    mVoicePrimaryWeaponAttack : number;
    mVoicePrimaryEliteWeaponAttack : number;
    mVoiceSecondaryWeaponAttack : number;
    mVoiceSecondaryEliteWeaponAttack : number;
    mVoiceDeploy : number;
    mVoiceUndeploy : number;
    mEnterGrinderSound : number;
    mLeaveGrinderSound : number;
    mEnterBioReactorSound : number;
    mLeaveBioReactorSound : number;
    mActivateSound : number;
    mDeactivateSound : number;
    mMindClearedSound : number;
    mMovementZone : any;
    mGuardRange : number;
    mMinDebris : number;
    mMaxDebris : number;
    mDebrisAnims : any;
    mPassengers : number;
    mOpenTopped : boolean;
    mSight : number;
    mResourceGatherer : boolean;
    mResourceDestination : boolean;
    mRevealToAll : boolean;
    mDrainable : boolean;
    mSensorsSight : number;
    mDetectDisguiseRange : number;
    mBombSight : number;
    mLeadershipRating : number;
    mNavalTargeting : any;
    mLandTargeting : any;
    mBuildTimeMultiplier : number;
    mMindControlRingOffset : number;
    mCost : number;
    mSoylent : number;
    mFlightLevel : number;
    mAirstrikeTeam : number;
    mEliteAirstrikeTeam : number;
    mAirstrikeTeamType : AircraftTypeClass;
    mEliteAirstrikeTeamType : AircraftTypeClass;
    mAirstrikeRechargeTime : number;
    mEliteAirstrikeRechargeTime : number;
    mTechLevel : number;
    mPrerequisite : any;
    mPrerequisiteOverride : any;
    mThreatPosed : number;
    mPoints : number;
    mSpeed : number;
    mSpeedType : any;
    mInitialAmmo : number;
    mAmmo : number;
    mIFVMode : number;
    mAirRangeBonus : number;
    mBerserkFriendly : boolean;
    mSprayAttack : boolean;
    mPushy : boolean;
    mNatural : boolean;
    mUnnatural : boolean;
    mCloseRange : boolean;
    mReload : number;
    mEmptyReload : number;
    mReloadIncrement : number;
    mRadialFireSegments : number;
    mDeployFireWeapon : number;
    mDeployFire : boolean;
    mDeployToLand : boolean;
    mMobileFire : boolean;
    mOpportunityFire : boolean;
    mDistributedFire : boolean;
    mDamageReducesReadiness : boolean;
    mReadinessReductionMultiplier : number;
    mUnloadingClass : UnitTypeClass;
    mDeployingAnim : AnimTypeClass;
    mAttackFriendlies : boolean;
    mAttackCursorOnFriendlies : boolean;
    mUndeployDelay : number;
    mPreventAttackMove : boolean;
    mOwnerFlags : number;
    mAIBasePlanningSide : number;
    mStupidHunt : boolean;
    mAllowedToStartInMultiplayer : boolean;
    mCameoFile : number;
    mCameo : any;
    mCameoAllocated : boolean;
    mAltCameoFile : number;
    mAltCameo : any;
    mAltCameoAllocated : boolean;
    mRotCount : number;
    mROT : number;
    mTurretOffset : number;
    mCanBeHidden : boolean;
    mPoints2 : number;
    mExplosion : any;
    mDestroyAnim : any;
    mNaturalParticleSystem : ParticleSystemTypeClass;
    mNaturalParticleSystemLocation : any;
    mRefinerySmokeParticleSystem : ParticleSystemTypeClass;
    mDamageParticleSystems : any;
    mDestroyParticleSystems : any;
    mDamageSmokeOffset : any;
    mDamSmkOffScrnRel : boolean;
    mDestroySmokeOffset : any;
    mRefinerySmokeOffsetOne : any;
    mRefinerySmokeOffsetTwo : any;
    mRefinerySmokeOffsetThree : any;
    mRefinerySmokeOffsetFour : any;
    mShadowIndex : number;
    mStorage : number;
    mTurretNotExportedOnGround : boolean;
    mGunner : boolean;
    mHasTurretTooltips : boolean;
    mTurretCount : number;
    mWeaponCount : number;
    mIsChargeTurret : boolean;
    mTurretWeapon : number;
    mAlternativeFLH : any;
    mWeapon : WeaponStruct;
    mClearAllWeapons : boolean;
    mEliteWeapon : WeaponStruct;
    mTypeImmune : boolean;
    mMoveToShroud : boolean;
    mTrainable : boolean;
    mDamageSparks : boolean;
    mTargetLaser : boolean;
    mImmuneToVeins : boolean;
    mTiberiumHeal : boolean;
    mCloakStop : boolean;
    mIsTrain : boolean;
    mIsDropship : boolean;
    mToProtect : boolean;
    mDisableable : boolean;
    mUnbuildable : boolean;
    mDoubleOwned : boolean;
    mInvisible : boolean;
    mRadarVisible : boolean;
    mHasPrimary : boolean;
    mSensors : boolean;
    mNominal : boolean;
    mDontScore : boolean;
    mDamageSelf : boolean;
    mTurret : boolean;
    mTurretRecoil : boolean;
    mTurretAnimData : TurretControl;
    munknown_bool_CB4 : boolean;
    mBarrelAnimData : TurretControl;
    munknown_bool_CC8 : boolean;
    mRepairable : boolean;
    mCrewed : boolean;
    mNaval : boolean;
    mRemapable : boolean;
    mCloakable : boolean;
    mGapGenerator : boolean;
    mGapRadiusInCells : number;
    mSuperGapRadiusInCells : number;
    mTeleporter : boolean;
    mIsGattling : boolean;
    mWeaponStages : number;
    mWeaponStage : number;
    mEliteStage : number;
    mRateUp : number;
    mRateDown : number;
    mSelfHealing : boolean;
    mExplodes : boolean;
    mDeathWeapon : WeaponTypeClass;
    mDeathWeaponDamageModifier : number;
    mNoAutoFire : boolean;
    mTurretSpins : boolean;
    mTiltCrashJumpjet : boolean;
    mNormalized : boolean;
    mManualReload : boolean;
    mVisibleLoad : boolean;
    mLightningRod : boolean;
    mHunterSeeker : boolean;
    mCrusher : boolean;
    mOmniCrusher : boolean;
    mOmniCrushResistant : boolean;
    mTiltsWhenCrushes : boolean;
    mIsSubterranean : boolean;
    mAutoCrush : boolean;
    mBunkerable : boolean;
    mCanDisguise : boolean;
    mPermaDisguise : boolean;
    mDetectDisguise : boolean;
    mDisguiseWhenStill : boolean;
    mCanApproachTarget : boolean;
    mCanRecalcApproachTarget : boolean;
    mImmuneToPsionics : boolean;
    mImmuneToPsionicWeapons : boolean;
    mImmuneToRadiation : boolean;
    mParasiteable : boolean;
    mDefaultToGuardArea : boolean;
    mWarpable : boolean;
    mImmuneToPoison : boolean;
    mReselectIfLimboed : boolean;
    mRejoinTeamIfLimboed : boolean;
    mSlaved : boolean;
    mEnslaves : InfantryTypeClass;
    mSlavesNumber : number;
    mSlaveRegenRate : number;
    mSlaveReloadRate : number;
    mOpenTransportWeapon : number;
    mSpawned : boolean;
    mSpawns : AircraftTypeClass;
    mSpawnsNumber : number;
    mSpawnRegenRate : number;
    mSpawnReloadRate : number;
    mMissileSpawn : boolean;
    mUnderwater : boolean;
    mBalloonHover : boolean;
    mSuppressionThreshold : number;
    mJumpjetTurnRate : number;
    mJumpjetSpeed : number;
    mJumpjetClimb : number;
    mJumpjetCrash : number;
    mJumpjetHeight : number;
    mJumpjetAccel : number;
    mJumpjetWobbles : number;
    mJumpjetNoWobbles : boolean;
    mJumpjetDeviation : number;
    mJumpJet : boolean;
    mCrashable : boolean;
    mConsideredAircraft : boolean;
    mOrganic : boolean;
    mNoShadow : boolean;
    mCanPassiveAquire : boolean;
    mCanRetaliate : boolean;
    mRequiresStolenThirdTech : boolean;
    mRequiresStolenSovietTech : boolean;
    mRequiresStolenAlliedTech : boolean;
    mRequiredHouses : number;
    mForbiddenHouses : number;
    mSecretHouses : number;
    mUseBuffer : boolean;
    mSecondSpawnOffset : any;
    mIsSelectableCombatant : boolean;
    mAccelerates : boolean;
    mDisableVoxelCache : boolean;
    mDisableShadowCache : boolean;
    mZFudgeCliff : number;
    mZFudgeColumn : number;
    mZFudgeTunnel : number;
    mZFudgeBridge : number;
    mPaletteFile : number;
    mPalette : any;
    malign_DF4 : number;
}
class WeaponStruct
{
    mWeaponType : WeaponTypeClass;
    mFLH : any;
    mBarrelLength : number;
    mBarrelThickness : number;
    mTurretLocked : boolean;
}
class WeaponTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : WeaponTypeClass;
    FindOrAllocate(pID_0 : number) : WeaponTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    CalculateSpeed() : void;
    sAbsID : any;
    sArray : any;
    mAmbientDamage : number;
    mBurst : number;
    mProjectile : BulletTypeClass;
    mDamage : number;
    mSpeed : number;
    mWarhead : WarheadTypeClass;
    mROF : number;
    mRange : number;
    mMinimumRange : number;
    mReport : any;
    m__Report : number;
    mDownReport : any;
    m__DownReport : number;
    mAnim : any;
    m__Anim : number;
    mOccupantAnim : AnimTypeClass;
    mAssaultAnim : AnimTypeClass;
    mOpenToppedAnim : AnimTypeClass;
    mAttachedParticleSystem : ParticleSystemTypeClass;
    mLaserInnerColor : any;
    mLaserOuterColor : any;
    mLaserOuterSpread : any;
    mUseFireParticles : boolean;
    mUseSparkParticles : boolean;
    mOmniFire : boolean;
    mDistributedWeaponFire : boolean;
    mIsRailgun : boolean;
    mLobber : boolean;
    mBright : boolean;
    mIsSonic : boolean;
    mSpawner : boolean;
    mLimboLaunch : boolean;
    mDecloakToFire : boolean;
    mCellRangefinding : boolean;
    mFireOnce : boolean;
    mNeverUse : boolean;
    mRevealOnFire : boolean;
    mTerrainFire : boolean;
    mSabotageCursor : boolean;
    mMigAttackCursor : boolean;
    mDisguiseFireOnly : boolean;
    mDisguiseFakeBlinkTime : number;
    mInfiniteMindControl : boolean;
    mFireWhileMoving : boolean;
    mDrainWeapon : boolean;
    mFireInTransport : boolean;
    mSuicide : boolean;
    mTurboBoost : boolean;
    mSupress : boolean;
    mCamera : boolean;
    mCharges : boolean;
    mIsLaser : boolean;
    mDiskLaser : boolean;
    mIsLine : boolean;
    mIsBigLaser : boolean;
    mIsHouseColor : boolean;
    mLaserDuration : number;
    mIonSensitive : boolean;
    mAreaFire : boolean;
    mIsElectricBolt : boolean;
    mDrawBoltAsLaser : boolean;
    mIsAlternateColor : boolean;
    mIsRadBeam : boolean;
    mIsRadEruption : boolean;
    mRadLevel : number;
    mIsMagBeam : boolean;
}
class BulletTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : BulletTypeClass;
    FindOrAllocate(pID_0 : number) : BulletTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    Rotates() : boolean;
    SetScaledSpawnDelay(delay_0 : number) : void;
    CreateBullet(Target_0 : AbstractClass, Owner_1 : TechnoClass, Damage_2 : number, WH_3 : WarheadTypeClass, Speed_4 : number, Bright_5 : boolean) : BulletClass;
    sAbsID : any;
    sArray : any;
    mAirburst : boolean;
    mFloater : boolean;
    mSubjectToCliffs : boolean;
    mSubjectToElevation : boolean;
    mSubjectToWalls : boolean;
    mVeryHigh : boolean;
    mShadow : boolean;
    mArcing : boolean;
    mDropping : boolean;
    mLevel : boolean;
    mInviso : boolean;
    mProximity : boolean;
    mRanged : boolean;
    mNoRotate : boolean;
    mInaccurate : boolean;
    mFlakScatter : boolean;
    mAA : boolean;
    mAG : boolean;
    mDegenerates : boolean;
    mBouncy : boolean;
    mAnimPalette : boolean;
    mFirersPalette : boolean;
    mCluster : number;
    mAirburstWeapon : WeaponTypeClass;
    mShrapnelWeapon : WeaponTypeClass;
    mShrapnelCount : number;
    mDetonationAltitude : number;
    mVertical : boolean;
    mElasticity : number;
    mAcceleration : number;
    mColor : any;
    mTrailer : AnimTypeClass;
    mROT : number;
    mCourseLockDuration : number;
    mSpawnDelay : number;
    mScaledSpawnDelay : number;
    mScalable : boolean;
    mArm : number;
    mAnimLow : number;
    mAnimHigh : number;
    mAnimRate : number;
    mFlat : boolean;
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
    ApplyRadiationToCell(cell_0 : any, radius_1 : number, amount_2 : number) : void;
    LoseTarget() : void;
    IsHoming() : boolean;
    SetWeaponType(weapon_0 : WeaponTypeClass) : void;
    GetWeaponType() : WeaponTypeClass;
    InitScalable() : void;
    NukeMaker() : void;
    GetTargetCoords() : any;
    sAbsID : any;
    sArray : any;
    sScalableBullets : any;
    mType : BulletTypeClass;
    mOwner : TechnoClass;
    munknown_B4 : boolean;
    mData : BulletData;
    mBright : boolean;
    munknown_E4 : number;
    mVelocity : any;
    munknown_100 : number;
    munknown_104 : boolean;
    munknown_108 : number;
    mTarget : AbstractClass;
    mSpeed : number;
    mInheritedColor : number;
    munknown_118 : number;
    munknown_11C : number;
    munknown_120 : number;
    mWH : WarheadTypeClass;
    mAnimFrame : number;
    mAnimRateCounter : number;
    mWeaponType : WeaponTypeClass;
    mSourceCoords : any;
    mTargetCoords : any;
    mLastMapCoords : any;
    mDamageMultiplier : number;
    mNextAnim : AnimClass;
    mSpawnNextAnim : boolean;
    mRange : number;
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
    mLastCommands : any;
    mRadioLinks : any;
    m__RadioLinks : number;
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
    mCurrentMission : any;
    mSuspendedMission : any;
    mQueuedMission : any;
    munknown_bool_B8 : boolean;
    mMissionStatus : number;
    mCurrentMissionStartTime : number;
    munknown_C4 : number;
    mUpdateTimer : CDTimerClass;
    m__UpdateTimer : number;
}
class InfantryTypeClass
    extends TechnoTypeClass
{
    Find(pID_0 : number) : InfantryTypeClass;
    FindOrAllocate(pID_0 : number) : InfantryTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mArrayIndex : number;
    mPip : any;
    mOccupyPip : any;
    mOccupyWeapon : WeaponStruct;
    mEliteOccupyWeapon : WeaponStruct;
    mSequence : any;
    mFireUp : number;
    mFireProne : number;
    mSecondaryFire : number;
    mSecondaryProne : number;
    mDeadBodies : any;
    mDeathAnims : any;
    mVoiceComment : any;
    mEnterWaterSound : number;
    mLeaveWaterSound : number;
    mCyborg : boolean;
    mNotHuman : boolean;
    mIvan : boolean;
    mDirectionDistance : number;
    mOccupier : boolean;
    mAssaulter : boolean;
    mHarvestRate : number;
    mFearless : boolean;
    mCrawls : boolean;
    mInfiltrate : boolean;
    mFraidycat : boolean;
    mTiberiumProof : boolean;
    mCivilian : boolean;
    mC4 : boolean;
    mEngineer : boolean;
    mAgent : boolean;
    mThief : boolean;
    mVehicleThief : boolean;
    mDoggie : boolean;
    mDeployer : boolean;
    mDeployedCrushable : boolean;
    mUseOwnName : boolean;
    mJumpJetTurn : boolean;
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
    GetUIName() : number;
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
    Cell2Coord(cell_0 : any, z_1 : number) : any;
    Coord2Cell(crd_0 : any) : any;
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
    sAbsID : any;
    sBridgeLevels : number;
    sBridgeHeight : number;
    mMapCoords : any;
    mFoggedObjects : any;
    mBridgeOwnerCell : CellClass;
    munknown_30 : number;
    mLightConvert : any;
    mIsoTileTypeIndex : number;
    mAttachedTag : TagClass;
    mRubble : BuildingTypeClass;
    mOverlayTypeIndex : number;
    mSmudgeTypeIndex : number;
    mPassability : any;
    mWallOwnerIndex : number;
    mInfantryOwnerIndex : number;
    mAltInfantryOwnerIndex : number;
    munknown_5C : number;
    munknown_60 : number;
    mRedrawFrame : number;
    mInViewportRect : any;
    mCloakedByHouses : number;
    mBaseSpacerOfHouses : number;
    mJumpjet : FootClass;
    mFirstObject : ObjectClass;
    mAltObject : ObjectClass;
    mLandType : any;
    mRadLevel : number;
    mRadSite : RadSiteClass;
    mPixelFX : any;
    mOccupyHeightsCoveringMe : number;
    mIntensity : number;
    mAmbient : number;
    mIntensity_Normal : number;
    mIntensity_Terrain : number;
    mColor1_Blue : number;
    mColor2_Red : number;
    mColor2_Green : number;
    mColor2_Blue : number;
    mTubeIndex : number;
    munknown_118 : number;
    mIsIceGrowthAllowed : number;
    mHeight : number;
    mLevel : number;
    mSlopeIndex : number;
    munknown_11D : number;
    mOverlayData : number;
    mSmudgeData : number;
    mVisibility : number;
    mFoggedness : number;
    mBlockedNeighbours : number;
    mOccupationFlags : number;
    mAltOccupationFlags : number;
    mAltFlags : any;
    mShroudCounter : number;
    mGapsCoveringThisCell : number;
    mVisibilityChanged : boolean;
    munknown_13C : number;
    mFlags : any;
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
    PlayAnim(animName_0 : number, Slot_1 : any, Damaged_2 : boolean, Garrisoned_3 : boolean, effectDelay_4 : number) : void;
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
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mType : BuildingTypeClass;
    mFactory : FactoryClass;
    mC4Timer : CDTimerClass;
    mBState : number;
    mQueueBState : number;
    mOwnerCountryIndex : number;
    mC4AppliedBy : InfantryClass;
    munknown_544 : number;
    mFirestormAnim : AnimClass;
    mPsiWarnAnim : AnimClass;
    munknown_timer_550 : CDTimerClass;
    mAnims : AnimClass;
    mAnimStates : boolean;
    mDamageFireAnims : AnimClass;
    mRequiresDamageFires : boolean;
    mUpgrades : BuildingTypeClass;
    mFiringSWType : number;
    munknown_5FC : number;
    mSpotlight : BuildingLightClass;
    mGateTimer : RateTimer;
    mLightSource : LightSourceClass;
    mLaserFenceFrame : number;
    mFirestormWallFrame : number;
    mRepairProgress : StageClass;
    munknown_rect_63C : any;
    munknown_coord_64C : any;
    munknown_int_658 : number;
    munknown_65C : number;
    mHasPower : boolean;
    mIsOverpowered : boolean;
    mRegisteredAsPoweredUnitSource : boolean;
    mSupportingPrisms : number;
    mHasExtraPowerBonus : boolean;
    mHasExtraPowerDrain : boolean;
    mOverpowerers : any;
    mOccupants : any;
    mFiringOccupantIndex : number;
    mAudio7 : any;
    mAudio8 : any;
    mWasOnline : boolean;
    mShowRealName : boolean;
    mBeingProduced : boolean;
    mShouldRebuild : boolean;
    mHasEngineer : boolean;
    mCashProductionTimer : CDTimerClass;
    mAI_Sellable : boolean;
    mIsReadyToCommence : boolean;
    mNeedsRepairs : boolean;
    mC4Applied : boolean;
    mNoCrew : boolean;
    munknown_bool_6E1 : boolean;
    munknown_bool_6E2 : boolean;
    mHasBeenCaptured : boolean;
    mActuallyPlacedOnMap : boolean;
    munknown_bool_6E5 : boolean;
    mIsDamaged : boolean;
    mIsFogged : boolean;
    mIsBeingRepaired : boolean;
    mHasBuildUp : boolean;
    mStuffEnabled : boolean;
    mHasCloakingData : number;
    mCloakRadius : number;
    mTranslucency : number;
    mStorageFilledSlots : number;
    mSecretProduction : TechnoTypeClass;
    mColorAdd : any;
    munknown_int_6FC : number;
    munknown_short_700 : number;
    mUpgradeLevel : number;
    mGateStage : number;
    mPrismStage : any;
    mPrismTargetCoords : any;
    mDelayBeforeFiring : number;
    mBunkerState : number;
}
class BuildingTypeClass
    extends TechnoTypeClass
{
    Find(pID_0 : number) : BuildingTypeClass;
    FindOrAllocate(pID_0 : number) : BuildingTypeClass;
    FindIndex(pID_0 : number) : number;
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
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mArrayIndex : number;
    mFoundationData : any;
    mBuildup : any;
    mBuildupLoaded : boolean;
    mBuildCat : any;
    mHalfDamageSmokeLocation1 : any;
    mHalfDamageSmokeLocation2 : any;
    malign_E24 : number;
    mGateCloseDelay : number;
    mLightVisibility : number;
    mLightIntensity : number;
    mLightRedTint : number;
    mLightGreenTint : number;
    mLightBlueTint : number;
    mPrimaryFirePixelOffset : any;
    mSecondaryFirePixelOffset : any;
    mToOverlay : OverlayTypeClass;
    mToTile : number;
    mBuildupFile : number;
    mBuildupSound : number;
    mPackupSound : number;
    mCreateUnitSound : number;
    mUnitEnterSound : number;
    mUnitExitSound : number;
    mWorkingSound : number;
    mNotWorkingSound : number;
    mPowersUpBuilding : number;
    mFreeUnit : UnitTypeClass;
    mSecretInfantry : InfantryTypeClass;
    mSecretUnit : UnitTypeClass;
    mSecretBuilding : BuildingTypeClass;
    mfield_EB0 : number;
    mAdjacent : number;
    mFactory : any;
    mTargetCoordOffset : any;
    mExitCoord : any;
    mFoundationOutside : any;
    mfield_ED8 : number;
    mDeployFacing : number;
    mPowerBonus : number;
    mPowerDrain : number;
    mExtraPowerBonus : number;
    mExtraPowerDrain : number;
    mFoundation : any;
    mHeight : number;
    mOccupyHeight : number;
    mMidPoint : number;
    mDoorStages : number;
    mBuildingAnimFrame : BuildingAnimFrameStruct;
    mBuildingAnim : BuildingAnimStruct;
    mUpgrades : number;
    mDeployingAnim : any;
    mDeployingAnimLoaded : boolean;
    mUnderDoorAnim : any;
    mUnderDoorAnimLoaded : boolean;
    mRubble : any;
    mRubbleLoaded : boolean;
    mRoofDeployingAnim : any;
    mRoofDeployingAnimLoaded : boolean;
    mUnderRoofDoorAnim : any;
    mUnderRoofDoorAnimLoaded : boolean;
    mDoorAnim : any;
    mSpecialZOverlay : any;
    mSpecialZOverlayZAdjust : number;
    mBibShape : any;
    mBibShapeLoaded : boolean;
    mNormalZAdjust : number;
    mAntiAirValue : number;
    mAntiArmorValue : number;
    mAntiInfantryValue : number;
    mZShapePointMove : any;
    munknown_1538 : number;
    munknown_153C : number;
    munknown_1540 : number;
    munknown_1544 : number;
    mExtraLight : number;
    mTogglePower : boolean;
    mHasSpotlight : boolean;
    mIsTemple : boolean;
    mIsPlug : boolean;
    mHoverPad : boolean;
    mBaseNormal : boolean;
    mEligibileForAllyBuilding : boolean;
    mEligibleForDelayKill : boolean;
    mNeedsEngineer : boolean;
    mCaptureEvaEvent : number;
    mProduceCashStartup : number;
    mProduceCashAmount : number;
    mProduceCashDelay : number;
    mInfantryGainSelfHeal : number;
    mUnitsGainSelfHeal : number;
    mRefinerySmokeFrames : number;
    mBib : boolean;
    mWall : boolean;
    mCapturable : boolean;
    mPowered : boolean;
    mPoweredSpecial : boolean;
    mOverpowerable : boolean;
    mSpyable : boolean;
    mCanC4 : boolean;
    mWantsExtraSpace : boolean;
    mUnsellable : boolean;
    mClickRepairable : boolean;
    mCanBeOccupied : boolean;
    mCanOccupyFire : boolean;
    mMaxNumberOccupants : number;
    mShowOccupantPips : boolean;
    mMuzzleFlash : any;
    mDamageFireOffset : any;
    mQueueingCell : any;
    mNumberImpassableRows : number;
    mRemoveOccupy : any;
    mAddOccupy : any;
    mRadar : boolean;
    mSpySat : boolean;
    mChargeAnim : boolean;
    mIsAnimDelayedFire : boolean;
    mSiloDamage : boolean;
    mUnitRepair : boolean;
    mUnitReload : boolean;
    mBunker : boolean;
    mCloning : boolean;
    mGrinding : boolean;
    mUnitAbsorb : boolean;
    mInfantryAbsorb : boolean;
    mSecretLab : boolean;
    mDoubleThick : boolean;
    mFlat : boolean;
    mDockUnload : boolean;
    mRecoilless : boolean;
    mHasStupidGuardMode : boolean;
    mBridgeRepairHut : boolean;
    mGate : boolean;
    mSAM : boolean;
    mConstructionYard : boolean;
    mNukeSilo : boolean;
    mRefinery : boolean;
    mWeeder : boolean;
    mWeaponsFactory : boolean;
    mLaserFencePost : boolean;
    mLaserFence : boolean;
    mFirestormWall : boolean;
    mHospital : boolean;
    mArmory : boolean;
    mEMPulseCannon : boolean;
    mTickTank : boolean;
    mTurretAnimIsVoxel : boolean;
    mBarrelAnimIsVoxel : boolean;
    mCloakGenerator : boolean;
    mSensorArray : boolean;
    mICBMLauncher : boolean;
    mArtillary : boolean;
    mHelipad : boolean;
    mOrePurifier : boolean;
    mFactoryPlant : boolean;
    mInfantryCostBonus : number;
    mUnitsCostBonus : number;
    mAircraftCostBonus : number;
    mBuildingsCostBonus : number;
    mDefensesCostBonus : number;
    mGDIBarracks : boolean;
    mNODBarracks : boolean;
    mYuriBarracks : boolean;
    mChargedAnimTime : number;
    mDelayedFireDelay : number;
    mSuperWeapon : number;
    mSuperWeapon2 : number;
    mGateStages : number;
    mPowersUpToLevel : number;
    mDamagedDoor : boolean;
    mInvisibleInGame : boolean;
    mTerrainPalette : boolean;
    mPlaceAnywhere : boolean;
    mExtraDamageStage : boolean;
    mAIBuildThis : boolean;
    mIsBaseDefense : boolean;
    mCloakRadiusInCells : number;
    mConcentricRadialIndicator : boolean;
    mPsychicDetectionRadius : number;
    mBarrelStartPitch : number;
    mVoxelBarrelFile : number;
    mVoxelBarrelOffsetToPitchPivotPoint : any;
    mVoxelBarrelOffsetToRotatePivotPoint : any;
    mVoxelBarrelOffsetToBuildingPivotPoint : any;
    mVoxelBarrelOffsetToBarrelEnd : any;
    mDemandLoad : boolean;
    mDemandLoadBuildup : boolean;
    mFreeBuildup : boolean;
    mIsThreatRatingNode : boolean;
    mPrimaryFireDualOffset : boolean;
    mProtectWithWall : boolean;
    mCanHideThings : boolean;
    mCrateBeneath : boolean;
    mLeaveRubble : boolean;
    mCrateBeneathIsMoney : boolean;
    mTheaterSpecificID : number;
    mNumberOfDocks : number;
    mDockingOffsets : any;
}
class BuildingAnimStruct
{
    mAnim : number;
    mDamaged : number;
    mGarrisoned : number;
    mPosition : any;
    mZAdjust : number;
    mYSort : number;
    mPowered : boolean;
    mPoweredLight : boolean;
    mPoweredEffect : boolean;
    mPoweredSpecial : boolean;
}
class OverlayTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : OverlayTypeClass;
    FindOrAllocate(pID_0 : number) : OverlayTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    vt_entry_6C(pDest_0 : any, pSrc_1 : any) : any;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    Draw(pClientCoords_0 : any, pClipRect_1 : any, nFrame_2 : number) : void;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mLandType : any;
    mCellAnim : AnimTypeClass;
    mDamageLevels : number;
    mStrength : number;
    mWall : boolean;
    mTiberium : boolean;
    mCrate : boolean;
    mCrateTrigger : boolean;
    mNoUseTileLandType : boolean;
    mIsVeinholeMonster : boolean;
    mIsVeins : boolean;
    mImageLoaded : boolean;
    mExplodes : boolean;
    mChainReaction : boolean;
    mOverrides : boolean;
    mDrawFlat : boolean;
    mIsRubble : boolean;
    mIsARock : boolean;
    mRadarColor : any;
}
class UnitTypeClass
    extends TechnoTypeClass
{
    Find(pID_0 : number) : UnitTypeClass;
    FindOrAllocate(pID_0 : number) : UnitTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mArrayIndex : number;
    mMovementRestrictedTo : any;
    mHalfDamageSmokeLocation : any;
    mPassive : boolean;
    mCrateGoodie : boolean;
    mHarvester : boolean;
    mWeeder : boolean;
    munknown_E10 : boolean;
    mHasTurret : boolean;
    mDeployToFire : boolean;
    mIsSimpleDeployer : boolean;
    mIsTilter : boolean;
    mUseTurretShadow : boolean;
    mTooBigToFitUnderBridge : boolean;
    mCanBeach : boolean;
    mSmallVisceroid : boolean;
    mLargeVisceroid : boolean;
    mCarriesCrate : boolean;
    mNonVehicle : boolean;
    mStandingFrames : number;
    mDeathFrames : number;
    mDeathFrameRate : number;
    mStartStandFrame : number;
    mStartWalkFrame : number;
    mStartFiringFrame : number;
    mStartDeathFrame : number;
    mMaxDeathCounter : number;
    mFacings : number;
    mFiringSyncFrame0 : number;
    mFiringSyncFrame1 : number;
    mBurstDelay0 : number;
    mBurstDelay1 : number;
    mBurstDelay2 : number;
    mBurstDelay3 : number;
    mAltImage : any;
    mWalkFrames : number;
    mFiringFrames : number;
    mAltImageFile : number;
}
class BuildingAnimFrameStruct
{
    mdwUnknown : number;
    mFrameCount : number;
    mFrameDuration : number;
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
    FindByOwnerAndProduct(pHouse_0 : HouseClass, pItem_1 : TechnoTypeClass) : FactoryClass;
    sAbsID : any;
    sArray : any;
    mProduction : StageClass;
    mQueuedObjects : any;
    mObject : TechnoClass;
    mOnHold : boolean;
    mIsDifferent : boolean;
    mBalance : number;
    mOriginalBalance : number;
    mSpecialItem : number;
    mOwner : HouseClass;
    mIsSuspended : boolean;
    mIsManual : boolean;
}
class StageClass
{
    Start(rate_0 : number) : void;
    Start(rate_0 : number, step_1 : number) : void;
    Update() : boolean;
    mValue : number;
    mHasChanged : boolean;
    mTimer : CDTimerClass;
    mRate : number;
    mStep : number;
}
class InfantryClass
    extends FootClass
{
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    IsDeployed() : boolean;
    PlayAnim(index_0 : any, force_1 : boolean, randomStartFrame_2 : boolean) : boolean;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mType : InfantryTypeClass;
    mSequenceAnim : any;
    munknown_Timer_6C8 : CDTimerClass;
    mPanicDurationLeft : number;
    mPermanentBerzerk : boolean;
    mTechnician : boolean;
    munknown_bool_6DA : boolean;
    mCrawling : boolean;
    munknown_bool_6DC : boolean;
    munknown_bool_6DD : boolean;
    munknown_6E0 : number;
    mShouldDeploy : boolean;
    munknown_int_6E8 : number;
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
    sAbsDerivateID : any;
    sArray : any;
    mPlanningPathIdx : number;
    mWaypointNearbyAccessibleCellDelta : any;
    mWaypointCell : any;
    munknown_52C : number;
    munknown_530 : number;
    munknown_534 : number;
    mWalkedFramesSoFar : number;
    munknown_bool_53C : boolean;
    munknown_540 : number;
    mAudio7 : any;
    m__Audio7 : number;
    mCurrentMapCoords : any;
    mLastMapCoords : any;
    mLastFlightMapCoords : any;
    mCurrentJumpjetMapCoords : any;
    munknown_coords_568 : any;
    mSpeedPercentage : number;
    mSpeedMultiplier : number;
    munknown_abstract_array_588 : any;
    m__unknown_abstract_array_588 : number;
    munknown_5A0 : AbstractClass;
    mDestination : AbstractClass;
    mLastDestination : AbstractClass;
    mNavQueue : any;
    m__NavQueue : number;
    munknown_int_5C4 : number;
    munknown_5C8 : number;
    munknown_5CC : number;
    munknown_5D0 : number;
    munknown_bool_5D1 : boolean;
    mTeam : TeamClass;
    mNextTeamMember : FootClass;
    munknown_5DC : number;
    mPathDirections : number;
    mPathDelayTimer : CDTimerClass;
    m__PathDelayTimer : number;
    munknown_int_64C : number;
    munknown_timer_650 : CDTimerClass;
    m__unknown_timer_650 : number;
    mSightTimer : CDTimerClass;
    m__SightTimer : number;
    mBlockagePathTimer : CDTimerClass;
    m__BlockagePathTimer : number;
    mLocomotor : any;
    m__Locomotor : number;
    munknown_point3d_678 : any;
    mTubeIndex : number;
    munknown_bool_685 : boolean;
    mWaypointIndex : number;
    munknown_bool_687 : boolean;
    munknown_bool_688 : boolean;
    mIsInitiated : boolean;
    mShouldScanForTarget : boolean;
    munknown_bool_68B : boolean;
    mIsDeploying : boolean;
    mIsFiring : boolean;
    munknown_bool_68E : boolean;
    mShouldEnterAbsorber : boolean;
    mShouldEnterOccupiable : boolean;
    mShouldGarrisonStructure : boolean;
    mParasiteEatingMe : FootClass;
    munknown_698 : number;
    mParasiteImUsing : ParasiteClass;
    mParalysisTimer : CDTimerClass;
    m__ParalysisTimer : number;
    munknown_bool_6AC : boolean;
    mIsAttackedByLocomotor : boolean;
    mIsLetGoByLocomotor : boolean;
    munknown_bool_6AF : boolean;
    munknown_bool_6B0 : boolean;
    munknown_bool_6B1 : boolean;
    munknown_bool_6B2 : boolean;
    munknown_bool_6B3 : boolean;
    munknown_bool_6B4 : boolean;
    munknown_bool_6B5 : boolean;
    mFrozenStill : boolean;
    munknown_bool_6B7 : boolean;
    munknown_bool_6B8 : boolean;
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
    sAbsID : any;
    sArray : any;
    mType : TeamTypeClass;
    mCurrentScript : ScriptClass;
    mOwner : HouseClass;
    mTarget : HouseClass;
    mSpawnCell : CellClass;
    mClosestMember : FootClass;
    mQueuedFocus : AbstractClass;
    mFocus : AbstractClass;
    munknown_44 : number;
    mTotalObjects : number;
    mTotalThreatValue : number;
    mCreationFrame : number;
    mFirstUnit : FootClass;
    mGuardAreaTimer : CDTimerClass;
    mSuspendTimer : CDTimerClass;
    mTag : TagClass;
    mIsTransient : boolean;
    mNeedsReGrouping : boolean;
    mGuardSlowerIsNotUnderStrength : boolean;
    mIsForcedActive : boolean;
    mIsHasBeen : boolean;
    mIsFullStrength : boolean;
    mIsUnderStrength : boolean;
    mIsReforming : boolean;
    mIsLagging : boolean;
    mNeedsToDisappear : boolean;
    mJustDisappeared : boolean;
    mIsMoving : boolean;
    mStepCompleted : boolean;
    mTargetNotAssigned : boolean;
    mIsLeavingMap : boolean;
    mIsSuspended : boolean;
    mAchievedGreatSuccess : boolean;
    mCountObjects : number;
}
class TeamTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : TeamTypeClass;
    FindOrAllocate(pID_0 : number) : TeamTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    LoadFromINIList(pINI_0 : any, IsGlobal_1 : boolean) : boolean;
    CreateTeam(pHouse_0 : HouseClass) : TeamClass;
    DestroyAllInstances() : void;
    GetGroup() : number;
    GetWaypoint(buffer_0 : any) : any;
    GetTransportWaypoint(buffer_0 : any) : any;
    CanRecruitUnit(pUnit_0 : FootClass, pOwner_1 : HouseClass) : boolean;
    FlashAllInstances(Duration_0 : number) : void;
    FindFirstInstance() : TeamClass;
    ProcessTaskForce() : void;
    ProcessAllTaskforces() : void;
    GetHouse() : HouseClass;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mGroup : number;
    mVeteranLevel : number;
    mLoadable : boolean;
    mFull : boolean;
    mAnnoyance : boolean;
    mGuardSlower : boolean;
    mRecruiter : boolean;
    mAutocreate : boolean;
    mPrebuild : boolean;
    mReinforce : boolean;
    mWhiner : boolean;
    mAggressive : boolean;
    mLooseRecruit : boolean;
    mSuicide : boolean;
    mDroppod : boolean;
    mUseTransportOrigin : boolean;
    mDropshipLoadout : boolean;
    mOnTransOnly : boolean;
    mPriority : number;
    mMax : number;
    mfield_BC : number;
    mMindControlDecision : number;
    mOwner : HouseClass;
    midxHouse : number;
    mTechLevel : number;
    mTag : TagClass;
    mWaypoint : number;
    mTransportWaypoint : number;
    mcntInstances : number;
    mScriptType : ScriptTypeClass;
    mTaskForce : TaskForceClass;
    mIsGlobal : number;
    mfield_EC : number;
    mfield_F0 : boolean;
    mfield_F1 : boolean;
    mAvoidThreats : boolean;
    mIonImmune : boolean;
    mTransportsReturnOnUnload : boolean;
    mAreTeamMembersRecruitable : boolean;
    mIsBaseDefense : boolean;
    mOnlyTargetHouseEnemy : boolean;
}
class TagClass
    extends AbstractClass
{
    GetInstance(pType_0 : TagTypeClass) : TagClass;
    DeleteAll() : void;
    NotifyGlobalChanged(idxGlobal_0 : number) : void;
    NotifyLocalChanged(idxLocal_0 : number) : void;
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
    sAbsID : any;
    sArray : any;
    mType : TagTypeClass;
    mFirstTrigger : TriggerClass;
    mInstanceCount : number;
    mDefaultCoords : any;
    mDestroyed : boolean;
    mIsExecuting : boolean;
}
class TagTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : TagTypeClass;
    FindOrAllocate(pID_0 : number) : TagTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    WhatAmI() : any;
    Size() : number;
    ComputeCRC(crc_0 : any) : void;
    GetArrayIndex() : number;
    LoadFromINI(pINI_0 : any) : boolean;
    SaveToINI(pINI_0 : any) : boolean;
    LoadFromINIList(pINI_0 : any) : void;
    SaveToINIList(pINI_0 : any) : void;
    FindByNameOrID(pName_0 : number) : TagTypeClass;
    GetFlags() : any;
    HasAllowWinAction() : boolean;
    HasCrossesHorizontalLineEvent() : boolean;
    HasCrossesVerticalLineEvent() : boolean;
    HasZoneEntryByEvent() : boolean;
    AddTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    RemoveTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    ContainsTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mPersistence : any;
    mFirstTrigger : TriggerTypeClass;
}
class TriggerTypeClass
{
}
class TriggerClass
    extends AbstractClass
{
    GetInstance(pType_0 : TriggerTypeClass) : TriggerClass;
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
    sAbsID : any;
    sArray : any;
    mType : TriggerTypeClass;
    mNextTrigger : TriggerClass;
    mHouse : HouseClass;
    mDestroyed : boolean;
    mTimer : CDTimerClass;
    mOccuredEvents : number;
    mEnabled : boolean;
}
class ScriptTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : ScriptTypeClass;
    FindOrAllocate(pID_0 : number) : ScriptTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    LoadFromINIList(pINI_0 : any, IsGlobal_1 : boolean) : boolean;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mIsGlobal : boolean;
    mActionsCount : number;
    mScriptActions : ScriptActionNode;
}
class ScriptActionNode
{
    mAction : number;
    mArgument : number;
}
class TaskForceClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : TaskForceClass;
    FindOrAllocate(pID_0 : number) : TaskForceClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    sAbsID : any;
    sArray : any;
    mGroup : number;
    mCountEntries : number;
    mIsGlobal : boolean;
    mEntries : TaskForceEntryStruct;
}
class TaskForceEntryStruct
{
    mAmount : number;
    mType : TechnoTypeClass;
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
    sAbsID : any;
    mType : ScriptTypeClass;
    mfield_28 : number;
    mCurrentMission : number;
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
    sAbsID : any;
    sArray : any;
    mOwner : FootClass;
    mVictim : FootClass;
    mSuppressionTimer : CDTimerClass;
    mDamageDeliveryTimer : CDTimerClass;
    mGrappleAnim : AnimClass;
    mGrappleState : any;
    mGrappleAnimFrame : number;
    mGrappleAnimDelay : number;
    mGrappleAnimGotInvalid : boolean;
}
class BuildingLightClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SetBehaviour(mode_0 : any) : void;
    sAbsID : any;
    sArray : any;
    mSpeed : number;
    mfield_B8 : any;
    mfield_C4 : any;
    mAcceleration : number;
    mDirection : boolean;
    mBehaviourMode : any;
    mFollowingObject : ObjectClass;
    mOwnerObject : TechnoClass;
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
    UpdateLightConverts(value_0 : number) : void;
    sAbsID : any;
    mLightIntensity : number;
    mLightTint : TintStruct;
    mDetailLevel : number;
    mLocation : any;
    mLightVisibility : number;
    mActivated : boolean;
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
    ReadINI(pINI_0 : any) : void;
    WriteINI(pINI_0 : any) : void;
    ShouldCrashIt(pTarget_0 : TechnoClass) : boolean;
    AssignDestination_7447B0(pTarget_0 : AbstractClass) : AbstractClass;
    AStarAttempt(cell1_0 : any, cell2_1 : any) : boolean;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    munknown_int_6C0 : number;
    mType : UnitTypeClass;
    mFollowerCar : UnitClass;
    mFlagHouseIndex : number;
    mHasFollowerCar : boolean;
    mUnloading : boolean;
    mIsHarvesting : boolean;
    mTerrainPalette : boolean;
    munknown_int_6D4 : number;
    mDeathFrameCounter : number;
    mElectricBolt : EBolt;
    mDeployed : boolean;
    mDeploying : boolean;
    mUndeploying : boolean;
    mNonPassengerCount : number;
    mToolTipText : number;
}
class EBolt
{
    SetOwner(pOwner_0 : UnitClass, idxWeapon_1 : number) : void;
    ClearOwner() : void;
    GetSourceCoords(outBuffer_0 : any) : any;
    GetSourceCoords() : any;
    Fire(P1_0 : any, P2_1 : any, arg18_2 : number) : void;
    sArray : any;
    mPoint1 : any;
    mPoint2 : any;
    munknown_18 : number;
    mRandom : number;
    mOwner : TechnoClass;
    mWeaponSlot : number;
    mLifetime : number;
    mAlternateColor : boolean;
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
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mType : AircraftTypeClass;
    munknown_bool_6C8 : boolean;
    mHasPassengers : boolean;
    mIsKamikaze : boolean;
    mDockNowHeadingTo : BuildingClass;
    munknown_bool_6D0 : boolean;
    munknown_bool_6D1 : boolean;
    munknown_bool_6D2 : boolean;
    munknown_char_6D3 : number;
    munknown_bool_6D4 : boolean;
    munknown_bool_6D5 : boolean;
}
class AircraftTypeClass
    extends TechnoTypeClass
{
    Find(pID_0 : number) : AircraftTypeClass;
    FindOrAllocate(pID_0 : number) : AircraftTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mArrayIndex : number;
    mCarryall : boolean;
    mTrailer : AnimTypeClass;
    mSpawnDelay : number;
    mRotors : boolean;
    mCustomRotor : boolean;
    mLandable : boolean;
    mFlyBy : boolean;
    mFlyBack : boolean;
    mAirportBound : boolean;
    mFighter : boolean;
}
class TerrainClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    sAbsID : any;
    sArray : any;
    mAnimation : StageClass;
    mType : TerrainTypeClass;
    mIsBurning : boolean;
    mIsCrumbling : boolean;
    munknown_rect_D0 : any;
}
class TerrainTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : TerrainTypeClass;
    FindOrAllocate(pID_0 : number) : TerrainTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mFoundation : number;
    mRadarColor : any;
    mAnimationRate : number;
    mAnimationProbability : number;
    mTemperateOccupationBits : number;
    mSnowOccupationBits : number;
    mWaterBound : boolean;
    mSpawnsTiberium : boolean;
    mIsFlammable : boolean;
    mIsAnimated : boolean;
    mIsVeinhole : boolean;
    mFoundationData : any;
}
class TiberiumClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : TiberiumClass;
    FindOrAllocate(pID_0 : number) : TiberiumClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    GetSizeMax(pcbSize_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    RegisterForGrowth(cell_0 : any) : void;
    FindIndex(idxOverlayType_0 : number) : number;
    Find(idxOverlayType_0 : number) : TiberiumClass;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mSpread : number;
    mSpreadPercentage : number;
    mGrowth : number;
    mGrowthPercentage : number;
    mValue : number;
    mPower : number;
    mColor : number;
    mDebris : any;
    m__Debris : number;
    mImage : OverlayTypeClass;
    mNumFrames : number;
    mNumImages : number;
    mfield_EC : number;
    mSpreadLogic : TiberiumLogic;
    m__SpreadLogic : number;
    mGrowthLogic : TiberiumLogic;
    m__GrowthLogic : number;
}
class TiberiumLogic
{
    Construct(nCount_0 : number) : void;
    Destruct() : void;
    mCount : number;
    mQueue : any;
    mCellIndexesWithTiberium : boolean;
    mNodes : any;
    mTimer : CDTimerClass;
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
    sAbsID : any;
    sArray : any;
    mLightSource : LightSourceClass;
    mRadLevelTimer : CDTimerClass;
    m__RadLevelTimer : number;
    mRadLightTimer : CDTimerClass;
    m__RadLightTimer : number;
    mBaseCell : any;
    mSpread : number;
    mSpreadInLeptons : number;
    mRadLevel : number;
    mLevelSteps : number;
    mIntensity : number;
    mTint : TintStruct;
    mIntensitySteps : number;
    mIntensityDecrement : number;
    mRadDuration : number;
    mRadTimeLeft : number;
}
class RGBClass
{
    Adjust(ratio_0 : number, rgb_1 : RGBClass) : void;
    Difference(rgb_0 : RGBClass) : number;
    ToInt() : number;
    sWhite : any;
    sRedShiftLeft : any;
    sRedShiftRight : any;
    sGreenShiftLeft : any;
    sGreenShiftRight : any;
    sBlueShiftLeft : any;
    sBlueShiftRight : any;
    mRed : number;
    mGreen : number;
    mBlue : number;
}
class LaserDrawClass
{
    mProgress : StageClass;
    m__Progress : number;
    mThickness : number;
    mIsHouseColor : boolean;
    mIsSupported : boolean;
    mSource : any;
    mTarget : any;
    mZAdjust : number;
    mfield_40 : number;
    mInnerColor : any;
    mOuterColor : any;
    mOuterSpread : any;
    mDuration : number;
    mBlinks : boolean;
    mBlinkState : boolean;
    mFades : boolean;
    mStartIntensity : number;
    mEndIntensity : number;
}
class FlashData
{
    Update() : boolean;
    mDurationRemaining : number;
    mFlashingNow : boolean;
}
class PassengersClass
{
    AddPassenger(pPassenger_0 : FootClass) : void;
    GetFirstPassenger() : FootClass;
    RemoveFirstPassenger() : FootClass;
    GetTotalSize() : number;
    IndexOf(candidate_0 : FootClass) : number;
    mNumPassengers : number;
    mFirstPassenger : FootClass;
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
    mVeterancy : number;
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
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    mOwner : TechnoClass;
    mTarget : TechnoClass;
    mLifeTimer : CDTimerClass;
    munknown_pointer_38 : void;
    mSourceSW : SuperClass;
    mNextTemporal : TemporalClass;
    mPrevTemporal : TemporalClass;
    mWarpRemaining : number;
    mWarpPerStep : number;
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
    NameReadiness() : number;
    ShouldDrawProgress() : boolean;
    ShouldFlashTab() : boolean;
    sAbsID : any;
    sAbsVTable : number;
    sArray : any;
    sShowTimers : any;
    mCustomChargeTime : number;
    mType : SuperWeaponTypeClass;
    mOwner : HouseClass;
    mRechargeTimer : CDTimerClass;
    mBlinkState : boolean;
    mBlinkTimer : any;
    mSpecialSoundDuration : number;
    mSpecialSoundLocation : any;
    mCanHold : boolean;
    mChronoMapCoords : any;
    mAnimation : AnimClass;
    mAnimationGotInvalid : boolean;
    mIsPresent : boolean;
    mIsOneTime : boolean;
    mIsReady : boolean;
    mIsSuspended : boolean;
    mReadyFrame : number;
    mCameoChargeState : number;
    mChargeDrainState : any;
}
class SuperWeaponTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : SuperWeaponTypeClass;
    FindOrAllocate(pID_0 : number) : SuperWeaponTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    MouseOverObject(cell_0 : any, pObjBelowMouse_1 : ObjectClass) : any;
    FindFirstOfAction(Action_0 : any) : SuperWeaponTypeClass;
    sAbsID : any;
    sArray : any;
    mArrayIndex : number;
    mWeaponType : WeaponTypeClass;
    mRechargeVoice : number;
    mChargingVoice : number;
    mImpatientVoice : number;
    mSuspendVoice : number;
    mRechargeTime : number;
    mType : any;
    mSidebarImage : any;
    mAction : any;
    mSpecialSound : number;
    mStartSound : number;
    mAuxBuilding : BuildingTypeClass;
    mSidebarImageFile : number;
    mUseChargeDrain : boolean;
    mIsPowered : boolean;
    mDisableableFromShell : boolean;
    mFlashSidebarTabFrames : number;
    mAIDefendAgainst : boolean;
    mPreClick : boolean;
    mPostClick : boolean;
    mPreDependent : number;
    mShowTimer : boolean;
    mManualControl : boolean;
    mRange : number;
    mLineMultiplier : number;
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
    sAbsID : any;
    mAirstrikeTeam : number;
    mEliteAirstrikeTeam : number;
    mAirstrikeTeamTypeIndex : number;
    mEliteAirstrikeTeamTypeIndex : number;
    munknown_34 : number;
    munknown_38 : number;
    mIsOnMission : boolean;
    munknown_bool_3D : boolean;
    mTeamDissolveFrame : number;
    mAirstrikeRechargeTime : number;
    mEliteAirstrikeRechargeTime : number;
    mOwner : TechnoClass;
    mTarget : ObjectClass;
    mAirstrikeTeamType : AircraftTypeClass;
    mEliteAirstrikeTeamType : AircraftTypeClass;
    mFirstObject : FootClass;
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
    sAbsID : any;
    sArray : any;
    mControlNodes : any;
    mMaxControlNodes : number;
    mInfiniteMindControl : boolean;
    mOverloadDeathSoundPlayed : boolean;
    mOverloadPipState : number;
    mOwner : TechnoClass;
    mOverloadDamageDelay : number;
}
class ControlNode
{
    mUnit : TechnoClass;
    mOriginalOwner : HouseClass;
    mLinkDrawTimer : CDTimerClass;
    m__LinkDrawTimer : number;
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
    sAbsID : any;
    sArray : any;
    mOwner : TechnoClass;
    mSpawnType : AircraftTypeClass;
    mSpawnCount : number;
    mRegenRate : number;
    mReloadRate : number;
    mSpawnedNodes : any;
    mUpdateTimer : CDTimerClass;
    mSpawnTimer : CDTimerClass;
    mTarget : AbstractClass;
    mNewTarget : AbstractClass;
    mStatus : any;
}
class SpawnControl
{
    mUnit : AircraftClass;
    mStatus : any;
    mSpawnTimer : CDTimerClass;
    mIsSpawnMissile : number;
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
    sAbsID : any;
    sArray : any;
    mOwner : TechnoClass;
    mSlaveType : InfantryTypeClass;
    mSlaveCount : number;
    mRegenRate : number;
    mReloadRate : number;
    mSlaveNodes : any;
    mRespawnTimer : CDTimerClass;
    mState : any;
    mLastScanFrame : number;
}
class ParticleSystemClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    sAbsID : any;
    sArray : any;
    mType : ParticleSystemTypeClass;
    mSpawnDistanceToOwner : any;
    mParticles : any;
    m__Particles : number;
    mTargetCoords : any;
    mOwner : ObjectClass;
    mTarget : AbstractClass;
    mSpawnFrames : number;
    mLifetime : number;
    mSparkSpawnFrames : number;
    mSpotlightRadius : number;
    mTimeToDie : boolean;
    munknown_bool_F9 : boolean;
    mOwnerHouse : HouseClass;
}
class ParticleSystemTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : ParticleSystemTypeClass;
    FindOrAllocate(pID_0 : number) : ParticleSystemTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(mcoords_0 : any, owner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sArray : any;
    mHoldsWhat : number;
    mSpawns : boolean;
    mSpawnFrames : number;
    mSlowdown : number;
    mParticleCap : number;
    mSpawnRadius : number;
    mSpawnCutoff : number;
    mSpawnTranslucencyCutoff : number;
    mBehavesLike : any;
    mLifetime : number;
    mSpawnDirection : any;
    mParticlesPerCoord : number;
    mSpiralDeltaPerCoord : number;
    mSpiralRadius : number;
    mPositionPerturbationCoefficient : number;
    mMovementPerturbationCoefficient : number;
    mVelocityPerturbationCoefficient : number;
    mSpawnSparkPercentage : number;
    mSparkSpawnFrames : number;
    mLightSize : number;
    mLaserColor : any;
    mLaser : boolean;
    mOneFrameLight : boolean;
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
    sAbsID : any;
    sArray : any;
    mType : ParticleTypeClass;
    munknown_B0 : number;
    munknown_B1 : number;
    munknown_B2 : number;
    munknown_B4 : number;
    munknown_B8 : number;
    munknown_BC : number;
    mVelocity : any;
    munknown_CC : number;
    munknown_double_D0 : number;
    munknown_D8 : number;
    munknown_DC : number;
    munknown_E0 : number;
    mSpeed : number;
    munknown_coords_E8 : any;
    munknown_coords_F4 : any;
    munknown_coords_100 : any;
    munknown_vector3d_10C : any;
    munknown_vector3d_118 : any;
    mParticleSystem : ParticleSystemClass;
    mRemainingEC : number;
    mRemainingDC : number;
    mStateAIAdvance : number;
    munknown_12D : number;
    mStartStateAI : number;
    mTranslucency : number;
    munknown_130 : number;
    munknown_131 : number;
}
class ParticleTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : ParticleTypeClass;
    FindOrAllocate(pID_0 : number) : ParticleTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(mcoords_0 : any, owner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sArray : any;
    mNextParticleOffset : any;
    mXVelocity : number;
    mYVelocity : number;
    mMinZVelocity : number;
    mZVelocityRange : number;
    mColorSpeed : number;
    mColorList : any;
    mStartColor1 : any;
    mStartColor2 : any;
    mMaxDC : number;
    mMaxEC : number;
    mWarhead : WarheadTypeClass;
    mDamage : number;
    mStartFrame : number;
    mNumLoopFrames : number;
    mTranslucency : number;
    mWindEffect : number;
    mVelocity : number;
    mDeacc : number;
    mRadius : number;
    mDeleteOnStateLimit : boolean;
    mEndStateAI : number;
    mStartStateAI : number;
    mStateAIAdvance : number;
    mFinalDamageState : number;
    mTranslucent25State : number;
    mTranslucent50State : number;
    mNormalized : boolean;
    mNextParticle : ParticleTypeClass;
    mBehavesLike : any;
}
class WarheadTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : WarheadTypeClass;
    FindOrAllocate(pID_0 : number) : WarheadTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    sAbsID : any;
    sArray : any;
    mDeform : number;
    mVerses : number;
    mProneDamage : number;
    mDeformTreshold : number;
    mAnimList : any;
    mInfDeath : any;
    mCellSpread : number;
    mCellInset : number;
    mPercentAtMax : number;
    mCausesDelayKill : boolean;
    mDelayKillFrames : number;
    mDelayKillAtMax : number;
    mCombatLightSize : number;
    mParticle : ParticleTypeClass;
    mWall : boolean;
    mWallAbsoluteDestroyer : boolean;
    mPenetratesBunker : boolean;
    mWood : boolean;
    mTiberium : boolean;
    munknown_bool_149 : boolean;
    mSparky : boolean;
    mSonic : boolean;
    mFire : boolean;
    mConventional : boolean;
    mRocker : boolean;
    mDirectRocker : boolean;
    mBright : boolean;
    mCLDisableRed : boolean;
    mCLDisableGreen : boolean;
    mCLDisableBlue : boolean;
    mEMEffect : boolean;
    mMindControl : boolean;
    mPoison : boolean;
    mIvanBomb : boolean;
    mElectricAssault : boolean;
    mParasite : boolean;
    mTemporal : boolean;
    mIsLocomotor : boolean;
    mLocomotor : any;
    mAirstrike : boolean;
    mPsychedelic : boolean;
    mBombDisarm : boolean;
    mParalyzes : number;
    mCulling : boolean;
    mMakesDisguise : boolean;
    mNukeMaker : boolean;
    mRadiation : boolean;
    mPsychicDamage : boolean;
    mAffectsAllies : boolean;
    mBullets : boolean;
    mVeinhole : boolean;
    mShakeXlo : number;
    mShakeXhi : number;
    mShakeYlo : number;
    mShakeYhi : number;
    mDebrisTypes : any;
    mDebrisMaximums : any;
    mMaxDebris : number;
    mMinDebris : number;
}
class VoxelAnimTypeClass
    extends ObjectTypeClass
{
    Find(pID_0 : number) : VoxelAnimTypeClass;
    FindOrAllocate(pID_0 : number) : VoxelAnimTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    WhatAmI() : any;
    Size() : number;
    SpawnAtMapCoords(pMapCoords_0 : any, pOwner_1 : HouseClass) : boolean;
    CreateObject(owner_0 : HouseClass) : ObjectClass;
    sAbsID : any;
    sArray : any;
    mNormalized : boolean;
    mTranslucent : boolean;
    mSourceShared : boolean;
    mVoxelIndex : number;
    mDuration : number;
    mElasticity : number;
    mMinAngularVelocity : number;
    mMaxAngularVelocity : number;
    mMinZVel : number;
    mMaxZVel : number;
    mMaxXYVel : number;
    mIsMeteor : boolean;
    mSpawns : VoxelAnimTypeClass;
    mSpawnCount : number;
    mStartSound : number;
    mStopSound : number;
    mBounceAnim : AnimTypeClass;
    mExpireAnim : AnimTypeClass;
    mTrailerAnim : AnimTypeClass;
    mDamage : number;
    mDamageRadius : number;
    mWarhead : WarheadTypeClass;
    mAttachedSystem : ParticleSystemTypeClass;
    mIsTiberium : boolean;
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
    sAbsID : any;
    sArray : any;
    mTarget : TechnoClass;
    mType : any;
    msomeCoords : any;
    mfield_BC : number;
    mfield_C0 : number;
    mfield_C4 : number;
    mfield_C8 : number;
    mfield_CC : number;
    mfield_D0 : number;
    mfield_D4 : number;
    mfield_D8 : number;
    mfield_DC : number;
    mfield_E0 : number;
    mfield_E4 : number;
    mfield_E8 : number;
    mfield_EC : number;
    mfield_F0 : number;
    mfield_F4 : number;
    mfield_F8 : number;
    mfield_FC : number;
    mfield_100 : number;
    mfield_104 : number;
    mfield_108 : number;
    mfield_10C : number;
    mfield_110 : number;
    mfield_114 : number;
    mfield_118 : number;
    mfield_11C : number;
    mfield_120 : number;
    mfield_124 : number;
    mfield_128 : number;
    mfield_12C : number;
    mfield_12D : number;
    mfield_12E : number;
    mfield_12F : number;
    mWaveIntensity : number;
    mfield_134 : number;
    mfield_138 : number;
    mfield_13C : number;
    mfield_140 : number;
    mfield_144 : number;
    mfield_148 : number;
    mfield_14C : number;
    mfield_150 : number;
    mfield_154 : number;
    mfield_158 : number;
    mfield_15C : number;
    mfield_160 : number;
    mfield_164 : number;
    mfield_168 : number;
    mfield_16C : number;
    mfield_170 : number;
    mfield_174 : number;
    mfield_178 : number;
    mfield_17C : number;
    mfield_180 : number;
    mfield_184 : number;
    mfield_188 : number;
    mfield_18C : number;
    mfield_190 : number;
    mfield_194 : number;
    mfield_198 : number;
    mfield_19C : number;
    mfield_1A0 : number;
    mfield_1A4 : number;
    mfield_1A8 : number;
    mfield_1AC : number;
    mfield_1B0 : number;
    mfield_1B4 : number;
    mfield_1B8 : number;
    mfield_1BC : number;
    mfield_1C0 : number;
    mfield_1C4 : number;
    mfield_1C8 : number;
    mfield_1CC : number;
    mLaserIntensity : number;
    mOwner : TechnoClass;
    mFacing : FacingClass;
    mCells : any;
    munknown_208 : number;
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
    mRate1 : number;
    mActionTimer : CDTimerClass;
    mRate2 : number;
    mState1 : boolean;
    mState2 : boolean;
}
class RecoilData
{
    Update() : void;
    Fire() : void;
    mTurret : TurretControl;
    mTravelPerFrame : number;
    mTravelSoFar : number;
    mState : any;
    mTravelFramesLeft : number;
}
class TurretControl
{
    mTravel : number;
    mCompressFrames : number;
    mRecoverFrames : number;
    mHoldFrames : number;
}
class RadBeam
{
    Allocate(mode_0 : any) : RadBeam;
    SetColor(color_0 : any) : void;
    SetCoordsSource(loc_0 : any) : void;
    SetCoordsTarget(loc_0 : any) : void;
    sArray : any;
    munknown_0 : number;
    mOwner : TechnoClass;
    munknown_8 : number;
    munknown_C : number;
    mType : any;
    munknown_14 : number;
    munknown_18 : number;
    mColor : any;
    mSourceLocation : any;
    mTargetLocation : any;
    mPeriod : number;
    mAmplitude : number;
    munknown_48 : number;
    munknown_50 : number;
    munknown_54 : number;
    munknown_58 : number;
    munknown_5C : number;
    munknown_60 : number;
    munknown_64 : number;
    munknown_68 : number;
    mAnotherLocation : any;
    munknown_7C : number;
    munknown_80 : number;
    munknown_88 : number;
    munknown_8C : number;
    mAndAnotherLocation : any;
    munknown_9C : number;
    munknown_A0 : number;
    munknown_A4 : number;
    munknown_A8 : number;
    munknown_AC : number;
    munknown_B0 : number;
    munknown_B4 : number;
    munknown_B8 : number;
    munknown_C0 : number;
    munknown_C4 : number;
}
class PlanningTokenClass
{
    sArray : any;
    mOwnerUnit : TechnoClass;
    mPlanningNodes : any;
    mfield_1C : boolean;
    mfield_1D : boolean;
    munknown_20_88 : number;
    m__unknown_20_88 : number;
    mfield_8C : number;
    mClosedLoopNodeCount : number;
    mStepsToClosedLoop : number;
    mfield_98 : boolean;
    mfield_99 : boolean;
}
class PlanningNodeClass
{
    sUnknown1 : any;
    sUnknown2 : any;
    sUnknown3 : any;
    sPlanningModeActive : any;
    mPlanningMembers : any;
    mfield_18 : number;
    mfield_1C : boolean;
    mPlanningBranches : any;
}
class PlanningMemberClass
{
    mOwner : TechnoClass;
    mPacket : number;
    mfield_8 : number;
    mfield_C : number;
}
class PlanningBranchClass
{
}
class BulletData
{
    mUnknownTimer : CDTimerClass;
    mArmTimer : CDTimerClass;
    mLocation : any;
    mDistance : number;
}
class AbilitiesStruct
{
    mFASTER : boolean;
    mSTRONGER : boolean;
    mFIREPOWER : boolean;
    mSCATTER : boolean;
    mROF : boolean;
    mSIGHT : boolean;
    mCLOAK : boolean;
    mTIBERIUM_PROOF : boolean;
    mVEIN_PROOF : boolean;
    mSELF_HEAL : boolean;
    mEXPLODES : boolean;
    mRADAR_INVISIBLE : boolean;
    mSENSORS : boolean;
    mFEARLESS : boolean;
    mC4 : boolean;
    mTIBERIUM_HEAL : boolean;
    mGUARD_AREA : boolean;
    mCRUSHER : boolean;
}
class BounceClass
{
    Initialize(coords_0 : any, elasticity_1 : number, gravity_2 : number, maxVelocity_3 : number, velocity_4 : any, angularVelocity_5 : number) : void;
    GetCoords(pBuffer_0 : any) : any;
    GetCoords() : any;
    GetDrawingMatrix(pBuffer_0 : any) : any;
    GetDrawingMatrix() : any;
    Update() : any;
    mElasticity : number;
    mGravity : number;
    mMaxVelocity : number;
    mCoords : any;
    mVelocity : any;
    mCurrentAngle : any;
    mAngularVelocity : any;
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
    sAbsID : any;
    mOwner : TechnoClass;
    mOwnerHouse : HouseClass;
    mTarget : ObjectClass;
    mDeathBomb : number;
    mPlantingFrame : number;
    mDetonationFrame : number;
    mAudio : any;
    mTickSound : number;
    mShouldPlayTickingSound : number;
    mHarmless : boolean;
}
class LineTrail
{
    SetDecrement(val_0 : number) : void;
    DeleteAll() : void;
    sArray : any;
    mColor : any;
    mOwner : ObjectClass;
    mDecrement : number;
    mActiveSlot : number;
    mTrails : LineTrailNode;
}
class LineTrailNode
{
    mPosition : any;
    mValue : number;
}
class WaypointClass
{
    mCoords : any;
    munknown : number;
}
class HouseTypeClass
    extends AbstractTypeClass
{
    Find(pID_0 : number) : HouseTypeClass;
    FindOrAllocate(pID_0 : number) : HouseTypeClass;
    FindIndex(pID_0 : number) : number;
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    FindParentCountry() : HouseTypeClass;
    FindParentCountryIndex() : number;
    FindIndexOfName(name_0 : number) : number;
    sAbsID : any;
    sArray : any;
    mParentCountry : any;
    mArrayIndex : number;
    mArrayIndex2 : number;
    mSideIndex : number;
    mColorSchemeIndex : number;
    mFirepowerMult : number;
    mGroundspeedMult : number;
    mAirspeedMult : number;
    mArmorMult : number;
    mROFMult : number;
    mCostMult : number;
    mBuildtimeMult : number;
    mArmorInfantryMult : number;
    mArmorUnitsMult : number;
    mArmorAircraftMult : number;
    mArmorBuildingsMult : number;
    mArmorDefensesMult : number;
    mCostInfantryMult : number;
    mCostUnitsMult : number;
    mCostAircraftMult : number;
    mCostBuildingsMult : number;
    mCostDefensesMult : number;
    mSpeedInfantryMult : number;
    mSpeedUnitsMult : number;
    mSpeedAircraftMult : number;
    mBuildtimeInfantryMult : number;
    mBuildtimeUnitsMult : number;
    mBuildtimeAircraftMult : number;
    mBuildtimeBuildingsMult : number;
    mBuildtimeDefensesMult : number;
    mIncomeMult : number;
    mVeteranInfantry : any;
    mVeteranUnits : any;
    mVeteranAircraft : any;
    mSuffix : number;
    mPrefix : number;
    mMultiplay : boolean;
    mMultiplayPassive : boolean;
    mWallOwner : boolean;
    mSmartAI : boolean;
}
class StartingTechnoStruct
{
    mUnit : TechnoTypeClass;
    mCell : any;
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
    sAbsID : any;
    mCurrentWaypointIndex : number;
    mWaypoints : any;
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
    mUnitTotals : number;
    mUnitCount : number;
    mInNetworkFormat : number;
}
class ZoneInfoStruct
{
    mAircraft : number;
    mArmor : number;
    mInfantry : number;
}
class AngerStruct
{
    mHouse : HouseClass;
    mAngerLevel : number;
}
class ScoutStruct
{
    mHouse : HouseClass;
    mIsPreferred : boolean;
}
class DropshipStruct
{
    mTimer : CDTimerClass;
    m__Timer : number;
    munknown_C : number;
    mCount : number;
    mTypes : TechnoTypeClass;
    mTotalCost : number;
}
class BaseClass
{
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any) : number;
    ComputeCRC(crc_0 : any) : void;
    FailedToPlaceNode(Node_0 : BaseNodeClass) : number;
    mBaseNodes : any;
    m__BaseNodes : number;
    mPercentBuilt : number;
    mCells_24 : any;
    m__Cells_24 : number;
    mCells_38 : any;
    m__Cells_38 : number;
    mCenter : any;
    mOwner : HouseClass;
}
class BaseNodeClass
{
    mBuildingTypeIndex : number;
    mMapCoords : any;
    mPlaced : boolean;
    mAttempts : number;
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
    mNext : LinkClass;
    mPrevious : LinkClass;
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
    GetColorScheme() : number;
    mX : number;
    mY : number;
    mWidth : number;
    mHeight : number;
    mNeedsRedraw : boolean;
    mIsSticky : boolean;
    mDisabled : boolean;
    mFlags : any;
}
class OverlayClass
    extends ObjectClass
{
    GetClassID(pClassID_0 : any) : number;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any, fClearDirty_1 : number) : number;
    WhatAmI() : any;
    Size() : number;
    GetTiberiumType(overlayTypeIndex_0 : number) : number;
    sAbsID : any;
    sArray : any;
    mType : OverlayTypeClass;
}
class GScreenClass
{
    DoBlit(mouseCaptured_0 : boolean, surface_1 : any, rect_2 : any) : void;
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
    sInstance : any;
    mScreenShakeX : number;
    mScreenShakeY : number;
    mBitfield : number;
}
class Crate
{
    mCrateTimer : CDTimerClass;
    mLocation : any;
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
    GetLayer(lyr_0 : any) : LayerClass;
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
    GetCellIndex(MapCoords_0 : any) : number;
    GetRandomCoordsNear(outBuffer_0 : any, coords_1 : any, distance_2 : number, center_3 : boolean) : any;
    GetRandomCoordsNear(coords_0 : any, distance_1 : number, center_2 : boolean) : any;
    PickInfantrySublocation(outBuffer_0 : any, coords_1 : any, ignoreContents_2 : boolean) : any;
    PickInfantrySublocation(coords_0 : any, ignoreContents_1 : boolean) : any;
    UnselectAll() : void;
    CenterMap() : void;
    CellIteratorReset() : void;
    CellIteratorNext() : CellClass;
    GetMovementZoneType(MapCoords_0 : any, movementZone_1 : any, isBridge_2 : boolean) : number;
    DamageArea(Coords_0 : any, Damage_1 : number, SourceObject_2 : TechnoClass, WH_3 : WarheadTypeClass, AffectsTiberium_4 : boolean, SourceHouse_5 : HouseClass) : any;
    SelectDamageAnimation(Damage_0 : number, WH_1 : WarheadTypeClass, LandType_2 : any, coords_3 : any) : AnimTypeClass;
    FlashbangWarheadAt(Damage_0 : number, WH_1 : WarheadTypeClass, coords_2 : any, Force_3 : boolean, CLDisableFlags_4 : any) : void;
    GetTotalDamage(damage_0 : number, pWarhead_1 : WarheadTypeClass, armor_2 : any, distance_3 : number) : number;
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
    sInstance : any;
    sInvalidCell : any;
    sMaxCells : number;
    sLogics : any;
    sObjectsInLayers : any;
    sMovementAdjustArray : any;
    munknown_10 : number;
    munknown_pointer_14 : void;
    mMovementZones : void;
    msomecount_4C : number;
    mZoneConnections : any;
    mLevelAndPassability : any;
    mValidMapCellCount : number;
    mLevelAndPassabilityStruct2pointer_70 : any;
    munknown_74 : number;
    munknown_78 : number;
    munknown_7C : number;
    munknown_80 : number;
    mSubzoneTracking1 : any;
    mSubzoneTracking2 : any;
    mSubzoneTracking3 : any;
    mCellStructs1 : any;
    mMapRect : any;
    mVisibleRect : any;
    mCellIterator_NextX : number;
    mCellIterator_NextY : number;
    mCellIterator_CurrentY : number;
    mCellIterator_NextCell : CellClass;
    mZoneIterator_X : number;
    mZoneIterator_Y : number;
    mMapCoordBounds : LTRBStruct;
    mTotalValue : number;
    mCells : any;
    mMaxLevel : number;
    mMaxWidth : number;
    mMaxHeight : number;
    mMaxNumCells : number;
    mCrates : Crate;
    mRedraws : number;
    mTaggedCells : any;
}
class DisplayClass
    extends MapClass
{
    ProcessClickCoords(src_0 : any, XYdst_1 : any, XYZdst_2 : any, Target_3 : ObjectClass, a5_4 : number, a6_5 : number) : boolean;
    SetActiveFoundation(Coords_0 : any) : void;
    Load(pStm_0 : any) : number;
    Save(pStm_0 : any) : number;
    LoadFromINI(pINI_0 : any) : void;
    GetToolTip(nDlgID_0 : number) : number;
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
    sInstance : any;
    mCurrentFoundation_CenterCell : any;
    mCurrentFoundation_TopLeftOffset : any;
    mCurrentFoundation_Data : any;
    munknown_1180 : boolean;
    munknown_1181 : boolean;
    mCurrentFoundationCopy_CenterCell : any;
    mCurrentFoundationCopy_TopLeftOffset : any;
    mCurrentFoundationCopy_Data : any;
    munknown_1190 : number;
    munknown_1194 : number;
    munknown_1198 : number;
    mFollowObject : boolean;
    mObjectToFollow : ObjectClass;
    mCurrentBuilding : ObjectClass;
    mCurrentBuildingType : ObjectTypeClass;
    munknown_11AC : number;
    mRepairMode : boolean;
    mSellMode : boolean;
    mPowerToggleMode : boolean;
    mPlanningMode : boolean;
    mPlaceBeaconMode : boolean;
    mCurrentSWTypeIndex : number;
    munknown_11BC : number;
    munknown_11C0 : number;
    munknown_11C4 : number;
    munknown_11C8 : number;
    munknown_bool_11CC : boolean;
    munknown_bool_11CD : boolean;
    munknown_bool_11CE : boolean;
    mDraggingRectangle : boolean;
    munknown_bool_11D0 : boolean;
    munknown_bool_11D1 : boolean;
    munknown_11D4 : number;
    munknown_11D8 : number;
    munknown_11DC : number;
    munknown_11E0 : number;
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
