/// <reference path = "../index.d.ts"/>
declare module "YRpp" {
import { $Ref } from "puerts";
// BytePalette
class BytePalette
{
    // skip operator[]
    // skip operator[]
    // public ColorStruct[256] Entries
    m_Entries : ColorStruct;
}
// used for light colors
// TintStruct
class TintStruct
{
    // public TintStruct()
    constructor();
    // public TintStruct(int r, int g, int b)
    constructor(r_0 : number, g_1 : number, b_2 : number);
    // public bool operator==(TintStruct const rhs) const
    op_Equality(rhs_0 : TintStruct) : boolean;
    // public bool operator!=(TintStruct const rhs) const
    op_Inequality(rhs_0 : TintStruct) : boolean;
    // public bool operator<(TintStruct const rhs) const
    op_LessThan(rhs_0 : TintStruct) : boolean;
    // public int Red
    m_Red : number;
    // public int Green
    m_Green : number;
    // public int Blue
    m_Blue : number;
}
// Random number range
// RandomStruct
class RandomStruct
{
    // public int Min
    m_Min : number;
    // public int Max
    m_Max : number;
}
// LTRBStruct
class LTRBStruct
{
    // public int Left
    m_Left : number;
    // public int Top
    m_Top : number;
    // public int Right
    m_Right : number;
    // public int Bottom
    m_Bottom : number;
}
// Timer that counts down towards zero at specified rate, counted in frames.
// RateTimer
class RateTimer
{
    // public RateTimer()
    constructor();
    // public RateTimer(int rate)
    constructor(rate_0 : number);
    // public void Start(int rate)
    Start(rate_0 : number) : void;
    // public int Rate
    m_Rate : number;
}
// FacingClass
class FacingClass
{
    // public FacingClass()
    constructor();
    // public FacingClass(noinit_t const&)
    constructor(_0 : any);
    // public FacingClass(int rate)
    constructor(rate_0 : number);
    // public FacingClass(DirStruct const& facing)
    constructor(facing_0 : DirStruct);
    // public FacingClass(DirType dir)
    constructor(dir_0 : DirType);
    // public FacingClass(FacingClass const& another)
    constructor(another_0 : FacingClass);
    // skip operator=
    // public bool SetDesired(DirStruct const& facing)
    SetDesired(facing_0 : DirStruct) : boolean;
    // public bool SetCurrent(DirStruct const& facing)
    SetCurrent(facing_0 : DirStruct) : boolean;
    // public DirStruct Desired() const
    Desired() : DirStruct;
    // public DirStruct Current() const
    Current() : DirStruct;
    // public bool IsRotating() const
    IsRotating() : boolean;
    // public bool IsRotatingCCW() const
    IsRotatingCCW() : boolean;
    // public bool IsRotatingCW() const
    IsRotatingCW() : boolean;
    // public DirStruct Difference() const
    Difference() : DirStruct;
    // public void SetROT(int rate)
    SetROT(rate_0 : number) : void;
    // public DirStruct DesiredFacing
    m_DesiredFacing : DirStruct;
    // The starting direction from which to calcuate the rotation.
    // public DirStruct StartFacing
    m_StartFacing : DirStruct;
    // public CDTimerClass RotationTimer
    m_RotationTimer : CDTimerClass;
    // public DirStruct ROT
    m_ROT : DirStruct;
}
// ILocomotion
interface ILocomotion
{
    // Links object to locomotor.
    // public virtual long Link_To_Object(void * pointer) = 0
    Link_To_Object(pointer_0 : void) : number;
    // Sees if object is moving.
    // public virtual bool Is_Moving() = 0
    Is_Moving() : boolean;
    // Fetches destination coordinate.
    // public virtual CoordStruct Destination() = 0
    Destination() : CoordStruct;
    // Fetches immediate (next cell) destination coordinate.
    // public virtual CoordStruct Head_To_Coord() = 0
    Head_To_Coord() : CoordStruct;
    // Determine if specific cell can be entered.
    // public virtual Move Can_Enter_Cell(CellStruct cell) = 0
    Can_Enter_Cell(cell_0 : CellStruct) : Move;
    // Should object cast a shadow?
    // public virtual bool Is_To_Have_Shadow() = 0
    Is_To_Have_Shadow() : boolean;
    // Fetch voxel draw matrix.
    // public virtual Matrix3D Draw_Matrix(VoxelIndexKey * pIndex) = 0
    Draw_Matrix(pIndex_0 : any) : Matrix3D;
    // Fetch shadow draw matrix.
    // public virtual Matrix3D Shadow_Matrix(VoxelIndexKey * pIndex) = 0
    Shadow_Matrix(pIndex_0 : any) : Matrix3D;
    // Draw point center location.
    // public virtual Point2D Draw_Point() = 0
    Draw_Point() : Point2D;
    // Shadow draw point center location.
    // public virtual Point2D Shadow_Point() = 0
    Shadow_Point() : Point2D;
    // Visual character for drawing.
    // public virtual VisualType Visual_Character(bool raw) = 0
    Visual_Character(raw_0 : boolean) : VisualType;
    // Z adjust control value.
    // public virtual int Z_Adjust() = 0
    Z_Adjust() : number;
    // Z gradient control value.
    // public virtual ZGradient Z_Gradient() = 0
    Z_Gradient() : ZGradient;
    // Process movement of object.]
    // public virtual bool Process() = 0
    Process() : boolean;
    // Instruct to move to location specified.
    // public virtual void Move_To(CoordStruct to) = 0
    Move_To(to_0 : CoordStruct) : void;
    // Stop moving at first opportunity.
    // public virtual void Stop_Moving() = 0
    Stop_Moving() : void;
    // Try to face direction specified.
    // public virtual void Do_Turn(DirStruct coord) = 0
    Do_Turn(coord_0 : DirStruct) : void;
    // Object is appearing in the world.
    // public virtual void Unlimbo() = 0
    Unlimbo() : void;
    // Special tilting AI function.
    // public virtual void Tilt_Pitch_AI() = 0
    Tilt_Pitch_AI() : void;
    // Locomotor becomes powered.
    // public virtual bool Power_On() = 0
    Power_On() : boolean;
    // Locomotor loses power.
    // public virtual bool Power_Off() = 0
    Power_Off() : boolean;
    // Is locomotor powered?
    // public virtual bool Is_Powered() = 0
    Is_Powered() : boolean;
    // Is locomotor sensitive to ion storms?
    // public virtual bool Is_Ion_Sensitive() = 0
    Is_Ion_Sensitive() : boolean;
    // Push object in direction specified.
    // public virtual bool Push(DirStruct dir) = 0
    Push(dir_0 : DirStruct) : boolean;
    // Shove object (with spin) in direction specified.
    // public virtual bool Shove(DirStruct dir) = 0
    Shove(dir_0 : DirStruct) : boolean;
    // Force drive track -- special case only.
    // public virtual void Force_Track(int track, CoordStruct coord) = 0
    Force_Track(track_0 : number, coord_1 : CoordStruct) : void;
    // What display layer is it located in.
    // public virtual Layer In_Which_Layer() = 0
    In_Which_Layer() : Layer;
    // Don't use this function.
    // public virtual void Force_Immediate_Destination(CoordStruct coord) = 0
    Force_Immediate_Destination(coord_0 : CoordStruct) : void;
    // Force a voxel unit to a given slope. Used in cratering.
    // public virtual void Force_New_Slope(int ramp) = 0
    Force_New_Slope(ramp_0 : number) : void;
    // Is it actually moving across the ground this very second?
    // public virtual bool Is_Moving_Now() = 0
    Is_Moving_Now() : boolean;
    // Actual current speed of object expressed as leptons per game frame.
    // public virtual int Apparent_Speed() = 0
    Apparent_Speed() : number;
    // Special drawing feedback code (locomotor specific meaning)
    // public virtual int Drawing_Code() = 0
    Drawing_Code() : number;
    // Queries if any locomotor specific state prevents the object from firing.
    // public virtual FireError Can_Fire() = 0
    Can_Fire() : FireError;
    // Queries the general state of the locomotor.
    // public virtual int Get_Status() = 0
    Get_Status() : number;
    // Forces a hunter seeker droid to find a target.
    // public virtual void Acquire_Hunter_Seeker_Target() = 0
    Acquire_Hunter_Seeker_Target() : void;
    // Is this object surfacing?
    // public virtual bool Is_Surfacing() = 0
    Is_Surfacing() : boolean;
    // Lifts all occupation bits associated with the object off the map
    // public virtual void Mark_All_Occupation_Bits(MarkType mark) = 0
    Mark_All_Occupation_Bits(mark_0 : MarkType) : void;
    // Is this object in the process of moving into this coord.
    // public virtual bool Is_Moving_Here(CoordStruct to) = 0
    Is_Moving_Here(to_0 : CoordStruct) : boolean;
    // Will this object jump tracks?
    // public virtual bool Will_Jump_Tracks() = 0
    Will_Jump_Tracks() : boolean;
    // Infantry moving query function.
    // public virtual bool Is_Really_Moving_Now() = 0
    Is_Really_Moving_Now() : boolean;
    // Falsifies the IsReallyMoving flag in WalkLocomotionClass.
    // public virtual void Stop_Movement_Animation() = 0
    Stop_Movement_Animation() : void;
    // Object is disappearing from the world.
    // Was added post TLB generation.
    // public virtual void Limbo() = 0
    Limbo() : void;
    // Locks the locomotor from being deleted.
    // public virtual void Lock() = 0
    Lock() : void;
    // Unlocks the locomotor from being deleted.
    // public virtual void Unlock() = 0
    Unlock() : void;
    // Queries internal variables.
    // public virtual int Get_Track_Number() = 0
    Get_Track_Number() : number;
    // Queries internal variables.
    // public virtual int Get_Track_Index() = 0
    Get_Track_Index() : number;
    // Queries internal variables.
    // public virtual int Get_Speed_Accum() = 0
    Get_Speed_Accum() : number;
}
// 'Piggyback' one locomotor onto another.
// IPiggyback
interface IPiggyback
{
    // Piggybacks a locomotor onto this one.
    // public virtual long Begin_Piggyback(ILocomotion * pointer) = 0
    Begin_Piggyback(pointer_0 : ILocomotion) : number;
    // End piggyback process and restore locomotor interface pointer.
    // public virtual long End_Piggyback(ILocomotion * * pointer) = 0
    End_Piggyback(pointer_0 : ILocomotion) : number;
    // Determines when should the piggybacking be ended (done automatically in FootClass::AI).
    // public virtual bool Is_Ok_To_End() = 0
    Is_Ok_To_End() : boolean;
    // Fetches piggybacked locomotor class ID.
    // public virtual long Piggyback_CLSID(_GUID * classid) = 0
    Piggyback_CLSID(classid_0 : any) : number;
    // Is it currently piggybacking another locomotor?
    // public virtual bool Is_Piggybacking() = 0
    Is_Piggybacking() : boolean;
}
// forward declarations
// TechnoClass
class TechnoClass
    extends RadioClass
{
    // Constructor
    // public TechnoClass(HouseClass * pOwner)
    constructor(pOwner_0 : HouseClass);
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // ObjectClass
    // public virtual bool Limbo()
    Limbo() : boolean;
    // TechnoClass
    // public virtual bool IsUnitFactory() const
    IsUnitFactory() : boolean;
    // public virtual bool IsCloakable() const
    IsCloakable() : boolean;
    // public virtual bool CanScatter() const
    CanScatter() : boolean;
    // public virtual bool BelongsToATeam() const
    BelongsToATeam() : boolean;
    // public virtual bool ShouldSelfHealOneStep() const
    ShouldSelfHealOneStep() : boolean;
    // public virtual bool IsVoxel() const
    IsVoxel() : boolean;
    // public virtual bool vt_entry_29C()
    vt_entry_29C() : boolean;
    // public virtual bool IsReadyToCloak() const
    IsReadyToCloak() : boolean;
    // public virtual bool ShouldNotBeCloaked() const
    ShouldNotBeCloaked() : boolean;
    // public virtual DirStruct * TurretFacing(DirStruct * pBuffer) const
    TurretFacing(pBuffer_0 : DirStruct) : DirStruct;
    // public virtual bool IsArmed() const
    IsArmed() : boolean;
    // public virtual bool vt_entry_2B0() const
    vt_entry_2B0() : boolean;
    // public virtual double GetStoragePercentage() const
    GetStoragePercentage() : number;
    // public virtual int GetPipFillLevel() const
    GetPipFillLevel() : number;
    // public virtual int GetRefund() const
    GetRefund() : number;
    // public virtual int GetThreatValue() const
    GetThreatValue() : number;
    // public virtual bool IsInSameZoneAs(AbstractClass * pTarget)
    IsInSameZoneAs(pTarget_0 : AbstractClass) : boolean;
    // public virtual unsigned long vt_entry_2C8(unsigned long dwUnk, unsigned long dwUnk2)
    vt_entry_2C8(dwUnk_0 : number, dwUnk2_1 : number) : number;
    // public virtual bool IsInSameZoneAsCoords(CoordStruct const& coord)
    IsInSameZoneAsCoords(coord_0 : CoordStruct) : boolean;
    // public virtual int GetCrewCount() const
    GetCrewCount() : number;
    // public virtual int GetAntiAirValue() const
    GetAntiAirValue() : number;
    // public virtual int GetAntiArmorValue() const
    GetAntiArmorValue() : number;
    // public virtual int GetAntiInfantryValue() const
    GetAntiInfantryValue() : number;
    // public virtual void GotHijacked()
    GotHijacked() : void;
    // public virtual int SelectWeapon(AbstractClass * pTarget) const
    SelectWeapon(pTarget_0 : AbstractClass) : number;
    // public virtual int SelectNavalTargeting(AbstractClass * pTarget) const
    SelectNavalTargeting(pTarget_0 : AbstractClass) : number;
    // public virtual int GetZAdjustment() const
    GetZAdjustment() : number;
    // public virtual ZGradient GetZGradient() const
    GetZGradient() : ZGradient;
    // public virtual CellStruct GetLastFlightMapCoords() const
    GetLastFlightMapCoords() : CellStruct;
    // public virtual void SetLastFlightMapCoords(CellStruct coord)
    SetLastFlightMapCoords(coord_0 : CellStruct) : void;
    // public virtual CellStruct * vt_entry_2FC(CellStruct * Buffer, unsigned long dwUnk2, unsigned long dwUnk3) const
    vt_entry_2FC(Buffer_0 : CellStruct, dwUnk2_1 : number, dwUnk3_2 : number) : CellStruct;
    // public virtual CoordStruct * vt_entry_300(CoordStruct * Buffer, unsigned long dwUnk2) const
    vt_entry_300(Buffer_0 : CoordStruct, dwUnk2_1 : number) : CoordStruct;
    // public virtual unsigned long vt_entry_304(unsigned long dwUnk, unsigned long dwUnk2) const
    vt_entry_304(dwUnk_0 : number, dwUnk2_1 : number) : number;
    // public virtual DirStruct * GetRealFacing(DirStruct * pBuffer) const
    GetRealFacing(pBuffer_0 : DirStruct) : DirStruct;
    // public virtual InfantryTypeClass * GetCrew() const
    GetCrew() : InfantryTypeClass;
    // public virtual bool vt_entry_310() const
    vt_entry_310() : boolean;
    // public virtual bool CanDeploySlashUnload() const
    CanDeploySlashUnload() : boolean;
    // public virtual int GetROF(int nWeapon) const
    GetROF(nWeapon_0 : number) : number;
    // public virtual int GetGuardRange(int dwUnk) const
    GetGuardRange(dwUnk_0 : number) : number;
    // public virtual bool vt_entry_320() const
    vt_entry_320() : boolean;
    // public virtual bool IsRadarVisible(int * pOutDetection) const
    IsRadarVisible(pOutDetection_0 : number) : boolean;
    // public virtual bool IsSensorVisibleToPlayer() const
    IsSensorVisibleToPlayer() : boolean;
    // public virtual bool IsSensorVisibleToHouse(HouseClass * House) const
    IsSensorVisibleToHouse(House_0 : HouseClass) : boolean;
    // public virtual bool IsEngineer() const
    IsEngineer() : boolean;
    // public virtual void ProceedToNextPlanningWaypoint()
    ProceedToNextPlanningWaypoint() : void;
    // public virtual CellStruct * ScanForTiberium(CellStruct *, int range, unsigned long dwUnk3) const
    ScanForTiberium(_0 : CellStruct, range_1 : number, dwUnk3_2 : number) : CellStruct;
    // public virtual bool EnterGrinder()
    EnterGrinder() : boolean;
    // public virtual bool EnterBioReactor()
    EnterBioReactor() : boolean;
    // public virtual bool EnterTankBunker()
    EnterTankBunker() : boolean;
    // public virtual bool EnterBattleBunker()
    EnterBattleBunker() : boolean;
    // public virtual bool GarrisonStructure()
    GarrisonStructure() : boolean;
    // public virtual bool IsPowerOnline() const
    IsPowerOnline() : boolean;
    // public virtual void QueueVoice(int idxVoc)
    QueueVoice(idxVoc_0 : number) : void;
    // public virtual int VoiceEnter()
    VoiceEnter() : number;
    // public virtual int VoiceHarvest()
    VoiceHarvest() : number;
    // public virtual int VoiceSelect()
    VoiceSelect() : number;
    // public virtual int VoiceCapture()
    VoiceCapture() : number;
    // public virtual int VoiceMove()
    VoiceMove() : number;
    // public virtual int VoiceDeploy()
    VoiceDeploy() : number;
    // public virtual int VoiceAttack(ObjectClass * pTarget)
    VoiceAttack(pTarget_0 : ObjectClass) : number;
    // public virtual bool ClickedEvent(EventType event)
    ClickedEvent(event_0 : EventType) : boolean;
    // depending on the mission you click, cells/Target are not always needed
    // public virtual bool ClickedMission(Mission Mission, ObjectClass * pTarget, CellClass * TargetCell, CellClass * NearestTargetCellICanEnter)
    ClickedMission(Mission_0 : Mission, pTarget_1 : ObjectClass, TargetCell_2 : CellClass, NearestTargetCellICanEnter_3 : CellClass) : boolean;
    // public virtual bool IsUnderEMP() const
    IsUnderEMP() : boolean;
    // public virtual bool IsParalyzed() const
    IsParalyzed() : boolean;
    // public virtual bool CanCheer() const
    CanCheer() : boolean;
    // public virtual void Cheer(bool Force)
    Cheer(Force_0 : boolean) : void;
    // public virtual int GetDefaultSpeed() const
    GetDefaultSpeed() : number;
    // public virtual void DecreaseAmmo()
    DecreaseAmmo() : void;
    // public virtual void AddPassenger(FootClass * pPassenger)
    AddPassenger(pPassenger_0 : FootClass) : void;
    // public virtual bool CanDisguiseAs(AbstractClass * pTarget) const
    CanDisguiseAs(pTarget_0 : AbstractClass) : boolean;
    // public virtual bool TargetAndEstimateDamage(CoordStruct& coord, ThreatType threat)
    TargetAndEstimateDamage(coord_0 : CoordStruct, threat_1 : ThreatType) : boolean;
    // public virtual void Stun()
    Stun() : void;
    // public virtual bool TriggersCellInset(AbstractClass * pTarget)
    TriggersCellInset(pTarget_0 : AbstractClass) : boolean;
    // public virtual bool IsCloseEnough(AbstractClass * pTarget, int idxWeapon) const
    IsCloseEnough(pTarget_0 : AbstractClass, idxWeapon_1 : number) : boolean;
    // public virtual bool IsCloseEnoughToAttack(AbstractClass * pTarget) const
    IsCloseEnoughToAttack(pTarget_0 : AbstractClass) : boolean;
    // public virtual bool IsCloseEnoughToAttackCoords(CoordStruct const& Coords) const
    IsCloseEnoughToAttackCoords(Coords_0 : CoordStruct) : boolean;
    // public virtual bool InAuxiliarySearchRange(AbstractClass * pTarget) const
    InAuxiliarySearchRange(pTarget_0 : AbstractClass) : boolean;
    // public virtual void Destroyed(ObjectClass * Killer) = 0
    Destroyed(Killer_0 : ObjectClass) : void;
    // public virtual FireError GetFireErrorWithoutRange(AbstractClass * pTarget, int nWeaponIndex) const
    GetFireErrorWithoutRange(pTarget_0 : AbstractClass, nWeaponIndex_1 : number) : FireError;
    // public virtual FireError GetFireError(AbstractClass * pTarget, int nWeaponIndex, bool ignoreRange) const
    GetFireError(pTarget_0 : AbstractClass, nWeaponIndex_1 : number, ignoreRange_2 : boolean) : FireError;
    // public virtual AbstractClass * GreatestThreat(ThreatType threat, CoordStruct * pCoord, bool onlyTargetHouseEnemy)
    GreatestThreat(threat_0 : ThreatType, pCoord_1 : CoordStruct, onlyTargetHouseEnemy_2 : boolean) : AbstractClass;
    // public virtual void SetTarget(AbstractClass * pTarget)
    SetTarget(pTarget_0 : AbstractClass) : void;
    // public virtual BulletClass * Fire(AbstractClass * pTarget, int nWeaponIndex)
    Fire(pTarget_0 : AbstractClass, nWeaponIndex_1 : number) : BulletClass;
    // public virtual void Guard()
    Guard() : void;
    // public virtual bool SetOwningHouse(HouseClass * pHouse, bool announce = true)
    SetOwningHouse(pHouse_0 : HouseClass, announce_1 : boolean) : boolean;
    // public virtual void vt_entry_3D8(unsigned long dwUnk, unsigned long dwUnk2, unsigned long dwUnk3)
    vt_entry_3D8(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : void;
    // public virtual bool Crash(ObjectClass * Killer)
    Crash(Killer_0 : ObjectClass) : boolean;
    // public virtual bool IsAreaFire() const
    IsAreaFire() : boolean;
    // public virtual int IsNotSprayAttack() const
    IsNotSprayAttack() : number;
    // public virtual int GetSecondaryWeaponIndex() const
    GetSecondaryWeaponIndex() : number;
    // public virtual int IsNotSprayAttack2() const
    IsNotSprayAttack2() : number;
    // public virtual WeaponStruct * GetDeployWeapon() const
    GetDeployWeapon() : WeaponStruct;
    // public virtual WeaponStruct * GetTurretWeapon() const
    GetTurretWeapon() : WeaponStruct;
    // public virtual WeaponStruct * GetWeapon(int nWeaponIndex) const
    GetWeapon(nWeaponIndex_0 : number) : WeaponStruct;
    // public virtual bool HasTurret() const
    HasTurret() : boolean;
    // public virtual bool CanOccupyFire() const
    CanOccupyFire() : boolean;
    // public virtual int GetOccupyRangeBonus() const
    GetOccupyRangeBonus() : number;
    // public virtual int GetOccupantCount() const
    GetOccupantCount() : number;
    // public virtual void OnFinishRepair()
    OnFinishRepair() : void;
    // public virtual void UpdateCloak(bool bUnk = 1)
    UpdateCloak(bUnk_0 : boolean) : void;
    // public virtual void CreateGap()
    CreateGap() : void;
    // public virtual void DestroyGap()
    DestroyGap() : void;
    // public virtual void vt_entry_41C()
    vt_entry_41C() : void;
    // public virtual void Sensed()
    Sensed() : void;
    // public virtual void Reload()
    Reload() : void;
    // public virtual void vt_entry_428()
    vt_entry_428() : void;
    // Returns target's coordinates if on attack mission 
    // &
    // have target, otherwise own coordinates.
    // public virtual CoordStruct * GetAttackCoordinates(CoordStruct * pCrd) const
    GetAttackCoordinates(pCrd_0 : CoordStruct) : CoordStruct;
    // public virtual bool IsNotWarpingIn() const
    IsNotWarpingIn() : boolean;
    // public virtual bool vt_entry_434(unsigned long dwUnk) const
    vt_entry_434(dwUnk_0 : number) : boolean;
    // public virtual void DrawActionLines(bool Force, unsigned long dwUnk2)
    DrawActionLines(Force_0 : boolean, dwUnk2_1 : number) : void;
    // public virtual unsigned long GetDisguiseFlags(unsigned long existingFlags) const
    GetDisguiseFlags(existingFlags_0 : number) : number;
    // public virtual bool IsClearlyVisibleTo(HouseClass * House) const
    IsClearlyVisibleTo(House_0 : HouseClass) : boolean;
    // public virtual void DrawVoxel(VoxelStruct const& Voxel, unsigned long dwUnk2, short Facing, IndexClass<int, int> const& VoxelIndex, RectangleStruct const& Rect, Point2D const& Location, Matrix3D const& Matrix, int Intensity, unsigned long dwUnk9, unsigned long dwUnk10)
    DrawVoxel(Voxel_0 : any, dwUnk2_1 : number, Facing_2 : number, VoxelIndex_3 : any, Rect_4 : RectangleStruct, Location_5 : Point2D, Matrix_6 : Matrix3D, Intensity_7 : number, dwUnk9_8 : number, dwUnk10_9 : number) : void;
    // public virtual void vt_entry_448(unsigned long dwUnk, unsigned long dwUnk2)
    vt_entry_448(dwUnk_0 : number, dwUnk2_1 : number) : void;
    // public virtual void DrawHealthBar(Point2D * pLocation, RectangleStruct * pBounds, bool bUnk3) const
    DrawHealthBar(pLocation_0 : Point2D, pBounds_1 : RectangleStruct, bUnk3_2 : boolean) : void;
    // public virtual void DrawPipScalePips(Point2D * pLocation, Point2D * pOriginalLocation, RectangleStruct * pBounds) const
    DrawPipScalePips(pLocation_0 : Point2D, pOriginalLocation_1 : Point2D, pBounds_2 : RectangleStruct) : void;
    // public virtual void DrawVeterancyPips(Point2D * pLocation, RectangleStruct * pBounds) const
    DrawVeterancyPips(pLocation_0 : Point2D, pBounds_1 : RectangleStruct) : void;
    // public virtual void DrawExtraInfo(Point2D const& location, Point2D const& originalLocation, RectangleStruct const& bounds) const
    DrawExtraInfo(location_0 : Point2D, originalLocation_1 : Point2D, bounds_2 : RectangleStruct) : void;
    // public virtual void Uncloak(bool bPlaySound)
    Uncloak(bPlaySound_0 : boolean) : void;
    // public virtual void Cloak(bool bPlaySound)
    Cloak(bPlaySound_0 : boolean) : void;
    // public virtual unsigned long vt_entry_464(unsigned long dwUnk) const
    vt_entry_464(dwUnk_0 : number) : number;
    // public virtual void UpdateRefinerySmokeSystems()
    UpdateRefinerySmokeSystems() : void;
    // public virtual unsigned long DisguiseAs(AbstractClass * pTarget)
    DisguiseAs(pTarget_0 : AbstractClass) : number;
    // public virtual void ClearDisguise()
    ClearDisguise() : void;
    // public virtual bool IsItTimeForIdleActionYet() const
    IsItTimeForIdleActionYet() : boolean;
    // public virtual bool UpdateIdleAction()
    UpdateIdleAction() : boolean;
    // public virtual void vt_entry_47C(unsigned long dwUnk)
    vt_entry_47C(dwUnk_0 : number) : void;
    // public virtual void SetDestination(AbstractClass * pDest, bool bUnk)
    SetDestination(pDest_0 : AbstractClass, bUnk_1 : boolean) : void;
    // public virtual bool EnterIdleMode(bool initial, bool unused)
    EnterIdleMode(initial_0 : boolean, unused_1 : boolean) : boolean;
    // public virtual void UpdateSight(unsigned long dwUnk, unsigned long dwUnk2, unsigned long dwUnk3, unsigned long dwUnk4, unsigned long dwUnk5)
    UpdateSight(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number, dwUnk5_4 : number) : void;
    // public virtual void vt_entry_48C(unsigned long dwUnk, unsigned long dwUnk2, unsigned long dwUnk3, unsigned long dwUnk4)
    vt_entry_48C(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number) : void;
    // public virtual bool ForceCreate(CoordStruct& coord, unsigned long dwUnk = 0)
    ForceCreate(coord_0 : CoordStruct, dwUnk_1 : number) : boolean;
    // public virtual void RadarTrackingStart()
    RadarTrackingStart() : void;
    // public virtual void RadarTrackingStop()
    RadarTrackingStop() : void;
    // public virtual void RadarTrackingFlash()
    RadarTrackingFlash() : void;
    // public virtual void RadarTrackingUpdate(bool bUnk)
    RadarTrackingUpdate(bUnk_0 : boolean) : void;
    // public virtual Mission RespondMegaEventMission(EventClass * pRespondTo)
    RespondMegaEventMission(pRespondTo_0 : EventClass) : Mission;
    // public virtual void ClearMegaMissionData()
    ClearMegaMissionData() : void;
    // public virtual bool HaveMegaMission() const
    HaveMegaMission() : boolean;
    // public virtual bool HaveAttackMoveTarget() const
    HaveAttackMoveTarget() : boolean;
    // public virtual Mission GetMegaMission() const
    GetMegaMission() : Mission;
    // public virtual CoordStruct * GetAttackMoveCoords(CoordStruct * pBuffer)
    GetAttackMoveCoords(pBuffer_0 : CoordStruct) : CoordStruct;
    // public virtual bool CanUseWaypoint() const
    CanUseWaypoint() : boolean;
    // public virtual bool CanAttackOnTheMove() const
    CanAttackOnTheMove() : boolean;
    // public virtual bool MegaMissionIsAttackMove() const
    MegaMissionIsAttackMove() : boolean;
    // public virtual bool ContinueMegaMission()
    ContinueMegaMission() : boolean;
    // public virtual void UpdateAttackMove()
    UpdateAttackMove() : void;
    // public virtual bool RefreshMegaMission()
    RefreshMegaMission() : boolean;
    // (re-)starts the reload timer
    // public void StartReloading()
    StartReloading() : void;
    // public bool ShouldSuppress(CellStruct * coords) const
    ShouldSuppress(coords_0 : CellStruct) : boolean;
    // smooth operator
    // public char const * get_ID() const
    get_ID() : string;
    // public int TimeToBuild() const
    TimeToBuild() : number;
    // public bool IsMindControlled() const
    IsMindControlled() : boolean;
    // public bool CanBePermaMindControlled() const
    CanBePermaMindControlled() : boolean;
    // public LaserDrawClass * CreateLaser(ObjectClass * pTarget, int idxWeapon, WeaponTypeClass * pWeapon, CoordStruct const& Coords)
    CreateLaser(pTarget_0 : ObjectClass, idxWeapon_1 : number, pWeapon_2 : WeaponTypeClass, Coords_3 : CoordStruct) : LaserDrawClass;
    // Cell->AddThreat(this->Owner, -this->ThreatPosed);
    // this->ThreatPosed = 0;
    // int Threat = this->CalculateThreat(); // this is another gem of a function, to be revealed another time...
    // this->ThreatPosed = Threat;
    // Cell->AddThreat(this->Owner, Threat);
    // public void UpdateThreatInCell(CellClass * Cell)
    UpdateThreatInCell(Cell_0 : CellClass) : void;
    // slave of the next one
    // public bool CanAutoTargetObject(ThreatType targetFlags, int canTargetWhatAmI, int wantedDistance, TechnoClass * pTarget, int * pThreatPosed, unsigned long dwUnk, CoordStruct * pSourceCoords) const
    CanAutoTargetObject(targetFlags_0 : ThreatType, canTargetWhatAmI_1 : number, wantedDistance_2 : number, pTarget_3 : TechnoClass, pThreatPosed_4 : number, dwUnk_5 : number, pSourceCoords_6 : CoordStruct) : boolean;
    // called by AITeam Attack Target Type and autoscan
    // public bool TryAutoTargetObject(ThreatType targetFlags, int canTargetWhatAmI, CellStruct * pCoords, unsigned long dwUnk1, unsigned long * dwUnk2, int * pThreatPosed, unsigned long dwUnk3)
    TryAutoTargetObject(targetFlags_0 : ThreatType, canTargetWhatAmI_1 : number, pCoords_2 : CellStruct, dwUnk1_3 : number, dwUnk2_4 : number, pThreatPosed_5 : number, dwUnk3_6 : number) : boolean;
    // public void Reactivate()
    Reactivate() : void;
    // public void Deactivate()
    Deactivate() : void;
    // this should be the transport, but it's unused
    // marks passenger as "InOpenTopped" for targeting, range scanning and other purposes
    // public void EnteredOpenTopped(TechnoClass * pWho)
    EnteredOpenTopped(pWho_0 : TechnoClass) : void;
    // this should be the transport, but it's unused
    // reverses the above
    // public void ExitedOpenTopped(TechnoClass * pWho)
    ExitedOpenTopped(pWho_0 : TechnoClass) : void;
    // called when the source unit dies - passengers are about to get kicked out, this basically calls ->ExitedOpenTransport on each passenger
    // public void MarkPassengersAsExited()
    MarkPassengersAsExited() : void;
    // for gattlings
    // public void SetCurrentWeaponStage(int idx)
    SetCurrentWeaponStage(idx_0 : number) : void;
    // public void SetArchiveTarget(AbstractClass * pTarget)
    SetArchiveTarget(pTarget_0 : AbstractClass) : void;
    // public void DrawVoxelShadow(VoxelStruct * vxl, int shadow_index, VoxelIndexKey vxl_index_key, IndexClass<ShadowVoxelIndexKey, VoxelCacheStruct *> * shadow_cache, RectangleStruct * bound, Point2D * a3, Matrix3D * matrix, bool again, Surface * surface, Point2D shadow_point)
    DrawVoxelShadow(vxl_0 : any, shadow_index_1 : number, vxl_index_key_2 : any, shadow_cache_3 : any, bound_4 : RectangleStruct, a3_5 : Point2D, matrix_6 : Matrix3D, again_7 : boolean, surface_8 : Surface, shadow_point_9 : Point2D) : void;
    // public void DrawObject(SHPStruct * pSHP, int nFrame, Point2D * pLocation, RectangleStruct * pBounds, int, int, int nZAdjust, ZGradient eZGradientDescIdx, int, int nBrightness, int TintColor, SHPStruct * pZShape, int nZFrame, int nZOffsetX, int nZOffsetY, int)
    DrawObject(pSHP_0 : any, nFrame_1 : number, pLocation_2 : Point2D, pBounds_3 : RectangleStruct, _4 : number, _5 : number, nZAdjust_6 : number, eZGradientDescIdx_7 : ZGradient, _8 : number, nBrightness_9 : number, TintColor_10 : number, pZShape_11 : any, nZFrame_12 : number, nZOffsetX_13 : number, nZOffsetY_14 : number, _15 : number) : void;
    // public int sub_70DE00(int State)
    sub_70DE00(State_0 : number) : number;
    // public int ClearPlanningTokens(EventClass * pEvent)
    ClearPlanningTokens(pEvent_0 : EventClass) : number;
    // public void SetTargetForPassengers(AbstractClass * pTarget)
    SetTargetForPassengers(pTarget_0 : AbstractClass) : void;
    // public void KillPassengers(TechnoClass * pSource)
    KillPassengers(pSource_0 : TechnoClass) : void;
    // returns the house that created this object (factoring in Mind Control)
    // public HouseClass * GetOriginalOwner() const
    GetOriginalOwner() : HouseClass;
    // public void FireDeathWeapon(int additionalDamage)
    FireDeathWeapon(additionalDamage_0 : number) : void;
    // public bool HasAbility(Ability ability) const
    HasAbility(ability_0 : Ability) : boolean;
    // public void ClearSidebarTabObject() const
    ClearSidebarTabObject() : void;
    // public LightConvertClass * GetDrawer() const
    GetDrawer() : LightConvertClass;
    // public int GetEffectTintIntensity(int currentIntensity)
    GetEffectTintIntensity(currentIntensity_0 : number) : number;
    // public int GetInvulnerabilityTintIntensity(int currentIntensity)
    GetInvulnerabilityTintIntensity(currentIntensity_0 : number) : number;
    // public int GetAirstrikeTintIntensity(int currentIntensity)
    GetAirstrikeTintIntensity(currentIntensity_0 : number) : number;
    // public int CombatDamage(int nWeaponIndex) const
    CombatDamage(nWeaponIndex_0 : number) : number;
    // public WeaponStruct * GetPrimaryWeapon() const
    GetPrimaryWeapon() : WeaponStruct;
    // public bool TryNextPlanningTokenNode()
    TryNextPlanningTokenNode() : boolean;
    // public int GetIonCannonValue(AIDifficulty difficulty) const
    GetIonCannonValue(difficulty_0 : AIDifficulty) : number;
    // public int GetIonCannonValue(AIDifficulty difficulty, int maxHealth) const
    GetIonCannonValue(difficulty_0 : AIDifficulty, maxHealth_1 : number) : number;
    // public DirStruct TurretFacing() const
    TurretFacing() : DirStruct;
    // public DirStruct GetRealFacing() const
    GetRealFacing() : DirStruct;
    // Invokes AI response on their 'base' being attacked. Used by buildings, ToProtect=true technos and Whiner=true team members.
    // public void BaseIsAttacked(TechnoClass * pEnemy)
    BaseIsAttacked(pEnemy_0 : TechnoClass) : void;
    // public static AbstractFlags const AbsDerivateID = AbstractFlags::Techno
    static s_AbsDerivateID : AbstractFlags;
    // public static constant_ptr<DynamicVectorClass<TechnoClass *>, 11070584> const Array = 0xA8EC78u
    static s_Array : DynamicVectorClass<TechnoClass>;
    // unit carrying me
    // public TechnoClass * Transporter
    m_Transporter : TechnoClass;
    // public int LastFireBulletFrame
    m_LastFireBulletFrame : number;
    // for IFV/gattling/charge turrets
    // public int CurrentTurretNumber
    m_CurrentTurretNumber : number;
    // public int unknown_int_128
    m_unknown_int_128 : number;
    // public AnimClass * BehindAnim
    m_BehindAnim : AnimClass;
    // public AnimClass * DeployAnim
    m_DeployAnim : AnimClass;
    // public bool InAir
    m_InAir : boolean;
    // for IFV/gattling
    // public int CurrentWeaponNumber
    m_CurrentWeaponNumber : number;
    // only used for promotion detection
    // public Rank CurrentRanking
    m_CurrentRanking : Rank;
    // public int CurrentGattlingStage
    m_CurrentGattlingStage : number;
    // sum of RateUps and RateDowns
    // public int GattlingValue
    m_GattlingValue : number;
    // public int TurretAnimFrame
    m_TurretAnimFrame : number;
    // only set in ctor
    // public HouseClass * InitialOwner
    m_InitialOwner : HouseClass;
    // public unsigned long align_154
    m_align_154 : number;
    // public double ArmorMultiplier
    m_ArmorMultiplier : number;
    // public double FirepowerMultiplier
    m_FirepowerMultiplier : number;
    // ^
    // public int IronTintStage
    m_IronTintStage : number;
    // ^
    // public unsigned long AirstrikeTintStage
    m_AirstrikeTintStage : number;
    // 0 or 1, NOT a bool - is this under ForceShield as opposed to IC?
    // public int ForceShielded
    m_ForceShielded : number;
    // Robot Tanks without power for instance
    // public bool Deactivated
    m_Deactivated : boolean;
    // eg Disk -> PowerPlant, this points to PowerPlant
    // public TechnoClass * DrainTarget
    m_DrainTarget : TechnoClass;
    // eg Disk -> PowerPlant, this points to Disk
    // public TechnoClass * DrainingMe
    m_DrainingMe : TechnoClass;
    // public AnimClass * DrainAnim
    m_DrainAnim : AnimClass;
    // public bool Disguised
    m_Disguised : boolean;
    // public unsigned long DisguiseCreationFrame
    m_DisguiseCreationFrame : number;
    // public bool UnlimboingInfantry
    m_UnlimboingInfantry : boolean;
    // public Point2D RadarPosition
    m_RadarPosition : Point2D;
    // 0-9, assigned by CTRL+Number, these kinds // also set by aimd TeamType->Group !
    // public int Group
    m_Group : number;
    // Set when told to guard a unit or such, or to distinguish undeploy and selling. Also used by rally points as well as harvesters for remembering ore fields etc.
    // public AbstractClass * ArchiveTarget
    m_ArchiveTarget : AbstractClass;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // public CloakState CloakState
    m_CloakState : CloakState;
    // don't ask! set to 0 in CTOR, never modified, only used as ((this->Fetch_ID) + this->WarpFactor) % 400 for something in cloak ripple
    // public float WarpFactor
    m_WarpFactor : number;
    // public bool unknown_bool_250
    m_unknown_bool_250 : boolean;
    // public CoordStruct LastSightCoords
    m_LastSightCoords : CoordStruct;
    // public int LastSightRange
    m_LastSightRange : number;
    // public int LastSightHeight
    m_LastSightHeight : number;
    // GapGenerator, when SuperGapRadiusInCells != GapRadiusInCells, you can deploy the gap to boost radius
    // public bool GapSuperCharged
    m_GapSuperCharged : boolean;
    // is currently generating gap
    // public bool GeneratingGap
    m_GeneratingGap : boolean;
    // public int GapRadius
    m_GapRadius : number;
    // is being warped by CLEG
    // public bool BeingWarpedOut
    m_BeingWarpedOut : boolean;
    // phasing in after chrono-jump
    // public bool WarpingOut
    m_WarpingOut : boolean;
    // public bool unknown_bool_272
    m_unknown_bool_272 : boolean;
    // public unsigned char unused_273
    m_unused_273 : number;
    // CLEG attacking Power Plant : CLEG's this
    // public TemporalClass * TemporalImUsing
    m_TemporalImUsing : TemporalClass;
    // CLEG attacking Power Plant : PowerPlant's this
    // public TemporalClass * TemporalTargetingMe
    m_TemporalTargetingMe : TemporalClass;
    // by chrono aftereffects
    // public bool IsImmobilized
    m_IsImmobilized : boolean;
    // public unsigned long unknown_280
    m_unknown_280 : number;
    // countdown after chronosphere warps things around
    // public int ChronoLockRemaining
    m_ChronoLockRemaining : number;
    // teleport loco and chsphere set this
    // public CoordStruct ChronoDestCoords
    m_ChronoDestCoords : CoordStruct;
    // Boris
    // public AirstrikeClass * Airstrike
    m_Airstrike : AirstrikeClass;
    // public bool Berzerk
    m_Berzerk : boolean;
    // public unsigned long BerzerkDurationLeft
    m_BerzerkDurationLeft : number;
    // hardcoded array of xyz offsets for sprayattack, 0 - 7, see 6FE0AD
    // public unsigned long SprayOffsetIndex
    m_SprayOffsetIndex : number;
    // DeployedCrushable fiddles this, otherwise all 0
    // public bool Uncrushable
    m_Uncrushable : boolean;
    // unless source is Pushy=
    // abs_Infantry source links with abs_Unit target and vice versa - can't attack others until current target flips
    // no checking whether source is Infantry, but no update for other types either
    // old Brute hack
    // public FootClass * DirectRockerLinkedUnit
    m_DirectRockerLinkedUnit : FootClass;
    // mag->LocoTarget = victim
    // public FootClass * LocomotorTarget
    m_LocomotorTarget : FootClass;
    // victim->LocoSource = mag
    // public FootClass * LocomotorSource
    m_LocomotorSource : FootClass;
    // if attacking
    // public AbstractClass * Target
    m_Target : AbstractClass;
    // public AbstractClass * LastTarget
    m_LastTarget : AbstractClass;
    // for Yuris
    // public CaptureManagerClass * CaptureManager
    m_CaptureManager : CaptureManagerClass;
    // public TechnoClass * MindControlledBy
    m_MindControlledBy : TechnoClass;
    // public bool MindControlledByAUnit
    m_MindControlledByAUnit : boolean;
    // public AnimClass * MindControlRingAnim
    m_MindControlRingAnim : AnimClass;
    // used for a TAction
    // public HouseClass * MindControlledByHouse
    m_MindControlledByHouse : HouseClass;
    // public SpawnManagerClass * SpawnManager
    m_SpawnManager : SpawnManagerClass;
    // on DMISL , points to DRED and such
    // public TechnoClass * SpawnOwner
    m_SpawnOwner : TechnoClass;
    // public SlaveManagerClass * SlaveManager
    m_SlaveManager : SlaveManagerClass;
    // on SLAV, points to YAREFN
    // public TechnoClass * SlaveOwner
    m_SlaveOwner : TechnoClass;
    // used for mind control
    // public HouseClass * OriginallyOwnedByHouse
    m_OriginallyOwnedByHouse : HouseClass;
    // units point to the Building bunkering them, building points to Foot contained within
    // public TechnoClass * BunkerLinkedItem
    m_BunkerLinkedItem : TechnoClass;
    // not exactly, and it doesn't affect the drawing, only internal state of a dropship
    // public float PitchAngle
    m_PitchAngle : number;
    // Set to same duration (frames) as RearmTimer when weapon is fired. Only used by IsChargeTurret to calculate timespan during which to display turret animation.
    // public int ChargeTurretDelay
    m_ChargeTurretDelay : number;
    // public int Ammo
    m_Ammo : number;
    // set to actual cost when this gets queued in factory, updated only in building's 42C
    // public int Value
    m_Value : number;
    // public ParticleSystemClass * FireParticleSystem
    m_FireParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * SparkParticleSystem
    m_SparkParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * NaturalParticleSystem
    m_NaturalParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * DamageParticleSystem
    m_DamageParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * RailgunParticleSystem
    m_RailgunParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * unk1ParticleSystem
    m_unk1ParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * unk2ParticleSystem
    m_unk2ParticleSystem : ParticleSystemClass;
    // public ParticleSystemClass * FiringParticleSystem
    m_FiringParticleSystem : ParticleSystemClass;
    // Beams
    // public WaveClass * Wave
    m_Wave : WaveClass;
    // in this frame, in radians - if abs() exceeds pi/2, it dies
    // public float AngleRotatedSideways
    m_AngleRotatedSideways : number;
    // same
    // public float AngleRotatedForwards
    m_AngleRotatedForwards : number;
    // left to right - positive pushes left side up
    // public float RockingSidewaysPerFrame
    m_RockingSidewaysPerFrame : number;
    // back to front - positive pushes ass up
    // public float RockingForwardsPerFrame
    m_RockingForwardsPerFrame : number;
    // mutant hijacker
    // public int HijackerInfantryType
    m_HijackerInfantryType : number;
    // public unsigned long unknown_34C
    m_unknown_34C : number;
    // public int CurrentBurstIndex
    m_CurrentBurstIndex : number;
    // public short unknown_short_3C8
    m_unknown_short_3C8 : number;
    // public unsigned short unknown_3CA
    m_unknown_3CA : number;
    // is this techno contained in OwningPlayer->Owned... counts?
    // public bool CountedAsOwned
    m_CountedAsOwned : boolean;
    // public bool IsSinking
    m_IsSinking : boolean;
    // if(IsSinking 
    // &
    // &
    // !WasSinkingAlready) { play SinkingSound; WasSinkingAlready = 1; }
    // public bool WasSinkingAlready
    m_WasSinkingAlready : boolean;
    // public bool unknown_bool_3CF
    m_unknown_bool_3CF : boolean;
    // public bool unknown_bool_3D0
    m_unknown_bool_3D0 : boolean;
    // ReceiveDamage when not HouseClass_IsAlly
    // public bool HasBeenAttacked
    m_HasBeenAttacked : boolean;
    // public bool Cloakable
    m_Cloakable : boolean;
    // doubleclicking a warfac/barracks sets it as primary
    // public bool IsPrimaryFactory
    m_IsPrimaryFactory : boolean;
    // public bool Spawned
    m_Spawned : boolean;
    // public bool IsInPlayfield
    m_IsInPlayfield : boolean;
    // public bool IsTether
    m_IsTether : boolean;
    // public bool IsAlternativeTether
    m_IsAlternativeTether : boolean;
    // Returns true if owned by the player on this computer
    // public bool IsOwnedByCurrentPlayer
    m_IsOwnedByCurrentPlayer : boolean;
    // public bool DiscoveredByCurrentPlayer
    m_DiscoveredByCurrentPlayer : boolean;
    // public bool DiscoveredByComputer
    m_DiscoveredByComputer : boolean;
    // public bool unknown_bool_41D
    m_unknown_bool_41D : boolean;
    // public bool unknown_bool_41E
    m_unknown_bool_41E : boolean;
    // public bool unknown_bool_41F
    m_unknown_bool_41F : boolean;
    // used for LeptonsPerSightIncrease
    // public char SightIncrease
    m_SightIncrease : number;
    // these two are like Lenny and Carl, weird purpose and never seen separate
    // public bool RecruitableA
    m_RecruitableA : boolean;
    // they're usually set on preplaced objects in maps
    // public bool RecruitableB
    m_RecruitableB : boolean;
    // public bool IsRadarTracked
    m_IsRadarTracked : boolean;
    // public bool IsOnCarryall
    m_IsOnCarryall : boolean;
    // public bool IsCrashing
    m_IsCrashing : boolean;
    // public bool WasCrashingAlready
    m_WasCrashingAlready : boolean;
    // public bool IsBeingManipulated
    m_IsBeingManipulated : boolean;
    // set when something is being molested by a locomotor such as magnetron
    // public TechnoClass * BeingManipulatedBy
    m_BeingManipulatedBy : TechnoClass;
    // the pointee will be marked as the killer of whatever the victim falls onto
    // public HouseClass * ChronoWarpedByHouse
    m_ChronoWarpedByHouse : HouseClass;
    // public bool unknown_bool_430
    m_unknown_bool_430 : boolean;
    // public bool IsMouseHovering
    m_IsMouseHovering : boolean;
    // public bool ShouldBeReselectOnUnlimbo
    m_ShouldBeReselectOnUnlimbo : boolean;
    // public TeamClass * OldTeam
    m_OldTeam : TeamClass;
    // for absorbers, infantry uses this to manually control OwnedInfantry count
    // public bool CountedAsOwnedSpecial
    m_CountedAsOwnedSpecial : boolean;
    // in UnitAbsorb/InfantryAbsorb or smth, lousy memory
    // public bool Absorbed
    m_Absorbed : boolean;
    // public bool unknown_bool_43A
    m_unknown_bool_43A : boolean;
    // public unsigned long unknown_43C
    m_unknown_43C : number;
    // Turret is moving?
    // public int unknown_BOOL_49C
    m_unknown_BOOL_49C : number;
    // public int TurretIsRotating
    m_TurretIsRotating : number;
    // public bool unknown_bool_4B8
    m_unknown_bool_4B8 : boolean;
    // public unsigned long unknown_4BC
    m_unknown_4BC : number;
    // public bool unknown_bool_4D4
    m_unknown_bool_4D4 : boolean;
    // public unsigned long unknown_4D8
    m_unknown_4D8 : number;
    // public unsigned long QueuedVoiceIndex
    m_QueuedVoiceIndex : number;
    // public unsigned long unknown_4F4
    m_unknown_4F4 : number;
    // public bool unknown_bool_4F8
    m_unknown_bool_4F8 : boolean;
    // gets initialized with the current Frame, but this is NOT a TimerStruct!
    // public unsigned long unknown_4FC
    m_unknown_4FC : number;
    // public TechnoClass * QueueUpToEnter
    m_QueueUpToEnter : TechnoClass;
    // public unsigned long EMPLockRemaining
    m_EMPLockRemaining : number;
    // calculated to include cargo etc
    // public unsigned long ThreatPosed
    m_ThreatPosed : number;
    // public unsigned long ShouldLoseTargetNow
    m_ShouldLoseTargetNow : number;
    // public RadBeam * FiringRadBeam
    m_FiringRadBeam : RadBeam;
    // public PlanningTokenClass * PlanningToken
    m_PlanningToken : PlanningTokenClass;
    // public ObjectTypeClass * Disguise
    m_Disguise : ObjectTypeClass;
    // public HouseClass * DisguisedAsHouse
    m_DisguisedAsHouse : HouseClass;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public FlashData Flashing
    m_Flashing : FlashData;
    // public char[8] __Flashing
    m___Flashing : string;
    // how the unit animates
    // public StageClass Animation
    m_Animation : StageClass;
    // public char[28] __Animation
    m___Animation : string;
    // public PassengersClass Passengers
    m_Passengers : PassengersClass;
    // public char[8] __Passengers
    m___Passengers : string;
    // public VeterancyStruct Veterancy
    m_Veterancy : VeterancyStruct;
    // public char[4] __Veterancy
    m___Veterancy : string;
    // MOO
    // public CDTimerClass IdleActionTimer
    m_IdleActionTimer : CDTimerClass;
    // public char[12] __IdleActionTimer
    m___IdleActionTimer : string;
    // public CDTimerClass RadarFlashTimer
    m_RadarFlashTimer : CDTimerClass;
    // public char[12] __RadarFlashTimer
    m___RadarFlashTimer : string;
    // Duration = 45 on init!
    // public CDTimerClass TargetingTimer
    m_TargetingTimer : CDTimerClass;
    // public char[12] __TargetingTimer
    m___TargetingTimer : string;
    // public CDTimerClass IronCurtainTimer
    m_IronCurtainTimer : CDTimerClass;
    // public char[12] __IronCurtainTimer
    m___IronCurtainTimer : string;
    // how often to alternate the effect color
    // public CDTimerClass IronTintTimer
    m_IronTintTimer : CDTimerClass;
    // public char[12] __IronTintTimer
    m___IronTintTimer : string;
    // public CDTimerClass AirstrikeTimer
    m_AirstrikeTimer : CDTimerClass;
    // public char[12] __AirstrikeTimer
    m___AirstrikeTimer : string;
    // tracks alternation of the effect color
    // public CDTimerClass AirstrikeTintTimer
    m_AirstrikeTintTimer : CDTimerClass;
    // public char[12] __AirstrikeTintTimer
    m___AirstrikeTintTimer : string;
    // Rules->InfantryBlinkDisguiseTime , detects mirage firing per description
    // public CDTimerClass InfantryBlinkTimer
    m_InfantryBlinkTimer : CDTimerClass;
    // public char[12] __InfantryBlinkTimer
    m___InfantryBlinkTimer : string;
    // disguise disruption timer
    // public CDTimerClass DisguiseBlinkTimer
    m_DisguiseBlinkTimer : CDTimerClass;
    // public char[12] __DisguiseBlinkTimer
    m___DisguiseBlinkTimer : string;
    // public CDTimerClass ReloadTimer
    m_ReloadTimer : CDTimerClass;
    // public char[12] __ReloadTimer
    m___ReloadTimer : string;
    // each bit corresponds to one player on the map, telling us whether that player has (1) or hasn't (0) spied this building, and the game should display what's being produced inside it to that player. The bits are arranged by player ID, i.e. bit 0 refers to house #0 in HouseClass::Array, 1 to 1, etc.; query like ((1 
    // <
    // <
    // somePlayer->ArrayIndex) 
    // &
    // someFactory->DisplayProductionToHouses) != 0
    // public IndexBitfield<HouseClass *> DisplayProductionTo
    m_DisplayProductionTo : any;
    // public char[4] __DisplayProductionTo
    m___DisplayProductionTo : string;
    // phase from [opaque] -> [fading] -> [transparent] , [General]CloakingStages= long
    // public StageClass CloakProgress
    m_CloakProgress : StageClass;
    // public char[28] __CloakProgress
    m___CloakProgress : string;
    // delay before cloaking again
    // public CDTimerClass CloakDelayTimer
    m_CloakDelayTimer : CDTimerClass;
    // public char[12] __CloakDelayTimer
    m___CloakDelayTimer : string;
    // Originally named Arm in RA1, but this is more descriptive name.
    // public CDTimerClass RearmTimer
    m_RearmTimer : CDTimerClass;
    // public char[12] __RearmTimer
    m___RearmTimer : string;
    // public StorageClass Tiberium
    m_Tiberium : StorageClass;
    // public char[16] __Tiberium
    m___Tiberium : string;
    // times the deploy, unload, etc. cycles
    // public TransitionTimer UnloadTimer
    m_UnloadTimer : TransitionTimer;
    // public char[32] __UnloadTimer
    m___UnloadTimer : string;
    // public FacingClass BarrelFacing
    m_BarrelFacing : FacingClass;
    // public char[24] __BarrelFacing
    m___BarrelFacing : string;
    // public FacingClass PrimaryFacing
    m_PrimaryFacing : FacingClass;
    // public char[24] __PrimaryFacing
    m___PrimaryFacing : string;
    // public FacingClass SecondaryFacing
    m_SecondaryFacing : FacingClass;
    // public char[24] __SecondaryFacing
    m___SecondaryFacing : string;
    // public CDTimerClass TargetLaserTimer
    m_TargetLaserTimer : CDTimerClass;
    // public char[12] __TargetLaserTimer
    m___TargetLaserTimer : string;
    // public RecoilData TurretRecoil
    m_TurretRecoil : RecoilData;
    // public char[32] __TurretRecoil
    m___TurretRecoil : string;
    // public RecoilData BarrelRecoil
    m_BarrelRecoil : RecoilData;
    // public char[32] __BarrelRecoil
    m___BarrelRecoil : string;
    // public DynamicVectorClass<int> CurrentTargetThreatValues
    m_CurrentTargetThreatValues : DynamicVectorClass<number>;
    // public char[24] __CurrentTargetThreatValues
    m___CurrentTargetThreatValues : string;
    // public DynamicVectorClass<AbstractClass *> CurrentTargets
    m_CurrentTargets : DynamicVectorClass<AbstractClass>;
    // public char[24] __CurrentTargets
    m___CurrentTargets : string;
    // if DistributedFire=yes, this is used to determine which possible targets should be ignored in the latest threat scan
    // public DynamicVectorClass<AbstractClass *> AttackedTargets
    m_AttackedTargets : DynamicVectorClass<AbstractClass>;
    // public char[24] __AttackedTargets
    m___AttackedTargets : string;
    // public AudioController Audio3
    m_Audio3 : any;
    // public char[20] __Audio3
    m___Audio3 : string;
    // public AudioController Audio4
    m_Audio4 : any;
    // public char[20] __Audio4
    m___Audio4 : string;
    // public AudioController Audio5
    m_Audio5 : any;
    // public char[20] __Audio5
    m___Audio5 : string;
    // public AudioController Audio6
    m_Audio6 : any;
    // public char[20] __Audio6
    m___Audio6 : string;
}
// forward declarations
// HouseClass
class HouseClass
    extends AbstractClass
{
    // Constructor
    // public HouseClass(HouseTypeClass * pCountry)
    constructor(pCountry_0 : HouseTypeClass);
    // IConnectionPointContainer
    // public virtual long EnumConnectionPoints(IEnumConnectionPoints * * ppEnum)
    EnumConnectionPoints(ppEnum_0 : any | any) : number;
    // public virtual long FindConnectionPoint(_GUID * riid, IConnectionPoint * * ppCP)
    FindConnectionPoint(riid_0 : any | any, ppCP_1 : any | any) : number;
    // IPublicHouse
    // public virtual long Apparent_Category_Quantity(Category category) const
    Apparent_Category_Quantity(category_0 : Category | any) : number;
    // public virtual long Apparent_Category_Power(Category category) const
    Apparent_Category_Power(category_0 : Category | any) : number;
    // public virtual CellStruct Apparent_Base_Center() const
    Apparent_Base_Center() : CellStruct;
    // public virtual bool Is_Powered() const
    Is_Powered() : boolean;
    // IHouse
    // public virtual long ID_Number() const
    ID_Number() : number;
    // public virtual wchar_t * Name() const
    Name() : number;
    // public virtual IApplication * Get_Application()
    Get_Application() : any;
    // public virtual long Available_Money() const
    Available_Money() : number;
    // public virtual long Available_Storage() const
    Available_Storage() : number;
    // public virtual long Power_Output() const
    Power_Output() : number;
    // public virtual long Power_Drain() const
    Power_Drain() : number;
    // public virtual long Category_Quantity(Category category) const
    Category_Quantity(category_0 : Category | any) : number;
    // public virtual long Category_Power(Category category) const
    Category_Power(category_0 : Category | any) : number;
    // public virtual CellStruct Base_Center() const
    Base_Center() : CellStruct;
    // public virtual long Fire_Sale() const
    Fire_Sale() : number;
    // public virtual long All_To_Hunt()
    All_To_Hunt() : number;
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public bool IsAlliedWith(int idxHouse) const
    IsAlliedWith(idxHouse_0 : number) : boolean;
    // public bool IsAlliedWith(HouseClass const * pHouse) const
    IsAlliedWith(pHouse_0 : HouseClass) : boolean;
    // public bool IsAlliedWith(ObjectClass const * pObject) const
    IsAlliedWith(pObject_0 : ObjectClass) : boolean;
    // public bool IsAlliedWith(AbstractClass const * pAbstract) const
    IsAlliedWith(pAbstract_0 : AbstractClass) : boolean;
    // public void MakeAlly(int iHouse, bool bAnnounce)
    MakeAlly(iHouse_0 : number, bAnnounce_1 : boolean) : void;
    // public void MakeAlly(HouseClass * pWho, bool bAnnounce)
    MakeAlly(pWho_0 : HouseClass, bAnnounce_1 : boolean) : void;
    // public void MakeEnemy(HouseClass * pWho, bool bAnnounce)
    MakeEnemy(pWho_0 : HouseClass, bAnnounce_1 : boolean) : void;
    // public void AdjustThreats()
    AdjustThreats() : void;
    // public void UpdateAngerNodes(int nScoreAdd, HouseClass * pHouse)
    UpdateAngerNodes(nScoreAdd_0 : number, pHouse_1 : HouseClass) : void;
    // public void AllyAIHouses()
    AllyAIHouses() : void;
    // no explosions, just poooof
    // public void SDDTORAllAndTriggers()
    SDDTORAllAndTriggers() : void;
    // public void AcceptDefeat()
    AcceptDefeat() : void;
    // every matching object takes damage and explodes
    // public void DestroyAll()
    DestroyAll() : void;
    // public void DestroyAllBuildings()
    DestroyAllBuildings() : void;
    // public void DestroyAllNonBuildingsNonNaval()
    DestroyAllNonBuildingsNonNaval() : void;
    // public void DestroyAllNonBuildingsNaval()
    DestroyAllNonBuildingsNaval() : void;
    // public void RespawnStartingBuildings()
    RespawnStartingBuildings() : void;
    // public void RespawnStartingForces()
    RespawnStartingForces() : void;
    // public unsigned char Win(bool bSavourSomething)
    Win(bSavourSomething_0 : boolean) : number;
    // public unsigned char Lose(bool bSavourSomething)
    Lose(bSavourSomething_0 : boolean) : number;
    // public void RegisterJustBuilt(TechnoClass * pTechno)
    RegisterJustBuilt(pTechno_0 : TechnoClass) : void;
    // public bool CanAlly(HouseClass * pOther) const
    CanAlly(pOther_0 : HouseClass) : boolean;
    // public bool CanOverpower(TechnoClass * pTarget) const
    CanOverpower(pTarget_0 : TechnoClass) : boolean;
    // warning: logic pretty much broken
    // public void LostPoweredCenter(TechnoTypeClass * pTechnoType)
    LostPoweredCenter(pTechnoType_0 : TechnoTypeClass) : void;
    // public void GainedPoweredCenter(TechnoTypeClass * pTechnoType)
    GainedPoweredCenter(pTechnoType_0 : TechnoTypeClass) : void;
    // public bool DoInfantrySelfHeal() const
    DoInfantrySelfHeal() : boolean;
    // public int GetInfSelfHealStep() const
    GetInfSelfHealStep() : number;
    // public bool DoUnitsSelfHeal() const
    DoUnitsSelfHeal() : boolean;
    // public int GetUnitSelfHealStep() const
    GetUnitSelfHealStep() : number;
    // public void UpdatePower()
    UpdatePower() : void;
    // public void CreatePowerOutage(int duration)
    CreatePowerOutage(duration_0 : number) : void;
    // public double GetPowerPercentage() const
    GetPowerPercentage() : number;
    // public bool HasFullPower() const
    HasFullPower() : boolean;
    // public bool HasLowPower() const
    HasLowPower() : boolean;
    // public void CreateRadarOutage(int duration)
    CreateRadarOutage(duration_0 : number) : void;
    // won't work if has spysat
    // public void ReshroudMap()
    ReshroudMap() : void;
    // public void Cheer()
    Cheer() : void;
    // public void BuildingUnderAttack(BuildingClass * pBld)
    BuildingUnderAttack(pBld_0 : BuildingClass) : void;
    // public void TakeMoney(int amount)
    TakeMoney(amount_0 : number) : void;
    // public void GiveMoney(int amount)
    GiveMoney(amount_0 : number) : void;
    // public bool CanTransactMoney(int amount) const
    CanTransactMoney(amount_0 : number) : boolean;
    // public void TransactMoney(int amount)
    TransactMoney(amount_0 : number) : void;
    // public void GiveTiberium(float amount, int type)
    GiveTiberium(amount_0 : number, type_1 : number) : void;
    // public void UpdateAllSilos(int prevStorage, int prevTotalStorage)
    UpdateAllSilos(prevStorage_0 : number, prevTotalStorage_1 : number) : void;
    // public double GetStoragePercentage()
    GetStoragePercentage() : number;
    // no LostThreatNode() , this gets called also when node building dies! BUG
    // public void AcquiredThreatNode()
    AcquiredThreatNode() : void;
    // these are for mostly for map actions - HouseClass* foo = IsMP() ? Find_YesMP() : Find_NoMP();
    // public static bool Index_IsMP(int idx)
    static Index_IsMP(idx_0 : number) : boolean;
    // public static HouseClass * FindByCountryIndex(int HouseType)
    static FindByCountryIndex(HouseType_0 : number) : HouseClass;
    // public static HouseClass * FindByIndex(int idxHouse)
    static FindByIndex(idxHouse_0 : number) : HouseClass;
    // public static int FindIndexByName(char const * name)
    static FindIndexByName(name_0 : string) : number;
    // public static int GetPlayerAtFromString(char const * name)
    static GetPlayerAtFromString(name_0 : string) : number;
    // public static HouseClass * FindByPlayerAt(int at)
    static FindByPlayerAt(at_0 : number) : HouseClass;
    // gets the first house of a type with this name
    // public static HouseClass * FindByCountryName(char const * name)
    static FindByCountryName(name_0 : string) : HouseClass;
    // gets the first house of a type with name Neutral
    // public static HouseClass * FindNeutral()
    static FindNeutral() : HouseClass;
    // gets the first house of a type with name Special
    // public static HouseClass * FindSpecial()
    static FindSpecial() : HouseClass;
    // gets the first house of a side with this name
    // public static HouseClass * FindBySideIndex(int index)
    static FindBySideIndex(index_0 : number) : HouseClass;
    // gets the first house of a type with this name
    // public static HouseClass * FindBySideName(char const * name)
    static FindBySideName(name_0 : string) : HouseClass;
    // gets the first house of a type from the Civilian side
    // public static HouseClass * FindCivilianSide()
    static FindCivilianSide() : HouseClass;
    // public static void LoadFromINIList(CCINIClass * pINI)
    static LoadFromINIList(pINI_0 : CCINIClass) : void;
    // public int GetSpawnPosition()
    GetSpawnPosition() : number;
    // public WaypointClass * GetPlanningWaypointAt(CellStruct * coords)
    GetPlanningWaypointAt(coords_0 : CellStruct) : WaypointClass;
    // public bool GetPlanningWaypointProperties(WaypointClass * wpt, int& idxPath, unsigned char& idxWP)
    GetPlanningWaypointProperties(wpt_0 : WaypointClass, idxPath_1 : number, idxWP_2 : number) : boolean;
    // calls WaypointPathClass::WaypointPathClass() if needed
    // public void EnsurePlanningPathExists(int idx)
    EnsurePlanningPathExists(idx_0 : number) : void;
    // call after the availability of a factory has changed.
    // public void Update_FactoriesQueues(AbstractType factoryOf, bool isNaval, BuildCat buildCat) const
    Update_FactoriesQueues(factoryOf_0 : AbstractType, isNaval_1 : boolean, buildCat_2 : BuildCat) : void;
    // returns the factory owned by this house, having pItem in production right now, not queued
    // public FactoryClass * GetFactoryProducing(TechnoTypeClass const * pItem) const
    GetFactoryProducing(pItem_0 : TechnoTypeClass) : FactoryClass;
    // finds a buildingtype from the given array that this house can build
    // this checks whether the Owner=, Required/ForbiddenHouses= , AIBasePlanningSide= match and if SuperWeapon= (not SW2=) is not forbidden
    // public BuildingTypeClass * FirstBuildableFromArray(DynamicVectorClass<BuildingTypeClass *> const& items)
    FirstBuildableFromArray(items_0 : DynamicVectorClass<BuildingTypeClass>) : BuildingTypeClass;
    // are all prereqs for Techno listed in vectorBuildings[0..vectorLength]. Yes, the length is needed (the vector is used for breadth-first search)
    // public bool AllPrerequisitesAvailable(TechnoTypeClass const * pItem, DynamicVectorClass<BuildingTypeClass *> const& vectorBuildings, int vectorLength)
    AllPrerequisitesAvailable(pItem_0 : TechnoTypeClass, vectorBuildings_1 : DynamicVectorClass<BuildingTypeClass>, vectorLength_2 : number) : boolean;
    // Whether any human player controls this house.
    // public bool IsControlledByHuman() const
    IsControlledByHuman() : boolean;
    // Whether the human player on this computer can control this house.
    // public bool IsControlledByCurrentPlayer() const
    IsControlledByCurrentPlayer() : boolean;
    // Target ought to be Object, I imagine, but cell doesn't work then
    // public void SendSpyPlanes(int AircraftTypeIdx, int AircraftAmount, Mission SetMission, AbstractClass * Target, ObjectClass * Destination)
    SendSpyPlanes(AircraftTypeIdx_0 : number, AircraftAmount_1 : number, SetMission_2 : Mission, Target_3 : AbstractClass, Destination_4 : ObjectClass) : void;
    // registering in prereq counters (all technoes get logged, but only buildings get checked on validation... wtf)
    // public void RegisterGain(TechnoClass * pTechno, bool ownerChange)
    RegisterGain(pTechno_0 : TechnoClass, ownerChange_1 : boolean) : void;
    // public void RegisterLoss(TechnoClass * pTechno, bool keepTiberium)
    RegisterLoss(pTechno_0 : TechnoClass, keepTiberium_1 : boolean) : void;
    // public BuildingClass * FindBuildingOfType(int idx, int sector = -1) const
    FindBuildingOfType(idx_0 : number, sector_1 : number) : BuildingClass;
    // public AnimClass * PsiWarn(CellClass * pTarget, BulletClass * Bullet, char * AnimName)
    PsiWarn(pTarget_0 : CellClass, Bullet_1 : BulletClass, AnimName_2 : string) : AnimClass;
    // public bool Fire_LightningStorm(SuperClass * pSuper)
    Fire_LightningStorm(pSuper_0 : SuperClass) : boolean;
    // public bool Fire_ParaDrop(SuperClass * pSuper)
    Fire_ParaDrop(pSuper_0 : SuperClass) : boolean;
    // public bool Fire_PsyDom(SuperClass * pSuper)
    Fire_PsyDom(pSuper_0 : SuperClass) : boolean;
    // public bool Fire_GenMutator(SuperClass * pSuper)
    Fire_GenMutator(pSuper_0 : SuperClass) : boolean;
    // public bool IonSensitivesShouldBeOffline() const
    IonSensitivesShouldBeOffline() : boolean;
    // public char const * get_ID() const
    get_ID() : string;
    // public int FindSuperWeaponIndex(SuperWeaponType type) const
    FindSuperWeaponIndex(type_0 : SuperWeaponType) : number;
    // public SuperClass * FindSuperWeapon(SuperWeaponType type) const
    FindSuperWeapon(type_0 : SuperWeaponType) : SuperClass;
    // Count owned now
    // public int CountOwnedNow(TechnoTypeClass const * pItem) const
    CountOwnedNow(pItem_0 : TechnoTypeClass) : number;
    // public int CountOwnedNow(BuildingTypeClass const * const pItem) const
    CountOwnedNow(pItem_0 : BuildingTypeClass) : number;
    // public int CountOwnedNow(AircraftTypeClass const * const pItem) const
    CountOwnedNow(pItem_0 : AircraftTypeClass) : number;
    // public int CountOwnedNow(InfantryTypeClass const * const pItem) const
    CountOwnedNow(pItem_0 : InfantryTypeClass) : number;
    // public int CountOwnedNow(UnitTypeClass const * const pItem) const
    CountOwnedNow(pItem_0 : UnitTypeClass) : number;
    // Count owned and present
    // public int CountOwnedAndPresent(TechnoTypeClass const * pItem) const
    CountOwnedAndPresent(pItem_0 : TechnoTypeClass) : number;
    // public int CountOwnedAndPresent(BuildingTypeClass const * const pItem) const
    CountOwnedAndPresent(pItem_0 : BuildingTypeClass) : number;
    // public int CountOwnedAndPresent(AircraftTypeClass const * const pItem) const
    CountOwnedAndPresent(pItem_0 : AircraftTypeClass) : number;
    // public int CountOwnedAndPresent(InfantryTypeClass const * const pItem) const
    CountOwnedAndPresent(pItem_0 : InfantryTypeClass) : number;
    // public int CountOwnedAndPresent(UnitTypeClass const * const pItem) const
    CountOwnedAndPresent(pItem_0 : UnitTypeClass) : number;
    // Count owned ever
    // public int CountOwnedEver(TechnoTypeClass const * pItem) const
    CountOwnedEver(pItem_0 : TechnoTypeClass) : number;
    // public int CountOwnedEver(BuildingTypeClass const * const pItem) const
    CountOwnedEver(pItem_0 : BuildingTypeClass) : number;
    // public int CountOwnedEver(AircraftTypeClass const * const pItem) const
    CountOwnedEver(pItem_0 : AircraftTypeClass) : number;
    // public int CountOwnedEver(InfantryTypeClass const * const pItem) const
    CountOwnedEver(pItem_0 : InfantryTypeClass) : number;
    // public int CountOwnedEver(UnitTypeClass const * const pItem) const
    CountOwnedEver(pItem_0 : UnitTypeClass) : number;
    // public bool HasFromSecretLab(TechnoTypeClass const * const pItem) const
    HasFromSecretLab(pItem_0 : TechnoTypeClass) : boolean;
    // public bool HasAllStolenTech(TechnoTypeClass const * const pItem) const
    HasAllStolenTech(pItem_0 : TechnoTypeClass) : boolean;
    // public bool HasFactoryForObject(TechnoTypeClass const * const pItem) const
    HasFactoryForObject(pItem_0 : TechnoTypeClass) : boolean;
    // public bool CanExpectToBuild(TechnoTypeClass const * pItem) const
    CanExpectToBuild(pItem_0 : TechnoTypeClass) : boolean;
    // public bool CanExpectToBuild(TechnoTypeClass const * pItem, int idxParent) const
    CanExpectToBuild(pItem_0 : TechnoTypeClass, idxParent_1 : number) : boolean;
    // public bool InOwners(TechnoTypeClass const * const pItem) const
    InOwners(pItem_0 : TechnoTypeClass) : boolean;
    // public bool InRequiredHouses(TechnoTypeClass const * const pItem) const
    InRequiredHouses(pItem_0 : TechnoTypeClass) : boolean;
    // public bool InForbiddenHouses(TechnoTypeClass const * const pItem) const
    InForbiddenHouses(pItem_0 : TechnoTypeClass) : boolean;
    // public CanBuildResult CanBuild(TechnoTypeClass const * pItem, bool buildLimitOnly, bool allowIfInProduction) const
    CanBuild(pItem_0 : TechnoTypeClass, buildLimitOnly_1 : boolean, allowIfInProduction_2 : boolean) : CanBuildResult;
    // public int AI_BaseConstructionUpdate()
    AI_BaseConstructionUpdate() : number;
    // public int AI_VehicleConstructionUpdate()
    AI_VehicleConstructionUpdate() : number;
    // public void AI_TryFireSW()
    AI_TryFireSW() : void;
    // public bool Fire_SW(int idx, CellStruct const& coords)
    Fire_SW(idx_0 : number, coords_1 : CellStruct) : boolean;
    // public CellStruct * PickTargetByType(CellStruct& outBuffer, QuarryType targetType) const
    PickTargetByType(outBuffer_0 : CellStruct, targetType_1 : QuarryType) : CellStruct;
    // public CellStruct PickTargetByType(QuarryType targetType) const
    PickTargetByType(targetType_0 : QuarryType) : CellStruct;
    // public CellStruct * PickIonCannonTarget(CellStruct& outBuffer) const
    PickIonCannonTarget(outBuffer_0 : CellStruct) : CellStruct;
    // public CellStruct PickIonCannonTarget() const
    PickIonCannonTarget() : CellStruct;
    // public bool IsIonCannonEligibleTarget(TechnoClass const * pTechno) const
    IsIonCannonEligibleTarget(pTechno_0 : TechnoClass) : boolean;
    // public void UpdateFlagCoords(UnitClass * NewCarrier, unsigned long dwUnk)
    UpdateFlagCoords(NewCarrier_0 : UnitClass, dwUnk_1 : number) : void;
    // public void DroppedFlag(CellStruct * Where, UnitClass * Who)
    DroppedFlag(Where_0 : CellStruct, Who_1 : UnitClass) : void;
    // public char PickedUpFlag(UnitClass * Who, unsigned long dwUnk)
    PickedUpFlag(Who_0 : UnitClass, dwUnk_1 : number) : number;
    // public FactoryClass * GetPrimaryFactory(AbstractType absID, bool naval, BuildCat buildCat) const
    GetPrimaryFactory(absID_0 : AbstractType, naval_1 : boolean, buildCat_2 : BuildCat) : FactoryClass;
    // public void SetPrimaryFactory(FactoryClass * pFactory, AbstractType absID, bool naval, BuildCat buildCat)
    SetPrimaryFactory(pFactory_0 : FactoryClass, absID_1 : AbstractType, naval_2 : boolean, buildCat_3 : BuildCat) : void;
    // public CellStruct const& GetBaseCenter() const
    GetBaseCenter() : CellStruct;
    // public unsigned int GetAIDifficultyIndex() const
    GetAIDifficultyIndex() : number;
    // At the moment, this function is really just a more intuitively named mask for
    // this->Type->MultiplayPassive, but it might be expanded into something more
    // complicated later.
    // Primarily used to check if something is owned by the neutral house.
    // 
    // @return true if house is passive in multiplayer, false if not.
    // @author Renegade
    // @date 01.03.10
    // public bool IsNeutral() const
    IsNeutral() : boolean;
    // Whether this house is equal to CurrentPlayer
    // public bool IsCurrentPlayer() const
    IsCurrentPlayer() : boolean;
    // Whether this house is equal to Observer
    // public bool IsObserver() const
    IsObserver() : boolean;
    // Whether CurrentPlayer is equal to Observer
    // public static bool IsCurrentPlayerObserver()
    static IsCurrentPlayerObserver() : boolean;
    // public int CalculateCostMultipliers()
    CalculateCostMultipliers() : number;
    // public void ForceEnd()
    ForceEnd() : void;
    // public void RemoveTracking(TechnoClass * pTechno)
    RemoveTracking(pTechno_0 : TechnoClass) : void;
    // public void AddTracking(TechnoClass * pTechno)
    AddTracking(pTechno_0 : TechnoClass) : void;
    // public double GetWeedStoragePercentage()
    GetWeedStoragePercentage() : number;
    // public bool AISupers()
    AISupers() : boolean;
    // public static AbstractType const AbsID = AbstractType::House
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<HouseClass *>, 11010600> const Array = 0xA80228u
    static s_Array : DynamicVectorClass<HouseClass>;
    // House of player at this computer.
    // public static reference<HouseClass *, 11025740, 0> const CurrentPlayer = 0xA83D4Cu
    static s_CurrentPlayer : HouseClass;
    // House of player that is observer.
    // public static reference<HouseClass *, 11276696, 0> const Observer = 0xAC1198u
    static s_Observer : HouseClass;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public HouseTypeClass * Type
    m_Type : HouseTypeClass;
    // public int CountResourceGatherers
    m_CountResourceGatherers : number;
    // public int CountResourceDestinations
    m_CountResourceDestinations : number;
    // public int CountWarfactories
    m_CountWarfactories : number;
    // public int InfantrySelfHeal
    m_InfantrySelfHeal : number;
    // public int UnitsSelfHeal
    m_UnitsSelfHeal : number;
    // be advised that it's reverse, Hard == 0 and Easy == 2. I'm sure Westwood has a good reason for this. Yep.
    // public AIDifficulty AIDifficulty
    m_AIDifficulty : AIDifficulty;
    // used
    // public double FirepowerMultiplier
    m_FirepowerMultiplier : number;
    // unused ...
    // public double GroundspeedMultiplier
    m_GroundspeedMultiplier : number;
    // public double AirspeedMultiplier
    m_AirspeedMultiplier : number;
    // public double ArmorMultiplier
    m_ArmorMultiplier : number;
    // public double ROFMultiplier
    m_ROFMultiplier : number;
    // public double CostMultiplier
    m_CostMultiplier : number;
    // ... unused ends
    // public double BuildTimeMultiplier
    m_BuildTimeMultiplier : number;
    // public double RepairDelay
    m_RepairDelay : number;
    // public double BuildDelay
    m_BuildDelay : number;
    // public int IQLevel
    m_IQLevel : number;
    // public int TechLevel
    m_TechLevel : number;
    // ask question, receive brain damage
    // public IndexBitfield<HouseClass *> AltAllies
    m_AltAllies : any;
    // not sure how these are used // actual credits = this * 100
    // public int StartingCredits
    m_StartingCredits : number;
    // public Edge StartingEdge
    m_StartingEdge : Edge;
    // public unsigned long AIState_1E4
    m_AIState_1E4 : number;
    // public int SideIndex
    m_SideIndex : number;
    // Is controlled by a human player.
    // public bool IsHumanPlayer
    m_IsHumanPlayer : boolean;
    // Is controlled by current player.
    // public bool IsInPlayerControl
    m_IsInPlayerControl : boolean;
    // AI production has begun.
    // public bool Production
    m_Production : boolean;
    // public bool AutocreateAllowed
    m_AutocreateAllowed : boolean;
    // public bool NodeLogic_1F0
    m_NodeLogic_1F0 : boolean;
    // public bool ShipYardConst_1F1
    m_ShipYardConst_1F1 : boolean;
    // public bool AITriggersActive
    m_AITriggersActive : boolean;
    // public bool AutoBaseBuilding
    m_AutoBaseBuilding : boolean;
    // public bool DiscoveredByPlayer
    m_DiscoveredByPlayer : boolean;
    // public bool Defeated
    m_Defeated : boolean;
    // public bool IsGameOver
    m_IsGameOver : boolean;
    // public bool IsWinner
    m_IsWinner : boolean;
    // public bool IsLoser
    m_IsLoser : boolean;
    // used by the CivEvac triggers
    // public bool CiviliansEvacuated
    m_CiviliansEvacuated : boolean;
    // public bool FirestormActive
    m_FirestormActive : boolean;
    // public bool HasThreatNode
    m_HasThreatNode : boolean;
    // public bool RecheckTechTree
    m_RecheckTechTree : boolean;
    // public int IPAddress
    m_IPAddress : number;
    // public int TournamentTeamID
    m_TournamentTeamID : number;
    // public bool LostConnection
    m_LostConnection : boolean;
    // public int SelectedPathIndex
    m_SelectedPathIndex : number;
    // 12 paths for "planning mode"
    // public WaypointPathClass *[12] PlanningPaths
    m_PlanningPaths : WaypointPathClass;
    // ??? exe says so
    // public char Visionary
    m_Visionary : number;
    // public bool MapIsClear
    m_MapIsClear : boolean;
    // public bool IsTiberiumShort
    m_IsTiberiumShort : boolean;
    // public bool HasBeenSpied
    m_HasBeenSpied : boolean;
    // Something of this house has been entered by a Thief/VehicleThief
    // public bool HasBeenThieved
    m_HasBeenThieved : boolean;
    // BuildingClass::Repair, handholder for hurr durf AI
    // public bool Repairing
    m_Repairing : boolean;
    // public bool IsBuiltSomething
    m_IsBuiltSomething : boolean;
    // public bool IsResigner
    m_IsResigner : boolean;
    // public bool IsGiverUpper
    m_IsGiverUpper : boolean;
    // public bool AllToHunt
    m_AllToHunt : boolean;
    // public bool IsParanoid
    m_IsParanoid : boolean;
    // public bool IsToLook
    m_IsToLook : boolean;
    // no idea why we got this twice
    // public int IQLevel2
    m_IQLevel2 : number;
    // public AIMode AIMode
    m_AIMode : AIMode;
    // public int LastBuiltBuildingType
    m_LastBuiltBuildingType : number;
    // public int LastBuiltInfantryType
    m_LastBuiltInfantryType : number;
    // public int LastBuiltAircraftType
    m_LastBuiltAircraftType : number;
    // public int LastBuiltVehicleType
    m_LastBuiltVehicleType : number;
    // some ra1 residue map trigger-fu, should die a painful death
    // public int AllowWinBlocks
    m_AllowWinBlocks : number;
    // asswards! whether this player has infiltrated stuff
    // public bool Side2TechInfiltrated
    m_Side2TechInfiltrated : boolean;
    // which is listed in [AI]->BuildTech
    // public bool Side1TechInfiltrated
    m_Side1TechInfiltrated : boolean;
    // and has the appropriate AIBasePlanningSide
    // public bool Side0TechInfiltrated
    m_Side0TechInfiltrated : boolean;
    // public bool BarracksInfiltrated
    m_BarracksInfiltrated : boolean;
    // public bool WarFactoryInfiltrated
    m_WarFactoryInfiltrated : boolean;
    // these four are unused horrors
    // checking prerequisites:
    // if(1 
    // <
    // <
    // this->Country->IndexInArray 
    // &
    // item->RequiredHouses
    // || (item->WhatAmI == abs_InfantryType 
    // &
    // &
    // (item->RequiredHouses 
    // &
    // this->InfantryAltOwner))
    // || (item->WhatAmI == abs_UnitType 
    // &
    // &
    // (item->RequiredHouses 
    // &
    // this->UnitAltOwner))
    // || (item->WhatAmI == abs_AircraftType 
    // &
    // &
    // (item->RequiredHouses 
    // &
    // this->AircraftAltOwner))
    // || (item->WhatAmI == abs_BuildingType 
    // &
    // &
    // (item->RequiredHouses 
    // &
    // this->BuildingAltOwner))
    // )
    // { can build }
    // public unsigned long InfantryAltOwner
    m_InfantryAltOwner : number;
    // public unsigned long UnitAltOwner
    m_UnitAltOwner : number;
    // public unsigned long AircraftAltOwner
    m_AircraftAltOwner : number;
    // public unsigned long BuildingAltOwner
    m_BuildingAltOwner : number;
    // public int AirportDocks
    m_AirportDocks : number;
    // public int PoweredUnitCenters
    m_PoweredUnitCenters : number;
    // public int CreditsSpent
    m_CreditsSpent : number;
    // public int HarvestedCredits
    m_HarvestedCredits : number;
    // public int StolenBuildingsCredits
    m_StolenBuildingsCredits : number;
    // public int OwnedUnits
    m_OwnedUnits : number;
    // public int OwnedNavy
    m_OwnedNavy : number;
    // public int OwnedBuildings
    m_OwnedBuildings : number;
    // public int OwnedInfantry
    m_OwnedInfantry : number;
    // public int OwnedAircraft
    m_OwnedAircraft : number;
    // public int Balance
    m_Balance : number;
    // capacity of all building Storage
    // public int TotalStorage
    m_TotalStorage : number;
    // public unsigned long unknown_324
    m_unknown_324 : number;
    // public int NumAirpads
    m_NumAirpads : number;
    // public int NumBarracks
    m_NumBarracks : number;
    // public int NumWarFactories
    m_NumWarFactories : number;
    // public int NumConYards
    m_NumConYards : number;
    // public int NumShipyards
    m_NumShipyards : number;
    // public int NumOrePurifiers
    m_NumOrePurifiers : number;
    // public float CostInfantryMult
    m_CostInfantryMult : number;
    // public float CostUnitsMult
    m_CostUnitsMult : number;
    // public float CostAircraftMult
    m_CostAircraftMult : number;
    // public float CostBuildingsMult
    m_CostBuildingsMult : number;
    // public float CostDefensesMult
    m_CostDefensesMult : number;
    // public int PowerOutput
    m_PowerOutput : number;
    // public int PowerDrain
    m_PowerDrain : number;
    // public FactoryClass * Primary_ForAircraft
    m_Primary_ForAircraft : FactoryClass;
    // public FactoryClass * Primary_ForInfantry
    m_Primary_ForInfantry : FactoryClass;
    // public FactoryClass * Primary_ForVehicles
    m_Primary_ForVehicles : FactoryClass;
    // public FactoryClass * Primary_ForShips
    m_Primary_ForShips : FactoryClass;
    // public FactoryClass * Primary_ForBuildings
    m_Primary_ForBuildings : FactoryClass;
    // public FactoryClass * Primary_Unused1
    m_Primary_Unused1 : FactoryClass;
    // public FactoryClass * Primary_Unused2
    m_Primary_Unused2 : FactoryClass;
    // public FactoryClass * Primary_Unused3
    m_Primary_Unused3 : FactoryClass;
    // public FactoryClass * Primary_ForDefenses
    m_Primary_ForDefenses : FactoryClass;
    // public unsigned char AircraftType_53D0
    m_AircraftType_53D0 : number;
    // public unsigned char InfantryType_53D1
    m_InfantryType_53D1 : number;
    // public unsigned char VehicleType_53D2
    m_VehicleType_53D2 : number;
    // public unsigned char ShipType_53D3
    m_ShipType_53D3 : number;
    // public unsigned char BuildingType_53D4
    m_BuildingType_53D4 : number;
    // public unsigned char unknown_53D5
    m_unknown_53D5 : number;
    // public unsigned char unknown_53D6
    m_unknown_53D6 : number;
    // public unsigned char unknown_53D7
    m_unknown_53D7 : number;
    // public unsigned char DefenseType_53D8
    m_DefenseType_53D8 : number;
    // public unsigned char unknown_53D9
    m_unknown_53D9 : number;
    // public unsigned char unknown_53DA
    m_unknown_53DA : number;
    // public unsigned char unknown_53DB
    m_unknown_53DB : number;
    // public UnitClass * OurFlagCarrier
    m_OurFlagCarrier : UnitClass;
    // public CellStruct OurFlagCoords
    m_OurFlagCoords : CellStruct;
    // 20 Houses only!
    // public int[20] KilledUnitsOfHouses
    m_KilledUnitsOfHouses : number;
    // public int TotalKilledUnits
    m_TotalKilledUnits : number;
    // 20 Houses only!
    // public int[20] KilledBuildingsOfHouses
    m_KilledBuildingsOfHouses : number;
    // public int TotalKilledBuildings
    m_TotalKilledBuildings : number;
    // public int WhoLastHurtMe
    m_WhoLastHurtMe : number;
    // public CellStruct BaseSpawnCell
    m_BaseSpawnCell : CellStruct;
    // set by map action 137 and 138
    // public CellStruct BaseCenter
    m_BaseCenter : CellStruct;
    // public int Radius
    m_Radius : number;
    // public int LATime
    m_LATime : number;
    // public int LAEnemy
    m_LAEnemy : number;
    // public int ToCapture
    m_ToCapture : number;
    // this crap is being rewritten to use house indices instead of house types
    // public IndexBitfield<HouseClass *> RadarVisibleTo
    m_RadarVisibleTo : any;
    // public int SiloMoney
    m_SiloMoney : number;
    // Set via map action 35. The preferred object type to attack.
    // public QuarryType PreferredTargetType
    m_PreferredTargetType : QuarryType;
    // Set via map action 135 and 136. Used to override firing location of targettable SWs.
    // public CellStruct PreferredTargetCell
    m_PreferredTargetCell : CellStruct;
    // Set via map action 140 and 141, or when an AIDefendAgainst SW is launched.
    // public CellStruct PreferredDefensiveCell
    m_PreferredDefensiveCell : CellStruct;
    // No known function sets this to a real value, but it would take precedence over the other.
    // public CellStruct PreferredDefensiveCell2
    m_PreferredDefensiveCell2 : CellStruct;
    // The frame the PreferredDefensiveCell was set. Used to fire the Force Shield.
    // public int PreferredDefensiveCellStartTime
    m_PreferredDefensiveCellStartTime : number;
    // both unused
    // public int InitialAttackDelay
    m_InitialAttackDelay : number;
    // public int EnemyHouseIndex
    m_EnemyHouseIndex : number;
    // public int ProducingBuildingTypeIndex
    m_ProducingBuildingTypeIndex : number;
    // public int ProducingUnitTypeIndex
    m_ProducingUnitTypeIndex : number;
    // public int ProducingInfantryTypeIndex
    m_ProducingInfantryTypeIndex : number;
    // public int ProducingAircraftTypeIndex
    m_ProducingAircraftTypeIndex : number;
    // public int RatioAITriggerTeam
    m_RatioAITriggerTeam : number;
    // public int RatioTeamAircraft
    m_RatioTeamAircraft : number;
    // public int RatioTeamInfantry
    m_RatioTeamInfantry : number;
    // public int RatioTeamBuildings
    m_RatioTeamBuildings : number;
    // public int BaseDefenseTeamCount
    m_BaseDefenseTeamCount : number;
    // public int CurrentDropshipIndex
    m_CurrentDropshipIndex : number;
    // don't ask
    // public unsigned char HasCloakingRanges
    m_HasCloakingRanges : number;
    // public ColorStruct Color
    m_Color : ColorStruct;
    // my idb says so
    // public ColorStruct LaserColor
    m_LaserColor : ColorStruct;
    // public BaseClass Base
    m_Base : BaseClass;
    // public bool RecheckPower
    m_RecheckPower : boolean;
    // public bool RecheckRadar
    m_RecheckRadar : boolean;
    // public bool SpySatActive
    m_SpySatActive : boolean;
    // public bool IsBeingDrained
    m_IsBeingDrained : boolean;
    // public Edge Edge
    m_Edge : Edge;
    // public CellStruct EMPTarget
    m_EMPTarget : CellStruct;
    // public CellStruct NukeTarget
    m_NukeTarget : CellStruct;
    // flags, one bit per HouseClass instance
    // public IndexBitfield<HouseClass *> Allies
    m_Allies : any;
    // public IAIHouse * AIGeneral
    m_AIGeneral : any;
    // BLARGH
    // public unsigned int[130][130] ThreatPosedEstimates
    m_ThreatPosedEstimates : number;
    // this defaults to the owner country's name in SP or 
    // <human
    // player>
    // <computer
    // player> in MP. Used as owner for preplaced map objects
    // public char[21] PlainName
    m_PlainName : string;
    // this contains the UIName= text from the INI! or
    // public char[33] UINameString
    m_UINameString : string;
    // this contains the CSF string from UIName= above, or a copy of the country's UIName if not defined. Take note that this is shorter than the country's UIName can be...
    // public wchar_t[21] UIName
    m_UIName : number;
    // public int ColorSchemeIndex
    m_ColorSchemeIndex : number;
    // public IndexBitfield<HouseClass *> StartingAllies
    m_StartingAllies : any;
    // public unsigned long unknown_16060
    m_unknown_16060 : number;
    // public unsigned long unknown_1607C
    m_unknown_1607C : number;
    // public unsigned long unknown_16080
    m_unknown_16080 : number;
    // public unsigned long unknown_16084
    m_unknown_16084 : number;
    // public double unused_16088
    m_unused_16088 : number;
    // public double unused_16090
    m_unused_16090 : number;
    // public unsigned long padding_16098
    m_padding_16098 : number;
    // defaults to 0.33, AIForcePredictionFudge'd later
    // public float PredictionEnemyArmor
    m_PredictionEnemyArmor : number;
    // public float PredictionEnemyAir
    m_PredictionEnemyAir : number;
    // public float PredictionEnemyInfantry
    m_PredictionEnemyInfantry : number;
    // public int TotalOwnedInfantryCost
    m_TotalOwnedInfantryCost : number;
    // public int TotalOwnedVehicleCost
    m_TotalOwnedVehicleCost : number;
    // public int TotalOwnedAircraftCost
    m_TotalOwnedAircraftCost : number;
    // public int PowerSurplus
    m_PowerSurplus : number;
    // public DynamicVectorClass<TagClass *> RelatedTags
    m_RelatedTags : DynamicVectorClass<TagClass>;
    // public char[24] __RelatedTags
    m___RelatedTags : string;
    // public DynamicVectorClass<BuildingClass *> ConYards
    m_ConYards : DynamicVectorClass<BuildingClass>;
    // public char[24] __ConYards
    m___ConYards : string;
    // public DynamicVectorClass<BuildingClass *> Buildings
    m_Buildings : DynamicVectorClass<BuildingClass>;
    // public char[24] __Buildings
    m___Buildings : string;
    // public DynamicVectorClass<BuildingClass *> UnitRepairStations
    m_UnitRepairStations : DynamicVectorClass<BuildingClass>;
    // public char[24] __UnitRepairStations
    m___UnitRepairStations : string;
    // public DynamicVectorClass<BuildingClass *> Grinders
    m_Grinders : DynamicVectorClass<BuildingClass>;
    // public char[24] __Grinders
    m___Grinders : string;
    // public DynamicVectorClass<BuildingClass *> Absorbers
    m_Absorbers : DynamicVectorClass<BuildingClass>;
    // public char[24] __Absorbers
    m___Absorbers : string;
    // public DynamicVectorClass<BuildingClass *> Bunkers
    m_Bunkers : DynamicVectorClass<BuildingClass>;
    // public char[24] __Bunkers
    m___Bunkers : string;
    // public DynamicVectorClass<BuildingClass *> Occupiables
    m_Occupiables : DynamicVectorClass<BuildingClass>;
    // public char[24] __Occupiables
    m___Occupiables : string;
    // public DynamicVectorClass<BuildingClass *> CloningVats
    m_CloningVats : DynamicVectorClass<BuildingClass>;
    // public char[24] __CloningVats
    m___CloningVats : string;
    // public DynamicVectorClass<BuildingClass *> SecretLabs
    m_SecretLabs : DynamicVectorClass<BuildingClass>;
    // public char[24] __SecretLabs
    m___SecretLabs : string;
    // public DynamicVectorClass<BuildingClass *> PsychicDetectionBuildings
    m_PsychicDetectionBuildings : DynamicVectorClass<BuildingClass>;
    // public char[24] __PsychicDetectionBuildings
    m___PsychicDetectionBuildings : string;
    // public DynamicVectorClass<BuildingClass *> FactoryPlants
    m_FactoryPlants : DynamicVectorClass<BuildingClass>;
    // public char[24] __FactoryPlants
    m___FactoryPlants : string;
    // public DynamicVectorClass<StartingTechnoStruct *> StartingUnits
    m_StartingUnits : DynamicVectorClass<StartingTechnoStruct>;
    // public char[24] __StartingUnits
    m___StartingUnits : string;
    // public DynamicVectorClass<SuperClass *> Supers
    m_Supers : DynamicVectorClass<SuperClass>;
    // public char[24] __Supers
    m___Supers : string;
    // for AI
    // public CDTimerClass RepairTimer
    m_RepairTimer : CDTimerClass;
    // public char[12] __RepairTimer
    m___RepairTimer : string;
    // public CDTimerClass AlertTimer
    m_AlertTimer : CDTimerClass;
    // public char[12] __AlertTimer
    m___AlertTimer : string;
    // public CDTimerClass BorrowedTime
    m_BorrowedTime : CDTimerClass;
    // public char[12] __BorrowedTime
    m___BorrowedTime : string;
    // public CDTimerClass PowerBlackoutTimer
    m_PowerBlackoutTimer : CDTimerClass;
    // public char[12] __PowerBlackoutTimer
    m___PowerBlackoutTimer : string;
    // public CDTimerClass RadarBlackoutTimer
    m_RadarBlackoutTimer : CDTimerClass;
    // public char[12] __RadarBlackoutTimer
    m___RadarBlackoutTimer : string;
    // public StorageClass OwnedTiberium
    m_OwnedTiberium : StorageClass;
    // public char[16] __OwnedTiberium
    m___OwnedTiberium : string;
    // public StorageClass OwnedWeed
    m_OwnedWeed : StorageClass;
    // public char[16] __OwnedWeed
    m___OwnedWeed : string;
    // public UnitTrackerClass BuiltAircraftTypes
    m_BuiltAircraftTypes : UnitTrackerClass;
    // public char[2056] __BuiltAircraftTypes
    m___BuiltAircraftTypes : string;
    // public UnitTrackerClass BuiltInfantryTypes
    m_BuiltInfantryTypes : UnitTrackerClass;
    // public char[2056] __BuiltInfantryTypes
    m___BuiltInfantryTypes : string;
    // public UnitTrackerClass BuiltUnitTypes
    m_BuiltUnitTypes : UnitTrackerClass;
    // public char[2056] __BuiltUnitTypes
    m___BuiltUnitTypes : string;
    // public UnitTrackerClass BuiltBuildingTypes
    m_BuiltBuildingTypes : UnitTrackerClass;
    // public char[2056] __BuiltBuildingTypes
    m___BuiltBuildingTypes : string;
    // public UnitTrackerClass KilledAircraftTypes
    m_KilledAircraftTypes : UnitTrackerClass;
    // public char[2056] __KilledAircraftTypes
    m___KilledAircraftTypes : string;
    // public UnitTrackerClass KilledInfantryTypes
    m_KilledInfantryTypes : UnitTrackerClass;
    // public char[2056] __KilledInfantryTypes
    m___KilledInfantryTypes : string;
    // public UnitTrackerClass KilledUnitTypes
    m_KilledUnitTypes : UnitTrackerClass;
    // public char[2056] __KilledUnitTypes
    m___KilledUnitTypes : string;
    // public UnitTrackerClass KilledBuildingTypes
    m_KilledBuildingTypes : UnitTrackerClass;
    // public char[2056] __KilledBuildingTypes
    m___KilledBuildingTypes : string;
    // public UnitTrackerClass CapturedBuildings
    m_CapturedBuildings : UnitTrackerClass;
    // public char[2056] __CapturedBuildings
    m___CapturedBuildings : string;
    // YES, THIS IS HOW WW WASTES TONS OF RAM
    // public UnitTrackerClass CollectedCrates
    m_CollectedCrates : UnitTrackerClass;
    // public char[2056] __CollectedCrates
    m___CollectedCrates : string;
    // public ZoneInfoStruct[5] ZoneInfos
    m_ZoneInfos : ZoneInfoStruct;
    // public char[60] __ZoneInfos
    m___ZoneInfos : string;
    // Used for: Counting objects ever owned
    // altered on each object's loss or gain
    // BuildLimit > 0 validation uses this
    // public CounterClass OwnedBuildingTypes
    m_OwnedBuildingTypes : CounterClass;
    // public char[20] __OwnedBuildingTypes
    m___OwnedBuildingTypes : string;
    // public CounterClass OwnedUnitTypes
    m_OwnedUnitTypes : CounterClass;
    // public char[20] __OwnedUnitTypes
    m___OwnedUnitTypes : string;
    // public CounterClass OwnedInfantryTypes
    m_OwnedInfantryTypes : CounterClass;
    // public char[20] __OwnedInfantryTypes
    m___OwnedInfantryTypes : string;
    // public CounterClass OwnedAircraftTypes
    m_OwnedAircraftTypes : CounterClass;
    // public char[20] __OwnedAircraftTypes
    m___OwnedAircraftTypes : string;
    // Used for: Counting objects currently owned and on the map
    // altered on each object's loss or gain
    // AITriggerType condition uses this
    // original PrereqOverride check uses this
    // original Prerequisite check uses this
    // AuxBuilding check uses this
    // public CounterClass ActiveBuildingTypes
    m_ActiveBuildingTypes : CounterClass;
    // public char[20] __ActiveBuildingTypes
    m___ActiveBuildingTypes : string;
    // public CounterClass ActiveUnitTypes
    m_ActiveUnitTypes : CounterClass;
    // public char[20] __ActiveUnitTypes
    m___ActiveUnitTypes : string;
    // public CounterClass ActiveInfantryTypes
    m_ActiveInfantryTypes : CounterClass;
    // public char[20] __ActiveInfantryTypes
    m___ActiveInfantryTypes : string;
    // public CounterClass ActiveAircraftTypes
    m_ActiveAircraftTypes : CounterClass;
    // public char[20] __ActiveAircraftTypes
    m___ActiveAircraftTypes : string;
    // Used for: Counting objects produced from Factory
    // not altered when things get taken over or removed
    // BuildLimit 
    // <
    // 0 validation uses this
    // public CounterClass FactoryProducedBuildingTypes
    m_FactoryProducedBuildingTypes : CounterClass;
    // public char[20] __FactoryProducedBuildingTypes
    m___FactoryProducedBuildingTypes : string;
    // public CounterClass FactoryProducedUnitTypes
    m_FactoryProducedUnitTypes : CounterClass;
    // public char[20] __FactoryProducedUnitTypes
    m___FactoryProducedUnitTypes : string;
    // public CounterClass FactoryProducedInfantryTypes
    m_FactoryProducedInfantryTypes : CounterClass;
    // public char[20] __FactoryProducedInfantryTypes
    m___FactoryProducedInfantryTypes : string;
    // public CounterClass FactoryProducedAircraftTypes
    m_FactoryProducedAircraftTypes : CounterClass;
    // public char[20] __FactoryProducedAircraftTypes
    m___FactoryProducedAircraftTypes : string;
    // public CDTimerClass AttackTimer
    m_AttackTimer : CDTimerClass;
    // public char[12] __AttackTimer
    m___AttackTimer : string;
    // arghghghgh bugged
    // public DynamicVectorClass<AngerStruct> AngerNodes
    m_AngerNodes : DynamicVectorClass<AngerStruct>;
    // public char[24] __AngerNodes
    m___AngerNodes : string;
    // filled with data which is never used, jood gob WW
    // public DynamicVectorClass<ScoutStruct> ScoutNodes
    m_ScoutNodes : DynamicVectorClass<ScoutStruct>;
    // public char[24] __ScoutNodes
    m___ScoutNodes : string;
    // public CDTimerClass AITimer
    m_AITimer : CDTimerClass;
    // public char[12] __AITimer
    m___AITimer : string;
    // public CDTimerClass Unknown_Timer_5640
    m_Unknown_Timer_5640 : CDTimerClass;
    // public char[12] __Unknown_Timer_5640
    m___Unknown_Timer_5640 : string;
    // public DropshipStruct[3] DropshipData
    m_DropshipData : DropshipStruct;
    // public char[132] __DropshipData
    m___DropshipData : string;
    // //-> 32 players possible here
    // public CDTimerClass DamageDelayTimer
    m_DamageDelayTimer : CDTimerClass;
    // public char[12] __DamageDelayTimer
    m___DamageDelayTimer : string;
    // for AI attacks
    // public CDTimerClass TeamDelayTimer
    m_TeamDelayTimer : CDTimerClass;
    // public char[12] __TeamDelayTimer
    m___TeamDelayTimer : string;
    // public CDTimerClass TriggerDelayTimer
    m_TriggerDelayTimer : CDTimerClass;
    // public char[12] __TriggerDelayTimer
    m___TriggerDelayTimer : string;
    // public CDTimerClass SpeakAttackDelayTimer
    m_SpeakAttackDelayTimer : CDTimerClass;
    // public char[12] __SpeakAttackDelayTimer
    m___SpeakAttackDelayTimer : string;
    // public CDTimerClass SpeakPowerDelayTimer
    m_SpeakPowerDelayTimer : CDTimerClass;
    // public char[12] __SpeakPowerDelayTimer
    m___SpeakPowerDelayTimer : string;
    // public CDTimerClass SpeakMoneyDelayTimer
    m_SpeakMoneyDelayTimer : CDTimerClass;
    // public char[12] __SpeakMoneyDelayTimer
    m___SpeakMoneyDelayTimer : string;
    // public CDTimerClass SpeakMaxedDelayTimer
    m_SpeakMaxedDelayTimer : CDTimerClass;
    // public char[12] __SpeakMaxedDelayTimer
    m___SpeakMaxedDelayTimer : string;
    // public int StartingPoint
    m_StartingPoint : number;
    // Could it really be a CellStruct ? - Saved for backwards compatibility
    // public CellStruct StartingCell
    m_StartingCell : CellStruct;
    // public DynamicVectorClass<IConnectionPoint *> WaypointPath
    m_WaypointPath : DynamicVectorClass<any>;
    // public char[24] __WaypointPath
    m___WaypointPath : string;
}
// StorageClass
class StorageClass
{
    // public float GetAmount(int index) const
    GetAmount(index_0 : number) : number;
    // public float GetTotalAmount() const
    GetTotalAmount() : number;
    // public float AddAmount(float amount, int index)
    AddAmount(amount_0 : number, index_1 : number) : number;
    // public float RemoveAmount(float amount, int index)
    RemoveAmount(amount_0 : number, index_1 : number) : number;
    // public int GetTotalValue() const
    GetTotalValue() : number;
    // public float Tiberium1
    m_Tiberium1 : number;
    // public float Tiberium2
    m_Tiberium2 : number;
    // public float Tiberium3
    m_Tiberium3 : number;
    // public float Tiberium4
    m_Tiberium4 : number;
}
// The AbstractClass is the base class of all game objects.
// AbstractClass
class AbstractClass
{
    // public char const * GetRTTIName() const
    GetRTTIName() : string;
    // public static char const * GetRTTIName(AbstractType abs)
    static GetRTTIName(abs_0 : AbstractType) : string;
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID) = 0
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long IsDirty()
    IsDirty() : number;
    // public virtual long Load(IStream * pStm) = 0
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty) = 0
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // public virtual long GetSizeMax(_ULARGE_INTEGER * pcbSize)
    GetSizeMax(pcbSize_0 : any | any) : number;
    // IRTTITypeInfo
    // public virtual AbstractType What_Am_I() const
    What_Am_I() : AbstractType;
    // public virtual int Fetch_ID() const
    Fetch_ID() : number;
    // public virtual void Create_ID()
    Create_ID() : void;
    // INoticeSink
    // public virtual bool INoticeSink_Unknown(unsigned long dwUnknown)
    INoticeSink_Unknown(dwUnknown_0 : number | any) : boolean;
    // INoticeSource
    // public virtual void INoticeSource_Unknown()
    INoticeSource_Unknown() : void;
    // AbstractClass
    // public virtual void Init()
    Init() : void;
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    // public virtual AbstractType WhatAmI() const = 0
    WhatAmI() : AbstractType;
    // public virtual int Size() const = 0
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any) : void;
    // public virtual int GetOwningHouseIndex() const
    GetOwningHouseIndex() : number;
    // public virtual HouseClass * GetOwningHouse() const
    GetOwningHouse() : HouseClass;
    // public virtual int GetArrayIndex() const
    GetArrayIndex() : number;
    // public virtual bool IsDead() const
    IsDead() : boolean;
    // public virtual CoordStruct * GetCoords(CoordStruct * pCrd) const
    GetCoords(pCrd_0 : CoordStruct) : CoordStruct;
    // public virtual CoordStruct * GetDestination(CoordStruct * pCrd, TechnoClass * pDocker = nullptr) const
    GetDestination(pCrd_0 : CoordStruct, pDocker_1 : TechnoClass) : CoordStruct;
    // public virtual bool IsOnFloor() const
    IsOnFloor() : boolean;
    // public virtual bool IsInAir() const
    IsInAir() : boolean;
    // public virtual CoordStruct * GetCenterCoords(CoordStruct * pCrd) const
    GetCenterCoords(pCrd_0 : CoordStruct) : CoordStruct;
    // public virtual void Update()
    Update() : void;
    // non-virtual
    // public static void AnnounceExpiredPointer(AbstractClass * pAbstract, bool removed = true)
    static AnnounceExpiredPointer(pAbstract_0 : AbstractClass, removed_1 : boolean) : void;
    // public static void RemoveAllInactive()
    static RemoveAllInactive() : void;
    // public void AnnounceExpiredPointer(bool removed = true)
    AnnounceExpiredPointer(removed_0 : boolean) : void;
    // public CoordStruct GetCoords() const
    GetCoords() : CoordStruct;
    // public CoordStruct GetDestination(TechnoClass * pDocker = nullptr) const
    GetDestination(pDocker_0 : TechnoClass) : CoordStruct;
    // public CoordStruct GetCenterCoords() const
    GetCenterCoords() : CoordStruct;
    // public DirStruct * GetTargetDirection(DirStruct * pDir, AbstractClass * pTarget) const
    GetTargetDirection(pDir_0 : DirStruct, pTarget_1 : AbstractClass) : DirStruct;
    // public DirStruct GetTargetDirection(AbstractClass * pTarget) const
    GetTargetDirection(pTarget_0 : AbstractClass) : DirStruct;
    // public int DistanceFrom(AbstractClass * that) const
    DistanceFrom(that_0 : AbstractClass) : number;
    // public int DistanceFrom3D(AbstractClass * that) const
    DistanceFrom3D(that_0 : AbstractClass) : number;
    // Operators
    // public bool operator<(AbstractClass const& rhs) const
    op_LessThan(rhs_0 : AbstractClass) : boolean;
    // skip operator new
    // skip operator delete
    // public static AbstractType const AbsID = AbstractType::Abstract
    static s_AbsID : AbstractType;
    // public static constant_ptr<DynamicVectorClass<AbstractClass *>, 11597600> const Array = 0xB0F720u
    static s_Array : DynamicVectorClass<AbstractClass>;
    // public static reference<IndexClass<int, int>, 11593792, 0> const TargetIndex = 0xB0E840u
    static s_TargetIndex : any;
    // generated by IRTTIInfo::Create_ID through an amazingly simple sequence of return ++ScenarioClass::Instance->UniqueID;
    // public unsigned long UniqueID
    m_UniqueID : number;
    // flags, see AbstractFlags enum in GeneralDefinitions.
    // public AbstractFlags AbstractFlags
    m_AbstractFlags : AbstractFlags;
    // public unsigned long unknown_18
    m_unknown_18 : number;
    // public long RefCount
    m_RefCount : number;
    // for IPersistStream.
    // public bool Dirty
    m_Dirty : boolean;
}
// forward declarations
// ObjectClass
class ObjectClass
    extends AbstractClass
{
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // AbstractClass
    // public virtual bool IsOnFloor() const
    IsOnFloor() : boolean;
    // public virtual bool IsInAir() const
    IsInAir() : boolean;
    // ObjectClass
    // public virtual void AnimPointerExpired(AnimClass * pAnim)
    AnimPointerExpired(pAnim_0 : AnimClass) : void;
    // public virtual bool IsSelectable() const
    IsSelectable() : boolean;
    // public virtual VisualType VisualCharacter(short SpecificOwner, HouseClass * WhoIsAsking) const
    VisualCharacter(SpecificOwner_0 : number, WhoIsAsking_1 : HouseClass) : VisualType;
    // public virtual SHPStruct * GetImage() const
    GetImage() : any;
    // public virtual Action MouseOverCell(CellStruct const * pCell, bool checkFog = false, bool ignoreForce = false) const
    MouseOverCell(pCell_0 : CellStruct, checkFog_1 : boolean, ignoreForce_2 : boolean) : Action;
    // public virtual Action MouseOverObject(ObjectClass const * pObject, bool ignoreForce = false) const
    MouseOverObject(pObject_0 : ObjectClass, ignoreForce_1 : boolean) : Action;
    // public virtual Layer InWhichLayer() const
    InWhichLayer() : Layer;
    // public virtual bool IsSurfaced()
    IsSurfaced() : boolean;
    // Building returns if it is 1x1 and has UndeploysInto
    // inf returns 0
    // unit returns !NonVehicle
    // Aircraft returns IsOnFloor()
    // users include:
    // 452656 - is this building click-repairable
    // 440C26 - should this building get considered in BaseSpacing
    // 445A8E - -""-
    // 51E7D1 - can a VehicleThief be clicked to steal this unit
    // 51E4D9 - can an engi be clicked to enter this to fix/takeover
    // 51F0D3 - -""-
    // 51EA06 - can this building be C4'd?
    // 51E243 - can a VehicleThief steal this on his own decision
    // 4F93F3 - should this building's damage raise a BaseUnderAttack?
    // 442286 - -""-
    // 44296A - -""-
    // 741117 - can this be healed by a vehicle?
    // 6F8242 - can this aircraft be auto-target
    // 6F85BE - can this aircraft be auto-attacked
    // public virtual bool IsStrange() const
    IsStrange() : boolean;
    // public virtual TechnoTypeClass * GetTechnoType() const
    GetTechnoType() : TechnoTypeClass;
    // public virtual ObjectTypeClass * GetType() const
    GetType() : ObjectTypeClass;
    // public virtual unsigned long GetTypeOwners() const
    GetTypeOwners() : number;
    // public virtual wchar_t const * GetUIName() const
    GetUIName() : number;
    // public virtual bool CanBeRepaired() const
    CanBeRepaired() : boolean;
    // public virtual bool CanBeSold() const
    CanBeSold() : boolean;
    // public virtual bool IsActive() const
    IsActive() : boolean;
    // can the current player control this unit? (owned by him, not paralyzed, not spawned, not warping, not slaved...)
    // public virtual bool IsControllable() const
    IsControllable() : boolean;
    // On non-buildings this is same as GetCenterCoord(), on buildings it returns the target coordinate that is affected by TargetCoordOffset.
    // public virtual CoordStruct * GetTargetCoords(CoordStruct * pCrd) const
    GetTargetCoords(pCrd_0 : CoordStruct) : CoordStruct;
    // gets a building's free dock coordinates for a unit. falls back to this->GetCoords(pCrd);
    // public virtual CoordStruct * GetDockCoords(CoordStruct * pCrd, TechnoClass * docker) const
    GetDockCoords(pCrd_0 : CoordStruct, docker_1 : TechnoClass) : CoordStruct;
    // public virtual CoordStruct * GetRenderCoords(CoordStruct * pCrd) const
    GetRenderCoords(pCrd_0 : CoordStruct) : CoordStruct;
    // public virtual CoordStruct * GetFLH(CoordStruct * pDest, int idxWeapon, CoordStruct BaseCoords) const
    GetFLH(pDest_0 : CoordStruct, idxWeapon_1 : number, BaseCoords_2 : CoordStruct) : CoordStruct;
    // public virtual CoordStruct * GetExitCoords(CoordStruct * pCrd, unsigned long dwUnk) const
    GetExitCoords(pCrd_0 : CoordStruct, dwUnk_1 : number) : CoordStruct;
    // public virtual int GetYSort() const
    GetYSort() : number;
    // public virtual bool IsOnBridge(TechnoClass * pDocker = nullptr) const
    IsOnBridge(pDocker_0 : TechnoClass) : boolean;
    // public virtual bool IsStandingStill() const
    IsStandingStill() : boolean;
    // public virtual bool IsDisguised() const
    IsDisguised() : boolean;
    // public virtual bool IsDisguisedAs(HouseClass * target) const
    IsDisguisedAs(target_0 : HouseClass) : boolean;
    // public virtual ObjectTypeClass * GetDisguise(bool DisguisedAgainstAllies) const
    GetDisguise(DisguisedAgainstAllies_0 : boolean) : ObjectTypeClass;
    // public virtual HouseClass * GetDisguiseHouse(bool DisguisedAgainstAllies) const
    GetDisguiseHouse(DisguisedAgainstAllies_0 : boolean) : HouseClass;
    // remove object from the map
    // public virtual bool Limbo()
    Limbo() : boolean;
    // place the object on the map
    // public virtual bool Unlimbo(CoordStruct const& Crd, DirType dFaceDir)
    Unlimbo(Crd_0 : CoordStruct, dFaceDir_1 : DirType) : boolean;
    // cleanup things (lose line trail, deselect, etc). Permanently: destroyed/removed/gone opposed to just going out of sight.
    // public virtual void Disappear(bool permanently)
    Disappear(permanently_0 : boolean) : void;
    // public virtual void RegisterDestruction(TechnoClass * Destroyer)
    RegisterDestruction(Destroyer_0 : TechnoClass) : void;
    // maybe Object instead of Techno? Raises Map Events, grants veterancy, increments house kill counters
    // public virtual void RegisterKill(HouseClass * Destroyer)
    RegisterKill(Destroyer_0 : HouseClass) : void;
    // public virtual bool SpawnParachuted(CoordStruct const& coords)
    SpawnParachuted(coords_0 : CoordStruct) : boolean;
    // public virtual void DropAsBomb()
    DropAsBomb() : void;
    // public virtual void MarkAllOccupationBits(CoordStruct const& coords)
    MarkAllOccupationBits(coords_0 : CoordStruct) : void;
    // public virtual void UnmarkAllOccupationBits(CoordStruct const& coords)
    UnmarkAllOccupationBits(coords_0 : CoordStruct) : void;
    // public virtual void UnInit()
    UnInit() : void;
    // public virtual void Reveal()
    Reveal() : void;
    // public virtual KickOutResult KickOutUnit(TechnoClass * pTechno, CellStruct Cell)
    KickOutUnit(pTechno_0 : TechnoClass, Cell_1 : CellStruct) : KickOutResult;
    // public virtual bool DrawIfVisible(RectangleStruct * pBounds, bool EvenIfCloaked, unsigned long dwUnk3) const
    DrawIfVisible(pBounds_0 : RectangleStruct, EvenIfCloaked_1 : boolean, dwUnk3_2 : number) : boolean;
    // public virtual CellStruct const * GetFoundationData(bool includeBib = false) const
    GetFoundationData(includeBib_0 : boolean) : CellStruct;
    // public virtual void DrawBehind(Point2D * pLocation, RectangleStruct * pBounds) const
    DrawBehind(pLocation_0 : Point2D, pBounds_1 : RectangleStruct) : void;
    // public virtual void DrawExtras(Point2D * pLocation, RectangleStruct * pBounds) const
    DrawExtras(pLocation_0 : Point2D, pBounds_1 : RectangleStruct) : void;
    // public virtual void DrawIt(Point2D * pLocation, RectangleStruct * pBounds) const
    DrawIt(pLocation_0 : Point2D, pBounds_1 : RectangleStruct) : void;
    // public virtual void DrawAgain(Point2D const& location, RectangleStruct const& bounds) const
    DrawAgain(location_0 : Point2D, bounds_1 : RectangleStruct) : void;
    // public virtual void Undiscover()
    Undiscover() : void;
    // public virtual void See(unsigned long dwUnk, unsigned long dwUnk2)
    See(dwUnk_0 : number, dwUnk2_1 : number) : void;
    // public virtual bool Mark(MarkType value)
    Mark(value_0 : MarkType) : boolean;
    // public virtual RectangleStruct * GetDimensions(RectangleStruct * pRect) const
    GetDimensions(pRect_0 : RectangleStruct) : RectangleStruct;
    // public virtual RectangleStruct * GetRenderDimensions(RectangleStruct * pRect)
    GetRenderDimensions(pRect_0 : RectangleStruct) : RectangleStruct;
    // public virtual void DrawRadialIndicator(unsigned long dwUnk)
    DrawRadialIndicator(dwUnk_0 : number) : void;
    // public virtual void MarkForRedraw()
    MarkForRedraw() : void;
    // public virtual bool CanBeSelected() const
    CanBeSelected() : boolean;
    // public virtual bool CanBeSelectedNow() const
    CanBeSelectedNow() : boolean;
    // public virtual bool CellClickedAction(Action action, CellStruct * pCell, CellStruct * pCell1, bool bUnk)
    CellClickedAction(action_0 : Action, pCell_1 : CellStruct, pCell1_2 : CellStruct, bUnk_3 : boolean) : boolean;
    // public virtual bool ObjectClickedAction(Action action, ObjectClass * pTarget, bool bUnk)
    ObjectClickedAction(action_0 : Action, pTarget_1 : ObjectClass, bUnk_2 : boolean) : boolean;
    // public virtual void Flash(int Duration)
    Flash(Duration_0 : number) : void;
    // public virtual bool Select()
    Select() : boolean;
    // public virtual void Deselect()
    Deselect() : void;
    // public virtual DamageState IronCurtain(int nDuration, HouseClass * pSource, bool ForceShield)
    IronCurtain(nDuration_0 : number, pSource_1 : HouseClass, ForceShield_2 : boolean) : DamageState;
    // public virtual void StopAirstrikeTimer()
    StopAirstrikeTimer() : void;
    // public virtual void StartAirstrikeTimer(int Duration)
    StartAirstrikeTimer(Duration_0 : number) : void;
    // public virtual bool IsIronCurtained() const
    IsIronCurtained() : boolean;
    // public virtual bool IsCloseEnough3D(unsigned long dwUnk, unsigned long dwUnk2) const
    IsCloseEnough3D(dwUnk_0 : number, dwUnk2_1 : number) : boolean;
    // public virtual int GetWeaponRange(int idxWeapon) const
    GetWeaponRange(idxWeapon_0 : number) : number;
    // public virtual DamageState ReceiveDamage(int * pDamage, int DistanceFromEpicenter, WarheadTypeClass * pWH, ObjectClass * Attacker, bool IgnoreDefenses, bool PreventPassengerEscape, HouseClass * pAttackingHouse)
    ReceiveDamage(pDamage_0 : number, DistanceFromEpicenter_1 : number, pWH_2 : WarheadTypeClass, Attacker_3 : ObjectClass, IgnoreDefenses_4 : boolean, PreventPassengerEscape_5 : boolean, pAttackingHouse_6 : HouseClass) : DamageState;
    // public virtual void Destroy()
    Destroy() : void;
    // public virtual void Scatter(CoordStruct const& crd, bool ignoreMission, bool ignoreDestination)
    Scatter(crd_0 : CoordStruct, ignoreMission_1 : boolean, ignoreDestination_2 : boolean) : void;
    // public virtual bool Ignite()
    Ignite() : boolean;
    // public virtual void Extinguish()
    Extinguish() : void;
    // public virtual unsigned long GetPointsValue() const
    GetPointsValue() : number;
    // public virtual Mission GetCurrentMission() const
    GetCurrentMission() : Mission;
    // public virtual void RestoreMission(Mission mission)
    RestoreMission(mission_0 : Mission) : void;
    // public virtual void UpdatePosition(PCPType how)
    UpdatePosition(how_0 : PCPType) : void;
    // public virtual BuildingClass * FindFactory(bool allowOccupied, bool requirePower) const
    FindFactory(allowOccupied_0 : boolean, requirePower_1 : boolean) : BuildingClass;
    // public virtual RadioCommand ReceiveCommand(TechnoClass * pSender, RadioCommand command, AbstractClass *& pInOut)
    ReceiveCommand(pSender_0 : TechnoClass, command_1 : RadioCommand, pInOut_2 : AbstractClass) : RadioCommand;
    // public virtual bool DiscoveredBy(HouseClass * pHouse)
    DiscoveredBy(pHouse_0 : HouseClass) : boolean;
    // public virtual void SetRepairState(int state)
    SetRepairState(state_0 : number) : void;
    // public virtual void Sell(unsigned long dwUnk)
    Sell(dwUnk_0 : number) : void;
    // public virtual void AssignPlanningPath(int idxPath, char idxWP)
    AssignPlanningPath(idxPath_0 : number, idxWP_1 : number) : void;
    // public virtual void MoveToDirection(FacingType facing)
    MoveToDirection(facing_0 : FacingType) : void;
    // public virtual Move IsCellOccupied(CellClass * pDestCell, FacingType facing, int level, CellClass * pSourceCell, bool alt) const
    IsCellOccupied(pDestCell_0 : CellClass, facing_1 : FacingType, level_2 : number, pSourceCell_3 : CellClass, alt_4 : boolean) : Move;
    // public virtual unsigned long vt_entry_1B0(unsigned long dwUnk, unsigned long dwUnk2, unsigned long dwUnk3, unsigned long dwUnk4, unsigned long dwUnk5)
    vt_entry_1B0(dwUnk_0 : number, dwUnk2_1 : number, dwUnk3_2 : number, dwUnk4_3 : number, dwUnk5_4 : number) : number;
    // public virtual void SetLocation(CoordStruct const& crd)
    SetLocation(crd_0 : CoordStruct) : void;
    // these two work through the object's Location
    // public virtual CellStruct * GetMapCoords(CellStruct * pUCell) const
    GetMapCoords(pUCell_0 : CellStruct) : CellStruct;
    // public virtual CellClass * GetCell() const
    GetCell() : CellClass;
    // these two call ::GetCoords_() instead
    // public virtual CellStruct * GetMapCoordsAgain(CellStruct * pUCell) const
    GetMapCoordsAgain(pUCell_0 : CellStruct) : CellStruct;
    // public virtual CellClass * GetCellAgain() const
    GetCellAgain() : CellClass;
    // public virtual int GetHeight() const
    GetHeight() : number;
    // public virtual void SetHeight(unsigned long dwUnk)
    SetHeight(dwUnk_0 : number) : void;
    // public virtual int GetZ() const
    GetZ() : number;
    // public virtual bool IsBeingWarpedOut() const
    IsBeingWarpedOut() : boolean;
    // public virtual bool IsWarpingIn() const
    IsWarpingIn() : boolean;
    // public virtual bool IsWarpingSomethingOut() const
    IsWarpingSomethingOut() : boolean;
    // public virtual bool IsNotWarping() const
    IsNotWarping() : boolean;
    // public virtual LightConvertClass * GetRemapColour() const
    GetRemapColour() : LightConvertClass;
    // technically it takes an ecx
    // <this
    // > , but it's not used and ecx is immediately overwritten on entry
    // draws the mind control line when unit is selected
    // public static void DrawALinkTo(int src_X, int src_Y, int src_Z, int dst_X, int dst_Y, int dst_Z, ColorStruct color)
    static DrawALinkTo(src_X_0 : number, src_Y_1 : number, src_Z_2 : number, dst_X_3 : number, dst_Y_4 : number, dst_Z_5 : number, color_6 : ColorStruct) : void;
    // public double GetHealthPercentage() const
    GetHealthPercentage() : number;
    // public void SetHealthPercentage(double percentage)
    SetHealthPercentage(percentage_0 : number) : void;
    // public bool IsRedHP() const
    IsRedHP() : boolean;
    // public bool IsYellowHP() const
    IsYellowHP() : boolean;
    // public bool IsGreenHP() const
    IsGreenHP() : boolean;
    // public HealthState GetHealthStatus() const
    GetHealthStatus() : HealthState;
    // public bool AttachTrigger(TagClass * pTag)
    AttachTrigger(pTag_0 : TagClass) : boolean;
    // public void BecomeUntargetable()
    BecomeUntargetable() : void;
    // public void ReplaceTag(TagClass * pTag)
    ReplaceTag(pTag_0 : TagClass) : void;
    // public int GetCellLevel() const
    GetCellLevel() : number;
    // public bool IsCrushable(TechnoClass * pCrusher)
    IsCrushable(pCrusher_0 : TechnoClass) : boolean;
    // public CellStruct GetMapCoords() const
    GetMapCoords() : CellStruct;
    // public CellStruct GetMapCoordsAgain() const
    GetMapCoordsAgain() : CellStruct;
    // On non-buildings this is same as GetCenterCoord(), on buildings it returns the target coordinate that is affected by TargetCoordOffset.
    // public CoordStruct GetTargetCoords() const
    GetTargetCoords() : CoordStruct;
    // public CoordStruct GetRenderCoords() const
    GetRenderCoords() : CoordStruct;
    // public CoordStruct GetFLH(int idxWeapon, CoordStruct const& base) const
    GetFLH(idxWeapon_0 : number, base_1 : CoordStruct) : CoordStruct;
    // public static AbstractFlags const AbsDerivateID = AbstractFlags::Object
    static s_AbsDerivateID : AbstractFlags;
    // global arrays
    // public static reference<DynamicVectorClass<ObjectClass *>, 11070648, 0> const CurrentObjects = 0xA8ECB8u
    static s_CurrentObjects : DynamicVectorClass<ObjectClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public unsigned long unknown_24
    m_unknown_24 : number;
    // public unsigned long unknown_28
    m_unknown_28 : number;
    // how fast is it falling down? only works if FallingDown is set below, and actually positive numbers will move the thing UPWARDS
    // public int FallRate
    m_FallRate : number;
    // Next Object in the same cell or transport. This is a linked list of Objects.
    // public ObjectClass * NextObject
    m_NextObject : ObjectClass;
    // Should be TagClass , TODO: change when implemented
    // public TagClass * AttachedTag
    m_AttachedTag : TagClass;
    // Ivan's little friends.
    // public BombClass * AttachedBomb
    m_AttachedBomb : BombClass;
    // public int CustomSound
    m_CustomSound : number;
    // In range of player's bomb seeing units, so should draw it
    // public bool BombVisible
    m_BombVisible : boolean;
    // The current Health.
    // public int Health
    m_Health : number;
    // used for auto-targeting threat estimation
    // public int EstimatedHealth
    m_EstimatedHealth : number;
    // has this object been placed on the map?
    // public bool IsOnMap
    m_IsOnMap : boolean;
    // public unsigned long unknown_78
    m_unknown_78 : number;
    // public unsigned long unknown_7C
    m_unknown_7C : number;
    // public bool NeedsRedraw
    m_NeedsRedraw : boolean;
    // act as if it doesn't exist - e.g., post mortem state before being deleted
    // public bool InLimbo
    m_InLimbo : boolean;
    // public bool InOpenToppedTransport
    m_InOpenToppedTransport : boolean;
    // Has the player selected this Object?
    // public bool IsSelected
    m_IsSelected : boolean;
    // Is this Object parachuting?
    // public bool HasParachute
    m_HasParachute : boolean;
    // Current parachute Anim.
    // public AnimClass * Parachute
    m_Parachute : AnimClass;
    // public bool OnBridge
    m_OnBridge : boolean;
    // public bool IsFallingDown
    m_IsFallingDown : boolean;
    // last falling state when FootClass::Update executed. used to find out whether it changed.
    // public bool WasFallingDown
    m_WasFallingDown : boolean;
    // if set, will explode after FallingDown brings it to contact with the ground
    // public bool IsABomb
    m_IsABomb : boolean;
    // Self-explanatory.
    // public bool IsAlive
    m_IsAlive : boolean;
    // public Layer LastLayer
    m_LastLayer : Layer;
    // has this object been added to the logic collection?
    // public bool IsInLogic
    m_IsInLogic : boolean;
    // was this object in viewport when drawn?
    // public bool IsVisible
    m_IsVisible : boolean;
    // Absolute current 3D location (in leptons)
    // public CoordStruct Location
    m_Location : CoordStruct;
    // public LineTrail * LineTrailer
    m_LineTrailer : LineTrail;
    // the "mofo" struct, evil evil stuff
    // public AudioController AmbientSoundController
    m_AmbientSoundController : any;
    // public char[20] __AmbientSoundController
    m___AmbientSoundController : string;
    // the "mofo" struct, evil evil stuff
    // public AudioController CustomSoundController
    m_CustomSoundController : any;
    // public char[20] __CustomSoundController
    m___CustomSoundController : string;
}
// forward declarations
// AnimClass
class AnimClass
    extends ObjectClass
{
    // Constructor
    // TODO fix
    // public AnimClass(AnimTypeClass * pAnimType, CoordStruct const& Location, int LoopDelay = 0, int LoopCount = 1, unsigned long flags = 0x600, int ForceZAdjust = 0, bool reverse = false)
    constructor(pAnimType_0 : AnimTypeClass, Location_1 : CoordStruct, LoopDelay_2 : number, LoopCount_3 : number, flags_4 : number, ForceZAdjust_5 : number, reverse_6 : boolean);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool detachFromAll)
    PointerExpired(pAbstract_0 : AbstractClass | any, detachFromAll_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectClass
    // AnimClass
    // public virtual int AnimExtras()
    AnimExtras() : number;
    // public virtual int GetEnd() const
    GetEnd() : number;
    // public void SetOwnerObject(ObjectClass * pOwner)
    SetOwnerObject(pOwner_0 : ObjectClass) : void;
    // public void Pause()
    Pause() : void;
    // public void Unpause()
    Unpause() : void;
    // Anim start logic: sound event handling, tiberium chain reaction etc.
    // public void Start() const
    Start() : void;
    // Anim midpoint logic: particle spawning, smudges etc.
    // public bool Middle() const
    Middle() : boolean;
    // public static AbstractType const AbsID = AbstractType::Anim
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<AnimClass *>, 11069864> const Array = 0xA8E9A8u
    static s_Array : DynamicVectorClass<AnimClass>;
    // The AnimType.
    // public AnimTypeClass * Type
    m_Type : AnimTypeClass;
    // set by AnimClass::SetOwnerObject (0x424B50)
    // public ObjectClass * OwnerObject
    m_OwnerObject : ObjectClass;
    // public unsigned long unknown_D0
    m_unknown_D0 : number;
    // Palette?
    // public LightConvertClass * LightConvert
    m_LightConvert : LightConvertClass;
    // assert( (*ColorScheme::Array)[this->LightConvertIndex] == this->LightConvert ;
    // public int LightConvertIndex
    m_LightConvertIndex : number;
    // filename set for destroy anims
    // public char[32] PaletteName
    m_PaletteName : string;
    // public int TintColor
    m_TintColor : number;
    // public int ZAdjust
    m_ZAdjust : number;
    // same as YSortAdjust from Type
    // public int YSortAdjust
    m_YSortAdjust : number;
    // the destination the anim tries to reach
    // public CoordStruct FlamingGuyCoords
    m_FlamingGuyCoords : CoordStruct;
    // number of failed attemts to reach water. the random destination generator stops if >= 7
    // public int FlamingGuyRetries
    m_FlamingGuyRetries : number;
    // whether this anim will invalidate on buildings, and whether it's tintable
    // public bool IsBuildingAnim
    m_IsBuildingAnim : boolean;
    // temporal'd building's active anims
    // public bool UnderTemporal
    m_UnderTemporal : boolean;
    // if paused, does not advance anim, does not deliver damage
    // public bool Paused
    m_Paused : boolean;
    // set when unpaused
    // public bool Unpaused
    m_Unpaused : boolean;
    // the animation value when paused
    // public int PausedAnimFrame
    m_PausedAnimFrame : number;
    // anim is forced to be played from end to start
    // public bool Reverse
    m_Reverse : boolean;
    // public unsigned long unknown_124
    m_unknown_124 : number;
    // on a scale of 1 - 100
    // public unsigned char TranslucencyLevel
    m_TranslucencyLevel : number;
    // or something to that effect, set just before UnInit
    // public bool TimeToDie
    m_TimeToDie : boolean;
    // public BulletClass * AttachedBullet
    m_AttachedBullet : BulletClass;
    // Used for remap (AltPalette).
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // randomized value, depending on RandomLoopDelay
    // public int LoopDelay
    m_LoopDelay : number;
    // Stores accumulated fractional animation damage and gets added to Type->Damage if at least 1.0 or above. Defaults to 1.0.
    // public double Accum
    m_Accum : number;
    // argument that's 0x600 most of the time
    // public BlitterFlags AnimFlags
    m_AnimFlags : BlitterFlags;
    // enables IsMeteor and Bouncer special behavior (AnimExtras)
    // public bool HasExtras
    m_HasExtras : boolean;
    // defaulted to deleteAfterIterations, when reaches zero, UnInit() is called
    // public unsigned char RemainingIterations
    m_RemainingIterations : number;
    // public unsigned char unknown_196
    m_unknown_196 : number;
    // public unsigned char unknown_197
    m_unknown_197 : number;
    // Not official name, only set to true on TActionClass-created animations and prevents sounds, damage and TiberiumChainReaction from working.
    // public bool IsInert
    m_IsInert : boolean;
    // public bool IsFogged
    m_IsFogged : boolean;
    // finish animation and remove
    // public bool FlamingGuyExpire
    m_FlamingGuyExpire : boolean;
    // set when something prevents the anim from going on: cell occupied, veins destoyed or unit gone, ...
    // public bool UnableToContinue
    m_UnableToContinue : boolean;
    // set in constructor, cleared during Update. skips damage, veins, tiberium chain reaction and animation progress
    // public bool SkipProcessOnce
    m_SkipProcessOnce : boolean;
    // don't draw, but Update state anyway
    // public bool Invisible
    m_Invisible : boolean;
    // powered animation has no power
    // public bool PowerOff
    m_PowerOff : boolean;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public StageClass Animation
    m_Animation : StageClass;
    // public char[28] __Animation
    m___Animation : string;
    // public BounceClass Bounce
    m_Bounce : BounceClass;
    // public char[80] __Bounce
    m___Bounce : string;
    // public AudioController Audio3
    m_Audio3 : any;
    // public char[20] __Audio3
    m___Audio3 : string;
    // public AudioController Audio4
    m_Audio4 : any;
    // public char[20] __Audio4
    m___Audio4 : string;
}
// forward declarations
// AnimTypeClass
class AnimTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public AnimTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static AnimTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : AnimTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static AnimTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : AnimTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // AnimTypeClass
    // public virtual SHPStruct * LoadImageA()
    LoadImageA() : any;
    // public virtual void Load2DArt()
    Load2DArt() : void;
    // public static AbstractType const AbsID = AbstractType::AnimType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<AnimTypeClass *>, 9126224> const Array = 0x8B4150u
    static s_Array : DynamicVectorClass<AnimTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public int MiddleFrameIndex
    m_MiddleFrameIndex : number;
    // public int MiddleFrameWidth
    m_MiddleFrameWidth : number;
    // public int MiddleFrameHeight
    m_MiddleFrameHeight : number;
    // public unsigned char unknown_2A4
    m_unknown_2A4 : number;
    // public double Damage
    m_Damage : number;
    // public int Rate
    m_Rate : number;
    // public int Start
    m_Start : number;
    // public int LoopStart
    m_LoopStart : number;
    // public int LoopEnd
    m_LoopEnd : number;
    // public int End
    m_End : number;
    // public int LoopCount
    m_LoopCount : number;
    // public AnimTypeClass * Next
    m_Next : AnimTypeClass;
    // index of that ParticleTypeClass
    // public int SpawnsParticle
    m_SpawnsParticle : number;
    // public int NumParticles
    m_NumParticles : number;
    // public int DetailLevel
    m_DetailLevel : number;
    // public int TranslucencyDetailLevel
    m_TranslucencyDetailLevel : number;
    // public RandomStruct RandomLoopDelay
    m_RandomLoopDelay : RandomStruct;
    // public RandomStruct RandomRate
    m_RandomRate : RandomStruct;
    // public int Translucency
    m_Translucency : number;
    // public AnimTypeClass * Spawns
    m_Spawns : AnimTypeClass;
    // public int SpawnCount
    m_SpawnCount : number;
    // VocClass index
    // public int Report
    m_Report : number;
    // VocClass index
    // public int StopSound
    m_StopSound : number;
    // public AnimTypeClass * BounceAnim
    m_BounceAnim : AnimTypeClass;
    // public AnimTypeClass * ExpireAnim
    m_ExpireAnim : AnimTypeClass;
    // public AnimTypeClass * TrailerAnim
    m_TrailerAnim : AnimTypeClass;
    // MISTYPE BY WESTWOOD!
    // public int TrailerSeperation
    m_TrailerSeperation : number;
    // public double Elasticity
    m_Elasticity : number;
    // public double MinZVel
    m_MinZVel : number;
    // public double unknown_double_320
    m_unknown_double_320 : number;
    // public double MaxXYVel
    m_MaxXYVel : number;
    // public WarheadTypeClass * Warhead
    m_Warhead : WarheadTypeClass;
    // public int DamageRadius
    m_DamageRadius : number;
    // public OverlayTypeClass * TiberiumSpawnType
    m_TiberiumSpawnType : OverlayTypeClass;
    // public int TiberiumSpreadRadius
    m_TiberiumSpreadRadius : number;
    // public int YSortAdjust
    m_YSortAdjust : number;
    // public int YDrawOffset
    m_YDrawOffset : number;
    // public int ZAdjust
    m_ZAdjust : number;
    // public int MakeInfantry
    m_MakeInfantry : number;
    // public int RunningFrames
    m_RunningFrames : number;
    // public bool IsFlamingGuy
    m_IsFlamingGuy : boolean;
    // public bool IsVeins
    m_IsVeins : boolean;
    // public bool IsMeteor
    m_IsMeteor : boolean;
    // public bool TiberiumChainReaction
    m_TiberiumChainReaction : boolean;
    // public bool IsTiberium
    m_IsTiberium : boolean;
    // public bool HideIfNoOre
    m_HideIfNoOre : boolean;
    // public bool Bouncer
    m_Bouncer : boolean;
    // public bool Tiled
    m_Tiled : boolean;
    // public bool ShouldUseCellDrawer
    m_ShouldUseCellDrawer : boolean;
    // public bool UseNormalLight
    m_UseNormalLight : boolean;
    // not loaded from ini anymore
    // public bool DemandLoad
    m_DemandLoad : boolean;
    // not loaded from ini anymore
    // public bool FreeLoad
    m_FreeLoad : boolean;
    // public bool IsAnimatedTiberium
    m_IsAnimatedTiberium : boolean;
    // public bool AltPalette
    m_AltPalette : boolean;
    // public bool Normalized
    m_Normalized : boolean;
    // public Layer Layer
    m_Layer : Layer;
    // public bool DoubleThick
    m_DoubleThick : boolean;
    // public bool Flat
    m_Flat : boolean;
    // public bool Translucent
    m_Translucent : boolean;
    // public bool Scorch
    m_Scorch : boolean;
    // public bool Flamer
    m_Flamer : boolean;
    // public bool Crater
    m_Crater : boolean;
    // public bool ForceBigCraters
    m_ForceBigCraters : boolean;
    // public bool Sticky
    m_Sticky : boolean;
    // public bool PingPong
    m_PingPong : boolean;
    // public bool Reverse
    m_Reverse : boolean;
    // public bool Shadow
    m_Shadow : boolean;
    // public bool PsiWarning
    m_PsiWarning : boolean;
    // public bool ShouldFogRemove
    m_ShouldFogRemove : boolean;
}
// ---
// ObjectTypeClass
class ObjectTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public ObjectTypeClass(char const * pID)
    constructor(pID_0 : string);
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // public virtual long GetSizeMax(_ULARGE_INTEGER * pcbSize)
    GetSizeMax(pcbSize_0 : any | any) : number;
    // ObjectTypeClass
    // public virtual CoordStruct * vt_entry_6C(CoordStruct * pDest, CoordStruct * pSrc) const
    vt_entry_6C(pDest_0 : CoordStruct, pSrc_1 : CoordStruct) : CoordStruct;
    // public virtual unsigned long GetOwners() const
    GetOwners() : number;
    // public virtual int GetPipMax() const
    GetPipMax() : number;
    // public virtual void vt_entry_78(unsigned long dwUnk) const
    vt_entry_78(dwUnk_0 : number) : void;
    // public virtual void Dimension2(CoordStruct * pDest)
    Dimension2(pDest_0 : CoordStruct) : void;
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner) = 0
    SpawnAtMapCoords(pMapCoords_0 : CellStruct, pOwner_1 : HouseClass) : boolean;
    // public virtual int GetActualCost(HouseClass * pHouse) const
    GetActualCost(pHouse_0 : HouseClass) : number;
    // public virtual int GetBuildSpeed() const
    GetBuildSpeed() : number;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner) = 0
    CreateObject(pOwner_0 : HouseClass) : ObjectClass;
    // public virtual CellStruct * GetFoundationData(bool IncludeBib) const
    GetFoundationData(IncludeBib_0 : boolean) : CellStruct;
    // public virtual BuildingClass * FindFactory(bool allowOccupied, bool requirePower, bool requireCanBuild, HouseClass const * pHouse) const
    FindFactory(allowOccupied_0 : boolean, requirePower_1 : boolean, requireCanBuild_2 : boolean, pHouse_3 : HouseClass) : BuildingClass;
    // public virtual SHPStruct * GetCameo() const
    GetCameo() : any;
    // public virtual SHPStruct * GetImage() const
    GetImage() : any;
    // public static bool IsBuildCat5(AbstractType abstractID, int idx)
    static IsBuildCat5(abstractID_0 : AbstractType, idx_1 : number) : boolean;
    // public static TechnoTypeClass * GetTechnoType(AbstractType abstractID, int idx)
    static GetTechnoType(abstractID_0 : AbstractType, idx_1 : number) : TechnoTypeClass;
    // public void LoadVoxel()
    LoadVoxel() : void;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public ColorStruct RadialColor
    m_RadialColor : ColorStruct;
    // public unsigned char unused_9B
    m_unused_9B : number;
    // public Armor Armor
    m_Armor : Armor;
    // public int Strength
    m_Strength : number;
    // public SHPStruct * Image
    m_Image : any;
    // public bool ImageAllocated
    m_ImageAllocated : boolean;
    // public SHPStruct * AlphaImage
    m_AlphaImage : any;
    // public VoxelStruct MainVoxel
    m_MainVoxel : any;
    // also used for WO voxels
    // public VoxelStruct TurretVoxel
    m_TurretVoxel : any;
    // public VoxelStruct BarrelVoxel
    m_BarrelVoxel : any;
    // public VoxelStruct[18] ChargerTurrets
    m_ChargerTurrets : any;
    // public VoxelStruct[18] ChargerBarrels
    m_ChargerBarrels : any;
    // public bool NoSpawnAlt
    m_NoSpawnAlt : boolean;
    // public int MaxDimension
    m_MaxDimension : number;
    // index
    // public int CrushSound
    m_CrushSound : number;
    // index
    // public int AmbientSound
    m_AmbientSound : number;
    // public char[25] ImageFile
    m_ImageFile : string;
    // public bool AlternateArcticArt
    m_AlternateArcticArt : boolean;
    // not read from ini
    // public bool ArcticArtInUse
    m_ArcticArtInUse : boolean;
    // public char[25] AlphaImageFile
    m_AlphaImageFile : string;
    // public bool Theater
    m_Theater : boolean;
    // public bool Crushable
    m_Crushable : boolean;
    // public bool Bombable
    m_Bombable : boolean;
    // public bool RadarInvisible
    m_RadarInvisible : boolean;
    // public bool Selectable
    m_Selectable : boolean;
    // public bool LegalTarget
    m_LegalTarget : boolean;
    // public bool Insignificant
    m_Insignificant : boolean;
    // public bool Immune
    m_Immune : boolean;
    // add objects to the logic vector
    // public bool IsLogic
    m_IsLogic : boolean;
    // public bool AllowCellContent
    m_AllowCellContent : boolean;
    // public bool Voxel
    m_Voxel : boolean;
    // public bool NewTheater
    m_NewTheater : boolean;
    // public bool HasRadialIndicator
    m_HasRadialIndicator : boolean;
    // public bool IgnoresFirestorm
    m_IgnoresFirestorm : boolean;
    // public bool UseLineTrail
    m_UseLineTrail : boolean;
    // public ColorStruct LineTrailColor
    m_LineTrailColor : ColorStruct;
    // public int LineTrailColorDecrement
    m_LineTrailColorDecrement : number;
    // public IndexClass<MainVoxelIndexKey, VoxelCacheStruct *> VoxelMainCache
    m_VoxelMainCache : any;
    // public IndexClass<TurretWeaponVoxelIndexKey, VoxelCacheStruct *> VoxelTurretWeaponCache
    m_VoxelTurretWeaponCache : any;
    // public IndexClass<ShadowVoxelIndexKey, VoxelCacheStruct *> VoxelShadowCache
    m_VoxelShadowCache : any;
    // public IndexClass<TurretBarrelVoxelIndexKey, VoxelCacheStruct *> VoxelTurretBarrelCache
    m_VoxelTurretBarrelCache : any;
}
// ---
// AbstractTypeClass
class AbstractTypeClass
    extends AbstractClass
{
    // Constructor
    // public AbstractTypeClass(char const * pID)
    constructor(pID_0 : string);
    // AbstractTypeClass
    // public virtual void LoadTheaterSpecificArt(TheaterType th_type)
    LoadTheaterSpecificArt(th_type_0 : TheaterType) : void;
    // public virtual bool LoadFromINI(CCINIClass * pINI)
    LoadFromINI(pINI_0 : CCINIClass) : boolean;
    // public virtual bool SaveToINI(CCINIClass * pINI)
    SaveToINI(pINI_0 : CCINIClass) : boolean;
    // public char const * get_ID() const
    get_ID() : string;
    // public static AbstractType const AbsID = AbstractType::Abstract
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<AbstractTypeClass *>, 11069800> const Array = 0xA8E968u
    static s_Array : DynamicVectorClass<AbstractTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public char[24] ID
    m_ID : string;
    // public char[32] UINameLabel
    m_UINameLabel : string;
    // public wchar_t const * UIName
    m_UIName : number;
    // public char[49] Name
    m_Name : string;
}
// Extended INI class specified for C
// &C
// use
// CCINIClass
class CCINIClass
    extends INIClass
{
    // non-static
    // public CCINIClass()
    constructor();
    // public void LoadFromFile(char const * filename)
    LoadFromFile(filename_0 : string) : void;
    // Parses an INI file from a CCFile
    // public CCINIClass * ReadCCFile(FileClass * pCCFile, bool bDigest = false, bool bLoadComments = false)
    ReadCCFile(pCCFile_0 : any, bDigest_1 : boolean, bLoadComments_2 : boolean) : CCINIClass;
    // public void WriteCCFile(FileClass * pCCFile, bool bDigest = false)
    WriteCCFile(pCCFile_0 : any, bDigest_1 : boolean) : void;
    // Copies the string table entry pointed to by the INI value into pBuffer.
    // public int ReadStringtableEntry(char const * pSection, char const * pKey, wchar_t * pBuffer, size_t szBufferSize)
    ReadStringtableEntry(pSection_0 : string, pKey_1 : string, pBuffer_2 : number, szBufferSize_3 : any) : number;
    // public int ReadStringtableEntry(char const * pSection, char const * pKey, wchar_t[-1]& pBuffer = Size)
    ReadStringtableEntry(pSection_0 : string, pKey_1 : string, pBuffer_2 : number) : number;
    // public unsigned long GetCRC()
    GetCRC() : number;
    // STATIC
    // public static reference<unsigned long, 12025344, 0> const RulesHash = 0xB77E00u
    static s_RulesHash : number;
    // public static reference<unsigned long, 12025348, 0> const ArtHash = 0xB77E04u
    static s_ArtHash : number;
    // public static reference<unsigned long, 12025352, 0> const AIHash = 0xB77E08u
    static s_AIHash : number;
    // this is a pointer in the class
    // public static reference<CCINIClass *, 8941640, 0> const INI_Rules = 0x887048u
    static s_INI_Rules : CCINIClass;
    // these are static class variables, why the fuck did you differentiate them, WW?
    // public static reference<CCINIClass, 8941864, 0> const INI_AI = 0x887128u
    static s_INI_AI : CCINIClass;
    // public static reference<CCINIClass, 8941952, 0> const INI_Art = 0x887180u
    static s_INI_Art : CCINIClass;
    // public static reference<CCINIClass, 8942088, 0> const INI_UIMD = 0x887208u
    static s_INI_UIMD : CCINIClass;
    // public static reference<CCINIClass, 8941760, 0> const INI_RA2MD = 0x8870C0u
    static s_INI_RA2MD : CCINIClass;
    // Properties
    // public bool Digested
    m_Digested : boolean;
    // public unsigned char[20] Digest
    m_Digest : ArrayBuffer;
}
// Basic INI class
// INIClass
class INIClass
{
    // public INIClass()
    constructor();
    // public void Reset()
    Reset() : void;
    // public void Clear(char const * s1, char * s2)
    Clear(s1_0 : string, s2_1 : string) : void;
    // public INIClass::INISection * GetSection(char const * pSection)
    GetSection(pSection_0 : string) : any;
    // public int GetKeyCount(char const * pSection)
    GetKeyCount(pSection_0 : string) : number;
    // public char const * GetKeyName(char const * pSection, int nKeyIndex)
    GetKeyName(pSection_0 : string, nKeyIndex_1 : number) : string;
    // Reads an ANSI string. Returns the string's length.
    // public int ReadString(char const * pSection, char const * pKey, char const * pDefault, char * pBuffer, size_t szBufferSize)
    ReadString(pSection_0 : string, pKey_1 : string, pDefault_2 : string, pBuffer_3 : string, szBufferSize_4 : any) : number;
    // public int GetString(char const * pSection, char const * pKey, char * pBuffer, size_t szBufferSize)
    GetString(pSection_0 : string, pKey_1 : string, pBuffer_2 : string, szBufferSize_3 : any) : number;
    // Writes an ANSI string.
    // public bool WriteString(char const * pSection, char const * pKey, char const * pString)
    WriteString(pSection_0 : string, pKey_1 : string, pString_2 : string) : boolean;
    // Reads an escaped Unicode string. Returns the string's length.
    // public int ReadUnicodeString(char const * pSection, char const * pKey, wchar_t const * pDefault, wchar_t * pBuffer, size_t szBufferSize)
    ReadUnicodeString(pSection_0 : string, pKey_1 : string, pDefault_2 : number, pBuffer_3 : number, szBufferSize_4 : any) : number;
    // Writes an escaped Unicode string.
    // public bool WriteUnicodeString(char const * pSection, char const * pKey, wchar_t const * pString)
    WriteUnicodeString(pSection_0 : string, pKey_1 : string, pString_2 : number) : boolean;
    // Reads an boolean value.
    // public bool ReadBool(char const * pSection, char const * pKey, bool bDefault)
    ReadBool(pSection_0 : string, pKey_1 : string, bDefault_2 : boolean) : boolean;
    // public void GetBool(char const * pSection, char const * pKey, bool& bValue)
    GetBool(pSection_0 : string, pKey_1 : string, bValue_2 : boolean) : void;
    // Writes an boolean value.
    // public bool WriteBool(char const * pSection, char const * pKey, bool bValue)
    WriteBool(pSection_0 : string, pKey_1 : string, bValue_2 : boolean) : boolean;
    // Reads an integer value.
    // public int ReadInteger(char const * pSection, char const * pKey, int nDefault)
    ReadInteger(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    // public void GetInteger(char const * pSection, char const * pKey, int& nValue)
    GetInteger(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    // Writes an integer value.
    // public bool WriteInteger(char const * pSection, char const * pKey, int nValue, bool bHex)
    WriteInteger(pSection_0 : string, pKey_1 : string, nValue_2 : number, bHex_3 : boolean) : boolean;
    // Reads a decimal value.
    // public double ReadDouble(char const * pSection, char const * pKey, double dDefault)
    ReadDouble(pSection_0 : string, pKey_1 : string, dDefault_2 : number) : number;
    // public void GetDouble(char const * pSection, char const * pKey, double& nValue)
    GetDouble(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    // Writes a decimal value.
    // public bool WriteDouble(char const * pSection, char const * pKey, double dValue)
    WriteDouble(pSection_0 : string, pKey_1 : string, dValue_2 : number) : boolean;
    // public int ReadRate(char const * pSection, char const * pKey, int nDefault)
    ReadRate(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    // public void GetRate(char const * pSection, char const * pKey, int& nValue)
    GetRate(pSection_0 : string, pKey_1 : string, nValue_2 : number) : void;
    // public bool WriteRate(char const * pSection, char const * pKey, int nValue)
    WriteRate(pSection_0 : string, pKey_1 : string, nValue_2 : number) : boolean;
    // Reads two integer values.
    // public int * Read2Integers(int * pBuffer, char const * pSection, char const * pKey, int * pDefault)
    Read2Integers(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    // public Point2D * ReadPoint2D(Point2D& ret, char const * pSection, char const * pKey, Point2D& defValue)
    ReadPoint2D(ret_0 : Point2D, pSection_1 : string, pKey_2 : string, defValue_3 : Point2D) : Point2D;
    // public void GetPoint2D(char const * pSection, char const * pKey, Point2D& value)
    GetPoint2D(pSection_0 : string, pKey_1 : string, value_2 : Point2D) : void;
    // Writes two integer values.
    // public bool Write2Integers(char const * pSection, char const * pKey, int * pValues)
    Write2Integers(pSection_0 : string, pKey_1 : string, pValues_2 : number) : boolean;
    // Reads three integer values.
    // public int * Read3Integers(int * pBuffer, char const * pSection, char const * pKey, int * pDefault)
    Read3Integers(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    // public CoordStruct * ReadPoint3D(CoordStruct& ret, char const * pSection, char const * pKey, CoordStruct& defValue)
    ReadPoint3D(ret_0 : CoordStruct, pSection_1 : string, pKey_2 : string, defValue_3 : CoordStruct) : CoordStruct;
    // public void GetPoint3D(char const * pSection, char const * pKey, CoordStruct& value)
    GetPoint3D(pSection_0 : string, pKey_1 : string, value_2 : CoordStruct) : void;
    // Reads three byte values.
    // public unsigned char * Read3Bytes(unsigned char * pBuffer, char const * pSection, char const * pKey, unsigned char * pDefault)
    Read3Bytes(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    // Writes three byte values.
    // public bool Write3Bytes(char const * pSection, char const * pKey, unsigned char * pValues)
    Write3Bytes(pSection_0 : string, pKey_1 : string, pValues_2 : number) : boolean;
    // Tests whether the given section and key exists. If key is NULL, only the section will be looked for.
    // public bool Exists(char const * pSection, char const * pKey)
    Exists(pSection_0 : string, pKey_1 : string) : boolean;
    // public int ReadTime(char const * pSection, char const * pKey, int nDefault)
    ReadTime(pSection_0 : string, pKey_1 : string, nDefault_2 : number) : number;
    // public bool WriteTime(char const * pSection, char const * pKey, int nValue)
    WriteTime(pSection_0 : string, pKey_1 : string, nValue_2 : number) : boolean;
    // Pip= to idx ( pip strings with index 
    // <
    // pDefault are not even scanned! )
    // public int ReadPip(char const * pSection, char const * pKey, int pDefault)
    ReadPip(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // PipScale= to idx
    // public int ReadPipScale(char const * pSection, char const * pKey, int pDefault)
    ReadPipScale(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Category= to idx
    // public int ReadCategory(char const * pSection, char const * pKey, int pDefault)
    ReadCategory(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Color=%s to idx
    // public int ReadColorString(char const * pSection, char const * pKey, int pDefault)
    ReadColorString(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Foundation= to idx
    // public int ReadFoundation(char const * pSection, char const * pKey, int pDefault)
    ReadFoundation(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // MovementZone= to idx
    // public int ReadMovementZone(char const * pSection, char const * pKey, int pDefault)
    ReadMovementZone(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // SpeedType= to idx
    // public int ReadSpeedType(char const * pSection, char const * pKey, int pDefault)
    ReadSpeedType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // [SW]Action= to idx
    // public int ReadSWAction(char const * pSection, char const * pKey, int pDefault)
    ReadSWAction(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // [SW]Type= to idx
    // public int ReadSWType(char const * pSection, char const * pKey, int pDefault)
    ReadSWType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // EVA Event name to idx
    // public int ReadVoxName(char const * pSection, char const * pKey, int pDefault)
    ReadVoxName(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Factory= to idx
    // public int ReadFactory(char const * pSection, char const * pKey, int pDefault)
    ReadFactory(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadBuildCat(char const * pSection, char const * pKey, int pDefault)
    ReadBuildCat(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Parses a list of Countries and returns a bitfield, i.e. Owner= or RequiredHouses=
    // public int ReadHouseTypesList(char const * pSection, char const * pKey, int pDefault)
    ReadHouseTypesList(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Parses a list of Houses and returns a bitfield, i.e. Allies= in map
    // public int ReadHousesList(char const * pSection, char const * pKey, int pDefault)
    ReadHousesList(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadArmorType(char const * pSection, char const * pKey, int pDefault)
    ReadArmorType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadLandType(char const * pSection, char const * pKey, int pDefault)
    ReadLandType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // supports MP names (
    // <Player
    // @
    // X>) too, wtf
    // ALLOCATES if country name is not found
    // returns idx of country it reads
    // public int ReadHouseType(char const * pSection, char const * pKey, int pDefault)
    ReadHouseType(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // ALLOCATES if name is not found
    // public int ReadSide(char const * pSection, char const * pKey, int pDefault)
    ReadSide(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // returns index of movie with this filename
    // public int ReadMovie(char const * pSection, char const * pKey, int pDefault)
    ReadMovie(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // map theater
    // public int ReadTheater(char const * pSection, char const * pKey, int pDefault)
    ReadTheater(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadTheme(char const * pSection, char const * pKey, int pDefault)
    ReadTheme(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadEdge(char const * pSection, char const * pKey, int pDefault)
    ReadEdge(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadPowerup(char const * pSection, char const * pKey, int pDefault)
    ReadPowerup(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // [Anim]Layer= to idx
    // public int ReadLayer(char const * pSection, char const * pKey, int pDefault)
    ReadLayer(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // public int ReadVHPScan(char const * pSection, char const * pKey, int pDefault)
    ReadVHPScan(pSection_0 : string, pKey_1 : string, pDefault_2 : number) : number;
    // Color=%d,%d,%d to idx , used to parse [Colors]
    // public ColorStruct * ReadColor(ColorStruct * pBuffer, char const * pSection, char const * pKey, ColorStruct const& defValue)
    ReadColor(pBuffer_0 : ColorStruct, pSection_1 : string, pKey_2 : string, defValue_3 : ColorStruct) : ColorStruct;
    // public ColorStruct ReadColor(char const * const pSection, char const * const pKey, ColorStruct const& defValue)
    ReadColor(pSection_0 : number, pKey_1 : number, defValue_2 : ColorStruct) : ColorStruct;
    // public void GetColor(char const * const pSection, char const * const pKey, ColorStruct& value)
    GetColor(pSection_0 : number, pKey_1 : number, value_2 : ColorStruct) : void;
    // public bool WriteColor(char const * const pSection, char const * const pKey, ColorStruct const& color)
    WriteColor(pSection_0 : number, pKey_1 : number, color_2 : ColorStruct) : boolean;
    // OverlayPack, OverlayDataPack, IsoMapPack5
    // Those uses 1=xxxx, 2=xxxx, 3=xxxx .etc.
    // public size_t ReadUUBlock(char const * const pSection, void * pBuffer, size_t length)
    ReadUUBlock(pSection_0 : number, pBuffer_1 : void, length_2 : any) : any;
    // public bool WriteUUBlock(char const * const pSection, void * pBuffer, size_t length)
    WriteUUBlock(pSection_0 : number, pBuffer_1 : void, length_2 : any) : boolean;
    // 18 bytes
    // public unsigned char * ReadAbilities(unsigned char * pBuffer, char const * pSection, char const * pKey, unsigned char * pDefault)
    ReadAbilities(pBuffer_0 : number, pSection_1 : string, pKey_2 : string, pDefault_3 : number) : number;
    // public TechnoTypeClass * GetTechnoType(char const * pSection, char const * pKey)
    GetTechnoType(pSection_0 : string, pKey_1 : string) : TechnoTypeClass;
    // safer and more convenient overload for string reading
    // public int ReadString(char const * pSection, char const * pKey, char const * pDefault, char[-1]& pBuffer = Size)
    ReadString(pSection_0 : string, pKey_1 : string, pDefault_2 : string, pBuffer_3 : number) : number;
    // public int GetString(char const * pSection, char const * pKey, char[-1]& pBuffer = Size)
    GetString(pSection_0 : string, pKey_1 : string, pBuffer_2 : number) : number;
    // safer and more convenient overload for escaped unicode string reading
    // public int ReadUnicodeString(char const * pSection, char const * pKey, wchar_t const * pDefault, wchar_t[-1]& pBuffer = Size)
    ReadUnicodeString(pSection_0 : string, pKey_1 : string, pDefault_2 : number, pBuffer_3 : number) : number;
    // fsldargh who the fuck decided to pass structures by value here
    // public static TypeList<int> * GetPrerequisites(TypeList<int> * pBuffer, INIClass * pINI, char const * pSection, char const * pKey, TypeList<int> Defaults)
    static GetPrerequisites(pBuffer_0 : TypeList<number>, pINI_1 : INIClass, pSection_2 : string, pKey_3 : string, Defaults_4 : TypeList<number>) : TypeList<number>;
    // public static bool IsBlank(char const * pValue)
    static IsBlank(pValue_0 : string) : boolean;
    // public char * CurrentSectionName
    m_CurrentSectionName : string;
    // public INIClass::INISection * CurrentSection
    m_CurrentSection : any;
    // public INIClass::INIComment * LineComments
    m_LineComments : any;
    // public List<INIClass::INISection> Sections
    m_Sections : any;
    // public char[28] __Sections
    m___Sections : string;
    // <CRCValue
    // of the Name, Pointer to the section>
    // public IndexType SectionIndex
    m_SectionIndex : any;
    // public char[20] __SectionIndex
    m___SectionIndex : string;
}
// forward declarations
// TechnoTypeClass
class TechnoTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public TechnoTypeClass(char const * id, SpeedType speedtype)
    constructor(id_0 : string, speedtype_1 : SpeedType);
    // public static TechnoTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : TechnoTypeClass;
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // public virtual long GetSizeMax(_ULARGE_INTEGER * pcbSize)
    GetSizeMax(pcbSize_0 : any | any) : number;
    // TechnoTypeClass
    // public virtual bool CanUseWaypoint() const
    CanUseWaypoint() : boolean;
    // public virtual bool CanAttackMove() const
    CanAttackMove() : boolean;
    // public virtual bool CanCreateHere(CellStruct const& mapCoords, HouseClass * pOwner) const
    CanCreateHere(mapCoords_0 : CellStruct, pOwner_1 : HouseClass) : boolean;
    // public virtual int GetCost() const
    GetCost() : number;
    // public virtual int GetRepairStepCost() const
    GetRepairStepCost() : number;
    // public virtual int GetRepairStep() const
    GetRepairStep() : number;
    // public virtual int GetRefund(HouseClass * pHouse, bool bUnk) const
    GetRefund(pHouse_0 : HouseClass, bUnk_1 : boolean) : number;
    // public virtual int GetFlightLevel() const
    GetFlightLevel() : number;
    // non-virtual
    // public static TechnoTypeClass * GetByTypeAndIndex(AbstractType abs, int index)
    static GetByTypeAndIndex(abs_0 : AbstractType, index_1 : number) : TechnoTypeClass;
    // public bool HasMultipleTurrets() const
    HasMultipleTurrets() : boolean;
    // public CoordStruct * GetParticleSysOffset(CoordStruct * pBuffer) const
    GetParticleSysOffset(pBuffer_0 : CoordStruct) : CoordStruct;
    // public CoordStruct GetParticleSysOffset() const
    GetParticleSysOffset() : CoordStruct;
    // public bool InOwners(unsigned long const bitHouseType) const
    InOwners(bitHouseType_0 : number) : boolean;
    // public bool InRequiredHouses(unsigned long const bitHouseType) const
    InRequiredHouses(bitHouseType_0 : number) : boolean;
    // public bool InForbiddenHouses(unsigned long const bitHouseType) const
    InForbiddenHouses(bitHouseType_0 : number) : boolean;
    // weapon related
    // public WeaponStruct& GetWeapon(size_t const index, bool const elite)
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    // public WeaponStruct const& GetWeapon(size_t const index, bool const elite) const
    GetWeapon(index_0 : any, elite_1 : boolean) : WeaponStruct;
    // public static constant_ptr<DynamicVectorClass<TechnoTypeClass *>, 11070208> const Array = 0xA8EB00u
    static s_Array : DynamicVectorClass<TechnoTypeClass>;
    // public static  MaxWeapons = 18
    static s_MaxWeapons : any;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int WalkRate
    m_WalkRate : number;
    // public int IdleRate
    m_IdleRate : number;
    // public AbilitiesStruct VeteranAbilities
    m_VeteranAbilities : AbilitiesStruct;
    // public AbilitiesStruct EliteAbilities
    m_EliteAbilities : AbilitiesStruct;
    // public double SpecialThreatValue
    m_SpecialThreatValue : number;
    // public double MyEffectivenessCoefficient
    m_MyEffectivenessCoefficient : number;
    // public double TargetEffectivenessCoefficient
    m_TargetEffectivenessCoefficient : number;
    // public double TargetSpecialThreatCoefficient
    m_TargetSpecialThreatCoefficient : number;
    // public double TargetStrengthCoefficient
    m_TargetStrengthCoefficient : number;
    // public double TargetDistanceCoefficient
    m_TargetDistanceCoefficient : number;
    // public double ThreatAvoidanceCoefficient
    m_ThreatAvoidanceCoefficient : number;
    // public int SlowdownDistance
    m_SlowdownDistance : number;
    // public unsigned long align_2FC
    m_align_2FC : number;
    // public double unknown_double_300
    m_unknown_double_300 : number;
    // public double AccelerationFactor
    m_AccelerationFactor : number;
    // public int CloakingSpeed
    m_CloakingSpeed : number;
    // public TypeList<VoxelAnimTypeClass *> DebrisTypes
    m_DebrisTypes : TypeList<VoxelAnimTypeClass>;
    // public TypeList<int> DebrisMaximums
    m_DebrisMaximums : TypeList<number>;
    // public _GUID Locomotor
    m_Locomotor : any;
    // public unsigned long align_35C
    m_align_35C : number;
    // public double VoxelScaleX
    m_VoxelScaleX : number;
    // public double VoxelScaleY
    m_VoxelScaleY : number;
    // public double Weight
    m_Weight : number;
    // public double PhysicalSize
    m_PhysicalSize : number;
    // public double Size
    m_Size : number;
    // public double SizeLimit
    m_SizeLimit : number;
    // public bool HoverAttack
    m_HoverAttack : boolean;
    // public int VHPScan
    m_VHPScan : number;
    // public int unknown_int_398
    m_unknown_int_398 : number;
    // public unsigned long align_39C
    m_align_39C : number;
    // public double RollAngle
    m_RollAngle : number;
    // public double PitchSpeed
    m_PitchSpeed : number;
    // public double PitchAngle
    m_PitchAngle : number;
    // public int BuildLimit
    m_BuildLimit : number;
    // public Category Category
    m_Category : Category;
    // public unsigned long unknown_3C0
    m_unknown_3C0 : number;
    // public unsigned long align_3C4
    m_align_3C4 : number;
    // public double DeployTime
    m_DeployTime : number;
    // public int FireAngle
    m_FireAngle : number;
    // public PipScale PipScale
    m_PipScale : PipScale;
    // public bool PipsDrawForAll
    m_PipsDrawForAll : boolean;
    // public int LeptonMindControlOffset
    m_LeptonMindControlOffset : number;
    // public int PixelSelectionBracketDelta
    m_PixelSelectionBracketDelta : number;
    // public int PipWrap
    m_PipWrap : number;
    // public TypeList<BuildingTypeClass *> Dock
    m_Dock : TypeList<BuildingTypeClass>;
    // public BuildingTypeClass * DeploysInto
    m_DeploysInto : BuildingTypeClass;
    // public UnitTypeClass * UndeploysInto
    m_UndeploysInto : UnitTypeClass;
    // public UnitTypeClass * PowersUnit
    m_PowersUnit : UnitTypeClass;
    // public bool PoweredUnit
    m_PoweredUnit : boolean;
    // public TypeList<int> VoiceSelect
    m_VoiceSelect : TypeList<number>;
    // public TypeList<int> VoiceSelectEnslaved
    m_VoiceSelectEnslaved : TypeList<number>;
    // public TypeList<int> VoiceSelectDeactivated
    m_VoiceSelectDeactivated : TypeList<number>;
    // public TypeList<int> VoiceMove
    m_VoiceMove : TypeList<number>;
    // public TypeList<int> VoiceAttack
    m_VoiceAttack : TypeList<number>;
    // public TypeList<int> VoiceSpecialAttack
    m_VoiceSpecialAttack : TypeList<number>;
    // public TypeList<int> VoiceDie
    m_VoiceDie : TypeList<number>;
    // public TypeList<int> VoiceFeedback
    m_VoiceFeedback : TypeList<number>;
    // public TypeList<int> MoveSound
    m_MoveSound : TypeList<number>;
    // public TypeList<int> DieSound
    m_DieSound : TypeList<number>;
    // public int AuxSound1
    m_AuxSound1 : number;
    // public int AuxSound2
    m_AuxSound2 : number;
    // public int CreateSound
    m_CreateSound : number;
    // public int DamageSound
    m_DamageSound : number;
    // public int ImpactWaterSound
    m_ImpactWaterSound : number;
    // public int ImpactLandSound
    m_ImpactLandSound : number;
    // public int CrashingSound
    m_CrashingSound : number;
    // public int SinkingSound
    m_SinkingSound : number;
    // public int VoiceFalling
    m_VoiceFalling : number;
    // public int VoiceCrashing
    m_VoiceCrashing : number;
    // public int VoiceSinking
    m_VoiceSinking : number;
    // public int VoiceEnter
    m_VoiceEnter : number;
    // public int VoiceCapture
    m_VoiceCapture : number;
    // public int TurretRotateSound
    m_TurretRotateSound : number;
    // public int EnterTransportSound
    m_EnterTransportSound : number;
    // public int LeaveTransportSound
    m_LeaveTransportSound : number;
    // public int DeploySound
    m_DeploySound : number;
    // public int UndeploySound
    m_UndeploySound : number;
    // public int ChronoInSound
    m_ChronoInSound : number;
    // public int ChronoOutSound
    m_ChronoOutSound : number;
    // public int VoiceHarvest
    m_VoiceHarvest : number;
    // public int VoicePrimaryWeaponAttack
    m_VoicePrimaryWeaponAttack : number;
    // public int VoicePrimaryEliteWeaponAttack
    m_VoicePrimaryEliteWeaponAttack : number;
    // public int VoiceSecondaryWeaponAttack
    m_VoiceSecondaryWeaponAttack : number;
    // public int VoiceSecondaryEliteWeaponAttack
    m_VoiceSecondaryEliteWeaponAttack : number;
    // public int VoiceDeploy
    m_VoiceDeploy : number;
    // public int VoiceUndeploy
    m_VoiceUndeploy : number;
    // public int EnterGrinderSound
    m_EnterGrinderSound : number;
    // public int LeaveGrinderSound
    m_LeaveGrinderSound : number;
    // public int EnterBioReactorSound
    m_EnterBioReactorSound : number;
    // public int LeaveBioReactorSound
    m_LeaveBioReactorSound : number;
    // public int ActivateSound
    m_ActivateSound : number;
    // public int DeactivateSound
    m_DeactivateSound : number;
    // public int MindClearedSound
    m_MindClearedSound : number;
    // public MovementZone MovementZone
    m_MovementZone : MovementZone;
    // public int GuardRange
    m_GuardRange : number;
    // public int MinDebris
    m_MinDebris : number;
    // public int MaxDebris
    m_MaxDebris : number;
    // public TypeList<AnimTypeClass *> DebrisAnims
    m_DebrisAnims : TypeList<AnimTypeClass>;
    // public int Passengers
    m_Passengers : number;
    // public bool OpenTopped
    m_OpenTopped : boolean;
    // public int Sight
    m_Sight : number;
    // public bool ResourceGatherer
    m_ResourceGatherer : boolean;
    // public bool ResourceDestination
    m_ResourceDestination : boolean;
    // public bool RevealToAll
    m_RevealToAll : boolean;
    // public bool Drainable
    m_Drainable : boolean;
    // public int SensorsSight
    m_SensorsSight : number;
    // public int DetectDisguiseRange
    m_DetectDisguiseRange : number;
    // public int BombSight
    m_BombSight : number;
    // public int LeadershipRating
    m_LeadershipRating : number;
    // public NavalTargetingType NavalTargeting
    m_NavalTargeting : NavalTargetingType;
    // public LandTargetingType LandTargeting
    m_LandTargeting : LandTargetingType;
    // public float BuildTimeMultiplier
    m_BuildTimeMultiplier : number;
    // public int MindControlRingOffset
    m_MindControlRingOffset : number;
    // public int Cost
    m_Cost : number;
    // public int Soylent
    m_Soylent : number;
    // public int FlightLevel
    m_FlightLevel : number;
    // public int AirstrikeTeam
    m_AirstrikeTeam : number;
    // public int EliteAirstrikeTeam
    m_EliteAirstrikeTeam : number;
    // public AircraftTypeClass * AirstrikeTeamType
    m_AirstrikeTeamType : AircraftTypeClass;
    // public AircraftTypeClass * EliteAirstrikeTeamType
    m_EliteAirstrikeTeamType : AircraftTypeClass;
    // public int AirstrikeRechargeTime
    m_AirstrikeRechargeTime : number;
    // public int EliteAirstrikeRechargeTime
    m_EliteAirstrikeRechargeTime : number;
    // public int TechLevel
    m_TechLevel : number;
    // public TypeList<int> Prerequisite
    m_Prerequisite : TypeList<number>;
    // public TypeList<int> PrerequisiteOverride
    m_PrerequisiteOverride : TypeList<number>;
    // public int ThreatPosed
    m_ThreatPosed : number;
    // public int Points
    m_Points : number;
    // public int Speed
    m_Speed : number;
    // public SpeedType SpeedType
    m_SpeedType : SpeedType;
    // public int InitialAmmo
    m_InitialAmmo : number;
    // public int Ammo
    m_Ammo : number;
    // public int IFVMode
    m_IFVMode : number;
    // public int AirRangeBonus
    m_AirRangeBonus : number;
    // public bool BerserkFriendly
    m_BerserkFriendly : boolean;
    // public bool SprayAttack
    m_SprayAttack : boolean;
    // public bool Pushy
    m_Pushy : boolean;
    // public bool Natural
    m_Natural : boolean;
    // public bool Unnatural
    m_Unnatural : boolean;
    // public bool CloseRange
    m_CloseRange : boolean;
    // public int Reload
    m_Reload : number;
    // public int EmptyReload
    m_EmptyReload : number;
    // public int ReloadIncrement
    m_ReloadIncrement : number;
    // public int RadialFireSegments
    m_RadialFireSegments : number;
    // public int DeployFireWeapon
    m_DeployFireWeapon : number;
    // public bool DeployFire
    m_DeployFire : boolean;
    // public bool DeployToLand
    m_DeployToLand : boolean;
    // public bool MobileFire
    m_MobileFire : boolean;
    // public bool OpportunityFire
    m_OpportunityFire : boolean;
    // public bool DistributedFire
    m_DistributedFire : boolean;
    // public bool DamageReducesReadiness
    m_DamageReducesReadiness : boolean;
    // public int ReadinessReductionMultiplier
    m_ReadinessReductionMultiplier : number;
    // public UnitTypeClass * UnloadingClass
    m_UnloadingClass : UnitTypeClass;
    // public AnimTypeClass * DeployingAnim
    m_DeployingAnim : AnimTypeClass;
    // public bool AttackFriendlies
    m_AttackFriendlies : boolean;
    // public bool AttackCursorOnFriendlies
    m_AttackCursorOnFriendlies : boolean;
    // public int UndeployDelay
    m_UndeployDelay : number;
    // public bool PreventAttackMove
    m_PreventAttackMove : boolean;
    // public unsigned long OwnerFlags
    m_OwnerFlags : number;
    // public int AIBasePlanningSide
    m_AIBasePlanningSide : number;
    // public bool StupidHunt
    m_StupidHunt : boolean;
    // public bool AllowedToStartInMultiplayer
    m_AllowedToStartInMultiplayer : boolean;
    // public char[25] CameoFile
    m_CameoFile : string;
    // public SHPStruct * Cameo
    m_Cameo : any;
    // public bool CameoAllocated
    m_CameoAllocated : boolean;
    // public char[25] AltCameoFile
    m_AltCameoFile : string;
    // public SHPStruct * AltCameo
    m_AltCameo : any;
    // public bool AltCameoAllocated
    m_AltCameoAllocated : boolean;
    // public int RotCount
    m_RotCount : number;
    // public int ROT
    m_ROT : number;
    // public int TurretOffset
    m_TurretOffset : number;
    // public bool CanBeHidden
    m_CanBeHidden : boolean;
    // twice
    // public int Points2
    m_Points2 : number;
    // public TypeList<AnimTypeClass *> Explosion
    m_Explosion : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> DestroyAnim
    m_DestroyAnim : TypeList<AnimTypeClass>;
    // public ParticleSystemTypeClass * NaturalParticleSystem
    m_NaturalParticleSystem : ParticleSystemTypeClass;
    // public CoordStruct NaturalParticleSystemLocation
    m_NaturalParticleSystemLocation : CoordStruct;
    // public ParticleSystemTypeClass * RefinerySmokeParticleSystem
    m_RefinerySmokeParticleSystem : ParticleSystemTypeClass;
    // public TypeList<ParticleSystemTypeClass *> DamageParticleSystems
    m_DamageParticleSystems : TypeList<ParticleSystemTypeClass>;
    // public TypeList<ParticleSystemTypeClass *> DestroyParticleSystems
    m_DestroyParticleSystems : TypeList<ParticleSystemTypeClass>;
    // public CoordStruct DamageSmokeOffset
    m_DamageSmokeOffset : CoordStruct;
    // public bool DamSmkOffScrnRel
    m_DamSmkOffScrnRel : boolean;
    // public CoordStruct DestroySmokeOffset
    m_DestroySmokeOffset : CoordStruct;
    // public CoordStruct RefinerySmokeOffsetOne
    m_RefinerySmokeOffsetOne : CoordStruct;
    // public CoordStruct RefinerySmokeOffsetTwo
    m_RefinerySmokeOffsetTwo : CoordStruct;
    // public CoordStruct RefinerySmokeOffsetThree
    m_RefinerySmokeOffsetThree : CoordStruct;
    // public CoordStruct RefinerySmokeOffsetFour
    m_RefinerySmokeOffsetFour : CoordStruct;
    // public int ShadowIndex
    m_ShadowIndex : number;
    // public int Storage
    m_Storage : number;
    // public bool TurretNotExportedOnGround
    m_TurretNotExportedOnGround : boolean;
    // public bool Gunner
    m_Gunner : boolean;
    // public bool HasTurretTooltips
    m_HasTurretTooltips : boolean;
    // public int TurretCount
    m_TurretCount : number;
    // public int WeaponCount
    m_WeaponCount : number;
    // public bool IsChargeTurret
    m_IsChargeTurret : boolean;
    // public int[18] TurretWeapon
    m_TurretWeapon : number;
    // public CoordStruct[5] AlternativeFLH
    m_AlternativeFLH : CoordStruct;
    // public WeaponStruct[18] Weapon
    m_Weapon : WeaponStruct;
    // public bool ClearAllWeapons
    m_ClearAllWeapons : boolean;
    // public WeaponStruct[18] EliteWeapon
    m_EliteWeapon : WeaponStruct;
    // public bool TypeImmune
    m_TypeImmune : boolean;
    // public bool MoveToShroud
    m_MoveToShroud : boolean;
    // public bool Trainable
    m_Trainable : boolean;
    // enabled for Cyborg InfantryTypes
    // public bool DamageSparks
    m_DamageSparks : boolean;
    // public bool TargetLaser
    m_TargetLaser : boolean;
    // public bool ImmuneToVeins
    m_ImmuneToVeins : boolean;
    // public bool TiberiumHeal
    m_TiberiumHeal : boolean;
    // public bool CloakStop
    m_CloakStop : boolean;
    // public bool IsTrain
    m_IsTrain : boolean;
    // public bool IsDropship
    m_IsDropship : boolean;
    // public bool ToProtect
    m_ToProtect : boolean;
    // public bool Disableable
    m_Disableable : boolean;
    // always false, if true it cannot be built from sidebar
    // public bool Unbuildable
    m_Unbuildable : boolean;
    // public bool DoubleOwned
    m_DoubleOwned : boolean;
    // public bool Invisible
    m_Invisible : boolean;
    // public bool RadarVisible
    m_RadarVisible : boolean;
    // not loaded from the INIs
    // public bool HasPrimary
    m_HasPrimary : boolean;
    // public bool Sensors
    m_Sensors : boolean;
    // public bool Nominal
    m_Nominal : boolean;
    // public bool DontScore
    m_DontScore : boolean;
    // public bool DamageSelf
    m_DamageSelf : boolean;
    // public bool Turret
    m_Turret : boolean;
    // public bool TurretRecoil
    m_TurretRecoil : boolean;
    // public TurretControl TurretAnimData
    m_TurretAnimData : TurretControl;
    // always false?
    // public bool unknown_bool_CB4
    m_unknown_bool_CB4 : boolean;
    // public TurretControl BarrelAnimData
    m_BarrelAnimData : TurretControl;
    // always false?
    // public bool unknown_bool_CC8
    m_unknown_bool_CC8 : boolean;
    // public bool Repairable
    m_Repairable : boolean;
    // public bool Crewed
    m_Crewed : boolean;
    // public bool Naval
    m_Naval : boolean;
    // public bool Remapable
    m_Remapable : boolean;
    // public bool Cloakable
    m_Cloakable : boolean;
    // public bool GapGenerator
    m_GapGenerator : boolean;
    // public char GapRadiusInCells
    m_GapRadiusInCells : number;
    // public char SuperGapRadiusInCells
    m_SuperGapRadiusInCells : number;
    // public bool Teleporter
    m_Teleporter : boolean;
    // public bool IsGattling
    m_IsGattling : boolean;
    // public int WeaponStages
    m_WeaponStages : number;
    // public int[6] WeaponStage
    m_WeaponStage : number;
    // public int[6] EliteStage
    m_EliteStage : number;
    // public int RateUp
    m_RateUp : number;
    // public int RateDown
    m_RateDown : number;
    // public bool SelfHealing
    m_SelfHealing : boolean;
    // public bool Explodes
    m_Explodes : boolean;
    // public WeaponTypeClass * DeathWeapon
    m_DeathWeapon : WeaponTypeClass;
    // public float DeathWeaponDamageModifier
    m_DeathWeaponDamageModifier : number;
    // public bool NoAutoFire
    m_NoAutoFire : boolean;
    // public bool TurretSpins
    m_TurretSpins : boolean;
    // public bool TiltCrashJumpjet
    m_TiltCrashJumpjet : boolean;
    // public bool Normalized
    m_Normalized : boolean;
    // public bool ManualReload
    m_ManualReload : boolean;
    // public bool VisibleLoad
    m_VisibleLoad : boolean;
    // public bool LightningRod
    m_LightningRod : boolean;
    // public bool HunterSeeker
    m_HunterSeeker : boolean;
    // public bool Crusher
    m_Crusher : boolean;
    // public bool OmniCrusher
    m_OmniCrusher : boolean;
    // public bool OmniCrushResistant
    m_OmniCrushResistant : boolean;
    // public bool TiltsWhenCrushes
    m_TiltsWhenCrushes : boolean;
    // public bool IsSubterranean
    m_IsSubterranean : boolean;
    // public bool AutoCrush
    m_AutoCrush : boolean;
    // public bool Bunkerable
    m_Bunkerable : boolean;
    // public bool CanDisguise
    m_CanDisguise : boolean;
    // public bool PermaDisguise
    m_PermaDisguise : boolean;
    // public bool DetectDisguise
    m_DetectDisguise : boolean;
    // public bool DisguiseWhenStill
    m_DisguiseWhenStill : boolean;
    // public bool CanApproachTarget
    m_CanApproachTarget : boolean;
    // public bool CanRecalcApproachTarget
    m_CanRecalcApproachTarget : boolean;
    // public bool ImmuneToPsionics
    m_ImmuneToPsionics : boolean;
    // public bool ImmuneToPsionicWeapons
    m_ImmuneToPsionicWeapons : boolean;
    // public bool ImmuneToRadiation
    m_ImmuneToRadiation : boolean;
    // public bool Parasiteable
    m_Parasiteable : boolean;
    // public bool DefaultToGuardArea
    m_DefaultToGuardArea : boolean;
    // public bool Warpable
    m_Warpable : boolean;
    // public bool ImmuneToPoison
    m_ImmuneToPoison : boolean;
    // public bool ReselectIfLimboed
    m_ReselectIfLimboed : boolean;
    // public bool RejoinTeamIfLimboed
    m_RejoinTeamIfLimboed : boolean;
    // public bool Slaved
    m_Slaved : boolean;
    // public InfantryTypeClass * Enslaves
    m_Enslaves : InfantryTypeClass;
    // public int SlavesNumber
    m_SlavesNumber : number;
    // public int SlaveRegenRate
    m_SlaveRegenRate : number;
    // public int SlaveReloadRate
    m_SlaveReloadRate : number;
    // public int OpenTransportWeapon
    m_OpenTransportWeapon : number;
    // public bool Spawned
    m_Spawned : boolean;
    // public AircraftTypeClass * Spawns
    m_Spawns : AircraftTypeClass;
    // public int SpawnsNumber
    m_SpawnsNumber : number;
    // public int SpawnRegenRate
    m_SpawnRegenRate : number;
    // public int SpawnReloadRate
    m_SpawnReloadRate : number;
    // public bool MissileSpawn
    m_MissileSpawn : boolean;
    // public bool Underwater
    m_Underwater : boolean;
    // public bool BalloonHover
    m_BalloonHover : boolean;
    // public int SuppressionThreshold
    m_SuppressionThreshold : number;
    // public int JumpjetTurnRate
    m_JumpjetTurnRate : number;
    // public int JumpjetSpeed
    m_JumpjetSpeed : number;
    // public float JumpjetClimb
    m_JumpjetClimb : number;
    // public float JumpjetCrash
    m_JumpjetCrash : number;
    // public int JumpjetHeight
    m_JumpjetHeight : number;
    // public float JumpjetAccel
    m_JumpjetAccel : number;
    // public float JumpjetWobbles
    m_JumpjetWobbles : number;
    // public bool JumpjetNoWobbles
    m_JumpjetNoWobbles : boolean;
    // public int JumpjetDeviation
    m_JumpjetDeviation : number;
    // public bool JumpJet
    m_JumpJet : boolean;
    // public bool Crashable
    m_Crashable : boolean;
    // public bool ConsideredAircraft
    m_ConsideredAircraft : boolean;
    // public bool Organic
    m_Organic : boolean;
    // public bool NoShadow
    m_NoShadow : boolean;
    // public bool CanPassiveAquire
    m_CanPassiveAquire : boolean;
    // public bool CanRetaliate
    m_CanRetaliate : boolean;
    // public bool RequiresStolenThirdTech
    m_RequiresStolenThirdTech : boolean;
    // public bool RequiresStolenSovietTech
    m_RequiresStolenSovietTech : boolean;
    // public bool RequiresStolenAlliedTech
    m_RequiresStolenAlliedTech : boolean;
    // public unsigned long RequiredHouses
    m_RequiredHouses : number;
    // public unsigned long ForbiddenHouses
    m_ForbiddenHouses : number;
    // public unsigned long SecretHouses
    m_SecretHouses : number;
    // public bool UseBuffer
    m_UseBuffer : boolean;
    // public CoordStruct SecondSpawnOffset
    m_SecondSpawnOffset : CoordStruct;
    // public bool IsSelectableCombatant
    m_IsSelectableCombatant : boolean;
    // public bool Accelerates
    m_Accelerates : boolean;
    // public bool DisableVoxelCache
    m_DisableVoxelCache : boolean;
    // public bool DisableShadowCache
    m_DisableShadowCache : boolean;
    // public int ZFudgeCliff
    m_ZFudgeCliff : number;
    // public int ZFudgeColumn
    m_ZFudgeColumn : number;
    // public int ZFudgeTunnel
    m_ZFudgeTunnel : number;
    // public int ZFudgeBridge
    m_ZFudgeBridge : number;
    // public char[32] PaletteFile
    m_PaletteFile : string;
    // no... idea....
    // public DynamicVectorClass<ColorScheme *> * Palette
    m_Palette : DynamicVectorClass<ColorScheme>;
    // public unsigned long align_DF4
    m_align_DF4 : number;
}
// WeaponStruct
class WeaponStruct
{
    // public WeaponStruct()
    constructor();
    // public bool operator==(WeaponStruct const& pWeap) const
    op_Equality(pWeap_0 : WeaponStruct) : boolean;
    // public WeaponTypeClass * WeaponType
    m_WeaponType : WeaponTypeClass;
    // public CoordStruct FLH
    m_FLH : CoordStruct;
    // public int BarrelLength
    m_BarrelLength : number;
    // public int BarrelThickness
    m_BarrelThickness : number;
    // public bool TurretLocked
    m_TurretLocked : boolean;
}
// ---
// WeaponTypeClass
class WeaponTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public WeaponTypeClass(char const * pID = nullptr)
    constructor(pID_0 : string);
    // Array
    // public static WeaponTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : WeaponTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static WeaponTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : WeaponTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // AbstractTypeClass
    // public void CalculateSpeed()
    CalculateSpeed() : void;
    // public ThreatType AllowedThreats()
    AllowedThreats() : ThreatType;
    // public static AbstractType const AbsID = AbstractType::WeaponType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<WeaponTypeClass *>, 8942952> const Array = 0x887568u
    static s_Array : DynamicVectorClass<WeaponTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int AmbientDamage
    m_AmbientDamage : number;
    // public int Burst
    m_Burst : number;
    // public BulletTypeClass * Projectile
    m_Projectile : BulletTypeClass;
    // public int Damage
    m_Damage : number;
    // public int Speed
    m_Speed : number;
    // public WarheadTypeClass * Warhead
    m_Warhead : WarheadTypeClass;
    // public int ROF
    m_ROF : number;
    // int(256 * ini value)
    // public int Range
    m_Range : number;
    // int(256 * ini value)
    // public int MinimumRange
    m_MinimumRange : number;
    // public AnimTypeClass * OccupantAnim
    m_OccupantAnim : AnimTypeClass;
    // public AnimTypeClass * AssaultAnim
    m_AssaultAnim : AnimTypeClass;
    // public AnimTypeClass * OpenToppedAnim
    m_OpenToppedAnim : AnimTypeClass;
    // public ParticleSystemTypeClass * AttachedParticleSystem
    m_AttachedParticleSystem : ParticleSystemTypeClass;
    // public ColorStruct LaserInnerColor
    m_LaserInnerColor : ColorStruct;
    // public ColorStruct LaserOuterColor
    m_LaserOuterColor : ColorStruct;
    // public ColorStruct LaserOuterSpread
    m_LaserOuterSpread : ColorStruct;
    // public bool UseFireParticles
    m_UseFireParticles : boolean;
    // public bool UseSparkParticles
    m_UseSparkParticles : boolean;
    // public bool OmniFire
    m_OmniFire : boolean;
    // public bool DistributedWeaponFire
    m_DistributedWeaponFire : boolean;
    // public bool IsRailgun
    m_IsRailgun : boolean;
    // public bool Lobber
    m_Lobber : boolean;
    // public bool Bright
    m_Bright : boolean;
    // public bool IsSonic
    m_IsSonic : boolean;
    // public bool Spawner
    m_Spawner : boolean;
    // public bool LimboLaunch
    m_LimboLaunch : boolean;
    // public bool DecloakToFire
    m_DecloakToFire : boolean;
    // public bool CellRangefinding
    m_CellRangefinding : boolean;
    // public bool FireOnce
    m_FireOnce : boolean;
    // public bool NeverUse
    m_NeverUse : boolean;
    // public bool RevealOnFire
    m_RevealOnFire : boolean;
    // public bool TerrainFire
    m_TerrainFire : boolean;
    // public bool SabotageCursor
    m_SabotageCursor : boolean;
    // public bool MigAttackCursor
    m_MigAttackCursor : boolean;
    // public bool DisguiseFireOnly
    m_DisguiseFireOnly : boolean;
    // public int DisguiseFakeBlinkTime
    m_DisguiseFakeBlinkTime : number;
    // public bool InfiniteMindControl
    m_InfiniteMindControl : boolean;
    // public bool FireWhileMoving
    m_FireWhileMoving : boolean;
    // public bool DrainWeapon
    m_DrainWeapon : boolean;
    // public bool FireInTransport
    m_FireInTransport : boolean;
    // public bool Suicide
    m_Suicide : boolean;
    // public bool TurboBoost
    m_TurboBoost : boolean;
    // public bool Supress
    m_Supress : boolean;
    // public bool Camera
    m_Camera : boolean;
    // public bool Charges
    m_Charges : boolean;
    // public bool IsLaser
    m_IsLaser : boolean;
    // public bool DiskLaser
    m_DiskLaser : boolean;
    // public bool IsLine
    m_IsLine : boolean;
    // public bool IsBigLaser
    m_IsBigLaser : boolean;
    // public bool IsHouseColor
    m_IsHouseColor : boolean;
    // public char LaserDuration
    m_LaserDuration : number;
    // public bool IonSensitive
    m_IonSensitive : boolean;
    // public bool AreaFire
    m_AreaFire : boolean;
    // public bool IsElectricBolt
    m_IsElectricBolt : boolean;
    // public bool DrawBoltAsLaser
    m_DrawBoltAsLaser : boolean;
    // public bool IsAlternateColor
    m_IsAlternateColor : boolean;
    // public bool IsRadBeam
    m_IsRadBeam : boolean;
    // public bool IsRadEruption
    m_IsRadEruption : boolean;
    // public int RadLevel
    m_RadLevel : number;
    // public bool IsMagBeam
    m_IsMagBeam : boolean;
    // sound indices
    // public TypeList<int> Report
    m_Report : TypeList<number>;
    // public char[28] __Report
    m___Report : string;
    // sound indices
    // public TypeList<int> DownReport
    m_DownReport : TypeList<number>;
    // public char[28] __DownReport
    m___DownReport : string;
    // public TypeList<AnimTypeClass *> Anim
    m_Anim : TypeList<AnimTypeClass>;
    // public char[28] __Anim
    m___Anim : string;
}
// ---
// BulletTypeClass
class BulletTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public BulletTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static BulletTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : BulletTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static BulletTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : BulletTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // AbstractTypeClass
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // public bool Rotates() const
    Rotates() : boolean;
    // public void SetScaledSpawnDelay(int delay)
    SetScaledSpawnDelay(delay_0 : number) : void;
    // public BulletClass * CreateBullet(AbstractClass * Target, TechnoClass * Owner, int Damage, WarheadTypeClass * WH, int Speed, bool Bright)
    CreateBullet(Target_0 : AbstractClass, Owner_1 : TechnoClass, Damage_2 : number, WH_3 : WarheadTypeClass, Speed_4 : number, Bright_5 : boolean) : BulletClass;
    // public static AbstractType const AbsID = AbstractType::BulletType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<BulletTypeClass *>, 11025536> const Array = 0xA83C80u
    static s_Array : DynamicVectorClass<BulletTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public bool Airburst
    m_Airburst : boolean;
    // public bool Floater
    m_Floater : boolean;
    // public bool SubjectToCliffs
    m_SubjectToCliffs : boolean;
    // public bool SubjectToElevation
    m_SubjectToElevation : boolean;
    // public bool SubjectToWalls
    m_SubjectToWalls : boolean;
    // public bool VeryHigh
    m_VeryHigh : boolean;
    // public bool Shadow
    m_Shadow : boolean;
    // public bool Arcing
    m_Arcing : boolean;
    // public bool Dropping
    m_Dropping : boolean;
    // public bool Level
    m_Level : boolean;
    // public bool Inviso
    m_Inviso : boolean;
    // public bool Proximity
    m_Proximity : boolean;
    // public bool Ranged
    m_Ranged : boolean;
    // actually has opposite meaning of Rotates. false means Rotates=yes.
    // public bool NoRotate
    m_NoRotate : boolean;
    // public bool Inaccurate
    m_Inaccurate : boolean;
    // public bool FlakScatter
    m_FlakScatter : boolean;
    // public bool AA
    m_AA : boolean;
    // public bool AG
    m_AG : boolean;
    // public bool Degenerates
    m_Degenerates : boolean;
    // public bool Bouncy
    m_Bouncy : boolean;
    // public bool AnimPalette
    m_AnimPalette : boolean;
    // public bool FirersPalette
    m_FirersPalette : boolean;
    // public int Cluster
    m_Cluster : number;
    // public WeaponTypeClass * AirburstWeapon
    m_AirburstWeapon : WeaponTypeClass;
    // public WeaponTypeClass * ShrapnelWeapon
    m_ShrapnelWeapon : WeaponTypeClass;
    // public int ShrapnelCount
    m_ShrapnelCount : number;
    // public int DetonationAltitude
    m_DetonationAltitude : number;
    // public bool Vertical
    m_Vertical : boolean;
    // public double Elasticity
    m_Elasticity : number;
    // public int Acceleration
    m_Acceleration : number;
    // public ColorScheme * Color
    m_Color : ColorScheme;
    // public AnimTypeClass * Trailer
    m_Trailer : AnimTypeClass;
    // public int ROT
    m_ROT : number;
    // public int CourseLockDuration
    m_CourseLockDuration : number;
    // public int SpawnDelay
    m_SpawnDelay : number;
    // public int ScaledSpawnDelay
    m_ScaledSpawnDelay : number;
    // public bool Scalable
    m_Scalable : boolean;
    // public int Arm
    m_Arm : number;
    // public unsigned char AnimLow
    m_AnimLow : number;
    // public unsigned char AnimHigh
    m_AnimHigh : number;
    // public unsigned char AnimRate
    m_AnimRate : number;
    // public bool Flat
    m_Flat : boolean;
}
// forward declarations
// BulletClass
class BulletClass
    extends ObjectClass
{
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // BulletClass
    // public virtual unsigned char GetAnimFrame() const
    GetAnimFrame() : number;
    // public virtual void SetTarget(AbstractClass * pTarget)
    SetTarget(pTarget_0 : AbstractClass) : void;
    // public virtual bool MoveTo(CoordStruct const& where, Vector3D<double> const& velocity)
    MoveTo(where_0 : CoordStruct, velocity_1 : Vector3D) : boolean;
    // non-virtual
    // after CoCreateInstance creates a bullet, this configures it
    // public void Construct(BulletTypeClass * pType, AbstractClass * pTarget, TechnoClass * pOwner, int damage, WarheadTypeClass * pWarhead, int speed, bool bright)
    Construct(pType_0 : BulletTypeClass, pTarget_1 : AbstractClass, pOwner_2 : TechnoClass, damage_3 : number, pWarhead_4 : WarheadTypeClass, speed_5 : number, bright_6 : boolean) : void;
    // calls Detonate with the appropriate coords
    // public void Explode(bool destroy = false)
    Explode(destroy_0 : boolean) : void;
    // detonate the bullet at specific coords
    // public void Detonate(CoordStruct const& coords)
    Detonate(coords_0 : CoordStruct) : void;
    // spawns off the proper amount of shrapnel projectiles
    // public void Shrapnel()
    Shrapnel() : void;
    // public static void ApplyRadiationToCell(CellStruct cell, int radius, int amount)
    static ApplyRadiationToCell(cell_0 : CellStruct, radius_1 : number, amount_2 : number) : void;
    // this bullet will miss and hit the ground instead.
    // if the original target is in air, it will disappear.
    // public void LoseTarget()
    LoseTarget() : void;
    // public bool IsHoming() const
    IsHoming() : boolean;
    // public void SetWeaponType(WeaponTypeClass * weapon)
    SetWeaponType(weapon_0 : WeaponTypeClass) : void;
    // public WeaponTypeClass * GetWeaponType() const
    GetWeaponType() : WeaponTypeClass;
    // only called in UnitClass::Fire if Type->Scalable
    // public void InitScalable()
    InitScalable() : void;
    // call only after the target, args, etc., have been set
    // public void NukeMaker()
    NukeMaker() : void;
    // helpers
    // public CoordStruct GetTargetCoords() const
    GetTargetCoords() : CoordStruct;
    // public static AbstractType const AbsID = AbstractType::Bullet
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<BulletClass *>, 11070784> const Array = 0xA8ED40u
    static s_Array : DynamicVectorClass<BulletClass>;
    // public static reference<DynamicVectorClass<BulletClass *>, 9035288, 0> const ScalableBullets = 0x89DE18u
    static s_ScalableBullets : DynamicVectorClass<BulletClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public BulletTypeClass * Type
    m_Type : BulletTypeClass;
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public bool unknown_B4
    m_unknown_B4 : boolean;
    // public BulletData Data
    m_Data : BulletData;
    // public bool Bright
    m_Bright : boolean;
    // public unsigned long unknown_E4
    m_unknown_E4 : number;
    // public Vector3D<double> Velocity
    m_Velocity : Vector3D;
    // public unsigned long unknown_100
    m_unknown_100 : number;
    // public bool unknown_104
    m_unknown_104 : boolean;
    // public bool CourseLock
    m_CourseLock : boolean;
    // public int CourseLockCounter
    m_CourseLockCounter : number;
    // public AbstractClass * Target
    m_Target : AbstractClass;
    // public int Speed
    m_Speed : number;
    // public int InheritedColor
    m_InheritedColor : number;
    // public unsigned long unknown_118
    m_unknown_118 : number;
    // public unsigned long unknown_11C
    m_unknown_11C : number;
    // public double unknown_120
    m_unknown_120 : number;
    // public WarheadTypeClass * WH
    m_WH : WarheadTypeClass;
    // public unsigned char AnimFrame
    m_AnimFrame : number;
    // public unsigned char AnimRateCounter
    m_AnimRateCounter : number;
    // public WeaponTypeClass * WeaponType
    m_WeaponType : WeaponTypeClass;
    // public CoordStruct SourceCoords
    m_SourceCoords : CoordStruct;
    // public CoordStruct TargetCoords
    m_TargetCoords : CoordStruct;
    // public CellStruct LastMapCoords
    m_LastMapCoords : CellStruct;
    // public int DamageMultiplier
    m_DamageMultiplier : number;
    // public AnimClass * NextAnim
    m_NextAnim : AnimClass;
    // public bool SpawnNextAnim
    m_SpawnNextAnim : boolean;
    // public int Range
    m_Range : number;
}
// forward declarations
// RadioClass
class RadioClass
    extends MissionClass
{
    // Constructor
    // public RadioClass()
    constructor();
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // these are oogly, westwood themselves admitted it, so it's probably even more of a wtf than the rest
    // public virtual RadioCommand SendToFirstLink(RadioCommand command)
    SendToFirstLink(command_0 : RadioCommand) : RadioCommand;
    // public virtual RadioCommand SendCommand(RadioCommand command, TechnoClass * pRecipient)
    SendCommand(command_0 : RadioCommand, pRecipient_1 : TechnoClass) : RadioCommand;
    // public virtual RadioCommand SendCommandWithData(RadioCommand command, AbstractClass *& pInOut, TechnoClass * pRecipient)
    SendCommandWithData(command_0 : RadioCommand, pInOut_1 : AbstractClass, pRecipient_2 : TechnoClass) : RadioCommand;
    // public virtual void SendToEachLink(RadioCommand command)
    SendToEachLink(command_0 : RadioCommand) : void;
    // get specific link
    // public TechnoClass * const& GetNthLink(int idx = 0) const
    GetNthLink(idx_0 : number) : TechnoClass;
    // whether any link is pLink
    // public bool ContainsLink(TechnoClass const * pLink) const
    ContainsLink(pLink_0 : TechnoClass) : boolean;
    // note: null pointers will always return -1
    // public int FindLinkIndex(TechnoClass const * pLink) const
    FindLinkIndex(pLink_0 : TechnoClass) : number;
    // iow: not full
    // public bool HasFreeLink() const
    HasFreeLink() : boolean;
    // iow: not full; consider pIgnore's link empty
    // public bool HasFreeLink(TechnoClass const * pIgnore) const
    HasFreeLink(pIgnore_0 : TechnoClass) : boolean;
    // iow. at least one link used
    // public bool HasAnyLink() const
    HasAnyLink() : boolean;
    // resizes the vector and nulls the new elements
    // public void SetLinkCount(int count)
    SetLinkCount(count_0 : number) : void;
    // new command updates these
    // public RadioCommand[3] LastCommands
    m_LastCommands : RadioCommand;
    // Docked units etc
    // public VectorClass<TechnoClass *> RadioLinks
    m_RadioLinks : VectorClass<TechnoClass>;
    // public char[16] __RadioLinks
    m___RadioLinks : string;
}
// forward declarations
// MissionClass
class MissionClass
    extends ObjectClass
{
    // Constructor
    // public MissionClass()
    constructor();
    // MissionClass
    // public virtual bool QueueMission(Mission mission, bool start_mission)
    QueueMission(mission_0 : Mission, start_mission_1 : boolean) : boolean;
    // public virtual bool NextMission()
    NextMission() : boolean;
    // public virtual void ForceMission(Mission mission)
    ForceMission(mission_0 : Mission) : void;
    // public virtual void Override_Mission(Mission mission, AbstractClass * target, AbstractClass * destination)
    Override_Mission(mission_0 : Mission, target_1 : AbstractClass, destination_2 : AbstractClass) : void;
    // public virtual bool Mission_Revert()
    Mission_Revert() : boolean;
    // public virtual bool MissionIsOverriden() const
    MissionIsOverriden() : boolean;
    // public virtual bool ReadyToNextMission() const
    ReadyToNextMission() : boolean;
    // public virtual int Mission_Sleep()
    Mission_Sleep() : number;
    // public virtual int Mission_Harmless()
    Mission_Harmless() : number;
    // public virtual int Mission_Ambush()
    Mission_Ambush() : number;
    // public virtual int Mission_Attack()
    Mission_Attack() : number;
    // public virtual int Mission_Capture()
    Mission_Capture() : number;
    // public virtual int Mission_Eaten()
    Mission_Eaten() : number;
    // public virtual int Mission_Guard()
    Mission_Guard() : number;
    // public virtual int Mission_AreaGuard()
    Mission_AreaGuard() : number;
    // public virtual int Mission_Harvest()
    Mission_Harvest() : number;
    // public virtual int Mission_Hunt()
    Mission_Hunt() : number;
    // public virtual int Mission_Move()
    Mission_Move() : number;
    // public virtual int Mission_Retreat()
    Mission_Retreat() : number;
    // public virtual int Mission_Return()
    Mission_Return() : number;
    // public virtual int Mission_Stop()
    Mission_Stop() : number;
    // public virtual int Mission_Unload()
    Mission_Unload() : number;
    // public virtual int Mission_Enter()
    Mission_Enter() : number;
    // public virtual int Mission_Construction()
    Mission_Construction() : number;
    // public virtual int Mission_Selling()
    Mission_Selling() : number;
    // public virtual int Mission_Repair()
    Mission_Repair() : number;
    // public virtual int Mission_Missile()
    Mission_Missile() : number;
    // public virtual int Mission_Open()
    Mission_Open() : number;
    // public virtual int Mission_Rescue()
    Mission_Rescue() : number;
    // public virtual int Mission_Patrol()
    Mission_Patrol() : number;
    // public virtual int Mission_ParaDropApproach()
    Mission_ParaDropApproach() : number;
    // public virtual int Mission_ParaDropOverfly()
    Mission_ParaDropOverfly() : number;
    // public virtual int Mission_Wait()
    Mission_Wait() : number;
    // public virtual int Mission_SpyPlaneApproach()
    Mission_SpyPlaneApproach() : number;
    // public virtual int Mission_SpyPlaneOverfly()
    Mission_SpyPlaneOverfly() : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public Mission CurrentMission
    m_CurrentMission : Mission;
    // public Mission SuspendedMission
    m_SuspendedMission : Mission;
    // public Mission QueuedMission
    m_QueuedMission : Mission;
    // public bool unknown_bool_B8
    m_unknown_bool_B8 : boolean;
    // public int MissionStatus
    m_MissionStatus : number;
    // in frames
    // public int CurrentMissionStartTime
    m_CurrentMissionStartTime : number;
    // public int MissionAccumulateTime
    m_MissionAccumulateTime : number;
    // public CDTimerClass UpdateTimer
    m_UpdateTimer : CDTimerClass;
    // public char[12] __UpdateTimer
    m___UpdateTimer : string;
}
// forward declarations
// InfantryTypeClass
class InfantryTypeClass
    extends TechnoTypeClass
{
    // Constructor
    // public InfantryTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static InfantryTypeClass * Find(char const * pID)
    static Find(pID_0 : string | any) : InfantryTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string | any) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::InfantryType
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7EB610
    static s_AbsVTable : number;
    // Array
    // public static constant_ptr<DynamicVectorClass<InfantryTypeClass *>, 11068232> const Array = 0xA8E348u
    static s_Array : DynamicVectorClass<InfantryTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public PipIndex Pip
    m_Pip : PipIndex;
    // public PipIndex OccupyPip
    m_OccupyPip : PipIndex;
    // public WeaponStruct OccupyWeapon
    m_OccupyWeapon : WeaponStruct;
    // public WeaponStruct EliteOccupyWeapon
    m_EliteOccupyWeapon : WeaponStruct;
    // public SequenceStruct * Sequence
    m_Sequence : any;
    // public int FireUp
    m_FireUp : number;
    // public int FireProne
    m_FireProne : number;
    // public int SecondaryFire
    m_SecondaryFire : number;
    // public int SecondaryProne
    m_SecondaryProne : number;
    // public TypeList<AnimTypeClass *> DeadBodies
    m_DeadBodies : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> DeathAnims
    m_DeathAnims : TypeList<AnimTypeClass>;
    // public TypeList<int> VoiceComment
    m_VoiceComment : TypeList<number>;
    // public int EnterWaterSound
    m_EnterWaterSound : number;
    // public int LeaveWaterSound
    m_LeaveWaterSound : number;
    // public bool Cyborg
    m_Cyborg : boolean;
    // public bool NotHuman
    m_NotHuman : boolean;
    // used for the bomb attack cursor...
    // public bool Ivan
    m_Ivan : boolean;
    // public int DirectionDistance
    m_DirectionDistance : number;
    // public bool Occupier
    m_Occupier : boolean;
    // public bool Assaulter
    m_Assaulter : boolean;
    // public int HarvestRate
    m_HarvestRate : number;
    // public bool Fearless
    m_Fearless : boolean;
    // public bool Crawls
    m_Crawls : boolean;
    // public bool Infiltrate
    m_Infiltrate : boolean;
    // public bool Fraidycat
    m_Fraidycat : boolean;
    // public bool TiberiumProof
    m_TiberiumProof : boolean;
    // public bool Civilian
    m_Civilian : boolean;
    // public bool C4
    m_C4 : boolean;
    // public bool Engineer
    m_Engineer : boolean;
    // public bool Agent
    m_Agent : boolean;
    // public bool Thief
    m_Thief : boolean;
    // public bool VehicleThief
    m_VehicleThief : boolean;
    // public bool Doggie
    m_Doggie : boolean;
    // public bool Deployer
    m_Deployer : boolean;
    // public bool DeployedCrushable
    m_DeployedCrushable : boolean;
    // public bool UseOwnName
    m_UseOwnName : boolean;
    // public bool JumpJetTurn
    m_JumpJetTurn : boolean;
}
// The AbstractClass is the base class of all game objects.
// CellClass
class CellClass
    extends AbstractClass
{
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // get content objects
    // public TechnoClass * FindTechnoNearestTo(Point2D const& offsetPixel, bool alt, TechnoClass const * pExcludeThis = nullptr) const
    FindTechnoNearestTo(offsetPixel_0 : Point2D, alt_1 : boolean, pExcludeThis_2 : TechnoClass) : TechnoClass;
    // public ObjectClass * FindObjectOfType(AbstractType abs, bool alt) const
    FindObjectOfType(abs_0 : AbstractType, alt_1 : boolean) : ObjectClass;
    // public BuildingClass * GetBuilding() const
    GetBuilding() : BuildingClass;
    // public UnitClass * GetUnit(bool alt) const
    GetUnit(alt_0 : boolean) : UnitClass;
    // public InfantryClass * GetInfantry(bool alt) const
    GetInfantry(alt_0 : boolean) : InfantryClass;
    // public AircraftClass * GetAircraft(bool alt) const
    GetAircraft(alt_0 : boolean) : AircraftClass;
    // public TerrainClass * GetTerrain(bool alt) const
    GetTerrain(alt_0 : boolean) : TerrainClass;
    // craziest thing... first iterates Content looking to Aircraft,
    // failing that, calls FindTechnoNearestTo,
    // if that fails too, reiterates Content looking for Terrain
    // public ObjectClass * GetSomeObject(CoordStruct const& coords, bool alt) const
    GetSomeObject(coords_0 : CoordStruct, alt_1 : boolean) : ObjectClass;
    // misc
    // public void SetWallOwner()
    SetWallOwner() : void;
    // public void IncreaseShroudCounter()
    IncreaseShroudCounter() : void;
    // public void ReduceShroudCounter()
    ReduceShroudCounter() : void;
    // public bool IsShrouded() const
    IsShrouded() : boolean;
    // public void Unshroud()
    Unshroud() : void;
    // public RectangleStruct * ShapeRect(RectangleStruct * pRet)
    ShapeRect(pRet_0 : RectangleStruct) : RectangleStruct;
    // public bool IsFogged()
    IsFogged() : boolean;
    // public void FogCell()
    FogCell() : void;
    // public void CleanFog()
    CleanFog() : void;
    // public void ClearFoggedObjects()
    ClearFoggedObjects() : void;
    // adjusts LAT
    // public void SetupLAT()
    SetupLAT() : void;
    // Recalculates cell attributes.
    // Checks for nearby cliff impassability, calls SetupLAT(), sets up TubeClass if tunnel, cell anim if attached etc.
    // Set cellLevel to -1 if you wish to not change it.
    // public void RecalcAttributes(int cellLevel)
    RecalcAttributes(cellLevel_0 : number) : void;
    // public void BlowUpBridge()
    BlowUpBridge() : void;
    // public bool CanThisExistHere(SpeedType SpeedType, BuildingTypeClass * pObject, HouseClass * pOwner) const
    CanThisExistHere(SpeedType_0 : SpeedType, pObject_1 : BuildingTypeClass, pOwner_2 : HouseClass) : boolean;
    // those unks are passed to TechnoClass::Scatter in that same order
    // public void ScatterContent(CoordStruct const& crd, bool ignoreMission, bool ignoreDestination, bool alt)
    ScatterContent(crd_0 : CoordStruct, ignoreMission_1 : boolean, ignoreDestination_2 : boolean, alt_3 : boolean) : void;
    // public CellClass * GetNeighbourCell(FacingType facing) const
    GetNeighbourCell(facing_0 : FacingType) : CellClass;
    // called whenever anything moves, first to remove threat from source cell, second time to add threat to dest cell
    // public void UpdateThreat(unsigned int SourceHouse, int ThreatLevel)
    UpdateThreat(SourceHouse_0 : number, ThreatLevel_1 : number) : void;
    // public void CollectCrate(FootClass * pCollector)
    CollectCrate(pCollector_0 : FootClass) : void;
    // public void ProcessColourComponents(int * arg0, int * pIntensity, int * pAmbient, int * a5, int * a6, int * tintR, int * tintG, int * tintB)
    ProcessColourComponents(arg0_0 : number, pIntensity_1 : number, pAmbient_2 : number, a5_3 : number, a6_4 : number, tintR_5 : number, tintG_6 : number, tintB_7 : number) : void;
    // public TubeClass * GetTunnel()
    GetTunnel() : any;
    // public RectangleStruct * GetContainingRect(RectangleStruct * dest) const
    GetContainingRect(dest_0 : RectangleStruct) : RectangleStruct;
    // don't laugh, it returns the uiname of contained tiberium... which nobody ever sets
    // public wchar_t const * GetUIName() const
    GetUIName() : number;
    // returns whether a cell behaves as if it contained overlay (for gates and wall towers)
    // public bool ConnectsToOverlay(int idxOverlay = -1, int direction = -1) const
    ConnectsToOverlay(idxOverlay_0 : number, direction_1 : number) : boolean;
    // returns the tiberium's index in OverlayTypes
    // public int GetContainedTiberiumIndex() const
    GetContainedTiberiumIndex() : number;
    // public int GetContainedTiberiumValue() const
    GetContainedTiberiumValue() : number;
    // public bool SpreadTiberium(bool forced)
    SpreadTiberium(forced_0 : boolean) : boolean;
    // add or create tiberium of the specified type
    // public bool IncreaseTiberium(int idxTiberium, int amount)
    IncreaseTiberium(idxTiberium_0 : number, amount_1 : number) : boolean;
    // decreases thze tiberium in the cell
    // public void ReduceTiberium(int amount)
    ReduceTiberium(amount_0 : number) : void;
    // public bool CanTiberiumGerminate(TiberiumClass * tib)
    CanTiberiumGerminate(tib_0 : TiberiumClass) : boolean;
    // public void SetMapCoords(CoordStruct const& coords)
    SetMapCoords(coords_0 : CoordStruct) : void;
    // public int GetFloorHeight(Point2D const& subcoords) const
    GetFloorHeight(subcoords_0 : Point2D) : number;
    // Factors in cell height from ramps, level etc.
    // public CoordStruct * GetCellCoords(CoordStruct * pOutBuffer) const
    GetCellCoords(pOutBuffer_0 : CoordStruct) : CoordStruct;
    // public CoordStruct GetCellCoords() const
    GetCellCoords() : CoordStruct;
    // public void ActivateVeins()
    ActivateVeins() : void;
    // cloak generators
    // public bool CloakGen_InclHouse(unsigned int idx) const
    CloakGen_InclHouse(idx_0 : number) : boolean;
    // public void CloakGen_AddHouse(unsigned int idx)
    CloakGen_AddHouse(idx_0 : number) : void;
    // public void CloakGen_RemHouse(unsigned int idx)
    CloakGen_RemHouse(idx_0 : number) : void;
    // unused, returns 0 if that house doesn't have cloakgens covering this cell or Player has sensors over this cell
    // public bool DrawObjectsCloaked(int OwnerHouseIdx) const
    DrawObjectsCloaked(OwnerHouseIdx_0 : number) : boolean;
    // sensors
    // public bool Sensors_InclHouse(unsigned int idx) const
    Sensors_InclHouse(idx_0 : number) : boolean;
    // public void Sensors_AddOfHouse(unsigned int idx)
    Sensors_AddOfHouse(idx_0 : number) : void;
    // public void Sensors_RemOfHouse(unsigned int idx)
    Sensors_RemOfHouse(idx_0 : number) : void;
    // disguise sensors
    // public bool DisguiseSensors_InclHouse(unsigned int idx) const
    DisguiseSensors_InclHouse(idx_0 : number) : boolean;
    // public void DisguiseSensors_AddOfHouse(unsigned int idx)
    DisguiseSensors_AddOfHouse(idx_0 : number) : void;
    // public void DisguiseSensors_RemOfHouse(unsigned int idx)
    DisguiseSensors_RemOfHouse(idx_0 : number) : void;
    // Rad Sites
    // public void SetRadSite(RadSiteClass * pRad)
    SetRadSite(pRad_0 : RadSiteClass) : void;
    // public RadSiteClass * GetRadSite() const
    GetRadSite() : RadSiteClass;
    // public bool IsRadiated() const
    IsRadiated() : boolean;
    // public int GetRadLevel() const
    GetRadLevel() : number;
    // public void RadLevel_Increase(double amount)
    RadLevel_Increase(amount_0 : number) : void;
    // public void RadLevel_Decrease(double amount)
    RadLevel_Decrease(amount_0 : number) : void;
    // helper
    // public bool ContainsBridge() const
    ContainsBridge() : boolean;
    // public bool ContainsBridgeEx() const
    ContainsBridgeEx() : boolean;
    // helper mimicking game's behaviour
    // public ObjectClass * GetContent() const
    GetContent() : ObjectClass;
    // public int GetLevel() const
    GetLevel() : number;
    // public bool Tile_Is_Tunnel() const
    Tile_Is_Tunnel() : boolean;
    // public bool Tile_Is_Water() const
    Tile_Is_Water() : boolean;
    // public bool Tile_Is_Blank() const
    Tile_Is_Blank() : boolean;
    // public bool Tile_Is_Ramp() const
    Tile_Is_Ramp() : boolean;
    // public bool Tile_Is_Cliff() const
    Tile_Is_Cliff() : boolean;
    // public bool Tile_Is_Shore() const
    Tile_Is_Shore() : boolean;
    // public bool Tile_Is_Wet() const
    Tile_Is_Wet() : boolean;
    // public bool Tile_Is_MiscPave() const
    Tile_Is_MiscPave() : boolean;
    // public bool Tile_Is_Pave() const
    Tile_Is_Pave() : boolean;
    // public bool Tile_Is_DirtRoad() const
    Tile_Is_DirtRoad() : boolean;
    // public bool Tile_Is_PavedRoad() const
    Tile_Is_PavedRoad() : boolean;
    // public bool Tile_Is_PavedRoadEnd() const
    Tile_Is_PavedRoadEnd() : boolean;
    // public bool Tile_Is_PavedRoadSlope() const
    Tile_Is_PavedRoadSlope() : boolean;
    // public bool Tile_Is_Median() const
    Tile_Is_Median() : boolean;
    // public bool Tile_Is_Bridge() const
    Tile_Is_Bridge() : boolean;
    // public bool Tile_Is_WoodBridge() const
    Tile_Is_WoodBridge() : boolean;
    // public bool Tile_Is_ClearToSandLAT() const
    Tile_Is_ClearToSandLAT() : boolean;
    // public bool Tile_Is_Green() const
    Tile_Is_Green() : boolean;
    // public bool Tile_Is_NotWater() const
    Tile_Is_NotWater() : boolean;
    // public bool Tile_Is_DestroyableCliff() const
    Tile_Is_DestroyableCliff() : boolean;
    // public static CoordStruct Cell2Coord(CellStruct const& cell, int z = 0)
    static Cell2Coord(cell_0 : CellStruct, z_1 : number) : CoordStruct;
    // public static CellStruct Coord2Cell(CoordStruct const& crd)
    static Coord2Cell(crd_0 : CoordStruct) : CellStruct;
    // public CoordStruct FixHeight(CoordStruct crd) const
    FixHeight(crd_0 : CoordStruct) : CoordStruct;
    // helper - gets coords and fixes height for bridge
    // public CoordStruct GetCoordsWithBridge() const
    GetCoordsWithBridge() : CoordStruct;
    // public void MarkForRedraw()
    MarkForRedraw() : void;
    // public void ChainReaction()
    ChainReaction() : void;
    // public CoordStruct * FindInfantrySubposition(CoordStruct * pOutBuffer, CoordStruct const& coords, bool ignoreContents, bool alt, bool useCellCoords)
    FindInfantrySubposition(pOutBuffer_0 : CoordStruct, coords_1 : CoordStruct, ignoreContents_2 : boolean, alt_3 : boolean, useCellCoords_4 : boolean) : CoordStruct;
    // public CoordStruct FindInfantrySubposition(CoordStruct const& coords, bool ignoreContents, bool alt, bool useCellCoords)
    FindInfantrySubposition(coords_0 : CoordStruct, ignoreContents_1 : boolean, alt_2 : boolean, useCellCoords_3 : boolean) : CoordStruct;
    // public bool TryAssignJumpjet(FootClass * pObject)
    TryAssignJumpjet(pObject_0 : FootClass) : boolean;
    // public void AddContent(ObjectClass * Content, bool onBridge)
    AddContent(Content_0 : ObjectClass, onBridge_1 : boolean) : void;
    // public void RemoveContent(ObjectClass * pContent, bool onBridge)
    RemoveContent(pContent_0 : ObjectClass, onBridge_1 : boolean) : void;
    // public void ReplaceTag(TagClass * pTag)
    ReplaceTag(pTag_0 : TagClass) : void;
    // public void UpdateCellLighting()
    UpdateCellLighting() : void;
    // public void CalculateLightSourceLighting(int& nIntensity, int& nAmbient, int& Red1, int& Green1, int& Blue1, int& Red2, int& Green2, int& Blue2)
    CalculateLightSourceLighting(nIntensity_0 : number, nAmbient_1 : number, Red1_2 : number, Green1_3 : number, Blue1_4 : number, Red2_5 : number, Green2_6 : number, Blue2_7 : number) : void;
    // public void InitLightConvert(LightConvertClass * pDrawer = nullptr, int nIntensity = 0x10000, int nAmbient = 0, int Red1 = 1000, int Green1 = 1000, int Blue1 = 1000)
    InitLightConvert(pDrawer_0 : LightConvertClass, nIntensity_1 : number, nAmbient_2 : number, Red1_3 : number, Green1_4 : number, Blue1_5 : number) : void;
    // public void DrawOverlay(Point2D const& Location, RectangleStruct const& Bound)
    DrawOverlay(Location_0 : Point2D, Bound_1 : RectangleStruct) : void;
    // public void DrawOverlayShadow(Point2D const& Location, RectangleStruct const& Bound)
    DrawOverlayShadow(Location_0 : Point2D, Bound_1 : RectangleStruct) : void;
    // public bool IsClearToMove(SpeedType speedType, bool ignoreInfantry, bool ignoreVehicles, int zone, MovementZone movementZone, int level, bool isBridge)
    IsClearToMove(speedType_0 : SpeedType, ignoreInfantry_1 : boolean, ignoreVehicles_2 : boolean, zone_3 : number, movementZone_4 : MovementZone, level_5 : number, isBridge_6 : boolean) : boolean;
    // public static AbstractType const AbsID = AbstractType::Cell
    static s_AbsID : AbstractType;
    // public static int const BridgeLevels = 4
    static s_BridgeLevels : number;
    // the height of a bridge in leptons
    // see ABC5DC, AC13BC
    // public static int const BridgeHeight = BridgeLevels * Unsorted::LevelHeight
    static s_BridgeHeight : number;
    // Where on the map does this Cell lie?
    // public CellStruct MapCoords
    m_MapCoords : CellStruct;
    // public DynamicVectorClass<FoggedObjectClass *> * FoggedObjects
    m_FoggedObjects : DynamicVectorClass<FoggedObjectClass>;
    // public CellClass * BridgeOwnerCell
    m_BridgeOwnerCell : CellClass;
    // public unsigned long unknown_30
    m_unknown_30 : number;
    // public LightConvertClass * LightConvert
    m_LightConvert : LightConvertClass;
    // What tile is this Cell?
    // public int IsoTileTypeIndex
    m_IsoTileTypeIndex : number;
    // The cell tag
    // public TagClass * AttachedTag
    m_AttachedTag : TagClass;
    // The building type that provides the rubble image
    // public BuildingTypeClass * Rubble
    m_Rubble : BuildingTypeClass;
    // What Overlay lies on this Cell?
    // public int OverlayTypeIndex
    m_OverlayTypeIndex : number;
    // What Smudge lies on this Cell?
    // public int SmudgeTypeIndex
    m_SmudgeTypeIndex : number;
    // public PassabilityType Passability
    m_Passability : PassabilityType;
    // Which House owns the wall placed in this Cell?
    // public int WallOwnerIndex
    m_WallOwnerIndex : number;
    // // Determined by finding the nearest BuildingType and taking its owner
    // public int InfantryOwnerIndex
    m_InfantryOwnerIndex : number;
    // public int AltInfantryOwnerIndex
    m_AltInfantryOwnerIndex : number;
    // public unsigned long unknown_5C
    m_unknown_5C : number;
    // public unsigned long unknown_60
    m_unknown_60 : number;
    // public unsigned long RedrawFrame
    m_RedrawFrame : number;
    // public RectangleStruct InViewportRect
    m_InViewportRect : RectangleStruct;
    // Is this cell in a cloak generator's radius? One bit per House.
    // public unsigned long CloakedByHouses
    m_CloakedByHouses : number;
    // &
    // (1 
    // <
    // <
    // HouseX->ArrayIndex) == base spacing dummy for HouseX
    // public unsigned long BaseSpacerOfHouses
    m_BaseSpacerOfHouses : number;
    // a jumpjet occupying this cell atm
    // public FootClass * Jumpjet
    m_Jumpjet : FootClass;
    // The first Object on this Cell. NextObject functions as a linked list.
    // public ObjectClass * FirstObject
    m_FirstObject : ObjectClass;
    // public ObjectClass * AltObject
    m_AltObject : ObjectClass;
    // What type of floor is this Cell?
    // public LandType LandType
    m_LandType : LandType;
    // The level of radiation on this Cell.
    // public double RadLevel
    m_RadLevel : number;
    // A pointer to the responsible RadSite.
    // public RadSiteClass * RadSite
    m_RadSite : RadSiteClass;
    // public PixelFXClass * PixelFX
    m_PixelFX : any;
    // public int OccupyHeightsCoveringMe
    m_OccupyHeightsCoveringMe : number;
    // public unsigned long Intensity
    m_Intensity : number;
    // public unsigned short Ambient
    m_Ambient : number;
    // public unsigned short Intensity_Normal
    m_Intensity_Normal : number;
    // public unsigned short Intensity_Terrain
    m_Intensity_Terrain : number;
    // public unsigned short Color1_Blue
    m_Color1_Blue : number;
    // ColorStruct      Color2; //110-114
    // public unsigned short Color2_Red
    m_Color2_Red : number;
    // public unsigned short Color2_Green
    m_Color2_Green : number;
    // public unsigned short Color2_Blue
    m_Color2_Blue : number;
    // !
    // #
    // % Westwood braindamage, can't use > 127! (movsx eax, al)
    // public short TubeIndex
    m_TubeIndex : number;
    // public char unknown_118
    m_unknown_118 : number;
    // public char IsIceGrowthAllowed
    m_IsIceGrowthAllowed : number;
    // public char Height
    m_Height : number;
    // public char Level
    m_Level : number;
    // this + 2 == cell's slope shape as reflected by PLACE.SHP
    // public unsigned char SlopeIndex
    m_SlopeIndex : number;
    // public unsigned char unknown_11D
    m_unknown_11D : number;
    // The crate type on this cell. Also indicates some other weird properties
    // public unsigned char OverlayData
    m_OverlayData : number;
    // public unsigned char SmudgeData
    m_SmudgeData : number;
    // trust me, you don't wanna know... if you do, see 0x7F4194 and cry
    // public char Visibility
    m_Visibility : number;
    // same value as above: -2: Occluded completely, -1: Visible, 0...48: frame in fog.shp or shroud.shp
    // public char Foggedness
    m_Foggedness : number;
    // number of somehow occupied cells next to this
    // public unsigned char BlockedNeighbours
    m_BlockedNeighbours : number;
    // SubOccupations - 0x1 Center 0x2 Top(Abandoned) 0x4 Right 0x8 Left 0x10 Down / Terrains
    // 0x20 Units 0x40 Aircrafts 0x80 Buildings
    // public unsigned long OccupationFlags
    m_OccupationFlags : number;
    // public unsigned long AltOccupationFlags
    m_AltOccupationFlags : number;
    // related to Flags below
    // public AltCellFlags AltFlags
    m_AltFlags : AltCellFlags;
    // public int ShroudCounter
    m_ShroudCounter : number;
    // actual count of gapgens in this cell, no idea why they need a second layer
    // public unsigned long GapsCoveringThisCell
    m_GapsCoveringThisCell : number;
    // public bool VisibilityChanged
    m_VisibilityChanged : boolean;
    // public unsigned long unknown_13C
    m_unknown_13C : number;
    // Various settings.
    // public CellFlags Flags
    m_Flags : CellFlags;
}
// forward declarations
// BuildingClass
class BuildingClass
    extends TechnoClass
{
    // Constructor
    // public BuildingClass(BuildingTypeClass * pType, HouseClass * pOwner)
    constructor(pType_0 : BuildingTypeClass, pOwner_1 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectClass
    // MissionClass
    // TechnoClass
    // public virtual void Destroyed(ObjectClass * Killer)
    Destroyed(Killer_0 : ObjectClass | any) : void;
    // public virtual bool ForceCreate(CoordStruct& coord, unsigned long dwUnk = 0)
    ForceCreate(coord_0 : CoordStruct | any, dwUnk_1 : number | any) : boolean;
    // BuildingClass
    // public virtual CellStruct FindExitCell(unsigned long dwUnk, unsigned long dwUnk2) const
    FindExitCell(dwUnk_0 : number, dwUnk2_1 : number) : CellStruct;
    // public virtual int DistanceToDockingCoord(ObjectClass * pObj) const
    DistanceToDockingCoord(pObj_0 : ObjectClass) : number;
    // public virtual void Place(bool captured)
    Place(captured_0 : boolean) : void;
    // public virtual void UpdateConstructionOptions()
    UpdateConstructionOptions() : void;
    // public virtual void Draw(Point2D const& point, RectangleStruct const& rect)
    Draw(point_0 : Point2D, rect_1 : RectangleStruct) : void;
    // public virtual DirStruct FireAngleTo(ObjectClass * pObject) const
    FireAngleTo(pObject_0 : ObjectClass) : DirStruct;
    // public virtual void Destory(unsigned long dwUnused, TechnoClass * pTechno, bool NoSurvivor, CellStruct& cell)
    Destory(dwUnused_0 : number, pTechno_1 : TechnoClass, NoSurvivor_2 : boolean, cell_3 : CellStruct) : void;
    // public virtual bool TogglePrimaryFactory()
    TogglePrimaryFactory() : boolean;
    // public virtual void SensorArrayActivate(CellStruct cell = =CellStruct::Empty)
    SensorArrayActivate(cell_0 : CellStruct) : void;
    // public virtual void SensorArrayDeactivate(CellStruct cell = =CellStruct::Empty)
    SensorArrayDeactivate(cell_0 : CellStruct) : void;
    // public virtual void DisguiseDetectorActivate(CellStruct cell = =CellStruct::Empty)
    DisguiseDetectorActivate(cell_0 : CellStruct) : void;
    // public virtual void DisguiseDetectorDeactivate(CellStruct cell = =CellStruct::Empty)
    DisguiseDetectorDeactivate(cell_0 : CellStruct) : void;
    // public virtual int AlwaysZero()
    AlwaysZero() : number;
    // non-vt
    // public void UpdateAnimations()
    UpdateAnimations() : void;
    // public int GetCurrentFrame()
    GetCurrentFrame() : number;
    // public bool IsAllFogged() const
    IsAllFogged() : boolean;
    // public void SetRallypoint(CellStruct * pTarget, bool bPlayEVA)
    SetRallypoint(pTarget_0 : CellStruct, bPlayEVA_1 : boolean) : void;
    // public void FreezeInFog(DynamicVectorClass<FoggedObjectClass *> * pFoggedArray, CellClass * pCell, bool Visible)
    FreezeInFog(pFoggedArray_0 : DynamicVectorClass<FoggedObjectClass>, pCell_1 : CellClass, Visible_2 : boolean) : void;
    // power up
    // public void GoOnline()
    GoOnline() : void;
    // public void GoOffline()
    GoOffline() : void;
    // public int GetPowerOutput() const
    GetPowerOutput() : number;
    // public int GetPowerDrain() const
    GetPowerDrain() : number;
    // Firewall aka FirestormWall
    // depending on what facings of this building
    // are connected to another FWall,
    // returns the index of the image file
    // to draw.
    // public unsigned long GetFWFlags() const
    GetFWFlags() : number;
    // public void CreateEndPost(bool arg)
    CreateEndPost(arg_0 : boolean) : void;
    // kick out content
    // public void UnloadBunker()
    UnloadBunker() : void;
    // content is dead - chronosphered away or died inside
    // public void ClearBunker()
    ClearBunker() : void;
    // kick out content, remove anims, etc... don't ask me what's different from kick out
    // public void EmptyBunker()
    EmptyBunker() : void;
    // called after destruction - CrateBeneath, resetting foundation'ed cells
    // public void AfterDestruction()
    AfterDestruction() : void;
    // destroys the specific animation (active, turret, special, etc)
    // public void DestroyNthAnim(BuildingAnimSlot Slot)
    DestroyNthAnim(Slot_0 : BuildingAnimSlot) : void;
    // public void PlayNthAnim(BuildingAnimSlot Slot, int effectDelay = 0)
    PlayNthAnim(Slot_0 : BuildingAnimSlot, effectDelay_1 : number) : void;
    // public void PlayAnim(char const * animName, BuildingAnimSlot Slot, bool Damaged, bool Garrisoned, int effectDelay = 0)
    PlayAnim(animName_0 : string, Slot_1 : BuildingAnimSlot, Damaged_2 : boolean, Garrisoned_3 : boolean, effectDelay_4 : number) : void;
    // changes between building's damaged and undamaged animations.
    // public void ToggleDamagedAnims(bool isDamaged)
    ToggleDamagedAnims(isDamaged_0 : boolean) : void;
    // when the building is switched off
    // public void DisableStuff()
    DisableStuff() : void;
    // when the building is switched on
    // public void EnableStuff()
    EnableStuff() : void;
    // when the building is warped
    // public void DisableTemporal()
    DisableTemporal() : void;
    // when the building warped back in
    // public void EnableTemporal()
    EnableTemporal() : void;
    // returns Type->SuperWeapon, if its AuxBuilding is satisfied
    // public int FirstActiveSWIdx() const
    FirstActiveSWIdx() : number;
    // public int GetShapeNumber() const
    GetShapeNumber() : number;
    // public void BeginMode(BStateType bType)
    BeginMode(bType_0 : BStateType) : void;
    // returns Type->SuperWeapon2, if its AuxBuilding is satisfied
    // public int SecondActiveSWIdx() const
    SecondActiveSWIdx() : number;
    // public void FireLaser(CoordStruct Coords)
    FireLaser(Coords_0 : CoordStruct) : void;
    // public bool IsBeingDrained() const
    IsBeingDrained() : boolean;
    // public bool UpdateBunker()
    UpdateBunker() : boolean;
    // public void KillOccupants(TechnoClass * pAssaulter)
    KillOccupants(pAssaulter_0 : TechnoClass) : void;
    // returns false if this is a gate that needs time to open, true otherwise
    // public bool MakeTraversable()
    MakeTraversable() : boolean;
    // public bool CheckFog()
    CheckFog() : boolean;
    // public Matrix3D * GetVoxelBarrelOffsetMatrix(Matrix3D& ret)
    GetVoxelBarrelOffsetMatrix(ret_0 : Matrix3D) : Matrix3D;
    // returns false if this is a gate that is closed, true otherwise
    // public bool IsTraversable() const
    IsTraversable() : boolean;
    // public int DrawInfoTipAndSpiedSelection(Point2D * pLocation, RectangleStruct * pRect) const
    DrawInfoTipAndSpiedSelection(pLocation_0 : Point2D, pRect_1 : RectangleStruct) : number;
    // helpers
    // public bool HasSuperWeapon(int index) const
    HasSuperWeapon(index_0 : number) : boolean;
    // public TechnoTypeClass * GetSecretProduction() const
    GetSecretProduction() : TechnoTypeClass;
    // public AnimClass *& GetAnim(BuildingAnimSlot slot)
    GetAnim(slot_0 : BuildingAnimSlot) : AnimClass;
    // public AnimClass * const& GetAnim(BuildingAnimSlot slot) const
    GetAnim(slot_0 : BuildingAnimSlot) : AnimClass;
    // public bool& GetAnimState(BuildingAnimSlot slot)
    GetAnimState(slot_0 : BuildingAnimSlot) : boolean;
    // public bool const& GetAnimState(BuildingAnimSlot slot) const
    GetAnimState(slot_0 : BuildingAnimSlot) : boolean;
    // public static AbstractType const AbsID = AbstractType::Building
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7E3EBC
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<BuildingClass *>, 11070272> const Array = 0xA8EB40u
    static s_Array : DynamicVectorClass<BuildingClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public BuildingTypeClass * Type
    m_Type : BuildingTypeClass;
    // public FactoryClass * Factory
    m_Factory : FactoryClass;
    // public CDTimerClass C4Timer
    m_C4Timer : CDTimerClass;
    // public int BState
    m_BState : number;
    // public int QueueBState
    m_QueueBState : number;
    // public unsigned long OwnerCountryIndex
    m_OwnerCountryIndex : number;
    // public InfantryClass * C4AppliedBy
    m_C4AppliedBy : InfantryClass;
    // public unsigned long unknown_544
    m_unknown_544 : number;
    // pointer
    // public AnimClass * FirestormAnim
    m_FirestormAnim : AnimClass;
    // pointer
    // public AnimClass * PsiWarnAnim
    m_PsiWarnAnim : AnimClass;
    // public CDTimerClass FactoryRetryTimer
    m_FactoryRetryTimer : CDTimerClass;
    // see eBuildingAnims above for slot index meanings
    // public AnimClass *[21] Anims
    m_Anims : AnimClass;
    // one flag for each of the above anims (whether the anim was enabled when power went offline?)
    // public bool[21] AnimStates
    m_AnimStates : boolean;
    // public AnimClass *[8] DamageFireAnims
    m_DamageFireAnims : AnimClass;
    // if set, ::Update spawns damage fire anims and zeroes it
    // public bool RequiresDamageFires
    m_RequiresDamageFires : boolean;
    // 5E8 - 5F8 ????????
    // public BuildingTypeClass *[3] Upgrades
    m_Upgrades : BuildingTypeClass;
    // type # of sw being launched
    // public int FiringSWType
    m_FiringSWType : number;
    // public unsigned long unknown_5FC
    m_unknown_5FC : number;
    // public BuildingLightClass * Spotlight
    m_Spotlight : BuildingLightClass;
    // public RateTimer GateTimer
    m_GateTimer : RateTimer;
    // tiled light , LightIntensity > 0
    // public LightSourceClass * LightSource
    m_LightSource : LightSourceClass;
    // 0-7 for active directionals, 8/12 for offline ones, check ntfnce.shp or whatever
    // public unsigned long LaserFenceFrame
    m_LaserFenceFrame : number;
    // anim data for firestorm active animations
    // public unsigned long FirestormWallFrame
    m_FirestormWallFrame : number;
    // for hospital, armory, unitrepair etc
    // public StageClass RepairProgress
    m_RepairProgress : StageClass;
    // public RectangleStruct unknown_rect_63C
    m_unknown_rect_63C : RectangleStruct;
    // public CoordStruct unknown_coord_64C
    m_unknown_coord_64C : CoordStruct;
    // public int unknown_int_658
    m_unknown_int_658 : number;
    // public unsigned long unknown_65C
    m_unknown_65C : number;
    // public bool HasPower
    m_HasPower : boolean;
    // public bool IsOverpowered
    m_IsOverpowered : boolean;
    // each powered unit controller building gets this set on power activation and unset on power outage
    // public bool RegisteredAsPoweredUnitSource
    m_RegisteredAsPoweredUnitSource : boolean;
    // public unsigned long SupportingPrisms
    m_SupportingPrisms : number;
    // public bool HasExtraPowerBonus
    m_HasExtraPowerBonus : boolean;
    // public bool HasExtraPowerDrain
    m_HasExtraPowerDrain : boolean;
    // public DynamicVectorClass<InfantryClass *> Overpowerers
    m_Overpowerers : DynamicVectorClass<InfantryClass>;
    // public DynamicVectorClass<InfantryClass *> Occupants
    m_Occupants : DynamicVectorClass<InfantryClass>;
    // which occupant should get XP, which weapon should be fired (see 6FF074)
    // public int FiringOccupantIndex
    m_FiringOccupantIndex : number;
    // public AudioController Audio7
    m_Audio7 : any;
    // public AudioController Audio8
    m_Audio8 : any;
    // the the last state when Update()ing. if this changed since the last Update(), UpdatePowered is called.
    // public bool WasOnline
    m_WasOnline : boolean;
    // is also NOMINAL under [Structures]
    // public bool ShowRealName
    m_ShowRealName : boolean;
    // is also AI_REBUILDABLE under [Structures]
    // public bool BeingProduced
    m_BeingProduced : boolean;
    // is also AI_REPAIRABLE under [Structures]
    // public bool ShouldRebuild
    m_ShouldRebuild : boolean;
    // used to pass the NeedsEngineer check
    // public bool HasEngineer
    m_HasEngineer : boolean;
    // public CDTimerClass CashProductionTimer
    m_CashProductionTimer : CDTimerClass;
    // AI_SELLABLE under [Structures]
    // public bool AI_Sellable
    m_AI_Sellable : boolean;
    // public bool IsReadyToCommence
    m_IsReadyToCommence : boolean;
    // AI handholder for repair logic,
    // public bool NeedsRepairs
    m_NeedsRepairs : boolean;
    // public bool C4Applied
    m_C4Applied : boolean;
    // public bool NoCrew
    m_NoCrew : boolean;
    // public bool unknown_bool_6E1
    m_unknown_bool_6E1 : boolean;
    // public bool unknown_bool_6E2
    m_unknown_bool_6E2 : boolean;
    // has this building changed ownership at least once? affects crew and repair.
    // public bool HasBeenCaptured
    m_HasBeenCaptured : boolean;
    // public bool ActuallyPlacedOnMap
    m_ActuallyPlacedOnMap : boolean;
    // public bool unknown_bool_6E5
    m_unknown_bool_6E5 : boolean;
    // AI handholder for repair logic,
    // public bool IsDamaged
    m_IsDamaged : boolean;
    // public bool IsFogged
    m_IsFogged : boolean;
    // show animooted repair wrench
    // public bool IsBeingRepaired
    m_IsBeingRepaired : boolean;
    // public bool HasBuildUp
    m_HasBuildUp : boolean;
    // status set by EnableStuff() and DisableStuff()
    // public bool StuffEnabled
    m_StuffEnabled : boolean;
    // some fugly buffers
    // public char HasCloakingData
    m_HasCloakingData : number;
    // from Type->CloakRadiusInCells
    // public unsigned char CloakRadius
    m_CloakRadius : number;
    // public char Translucency
    m_Translucency : number;
    // the old "silo needed" logic
    // public unsigned long StorageFilledSlots
    m_StorageFilledSlots : number;
    // randomly assigned secret lab bonus, used if SecretInfantry, SecretUnit, and SecretBuilding are null
    // public TechnoTypeClass * SecretProduction
    m_SecretProduction : TechnoTypeClass;
    // public ColorStruct ColorAdd
    m_ColorAdd : ColorStruct;
    // public int unknown_int_6FC
    m_unknown_int_6FC : number;
    // public short unknown_short_700
    m_unknown_short_700 : number;
    // as defined by Type->UpgradesToLevel=
    // public unsigned char UpgradeLevel
    m_UpgradeLevel : number;
    // public char GateStage
    m_GateStage : number;
    // public PrismChargeState PrismStage
    m_PrismStage : PrismChargeState;
    // public CoordStruct PrismTargetCoords
    m_PrismTargetCoords : CoordStruct;
    // public unsigned long DelayBeforeFiring
    m_DelayBeforeFiring : number;
    // used in UpdateBunker and friends
    // public int BunkerState
    m_BunkerState : number;
}
// FoggedObjectClass
class FoggedObjectClass
{
}
// forward declarations
// BuildingTypeClass
class BuildingTypeClass
    extends TechnoTypeClass
{
    // Constructor
    // public BuildingTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static BuildingTypeClass * Find(char const * pID)
    static Find(pID_0 : string | any) : BuildingTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string | any) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // AbstractTypeClass
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // TechnoTypeClass
    // BuildingTypeClass
    // public virtual SHPStruct * LoadBuildup()
    LoadBuildup() : any;
    // non-virtual
    // public void ClearBuildUp()
    ClearBuildUp() : void;
    // public bool IsVehicle() const
    IsVehicle() : boolean;
    // public short GetFoundationWidth() const
    GetFoundationWidth() : number;
    // public short GetFoundationHeight(bool bIncludeBib) const
    GetFoundationHeight(bIncludeBib_0 : boolean) : number;
    // public bool CanPlaceHere(CellStruct * cell, HouseClass * owner) const
    CanPlaceHere(cell_0 : CellStruct, owner_1 : HouseClass) : boolean;
    // helpers
    // public bool HasSuperWeapon(int index) const
    HasSuperWeapon(index_0 : number) : boolean;
    // public bool HasSuperWeapon() const
    HasSuperWeapon() : boolean;
    // public bool CanTogglePower() const
    CanTogglePower() : boolean;
    // public BuildingAnimStruct& GetBuildingAnim(BuildingAnimSlot slot)
    GetBuildingAnim(slot_0 : BuildingAnimSlot) : BuildingAnimStruct;
    // public BuildingAnimStruct const& GetBuildingAnim(BuildingAnimSlot slot) const
    GetBuildingAnim(slot_0 : BuildingAnimSlot) : BuildingAnimStruct;
    // public static AbstractType const AbsID = AbstractType::BuildingType
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7E4570
    static s_AbsVTable : number;
    // Array
    // public static constant_ptr<DynamicVectorClass<BuildingTypeClass *>, 11025512> const Array = 0xA83C68u
    static s_Array : DynamicVectorClass<BuildingTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public CellStruct * FoundationData
    m_FoundationData : CellStruct;
    // public SHPStruct * Buildup
    m_Buildup : any;
    // public bool BuildupLoaded
    m_BuildupLoaded : boolean;
    // public BuildCat BuildCat
    m_BuildCat : BuildCat;
    // public CoordStruct HalfDamageSmokeLocation1
    m_HalfDamageSmokeLocation1 : CoordStruct;
    // public CoordStruct HalfDamageSmokeLocation2
    m_HalfDamageSmokeLocation2 : CoordStruct;
    // public unsigned long align_E24
    m_align_E24 : number;
    // public double GateCloseDelay
    m_GateCloseDelay : number;
    // public int LightVisibility
    m_LightVisibility : number;
    // public int LightIntensity
    m_LightIntensity : number;
    // public int LightRedTint
    m_LightRedTint : number;
    // public int LightGreenTint
    m_LightGreenTint : number;
    // public int LightBlueTint
    m_LightBlueTint : number;
    // public Point2D PrimaryFirePixelOffset
    m_PrimaryFirePixelOffset : Point2D;
    // public Point2D SecondaryFirePixelOffset
    m_SecondaryFirePixelOffset : Point2D;
    // public OverlayTypeClass * ToOverlay
    m_ToOverlay : OverlayTypeClass;
    // public IsometricTileTypeClass * ToTile
    m_ToTile : IsometricTileTypeClass;
    // public char[16] BuildupFile
    m_BuildupFile : string;
    // public int BuildupSound
    m_BuildupSound : number;
    // public int PackupSound
    m_PackupSound : number;
    // public int CreateUnitSound
    m_CreateUnitSound : number;
    // public int UnitEnterSound
    m_UnitEnterSound : number;
    // public int UnitExitSound
    m_UnitExitSound : number;
    // public int WorkingSound
    m_WorkingSound : number;
    // public int NotWorkingSound
    m_NotWorkingSound : number;
    // public char[24] PowersUpBuilding
    m_PowersUpBuilding : string;
    // public UnitTypeClass * FreeUnit
    m_FreeUnit : UnitTypeClass;
    // public InfantryTypeClass * SecretInfantry
    m_SecretInfantry : InfantryTypeClass;
    // public UnitTypeClass * SecretUnit
    m_SecretUnit : UnitTypeClass;
    // public BuildingTypeClass * SecretBuilding
    m_SecretBuilding : BuildingTypeClass;
    // public int field_EB0
    m_field_EB0 : number;
    // public int Adjacent
    m_Adjacent : number;
    // public AbstractType Factory
    m_Factory : AbstractType;
    // public CoordStruct TargetCoordOffset
    m_TargetCoordOffset : CoordStruct;
    // public CoordStruct ExitCoord
    m_ExitCoord : CoordStruct;
    // public CellStruct * FoundationOutside
    m_FoundationOutside : CellStruct;
    // public int field_ED8
    m_field_ED8 : number;
    // public int DeployFacing
    m_DeployFacing : number;
    // public int PowerBonus
    m_PowerBonus : number;
    // public int PowerDrain
    m_PowerDrain : number;
    // public int ExtraPowerBonus
    m_ExtraPowerBonus : number;
    // public int ExtraPowerDrain
    m_ExtraPowerDrain : number;
    // public Foundation Foundation
    m_Foundation : Foundation;
    // public int Height
    m_Height : number;
    // public int OccupyHeight
    m_OccupyHeight : number;
    // public int MidPoint
    m_MidPoint : number;
    // public int DoorStages
    m_DoorStages : number;
    // public BuildingAnimFrameStruct[6] BuildingAnimFrame
    m_BuildingAnimFrame : BuildingAnimFrameStruct;
    // public BuildingAnimStruct[21] BuildingAnim
    m_BuildingAnim : BuildingAnimStruct;
    // public int Upgrades
    m_Upgrades : number;
    // public SHPStruct * DeployingAnim
    m_DeployingAnim : any;
    // public bool DeployingAnimLoaded
    m_DeployingAnimLoaded : boolean;
    // public SHPStruct * UnderDoorAnim
    m_UnderDoorAnim : any;
    // public bool UnderDoorAnimLoaded
    m_UnderDoorAnimLoaded : boolean;
    // public SHPStruct * Rubble
    m_Rubble : any;
    // public bool RubbleLoaded
    m_RubbleLoaded : boolean;
    // public SHPStruct * RoofDeployingAnim
    m_RoofDeployingAnim : any;
    // public bool RoofDeployingAnimLoaded
    m_RoofDeployingAnimLoaded : boolean;
    // public SHPStruct * UnderRoofDoorAnim
    m_UnderRoofDoorAnim : any;
    // public bool UnderRoofDoorAnimLoaded
    m_UnderRoofDoorAnimLoaded : boolean;
    // public SHPStruct * DoorAnim
    m_DoorAnim : any;
    // public SHPStruct * SpecialZOverlay
    m_SpecialZOverlay : any;
    // public int SpecialZOverlayZAdjust
    m_SpecialZOverlayZAdjust : number;
    // public SHPStruct * BibShape
    m_BibShape : any;
    // public bool BibShapeLoaded
    m_BibShapeLoaded : boolean;
    // public int NormalZAdjust
    m_NormalZAdjust : number;
    // public int AntiAirValue
    m_AntiAirValue : number;
    // public int AntiArmorValue
    m_AntiArmorValue : number;
    // public int AntiInfantryValue
    m_AntiInfantryValue : number;
    // public Point2D ZShapePointMove
    m_ZShapePointMove : Point2D;
    // public int unknown_1538
    m_unknown_1538 : number;
    // public int unknown_153C
    m_unknown_153C : number;
    // public int unknown_1540
    m_unknown_1540 : number;
    // public int unknown_1544
    m_unknown_1544 : number;
    // public unsigned short ExtraLight
    m_ExtraLight : number;
    // public bool TogglePower
    m_TogglePower : boolean;
    // public bool HasSpotlight
    m_HasSpotlight : boolean;
    // public bool IsTemple
    m_IsTemple : boolean;
    // public bool IsPlug
    m_IsPlug : boolean;
    // public bool HoverPad
    m_HoverPad : boolean;
    // public bool BaseNormal
    m_BaseNormal : boolean;
    // public bool EligibileForAllyBuilding
    m_EligibileForAllyBuilding : boolean;
    // public bool EligibleForDelayKill
    m_EligibleForDelayKill : boolean;
    // public bool NeedsEngineer
    m_NeedsEngineer : boolean;
    // public int CaptureEvaEvent
    m_CaptureEvaEvent : number;
    // public int ProduceCashStartup
    m_ProduceCashStartup : number;
    // public int ProduceCashAmount
    m_ProduceCashAmount : number;
    // public int ProduceCashDelay
    m_ProduceCashDelay : number;
    // public int InfantryGainSelfHeal
    m_InfantryGainSelfHeal : number;
    // public int UnitsGainSelfHeal
    m_UnitsGainSelfHeal : number;
    // public int RefinerySmokeFrames
    m_RefinerySmokeFrames : number;
    // public bool Bib
    m_Bib : boolean;
    // public bool Wall
    m_Wall : boolean;
    // public bool Capturable
    m_Capturable : boolean;
    // public bool Powered
    m_Powered : boolean;
    // public bool PoweredSpecial
    m_PoweredSpecial : boolean;
    // public bool Overpowerable
    m_Overpowerable : boolean;
    // public bool Spyable
    m_Spyable : boolean;
    // public bool CanC4
    m_CanC4 : boolean;
    // public bool WantsExtraSpace
    m_WantsExtraSpace : boolean;
    // public bool Unsellable
    m_Unsellable : boolean;
    // public bool ClickRepairable
    m_ClickRepairable : boolean;
    // public bool CanBeOccupied
    m_CanBeOccupied : boolean;
    // public bool CanOccupyFire
    m_CanOccupyFire : boolean;
    // public int MaxNumberOccupants
    m_MaxNumberOccupants : number;
    // public bool ShowOccupantPips
    m_ShowOccupantPips : boolean;
    // public Point2D[10] MuzzleFlash
    m_MuzzleFlash : Point2D;
    // public Point2D[8] DamageFireOffset
    m_DamageFireOffset : Point2D;
    // public Point2D QueueingCell
    m_QueueingCell : Point2D;
    // public int NumberImpassableRows
    m_NumberImpassableRows : number;
    // public Point2D[8] RemoveOccupy
    m_RemoveOccupy : Point2D;
    // public Point2D[8] AddOccupy
    m_AddOccupy : Point2D;
    // public bool Radar
    m_Radar : boolean;
    // public bool SpySat
    m_SpySat : boolean;
    // public bool ChargeAnim
    m_ChargeAnim : boolean;
    // public bool IsAnimDelayedFire
    m_IsAnimDelayedFire : boolean;
    // public bool SiloDamage
    m_SiloDamage : boolean;
    // public bool UnitRepair
    m_UnitRepair : boolean;
    // public bool UnitReload
    m_UnitReload : boolean;
    // public bool Bunker
    m_Bunker : boolean;
    // public bool Cloning
    m_Cloning : boolean;
    // public bool Grinding
    m_Grinding : boolean;
    // public bool UnitAbsorb
    m_UnitAbsorb : boolean;
    // public bool InfantryAbsorb
    m_InfantryAbsorb : boolean;
    // public bool SecretLab
    m_SecretLab : boolean;
    // public bool DoubleThick
    m_DoubleThick : boolean;
    // public bool Flat
    m_Flat : boolean;
    // public bool DockUnload
    m_DockUnload : boolean;
    // public bool Recoilless
    m_Recoilless : boolean;
    // public bool HasStupidGuardMode
    m_HasStupidGuardMode : boolean;
    // public bool BridgeRepairHut
    m_BridgeRepairHut : boolean;
    // public bool Gate
    m_Gate : boolean;
    // public bool SAM
    m_SAM : boolean;
    // public bool ConstructionYard
    m_ConstructionYard : boolean;
    // public bool NukeSilo
    m_NukeSilo : boolean;
    // public bool Refinery
    m_Refinery : boolean;
    // public bool Weeder
    m_Weeder : boolean;
    // public bool WeaponsFactory
    m_WeaponsFactory : boolean;
    // public bool LaserFencePost
    m_LaserFencePost : boolean;
    // public bool LaserFence
    m_LaserFence : boolean;
    // public bool FirestormWall
    m_FirestormWall : boolean;
    // public bool Hospital
    m_Hospital : boolean;
    // public bool Armory
    m_Armory : boolean;
    // public bool EMPulseCannon
    m_EMPulseCannon : boolean;
    // public bool TickTank
    m_TickTank : boolean;
    // public bool TurretAnimIsVoxel
    m_TurretAnimIsVoxel : boolean;
    // public bool BarrelAnimIsVoxel
    m_BarrelAnimIsVoxel : boolean;
    // public bool CloakGenerator
    m_CloakGenerator : boolean;
    // public bool SensorArray
    m_SensorArray : boolean;
    // public bool ICBMLauncher
    m_ICBMLauncher : boolean;
    // public bool Artillary
    m_Artillary : boolean;
    // public bool Helipad
    m_Helipad : boolean;
    // public bool OrePurifier
    m_OrePurifier : boolean;
    // public bool FactoryPlant
    m_FactoryPlant : boolean;
    // public float InfantryCostBonus
    m_InfantryCostBonus : number;
    // public float UnitsCostBonus
    m_UnitsCostBonus : number;
    // public float AircraftCostBonus
    m_AircraftCostBonus : number;
    // public float BuildingsCostBonus
    m_BuildingsCostBonus : number;
    // public float DefensesCostBonus
    m_DefensesCostBonus : number;
    // public bool GDIBarracks
    m_GDIBarracks : boolean;
    // public bool NODBarracks
    m_NODBarracks : boolean;
    // public bool YuriBarracks
    m_YuriBarracks : boolean;
    // public float ChargedAnimTime
    m_ChargedAnimTime : number;
    // public int DelayedFireDelay
    m_DelayedFireDelay : number;
    // public int SuperWeapon
    m_SuperWeapon : number;
    // public int SuperWeapon2
    m_SuperWeapon2 : number;
    // public int GateStages
    m_GateStages : number;
    // public int PowersUpToLevel
    m_PowersUpToLevel : number;
    // public bool DamagedDoor
    m_DamagedDoor : boolean;
    // public bool InvisibleInGame
    m_InvisibleInGame : boolean;
    // public bool TerrainPalette
    m_TerrainPalette : boolean;
    // public bool PlaceAnywhere
    m_PlaceAnywhere : boolean;
    // public bool ExtraDamageStage
    m_ExtraDamageStage : boolean;
    // public bool AIBuildThis
    m_AIBuildThis : boolean;
    // public bool IsBaseDefense
    m_IsBaseDefense : boolean;
    // public unsigned char CloakRadiusInCells
    m_CloakRadiusInCells : number;
    // public bool ConcentricRadialIndicator
    m_ConcentricRadialIndicator : boolean;
    // public int PsychicDetectionRadius
    m_PsychicDetectionRadius : number;
    // public int BarrelStartPitch
    m_BarrelStartPitch : number;
    // public char[28] VoxelBarrelFile
    m_VoxelBarrelFile : string;
    // public CoordStruct VoxelBarrelOffsetToPitchPivotPoint
    m_VoxelBarrelOffsetToPitchPivotPoint : CoordStruct;
    // public CoordStruct VoxelBarrelOffsetToRotatePivotPoint
    m_VoxelBarrelOffsetToRotatePivotPoint : CoordStruct;
    // public CoordStruct VoxelBarrelOffsetToBuildingPivotPoint
    m_VoxelBarrelOffsetToBuildingPivotPoint : CoordStruct;
    // public CoordStruct VoxelBarrelOffsetToBarrelEnd
    m_VoxelBarrelOffsetToBarrelEnd : CoordStruct;
    // public bool DemandLoad
    m_DemandLoad : boolean;
    // public bool DemandLoadBuildup
    m_DemandLoadBuildup : boolean;
    // public bool FreeBuildup
    m_FreeBuildup : boolean;
    // public bool IsThreatRatingNode
    m_IsThreatRatingNode : boolean;
    // public bool PrimaryFireDualOffset
    m_PrimaryFireDualOffset : boolean;
    // public bool ProtectWithWall
    m_ProtectWithWall : boolean;
    // public bool CanHideThings
    m_CanHideThings : boolean;
    // public bool CrateBeneath
    m_CrateBeneath : boolean;
    // public bool LeaveRubble
    m_LeaveRubble : boolean;
    // public bool CrateBeneathIsMoney
    m_CrateBeneathIsMoney : boolean;
    // public char[19] TheaterSpecificID
    m_TheaterSpecificID : string;
    // public int NumberOfDocks
    m_NumberOfDocks : number;
    // public VectorClass<Vector3D<int>> DockingOffsets
    m_DockingOffsets : VectorClass<Vector3D>;
}
// BuildingAnimStruct
class BuildingAnimStruct
{
    // public char[16] Anim
    m_Anim : string;
    // public char[16] Damaged
    m_Damaged : string;
    // public char[16] Garrisoned
    m_Garrisoned : string;
    // public Point2D Position
    m_Position : Point2D;
    // public int ZAdjust
    m_ZAdjust : number;
    // public int YSort
    m_YSort : number;
    // public bool Powered
    m_Powered : boolean;
    // public bool PoweredLight
    m_PoweredLight : boolean;
    // public bool PoweredEffect
    m_PoweredEffect : boolean;
    // public bool PoweredSpecial
    m_PoweredSpecial : boolean;
}
// forward declarations
// OverlayTypeClass
class OverlayTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public OverlayTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static OverlayTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : OverlayTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual CoordStruct * vt_entry_6C(CoordStruct * pDest, CoordStruct * pSrc) const
    vt_entry_6C(pDest_0 : CoordStruct | any, pSrc_1 : CoordStruct | any) : CoordStruct;
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // OverlayTypeClass
    // public virtual void Draw(Point2D * pClientCoords, RectangleStruct * pClipRect, int nFrame)
    Draw(pClientCoords_0 : Point2D, pClipRect_1 : RectangleStruct, nFrame_2 : number) : void;
    // public static AbstractType const AbsID = AbstractType::OverlayType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<OverlayTypeClass *>, 11025792> const Array = 0xA83D80u
    static s_Array : DynamicVectorClass<OverlayTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public LandType LandType
    m_LandType : LandType;
    // public AnimTypeClass * CellAnim
    m_CellAnim : AnimTypeClass;
    // public int DamageLevels
    m_DamageLevels : number;
    // public int Strength
    m_Strength : number;
    // public bool Wall
    m_Wall : boolean;
    // public bool Tiberium
    m_Tiberium : boolean;
    // public bool Crate
    m_Crate : boolean;
    // public bool CrateTrigger
    m_CrateTrigger : boolean;
    // public bool NoUseTileLandType
    m_NoUseTileLandType : boolean;
    // public bool IsVeinholeMonster
    m_IsVeinholeMonster : boolean;
    // public bool IsVeins
    m_IsVeins : boolean;
    // not INI
    // public bool ImageLoaded
    m_ImageLoaded : boolean;
    // public bool Explodes
    m_Explodes : boolean;
    // public bool ChainReaction
    m_ChainReaction : boolean;
    // public bool Overrides
    m_Overrides : boolean;
    // public bool DrawFlat
    m_DrawFlat : boolean;
    // public bool IsRubble
    m_IsRubble : boolean;
    // public bool IsARock
    m_IsARock : boolean;
    // public ColorStruct RadarColor
    m_RadarColor : ColorStruct;
}
// IsometricTileTypeClass
class IsometricTileTypeClass
{
}
// forward declarations
// UnitTypeClass
class UnitTypeClass
    extends TechnoTypeClass
{
    // Constructor
    // public UnitTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static UnitTypeClass * Find(char const * pID)
    static Find(pID_0 : string | any) : UnitTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string | any) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::UnitType
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7F6218
    static s_AbsVTable : number;
    // Array
    // public static constant_ptr<DynamicVectorClass<UnitTypeClass *>, 11025632> const Array = 0xA83CE0u
    static s_Array : DynamicVectorClass<UnitTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public LandType MovementRestrictedTo
    m_MovementRestrictedTo : LandType;
    // public CoordStruct HalfDamageSmokeLocation
    m_HalfDamageSmokeLocation : CoordStruct;
    // public bool Passive
    m_Passive : boolean;
    // public bool CrateGoodie
    m_CrateGoodie : boolean;
    // public bool Harvester
    m_Harvester : boolean;
    // public bool Weeder
    m_Weeder : boolean;
    // public bool unknown_E10
    m_unknown_E10 : boolean;
    // not read from the INIs
    // public bool HasTurret
    m_HasTurret : boolean;
    // public bool DeployToFire
    m_DeployToFire : boolean;
    // public bool IsSimpleDeployer
    m_IsSimpleDeployer : boolean;
    // public bool IsTilter
    m_IsTilter : boolean;
    // public bool UseTurretShadow
    m_UseTurretShadow : boolean;
    // public bool TooBigToFitUnderBridge
    m_TooBigToFitUnderBridge : boolean;
    // public bool CanBeach
    m_CanBeach : boolean;
    // public bool SmallVisceroid
    m_SmallVisceroid : boolean;
    // public bool LargeVisceroid
    m_LargeVisceroid : boolean;
    // public bool CarriesCrate
    m_CarriesCrate : boolean;
    // public bool NonVehicle
    m_NonVehicle : boolean;
    // public int StandingFrames
    m_StandingFrames : number;
    // public int DeathFrames
    m_DeathFrames : number;
    // public int DeathFrameRate
    m_DeathFrameRate : number;
    // public int StartStandFrame
    m_StartStandFrame : number;
    // public int StartWalkFrame
    m_StartWalkFrame : number;
    // public int StartFiringFrame
    m_StartFiringFrame : number;
    // public int StartDeathFrame
    m_StartDeathFrame : number;
    // public int MaxDeathCounter
    m_MaxDeathCounter : number;
    // public int Facings
    m_Facings : number;
    // public int FiringSyncFrame0
    m_FiringSyncFrame0 : number;
    // public int FiringSyncFrame1
    m_FiringSyncFrame1 : number;
    // public int BurstDelay0
    m_BurstDelay0 : number;
    // public int BurstDelay1
    m_BurstDelay1 : number;
    // public int BurstDelay2
    m_BurstDelay2 : number;
    // public int BurstDelay3
    m_BurstDelay3 : number;
    // public SHPStruct * AltImage
    m_AltImage : any;
    // public char WalkFrames
    m_WalkFrames : number;
    // public char FiringFrames
    m_FiringFrames : number;
    // public char[25] AltImageFile
    m_AltImageFile : string;
}
// BuildingAnimFrameStruct
class BuildingAnimFrameStruct
{
    // public unsigned long dwUnknown
    m_dwUnknown : number;
    // public int FrameCount
    m_FrameCount : number;
    // public int FrameDuration
    m_FrameDuration : number;
}
// The AbstractClass is the base class of all game objects.
// FactoryClass
class FactoryClass
    extends AbstractClass
{
    // Constructor
    // public FactoryClass()
    constructor();
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // returns whether progress "IsDifferent" and resets the flag
    // public bool HasProgressChanged()
    HasProgressChanged() : boolean;
    // public bool DemandProduction(TechnoTypeClass const * pType, HouseClass * pOwner, bool shouldQueue)
    DemandProduction(pType_0 : TechnoTypeClass, pOwner_1 : HouseClass, shouldQueue_2 : boolean) : boolean;
    // aborts current product and puts the object in, completed and suspended
    // public void SetObject(TechnoClass * pObject)
    SetObject(pObject_0 : TechnoClass) : void;
    // public bool Suspend(bool manual)
    Suspend(manual_0 : boolean) : boolean;
    // public bool Unsuspend(bool manual)
    Unsuspend(manual_0 : boolean) : boolean;
    // public int GetBuildTimeFrames() const
    GetBuildTimeFrames() : number;
    // public bool AbandonProduction()
    AbandonProduction() : boolean;
    // returns Production.Value
    // public int GetProgress() const
    GetProgress() : number;
    // public bool IsDone() const
    IsDone() : boolean;
    // public int GetCostPerStep() const
    GetCostPerStep() : number;
    // checks the progress and updates the state if done
    // public bool CompletedProduction()
    CompletedProduction() : boolean;
    // builds an item from the queue
    // public void StartProduction()
    StartProduction() : void;
    // public bool RemoveOneFromQueue(TechnoTypeClass const * pItem)
    RemoveOneFromQueue(pItem_0 : TechnoTypeClass) : boolean;
    // in queue and in production
    // public int CountTotal(TechnoTypeClass const * pType) const
    CountTotal(pType_0 : TechnoTypeClass) : number;
    // whether at least one item is queued, not in production
    // public bool IsQueued(TechnoTypeClass const * pType) const
    IsQueued(pType_0 : TechnoTypeClass) : boolean;
    // public static FactoryClass * FindByOwnerAndProduct(HouseClass const * const pHouse, TechnoTypeClass const * const pItem)
    static FindByOwnerAndProduct(pHouse_0 : HouseClass, pItem_1 : TechnoTypeClass) : FactoryClass;
    // public static AbstractType const AbsID = AbstractType::Factory
    static s_AbsID : AbstractType;
    // public static constant_ptr<DynamicVectorClass<FactoryClass *>, 11025968> const Array = 0xA83E30u
    static s_Array : DynamicVectorClass<FactoryClass>;
    // hardcoded to be 54 steps (so cameo clock should be 54 frames)
    // public StageClass Production
    m_Production : StageClass;
    // public DynamicVectorClass<TechnoTypeClass *> QueuedObjects
    m_QueuedObjects : DynamicVectorClass<TechnoTypeClass>;
    // public TechnoClass * Object
    m_Object : TechnoClass;
    // paused when out of money, restored when funds available
    // public bool OnHold
    m_OnHold : boolean;
    // changed progress
    // public bool IsDifferent
    m_IsDifferent : boolean;
    // credits house still owes us for building this
    // public int Balance
    m_Balance : number;
    // public int OriginalBalance
    m_OriginalBalance : number;
    // -1 = none, else Iron Curtain? (was EMPulse in TS)
    // public int SpecialItem
    m_SpecialItem : number;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // completed production, before next (or waiting to place)
    // public bool IsSuspended
    m_IsSuspended : boolean;
    // whether the current suspension state was caused by the player
    // public bool IsManual
    m_IsManual : boolean;
}
// StageClass
class StageClass
{
    // public StageClass()
    constructor();
    // public StageClass(int rate)
    constructor(rate_0 : number);
    // public void Start(int rate)
    Start(rate_0 : number) : void;
    // public void Start(int rate, int step)
    Start(rate_0 : number, step_1 : number) : void;
    // returns whether the value changed.
    // public bool Update()
    Update() : boolean;
    // the current stage value
    // public int Value
    m_Value : number;
    // if the timer expired this frame and the stage value changed
    // public bool HasChanged
    m_HasChanged : boolean;
    // public CDTimerClass Timer
    m_Timer : CDTimerClass;
    // how many frames it takes to increment the stage value
    // public int Rate
    m_Rate : number;
    // added to the stage value every time the timer expires
    // public int Step
    m_Step : number;
}
// forward declarations
// InfantryClass
class InfantryClass
    extends FootClass
{
    // Constructor
    // public InfantryClass(InfantryTypeClass * pType, HouseClass * pOwner)
    constructor(pType_0 : InfantryTypeClass, pOwner_1 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectClass
    // public virtual Action MouseOverObject(ObjectClass const * pObject, bool ignoreForce = false) const
    MouseOverObject(pObject_0 : ObjectClass | any, ignoreForce_1 : boolean | any) : Action;
    // TechnoClass
    // public virtual FireError GetFireError(AbstractClass * pTarget, int nWeaponIndex, bool ignoreRange) const
    GetFireError(pTarget_0 : AbstractClass | any, nWeaponIndex_1 : number | any, ignoreRange_2 : boolean | any) : FireError;
    // InfantryClass
    // public virtual bool IsDeployed() const
    IsDeployed() : boolean;
    // public virtual bool PlayAnim(Sequence index, bool force = false, bool randomStartFrame = false)
    PlayAnim(index_0 : Sequence, force_1 : boolean, randomStartFrame_2 : boolean) : boolean;
    // public static AbstractType const AbsID = AbstractType::Infantry
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7EB058
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<InfantryClass *>, 11025896> const Array = 0xA83DE8u
    static s_Array : DynamicVectorClass<InfantryClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public InfantryTypeClass * Type
    m_Type : InfantryTypeClass;
    // which is currently playing
    // public Sequence SequenceAnim
    m_SequenceAnim : Sequence;
    // public CDTimerClass unknown_Timer_6C8
    m_unknown_Timer_6C8 : CDTimerClass;
    // set in ReceiveDamage on panicky units
    // public unsigned long PanicDurationLeft
    m_PanicDurationLeft : number;
    // set by script action, not cleared anywhere
    // public bool PermanentBerzerk
    m_PermanentBerzerk : boolean;
    // public bool Technician
    m_Technician : boolean;
    // public bool unknown_bool_6DA
    m_unknown_bool_6DA : boolean;
    // public bool Crawling
    m_Crawling : boolean;
    // public bool unknown_bool_6DC
    m_unknown_bool_6DC : boolean;
    // public bool unknown_bool_6DD
    m_unknown_bool_6DD : boolean;
    // public unsigned long unknown_6E0
    m_unknown_6E0 : number;
    // public bool ShouldDeploy
    m_ShouldDeploy : boolean;
    // public int unknown_int_6E8
    m_unknown_int_6E8 : number;
}
// forward declarations
// FootClass
class FootClass
    extends TechnoClass
{
    // Constructor
    // public FootClass(HouseClass * pOwner)
    constructor(pOwner_0 : HouseClass);
    // AbstractClass
    // ObjectClass
    // MissionClass
    // public virtual int Mission_AreaGuard()
    Mission_AreaGuard() : number;
    // TechnoClass
    // public virtual void Destroyed(ObjectClass * Killer)
    Destroyed(Killer_0 : ObjectClass | any) : void;
    // public virtual bool ForceCreate(CoordStruct& coord, unsigned long dwUnk = 0)
    ForceCreate(coord_0 : CoordStruct | any, dwUnk_1 : number | any) : boolean;
    // public virtual AbstractClass * GreatestThreat(ThreatType threat, CoordStruct * pCoord, bool onlyTargetHouseEnemy)
    GreatestThreat(threat_0 : ThreatType | any, pCoord_1 : CoordStruct | any, onlyTargetHouseEnemy_2 : boolean | any) : AbstractClass;
    // FootClass
    // public virtual void ReceiveGunner(FootClass * Gunner)
    ReceiveGunner(Gunner_0 : FootClass) : void;
    // public virtual void RemoveGunner(FootClass * Gunner)
    RemoveGunner(Gunner_0 : FootClass) : void;
    // public virtual bool IsLeavingMap() const
    IsLeavingMap() : boolean;
    // public virtual bool vt_entry_4E0() const
    vt_entry_4E0() : boolean;
    // public virtual bool CanDeployNow() const
    CanDeployNow() : boolean;
    // public virtual void AddSensorsAt(CellStruct cell)
    AddSensorsAt(cell_0 : CellStruct) : void;
    // public virtual void RemoveSensorsAt(CellStruct cell)
    RemoveSensorsAt(cell_0 : CellStruct) : void;
    // public virtual CoordStruct * vt_entry_4F0(CoordStruct * pCrd)
    vt_entry_4F0(pCrd_0 : CoordStruct) : CoordStruct;
    // public virtual void vt_entry_4F4()
    vt_entry_4F4() : void;
    // public virtual bool vt_entry_4F8()
    vt_entry_4F8() : boolean;
    // public virtual bool MoveTo(CoordStruct * pCrd)
    MoveTo(pCrd_0 : CoordStruct) : boolean;
    // public virtual bool StopMoving()
    StopMoving() : boolean;
    // public virtual bool vt_entry_504()
    vt_entry_504() : boolean;
    // public virtual bool ChronoWarpTo(CoordStruct pDest)
    ChronoWarpTo(pDest_0 : CoordStruct) : boolean;
    // public virtual void Draw_A_SHP(SHPStruct * SHP, int idxFacing, Point2D * Coords, RectangleStruct * Rectangle, unsigned long dwUnk5, unsigned long dwUnk6, unsigned long dwUnk7, ZGradient ZGradient, unsigned long dwUnk9, int extraLight, unsigned long dwUnk11, unsigned long dwUnk12, unsigned long dwUnk13, unsigned long dwUnk14, unsigned long dwUnk15, unsigned long dwUnk16)
    Draw_A_SHP(SHP_0 : any, idxFacing_1 : number, Coords_2 : Point2D, Rectangle_3 : RectangleStruct, dwUnk5_4 : number, dwUnk6_5 : number, dwUnk7_6 : number, ZGradient_7 : ZGradient, dwUnk9_8 : number, extraLight_9 : number, dwUnk11_10 : number, dwUnk12_11 : number, dwUnk13_12 : number, dwUnk14_13 : number, dwUnk15_14 : number, dwUnk16_15 : number) : void;
    // public virtual void Draw_A_VXL(VoxelStruct * VXL, int HVAFrameIndex, int Flags, IndexClass<int, int> * Cache, RectangleStruct * Rectangle, Point2D * CenterPoint, Matrix3D * Matrix, unsigned long dwUnk8, unsigned long DrawFlags, unsigned long dwUnk10)
    Draw_A_VXL(VXL_0 : any, HVAFrameIndex_1 : number, Flags_2 : number, Cache_3 : any, Rectangle_4 : RectangleStruct, CenterPoint_5 : Point2D, Matrix_6 : Matrix3D, dwUnk8_7 : number, DrawFlags_8 : number, dwUnk10_9 : number) : void;
    // public virtual void GoBerzerk()
    GoBerzerk() : void;
    // public virtual void Panic()
    Panic() : void;
    // public virtual void UnPanic()
    UnPanic() : void;
    // public virtual void PlayIdleAnim(int nIdleAnimNumber)
    PlayIdleAnim(nIdleAnimNumber_0 : number) : void;
    // public virtual unsigned long vt_entry_524()
    vt_entry_524() : number;
    // public virtual BuildingClass * TryNearestDockBuilding(TypeList<BuildingTypeClass *> * bList, unsigned long dwUnk2, unsigned long dwUnk3) const
    TryNearestDockBuilding(bList_0 : TypeList<BuildingTypeClass>, dwUnk2_1 : number, dwUnk3_2 : number) : BuildingClass;
    // public virtual BuildingClass * FindCloserDockBuilding(BuildingTypeClass * bType, unsigned long dwUnk2, unsigned long dwUnk3, int * pDistance) const
    FindCloserDockBuilding(bType_0 : BuildingTypeClass, dwUnk2_1 : number, dwUnk3_2 : number, pDistance_3 : number) : BuildingClass;
    // public virtual BuildingClass * FindNearestDockBuilding(BuildingTypeClass * bType, unsigned long dwUnk2, unsigned long dwUnk3) const
    FindNearestDockBuilding(bType_0 : BuildingTypeClass, dwUnk2_1 : number, dwUnk3_2 : number) : BuildingClass;
    // public virtual void vt_entry_534(unsigned long dwUnk, unsigned long dwUnk2)
    vt_entry_534(dwUnk_0 : number, dwUnk2_1 : number) : void;
    // public virtual int GetCurrentSpeed() const
    GetCurrentSpeed() : number;
    // public virtual AbstractClass * vt_entry_53C(unsigned long dwUnk)
    vt_entry_53C(dwUnk_0 : number) : AbstractClass;
    // public virtual void vt_entry_540(unsigned long dwUnk)
    vt_entry_540(dwUnk_0 : number) : void;
    // public virtual void SetSpeedPercentage(double percentage)
    SetSpeedPercentage(percentage_0 : number) : void;
    // public virtual void vt_entry_548()
    vt_entry_548() : void;
    // public virtual void vt_entry_54C()
    vt_entry_54C() : void;
    // public virtual bool IsLandZoneClear(AbstractClass * pDestination)
    IsLandZoneClear(pDestination_0 : AbstractClass) : boolean;
    // public bool CanBeRecruited(HouseClass * ByWhom) const
    CanBeRecruited(ByWhom_0 : HouseClass) : boolean;
    // only used by squid damage routines, normal wakes are created differently it seems
    // creates 3 wake animations behind the unit
    // public void CreateWakes(CoordStruct coords)
    CreateWakes(coords_0 : CoordStruct) : void;
    // can this jumpjet stay in this cell or not? (two jumpjets in one cell are not okay, locomotor kicks one of them out in the next frame)
    // public bool Jumpjet_LocationClear() const
    Jumpjet_LocationClear() : boolean;
    // public void Jumpjet_OccupyCell(CellStruct Cell)
    Jumpjet_OccupyCell(Cell_0 : CellStruct) : void;
    // changes locomotor to the given one, Magnetron style
    // mind that this locks up the source too, Magnetron style
    // public void FootClass_ImbueLocomotor(FootClass * target, _GUID clsid)
    FootClass_ImbueLocomotor(target_0 : FootClass, clsid_1 : any) : void;
    // var $this = this; $.each($this.Passengers, function(ix, p) { p.Location = $this.Location; });
    // public void UpdatePassengerCoords()
    UpdatePassengerCoords() : void;
    // public void AbortMotion()
    AbortMotion() : void;
    // public bool UpdatePathfinding(CellStruct unkCell, CellStruct unkCell2, int unk3)
    UpdatePathfinding(unkCell_0 : CellStruct, unkCell2_1 : CellStruct, unk3_2 : number) : boolean;
    // Removes the first passenger and updates the Gunner.
    // public FootClass * RemoveFirstPassenger()
    RemoveFirstPassenger() : FootClass;
    // Removes a specific passenger and updates the Gunner.
    // public FootClass * RemovePassenger(FootClass * pPassenger)
    RemovePassenger(pPassenger_0 : FootClass) : FootClass;
    // Adds a specific passenger and updates the Gunner.
    // public void EnterAsPassenger(FootClass * pPassenger)
    EnterAsPassenger(pPassenger_0 : FootClass) : void;
    // Adds to the NavQueue
    // public void QueueNavigationList(AbstractClass * target)
    QueueNavigationList(target_0 : AbstractClass) : void;
    // Clears NavQueue
    // public void ClearNavigationList()
    ClearNavigationList() : void;
    // searches cell, sets destination, and returns whether unit is on that cell
    // public bool MoveToTiberium(int radius, bool scanClose = false)
    MoveToTiberium(radius_0 : number, scanClose_1 : boolean) : boolean;
    // searches cell, sets destination, and returns whether unit is on that cell
    // public bool MoveToWeed(int radius)
    MoveToWeed(radius_0 : number) : boolean;
    // public static AbstractFlags const AbsDerivateID = AbstractFlags::Foot
    static s_AbsDerivateID : AbstractFlags;
    // public static constant_ptr<DynamicVectorClass<FootClass *>, 9125312> const Array = 0x8B3DC0u
    static s_Array : DynamicVectorClass<FootClass>;
    // which planning path am I following?
    // public int PlanningPathIdx
    m_PlanningPathIdx : number;
    // add to WaypointCell to get Nearby_Cell for this foot
    // public CellStruct WaypointNearbyAccessibleCellDelta
    m_WaypointNearbyAccessibleCellDelta : CellStruct;
    // current waypoint cell
    // public CellStruct WaypointCell
    m_WaypointCell : CellStruct;
    // unused?
    // public unsigned long unknown_52C
    m_unknown_52C : number;
    // public unsigned long unknown_530
    m_unknown_530 : number;
    // public unsigned long unknown_534
    m_unknown_534 : number;
    // public int WalkedFramesSoFar
    m_WalkedFramesSoFar : number;
    // public bool IsMoveSoundPlaying
    m_IsMoveSoundPlaying : boolean;
    // public int MoveSoundDelay
    m_MoveSoundDelay : number;
    // public CellStruct CurrentMapCoords
    m_CurrentMapCoords : CellStruct;
    // ::UpdatePosition uses this to remove threat from last occupied cell, etc
    // public CellStruct LastMapCoords
    m_LastMapCoords : CellStruct;
    // which cell was I occupying previously? only for AircraftTracker-tracked stuff
    // public CellStruct LastFlightMapCoords
    m_LastFlightMapCoords : CellStruct;
    // unconfirmed, which cell am I occupying? only for jumpjets
    // public CellStruct CurrentJumpjetMapCoords
    m_CurrentJumpjetMapCoords : CellStruct;
    // public CoordStruct unknown_coords_568
    m_unknown_coords_568 : CoordStruct;
    // public double SpeedPercentage
    m_SpeedPercentage : number;
    // public double SpeedMultiplier
    m_SpeedMultiplier : number;
    // public AbstractClass * unknown_5A0
    m_unknown_5A0 : AbstractClass;
    // possibly other objects as well
    // public AbstractClass * Destination
    m_Destination : AbstractClass;
    // public AbstractClass * LastDestination
    m_LastDestination : AbstractClass;
    // only Mission::AttackMove or Mission::None
    // public Mission MegaMission
    m_MegaMission : Mission;
    // when AttackMove target is a cell
    // public AbstractClass * MegaDestination
    m_MegaDestination : AbstractClass;
    // when AttackMove target is an object
    // public AbstractClass * MegaTarget
    m_MegaTarget : AbstractClass;
    // unused?
    // public unsigned char unknown_5D0
    m_unknown_5D0 : number;
    // fighting an enemy on the way
    // public bool HaveAttackMoveTarget
    m_HaveAttackMoveTarget : boolean;
    // public TeamClass * Team
    m_Team : TeamClass;
    // next unit in team
    // public FootClass * NextTeamMember
    m_NextTeamMember : FootClass;
    // public unsigned long unknown_5DC
    m_unknown_5DC : number;
    // list of directions to move in next, like tube directions
    // public int[24] PathDirections
    m_PathDirections : number;
    // public int unknown_int_64C
    m_unknown_int_64C : number;
    // public CoordStruct unknown_point3d_678
    m_unknown_point3d_678 : CoordStruct;
    // I'm in this tunnel
    // public char TubeIndex
    m_TubeIndex : number;
    // public bool unknown_bool_685
    m_unknown_bool_685 : boolean;
    // which waypoint in my planning path am I following?
    // public char WaypointIndex
    m_WaypointIndex : number;
    // public bool unknown_bool_687
    m_unknown_bool_687 : boolean;
    // public bool unknown_bool_688
    m_unknown_bool_688 : boolean;
    // Is a fully joined member of a team, used for regroup etc. checks
    // public bool IsInitiated
    m_IsInitiated : boolean;
    // public bool ShouldScanForTarget
    m_ShouldScanForTarget : boolean;
    // public bool unknown_bool_68B
    m_unknown_bool_68B : boolean;
    // public bool IsDeploying
    m_IsDeploying : boolean;
    // public bool IsFiring
    m_IsFiring : boolean;
    // public bool unknown_bool_68E
    m_unknown_bool_68E : boolean;
    // orders the unit to enter the closest bio reactor
    // public bool ShouldEnterAbsorber
    m_ShouldEnterAbsorber : boolean;
    // orders the unit to enter the closest battle bunker
    // public bool ShouldEnterOccupiable
    m_ShouldEnterOccupiable : boolean;
    // orders the unit to enter the closest neutral building
    // public bool ShouldGarrisonStructure
    m_ShouldGarrisonStructure : boolean;
    // the tdrone/squid that's eating me
    // public FootClass * ParasiteEatingMe
    m_ParasiteEatingMe : FootClass;
    // public int LastBeParasitedStartFrame
    m_LastBeParasitedStartFrame : number;
    // my parasitic half, nonzero for, eg, terror drone or squiddy
    // public ParasiteClass * ParasiteImUsing
    m_ParasiteImUsing : ParasiteClass;
    // public bool unknown_bool_6AC
    m_unknown_bool_6AC : boolean;
    // the unit's locomotor is jammed by a magnetron
    // public bool IsAttackedByLocomotor
    m_IsAttackedByLocomotor : boolean;
    // a magnetron attacked this unit and let it go. falling, landing, or sitting on the ground
    // public bool IsLetGoByLocomotor
    m_IsLetGoByLocomotor : boolean;
    // public bool unknown_bool_6AF
    m_unknown_bool_6AF : boolean;
    // public bool unknown_bool_6B0
    m_unknown_bool_6B0 : boolean;
    // public bool unknown_bool_6B1
    m_unknown_bool_6B1 : boolean;
    // public bool unknown_bool_6B2
    m_unknown_bool_6B2 : boolean;
    // public bool unknown_bool_6B3
    m_unknown_bool_6B3 : boolean;
    // public bool unknown_bool_6B4
    m_unknown_bool_6B4 : boolean;
    // public bool unknown_bool_6B5
    m_unknown_bool_6B5 : boolean;
    // frozen in first frame of the proper facing - when magnetron'd or warping
    // public bool FrozenStill
    m_FrozenStill : boolean;
    // public bool unknown_bool_6B7
    m_unknown_bool_6B7 : boolean;
    // public bool unknown_bool_6B8
    m_unknown_bool_6B8 : boolean;
    // public AudioController MoveSoundAudioController
    m_MoveSoundAudioController : any;
    // public char[20] __MoveSoundAudioController
    m___MoveSoundAudioController : string;
    // public DynamicVectorClass<AbstractClass *> unknown_abstract_array_588
    m_unknown_abstract_array_588 : DynamicVectorClass<AbstractClass>;
    // public char[24] __unknown_abstract_array_588
    m___unknown_abstract_array_588 : string;
    // Stores sequence of movement destinations
    // public DynamicVectorClass<AbstractClass *> NavQueue
    m_NavQueue : DynamicVectorClass<AbstractClass>;
    // public char[24] __NavQueue
    m___NavQueue : string;
    // public CDTimerClass PathDelayTimer
    m_PathDelayTimer : CDTimerClass;
    // public char[12] __PathDelayTimer
    m___PathDelayTimer : string;
    // public CDTimerClass unknown_timer_650
    m_unknown_timer_650 : CDTimerClass;
    // public char[12] __unknown_timer_650
    m___unknown_timer_650 : string;
    // public CDTimerClass SightTimer
    m_SightTimer : CDTimerClass;
    // public char[12] __SightTimer
    m___SightTimer : string;
    // public CDTimerClass BlockagePathTimer
    m_BlockagePathTimer : CDTimerClass;
    // public char[12] __BlockagePathTimer
    m___BlockagePathTimer : string;
    // public ILocomotionPtr Locomotor
    m_Locomotor : any;
    // public char[4] __Locomotor
    m___Locomotor : string;
    // for squid victims
    // public CDTimerClass ParalysisTimer
    m_ParalysisTimer : CDTimerClass;
    // public char[12] __ParalysisTimer
    m___ParalysisTimer : string;
}
// The AbstractClass is the base class of all game objects.
// TeamClass
class TeamClass
    extends AbstractClass
{
    // Constructor
    // public TeamClass(TeamTypeClass * pType, HouseClass * pOwner, int _unknown_44)
    constructor(pType_0 : TeamTypeClass, pOwner_1 : HouseClass, _unknown_44_2 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // fills dest with all types needed to complete this team. each type is
    // included as often as it is needed.
    // public void GetTaskForceMissingMemberTypes(DynamicVectorClass<TechnoTypeClass *>& dest) const
    GetTaskForceMissingMemberTypes(dest_0 : DynamicVectorClass<TechnoTypeClass>) : void;
    // public void LiberateMember(FootClass * pFoot, int idx = -1, unsigned char count = 0)
    LiberateMember(pFoot_0 : FootClass, idx_1 : number, count_2 : number) : void;
    // if bKeepQuantity is false, this will not change the quantity of each techno member
    // public bool AddMember(FootClass * pFoot, bool bForce)
    AddMember(pFoot_0 : FootClass, bForce_1 : boolean) : boolean;
    // public void AssignMissionTarget(AbstractClass * pTarget)
    AssignMissionTarget(pTarget_0 : AbstractClass) : void;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::Team
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<TeamClass *>, 9126120> const Array = 0x8B40E8u
    static s_Array : DynamicVectorClass<TeamClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TeamTypeClass * Type
    m_Type : TeamTypeClass;
    // public ScriptClass * CurrentScript
    m_CurrentScript : ScriptClass;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // public HouseClass * Target
    m_Target : HouseClass;
    // public CellClass * SpawnCell
    m_SpawnCell : CellClass;
    // public FootClass * ClosestMember
    m_ClosestMember : FootClass;
    // public AbstractClass * QueuedFocus
    m_QueuedFocus : AbstractClass;
    // public AbstractClass * Focus
    m_Focus : AbstractClass;
    // public int unknown_44
    m_unknown_44 : number;
    // public int TotalObjects
    m_TotalObjects : number;
    // public int TotalThreatValue
    m_TotalThreatValue : number;
    // public int CreationFrame
    m_CreationFrame : number;
    // public FootClass * FirstUnit
    m_FirstUnit : FootClass;
    // public CDTimerClass GuardAreaTimer
    m_GuardAreaTimer : CDTimerClass;
    // public CDTimerClass SuspendTimer
    m_SuspendTimer : CDTimerClass;
    // public TagClass * Tag
    m_Tag : TagClass;
    // public bool IsTransient
    m_IsTransient : boolean;
    // public bool NeedsReGrouping
    m_NeedsReGrouping : boolean;
    // public bool GuardSlowerIsNotUnderStrength
    m_GuardSlowerIsNotUnderStrength : boolean;
    // public bool IsForcedActive
    m_IsForcedActive : boolean;
    // public bool IsHasBeen
    m_IsHasBeen : boolean;
    // public bool IsFullStrength
    m_IsFullStrength : boolean;
    // public bool IsUnderStrength
    m_IsUnderStrength : boolean;
    // public bool IsReforming
    m_IsReforming : boolean;
    // public bool IsLagging
    m_IsLagging : boolean;
    // public bool NeedsToDisappear
    m_NeedsToDisappear : boolean;
    // public bool JustDisappeared
    m_JustDisappeared : boolean;
    // public bool IsMoving
    m_IsMoving : boolean;
    // can proceed to the next step of the script
    // public bool StepCompleted
    m_StepCompleted : boolean;
    // public bool TargetNotAssigned
    m_TargetNotAssigned : boolean;
    // public bool IsLeavingMap
    m_IsLeavingMap : boolean;
    // public bool IsSuspended
    m_IsSuspended : boolean;
    // executed script action 49, 0
    // public bool AchievedGreatSuccess
    m_AchievedGreatSuccess : boolean;
    // counts of each object specified in the Type
    // public int[6] CountObjects
    m_CountObjects : number;
}
// ---
// TeamTypeClass
class TeamTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public TeamTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static TeamTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : TeamTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static bool LoadFromINIList(CCINIClass * pINI, bool IsGlobal)
    static LoadFromINIList(pINI_0 : CCINIClass, IsGlobal_1 : boolean) : boolean;
    // public TeamClass * CreateTeam(HouseClass * pHouse)
    CreateTeam(pHouse_0 : HouseClass) : TeamClass;
    // public void DestroyAllInstances()
    DestroyAllInstances() : void;
    // public int GetGroup() const
    GetGroup() : number;
    // public CellStruct * GetWaypoint(CellStruct * buffer) const
    GetWaypoint(buffer_0 : CellStruct) : CellStruct;
    // public CellStruct * GetTransportWaypoint(CellStruct * buffer) const
    GetTransportWaypoint(buffer_0 : CellStruct) : CellStruct;
    // public bool CanRecruitUnit(FootClass * pUnit, HouseClass * pOwner) const
    CanRecruitUnit(pUnit_0 : FootClass, pOwner_1 : HouseClass) : boolean;
    // public void FlashAllInstances(int Duration)
    FlashAllInstances(Duration_0 : number) : void;
    // public TeamClass * FindFirstInstance() const
    FindFirstInstance() : TeamClass;
    // public void ProcessTaskForce()
    ProcessTaskForce() : void;
    // public static void ProcessAllTaskforces()
    static ProcessAllTaskforces() : void;
    // public HouseClass * GetHouse() const
    GetHouse() : HouseClass;
    // public static AbstractType const AbsID = AbstractType::TeamType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TeamTypeClass *>, 11070624> const Array = 0xA8ECA0u
    static s_Array : DynamicVectorClass<TeamTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public int Group
    m_Group : number;
    // public int VeteranLevel
    m_VeteranLevel : number;
    // public bool Loadable
    m_Loadable : boolean;
    // public bool Full
    m_Full : boolean;
    // public bool Annoyance
    m_Annoyance : boolean;
    // public bool GuardSlower
    m_GuardSlower : boolean;
    // public bool Recruiter
    m_Recruiter : boolean;
    // public bool Autocreate
    m_Autocreate : boolean;
    // public bool Prebuild
    m_Prebuild : boolean;
    // public bool Reinforce
    m_Reinforce : boolean;
    // public bool Whiner
    m_Whiner : boolean;
    // public bool Aggressive
    m_Aggressive : boolean;
    // public bool LooseRecruit
    m_LooseRecruit : boolean;
    // public bool Suicide
    m_Suicide : boolean;
    // public bool Droppod
    m_Droppod : boolean;
    // public bool UseTransportOrigin
    m_UseTransportOrigin : boolean;
    // public bool DropshipLoadout
    m_DropshipLoadout : boolean;
    // public bool OnTransOnly
    m_OnTransOnly : boolean;
    // public int Priority
    m_Priority : number;
    // public int Max
    m_Max : number;
    // public int field_BC
    m_field_BC : number;
    // public int MindControlDecision
    m_MindControlDecision : number;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // idx for MP
    // public int idxHouse
    m_idxHouse : number;
    // public int TechLevel
    m_TechLevel : number;
    // public TagClass * Tag
    m_Tag : TagClass;
    // public int Waypoint
    m_Waypoint : number;
    // public int TransportWaypoint
    m_TransportWaypoint : number;
    // public int cntInstances
    m_cntInstances : number;
    // public ScriptTypeClass * ScriptType
    m_ScriptType : ScriptTypeClass;
    // public TaskForceClass * TaskForce
    m_TaskForce : TaskForceClass;
    // public int IsGlobal
    m_IsGlobal : number;
    // public int field_EC
    m_field_EC : number;
    // public bool field_F0
    m_field_F0 : boolean;
    // public bool field_F1
    m_field_F1 : boolean;
    // public bool AvoidThreats
    m_AvoidThreats : boolean;
    // public bool IonImmune
    m_IonImmune : boolean;
    // public bool TransportsReturnOnUnload
    m_TransportsReturnOnUnload : boolean;
    // public bool AreTeamMembersRecruitable
    m_AreTeamMembersRecruitable : boolean;
    // public bool IsBaseDefense
    m_IsBaseDefense : boolean;
    // public bool OnlyTargetHouseEnemy
    m_OnlyTargetHouseEnemy : boolean;
}
// The AbstractClass is the base class of all game objects.
// TagClass
class TagClass
    extends AbstractClass
{
    // Constructor
    // public TagClass(TagTypeClass * pType)
    constructor(pType_0 : TagTypeClass);
    // finds an instance using the type, or creates one
    // public static TagClass * GetInstance(TagTypeClass * pType)
    static GetInstance(pType_0 : TagTypeClass) : TagClass;
    // deletes every tag in array
    // public static void DeleteAll()
    static DeleteAll() : void;
    // notifies all tags in array that a global was updated
    // public static void NotifyGlobalChanged(int idxGlobal)
    static NotifyGlobalChanged(idxGlobal_0 : number) : void;
    // notifies all tags in array that a global was updated
    // public static void NotifyLocalChanged(int idxLocal)
    static NotifyLocalChanged(idxLocal_0 : number) : void;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass | any, removed_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any | any) : void;
    // contains at least one Crosses Horizontal Line event
    // public bool HasCrossesHorizontalLineEvent() const
    HasCrossesHorizontalLineEvent() : boolean;
    // contains at least one Crosses Vertical Line event
    // public bool HasCrossesVerticalLineEvent() const
    HasCrossesVerticalLineEvent() : boolean;
    // contains at least one Zone Entry By event
    // public bool HasZoneEntryByEvent() const
    HasZoneEntryByEvent() : boolean;
    // contains at least one Allow Win action
    // public bool HasAllowWinAction() const
    HasAllowWinAction() : boolean;
    // called when a global is updated
    // public void GlobalChanged(int idxGlobal)
    GlobalChanged(idxGlobal_0 : number) : void;
    // called when a local is updated
    // public void LocalChanged(int idxLocal)
    LocalChanged(idxLocal_0 : number) : void;
    // whether there exist no other tag having the same type
    // note: this is not the same as this->InstanceCount
    // public bool IsOnlyInstanceOfType() const
    IsOnlyInstanceOfType() : boolean;
    // public bool RaiseEvent(TriggerEvent event, ObjectClass * pTagOwner, CellStruct location, bool forceAllOccured = false, TechnoClass * pSource = nullptr)
    RaiseEvent(event_0 : TriggerEvent, pTagOwner_1 : ObjectClass, location_2 : CellStruct, forceAllOccured_3 : boolean, pSource_4 : TechnoClass) : boolean;
    // whether the tag transfers when the owner is "changed",
    // like vehicle thief to tank and vice versa
    // public bool ShouldReplace() const
    ShouldReplace() : boolean;
    // public void Destroy()
    Destroy() : void;
    // public bool HasBeenDestroyed() const
    HasBeenDestroyed() : boolean;
    // adds a trigger to the list
    // public void AddTrigger(TriggerClass * pTrigger)
    AddTrigger(pTrigger_0 : TriggerClass) : void;
    // removes a trigger from the list
    // public bool RemoveTrigger(TriggerClass * pTrigger)
    RemoveTrigger(pTrigger_0 : TriggerClass) : boolean;
    // check whether the trigger is contained in the list
    // public bool ContainsTrigger(TriggerClass * pTrigger) const
    ContainsTrigger(pTrigger_0 : TriggerClass) : boolean;
    // public static AbstractType const AbsID = AbstractType::Tag
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<TagClass *>, 11593504> const Array = 0xB0E720u
    static s_Array : DynamicVectorClass<TagClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TagTypeClass * Type
    m_Type : TagTypeClass;
    // public TriggerClass * FirstTrigger
    m_FirstTrigger : TriggerClass;
    // public int InstanceCount
    m_InstanceCount : number;
    // public CellStruct DefaultCoords
    m_DefaultCoords : CellStruct;
    // public bool Destroyed
    m_Destroyed : boolean;
    // public bool IsExecuting
    m_IsExecuting : boolean;
}
// ---
// TagTypeClass
class TagTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public TagTypeClass(char const * pName)
    constructor(pName_0 : string);
    // Array
    // public static TagTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : TagTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass | any, removed_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any | any) : void;
    // AbstractTypeClass
    // public virtual int GetArrayIndex() const
    GetArrayIndex() : number;
    // public virtual bool LoadFromINI(CCINIClass * pINI)
    LoadFromINI(pINI_0 : CCINIClass | any) : boolean;
    // public virtual bool SaveToINI(CCINIClass * pINI)
    SaveToINI(pINI_0 : CCINIClass | any) : boolean;
    // static
    // public static void LoadFromINIList(CCINIClass * pINI)
    static LoadFromINIList(pINI_0 : CCINIClass) : void;
    // public static void SaveToINIList(CCINIClass * pINI)
    static SaveToINIList(pINI_0 : CCINIClass) : void;
    // public static TagTypeClass * FindByNameOrID(char const * pName)
    static FindByNameOrID(pName_0 : string) : TagTypeClass;
    // public Flags GetFlags() const
    GetFlags() : any;
    // contains at least one Allow Win action
    // public bool HasAllowWinAction() const
    HasAllowWinAction() : boolean;
    // contains at least one Crosses Horizontal Line event
    // public bool HasCrossesHorizontalLineEvent() const
    HasCrossesHorizontalLineEvent() : boolean;
    // contains at least one Crosses Vertical Line event
    // public bool HasCrossesVerticalLineEvent() const
    HasCrossesVerticalLineEvent() : boolean;
    // contains at least one Zone Entry By event
    // public bool HasZoneEntryByEvent() const
    HasZoneEntryByEvent() : boolean;
    // adds a trigger to the list
    // public bool AddTrigger(TriggerTypeClass * pTrigger)
    AddTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    // removes a trigger from the list
    // public bool RemoveTrigger(TriggerTypeClass * pTrigger)
    RemoveTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    // check whether the trigger is contained in the list
    // public bool ContainsTrigger(TriggerTypeClass * pTrigger) const
    ContainsTrigger(pTrigger_0 : TriggerTypeClass) : boolean;
    // public static AbstractType const AbsID = AbstractType::TagType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TagTypeClass *>, 11593600> const Array = 0xB0E780u
    static s_Array : DynamicVectorClass<TagTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public TriggerPersistence Persistence
    m_Persistence : TriggerPersistence;
    // public TriggerTypeClass * FirstTrigger
    m_FirstTrigger : TriggerTypeClass;
}
// ---
// TriggerTypeClass
class TriggerTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public TriggerTypeClass(char const * pName)
    constructor(pName_0 : string);
    // Array
    // public static TriggerTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : TriggerTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass | any, removed_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any | any) : void;
    // AbstractTypeClass
    // public virtual int GetArrayIndex() const
    GetArrayIndex() : number;
    // public virtual bool LoadFromINI(CCINIClass * pINI)
    LoadFromINI(pINI_0 : CCINIClass | any) : boolean;
    // public virtual bool SaveToINI(CCINIClass * pINI)
    SaveToINI(pINI_0 : CCINIClass | any) : boolean;
    // static
    // public static void LoadFromINIList(CCINIClass * pINI)
    static LoadFromINIList(pINI_0 : CCINIClass) : void;
    // public static void SaveToINIList(CCINIClass * pINI)
    static SaveToINIList(pINI_0 : CCINIClass) : void;
    // public TagTypeClass * FindByNameOrID(char const * pName)
    FindByNameOrID(pName_0 : string) : TagTypeClass;
    // public Flags GetFlags() const
    GetFlags() : any;
    // contains at least one Allow Win action
    // public bool HasAllowWinAction() const
    HasAllowWinAction() : boolean;
    // contains at least one Global Set or Global Cleared event
    // public bool HasGlobalSetOrClearedEvent(int idxGlobal) const
    HasGlobalSetOrClearedEvent(idxGlobal_0 : number) : boolean;
    // contains at least one Local Set or Local Cleared event
    // public bool HasLocalSetOrClearedEvent(int idxLocal) const
    HasLocalSetOrClearedEvent(idxLocal_0 : number) : boolean;
    // contains at least one Crosses Horizontal Line event
    // public bool HasCrossesHorizontalLineEvent() const
    HasCrossesHorizontalLineEvent() : boolean;
    // contains at least one Crosses Vertical Line event
    // public bool HasCrossesVerticalLineEvent() const
    HasCrossesVerticalLineEvent() : boolean;
    // contains at least one Zone Entry By event
    // public bool HasZoneEntryByEvent() const
    HasZoneEntryByEvent() : boolean;
    // deletes an action from the list
    // public bool RemoveAction(TActionClass * pAction)
    RemoveAction(pAction_0 : TActionClass) : boolean;
    // deletes an event from the list
    // public bool RemoveEvent(TEventClass * pEvent)
    RemoveEvent(pEvent_0 : TEventClass) : boolean;
    // public static AbstractType const AbsID = AbstractType::TriggerType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TriggerTypeClass *>, 9126264> const Array = 0x8B4178u
    static s_Array : DynamicVectorClass<TriggerTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // easy = 0, normal = 1, hard = 2
    // public bool[3] Difficulty
    m_Difficulty : boolean;
    // public bool Enabled
    m_Enabled : boolean;
    // vehicle thieves must take Tag with it when hijacking
    // public bool MustTransfer
    m_MustTransfer : boolean;
    // public HouseTypeClass * House
    m_House : HouseTypeClass;
    // public TriggerTypeClass * NextTrigger
    m_NextTrigger : TriggerTypeClass;
    // public TEventClass * FirstEvent
    m_FirstEvent : TEventClass;
    // public TActionClass * FirstAction
    m_FirstAction : TActionClass;
}
// The AbstractClass is the base class of all game objects.
// TActionClass
class TActionClass
    extends AbstractClass
{
    // Constructor
    // public TActionClass()
    constructor();
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass | any, removed_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any | any) : void;
    // public virtual int GetArrayIndex() const
    GetArrayIndex() : number;
    // you are responsible for doing INI::ReadString and strtok'ing it before calling
    // this func only calls strtok again, doesn't know anything about buffers
    // public void LoadFromINI()
    LoadFromINI() : void;
    // you allocate the buffer for this, and save it to ini yourself after this returns
    // this func only sprintf's the stuff it needs into buffer
    // public void PrepareSaveToINI(char * buffer) const
    PrepareSaveToINI(buffer_0 : string) : void;
    // fuck if I know what's the purpose of this, returns a bitfield of flags for trigger logic
    // public static int GetFlags(int actionKind)
    static GetFlags(actionKind_0 : number) : number;
    // transforms actionKind to a number saying what to parse arguments as (team/tag/trigger id, waypoint, integer, etc)
    // public static int GetMode(int actionKind)
    static GetMode(actionKind_0 : number) : number;
    // main brain, returns whether succeeded (mostly, no consistency in results what so ever)
    // trigger fires all actions regardless of result of this
    // public bool Execute(HouseClass * pHouse, ObjectClass * pObject, TriggerClass * pTrigger, CellStruct const& location)
    Execute(pHouse_0 : HouseClass, pObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LightningStrikeAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LightningStrikeAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RemoveParticleSystemsAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RemoveParticleSystemsAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool WakeupAttachedObjects(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    WakeupAttachedObjects(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetVeinGrowth(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetVeinGrowth(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTiberiumGrowth(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTiberiumGrowth(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetIceGrowth(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetIceGrowth(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool WakeupAllIdle(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    WakeupAllIdle(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool WakeupAllHarmless(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    WakeupAllHarmless(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool WakeupGroup(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    WakeupGroup(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayerWin(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayerWin(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayerLose(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayerLose(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EndScenario(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EndScenario(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool Apply100DamageAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    Apply100DamageAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SmallLightFlashAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SmallLightFlashAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MediumLightFlashAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MediumLightFlashAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LargeLightFlashAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LargeLightFlashAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SellAttachedBuildings(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SellAttachedBuildings(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool BerserkAttachedInfantry(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    BerserkAttachedInfantry(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SendAttachedBuildingsOffline(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SendAttachedBuildingsOffline(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SendAttachedBuildingsOnline(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SendAttachedBuildingsOnline(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SwitchAttachedObjectsToHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SwitchAttachedObjectsToHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SwitchAllObjectsToHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SwitchAllObjectsToHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MindControlBuildingsOfHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MindControlBuildingsOfHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RelinquishMindControlOfBuildingsOfHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RelinquishMindControlOfBuildingsOfHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PrintMessage(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PrintMessage(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MakeTwoHousesAlly(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MakeTwoHousesAlly(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MakeTwoHousesEnemy(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MakeTwoHousesEnemy(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTargetCell(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTargetCell(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool GrowShroud(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    GrowShroud(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool GlobalSet(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    GlobalSet(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool GlobalClear(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    GlobalClear(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RevealAroundWaypoint(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RevealAroundWaypoint(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ReduceTiberiumAt(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ReduceTiberiumAt(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RevealZoneOfWaypoint(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RevealZoneOfWaypoint(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerStart(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerStart(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerStop(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerStop(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerExtend(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerExtend(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerShorten(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerShorten(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerStartWithText(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerStartWithText(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool MissionTimerSetText(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    MissionTimerSetText(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayMovie(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayMovie(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayMovieInSidebar(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayMovieInSidebar(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayMovieInSidebarPauseGame(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayMovieInSidebarPauseGame(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayAudio(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayAudio(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayAudioAtRandomWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayAudioAtRandomWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayAudioAtSpecificWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayAudioAtSpecificWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool StopAudioAtSpecificWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    StopAudioAtSpecificWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool TeleportAllHouseObjectTo(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    TeleportAllHouseObjectTo(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ReshroudMapAroundWaypoint(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ReshroudMapAroundWaypoint(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayTheme(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayTheme(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayEVA(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayEVA(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool Grant1ShotSW(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    Grant1ShotSW(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool GrantPermanentSW(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    GrantPermanentSW(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DiplayDropFlare(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DiplayDropFlare(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool WinnerIs(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    WinnerIs(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LoserIs(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LoserIs(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EnableProductionForHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EnableProductionForHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool FireSale(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    FireSale(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EnableAutocreateForHouse(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EnableAutocreateForHouse(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool CreateTeam(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    CreateTeam(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAllInstancesOfTeam(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAllInstancesOfTeam(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SpawnTeam(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SpawnTeam(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SpawnTeamAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SpawnTeamAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAttached(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAttached(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResizePlayerView(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResizePlayerView(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayAnimAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayAnimAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool FireWeaponAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    FireWeaponAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PlayVoxelAnimAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PlayVoxelAnimAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LightningStormStart(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LightningStormStart(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LightningStormStop(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LightningStormStop(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool JumpCameraHome(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    JumpCameraHome(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ZoomIn(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ZoomIn(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ZoomOut(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ZoomOut(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetAttachedSpotlightBehaviour(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetAttachedSpotlightBehaviour(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DeleteTrigger(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DeleteTrigger(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DeleteTag(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DeleteTag(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ForceTrigger(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ForceTrigger(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EnableTrigger(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EnableTrigger(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RadarEventAdd(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RadarEventAdd(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LocalSet(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LocalSet(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LocalClear(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LocalClear(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ClearSmudges(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ClearSmudges(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool StartMeteorShower(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    StartMeteorShower(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetAmbientChangeStep(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetAmbientChangeStep(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetAmbientChangeRate(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetAmbientChangeRate(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTintRed(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTintRed(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTintGreen(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTintGreen(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTintBlue(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTintBlue(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetAmbientLevel(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetAmbientLevel(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetChronoScreenEffectState(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetChronoScreenEffectState(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EnableAITriggers(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EnableAITriggers(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DisableAITriggers(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DisableAITriggers(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool Cheer(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    Cheer(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RestoreStartingUnitsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RestoreStartingUnitsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RestoreStartingBuildingsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RestoreStartingBuildingsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAllObjectsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAllObjectsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAllBuildingsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAllBuildingsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAllNonNavalUnitsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAllNonNavalUnitsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool DestroyAllNavalUnitsOf(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    DestroyAllNavalUnitsOf(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetRatioAITeam(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetRatioAITeam(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetRatioAITeamAircraft(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetRatioAITeamAircraft(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetRatioAITeamInfantry(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetRatioAITeamInfantry(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetRatioAITeamUnits(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetRatioAITeamUnits(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool IonBlastAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    IonBlastAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool NukeAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    NukeAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool LightningStormAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    LightningStormAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool IronCurtainAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    IronCurtainAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetTechLevelOfTechnoType(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetTechLevelOfTechnoType(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ChronoInTeam(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ChronoInTeam(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool CrateAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    CrateAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ChemLauncherAtWP(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ChemLauncherAtWP(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ToggleTrainCrate(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ToggleTrainCrate(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool RadarBlackout(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    RadarBlackout(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool FlashTeamFor(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    FlashTeamFor(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool TalkBubble(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    TalkBubble(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool PauseScenarioFor(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    PauseScenarioFor(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool EjectOccupantsOfFirstAttachedBuilding(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    EjectOccupantsOfFirstAttachedBuilding(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SwitchToTab(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SwitchToTab(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool FlashCameo(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    FlashCameo(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SpawnBuilding(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SpawnBuilding(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetSWChargeLevel(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetSWChargeLevel(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetSWRechargeTime(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetSWRechargeTime(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResetSWRechargeTime(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResetSWRechargeTime(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResetSW(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResetSW(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetPreferredTargetCell(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetPreferredTargetCell(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResetTargetCell(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResetTargetCell(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetDefenseCell(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetDefenseCell(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResetDefenseCell(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResetDefenseCell(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool SetBaseCenter(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    SetBaseCenter(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool ResetBaseCenter(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    ResetBaseCenter(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // public bool FlashBuildingsOfType(HouseClass * pTargetHouse, ObjectClass * pSourceObject, TriggerClass * pTrigger, CellStruct const& location)
    FlashBuildingsOfType(pTargetHouse_0 : HouseClass, pSourceObject_1 : ObjectClass, pTrigger_2 : TriggerClass, location_3 : CellStruct) : boolean;
    // WHEEEEEW. End of slave functions.
    // public HouseClass * FindHouseByIndex(TriggerClass * pTrigger, int idxHouse) const
    FindHouseByIndex(pTrigger_0 : TriggerClass, idxHouse_1 : number) : HouseClass;
    // public static AbstractType const AbsID = AbstractType::Action
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<TActionClass *>, 11593304> const Array = 0xB0E658u
    static s_Array : DynamicVectorClass<TActionClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public TActionClass * NextAction
    m_NextAction : TActionClass;
    // public TriggerAction ActionKind
    m_ActionKind : TriggerAction;
    // public TeamTypeClass * TeamType
    m_TeamType : TeamTypeClass;
    // public int Waypoint
    m_Waypoint : number;
    // multipurpose
    // public int Value2
    m_Value2 : number;
    // public TagTypeClass * TagType
    m_TagType : TagTypeClass;
    // public TriggerTypeClass * TriggerType
    m_TriggerType : TriggerTypeClass;
    // public char[25] TechnoID
    m_TechnoID : string;
    // public char[32] Text
    m_Text : string;
    // multipurpose
    // public int Value
    m_Value : number;
    // map bounds for use with action 40
    // public RectangleStruct Bounds
    m_Bounds : RectangleStruct;
    // public int Param3
    m_Param3 : number;
    // public int Param4
    m_Param4 : number;
    // public int Param5
    m_Param5 : number;
    // public int Param6
    m_Param6 : number;
}
// forward declarations
// TriggerClass
class TriggerClass
    extends AbstractClass
{
    // Constructor
    // public TriggerClass(TriggerTypeClass * pType)
    constructor(pType_0 : TriggerTypeClass);
    // finds an instance using the type, or creates one
    // public static TriggerClass * GetInstance(TriggerTypeClass * pType)
    static GetInstance(pType_0 : TriggerTypeClass) : TriggerClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual void PointerExpired(AbstractClass * pAbstract, bool removed)
    PointerExpired(pAbstract_0 : AbstractClass | any, removed_1 : boolean | any) : void;
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any | any) : void;
    // contains at least one Crosses Horizontal Line event
    // public bool HasCrossesHorizontalLineEvent() const
    HasCrossesHorizontalLineEvent() : boolean;
    // contains at least one Crosses Vertical Line event
    // public bool HasCrossesVerticalLineEvent() const
    HasCrossesVerticalLineEvent() : boolean;
    // contains at least one Zone Entry By event
    // public bool HasZoneEntryByEvent() const
    HasZoneEntryByEvent() : boolean;
    // contains at least one Allow Win action
    // public bool HasAllowWinAction() const
    HasAllowWinAction() : boolean;
    // contains at least one Global Set or Global Cleared event
    // public bool HasGlobalSetOrClearedEvent(int idxGlobal) const
    HasGlobalSetOrClearedEvent(idxGlobal_0 : number) : boolean;
    // called when a global is updated. resets timers
    // public void NotifyGlobalChanged(int idxGlobal)
    NotifyGlobalChanged(idxGlobal_0 : number) : void;
    // called when a local is updated. resets timers
    // public void NotifyLocalChanged(int idxLocal)
    NotifyLocalChanged(idxLocal_0 : number) : void;
    // resets the timers for all Elapsed Time and Random Delay events
    // public void ResetTimers()
    ResetTimers() : void;
    // public void MarkEventAsOccured(int idx)
    MarkEventAsOccured(idx_0 : number) : void;
    // public void MarkEventAsNotOccured(int idx)
    MarkEventAsNotOccured(idx_0 : number) : void;
    // public bool HasEventOccured(int idx) const
    HasEventOccured(idx_0 : number) : boolean;
    // public void Destroy()
    Destroy() : void;
    // public bool HasBeenDestroyed() const
    HasBeenDestroyed() : boolean;
    // public void SetHouse(HouseClass * pHouse)
    SetHouse(pHouse_0 : HouseClass) : void;
    // public HouseClass * GetHouse() const
    GetHouse() : HouseClass;
    // enables the trigger and resets the timers
    // public void Enable()
    Enable() : void;
    // public void Disable()
    Disable() : void;
    // called whenever an event bubbles up, returns true if all of this
    // trigger's events occured. persistent events are remembered
    // public bool RegisterEvent(TriggerEvent event, ObjectClass * pObject, bool forceFire, bool persistent, TechnoClass * pSource)
    RegisterEvent(event_0 : TriggerEvent, pObject_1 : ObjectClass, forceFire_2 : boolean, persistent_3 : boolean, pSource_4 : TechnoClass) : boolean;
    // returns whether any action was executed
    // public bool FireActions(ObjectClass * pObj, CellStruct location)
    FireActions(pObj_0 : ObjectClass, location_1 : CellStruct) : boolean;
    // public static AbstractType const AbsID = AbstractType::Trigger
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<TriggerClass *>, 11070184> const Array = 0xA8EAE8u
    static s_Array : DynamicVectorClass<TriggerClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TriggerTypeClass * Type
    m_Type : TriggerTypeClass;
    // public TriggerClass * NextTrigger
    m_NextTrigger : TriggerClass;
    // public HouseClass * House
    m_House : HouseClass;
    // ActionClass::DestroyTrigger called on
    // public bool Destroyed
    m_Destroyed : boolean;
    // public CDTimerClass Timer
    m_Timer : CDTimerClass;
    // bitfield for 32 events max
    // public unsigned long OccuredEvents
    m_OccuredEvents : number;
    // public bool Enabled
    m_Enabled : boolean;
}
// The AbstractClass is the base class of all game objects.
// TEventClass
class TEventClass
    extends AbstractClass
{
    // Constructor
    // public TEventClass()
    constructor();
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // you are responsible for doing INI::ReadString and strtok'ing it before calling
    // this func only calls strtok again, doesn't know anything about buffers
    // public void LoadFromINI()
    LoadFromINI() : void;
    // you allocate the buffer for this, and save it to ini yourself after this returns
    // this func only sprintf's the stuff it needs into buffer
    // public void PrepareSaveToINI(char * buffer) const
    PrepareSaveToINI(buffer_0 : string) : void;
    // public static TriggerAttachType GetAttachType(int eventKind)
    static GetAttachType(eventKind_0 : number) : TriggerAttachType;
    // used in TriggerClass::HaveEventsOccured , when trigger is repeating
    // both need to be true to check this event as done
    // public bool GetStateA() const
    GetStateA() : boolean;
    // public bool GetStateB() const
    GetStateB() : boolean;
    // main brain
    // public bool HasOccured(int eventKind, HouseClass * pHouse, ObjectClass * Object, CDTimerClass * ActivationFrame, bool * isRepeating) const
    HasOccured(eventKind_0 : number, pHouse_1 : HouseClass, Object_2 : ObjectClass, ActivationFrame_3 : CDTimerClass, isRepeating_4 : boolean) : boolean;
    // public static AbstractType const AbsID = AbstractType::Event
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<TEventClass *>, 11596192> const Array = 0xB0F1A0u
    static s_Array : DynamicVectorClass<TEventClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public TEventClass * NextEvent
    m_NextEvent : TEventClass;
    // public TriggerEvent EventKind
    m_EventKind : TriggerEvent;
    // If this event needs to reference a team type, then this is the pointer to the team type object.
    // public TeamTypeClass * TeamType
    m_TeamType : TeamTypeClass;
    // public int Value
    m_Value : number;
    // public char[28] String
    m_String : string;
    // public HouseClass * House
    m_House : HouseClass;
}
// ---
// HouseTypeClass
class HouseTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public HouseTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static HouseTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : HouseTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // helpers
    // public HouseTypeClass * FindParentCountry() const
    FindParentCountry() : HouseTypeClass;
    // public int FindParentCountryIndex() const
    FindParentCountryIndex() : number;
    // public static int FindIndexOfName(char const * name)
    static FindIndexOfName(name_0 : string) : number;
    // public static AbstractType const AbsID = AbstractType::HouseType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<HouseTypeClass *>, 11025560> const Array = 0xA83C98u
    static s_Array : DynamicVectorClass<HouseTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public FixedString<25, char> ParentCountry
    m_ParentCountry : any;
    // public int ArrayIndex
    m_ArrayIndex : number;
    // dunno why
    // public int ArrayIndex2
    m_ArrayIndex2 : number;
    // public int SideIndex
    m_SideIndex : number;
    // public int ColorSchemeIndex
    m_ColorSchemeIndex : number;
    // are these unused TS leftovers?
    // public double FirepowerMult
    m_FirepowerMult : number;
    // public double GroundspeedMult
    m_GroundspeedMult : number;
    // public double AirspeedMult
    m_AirspeedMult : number;
    // public double ArmorMult
    m_ArmorMult : number;
    // public double ROFMult
    m_ROFMult : number;
    // public double CostMult
    m_CostMult : number;
    // public double BuildtimeMult
    m_BuildtimeMult : number;
    // ---
    // public float ArmorInfantryMult
    m_ArmorInfantryMult : number;
    // public float ArmorUnitsMult
    m_ArmorUnitsMult : number;
    // public float ArmorAircraftMult
    m_ArmorAircraftMult : number;
    // public float ArmorBuildingsMult
    m_ArmorBuildingsMult : number;
    // public float ArmorDefensesMult
    m_ArmorDefensesMult : number;
    // public float CostInfantryMult
    m_CostInfantryMult : number;
    // public float CostUnitsMult
    m_CostUnitsMult : number;
    // public float CostAircraftMult
    m_CostAircraftMult : number;
    // public float CostBuildingsMult
    m_CostBuildingsMult : number;
    // public float CostDefensesMult
    m_CostDefensesMult : number;
    // public float SpeedInfantryMult
    m_SpeedInfantryMult : number;
    // public float SpeedUnitsMult
    m_SpeedUnitsMult : number;
    // public float SpeedAircraftMult
    m_SpeedAircraftMult : number;
    // public float BuildtimeInfantryMult
    m_BuildtimeInfantryMult : number;
    // public float BuildtimeUnitsMult
    m_BuildtimeUnitsMult : number;
    // public float BuildtimeAircraftMult
    m_BuildtimeAircraftMult : number;
    // public float BuildtimeBuildingsMult
    m_BuildtimeBuildingsMult : number;
    // public float BuildtimeDefensesMult
    m_BuildtimeDefensesMult : number;
    // public float IncomeMult
    m_IncomeMult : number;
    // public TypeList<InfantryTypeClass *> VeteranInfantry
    m_VeteranInfantry : TypeList<InfantryTypeClass>;
    // public TypeList<UnitTypeClass *> VeteranUnits
    m_VeteranUnits : TypeList<UnitTypeClass>;
    // public TypeList<AircraftTypeClass *> VeteranAircraft
    m_VeteranAircraft : TypeList<AircraftTypeClass>;
    // public char[4] Suffix
    m_Suffix : string;
    // public char Prefix
    m_Prefix : number;
    // public bool Multiplay
    m_Multiplay : boolean;
    // public bool MultiplayPassive
    m_MultiplayPassive : boolean;
    // public bool WallOwner
    m_WallOwner : boolean;
    // "smart"?
    // public bool SmartAI
    m_SmartAI : boolean;
}
// forward declarations
// AircraftTypeClass
class AircraftTypeClass
    extends TechnoTypeClass
{
    // Constructor
    // public AircraftTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static AircraftTypeClass * Find(char const * pID)
    static Find(pID_0 : string | any) : AircraftTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string | any) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::AircraftType
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7E2868
    static s_AbsVTable : number;
    // Array
    // public static constant_ptr<DynamicVectorClass<AircraftTypeClass *>, 11055640> const Array = 0xA8B218u
    static s_Array : DynamicVectorClass<AircraftTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public bool Carryall
    m_Carryall : boolean;
    // public AnimTypeClass * Trailer
    m_Trailer : AnimTypeClass;
    // public int SpawnDelay
    m_SpawnDelay : number;
    // public bool Rotors
    m_Rotors : boolean;
    // public bool CustomRotor
    m_CustomRotor : boolean;
    // public bool Landable
    m_Landable : boolean;
    // public bool FlyBy
    m_FlyBy : boolean;
    // public bool FlyBack
    m_FlyBack : boolean;
    // public bool AirportBound
    m_AirportBound : boolean;
    // public bool Fighter
    m_Fighter : boolean;
}
// ---
// ScriptTypeClass
class ScriptTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public ScriptTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static ScriptTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : ScriptTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static ScriptTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : ScriptTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // AbstractTypeClass
    // public static bool LoadFromINIList(CCINIClass * pINI, bool IsGlobal)
    static LoadFromINIList(pINI_0 : CCINIClass, IsGlobal_1 : boolean) : boolean;
    // public static AbstractType const AbsID = AbstractType::ScriptType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<ScriptTypeClass *>, 9126344> const Array = 0x8B41C8u
    static s_Array : DynamicVectorClass<ScriptTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public bool IsGlobal
    m_IsGlobal : boolean;
    // public int ActionsCount
    m_ActionsCount : number;
    // public ScriptActionNode[50] ScriptActions
    m_ScriptActions : ScriptActionNode;
}
// ScriptActionNode
class ScriptActionNode
{
    // public int Action
    m_Action : number;
    // public int Argument
    m_Argument : number;
}
// ---
// TaskForceClass
class TaskForceClass
    extends AbstractTypeClass
{
    // Constructor
    // public TaskForceClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static TaskForceClass * Find(char const * pID)
    static Find(pID_0 : string) : TaskForceClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::TaskForce
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TaskForceClass *>, 11069648> const Array = 0xA8E8D0u
    static s_Array : DynamicVectorClass<TaskForceClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int Group
    m_Group : number;
    // public int CountEntries
    m_CountEntries : number;
    // public bool IsGlobal
    m_IsGlobal : boolean;
    // public TaskForceEntryStruct[6] Entries
    m_Entries : TaskForceEntryStruct;
}
// TaskForceEntryStruct
class TaskForceEntryStruct
{
    // public int Amount
    m_Amount : number;
    // public TechnoTypeClass * Type
    m_Type : TechnoTypeClass;
}
// The AbstractClass is the base class of all game objects.
// ScriptClass
class ScriptClass
    extends AbstractClass
{
    // Constructor
    // public ScriptClass(ScriptTypeClass * pType)
    constructor(pType_0 : ScriptTypeClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public ScriptActionNode * GetCurrentAction(ScriptActionNode * buffer) const
    GetCurrentAction(buffer_0 : ScriptActionNode) : ScriptActionNode;
    // public ScriptActionNode * GetNextAction(ScriptActionNode * buffer) const
    GetNextAction(buffer_0 : ScriptActionNode) : ScriptActionNode;
    // public bool ClearMission()
    ClearMission() : boolean;
    // public bool SetMission(int nLine)
    SetMission(nLine_0 : number) : boolean;
    // public bool NextMission()
    NextMission() : boolean;
    // public bool HasNextMission() const
    HasNextMission() : boolean;
    // public static AbstractType const AbsID = AbstractType::Script
    static s_AbsID : AbstractType;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public ScriptTypeClass * Type
    m_Type : ScriptTypeClass;
    // public int field_28
    m_field_28 : number;
    // public int CurrentMission
    m_CurrentMission : number;
}
// The AbstractClass is the base class of all game objects.
// ParasiteClass
class ParasiteClass
    extends AbstractClass
{
    // Constructor
    // public ParasiteClass(FootClass * pOwner = nullptr)
    constructor(pOwner_0 : FootClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void UpdateSquid()
    UpdateSquid() : void;
    // public bool UpdateGrapple()
    UpdateGrapple() : boolean;
    // public void ExitUnit()
    ExitUnit() : void;
    // public bool CanInfect(FootClass * pTarget) const
    CanInfect(pTarget_0 : FootClass) : boolean;
    // public void TryInfect(FootClass * pTarget)
    TryInfect(pTarget_0 : FootClass) : void;
    // public bool CanExistOnVictimCell() const
    CanExistOnVictimCell() : boolean;
    // public static AbstractType const AbsID = AbstractType::Parasite
    static s_AbsID : AbstractType;
    // public static constant_ptr<DynamicVectorClass<ParasiteClass *>, 11290896> const Array = 0xAC4910u
    static s_Array : DynamicVectorClass<ParasiteClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public FootClass * Owner
    m_Owner : FootClass;
    // public FootClass * Victim
    m_Victim : FootClass;
    // public CDTimerClass SuppressionTimer
    m_SuppressionTimer : CDTimerClass;
    // public CDTimerClass DamageDeliveryTimer
    m_DamageDeliveryTimer : CDTimerClass;
    // public AnimClass * GrappleAnim
    m_GrappleAnim : AnimClass;
    // public ParasiteState GrappleState
    m_GrappleState : ParasiteState;
    // public int GrappleAnimFrame
    m_GrappleAnimFrame : number;
    // public int GrappleAnimDelay
    m_GrappleAnimDelay : number;
    // public bool GrappleAnimGotInvalid
    m_GrappleAnimGotInvalid : boolean;
}
// forward declarations
// BuildingLightClass
class BuildingLightClass
    extends ObjectClass
{
    // Constructor
    // public BuildingLightClass(ObjectClass * pOwner)
    constructor(pOwner_0 : ObjectClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void SetBehaviour(SpotlightBehaviour mode)
    SetBehaviour(mode_0 : SpotlightBehaviour) : void;
    // public static AbstractType const AbsID = AbstractType::BuildingLight
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<BuildingLightClass *>, 9126288> const Array = 0x8B4190u
    static s_Array : DynamicVectorClass<BuildingLightClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public double Speed
    m_Speed : number;
    // public CoordStruct field_B8
    m_field_B8 : CoordStruct;
    // public CoordStruct field_C4
    m_field_C4 : CoordStruct;
    // public double Acceleration
    m_Acceleration : number;
    // public bool Direction
    m_Direction : boolean;
    // public SpotlightBehaviour BehaviourMode
    m_BehaviourMode : SpotlightBehaviour;
    // public ObjectClass * FollowingObject
    m_FollowingObject : ObjectClass;
    // public TechnoClass * OwnerObject
    m_OwnerObject : TechnoClass;
}
// The AbstractClass is the base class of all game objects.
// LightSourceClass
class LightSourceClass
    extends AbstractClass
{
    // Constructor
    // public LightSourceClass(int X, int Y, int Z, int nVisibility, int nIntensity, int Red, int Green, int Blue)
    constructor(X_0 : number, Y_1 : number, Z_2 : number, nVisibility_3 : number, nIntensity_4 : number, Red_5 : number, Green_6 : number, Blue_7 : number);
    // public LightSourceClass(CoordStruct Crd, int nVisibility, int nIntensity, TintStruct Tint)
    constructor(Crd_0 : CoordStruct, nVisibility_1 : number, nIntensity_2 : number, Tint_3 : TintStruct);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void Activate(unsigned long dwZero = 0)
    Activate(dwZero_0 : number) : void;
    // public void Deactivate(unsigned long dwZero = 0)
    Deactivate(dwZero_0 : number) : void;
    // public void ChangeLevels(int nIntensity, TintStruct Tint, char mode)
    ChangeLevels(nIntensity_0 : number, Tint_1 : TintStruct, mode_2 : number) : void;
    // public static void UpdateLightConverts(int value)
    static UpdateLightConverts(value_0 : number) : void;
    // public static AbstractType const AbsID = AbstractType::LightSource
    static s_AbsID : AbstractType;
    // public static constant_ptr<DynamicVectorClass<LightSourceClass *>, 11258384> const Array = 0xABCA10
    static s_Array : DynamicVectorClass<LightSourceClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int LightIntensity
    m_LightIntensity : number;
    // public TintStruct LightTint
    m_LightTint : TintStruct;
    // public int DetailLevel
    m_DetailLevel : number;
    // public CoordStruct Location
    m_Location : CoordStruct;
    // public int LightVisibility
    m_LightVisibility : number;
    // public bool Activated
    m_Activated : boolean;
}
// forward declarations
// UnitClass
class UnitClass
    extends FootClass
{
    // Constructor
    // public UnitClass(UnitTypeClass * pType, HouseClass * pOwner)
    constructor(pType_0 : UnitTypeClass, pOwner_1 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectClass
    // public virtual Action MouseOverCell(CellStruct const * pCell, bool checkFog = false, bool ignoreForce = false) const
    MouseOverCell(pCell_0 : CellStruct | any, checkFog_1 : boolean | any, ignoreForce_2 : boolean | any) : Action;
    // public virtual Action MouseOverObject(ObjectClass const * pObject, bool ignoreForce = false) const
    MouseOverObject(pObject_0 : ObjectClass | any, ignoreForce_1 : boolean | any) : Action;
    // public virtual void MarkAllOccupationBits(CoordStruct const& coords)
    MarkAllOccupationBits(coords_0 : CoordStruct | any) : void;
    // public virtual void UnmarkAllOccupationBits(CoordStruct const& coords)
    UnmarkAllOccupationBits(coords_0 : CoordStruct | any) : void;
    // ...and so on
    // FIXME other virtual function explicit addresses
    // public virtual FireError GetFireError(AbstractClass * pTarget, int nWeaponIndex, bool ignoreRange) const
    GetFireError(pTarget_0 : AbstractClass | any, nWeaponIndex_1 : number | any, ignoreRange_2 : boolean | any) : FireError;
    // UnitClass
    // main drawing functions - Draw() calles one of these, they call parent's Draw_A_smth
    // public virtual void DrawAsVXL(Point2D Coords, RectangleStruct BoundingRect, int Brightness, int Tint)
    DrawAsVXL(Coords_0 : Point2D, BoundingRect_1 : RectangleStruct, Brightness_2 : number, Tint_3 : number) : void;
    // public virtual void DrawAsSHP(Point2D Coords, RectangleStruct BoundingRect, int Brightness, int Tint)
    DrawAsSHP(Coords_0 : Point2D, BoundingRect_1 : RectangleStruct, Brightness_2 : number, Tint_3 : number) : void;
    // public virtual void DrawObject(Surface * pSurface, Point2D Coords, RectangleStruct CacheRect, int Brightness, int Tint)
    DrawObject(pSurface_0 : Surface | any, Coords_1 : Point2D | any, CacheRect_2 : RectangleStruct | any, Brightness_3 : number | any, Tint_4 : number | any) : void;
    // non-virtual
    // public bool IsDeactivated() const
    IsDeactivated() : boolean;
    // public void UpdateTube()
    UpdateTube() : void;
    // public void UpdateRotation()
    UpdateRotation() : void;
    // public void UpdateEdgeOfWorld()
    UpdateEdgeOfWorld() : void;
    // public void UpdateFiring()
    UpdateFiring() : void;
    // public void UpdateVisceroid()
    UpdateVisceroid() : void;
    // public void UpdateDisguise()
    UpdateDisguise() : void;
    // public void Explode()
    Explode() : void;
    // public bool GotoClearSpot()
    GotoClearSpot() : boolean;
    // public bool TryToDeploy()
    TryToDeploy() : boolean;
    // public void Deploy()
    Deploy() : void;
    // public void Undeploy()
    Undeploy() : void;
    // public bool Harvesting()
    Harvesting() : boolean;
    // public bool FlagAttach(int nHouseIdx)
    FlagAttach(nHouseIdx_0 : number) : boolean;
    // public bool FlagRemove()
    FlagRemove() : boolean;
    // public void APCCloseDoor()
    APCCloseDoor() : void;
    // public void APCOpenDoor()
    APCOpenDoor() : void;
    // public static void ReadINI(CCINIClass * pINI)
    static ReadINI(pINI_0 : CCINIClass) : void;
    // public static void WriteINI(CCINIClass * pINI)
    static WriteINI(pINI_0 : CCINIClass) : void;
    // public bool ShouldCrashIt(TechnoClass * pTarget)
    ShouldCrashIt(pTarget_0 : TechnoClass) : boolean;
    // public AbstractClass * AssignDestination_7447B0(AbstractClass * pTarget)
    AssignDestination_7447B0(pTarget_0 : AbstractClass) : AbstractClass;
    // public bool AStarAttempt(CellStruct const& cell1, CellStruct const& cell2)
    AStarAttempt(cell1_0 : CellStruct, cell2_1 : CellStruct) : boolean;
    // public static AbstractType const AbsID = AbstractType::Unit
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7F5C70
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<UnitClass *>, 9126152> const Array = 0x8B4108u
    static s_Array : DynamicVectorClass<UnitClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int unknown_int_6C0
    m_unknown_int_6C0 : number;
    // public UnitTypeClass * Type
    m_Type : UnitTypeClass;
    // groovy - link defined in the map's [Units] section, looked up on startup
    // public UnitClass * FollowerCar
    m_FollowerCar : UnitClass;
    // Carrying the flag of this House
    // public int FlagHouseIndex
    m_FlagHouseIndex : number;
    // This vehicle is another vehicle's FollowerCar (such as a train car following train).
    // public bool IsFollowerCar
    m_IsFollowerCar : boolean;
    // public bool Unloading
    m_Unloading : boolean;
    // public bool IsHarvesting
    m_IsHarvesting : boolean;
    // public bool TerrainPalette
    m_TerrainPalette : boolean;
    // public int unknown_int_6D4
    m_unknown_int_6D4 : number;
    // public int DeathFrameCounter
    m_DeathFrameCounter : number;
    // Unit is the owner of this
    // public EBolt * ElectricBolt
    m_ElectricBolt : EBolt;
    // public bool Deployed
    m_Deployed : boolean;
    // public bool Deploying
    m_Deploying : boolean;
    // public bool Undeploying
    m_Undeploying : boolean;
    // Set when unloading passengers. Units with TurretCount>0 will not unload the gunner.
    // public int NonPassengerCount
    m_NonPassengerCount : number;
    // public wchar_t[256] ToolTipText
    m_ToolTipText : number;
}
// Surface
class Surface
{
    // public Surface()
    constructor();
    // Surface
    // public virtual bool CopyFromWhole(Surface * pSrc, bool bUnk1, bool bUnk2)
    CopyFromWhole(pSrc_0 : Surface, bUnk1_1 : boolean, bUnk2_2 : boolean) : boolean;
    // public virtual bool CopyFromPart(RectangleStruct * pClipRect, Surface * pSrc, RectangleStruct * pSrcRect, bool bUnk1, bool bUnk2)
    CopyFromPart(pClipRect_0 : RectangleStruct, pSrc_1 : Surface, pSrcRect_2 : RectangleStruct, bUnk1_3 : boolean, bUnk2_4 : boolean) : boolean;
    // public virtual bool CopyFrom(RectangleStruct * pClipRect, RectangleStruct * pClipRect2, Surface * pSrc, RectangleStruct * pDestRect, RectangleStruct * pSrcRect, bool bUnk1, bool bUnk2)
    CopyFrom(pClipRect_0 : RectangleStruct, pClipRect2_1 : RectangleStruct, pSrc_2 : Surface, pDestRect_3 : RectangleStruct, pSrcRect_4 : RectangleStruct, bUnk1_5 : boolean, bUnk2_6 : boolean) : boolean;
    // public virtual bool FillRectEx(RectangleStruct * pClipRect, RectangleStruct * pFillRect, unsigned long nColor)
    FillRectEx(pClipRect_0 : RectangleStruct, pFillRect_1 : RectangleStruct, nColor_2 : number) : boolean;
    // public virtual bool FillRect(RectangleStruct * pFillRect, unsigned long nColor)
    FillRect(pFillRect_0 : RectangleStruct, nColor_1 : number) : boolean;
    // public virtual bool Fill(unsigned long nColor)
    Fill(nColor_0 : number) : boolean;
    // public virtual bool FillRectTrans(RectangleStruct * pClipRect, ColorStruct * pColor, int nOpacity)
    FillRectTrans(pClipRect_0 : RectangleStruct, pColor_1 : ColorStruct, nOpacity_2 : number) : boolean;
    // public virtual bool DrawEllipse(int XOff, int YOff, int CenterX, int CenterY, RectangleStruct Rect, unsigned long nColor)
    DrawEllipse(XOff_0 : number, YOff_1 : number, CenterX_2 : number, CenterY_3 : number, Rect_4 : RectangleStruct, nColor_5 : number) : boolean;
    // public virtual bool SetPixel(Point2D * pPoint, unsigned long nColor)
    SetPixel(pPoint_0 : Point2D, nColor_1 : number) : boolean;
    // public virtual unsigned long GetPixel(Point2D * pPoint)
    GetPixel(pPoint_0 : Point2D) : number;
    // public virtual bool DrawLineEx(RectangleStruct * pClipRect, Point2D * pStart, Point2D * pEnd, unsigned long nColor)
    DrawLineEx(pClipRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, nColor_3 : number) : boolean;
    // public virtual bool DrawLine(Point2D * pStart, Point2D * pEnd, unsigned long nColor)
    DrawLine(pStart_0 : Point2D, pEnd_1 : Point2D, nColor_2 : number) : boolean;
    // public virtual bool DrawLineColor_AZ(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, unsigned long nColor, unsigned long dwUnk1, unsigned long dwUnk2, bool bUnk)
    DrawLineColor_AZ(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, nColor_3 : number, dwUnk1_4 : number, dwUnk2_5 : number, bUnk_6 : boolean) : boolean;
    // public virtual bool DrawMultiplyingLine_AZ(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, unsigned long dwMultiplier, unsigned long dwUnk1, unsigned long dwUnk2, bool bUnk)
    DrawMultiplyingLine_AZ(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, dwMultiplier_3 : number, dwUnk1_4 : number, dwUnk2_5 : number, bUnk_6 : boolean) : boolean;
    // public virtual bool DrawSubtractiveLine_AZ(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, ColorStruct * pColor, unsigned long dwUnk1, unsigned long dwUnk2, bool bUnk1, bool bUnk2, bool bUkn3, bool bUkn4, float fUkn)
    DrawSubtractiveLine_AZ(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, pColor_3 : ColorStruct, dwUnk1_4 : number, dwUnk2_5 : number, bUnk1_6 : boolean, bUnk2_7 : boolean, bUkn3_8 : boolean, bUkn4_9 : boolean, fUkn_10 : number) : boolean;
    // public virtual bool DrawRGBMultiplyingLine_AZ(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, ColorStruct * pColor, float Intensity, unsigned long dwUnk1, unsigned long dwUnk2)
    DrawRGBMultiplyingLine_AZ(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, pColor_3 : ColorStruct, Intensity_4 : number, dwUnk1_5 : number, dwUnk2_6 : number) : boolean;
    // public virtual bool PlotLine(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, bool (*)(int *) * fpDrawCallback)
    PlotLine(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, fpDrawCallback_3 : any) : boolean;
    // public virtual bool DrawDashedLine(Point2D * pStart, Point2D * pEnd, int nColor, bool * Pattern, int nOffset)
    DrawDashedLine(pStart_0 : Point2D, pEnd_1 : Point2D, nColor_2 : number, Pattern_3 : boolean, nOffset_4 : number) : boolean;
    // public virtual bool DrawDashedLine_(Point2D * pStart, Point2D * pEnd, int nColor, bool * Pattern, int nOffset, bool bUkn)
    DrawDashedLine_(pStart_0 : Point2D, pEnd_1 : Point2D, nColor_2 : number, Pattern_3 : boolean, nOffset_4 : number, bUkn_5 : boolean) : boolean;
    // public virtual bool DrawLine_(Point2D * pStart, Point2D * pEnd, int nColor, bool bUnk)
    DrawLine_(pStart_0 : Point2D, pEnd_1 : Point2D, nColor_2 : number, bUnk_3 : boolean) : boolean;
    // public virtual bool DrawRectEx(RectangleStruct * pClipRect, RectangleStruct * pDrawRect, int nColor)
    DrawRectEx(pClipRect_0 : RectangleStruct, pDrawRect_1 : RectangleStruct, nColor_2 : number) : boolean;
    // public virtual bool DrawRect(RectangleStruct * pDrawRect, unsigned long dwColor)
    DrawRect(pDrawRect_0 : RectangleStruct, dwColor_1 : number) : boolean;
    // public virtual void * Lock(int X, int Y)
    Lock(X_0 : number, Y_1 : number) : void;
    // public virtual bool Unlock()
    Unlock() : boolean;
    // public virtual bool CanLock(unsigned long dwUkn1 = 0, unsigned long dwUkn2 = 0)
    CanLock(dwUkn1_0 : number, dwUkn2_1 : number) : boolean;
    // public virtual bool vt_entry_68(unsigned long dwUnk1, unsigned long dwUnk2)
    vt_entry_68(dwUnk1_0 : number, dwUnk2_1 : number) : boolean;
    // public virtual bool IsLocked()
    IsLocked() : boolean;
    // public virtual int GetBytesPerPixel()
    GetBytesPerPixel() : number;
    // public virtual int GetPitch()
    GetPitch() : number;
    // public virtual RectangleStruct * GetRect(RectangleStruct * pRect)
    GetRect(pRect_0 : RectangleStruct) : RectangleStruct;
    // public virtual int GetWidth()
    GetWidth() : number;
    // public virtual int GetHeight()
    GetHeight() : number;
    // public virtual bool IsDSurface()
    IsDSurface() : boolean;
    // Helper
    // public RectangleStruct GetRect()
    GetRect() : RectangleStruct;
    // Properties
    // public int Width
    m_Width : number;
    // public int Height
    m_Height : number;
}
// forward declarations
// EBolt
class EBolt
{
    // Constructor, Destructor
    // public EBolt()
    constructor();
    // public void SetOwner(UnitClass * pOwner, int idxWeapon)
    SetOwner(pOwner_0 : UnitClass, idxWeapon_1 : number) : void;
    // public void ClearOwner()
    ClearOwner() : void;
    // public CoordStruct * GetSourceCoords(CoordStruct * outBuffer) const
    GetSourceCoords(outBuffer_0 : CoordStruct) : CoordStruct;
    // public CoordStruct GetSourceCoords() const
    GetSourceCoords() : CoordStruct;
    // public void Fire(CoordStruct P1, CoordStruct P2, unsigned long arg18)
    Fire(P1_0 : CoordStruct, P2_1 : CoordStruct, arg18_2 : number) : void;
    // skip operator new
    // skip operator delete
    // public static constant_ptr<DynamicVectorClass<EBolt *>, 9047688> const Array = 0x8A0E88u
    static s_Array : DynamicVectorClass<EBolt>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public CoordStruct Point1
    m_Point1 : CoordStruct;
    // public CoordStruct Point2
    m_Point2 : CoordStruct;
    // Duration?
    // public unsigned long unknown_18
    m_unknown_18 : number;
    // Random number between 0 and 256
    // public int Random
    m_Random : number;
    // ingame this is a UnitClass but needed to circumvent some issues
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // which weapon # to use from owner
    // public int WeaponSlot
    m_WeaponSlot : number;
    // this is >>= 1 each time DrawAll() is called, 0 => dtor (inline). Hi, welcome to dumb ideas.
    // public int Lifetime
    m_Lifetime : number;
    // public bool AlternateColor
    m_AlternateColor : boolean;
}
// AircraftClass
// AircraftClass
class AircraftClass
    extends FootClass
{
    // Constructor
    // public AircraftClass(AircraftTypeClass * pType, HouseClass * pOwner)
    constructor(pType_0 : AircraftTypeClass, pOwner_1 : HouseClass);
    // IFlyControl
    // public virtual int Landing_Altitude()
    Landing_Altitude() : number;
    // public virtual int Landing_Direction()
    Landing_Direction() : number;
    // public virtual long Is_Loaded()
    Is_Loaded() : number;
    // public virtual long Is_Strafe()
    Is_Strafe() : number;
    // public virtual long Is_Fighter()
    Is_Fighter() : number;
    // public virtual long Is_Locked()
    Is_Locked() : number;
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public AbstractClass * FindFireLocation(AbstractClass * pTarget)
    FindFireLocation(pTarget_0 : AbstractClass) : AbstractClass;
    // public static AbstractType const AbsID = AbstractType::Aircraft
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7E22A4
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<AircraftClass *>, 11068304> const Array = 0xA8E390u
    static s_Array : DynamicVectorClass<AircraftClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public AircraftTypeClass * Type
    m_Type : AircraftTypeClass;
    // Whether or not to deduct ammo after firing run (strafing) is over
    // public bool ShouldLoseAmmo
    m_ShouldLoseAmmo : boolean;
    // parachutes
    // public bool HasPassengers
    m_HasPassengers : boolean;
    // when crashing down, duh
    // public bool IsKamikaze
    m_IsKamikaze : boolean;
    // public BuildingClass * DockNowHeadingTo
    m_DockNowHeadingTo : BuildingClass;
    // public bool unknown_bool_6D0
    m_unknown_bool_6D0 : boolean;
    // public bool unknown_bool_6D1
    m_unknown_bool_6D1 : boolean;
    // Whether or not aircraft is locked to a firing run (strafing)
    // public bool IsLocked
    m_IsLocked : boolean;
    // public char NumParadropsLeft
    m_NumParadropsLeft : number;
    // public bool IsCarryallNotLanding
    m_IsCarryallNotLanding : boolean;
    // Aircraft finished attack run and/or went idle and is now returning from it
    // public bool IsReturningFromAttackRun
    m_IsReturningFromAttackRun : boolean;
}
// forward declarations
// TerrainClass
class TerrainClass
    extends ObjectClass
{
    // Constructor, Destructor
    // public TerrainClass(TerrainTypeClass * tt, CellStruct coords)
    constructor(tt_0 : TerrainTypeClass, coords_1 : CellStruct);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // identification
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::Terrain
    static s_AbsID : AbstractType;
    // global array
    // public static constant_ptr<DynamicVectorClass<TerrainClass *>, 11069832> const Array = 0xA8E988u
    static s_Array : DynamicVectorClass<TerrainClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public StageClass Animation
    m_Animation : StageClass;
    // public TerrainTypeClass * Type
    m_Type : TerrainTypeClass;
    // this terrain object has been ignited
    // public bool IsBurning
    m_IsBurning : boolean;
    // finish the animation and uninit
    // public bool IsCrumbling
    m_IsCrumbling : boolean;
    // public RectangleStruct unknown_rect_D0
    m_unknown_rect_D0 : RectangleStruct;
}
// ---
// TerrainTypeClass
class TerrainTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public TerrainTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static TerrainTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : TerrainTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static TerrainTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : TerrainTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::TerrainType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TerrainTypeClass *>, 11068184> const Array = 0xA8E318u
    static s_Array : DynamicVectorClass<TerrainTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public int Foundation
    m_Foundation : number;
    // public ColorStruct RadarColor
    m_RadarColor : ColorStruct;
    // public int AnimationRate
    m_AnimationRate : number;
    // public float AnimationProbability
    m_AnimationProbability : number;
    // public int TemperateOccupationBits
    m_TemperateOccupationBits : number;
    // public int SnowOccupationBits
    m_SnowOccupationBits : number;
    // public bool WaterBound
    m_WaterBound : boolean;
    // public bool SpawnsTiberium
    m_SpawnsTiberium : boolean;
    // public bool IsFlammable
    m_IsFlammable : boolean;
    // public bool IsAnimated
    m_IsAnimated : boolean;
    // public bool IsVeinhole
    m_IsVeinhole : boolean;
    // public CellStruct * FoundationData
    m_FoundationData : CellStruct;
}
// ---
// TiberiumClass
class TiberiumClass
    extends AbstractTypeClass
{
    // Constructor
    // public TiberiumClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static TiberiumClass * Find(char const * pID)
    static Find(pID_0 : string) : TiberiumClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // public virtual long GetSizeMax(_ULARGE_INTEGER * pcbSize)
    GetSizeMax(pcbSize_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // TiberiumClass
    // public void RegisterForGrowth(CellStruct * cell)
    RegisterForGrowth(cell_0 : CellStruct) : void;
    // Static helpers
    // public static int FindIndex(int idxOverlayType)
    static FindIndex(idxOverlayType_0 : number) : number;
    // public static TiberiumClass * Find(int idxOverlayType)
    static Find(idxOverlayType_0 : number) : TiberiumClass;
    // public static AbstractType const AbsID = AbstractType::Tiberium
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<TiberiumClass *>, 11597032> const Array = 0xB0F4E8u
    static s_Array : DynamicVectorClass<TiberiumClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public int Spread
    m_Spread : number;
    // public double SpreadPercentage
    m_SpreadPercentage : number;
    // public int Growth
    m_Growth : number;
    // public double GrowthPercentage
    m_GrowthPercentage : number;
    // public int Value
    m_Value : number;
    // public int Power
    m_Power : number;
    // public int Color
    m_Color : number;
    // public OverlayTypeClass * Image
    m_Image : OverlayTypeClass;
    // public int NumFrames
    m_NumFrames : number;
    // public int NumImages
    m_NumImages : number;
    // public int NumSlopes
    m_NumSlopes : number;
    // public TypeList<AnimTypeClass *> Debris
    m_Debris : TypeList<AnimTypeClass>;
    // public char[28] __Debris
    m___Debris : string;
    // public TiberiumLogic SpreadLogic
    m_SpreadLogic : TiberiumLogic;
    // public char[28] __SpreadLogic
    m___SpreadLogic : string;
    // public TiberiumLogic GrowthLogic
    m_GrowthLogic : TiberiumLogic;
    // public char[28] __GrowthLogic
    m___GrowthLogic : string;
}
// TiberiumLogic
class TiberiumLogic
{
    // public void Construct(int nCount = PriorityQueueClassNode::SurfaceDataCount())
    Construct(nCount_0 : number) : void;
    // public void Destruct()
    Destruct() : void;
    // public int Count
    m_Count : number;
    // public PriorityQueueClass<PriorityQueueClassNode, std::less<PriorityQueueClassNode>> * Queue
    m_Queue : any;
    // public bool * CellIndexesWithTiberium
    m_CellIndexesWithTiberium : boolean;
    // public PriorityQueueClassNode * Nodes
    m_Nodes : any;
    // public CDTimerClass Timer
    m_Timer : CDTimerClass;
}
// The AbstractClass is the base class of all game objects.
// RadSiteClass
class RadSiteClass
    extends AbstractClass
{
    // Constructor
    // public RadSiteClass()
    constructor();
    // public RadSiteClass(CellStruct nBaseCoords, int nSpread, int nRadLevel)
    constructor(nBaseCoords_0 : CellStruct, nSpread_1 : number, nRadLevel_2 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // Start irradiating an area. Be sure to set the BaseCell, Spread and RadLevel first!
    // public void Activate()
    Activate() : void;
    // Remove the radiation effect of this site completely
    // public void Deactivate()
    Deactivate() : void;
    // Add the radiation of this RadSite to the cells.
    // public void Radiate()
    Radiate() : void;
    // Decrease the radiation of this RadSite by one step.
    // public void DecreaseRadiation()
    DecreaseRadiation() : void;
    // Decrease the cell tint and intensity of this RadSite.
    // public void DecreaseLight()
    DecreaseLight() : void;
    // Add this RadLevel to the current radiation.
    // public void Add(int nRadLevel)
    Add(nRadLevel_0 : number) : void;
    // Gets the current rad level (corresponds to the RadLevel at BaseCell).
    // public int GetRadLevel()
    GetRadLevel() : number;
    // Gets the rad level applied by this RadSite to a certain cell.
    // public int GetRadLevelAt(CellStruct * pCell)
    GetRadLevelAt(pCell_0 : CellStruct) : number;
    // Sets the rad level and the appropriate duration values.
    // public void SetRadLevel(int nRadLevel)
    SetRadLevel(nRadLevel_0 : number) : void;
    // Sets the center cell. Do not change when RadSite is activated.
    // public void SetBaseCell(CellStruct * pCell)
    SetBaseCell(pCell_0 : CellStruct) : void;
    // Gets the spread in cells.
    // public void GetSpread()
    GetSpread() : void;
    // Sets the spread in cells. Also updates the SpreadInLeptons.
    // public void SetSpread(int nCells)
    SetSpread(nCells_0 : number) : void;
    // Gets the current strenght of the effect, the ratio between time left and initial duration.
    // public double GetEffectPercentage()
    GetEffectPercentage() : number;
    // public static AbstractType const AbsID = AbstractType::RadSite
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<RadSiteClass *>, 11553744> const Array = 0xB04BD0u
    static s_Array : DynamicVectorClass<RadSiteClass>;
    // the light source attached to this instance
    // public LightSourceClass * LightSource
    m_LightSource : LightSourceClass;
    // center cell
    // public CellStruct BaseCell
    m_BaseCell : CellStruct;
    // range in cells
    // public int Spread
    m_Spread : number;
    // range in leptons
    // public int SpreadInLeptons
    m_SpreadInLeptons : number;
    // the radiation level,
    // public int RadLevel
    m_RadLevel : number;
    // cell's rad level reduced by (RadLevel/LevelSteps) every time RadLevelTimer elapses
    // public int LevelSteps
    m_LevelSteps : number;
    // the intensity at the beginning
    // public int Intensity
    m_Intensity : number;
    // RadColor at the current level
    // public TintStruct Tint
    m_Tint : TintStruct;
    // the number of intensity decreases during the duration
    // public int IntensitySteps
    m_IntensitySteps : number;
    // Intensity decremented by this every time RadLightDelay elapses
    // public int IntensityDecrement
    m_IntensityDecrement : number;
    // as currently set up, the rad site will stay for so many frames
    // public int RadDuration
    m_RadDuration : number;
    // the remaining frames. divided by RadDuration gives the factor
    // public int RadTimeLeft
    m_RadTimeLeft : number;
    // used to count down RadLevelDelay
    // public CDTimerClass RadLevelTimer
    m_RadLevelTimer : CDTimerClass;
    // public char[12] __RadLevelTimer
    m___RadLevelTimer : string;
    // used to count down RadLightDelay
    // public CDTimerClass RadLightTimer
    m_RadLightTimer : CDTimerClass;
    // public char[12] __RadLightTimer
    m___RadLightTimer : string;
}
// struct Blitter;
// LightConvertClass
class LightConvertClass
    extends ConvertClass
{
    // Constructor
    // public LightConvertClass(BytePalette * palette1, BytePalette * palette2, Surface * pSurface, int color_R, int color_G, int color_B, bool skipBlitters, unsigned char * pBuffer, size_t shadeCount)
    constructor(palette1_0 : BytePalette, palette2_1 : BytePalette, pSurface_2 : Surface, color_R_3 : number, color_G_4 : number, color_B_5 : number, skipBlitters_6 : boolean, pBuffer_7 : number, shadeCount_8 : any);
    // public virtual void UpdateColors(int red, int green, int blue, bool tinted)
    UpdateColors(red_0 : number, green_1 : number, blue_2 : number, tinted_3 : boolean) : void;
    // public static LightConvertClass * InitLightConvert(int red, int green, int blue)
    static InitLightConvert(red_0 : number, green_1 : number, blue_2 : number) : LightConvertClass;
    // global array
    // public static constant_ptr<DynamicVectorClass<LightConvertClass *>, 8910488> const Array = 0x87F698u
    static s_Array : DynamicVectorClass<LightConvertClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public RGBClass * UsedPalette1
    m_UsedPalette1 : RGBClass;
    // public RGBClass * UsedPalette2
    m_UsedPalette2 : RGBClass;
    // public unsigned char * IndexesToIgnore
    m_IndexesToIgnore : number;
    // public int RefCount
    m_RefCount : number;
    // public TintStruct Color1
    m_Color1 : TintStruct;
    // public TintStruct Color2
    m_Color2 : TintStruct;
    // public bool Tinted
    m_Tinted : boolean;
}
// struct Blitter;
// ConvertClass
class ConvertClass
{
    // public ConvertClass(BytePalette const& palette, BytePalette const& eightbitpalette, DSurface * pSurface, size_t shadeCount, bool skipBlitters)
    constructor(palette_0 : BytePalette, eightbitpalette_1 : BytePalette, pSurface_2 : DSurface, shadeCount_3 : any, skipBlitters_4 : boolean);
    // static ConvertClass* FindOrAllocate(const char* pFilename);
    // public static void CreateFromFile(char const * pFilename, BytePalette *& pPalette, ConvertClass *& pDestination)
    static CreateFromFile(pFilename_0 : string, pPalette_1 : BytePalette, pDestination_2 : ConvertClass) : void;
    // if you're drawing a SHP, call SHPStruct::HasCompression and choose one of these two based on that
    // public Blitter * SelectPlainBlitter(BlitterFlags flags) const
    SelectPlainBlitter(flags_0 : BlitterFlags) : any;
    // public RLEBlitter * SelectRLEBlitter(BlitterFlags flags) const
    SelectRLEBlitter(flags_0 : BlitterFlags) : any;
    // global array
    // public static constant_ptr<DynamicVectorClass<ConvertClass *>, 9039096> const Array = 0x89ECF8u
    static s_Array : DynamicVectorClass<ConvertClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int BytesPerPixel
    m_BytesPerPixel : number;
    // public Blitter *[50] Blitters
    m_Blitters : any;
    // public RLEBlitter *[39] RLEBlitters
    m_RLEBlitters : any;
    // public int ShadeCount
    m_ShadeCount : number;
    // new(ShadeCount* 8* BytesPerPixel) - gets filled with palette values on CTOR
    // public void * FullColorData
    m_FullColorData : void;
    // points to the middle of FullColorData above
    // public void * PaletteData
    m_PaletteData : void;
    // if(BytesPerPixel == 1) { ByteColorData = new byte[0x100]; }
    // public void * ByteColorData
    m_ByteColorData : void;
    // set right before drawing
    // public unsigned long CurrentZRemap
    m_CurrentZRemap : number;
    // Used by 50 alpha blending
    // public unsigned long HalfTranslucencyMask
    m_HalfTranslucencyMask : number;
    // Used by 25 and 75 alpha blending
    // public unsigned long QuatTranslucencyMask
    m_QuatTranslucencyMask : number;
}
// static Point2D* __fastcall Simple_Text_Print_Wide(Point2D* RetVal, const wchar_t* Text, Surface* Surface, RectangleStruct* Bounds,
// Point2D* Location, COLORREF ForeColor, COLORREF BackColor, TextPrintType Flag, bool bUkn)
// {
// JMP_STD(0x4A5EB0);
// }
// DSurface
class DSurface
    extends XSurface
{
    // public virtual bool DrawGradientLine(RectangleStruct * pRect, Point2D * pStart, Point2D * pEnd, ColorStruct * pStartColor, ColorStruct * pEndColor, float fStep, int nColor)
    DrawGradientLine(pRect_0 : RectangleStruct, pStart_1 : Point2D, pEnd_2 : Point2D, pStartColor_3 : ColorStruct, pEndColor_4 : ColorStruct, fStep_5 : number, nColor_6 : number) : boolean;
    // public virtual bool CanBlit()
    CanBlit() : boolean;
    // Comments from thomassneddon
    // public void DrawSHP(ConvertClass * Palette, SHPStruct * SHP, int FrameIndex, Point2D const * const Position, RectangleStruct const * const Bounds, BlitterFlags Flags, int Remap, int ZAdjust, ZGradient ZGradientDescIndex, int Brightness, int TintColor, SHPStruct * ZShape, int ZShapeFrame, int XOffset, int YOffset)
    DrawSHP(Palette_0 : ConvertClass, SHP_1 : any, FrameIndex_2 : number, Position_3 : Point2D, Bounds_4 : RectangleStruct, Flags_5 : BlitterFlags, Remap_6 : number, ZAdjust_7 : number, ZGradientDescIndex_8 : ZGradient, Brightness_9 : number, TintColor_10 : number, ZShape_11 : any, ZShapeFrame_12 : number, XOffset_13 : number, YOffset_14 : number) : void;
    // public void DrawTextA(wchar_t const * pText, RectangleStruct * pBounds, Point2D * pLocation, unsigned long ForeColor, unsigned long BackColor, TextPrintType Flag)
    DrawTextA(pText_0 : number, pBounds_1 : RectangleStruct, pLocation_2 : Point2D, ForeColor_3 : number, BackColor_4 : number, Flag_5 : TextPrintType) : void;
    // public void DrawTextA(wchar_t const * pText, Point2D * pLoction, unsigned long Color)
    DrawTextA(pText_0 : number, pLoction_1 : Point2D, Color_2 : number) : void;
    // public void DrawTextA(wchar_t const * pText, int X, int Y, unsigned long Color)
    DrawTextA(pText_0 : number, X_1 : number, Y_2 : number, Color_3 : number) : void;
    // public static reference<DSurface *, 8942332, 0> const Tile = 0x8872FCu
    static s_Tile : DSurface;
    // public static reference<DSurface *, 8942336, 0> const Sidebar = 0x887300u
    static s_Sidebar : DSurface;
    // public static reference<DSurface *, 8942344, 0> const Primary = 0x887308u
    static s_Primary : DSurface;
    // public static reference<DSurface *, 8942348, 0> const Hidden = 0x88730Cu
    static s_Hidden : DSurface;
    // public static reference<DSurface *, 8942352, 0> const Alternate = 0x887310u
    static s_Alternate : DSurface;
    // public static reference<DSurface *, 8942356, 0> const Temp = 0x887314u
    static s_Temp : DSurface;
    // public static reference<DSurface *, 8942364, 0> const Composite = 0x88731Cu
    static s_Composite : DSurface;
    // public static reference<RectangleStruct, 8941456, 0> const SidebarBounds = 0x886F90u
    static s_SidebarBounds : RectangleStruct;
    // public static reference<RectangleStruct, 8941472, 0> const ViewBounds = 0x886FA0u
    static s_ViewBounds : RectangleStruct;
    // public static reference<RectangleStruct, 8941488, 0> const WindowBounds = 0x886FB0u
    static s_WindowBounds : RectangleStruct;
    // public void * Buffer
    m_Buffer : void;
    // public bool IsAllocated
    m_IsAllocated : boolean;
    // public bool IsInVideoRam
    m_IsInVideoRam : boolean;
    // public IDirectDrawSurface * VideoSurfacePtr
    m_VideoSurfacePtr : any;
    // public _DDSURFACEDESC2 * VideoSurfaceDescription
    m_VideoSurfaceDescription : any;
}
// XSurface
class XSurface
    extends Surface
{
    // public XSurface(int nWidth = 640, int nHeight = 400)
    constructor(nWidth_0 : number, nHeight_1 : number);
    // public virtual bool PutPixelClip(Point2D * pPoint, short nUkn, RectangleStruct * pRect)
    PutPixelClip(pPoint_0 : Point2D, nUkn_1 : number, pRect_2 : RectangleStruct) : boolean;
    // public virtual short GetPixelClip(Point2D * pPoint, RectangleStruct * pRect)
    GetPixelClip(pPoint_0 : Point2D, pRect_1 : RectangleStruct) : number;
    // public int LockLevel
    m_LockLevel : number;
    // public int BytesPerPixel
    m_BytesPerPixel : number;
}
// RGBClass
class RGBClass
{
    // public RGBClass()
    constructor();
    // public RGBClass(int r, int g, int b)
    constructor(r_0 : number, g_1 : number, b_2 : number);
    // public RGBClass(int rgb, bool wordcolor = false)
    constructor(rgb_0 : number, wordcolor_1 : boolean);
    // public void Adjust(int ratio, RGBClass const& rgb)
    Adjust(ratio_0 : number, rgb_1 : RGBClass) : void;
    // public int Difference(RGBClass const& rgb) const
    Difference(rgb_0 : RGBClass) : number;
    // public int ToInt()
    ToInt() : number;
    // public static reference<RGBClass, 11010592, 0> const White = 0xA80220
    static s_White : RGBClass;
    // public static reference<int, 9047504, 0> const RedShiftLeft = 0x8A0DD0
    static s_RedShiftLeft : number;
    // public static reference<int, 9047508, 0> const RedShiftRight = 0x8A0DD4
    static s_RedShiftRight : number;
    // public static reference<int, 9047520, 0> const GreenShiftLeft = 0x8A0DE0
    static s_GreenShiftLeft : number;
    // public static reference<int, 9047524, 0> const GreenShiftRight = 0x8A0DE4
    static s_GreenShiftRight : number;
    // public static reference<int, 9047512, 0> const BlueShiftLeft = 0x8A0DD8
    static s_BlueShiftLeft : number;
    // public static reference<int, 9047516, 0> const BlueShiftRight = 0x8A0DDC
    static s_BlueShiftRight : number;
    // public unsigned char Red
    m_Red : number;
    // public unsigned char Green
    m_Green : number;
    // public unsigned char Blue
    m_Blue : number;
}
// EventClass
class EventClass
{
}
// LaserDrawClass
class LaserDrawClass
{
    // Constructor, Destructor
    // public LaserDrawClass(CoordStruct const& source, CoordStruct const& target, ColorStruct const& innerColor, ColorStruct const& outerColor, ColorStruct const& outerSpread, int duration)
    constructor(source_0 : CoordStruct, target_1 : CoordStruct, innerColor_2 : ColorStruct, outerColor_3 : ColorStruct, outerSpread_4 : ColorStruct, duration_5 : number);
    // public LaserDrawClass(CoordStruct source, CoordStruct target, int zAdjust, unsigned char unknown, ColorStruct innerColor, ColorStruct outerColor, ColorStruct outerSpread, int duration, bool blinks = false, bool fades = true, float startIntensity = 1.0f, float endIntensity = 0.0f)
    constructor(source_0 : CoordStruct, target_1 : CoordStruct, zAdjust_2 : number, unknown_3 : number, innerColor_4 : ColorStruct, outerColor_5 : ColorStruct, outerSpread_6 : ColorStruct, duration_7 : number, blinks_8 : boolean, fades_9 : boolean, startIntensity_10 : number, endIntensity_11 : number);
    // skip operator new
    // skip operator delete
    // only respected if IsHouseColor
    // public int Thickness
    m_Thickness : number;
    // public bool IsHouseColor
    m_IsHouseColor : boolean;
    // this changes the values for InnerColor (false: halve, true: double), HouseColor only
    // public bool IsSupported
    m_IsSupported : boolean;
    // public CoordStruct Source
    m_Source : CoordStruct;
    // public CoordStruct Target
    m_Target : CoordStruct;
    // public int ZAdjust
    m_ZAdjust : number;
    // public char field_40
    m_field_40 : number;
    // public ColorStruct InnerColor
    m_InnerColor : ColorStruct;
    // public ColorStruct OuterColor
    m_OuterColor : ColorStruct;
    // public ColorStruct OuterSpread
    m_OuterSpread : ColorStruct;
    // public int Duration
    m_Duration : number;
    // public bool Blinks
    m_Blinks : boolean;
    // public bool BlinkState
    m_BlinkState : boolean;
    // public bool Fades
    m_Fades : boolean;
    // public float StartIntensity
    m_StartIntensity : number;
    // public float EndIntensity
    m_EndIntensity : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public StageClass Progress
    m_Progress : StageClass;
    // public char[28] __Progress
    m___Progress : string;
}
// FlashData
class FlashData
{
    // public bool Update()
    Update() : boolean;
    // public int DurationRemaining
    m_DurationRemaining : number;
    // public bool FlashingNow
    m_FlashingNow : boolean;
}
// PassengersClass
class PassengersClass
{
    // public PassengersClass()
    constructor();
    // public void AddPassenger(FootClass * pPassenger)
    AddPassenger(pPassenger_0 : FootClass) : void;
    // public FootClass * GetFirstPassenger() const
    GetFirstPassenger() : FootClass;
    // public FootClass * RemoveFirstPassenger()
    RemoveFirstPassenger() : FootClass;
    // public int GetTotalSize() const
    GetTotalSize() : number;
    // public int IndexOf(FootClass * candidate) const
    IndexOf(candidate_0 : FootClass) : number;
    // public int NumPassengers
    m_NumPassengers : number;
    // public FootClass * FirstPassenger
    m_FirstPassenger : FootClass;
}
// VeterancyStruct
class VeterancyStruct
{
    // public VeterancyStruct()
    constructor();
    // public VeterancyStruct(double value)
    constructor(value_0 : number);
    // public void Add(int ownerCost, int victimCost)
    Add(ownerCost_0 : number, victimCost_1 : number) : void;
    // public void Add(double value)
    Add(value_0 : number) : void;
    // public Rank GetRemainingLevel() const
    GetRemainingLevel() : Rank;
    // public bool IsNegative() const
    IsNegative() : boolean;
    // public bool IsRookie() const
    IsRookie() : boolean;
    // public bool IsVeteran() const
    IsVeteran() : boolean;
    // public bool IsElite() const
    IsElite() : boolean;
    // public void Reset()
    Reset() : void;
    // public void SetRookie(bool notReally = true)
    SetRookie(notReally_0 : boolean) : void;
    // public void SetVeteran(bool yesReally = true)
    SetVeteran(yesReally_0 : boolean) : void;
    // public void SetElite(bool yesReally = true)
    SetElite(yesReally_0 : boolean) : void;
    // public float Veterancy
    m_Veterancy : number;
}
// The AirstrikeClass handles the airstrikes Boris calls in.
// TemporalClass
class TemporalClass
    extends AbstractClass
{
    // Constructor
    // public TemporalClass(TechnoClass * pOwnerUnit)
    constructor(pOwnerUnit_0 : TechnoClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void Fire(TechnoClass * pTarget)
    Fire(pTarget_0 : TechnoClass) : void;
    // public bool CanWarpTarget(TechnoClass * pTarget) const
    CanWarpTarget(pTarget_0 : TechnoClass) : boolean;
    // hardcoded to accumulate only up to 50 helpers
    // public int GetWarpPerStep(int nHelperCount = 0) const
    GetWarpPerStep(nHelperCount_0 : number) : number;
    // public void LetGo()
    LetGo() : void;
    // public void JustLetGo()
    JustLetGo() : void;
    // public void Detach()
    Detach() : void;
    // public static AbstractType const AbsID = AbstractType::Temporal
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7F5180
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<TemporalClass *>, 11594848> const Array = 0xB0EC60u
    static s_Array : DynamicVectorClass<TemporalClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public TechnoClass * Target
    m_Target : TechnoClass;
    // public CDTimerClass LifeTimer
    m_LifeTimer : CDTimerClass;
    // public void * unknown_pointer_38
    m_unknown_pointer_38 : void;
    // public SuperClass * SourceSW
    m_SourceSW : SuperClass;
    // public TemporalClass * NextTemporal
    m_NextTemporal : TemporalClass;
    // public TemporalClass * PrevTemporal
    m_PrevTemporal : TemporalClass;
    // public int WarpRemaining
    m_WarpRemaining : number;
    // public int WarpPerStep
    m_WarpPerStep : number;
}
// forward declarations
// SuperClass
class SuperClass
    extends AbstractClass
{
    // Constructor
    // public SuperClass(SuperWeaponTypeClass * pSWType, HouseClass * pOwner)
    constructor(pSWType_0 : SuperWeaponTypeClass, pOwner_1 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non virtual
    // public void CreateChronoAnim(CoordStruct coords)
    CreateChronoAnim(coords_0 : CoordStruct) : void;
    // public void Reset()
    Reset() : void;
    // was the setting successful? (did we have to change the state (true) or was it already in the same hold state(false))
    // public bool SetOnHold(bool onHold)
    SetOnHold(onHold_0 : boolean) : boolean;
    // public bool Grant(bool oneTime, bool announce, bool onHold)
    Grant(oneTime_0 : boolean, announce_1 : boolean, onHold_2 : boolean) : boolean;
    // true if this was ->Granted
    // public bool Lose()
    Lose() : boolean;
    // public bool IsPowered() const
    IsPowered() : boolean;
    // public void Launch(CellStruct const& cell, bool isPlayer)
    Launch(cell_0 : CellStruct, isPlayer_1 : boolean) : void;
    // public char CanFire() const
    CanFire() : number;
    // public void SetReadiness(bool ready)
    SetReadiness(ready_0 : boolean) : void;
    // public char StopPreclickAnim(bool isPlayer)
    StopPreclickAnim(isPlayer_0 : boolean) : number;
    // public char ClickFire(bool isPlayer, CellStruct const& cell)
    ClickFire(isPlayer_0 : boolean, cell_1 : CellStruct) : number;
    // public bool HasChargeProgressed(bool isPlayer)
    HasChargeProgressed(isPlayer_0 : boolean) : boolean;
    // public int AnimStage() const
    AnimStage() : number;
    // public void SetCharge(int percentage)
    SetCharge(percentage_0 : number) : void;
    // public int GetRechargeTime() const
    GetRechargeTime() : number;
    // public void SetRechargeTime(int time)
    SetRechargeTime(time_0 : number) : void;
    // public void ResetRechargeTime()
    ResetRechargeTime() : void;
    // public wchar_t const * NameReadiness() const
    NameReadiness() : number;
    // public bool ShouldDrawProgress() const
    ShouldDrawProgress() : boolean;
    // public bool ShouldFlashTab() const
    ShouldFlashTab() : boolean;
    // public static AbstractType const AbsID = AbstractType::Super
    static s_AbsID : AbstractType;
    // public static unsigned int const AbsVTable = 0x7F3FE8
    static s_AbsVTable : number;
    // Static
    // public static constant_ptr<DynamicVectorClass<SuperClass *>, 11025592> const Array = 0xA83CB8u
    static s_Array : DynamicVectorClass<SuperClass>;
    // public static reference<DynamicVectorClass<SuperClass *>, 11025744, 0> const ShowTimers = 0xA83D50u
    static s_ShowTimers : DynamicVectorClass<SuperClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int CustomChargeTime
    m_CustomChargeTime : number;
    // public SuperWeaponTypeClass * Type
    m_Type : SuperWeaponTypeClass;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // public CDTimerClass RechargeTimer
    m_RechargeTimer : CDTimerClass;
    // public bool BlinkState
    m_BlinkState : boolean;
    // public _LARGE_INTEGER BlinkTimer
    m_BlinkTimer : any;
    // see 0x6CD14F
    // public int SpecialSoundDuration
    m_SpecialSoundDuration : number;
    // public CoordStruct SpecialSoundLocation
    m_SpecialSoundLocation : CoordStruct;
    // 0x60
    // public bool CanHold
    m_CanHold : boolean;
    // 0x62
    // public CellStruct ChronoMapCoords
    m_ChronoMapCoords : CellStruct;
    // 0x68
    // public AnimClass * Animation
    m_Animation : AnimClass;
    // public bool AnimationGotInvalid
    m_AnimationGotInvalid : boolean;
    // public bool IsPresent
    m_IsPresent : boolean;
    // remove this SW when it has been fired once
    // public bool IsOneTime
    m_IsOneTime : boolean;
    // public bool IsReady
    m_IsReady : boolean;
    // public bool IsSuspended
    m_IsSuspended : boolean;
    // when did it become ready?
    // public int ReadyFrame
    m_ReadyFrame : number;
    // public int CameoChargeState
    m_CameoChargeState : number;
    // public ChargeDrainState ChargeDrainState
    m_ChargeDrainState : ChargeDrainState;
}
// ---
// SuperWeaponTypeClass
class SuperWeaponTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public SuperWeaponTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static SuperWeaponTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : SuperWeaponTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // SuperWeaponTypeClass
    // public virtual Action MouseOverObject(CellStruct const& cell, ObjectClass * pObjBelowMouse) const
    MouseOverObject(cell_0 : CellStruct, pObjBelowMouse_1 : ObjectClass) : Action;
    // non-virtual
    // public static SuperWeaponTypeClass * FindFirstOfAction(Action Action)
    static FindFirstOfAction(Action_0 : Action) : SuperWeaponTypeClass;
    // public static AbstractType const AbsID = AbstractType::SuperWeaponType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<SuperWeaponTypeClass *>, 11068208> const Array = 0xA8E330u
    static s_Array : DynamicVectorClass<SuperWeaponTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public WeaponTypeClass * WeaponType
    m_WeaponType : WeaponTypeClass;
    // not read, unused
    // public int RechargeVoice
    m_RechargeVoice : number;
    // not read, unused
    // public int ChargingVoice
    m_ChargingVoice : number;
    // not read, unused
    // public int ImpatientVoice
    m_ImpatientVoice : number;
    // not read, unused
    // public int SuspendVoice
    m_SuspendVoice : number;
    // in frames
    // public int RechargeTime
    m_RechargeTime : number;
    // public SuperWeaponType Type
    m_Type : SuperWeaponType;
    // public SHPStruct * SidebarImage
    m_SidebarImage : any;
    // public Action Action
    m_Action : Action;
    // public int SpecialSound
    m_SpecialSound : number;
    // public int StartSound
    m_StartSound : number;
    // public BuildingTypeClass * AuxBuilding
    m_AuxBuilding : BuildingTypeClass;
    // public char[24] SidebarImageFile
    m_SidebarImageFile : string;
    // public bool UseChargeDrain
    m_UseChargeDrain : boolean;
    // public bool IsPowered
    m_IsPowered : boolean;
    // public bool DisableableFromShell
    m_DisableableFromShell : boolean;
    // public int FlashSidebarTabFrames
    m_FlashSidebarTabFrames : number;
    // public bool AIDefendAgainst
    m_AIDefendAgainst : boolean;
    // public bool PreClick
    m_PreClick : boolean;
    // public bool PostClick
    m_PostClick : boolean;
    // public int PreDependent
    m_PreDependent : number;
    // public bool ShowTimer
    m_ShowTimer : boolean;
    // public bool ManualControl
    m_ManualControl : boolean;
    // public float Range
    m_Range : number;
    // public int LineMultiplier
    m_LineMultiplier : number;
}
// forward declarations
// AirstrikeClass
class AirstrikeClass
    extends AbstractClass
{
    // Constructor
    // public AirstrikeClass(TechnoClass * pOwner)
    constructor(pOwner_0 : TechnoClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void StartMission(ObjectClass * pTarget)
    StartMission(pTarget_0 : ObjectClass) : void;
    // public static AbstractType const AbsID = AbstractType::Airstrike
    static s_AbsID : AbstractType;
    // As in the INI files.
    // public int AirstrikeTeam
    m_AirstrikeTeam : number;
    // As in the INI files.
    // public int EliteAirstrikeTeam
    m_EliteAirstrikeTeam : number;
    // As in the INI files.
    // public int AirstrikeTeamTypeIndex
    m_AirstrikeTeamTypeIndex : number;
    // As in the INI files.
    // public int EliteAirstrikeTeamTypeIndex
    m_EliteAirstrikeTeamTypeIndex : number;
    // public unsigned long unknown_34
    m_unknown_34 : number;
    // unused?
    // public unsigned long unknown_38
    m_unknown_38 : number;
    // Is the Aircraft on its way?
    // public bool IsOnMission
    m_IsOnMission : boolean;
    // public bool unknown_bool_3D
    m_unknown_bool_3D : boolean;
    // when was the last time this team was invoked and subsequently dissolved
    // public unsigned long TeamDissolveFrame
    m_TeamDissolveFrame : number;
    // As in the INI files.
    // public int AirstrikeRechargeTime
    m_AirstrikeRechargeTime : number;
    // As in the INI files.
    // public int EliteAirstrikeRechargeTime
    m_EliteAirstrikeRechargeTime : number;
    // The unit that called the Airstrike (usually Boris).
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // The Airstrike's target.
    // public ObjectClass * Target
    m_Target : ObjectClass;
    // As in the INI files.
    // public AircraftTypeClass * AirstrikeTeamType
    m_AirstrikeTeamType : AircraftTypeClass;
    // As in the INI files.
    // public AircraftTypeClass * EliteAirstrikeTeamType
    m_EliteAirstrikeTeamType : AircraftTypeClass;
    // public FootClass * FirstObject
    m_FirstObject : FootClass;
}
// The AbstractClass is the base class of all game objects.
// CaptureManagerClass
class CaptureManagerClass
    extends AbstractClass
{
    // Constructor
    // public CaptureManagerClass(TechnoClass * pOwner, int nMaxControlNodes, bool bInfiniteControl)
    constructor(pOwner_0 : TechnoClass, nMaxControlNodes_1 : number, bInfiniteControl_2 : boolean);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public bool CaptureUnit(TechnoClass * pUnit)
    CaptureUnit(pUnit_0 : TechnoClass) : boolean;
    // public bool FreeUnit(TechnoClass * pUnit)
    FreeUnit(pUnit_0 : TechnoClass) : boolean;
    // public void FreeAll()
    FreeAll() : void;
    // public int NumControlNodes() const
    NumControlNodes() : number;
    // public bool CanCapture(TechnoClass * Target) const
    CanCapture(Target_0 : TechnoClass) : boolean;
    // public bool CannotControlAnyMore() const
    CannotControlAnyMore() : boolean;
    // public bool IsControllingSomething() const
    IsControllingSomething() : boolean;
    // public bool IsOverloading(bool * wasDamageApplied) const
    IsOverloading(wasDamageApplied_0 : boolean) : boolean;
    // public void HandleOverload()
    HandleOverload() : void;
    // public bool NeedsToDrawLinks() const
    NeedsToDrawLinks() : boolean;
    // public bool DrawLinks()
    DrawLinks() : boolean;
    // public void DecideUnitFate(TechnoClass * Unit)
    DecideUnitFate(Unit_0 : TechnoClass) : void;
    // public HouseClass * GetOriginalOwner(TechnoClass * Unit) const
    GetOriginalOwner(Unit_0 : TechnoClass) : HouseClass;
    // public static AbstractType const AbsID = AbstractType::CaptureManager
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<CaptureManagerClass *>, 9036016> const Array = 0x89E0F0u
    static s_Array : DynamicVectorClass<CaptureManagerClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public DynamicVectorClass<ControlNode *> ControlNodes
    m_ControlNodes : DynamicVectorClass<ControlNode>;
    // public int MaxControlNodes
    m_MaxControlNodes : number;
    // public bool InfiniteMindControl
    m_InfiniteMindControl : boolean;
    // Has the mind control death sound played already?
    // public bool OverloadDeathSoundPlayed
    m_OverloadDeathSoundPlayed : boolean;
    // Used to create the red overloading pip by returning true in IsOverloading's wasDamageApplied for 10 frames.
    // public int OverloadPipState
    m_OverloadPipState : number;
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // Decremented every frame. If it reaches zero, OverloadDamage is applied.
    // public int OverloadDamageDelay
    m_OverloadDamageDelay : number;
}
// ControlNode
class ControlNode
{
    // public ControlNode()
    constructor();
    // public TechnoClass * Unit
    m_Unit : TechnoClass;
    // public HouseClass * OriginalOwner
    m_OriginalOwner : HouseClass;
    // public CDTimerClass LinkDrawTimer
    m_LinkDrawTimer : CDTimerClass;
    // public char[12] __LinkDrawTimer
    m___LinkDrawTimer : string;
}
// The AbstractClass is the base class of all game objects.
// SpawnManagerClass
class SpawnManagerClass
    extends AbstractClass
{
    // Constructor
    // public SpawnManagerClass(TechnoClass * pOwner, AircraftTypeClass * pSpawnType, int nMaxNodes, int RegenRate, int ReloadRate)
    constructor(pOwner_0 : TechnoClass, pSpawnType_1 : AircraftTypeClass, nMaxNodes_2 : number, RegenRate_3 : number, ReloadRate_4 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void KillNodes()
    KillNodes() : void;
    // public void SetTarget(AbstractClass * pTarget)
    SetTarget(pTarget_0 : AbstractClass) : void;
    // public bool UpdateTarget()
    UpdateTarget() : boolean;
    // public void ResetTarget()
    ResetTarget() : void;
    // public int CountAliveSpawns() const
    CountAliveSpawns() : number;
    // public int CountDockedSpawns() const
    CountDockedSpawns() : number;
    // public int CountLaunchingSpawns() const
    CountLaunchingSpawns() : number;
    // public void UnlinkPointer()
    UnlinkPointer() : void;
    // public static AbstractType const AbsID = AbstractType::SpawnManager
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<SpawnManagerClass *>, 11581568> const Array = 0xB0B880u
    static s_Array : DynamicVectorClass<SpawnManagerClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public AircraftTypeClass * SpawnType
    m_SpawnType : AircraftTypeClass;
    // public int SpawnCount
    m_SpawnCount : number;
    // public int RegenRate
    m_RegenRate : number;
    // public int ReloadRate
    m_ReloadRate : number;
    // public DynamicVectorClass<SpawnControl *> SpawnedNodes
    m_SpawnedNodes : DynamicVectorClass<SpawnControl>;
    // public CDTimerClass UpdateTimer
    m_UpdateTimer : CDTimerClass;
    // public CDTimerClass SpawnTimer
    m_SpawnTimer : CDTimerClass;
    // public AbstractClass * Target
    m_Target : AbstractClass;
    // public AbstractClass * NewTarget
    m_NewTarget : AbstractClass;
    // public SpawnManagerStatus Status
    m_Status : SpawnManagerStatus;
}
// SpawnControl
class SpawnControl
{
    // public AircraftClass * Unit
    m_Unit : AircraftClass;
    // public SpawnNodeStatus Status
    m_Status : SpawnNodeStatus;
    // public CDTimerClass SpawnTimer
    m_SpawnTimer : CDTimerClass;
    // public int IsSpawnMissile
    m_IsSpawnMissile : number;
}
// The AbstractClass is the base class of all game objects.
// SlaveManagerClass
class SlaveManagerClass
    extends AbstractClass
{
    // Constructor
    // public SlaveManagerClass(TechnoClass * pOwner, InfantryTypeClass * pSlave, int num, int RegenRate, int ReloadRate)
    constructor(pOwner_0 : TechnoClass, pSlave_1 : InfantryTypeClass, num_2 : number, RegenRate_3 : number, ReloadRate_4 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // non-virtual
    // public void SetOwner(TechnoClass * NewOwner)
    SetOwner(NewOwner_0 : TechnoClass) : void;
    // public void CreateSlave(SlaveManagerClass::SlaveControl * Node)
    CreateSlave(Node_0 : SlaveManagerClass__SlaveControl) : void;
    // public void LostSlave(InfantryClass * Slave)
    LostSlave(Slave_0 : InfantryClass) : void;
    // public void Deploy2()
    Deploy2() : void;
    // switches the slaves to the killer house with cheers and hoorahs
    // note that this->Owner will be NULL once this function is done
    // public void Killed(TechnoClass * Killer, HouseClass * ForcedOwnerHouse = nullptr)
    Killed(Killer_0 : TechnoClass, ForcedOwnerHouse_1 : HouseClass) : void;
    // public bool ShouldWakeUpNow()
    ShouldWakeUpNow() : boolean;
    // the slaves will become free citizens without any announcements or cheers, if you don't call Killed() beforehand
    // public void ZeroOutSlaves()
    ZeroOutSlaves() : void;
    // stops scanning, spawning slaves and driving around.
    // public void SuspendWork()
    SuspendWork() : void;
    // resumes to harvest automatically.
    // public void ResumeWork()
    ResumeWork() : void;
    // public static AbstractType const AbsID = AbstractType::SlaveManager
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<SlaveManagerClass *>, 11580912> const Array = 0xB0B5F0u
    static s_Array : DynamicVectorClass<SlaveManagerClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public InfantryTypeClass * SlaveType
    m_SlaveType : InfantryTypeClass;
    // public int SlaveCount
    m_SlaveCount : number;
    // public int RegenRate
    m_RegenRate : number;
    // public int ReloadRate
    m_ReloadRate : number;
    // public DynamicVectorClass<SlaveManagerClass::SlaveControl *> SlaveNodes
    m_SlaveNodes : DynamicVectorClass<SlaveManagerClass__SlaveControl>;
    // public CDTimerClass RespawnTimer
    m_RespawnTimer : CDTimerClass;
    // public SlaveManagerStatus State
    m_State : SlaveManagerStatus;
    // public int LastScanFrame
    m_LastScanFrame : number;
}
// forward declarations
// ParticleSystemClass
class ParticleSystemClass
    extends ObjectClass
{
    // Constructor
    // public ParticleSystemClass(ParticleSystemTypeClass * pParticleSystemType, CoordStruct const& coords, AbstractClass * pTarget, ObjectClass * pOwner, CoordStruct const& targetCoords, HouseClass * pOwnerHouse)
    constructor(pParticleSystemType_0 : ParticleSystemTypeClass, coords_1 : CoordStruct, pTarget_2 : AbstractClass, pOwner_3 : ObjectClass, targetCoords_4 : CoordStruct, pOwnerHouse_5 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::ParticleSystem
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<ParticleSystemClass *>, 11010568> const Array = 0xA80208u
    static s_Array : DynamicVectorClass<ParticleSystemClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public ParticleSystemTypeClass * Type
    m_Type : ParticleSystemTypeClass;
    // public CoordStruct SpawnDistanceToOwner
    m_SpawnDistanceToOwner : CoordStruct;
    // public CoordStruct TargetCoords
    m_TargetCoords : CoordStruct;
    // public ObjectClass * Owner
    m_Owner : ObjectClass;
    // CellClass or TechnoClass
    // public AbstractClass * Target
    m_Target : AbstractClass;
    // from ParSysTypeClass
    // public int SpawnFrames
    m_SpawnFrames : number;
    // from ParSysTypeClass
    // public int Lifetime
    m_Lifetime : number;
    // from ParSysTypeClass
    // public int SparkSpawnFrames
    m_SparkSpawnFrames : number;
    // defaults to 29
    // public int SpotlightRadius
    m_SpotlightRadius : number;
    // public bool TimeToDie
    m_TimeToDie : boolean;
    // public bool unknown_bool_F9
    m_unknown_bool_F9 : boolean;
    // public HouseClass * OwnerHouse
    m_OwnerHouse : HouseClass;
    // public DynamicVectorClass<ParticleClass *> Particles
    m_Particles : DynamicVectorClass<ParticleClass>;
    // public char[24] __Particles
    m___Particles : string;
}
// forward declarations
// ParticleSystemTypeClass
class ParticleSystemTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public ParticleSystemTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static ParticleSystemTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : ParticleSystemTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static ParticleSystemTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : ParticleSystemTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * mcoords, HouseClass * owner)
    SpawnAtMapCoords(mcoords_0 : CellStruct | any, owner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::ParticleSystemType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<ParticleSystemTypeClass *>, 11025768> const Array = 0xA83D68u
    static s_Array : DynamicVectorClass<ParticleSystemTypeClass>;
    // ParticleType Array index
    // public int HoldsWhat
    m_HoldsWhat : number;
    // public bool Spawns
    m_Spawns : boolean;
    // public int SpawnFrames
    m_SpawnFrames : number;
    // public float Slowdown
    m_Slowdown : number;
    // public int ParticleCap
    m_ParticleCap : number;
    // public int SpawnRadius
    m_SpawnRadius : number;
    // public float SpawnCutoff
    m_SpawnCutoff : number;
    // public float SpawnTranslucencyCutoff
    m_SpawnTranslucencyCutoff : number;
    // public BehavesLike BehavesLike
    m_BehavesLike : BehavesLike;
    // public int Lifetime
    m_Lifetime : number;
    // public Vector3D<float> SpawnDirection
    m_SpawnDirection : Vector3D;
    // public double ParticlesPerCoord
    m_ParticlesPerCoord : number;
    // public double SpiralDeltaPerCoord
    m_SpiralDeltaPerCoord : number;
    // public double SpiralRadius
    m_SpiralRadius : number;
    // public double PositionPerturbationCoefficient
    m_PositionPerturbationCoefficient : number;
    // public double MovementPerturbationCoefficient
    m_MovementPerturbationCoefficient : number;
    // public double VelocityPerturbationCoefficient
    m_VelocityPerturbationCoefficient : number;
    // public double SpawnSparkPercentage
    m_SpawnSparkPercentage : number;
    // public int SparkSpawnFrames
    m_SparkSpawnFrames : number;
    // public int LightSize
    m_LightSize : number;
    // public ColorStruct LaserColor
    m_LaserColor : ColorStruct;
    // public bool Laser
    m_Laser : boolean;
    // public bool OneFrameLight
    m_OneFrameLight : boolean;
}
// forward declarations
// ParticleClass
class ParticleClass
    extends ObjectClass
{
    // Constructor
    // public ParticleClass(ParticleTypeClass * pParticleType, CoordStruct * pCrd1, CoordStruct * pCrd2, ParticleSystemClass * pParticleSystem)
    constructor(pParticleType_0 : ParticleTypeClass, pCrd1_1 : CoordStruct, pCrd2_2 : CoordStruct, pParticleSystem_3 : ParticleSystemClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ParticleClass
    // public virtual int vt_entry_1E8()
    vt_entry_1E8() : number;
    // public static AbstractType const AbsID = AbstractType::Particle
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<ParticleClass *>, 11025864> const Array = 0xA83DC8u
    static s_Array : DynamicVectorClass<ParticleClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public ParticleTypeClass * Type
    m_Type : ParticleTypeClass;
    // public unsigned char unknown_B0
    m_unknown_B0 : number;
    // public unsigned char unknown_B1
    m_unknown_B1 : number;
    // public unsigned char unknown_B2
    m_unknown_B2 : number;
    // public unsigned long unknown_B4
    m_unknown_B4 : number;
    // public unsigned long unknown_B8
    m_unknown_B8 : number;
    // public unsigned long unknown_BC
    m_unknown_BC : number;
    // public CoordStruct Velocity
    m_Velocity : CoordStruct;
    // public unsigned long unknown_CC
    m_unknown_CC : number;
    // public double unknown_double_D0
    m_unknown_double_D0 : number;
    // public unsigned long unknown_D8
    m_unknown_D8 : number;
    // public unsigned long unknown_DC
    m_unknown_DC : number;
    // public unsigned long unknown_E0
    m_unknown_E0 : number;
    // public float Speed
    m_Speed : number;
    // Crd2 in CTOR
    // public CoordStruct unknown_coords_E8
    m_unknown_coords_E8 : CoordStruct;
    // Crd1 in CTOR
    // public CoordStruct unknown_coords_F4
    m_unknown_coords_F4 : CoordStruct;
    // { 0, 0, 0} in CTOR
    // public CoordStruct unknown_coords_100
    m_unknown_coords_100 : CoordStruct;
    // public Vector3D<float> unknown_vector3d_10C
    m_unknown_vector3d_10C : Vector3D;
    // public Vector3D<float> unknown_vector3d_118
    m_unknown_vector3d_118 : Vector3D;
    // public ParticleSystemClass * ParticleSystem
    m_ParticleSystem : ParticleSystemClass;
    // public unsigned short RemainingEC
    m_RemainingEC : number;
    // public unsigned short RemainingDC
    m_RemainingDC : number;
    // public unsigned char StateAIAdvance
    m_StateAIAdvance : number;
    // public unsigned char unknown_12D
    m_unknown_12D : number;
    // public unsigned char StartStateAI
    m_StartStateAI : number;
    // public unsigned char Translucency
    m_Translucency : number;
    // public unsigned char unknown_130
    m_unknown_130 : number;
    // public unsigned char unknown_131
    m_unknown_131 : number;
}
// ---
// ParticleTypeClass
class ParticleTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public ParticleTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static ParticleTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : ParticleTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * mcoords, HouseClass * owner)
    SpawnAtMapCoords(mcoords_0 : CellStruct | any, owner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::ParticleType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<ParticleTypeClass *>, 11025816> const Array = 0xA83D98u
    static s_Array : DynamicVectorClass<ParticleTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public CoordStruct NextParticleOffset
    m_NextParticleOffset : CoordStruct;
    // public int XVelocity
    m_XVelocity : number;
    // public int YVelocity
    m_YVelocity : number;
    // public int MinZVelocity
    m_MinZVelocity : number;
    // public int ZVelocityRange
    m_ZVelocityRange : number;
    // public double ColorSpeed
    m_ColorSpeed : number;
    // public TypeList<RGBClass *> ColorList
    m_ColorList : TypeList<RGBClass>;
    // public ColorStruct StartColor1
    m_StartColor1 : ColorStruct;
    // public ColorStruct StartColor2
    m_StartColor2 : ColorStruct;
    // public int MaxDC
    m_MaxDC : number;
    // public int MaxEC
    m_MaxEC : number;
    // public WarheadTypeClass * Warhead
    m_Warhead : WarheadTypeClass;
    // public int Damage
    m_Damage : number;
    // public int StartFrame
    m_StartFrame : number;
    // public int NumLoopFrames
    m_NumLoopFrames : number;
    // public int Translucency
    m_Translucency : number;
    // public int WindEffect
    m_WindEffect : number;
    // public float Velocity
    m_Velocity : number;
    // public float Deacc
    m_Deacc : number;
    // public int Radius
    m_Radius : number;
    // public bool DeleteOnStateLimit
    m_DeleteOnStateLimit : boolean;
    // public unsigned char EndStateAI
    m_EndStateAI : number;
    // public unsigned char StartStateAI
    m_StartStateAI : number;
    // public unsigned char StateAIAdvance
    m_StateAIAdvance : number;
    // public unsigned char FinalDamageState
    m_FinalDamageState : number;
    // public unsigned char Translucent25State
    m_Translucent25State : number;
    // public unsigned char Translucent50State
    m_Translucent50State : number;
    // public bool Normalized
    m_Normalized : boolean;
    // public ParticleTypeClass * NextParticle
    m_NextParticle : ParticleTypeClass;
    // public BehavesLike BehavesLike
    m_BehavesLike : BehavesLike;
}
// forward declarations
// WarheadTypeClass
class WarheadTypeClass
    extends AbstractTypeClass
{
    // Constructor
    // public WarheadTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static WarheadTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : WarheadTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // public static WarheadTypeClass * FindOrAllocate(char const * id)
    static FindOrAllocate(id_0 : string) : WarheadTypeClass;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::WarheadType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<WarheadTypeClass *>, 8942784> const Array = 0x8874C0u
    static s_Array : DynamicVectorClass<WarheadTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public double Deform
    m_Deform : number;
    // public double[11] Verses
    m_Verses : number;
    // public double ProneDamage
    m_ProneDamage : number;
    // public int DeformTreshold
    m_DeformTreshold : number;
    // public TypeList<AnimTypeClass *> AnimList
    m_AnimList : TypeList<AnimTypeClass>;
    // public InfDeath InfDeath
    m_InfDeath : InfDeath;
    // public float CellSpread
    m_CellSpread : number;
    // public float CellInset
    m_CellInset : number;
    // public float PercentAtMax
    m_PercentAtMax : number;
    // public bool CausesDelayKill
    m_CausesDelayKill : boolean;
    // public int DelayKillFrames
    m_DelayKillFrames : number;
    // public float DelayKillAtMax
    m_DelayKillAtMax : number;
    // public float CombatLightSize
    m_CombatLightSize : number;
    // public ParticleTypeClass * Particle
    m_Particle : ParticleTypeClass;
    // public bool Wall
    m_Wall : boolean;
    // public bool WallAbsoluteDestroyer
    m_WallAbsoluteDestroyer : boolean;
    // public bool PenetratesBunker
    m_PenetratesBunker : boolean;
    // public bool Wood
    m_Wood : boolean;
    // public bool Tiberium
    m_Tiberium : boolean;
    // public bool unknown_bool_149
    m_unknown_bool_149 : boolean;
    // public bool Sparky
    m_Sparky : boolean;
    // public bool Sonic
    m_Sonic : boolean;
    // public bool Fire
    m_Fire : boolean;
    // public bool Conventional
    m_Conventional : boolean;
    // public bool Rocker
    m_Rocker : boolean;
    // public bool DirectRocker
    m_DirectRocker : boolean;
    // public bool Bright
    m_Bright : boolean;
    // public bool CLDisableRed
    m_CLDisableRed : boolean;
    // public bool CLDisableGreen
    m_CLDisableGreen : boolean;
    // public bool CLDisableBlue
    m_CLDisableBlue : boolean;
    // public bool EMEffect
    m_EMEffect : boolean;
    // public bool MindControl
    m_MindControl : boolean;
    // public bool Poison
    m_Poison : boolean;
    // public bool IvanBomb
    m_IvanBomb : boolean;
    // public bool ElectricAssault
    m_ElectricAssault : boolean;
    // public bool Parasite
    m_Parasite : boolean;
    // public bool Temporal
    m_Temporal : boolean;
    // public bool IsLocomotor
    m_IsLocomotor : boolean;
    // public _GUID Locomotor
    m_Locomotor : any;
    // public bool Airstrike
    m_Airstrike : boolean;
    // public bool Psychedelic
    m_Psychedelic : boolean;
    // public bool BombDisarm
    m_BombDisarm : boolean;
    // public int Paralyzes
    m_Paralyzes : number;
    // public bool Culling
    m_Culling : boolean;
    // public bool MakesDisguise
    m_MakesDisguise : boolean;
    // public bool NukeMaker
    m_NukeMaker : boolean;
    // public bool Radiation
    m_Radiation : boolean;
    // public bool PsychicDamage
    m_PsychicDamage : boolean;
    // public bool AffectsAllies
    m_AffectsAllies : boolean;
    // public bool Bullets
    m_Bullets : boolean;
    // public bool Veinhole
    m_Veinhole : boolean;
    // public int ShakeXlo
    m_ShakeXlo : number;
    // public int ShakeXhi
    m_ShakeXhi : number;
    // public int ShakeYlo
    m_ShakeYlo : number;
    // public int ShakeYhi
    m_ShakeYhi : number;
    // public TypeList<VoxelAnimTypeClass *> DebrisTypes
    m_DebrisTypes : TypeList<VoxelAnimTypeClass>;
    // public TypeList<int> DebrisMaximums
    m_DebrisMaximums : TypeList<number>;
    // public int MaxDebris
    m_MaxDebris : number;
    // public int MinDebris
    m_MinDebris : number;
}
// ---
// VoxelAnimTypeClass
class VoxelAnimTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public VoxelAnimTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static VoxelAnimTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : VoxelAnimTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * owner)
    CreateObject(owner_0 : HouseClass | any) : ObjectClass;
    // public static AbstractType const AbsID = AbstractType::VoxelAnimType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<VoxelAnimTypeClass *>, 11070248> const Array = 0xA8EB28u
    static s_Array : DynamicVectorClass<VoxelAnimTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public bool Normalized
    m_Normalized : boolean;
    // public bool Translucent
    m_Translucent : boolean;
    // public bool SourceShared
    m_SourceShared : boolean;
    // public int VoxelIndex
    m_VoxelIndex : number;
    // public int Duration
    m_Duration : number;
    // public double Elasticity
    m_Elasticity : number;
    // public double MinAngularVelocity
    m_MinAngularVelocity : number;
    // public double MaxAngularVelocity
    m_MaxAngularVelocity : number;
    // public double MinZVel
    m_MinZVel : number;
    // public double MaxZVel
    m_MaxZVel : number;
    // public double MaxXYVel
    m_MaxXYVel : number;
    // public bool IsMeteor
    m_IsMeteor : boolean;
    // public VoxelAnimTypeClass * Spawns
    m_Spawns : VoxelAnimTypeClass;
    // public int SpawnCount
    m_SpawnCount : number;
    // public int StartSound
    m_StartSound : number;
    // public int StopSound
    m_StopSound : number;
    // public AnimTypeClass * BounceAnim
    m_BounceAnim : AnimTypeClass;
    // public AnimTypeClass * ExpireAnim
    m_ExpireAnim : AnimTypeClass;
    // public AnimTypeClass * TrailerAnim
    m_TrailerAnim : AnimTypeClass;
    // public int Damage
    m_Damage : number;
    // public int DamageRadius
    m_DamageRadius : number;
    // public WarheadTypeClass * Warhead
    m_Warhead : WarheadTypeClass;
    // public ParticleSystemTypeClass * AttachedSystem
    m_AttachedSystem : ParticleSystemTypeClass;
    // public bool IsTiberium
    m_IsTiberium : boolean;
}
// forward declarations
// WaveClass
class WaveClass
    extends ObjectClass
{
    // Constructor
    // public WaveClass(CoordStruct const& From, CoordStruct const& To, TechnoClass * Owner, WaveType mode, AbstractClass * Target)
    constructor(From_0 : CoordStruct, To_1 : CoordStruct, Owner_2 : TechnoClass, mode_3 : WaveType, Target_4 : AbstractClass);
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public void Draw_Magnetic(CoordStruct const& xyzFrom, CoordStruct const& xyzTo)
    Draw_Magnetic(xyzFrom_0 : CoordStruct, xyzTo_1 : CoordStruct) : void;
    // public void Draw_NonMagnetic(CoordStruct const& xyzFrom, CoordStruct const& xyzTo)
    Draw_NonMagnetic(xyzFrom_0 : CoordStruct, xyzTo_1 : CoordStruct) : void;
    // public void Update_Wave()
    Update_Wave() : void;
    // ambient
    // public void DamageArea(CoordStruct const& location) const
    DamageArea(location_0 : CoordStruct) : void;
    // public static AbstractType const AbsID = AbstractType::Wave
    static s_AbsID : AbstractType;
    // public static constant_ptr<DynamicVectorClass<WaveClass *>, 11070520> const Array = 0xA8EC38u
    static s_Array : DynamicVectorClass<WaveClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public AbstractClass * Target
    m_Target : AbstractClass;
    // public WaveType Type
    m_Type : WaveType;
    // public CoordStruct LimboCoords
    m_LimboCoords : CoordStruct;
    // public CoordStruct Pos0
    m_Pos0 : CoordStruct;
    // public Point2D WaveStartMiddle
    m_WaveStartMiddle : Point2D;
    // public Point2D WaveEndMiddle
    m_WaveEndMiddle : Point2D;
    // public Point2D WaveEndSide1
    m_WaveEndSide1 : Point2D;
    // public Point2D WaveEndSide2
    m_WaveEndSide2 : Point2D;
    // public Point2D WaveStartSide1
    m_WaveStartSide1 : Point2D;
    // public Point2D WaveStartSide2
    m_WaveStartSide2 : Point2D;
    // public CoordStruct WaveEndSide1Coord
    m_WaveEndSide1Coord : CoordStruct;
    // public CoordStruct WaveEndSide2Coord
    m_WaveEndSide2Coord : CoordStruct;
    // public CoordStruct WaveStartSide1Coord
    m_WaveStartSide1Coord : CoordStruct;
    // public CoordStruct WaveStartSide2Coord
    m_WaveStartSide2Coord : CoordStruct;
    // public bool IsTraveling
    m_IsTraveling : boolean;
    // public bool ShouldEnd
    m_ShouldEnd : boolean;
    // public unsigned char field_12E
    m_field_12E : number;
    // public unsigned char field_12F
    m_field_12F : number;
    // for sonic/magna only
    // public int WaveEC
    m_WaveEC : number;
    // public int WaveCount
    m_WaveCount : number;
    // public double MatrixScale1
    m_MatrixScale1 : number;
    // public double MatrixScale2
    m_MatrixScale2 : number;
    // public int PointData_Counter
    m_PointData_Counter : number;
    // public unsigned long PointData_Pointer
    m_PointData_Pointer : number;
    // public Point2D[6] SonicPoints
    m_SonicPoints : Point2D;
    // public Point2D[4] MagPoints
    m_MagPoints : Point2D;
    // public int PointData2_X
    m_PointData2_X : number;
    // public int PointData2_Y
    m_PointData2_Y : number;
    // public unsigned long PointData2_Pointer
    m_PointData2_Pointer : number;
    // public int[8] PitchData
    m_PitchData : number;
    // public int FacingIndex
    m_FacingIndex : number;
    // for lasers only, ctor = 160, per frame -= 6, 32 == dtor
    // public int LaserEC
    m_LaserEC : number;
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public FacingClass Facing
    m_Facing : FacingClass;
    // public DynamicVectorClass<CellClass *> Cells
    m_Cells : DynamicVectorClass<CellClass>;
    // public int[14] ColorData
    m_ColorData : number;
}
// TransitionTimer
class TransitionTimer
{
    // Constructor, Destructor
    // public TransitionTimer()
    constructor();
    // public bool AreStates11()
    AreStates11() : boolean;
    // public bool AreStates10()
    AreStates10() : boolean;
    // public bool AreStates01()
    AreStates01() : boolean;
    // public bool AreStates00()
    AreStates00() : boolean;
    // public bool IsTimerFinished()
    IsTimerFinished() : boolean;
    // public void StartTimer11(double time)
    StartTimer11(time_0 : number) : void;
    // public void StartTimer10(double time)
    StartTimer10(time_0 : number) : void;
    // public void Update()
    Update() : void;
    // public double PercentageDone()
    PercentageDone() : number;
    // public void SetToDone()
    SetToDone() : void;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public double Rate1
    m_Rate1 : number;
    // public CDTimerClass ActionTimer
    m_ActionTimer : CDTimerClass;
    // public unsigned long Rate2
    m_Rate2 : number;
    // public bool State1
    m_State1 : boolean;
    // public bool State2
    m_State2 : boolean;
}
// RecoilData
class RecoilData
{
    // public void Update()
    Update() : void;
    // public void Fire()
    Fire() : void;
    // public TurretControl Turret
    m_Turret : TurretControl;
    // public float TravelPerFrame
    m_TravelPerFrame : number;
    // public float TravelSoFar
    m_TravelSoFar : number;
    // public RecoilState State
    m_State : any;
    // public int TravelFramesLeft
    m_TravelFramesLeft : number;
}
// TurretControl
class TurretControl
{
    // public int Travel
    m_Travel : number;
    // public int CompressFrames
    m_CompressFrames : number;
    // public int RecoverFrames
    m_RecoverFrames : number;
    // public int HoldFrames
    m_HoldFrames : number;
}
// RadBeam
class RadBeam
{
    // public static RadBeam * Allocate(RadBeamType mode)
    static Allocate(mode_0 : RadBeamType) : RadBeam;
    // public void SetColor(ColorStruct const& color)
    SetColor(color_0 : ColorStruct) : void;
    // public void SetCoordsSource(CoordStruct const& loc)
    SetCoordsSource(loc_0 : CoordStruct) : void;
    // public void SetCoordsTarget(CoordStruct const& loc)
    SetCoordsTarget(loc_0 : CoordStruct) : void;
    // public static constant_ptr<DynamicVectorClass<RadBeam *>, 11553376> const Array = 0xB04A60u
    static s_Array : DynamicVectorClass<RadBeam>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public unsigned long unknown_0
    m_unknown_0 : number;
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public unsigned char unknown_8
    m_unknown_8 : number;
    // if there's difference in the Y coord of SourceLocation and TargetLocation,
    // they're both converted to screen coords (2D)
    // and the difference of those Y coords is taken as this field
    // public unsigned long unknown_C
    m_unknown_C : number;
    // public RadBeamType Type
    m_Type : RadBeamType;
    // public unsigned long unknown_14
    m_unknown_14 : number;
    // public double unknown_18
    m_unknown_18 : number;
    // public ColorStruct Color
    m_Color : ColorStruct;
    // FLH
    // public CoordStruct SourceLocation
    m_SourceLocation : CoordStruct;
    // public CoordStruct TargetLocation
    m_TargetLocation : CoordStruct;
    // public unsigned long Period
    m_Period : number;
    // public double Amplitude
    m_Amplitude : number;
    // public double unknown_48
    m_unknown_48 : number;
    // public unsigned long unknown_50
    m_unknown_50 : number;
    // public unsigned long unknown_54
    m_unknown_54 : number;
    // public unsigned char unknown_58
    m_unknown_58 : number;
    // public unsigned long unknown_5C
    m_unknown_5C : number;
    // public unsigned long unknown_60
    m_unknown_60 : number;
    // public unsigned long unknown_64
    m_unknown_64 : number;
    // public double unknown_68
    m_unknown_68 : number;
    // public CoordStruct AnotherLocation
    m_AnotherLocation : CoordStruct;
    // public unsigned long unknown_7C
    m_unknown_7C : number;
    // public double unknown_80
    m_unknown_80 : number;
    // public unsigned long unknown_88
    m_unknown_88 : number;
    // public unsigned long unknown_8C
    m_unknown_8C : number;
    // public CoordStruct AndAnotherLocation
    m_AndAnotherLocation : CoordStruct;
    // public unsigned long unknown_9C
    m_unknown_9C : number;
    // public unsigned long unknown_A0
    m_unknown_A0 : number;
    // public unsigned long unknown_A4
    m_unknown_A4 : number;
    // public unsigned long unknown_A8
    m_unknown_A8 : number;
    // public unsigned long unknown_AC
    m_unknown_AC : number;
    // public unsigned long unknown_B0
    m_unknown_B0 : number;
    // public unsigned long unknown_B4
    m_unknown_B4 : number;
    // public double unknown_B8
    m_unknown_B8 : number;
    // public unsigned char unknown_C0
    m_unknown_C0 : number;
    // public unsigned long unknown_C4
    m_unknown_C4 : number;
}
// PlanningTokenClass
class PlanningTokenClass
{
    // public static constant_ptr<DynamicVectorClass<PlanningTokenClass *>, 11291768> const Array = 0xAC4C78u
    static s_Array : DynamicVectorClass<PlanningTokenClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public TechnoClass * OwnerUnit
    m_OwnerUnit : TechnoClass;
    // public DynamicVectorClass<PlanningNodeClass *> PlanningNodes
    m_PlanningNodes : DynamicVectorClass<PlanningNodeClass>;
    // public bool field_1C
    m_field_1C : boolean;
    // public bool field_1D
    m_field_1D : boolean;
    // public int field_8C
    m_field_8C : number;
    // public int ClosedLoopNodeCount
    m_ClosedLoopNodeCount : number;
    // public int StepsToClosedLoop
    m_StepsToClosedLoop : number;
    // public bool field_98
    m_field_98 : boolean;
    // public bool field_99
    m_field_99 : boolean;
    // public unsigned long[27] unknown_20_88
    m_unknown_20_88 : number;
    // public char[108] __unknown_20_88
    m___unknown_20_88 : string;
}
// PlanningNodeClass
class PlanningNodeClass
{
    // public static constant_ptr<DynamicVectorClass<PlanningNodeClass *>, 11291440> const Unknown1 = 0xAC4B30u
    static s_Unknown1 : DynamicVectorClass<PlanningNodeClass>;
    // public static constant_ptr<DynamicVectorClass<PlanningNodeClass *>, 11291672> const Unknown2 = 0xAC4C18u
    static s_Unknown2 : DynamicVectorClass<PlanningNodeClass>;
    // public static constant_ptr<DynamicVectorClass<PlanningNodeClass *>, 11291800> const Unknown3 = 0xAC4C98u
    static s_Unknown3 : DynamicVectorClass<PlanningNodeClass>;
    // public static reference<bool, 11291892, 0> const PlanningModeActive = 0xAC4CF4u
    static s_PlanningModeActive : boolean;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public DynamicVectorClass<PlanningMemberClass *> PlanningMembers
    m_PlanningMembers : DynamicVectorClass<PlanningMemberClass>;
    // public int field_18
    m_field_18 : number;
    // public bool field_1C
    m_field_1C : boolean;
    // public DynamicVectorClass<PlanningBranchClass *> PlanningBranches
    m_PlanningBranches : DynamicVectorClass<PlanningBranchClass>;
}
// static_assert(sizeof(PlanningBranchClass) == 0x78);
// PlanningMemberClass
class PlanningMemberClass
{
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public unsigned long Packet
    m_Packet : number;
    // public int field_8
    m_field_8 : number;
    // public char field_C
    m_field_C : number;
}
// PlanningBranchClass
class PlanningBranchClass
{
}
// BulletData
class BulletData
{
    // public CDTimerClass UnknownTimer
    m_UnknownTimer : CDTimerClass;
    // public CDTimerClass ArmTimer
    m_ArmTimer : CDTimerClass;
    // public CoordStruct Location
    m_Location : CoordStruct;
    // public int Distance
    m_Distance : number;
}
// ColorScheme
class ColorScheme
{
    // Constructor, Destructor
    // public ColorScheme(char const * pID, ColorStruct const& BaseColor, BytePalette const& Pal1, BytePalette const& Pal2, int ShadeCount, bool AddToArray)
    constructor(pID_0 : string, BaseColor_1 : ColorStruct, Pal1_2 : BytePalette, Pal2_3 : BytePalette, ShadeCount_4 : number, AddToArray_5 : boolean);
    // trap! most schemes are duplicated - ShadeCount 1 and ShadeCount 53
    // public static ColorScheme * Find(char const * pID, int ShadeCount = 1)
    static Find(pID_0 : string, ShadeCount_1 : number) : ColorScheme;
    // public static int FindIndex(char const * pID, int ShadeCount = 1)
    static FindIndex(pID_0 : string, ShadeCount_1 : number) : number;
    // public static ColorScheme * FindByName(char const * pID, ColorStruct const& BaseColor, BytePalette const& Pal1, BytePalette const& Pal2, int ShadeCount)
    static FindByName(pID_0 : string, BaseColor_1 : ColorStruct, Pal1_2 : BytePalette, Pal2_3 : BytePalette, ShadeCount_4 : number) : ColorScheme;
    // public static int GetNumberOfSchemes()
    static GetNumberOfSchemes() : number;
    // public static DynamicVectorClass<ColorScheme *> * GeneratePalette(char * name)
    static GeneratePalette(name_0 : string) : DynamicVectorClass<ColorScheme>;
    // Game uses a hash table to store color scheme vectors for extra palettes, this table can be iterated by calling this function.
    // public static DynamicVectorClass<ColorScheme *> * GetPaletteSchemesFromIterator(HashIterator * it)
    static GetPaletteSchemesFromIterator(it_0 : any) : DynamicVectorClass<ColorScheme>;
    // global array
    // public static constant_ptr<DynamicVectorClass<ColorScheme *>, 11556048> const Array = 0xB054D0u
    static s_Array : DynamicVectorClass<ColorScheme>;
    // this is off by one (always one higher than the actual index). that's because consistency and reason suck.
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public BytePalette Colors
    m_Colors : BytePalette;
    // public char * ID
    m_ID : string;
    // public ColorStruct BaseColor
    m_BaseColor : ColorStruct;
    // ??? remap - indices #16-#31 are changed to mathefuckikally derived shades of BaseColor, think unittem.pal
    // public LightConvertClass * LightConvert
    m_LightConvert : LightConvertClass;
    // public int ShadeCount
    m_ShadeCount : number;
    // public int MainShadeIndex
    m_MainShadeIndex : number;
}
// AbilitiesStruct
class AbilitiesStruct
{
    // skip operator[]
    // 0x00
    // public bool FASTER
    m_FASTER : boolean;
    // 0x01
    // public bool STRONGER
    m_STRONGER : boolean;
    // 0x02
    // public bool FIREPOWER
    m_FIREPOWER : boolean;
    // 0x03
    // public bool SCATTER
    m_SCATTER : boolean;
    // 0x04
    // public bool ROF
    m_ROF : boolean;
    // 0x05
    // public bool SIGHT
    m_SIGHT : boolean;
    // 0x06
    // public bool CLOAK
    m_CLOAK : boolean;
    // 0x07
    // public bool TIBERIUM_PROOF
    m_TIBERIUM_PROOF : boolean;
    // 0x08
    // public bool VEIN_PROOF
    m_VEIN_PROOF : boolean;
    // 0x09
    // public bool SELF_HEAL
    m_SELF_HEAL : boolean;
    // 0x0A
    // public bool EXPLODES
    m_EXPLODES : boolean;
    // 0x0B
    // public bool RADAR_INVISIBLE
    m_RADAR_INVISIBLE : boolean;
    // 0x0C
    // public bool SENSORS
    m_SENSORS : boolean;
    // 0x0D
    // public bool FEARLESS
    m_FEARLESS : boolean;
    // 0x0E
    // public bool C4
    m_C4 : boolean;
    // 0x0F
    // public bool TIBERIUM_HEAL
    m_TIBERIUM_HEAL : boolean;
    // 0x10
    // public bool GUARD_AREA
    m_GUARD_AREA : boolean;
    // 0x11
    // public bool CRUSHER
    m_CRUSHER : boolean;
}
// BounceClass
class BounceClass
{
    // constructors
    // public BounceClass()
    constructor();
    // public BounceClass(CoordStruct const& coords, double elasticity, double gravity, double maxVelocity, Vector3D<float> const& velocity, double angularVelocity)
    constructor(coords_0 : CoordStruct, elasticity_1 : number, gravity_2 : number, maxVelocity_3 : number, velocity_4 : Vector3D, angularVelocity_5 : number);
    // public void Initialize(CoordStruct const& coords, double elasticity, double gravity, double maxVelocity, Vector3D<float> const& velocity, double angularVelocity)
    Initialize(coords_0 : CoordStruct, elasticity_1 : number, gravity_2 : number, maxVelocity_3 : number, velocity_4 : Vector3D, angularVelocity_5 : number) : void;
    // public CoordStruct * GetCoords(CoordStruct * pBuffer) const
    GetCoords(pBuffer_0 : CoordStruct) : CoordStruct;
    // public CoordStruct GetCoords() const
    GetCoords() : CoordStruct;
    // public Matrix3D * GetDrawingMatrix(Matrix3D * pBuffer) const
    GetDrawingMatrix(pBuffer_0 : Matrix3D) : Matrix3D;
    // public Matrix3D GetDrawingMatrix() const
    GetDrawingMatrix() : Matrix3D;
    // public Status Update()
    Update() : any;
    // speed multiplier when bouncing off the ground
    // public double Elasticity
    m_Elasticity : number;
    // subtracted from the Z coords every frame
    // public double Gravity
    m_Gravity : number;
    // 0.0 disables check
    // public double MaxVelocity
    m_MaxVelocity : number;
    // position with precision
    // public Vector3D<float> Coords
    m_Coords : Vector3D;
    // speed components
    // public Vector3D<float> Velocity
    m_Velocity : Vector3D;
    // quaternion for drawing
    // public Quaternion CurrentAngle
    m_CurrentAngle : Quaternion;
    // second quaternion as per-frame delta
    // public Quaternion AngularVelocity
    m_AngularVelocity : Quaternion;
}
// The AbstractClass is the base class of all game objects.
// BombClass
class BombClass
    extends AbstractClass
{
    // Constructor
    // Bombs have a special constructor that just should not be called like this...
    // See BombListClass::Plant
    // public BombClass()
    constructor();
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public void Detonate()
    Detonate() : void;
    // public void Disarm()
    Disarm() : void;
    // public int IsDeathBomb() const
    IsDeathBomb() : number;
    // public int GetCurrentFlickerFrame() const
    GetCurrentFlickerFrame() : number;
    // public bool TimeToExplode() const
    TimeToExplode() : boolean;
    // public static AbstractType const AbsID = AbstractType::Bomb
    static s_AbsID : AbstractType;
    // Most likely Ivan.
    // public TechnoClass * Owner
    m_Owner : TechnoClass;
    // public HouseClass * OwnerHouse
    m_OwnerHouse : HouseClass;
    // attaching to objects is possible, but it will never detonate
    // public ObjectClass * Target
    m_Target : ObjectClass;
    // unused - if so, [General]CanDetonateDeathBomb applies instead of CanDetonateTimeBomb
    // public int DeathBomb
    m_DeathBomb : number;
    // public int PlantingFrame
    m_PlantingFrame : number;
    // public int DetonationFrame
    m_DetonationFrame : number;
    // public AudioController Audio
    m_Audio : any;
    // public int TickSound
    m_TickSound : number;
    // seems so
    // public int ShouldPlayTickingSound
    m_ShouldPlayTickingSound : number;
    // (mostly) set to 0 on plant, 1 on detonation/removal ?
    // public bool Harmless
    m_Harmless : boolean;
}
// LineTrail
class LineTrail
{
    // Constructor, Destructor
    // public LineTrail()
    constructor();
    // public void SetDecrement(int val)
    SetDecrement(val_0 : number) : void;
    // public static void DeleteAll()
    static DeleteAll() : void;
    // skip operator new
    // skip operator delete
    // public static constant_ptr<DynamicVectorClass<LineTrail *>, 11258744> const Array = 0xABCB78u
    static s_Array : DynamicVectorClass<LineTrail>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public ColorStruct Color
    m_Color : ColorStruct;
    // public ObjectClass * Owner
    m_Owner : ObjectClass;
    // public int Decrement
    m_Decrement : number;
    // public int ActiveSlot
    m_ActiveSlot : number;
    // public LineTrailNode[32] Trails
    m_Trails : LineTrailNode;
}
// LineTrailNode
class LineTrailNode
{
    // public CoordStruct Position
    m_Position : CoordStruct;
    // public int Value
    m_Value : number;
}
// this refers to the "planning mode" waypoints you place with your mouse, not mapping waypoints
// WaypointClass
class WaypointClass
{
    // need to define a == operator so it can be used in array classes
    // public bool operator==(WaypointClass const& tWaypoint) const
    op_Equality(tWaypoint_0 : WaypointClass) : boolean;
    // Properties
    // public CellStruct Coords
    m_Coords : CellStruct;
    // public unsigned long unknown
    m_unknown : number;
}
// StartingTechnoStruct
class StartingTechnoStruct
{
    // public TechnoTypeClass * Unit
    m_Unit : TechnoTypeClass;
    // public CellStruct Cell
    m_Cell : CellStruct;
}
// The AbstractClass is the base class of all game objects.
// WaypointPathClass
class WaypointPathClass
    extends AbstractClass
{
    // Constructor
    // public WaypointPathClass(int idx)
    constructor(idx_0 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public WaypointClass * GetWaypoint(int idx) const
    GetWaypoint(idx_0 : number) : WaypointClass;
    // public WaypointClass * GetWaypointAfter(int idx) const
    GetWaypointAfter(idx_0 : number) : WaypointClass;
    // public bool WaypointExistsAt(WaypointClass * wpt) const
    WaypointExistsAt(wpt_0 : WaypointClass) : boolean;
    // public static AbstractType const AbsID = AbstractType::Waypoint
    static s_AbsID : AbstractType;
    // seems that way
    // public int CurrentWaypointIndex
    m_CurrentWaypointIndex : number;
    // actual path waypoints, no *
    // public DynamicVectorClass<WaypointClass> Waypoints
    m_Waypoints : DynamicVectorClass<WaypointClass>;
}
// UnitTrackerClass
class UnitTrackerClass
{
    // public UnitTrackerClass()
    constructor();
    // public void IncrementUnitCount(int nUnit)
    IncrementUnitCount(nUnit_0 : number) : void;
    // public void DecrementUnitCount(int nUnit)
    DecrementUnitCount(nUnit_0 : number) : void;
    // public void PopulateUnitCount(int nCount)
    PopulateUnitCount(nCount_0 : number) : void;
    // public int GetUnitCount()
    GetUnitCount() : number;
    // public int const * GetArray()
    GetArray() : number;
    // public void ClearUnitCount()
    ClearUnitCount() : void;
    // public void ToNetworkFormat()
    ToNetworkFormat() : void;
    // public void ToPCFormat()
    ToPCFormat() : void;
    // public int[512] UnitTotals
    m_UnitTotals : number;
    // public int UnitCount
    m_UnitCount : number;
    // public int InNetworkFormat
    m_InNetworkFormat : number;
}
// ZoneInfoStruct
class ZoneInfoStruct
{
    // public int Aircraft
    m_Aircraft : number;
    // public int Armor
    m_Armor : number;
    // public int Infantry
    m_Infantry : number;
}
// that's how WW calls it, seems to track levels of how much it hates other houses... typical ww style, with bugs
// AngerStruct
class AngerStruct
{
    // need to define a == operator so it can be used in array classes
    // public bool operator==(AngerStruct const& tAnger) const
    op_Equality(tAnger_0 : AngerStruct) : boolean;
    // public HouseClass * House
    m_House : HouseClass;
    // public int AngerLevel
    m_AngerLevel : number;
}
// ScoutStruct
class ScoutStruct
{
    // need to define a == operator so it can be used in array classes
    // public bool operator==(ScoutStruct const& tScout) const
    op_Equality(tScout_0 : ScoutStruct) : boolean;
    // public HouseClass * House
    m_House : HouseClass;
    // public bool IsPreferred
    m_IsPreferred : boolean;
}
// used for each of the 3 drop ships. has more functions that are not reproduced here yet
// DropshipStruct
class DropshipStruct
{
    // public DropshipStruct()
    constructor();
    // public DropshipStruct(DropshipStruct const& other)
    constructor(other_0 : DropshipStruct);
    // public unsigned char unknown_C
    m_unknown_C : number;
    // public int Count
    m_Count : number;
    // public TechnoTypeClass *[5] Types
    m_Types : TechnoTypeClass;
    // public int TotalCost
    m_TotalCost : number;
    // public CDTimerClass Timer
    m_Timer : CDTimerClass;
    // public char[12] __Timer
    m___Timer : string;
}
// BaseClass
class BaseClass
{
    // public BaseClass()
    constructor();
    // VTable
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any) : number;
    // public virtual long Save(IStream * pStm)
    Save(pStm_0 : any) : number;
    // public virtual void ComputeCRC(CRCEngine& crc) const
    ComputeCRC(crc_0 : any) : void;
    // virtual ~BaseClass() { /*???*/ }; // gcc demands a virtual since virtual funcs exist
    // public int FailedToPlaceNode(BaseNodeClass * Node)
    FailedToPlaceNode(Node_0 : BaseNodeClass) : number;
    // public int PercentBuilt
    m_PercentBuilt : number;
    // public CellStruct Center
    m_Center : CellStruct;
    // public HouseClass * Owner
    m_Owner : HouseClass;
    // Properties
    // public DynamicVectorClass<BaseNodeClass> BaseNodes
    m_BaseNodes : DynamicVectorClass<BaseNodeClass>;
    // public char[24] __BaseNodes
    m___BaseNodes : string;
    // public DynamicVectorClass<Vector2D<short>> Cells_24
    m_Cells_24 : DynamicVectorClass<Vector2D>;
    // public char[24] __Cells_24
    m___Cells_24 : string;
    // public DynamicVectorClass<Vector2D<short>> Cells_38
    m_Cells_38 : DynamicVectorClass<Vector2D>;
    // public char[24] __Cells_38
    m___Cells_38 : string;
}
// --- BaseNodeClass
// BaseNodeClass
class BaseNodeClass
{
    // need to define a == operator so it can be used in array classes
    // public bool operator==(BaseNodeClass const& tBaseNode) const
    op_Equality(tBaseNode_0 : BaseNodeClass) : boolean;
    // public int BuildingTypeIndex
    m_BuildingTypeIndex : number;
    // public CellStruct MapCoords
    m_MapCoords : CellStruct;
    // public bool Placed
    m_Placed : boolean;
    // public int Attempts
    m_Attempts : number;
}
// Randomizer
class Randomizer
{
    // public Randomizer(unsigned long dwSeed = *reinterpret_cast<DWORD*>(0xA8ED94))
    constructor(dwSeed_0 : number);
    // public int Random()
    Random() : number;
    // public int RandomRanged(int nMin, int nMax)
    RandomRanged(nMin_0 : number, nMax_1 : number) : number;
    // helper methods
    // public double RandomDouble()
    RandomDouble() : number;
    // skip operator()
    // skip operator()
    // for any randomization happening inside a match (odds of a survivor, crate, etc), use the ScenarioClass::Random object instead!
    // this object should only be used for RMG and other randomness outside a match
    // public static reference<Randomizer, 8940424, 0> const Global = 0x886B88u
    static s_Global : Randomizer;
    // Properties
    // public bool unknown_00
    m_unknown_00 : boolean;
    // from Table
    // public int Next1
    m_Next1 : number;
    // from Table
    // public int Next2
    m_Next2 : number;
    // public unsigned long[250] Table
    m_Table : number;
}
// LinkClass
class LinkClass
{
    // Constructors
    // public LinkClass(LinkClass& another)
    constructor(another_0 : LinkClass);
    // LinkClass
    // public virtual LinkClass * GetNext()
    GetNext() : LinkClass;
    // public virtual LinkClass * GetPrev()
    GetPrev() : LinkClass;
    // public virtual LinkClass * Add(LinkClass& another)
    Add(another_0 : LinkClass) : LinkClass;
    // public virtual LinkClass * AddTail(LinkClass& another)
    AddTail(another_0 : LinkClass) : LinkClass;
    // public virtual LinkClass * AddHead(LinkClass& another)
    AddHead(another_0 : LinkClass) : LinkClass;
    // public virtual LinkClass * HeadOfList(LinkClass& another)
    HeadOfList(another_0 : LinkClass) : LinkClass;
    // public virtual LinkClass * TailOfList(LinkClass& another)
    TailOfList(another_0 : LinkClass) : LinkClass;
    // public virtual void Zap()
    Zap() : void;
    // public virtual LinkClass * Remove()
    Remove() : LinkClass;
    // skip operator=
    // Properties
    // public LinkClass * Next
    m_Next : LinkClass;
    // public LinkClass * Previous
    m_Previous : LinkClass;
}
// GadgetClass
class GadgetClass
    extends LinkClass
{
    // Constructors
    // public GadgetClass(int nX, int nY, int nWidth, int nHeight, GadgetFlag eFlag, bool bSticky)
    constructor(nX_0 : number, nY_1 : number, nWidth_2 : number, nHeight_3 : number, eFlag_4 : GadgetFlag, bSticky_5 : boolean);
    // public GadgetClass(GadgetClass& another)
    constructor(another_0 : GadgetClass);
    // LinkClass
    // public virtual GadgetClass * GetNext()
    GetNext() : GadgetClass;
    // public virtual GadgetClass * GetPrev()
    GetPrev() : GadgetClass;
    // public virtual GadgetClass * Remove()
    Remove() : GadgetClass;
    // GadgetClass
    // public virtual unsigned long Input()
    Input() : number;
    // public virtual void DrawAll(bool bForced)
    DrawAll(bForced_0 : boolean) : void;
    // public virtual void DeleteList()
    DeleteList() : void;
    // public virtual GadgetClass * ExtractGadget(unsigned int nID)
    ExtractGadget(nID_0 : number) : GadgetClass;
    // public virtual void MarkListToRedraw()
    MarkListToRedraw() : void;
    // public virtual void Disable()
    Disable() : void;
    // public virtual void Enable()
    Enable() : void;
    // public virtual unsigned int const GetID()
    GetID() : number;
    // public virtual void MarkRedraw()
    MarkRedraw() : void;
    // public virtual void PeerToPeer(unsigned int Flags, unsigned long * pKey, GadgetClass * pSendTo)
    PeerToPeer(Flags_0 : number, pKey_1 : number, pSendTo_2 : GadgetClass) : void;
    // public virtual void SetFocus()
    SetFocus() : void;
    // public virtual void KillFocus()
    KillFocus() : void;
    // public virtual bool IsFocused()
    IsFocused() : boolean;
    // public virtual bool IsListToRedraw()
    IsListToRedraw() : boolean;
    // public virtual bool IsToRedraw()
    IsToRedraw() : boolean;
    // public virtual void SetPosition(int X, int Y)
    SetPosition(X_0 : number, Y_1 : number) : void;
    // public virtual void SetDimension(int Width, int Height)
    SetDimension(Width_0 : number, Height_1 : number) : void;
    // public virtual bool Draw(bool bForced)
    Draw(bForced_0 : boolean) : boolean;
    // public virtual void OnMouseEnter()
    OnMouseEnter() : void;
    // public virtual void OnMouseLeave()
    OnMouseLeave() : void;
    // public virtual void StickyProcess(GadgetFlag Flags)
    StickyProcess(Flags_0 : GadgetFlag) : void;
    // public virtual bool Action(GadgetFlag Flags, unsigned long * pKey, KeyModifier Modifier)
    Action(Flags_0 : GadgetFlag, pKey_1 : number, Modifier_2 : KeyModifier) : boolean;
    // public virtual bool Clicked(unsigned long * pKey, GadgetFlag Flags, int X, int Y, KeyModifier Modifier)
    Clicked(pKey_0 : number, Flags_1 : GadgetFlag, X_2 : number, Y_3 : number, Modifier_4 : KeyModifier) : boolean;
    // skip operator=
    // public GadgetClass * ExtractGadgetAt(int X, int Y)
    ExtractGadgetAt(X_0 : number, Y_1 : number) : GadgetClass;
    // Statics
    // public static int GetColorScheme()
    static GetColorScheme() : number;
    // Properties
    // public int X
    m_X : number;
    // public int Y
    m_Y : number;
    // public int Width
    m_Width : number;
    // public int Height
    m_Height : number;
    // public bool NeedsRedraw
    m_NeedsRedraw : boolean;
    // public bool IsSticky
    m_IsSticky : boolean;
    // public bool Disabled
    m_Disabled : boolean;
    // public GadgetFlag Flags
    m_Flags : GadgetFlag;
}
// things that I can't put into nice meaningful classes
// Game
class Game
{
    // the game's own rounding function
    // infamous for true'ing (F2I(-5.00) == -4.00)
    // public static long long F2I64(double val)
    static F2I64(val_0 : number) : number;
    // the game's own rounding function
    // infamous for true'ing (F2I(-5.00) == -4.00)
    // public static int F2I(double val)
    static F2I(val_0 : number) : number;
    // public static void RaiseError(long err)
    static RaiseError(err_0 : number) : void;
    // actually is SessionClass::Callback
    // public static void SetProgress(int progress)
    static SetProgress(progress_0 : number) : void;
    // public static void CallBack()
    static CallBack() : void;
    // public static int GetResource(int ID, int Type)
    static GetResource(ID_0 : number, Type_1 : number) : number;
    // public static void CenterWindowIn(HWND__ * Child, HWND__ * Parent)
    static CenterWindowIn(Child_0 : any, Parent_1 : any) : void;
    // public static void sub_53E420(HWND__ * hWindow)
    static sub_53E420(hWindow_0 : any) : void;
    // public static void sub_53E3C0(HWND__ * hWindow)
    static sub_53E3C0(hWindow_0 : any) : void;
    // public static void OnWindowMoving(tagRECT * Rect)
    static OnWindowMoving(Rect_0 : any) : void;
    // public static void PlanningManager_WM_RBUTTONUP_63AB00(Point2D XY)
    static PlanningManager_WM_RBUTTONUP_63AB00(XY_0 : Point2D) : void;
    // public static long Save_Sides(IStream * pStm, DynamicVectorClass<SideClass *> * pVector)
    static Save_Sides(pStm_0 : any, pVector_1 : DynamicVectorClass<any>) : number;
    // public static void StreamerThreadFlush()
    static StreamerThreadFlush() : void;
    // public static void UICommands_TypeSelect_7327D0(char const * iniName)
    static UICommands_TypeSelect_7327D0(iniName_0 : string) : void;
    // public static bool IsTypeSelecting()
    static IsTypeSelecting() : boolean;
    // public static double GetFloaterGravity()
    static GetFloaterGravity() : number;
    // Main loop of the game.
    // public static void MainLoop()
    static MainLoop() : void;
    // public static void KeyboardProcess(unsigned long& input)
    static KeyboardProcess(input_0 : number) : void;
    // public static _LARGE_INTEGER AudioGetTime()
    static AudioGetTime() : any;
    // public static void InitRandom()
    static InitRandom() : void;
    // public static void ShowSpecialDialog()
    static ShowSpecialDialog() : void;
    // public static void DestroyVoxelCaches()
    static DestroyVoxelCaches() : void;
    // public static void InitUIStuff()
    static InitUIStuff() : void;
    // public static void DrawRadialIndicator(bool drawLine, bool adjustColor, CoordStruct const pCoord, ColorStruct color, float lineMultiplier, bool unknown1, bool unknown2)
    static DrawRadialIndicator(drawLine_0 : boolean, adjustColor_1 : boolean, pCoord_2 : CoordStruct, color_3 : ColorStruct, lineMultiplier_4 : number, unknown1_5 : boolean, unknown2_6 : boolean) : void;
    // public static void PlayMovie(char const * movieName, int queue_theme = -1, char use_hidden_surface1 = -1, char stretch_movie = -1, char use_hidden_surface2 = -1, char set_state_1 = -1)
    static PlayMovie(movieName_0 : string, queue_theme_1 : number, use_hidden_surface1_2 : number, stretch_movie_3 : number, use_hidden_surface2_4 : number, set_state_1_5 : number) : void;
    // public static void ComputeFrameCRC()
    static ComputeFrameCRC() : void;
    // public static void LogFrameCRC(int frameIndex)
    static LogFrameCRC(frameIndex_0 : number) : void;
    // the magic checksum for version validation - linked in StaticInits
    // public static reference<unsigned long, 8639840, 0> const Savegame_Magic = 0x83D560u
    static s_Savegame_Magic : number;
    // public static reference<DynamicVectorClass<unsigned long>, 11582600, 0> const COMClasses = 0xB0BC88u
    static s_COMClasses : DynamicVectorClass<number>;
    // public static reference<HWND__ *, 12006736, 0> const hWnd = 0xB73550u
    static s_hWnd : any;
    // public static reference<HINSTANCE__ *, 12006128, 0> const hInstance = 0xB732F0u
    static s_hInstance : any;
    // public static reference<bool, 8942616, 0> const bVPLRead = 0x887418u
    static s_bVPLRead : boolean;
    // public static reference<bool, 8653420, 0> const bVideoBackBuffer = 0x840A6Cu
    static s_bVideoBackBuffer : boolean;
    // public static reference<bool, 11070358, 0> const bAllowVRAMSidebar = 0xA8EB96u
    static s_bAllowVRAMSidebar : boolean;
    // public static reference<RecordFlag, 11064824, 0> const RecordingFlag = 0xA8D5F8u
    static s_RecordingFlag : RecordFlag;
    // public static reference<CCFileClass, 11064716, 0> const RecordFile = 0xA8D58Cu
    static s_RecordFile : any;
    // public static reference<bool, 8531185, 0> const bDrawShadow = 0x822CF1u
    static s_bDrawShadow : boolean;
    // public static reference<bool, 9047535, 0> const bAllowDirect3D = 0x8A0DEFu
    static s_bAllowDirect3D : boolean;
    // public static reference<bool, 9047536, 0> const bDirect3DIsUseable = 0x8A0DF0u
    static s_bDirect3DIsUseable : boolean;
    // public static reference<bool, 11069856, 0> const IsActive = 0xA8E9A0u
    static s_IsActive : boolean;
    // public static reference<bool, 11070848, 0> const IsFocused = 0xA8ED80u
    static s_IsFocused : boolean;
    // public static reference<int, 11070880, 0> const SpecialDialog = 0xA8EDA0u
    static s_SpecialDialog : number;
    // public static reference<bool, 11290836, 0> const PCXInitialized = 0xAC48D4
    static s_PCXInitialized : boolean;
    // public static reference<int, 11070868, 0> const Seed = 0xA8ED94u
    static s_Seed : number;
    // public static reference<int, 8531188, 0> const TechLevel = 0x822CF4u
    static s_TechLevel : number;
    // public static reference<int, 11056460, 0> const PlayerCount = 0xA8B54Cu
    static s_PlayerCount : number;
    // public static reference<int, 11056020, 0> const PlayerColor = 0xA8B394u
    static s_PlayerColor : number;
    // public static reference<bool, 11276488, 0> const ObserverMode = 0xAC10C8u
    static s_ObserverMode : boolean;
    // public static reference<char, 11057376, 0> const ScenarioName = 0xA8B8E0u
    static s_ScenarioName : number;
    // public static reference<bool, 11073452, 0> const DontSetExceptionHandler = 0xA8F7ACu
    static s_DontSetExceptionHandler : boolean;
    // public static reference<bool, 11552896, 0> const EnableMPSyncDebug = 0xB04880u
    static s_EnableMPSyncDebug : boolean;
    // public static reference<Vector3D<float>, 8942704, 0> const VoxelLightSource = 0x887470
    static s_VoxelLightSource : Vector3D;
    // public static reference<Vector3D<float>, 8942624, 0> const VoxelShadowLightSource = 0x887420
    static s_VoxelShadowLightSource : Vector3D;
}
// ---
// SmudgeTypeClass
class SmudgeTypeClass
    extends ObjectTypeClass
{
    // Constructor
    // public SmudgeTypeClass(char const * pID)
    constructor(pID_0 : string);
    // Array
    // public static SmudgeTypeClass * Find(char const * pID)
    static Find(pID_0 : string) : SmudgeTypeClass;
    // Array
    // public static int FindIndex(char const * pID)
    static FindIndex(pID_0 : string) : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // ObjectTypeClass
    // public virtual bool SpawnAtMapCoords(CellStruct * pMapCoords, HouseClass * pOwner)
    SpawnAtMapCoords(pMapCoords_0 : CellStruct | any, pOwner_1 : HouseClass | any) : boolean;
    // public virtual ObjectClass * CreateObject(HouseClass * pOwner)
    CreateObject(pOwner_0 : HouseClass | any) : ObjectClass;
    // SmudgeTypeClass
    // public virtual void DrawIt(Point2D const& Point, RectangleStruct const& Rect, int SmudgeData, int Height, CellStruct const& MapCoords)
    DrawIt(Point_0 : Point2D, Rect_1 : RectangleStruct, SmudgeData_2 : number, Height_3 : number, MapCoords_4 : CellStruct) : void;
    // public static void LoadFromIniList(int idxTheatre)
    static LoadFromIniList(idxTheatre_0 : number) : void;
    // public static AbstractType const AbsID = AbstractType::SmudgeType
    static s_AbsID : AbstractType;
    // Array
    // public static constant_ptr<DynamicVectorClass<SmudgeTypeClass *>, 11070488> const Array = 0xA8EC18u
    static s_Array : DynamicVectorClass<SmudgeTypeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ArrayIndex
    m_ArrayIndex : number;
    // public int Width
    m_Width : number;
    // public int Height
    m_Height : number;
    // public bool Crater
    m_Crater : boolean;
    // public bool Burn
    m_Burn : boolean;
}
// Difficulty
// DifficultyStruct
class DifficultyStruct
{
    // public double Firepower
    m_Firepower : number;
    // public double GroundSpeed
    m_GroundSpeed : number;
    // public double AirSpeed
    m_AirSpeed : number;
    // public double Armor
    m_Armor : number;
    // public double ROF
    m_ROF : number;
    // public double Cost
    m_Cost : number;
    // public double BuildTime
    m_BuildTime : number;
    // public double RepairDelay
    m_RepairDelay : number;
    // public double BuildDelay
    m_BuildDelay : number;
    // public bool BuildSlowdown
    m_BuildSlowdown : boolean;
    // public bool DestroyWalls
    m_DestroyWalls : boolean;
    // public bool ContentScan
    m_ContentScan : boolean;
}
// Rockets
// RocketStruct
class RocketStruct
{
    // public RocketStruct()
    constructor();
    // public RocketStruct(noinit_t)
    constructor(_0 : any);
    // public int PauseFrames
    m_PauseFrames : number;
    // public int TiltFrames
    m_TiltFrames : number;
    // public float PitchInitial
    m_PitchInitial : number;
    // public float PitchFinal
    m_PitchFinal : number;
    // public float TurnRate
    m_TurnRate : number;
    // shouldn't this be a float? prolly a mistake by WW...
    // public int RaiseRate
    m_RaiseRate : number;
    // public float Acceleration
    m_Acceleration : number;
    // public int Altitude
    m_Altitude : number;
    // public int Damage
    m_Damage : number;
    // public int EliteDamage
    m_EliteDamage : number;
    // public int BodyLength
    m_BodyLength : number;
    // public bool LazyCurve
    m_LazyCurve : boolean;
    // public AircraftTypeClass * Type
    m_Type : AircraftTypeClass;
}
// RulesClass
class RulesClass
{
    // CTOR / DTOR
    // public RulesClass()
    constructor();
    // call this for the first INI file only
    // public void Init(CCINIClass * pINI)
    Init(pINI_0 : CCINIClass) : void;
    // call this instead of Init for the later files (gamemode, map)
    // reads the generic/list sections like [VehicleTypes] from pINI
    // doesn't actually load [MTNK] or other list contents' sections
    // public void Read_File(CCINIClass * pINI)
    Read_File(pINI_0 : CCINIClass) : void;
    // public void Read_SpecialWeapons(CCINIClass * pINI)
    Read_SpecialWeapons(pINI_0 : CCINIClass) : void;
    // public void Read_AudioVisual(CCINIClass * pINI)
    Read_AudioVisual(pINI_0 : CCINIClass) : void;
    // public void Read_CrateRules(CCINIClass * pINI)
    Read_CrateRules(pINI_0 : CCINIClass) : void;
    // public void Read_CombatDamage(CCINIClass * pINI)
    Read_CombatDamage(pINI_0 : CCINIClass) : void;
    // public void Read_Radiation(CCINIClass * pINI)
    Read_Radiation(pINI_0 : CCINIClass) : void;
    // public void Read_ElevationModel(CCINIClass * pINI)
    Read_ElevationModel(pINI_0 : CCINIClass) : void;
    // public void Read_WallModel(CCINIClass * pINI)
    Read_WallModel(pINI_0 : CCINIClass) : void;
    // public void Read_Difficulty(CCINIClass * pINI)
    Read_Difficulty(pINI_0 : CCINIClass) : void;
    // public void Read_Colors(CCINIClass * pINI)
    Read_Colors(pINI_0 : CCINIClass) : void;
    // public void Read_ColorAdd(CCINIClass * pINI)
    Read_ColorAdd(pINI_0 : CCINIClass) : void;
    // public void Read_General(CCINIClass * pINI)
    Read_General(pINI_0 : CCINIClass) : void;
    // public void Read_MultiplayerDialogSettings(CCINIClass * pINI)
    Read_MultiplayerDialogSettings(pINI_0 : CCINIClass) : void;
    // public void Read_Maximums(CCINIClass * pINI)
    Read_Maximums(pINI_0 : CCINIClass) : void;
    // public void Read_InfantryTypes(CCINIClass * pINI)
    Read_InfantryTypes(pINI_0 : CCINIClass) : void;
    // public void Read_Countries(CCINIClass * pINI)
    Read_Countries(pINI_0 : CCINIClass) : void;
    // public void Read_VehicleTypes(CCINIClass * pINI)
    Read_VehicleTypes(pINI_0 : CCINIClass) : void;
    // public void Read_AircraftTypes(CCINIClass * pINI)
    Read_AircraftTypes(pINI_0 : CCINIClass) : void;
    // public void Read_Sides(CCINIClass * pINI)
    Read_Sides(pINI_0 : CCINIClass) : void;
    // public void Read_SuperWeaponTypes(CCINIClass * pINI)
    Read_SuperWeaponTypes(pINI_0 : CCINIClass) : void;
    // public void Read_BuildingTypes(CCINIClass * pINI)
    Read_BuildingTypes(pINI_0 : CCINIClass) : void;
    // public void Read_TerrainTypes(CCINIClass * pINI)
    Read_TerrainTypes(pINI_0 : CCINIClass) : void;
    // public void Read_Teams_obsolete(CCINIClass * pINI)
    Read_Teams_obsolete(pINI_0 : CCINIClass) : void;
    // public void Read_SmudgeTypes(CCINIClass * pINI)
    Read_SmudgeTypes(pINI_0 : CCINIClass) : void;
    // public void Read_OverlayTypes(CCINIClass * pINI)
    Read_OverlayTypes(pINI_0 : CCINIClass) : void;
    // public void Read_Animations(CCINIClass * pINI)
    Read_Animations(pINI_0 : CCINIClass) : void;
    // public void Read_VoxelAnims(CCINIClass * pINI)
    Read_VoxelAnims(pINI_0 : CCINIClass) : void;
    // public void Read_Warheads(CCINIClass * pINI)
    Read_Warheads(pINI_0 : CCINIClass) : void;
    // public void Read_Particles(CCINIClass * pINI)
    Read_Particles(pINI_0 : CCINIClass) : void;
    // public void Read_ParticleSystems(CCINIClass * pINI)
    Read_ParticleSystems(pINI_0 : CCINIClass) : void;
    // public void Read_AI(CCINIClass * pINI)
    Read_AI(pINI_0 : CCINIClass) : void;
    // public void Read_Powerups(CCINIClass * pINI)
    Read_Powerups(pINI_0 : CCINIClass) : void;
    // public void Read_LandCharacteristics(CCINIClass * pINI)
    Read_LandCharacteristics(pINI_0 : CCINIClass) : void;
    // public void Read_IQ(CCINIClass * pINI)
    Read_IQ(pINI_0 : CCINIClass) : void;
    // public void Read_JumpjetControls(CCINIClass * pINI)
    Read_JumpjetControls(pINI_0 : CCINIClass) : void;
    // public void Read_Difficulties(CCINIClass * pINI)
    Read_Difficulties(pINI_0 : CCINIClass) : void;
    // public void Read_Movies(CCINIClass * pINI)
    Read_Movies(pINI_0 : CCINIClass) : void;
    // public void Read_AdvancedCommandBar(CCINIClass * pINI)
    Read_AdvancedCommandBar(pINI_0 : CCINIClass) : void;
    // public void PointerGotInvalid(AbstractClass * pInvalid, bool removed)
    PointerGotInvalid(pInvalid_0 : AbstractClass, removed_1 : boolean) : void;
    // Static
    // public static reference<RulesClass *, 8942048, 0> const Instance = 0x8871E0u
    static s_Instance : RulesClass;
    // Properties
    // public int DetailMinFrameRateNormal
    m_DetailMinFrameRateNormal : number;
    // public int DetailMinFrameRateMovie
    m_DetailMinFrameRateMovie : number;
    // public int DetailBufferZoneWidth
    m_DetailBufferZoneWidth : number;
    // public int AmmoCrateDamage
    m_AmmoCrateDamage : number;
    // public UnitTypeClass * LargeVisceroid
    m_LargeVisceroid : UnitTypeClass;
    // public UnitTypeClass * SmallVisceroid
    m_SmallVisceroid : UnitTypeClass;
    // public int AttackingAircraftSightRange
    m_AttackingAircraftSightRange : number;
    // public double TunnelSpeed
    m_TunnelSpeed : number;
    // public double TiberiumHeal
    m_TiberiumHeal : number;
    // public int SelfHealInfantryFrames
    m_SelfHealInfantryFrames : number;
    // public int SelfHealInfantryAmount
    m_SelfHealInfantryAmount : number;
    // public int SelfHealUnitFrames
    m_SelfHealUnitFrames : number;
    // public int SelfHealUnitAmount
    m_SelfHealUnitAmount : number;
    // public bool FreeMCV
    m_FreeMCV : boolean;
    // public bool BerzerkAllowed
    m_BerzerkAllowed : boolean;
    // public int PoseDir
    m_PoseDir : number;
    // public int DeployDir
    m_DeployDir : number;
    // public AnimTypeClass * DropPodPuff
    m_DropPodPuff : AnimTypeClass;
    // public int WaypointAnimationSpeed
    m_WaypointAnimationSpeed : number;
    // public AnimTypeClass * BarrelExplode
    m_BarrelExplode : AnimTypeClass;
    // public TypeList<VoxelAnimTypeClass *> BarrelDebris
    m_BarrelDebris : TypeList<VoxelAnimTypeClass>;
    // public ParticleSystemTypeClass * BarrelParticle
    m_BarrelParticle : ParticleSystemTypeClass;
    // public float RadarEventColorSpeed
    m_RadarEventColorSpeed : number;
    // public int RadarEventMinRadius
    m_RadarEventMinRadius : number;
    // public float RadarEventSpeed
    m_RadarEventSpeed : number;
    // public float RadarEventRotationSpeed
    m_RadarEventRotationSpeed : number;
    // public int FlashFrameTime
    m_FlashFrameTime : number;
    // public int RadarCombatFlashTime
    m_RadarCombatFlashTime : number;
    // public int MaxWaypointPathLength
    m_MaxWaypointPathLength : number;
    // public AnimTypeClass * Wake
    m_Wake : AnimTypeClass;
    // public AnimTypeClass * NukeTakeOff
    m_NukeTakeOff : AnimTypeClass;
    // public AnimTypeClass * InfantryExplode
    m_InfantryExplode : AnimTypeClass;
    // public AnimTypeClass * FlamingInfantry
    m_FlamingInfantry : AnimTypeClass;
    // public AnimTypeClass * InfantryHeadPop
    m_InfantryHeadPop : AnimTypeClass;
    // public AnimTypeClass * InfantryNuked
    m_InfantryNuked : AnimTypeClass;
    // public AnimTypeClass * InfantryVirus
    m_InfantryVirus : AnimTypeClass;
    // public AnimTypeClass * InfantryBrute
    m_InfantryBrute : AnimTypeClass;
    // public AnimTypeClass * InfantryMutate
    m_InfantryMutate : AnimTypeClass;
    // public AnimTypeClass * Behind
    m_Behind : AnimTypeClass;
    // public double AITriggerSuccessWeightDelta
    m_AITriggerSuccessWeightDelta : number;
    // public double AITriggerFailureWeightDelta
    m_AITriggerFailureWeightDelta : number;
    // public double AITriggerTrackRecordCoefficient
    m_AITriggerTrackRecordCoefficient : number;
    // public int VeinholeMonsterStrength
    m_VeinholeMonsterStrength : number;
    // public int MaxVeinholeGrowth
    m_MaxVeinholeGrowth : number;
    // public int VeinholeGrowthRate
    m_VeinholeGrowthRate : number;
    // public int VeinholeShrinkRate
    m_VeinholeShrinkRate : number;
    // public AnimTypeClass * VeinAttack
    m_VeinAttack : AnimTypeClass;
    // public int VeinDamage
    m_VeinDamage : number;
    // public int MaximumQueuedObjects
    m_MaximumQueuedObjects : number;
    // public int AircraftFogReveal
    m_AircraftFogReveal : number;
    // public OverlayTypeClass * WoodCrateImg
    m_WoodCrateImg : OverlayTypeClass;
    // public OverlayTypeClass * CrateImg
    m_CrateImg : OverlayTypeClass;
    // public OverlayTypeClass * WaterCrateImg
    m_WaterCrateImg : OverlayTypeClass;
    // public TypeList<AnimTypeClass *> DropPod
    m_DropPod : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> DeadBodies
    m_DeadBodies : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> MetallicDebris
    m_MetallicDebris : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> BridgeExplosions
    m_BridgeExplosions : TypeList<AnimTypeClass>;
    // public int DigSound
    m_DigSound : number;
    // public int CreateUnitSound
    m_CreateUnitSound : number;
    // public int CreateInfantrySound
    m_CreateInfantrySound : number;
    // public int CreateAircraftSound
    m_CreateAircraftSound : number;
    // public int BaseUnderAttackSound
    m_BaseUnderAttackSound : number;
    // public int GUIMainButtonSound
    m_GUIMainButtonSound : number;
    // public int GUIBuildSound
    m_GUIBuildSound : number;
    // public int GUITabSound
    m_GUITabSound : number;
    // public int GUIOpenSound
    m_GUIOpenSound : number;
    // public int GUICloseSound
    m_GUICloseSound : number;
    // public int GUIMoveOutSound
    m_GUIMoveOutSound : number;
    // public int GUIMoveInSound
    m_GUIMoveInSound : number;
    // public int GUIComboOpenSound
    m_GUIComboOpenSound : number;
    // public int GUIComboCloseSound
    m_GUIComboCloseSound : number;
    // public int GUICheckboxSound
    m_GUICheckboxSound : number;
    // public int ScoreAnimSound
    m_ScoreAnimSound : number;
    // public int IFVTransformSound
    m_IFVTransformSound : number;
    // public int PsychicSensorDetectSound
    m_PsychicSensorDetectSound : number;
    // public int BuildingGarrisonedSound
    m_BuildingGarrisonedSound : number;
    // public int BuildingAbandonedSound
    m_BuildingAbandonedSound : number;
    // public int BuildingRepairedSound
    m_BuildingRepairedSound : number;
    // public int CheerSound
    m_CheerSound : number;
    // public int PlaceBeaconSound
    m_PlaceBeaconSound : number;
    // public int DefaultChronoSound
    m_DefaultChronoSound : number;
    // public int StartPlanningModeSound
    m_StartPlanningModeSound : number;
    // public int AddPlanningModeCommandSound
    m_AddPlanningModeCommandSound : number;
    // public int ExecutePlanSound
    m_ExecutePlanSound : number;
    // public int EndPlanningModeSound
    m_EndPlanningModeSound : number;
    // public int CrateMoneySound
    m_CrateMoneySound : number;
    // public int CrateRevealSound
    m_CrateRevealSound : number;
    // public int CrateFireSound
    m_CrateFireSound : number;
    // public int CrateArmourSound
    m_CrateArmourSound : number;
    // public int CrateSpeedSound
    m_CrateSpeedSound : number;
    // public int CrateUnitSound
    m_CrateUnitSound : number;
    // public int CratePromoteSound
    m_CratePromoteSound : number;
    // public int ImpactWaterSound
    m_ImpactWaterSound : number;
    // public int ImpactLandSound
    m_ImpactLandSound : number;
    // public int SinkingSound
    m_SinkingSound : number;
    // public int BombTickingSound
    m_BombTickingSound : number;
    // public int BombAttachSound
    m_BombAttachSound : number;
    // public int YuriMindControlSound
    m_YuriMindControlSound : number;
    // public int ChronoInSound
    m_ChronoInSound : number;
    // public int ChronoOutSound
    m_ChronoOutSound : number;
    // public int SpySatActivationSound
    m_SpySatActivationSound : number;
    // public int SpySatDeactivationSound
    m_SpySatDeactivationSound : number;
    // public int UpgradeVeteranSound
    m_UpgradeVeteranSound : number;
    // public int UpgradeEliteSound
    m_UpgradeEliteSound : number;
    // public int VoiceIFVRepair
    m_VoiceIFVRepair : number;
    // public int SlavesFreeSound
    m_SlavesFreeSound : number;
    // public int SlaveMinerDeploySound
    m_SlaveMinerDeploySound : number;
    // public int SlaveMinerUndeploySound
    m_SlaveMinerUndeploySound : number;
    // public int BunkerWallsUpSound
    m_BunkerWallsUpSound : number;
    // public int BunkerWallsDownSound
    m_BunkerWallsDownSound : number;
    // public int RepairBridgeSound
    m_RepairBridgeSound : number;
    // public int PsychicDominatorActivateSound
    m_PsychicDominatorActivateSound : number;
    // public int GeneticMutatorActivateSound
    m_GeneticMutatorActivateSound : number;
    // public int PsychicRevealActivateSound
    m_PsychicRevealActivateSound : number;
    // public int MasterMindOverloadDeathSound
    m_MasterMindOverloadDeathSound : number;
    // public int AirstrikeAbortSound
    m_AirstrikeAbortSound : number;
    // public int AirstrikeAttackVoice
    m_AirstrikeAttackVoice : number;
    // public int MindClearedSound
    m_MindClearedSound : number;
    // public int EnterGrinderSound
    m_EnterGrinderSound : number;
    // public int LeaveGrinderSound
    m_LeaveGrinderSound : number;
    // public int EnterBioReactorSound
    m_EnterBioReactorSound : number;
    // public int LeaveBioReactorSound
    m_LeaveBioReactorSound : number;
    // public int ActivateSound
    m_ActivateSound : number;
    // public int DeactivateSound
    m_DeactivateSound : number;
    // public int SpyPlaneCamera
    m_SpyPlaneCamera : number;
    // public int LetsDoTheTimeWarpOutAgain
    m_LetsDoTheTimeWarpOutAgain : number;
    // public int LetsDoTheTimeWarpInAgain
    m_LetsDoTheTimeWarpInAgain : number;
    // public int DiskLaserChargeUp
    m_DiskLaserChargeUp : number;
    // public int SpyPlaneCameraFrames
    m_SpyPlaneCameraFrames : number;
    // public AnimTypeClass * Dig
    m_Dig : AnimTypeClass;
    // public AnimTypeClass * IonBlast
    m_IonBlast : AnimTypeClass;
    // public AnimTypeClass * IonBeam
    m_IonBeam : AnimTypeClass;
    // public TypeList<AnimTypeClass *> DamageFireTypes
    m_DamageFireTypes : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> WeatherConClouds
    m_WeatherConClouds : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> WeatherConBolts
    m_WeatherConBolts : TypeList<AnimTypeClass>;
    // public AnimTypeClass * WeatherConBoltExplosion
    m_WeatherConBoltExplosion : AnimTypeClass;
    // public WarheadTypeClass * DominatorWarhead
    m_DominatorWarhead : WarheadTypeClass;
    // public AnimTypeClass * DominatorFirstAnim
    m_DominatorFirstAnim : AnimTypeClass;
    // public AnimTypeClass * DominatorSecondAnim
    m_DominatorSecondAnim : AnimTypeClass;
    // public int DominatorFireAtPercentage
    m_DominatorFireAtPercentage : number;
    // public int DominatorCaptureRange
    m_DominatorCaptureRange : number;
    // public int DominatorDamage
    m_DominatorDamage : number;
    // public int MindControlAttackLineFrames
    m_MindControlAttackLineFrames : number;
    // public int DrainMoneyFrameDelay
    m_DrainMoneyFrameDelay : number;
    // public int DrainMoneyAmount
    m_DrainMoneyAmount : number;
    // public AnimTypeClass * DrainAnimationType
    m_DrainAnimationType : AnimTypeClass;
    // public AnimTypeClass * ControlledAnimationType
    m_ControlledAnimationType : AnimTypeClass;
    // public AnimTypeClass * PermaControlledAnimationType
    m_PermaControlledAnimationType : AnimTypeClass;
    // public AnimTypeClass * ChronoBlast
    m_ChronoBlast : AnimTypeClass;
    // public AnimTypeClass * ChronoBlastDest
    m_ChronoBlastDest : AnimTypeClass;
    // public AnimTypeClass * ChronoPlacement
    m_ChronoPlacement : AnimTypeClass;
    // public AnimTypeClass * ChronoBeam
    m_ChronoBeam : AnimTypeClass;
    // public AnimTypeClass * WarpIn
    m_WarpIn : AnimTypeClass;
    // public AnimTypeClass * WarpOut
    m_WarpOut : AnimTypeClass;
    // public AnimTypeClass * WarpAway
    m_WarpAway : AnimTypeClass;
    // public AnimTypeClass * ChronoSparkle1
    m_ChronoSparkle1 : AnimTypeClass;
    // public AnimTypeClass * IronCurtainInvokeAnim
    m_IronCurtainInvokeAnim : AnimTypeClass;
    // public AnimTypeClass * ForceShieldInvokeAnim
    m_ForceShieldInvokeAnim : AnimTypeClass;
    // public AnimTypeClass * WeaponNullifyAnim
    m_WeaponNullifyAnim : AnimTypeClass;
    // public AnimTypeClass * AtmosphereEntry
    m_AtmosphereEntry : AnimTypeClass;
    // public TypeList<int> PrerequisitePower
    m_PrerequisitePower : TypeList<number>;
    // public TypeList<int> PrerequisiteFactory
    m_PrerequisiteFactory : TypeList<number>;
    // public TypeList<int> PrerequisiteBarracks
    m_PrerequisiteBarracks : TypeList<number>;
    // public TypeList<int> PrerequisiteRadar
    m_PrerequisiteRadar : TypeList<number>;
    // public TypeList<int> PrerequisiteTech
    m_PrerequisiteTech : TypeList<number>;
    // public TypeList<int> PrerequisiteProc
    m_PrerequisiteProc : TypeList<number>;
    // public UnitTypeClass * PrerequisiteProcAlternate
    m_PrerequisiteProcAlternate : UnitTypeClass;
    // public int GateUp
    m_GateUp : number;
    // public int GateDown
    m_GateDown : number;
    // public int TurnRate
    m_TurnRate : number;
    // public int Speed
    m_Speed : number;
    // public double Climb
    m_Climb : number;
    // public int CruiseHeight
    m_CruiseHeight : number;
    // public double Acceleration
    m_Acceleration : number;
    // public double WobblesPerSecond
    m_WobblesPerSecond : number;
    // public int WobbleDeviation
    m_WobbleDeviation : number;
    // public TypeList<int> RadarEventSuppressionDistances
    m_RadarEventSuppressionDistances : TypeList<number>;
    // public TypeList<int> RadarEventVisibilityDurations
    m_RadarEventVisibilityDurations : TypeList<number>;
    // public TypeList<int> RadarEventDurations
    m_RadarEventDurations : TypeList<number>;
    // public int IonCannonDamage
    m_IonCannonDamage : number;
    // public int RailgunDamageRadius
    m_RailgunDamageRadius : number;
    // public BuildingTypeClass * PrismType
    m_PrismType : BuildingTypeClass;
    // this is int(100 * ini value)
    // public int PrismSupportModifier
    m_PrismSupportModifier : number;
    // public int PrismSupportMax
    m_PrismSupportMax : number;
    // public int PrismSupportDelay
    m_PrismSupportDelay : number;
    // public int PrismSupportDuration
    m_PrismSupportDuration : number;
    // public int PrismSupportHeight
    m_PrismSupportHeight : number;
    // public RocketStruct V3Rocket
    m_V3Rocket : RocketStruct;
    // public RocketStruct DMisl
    m_DMisl : RocketStruct;
    // public RocketStruct CMisl
    m_CMisl : RocketStruct;
    // public int ParadropRadius
    m_ParadropRadius : number;
    // public double ZoomInFactor
    m_ZoomInFactor : number;
    // public double ConditionRedSparkingProbability
    m_ConditionRedSparkingProbability : number;
    // public double ConditionYellowSparkingProbability
    m_ConditionYellowSparkingProbability : number;
    // public int TiberiumExplosionDamage
    m_TiberiumExplosionDamage : number;
    // public int TiberiumStrength
    m_TiberiumStrength : number;
    // public float MinLowPowerProductionSpeed
    m_MinLowPowerProductionSpeed : number;
    // public float MaxLowPowerProductionSpeed
    m_MaxLowPowerProductionSpeed : number;
    // public float LowPowerPenaltyModifier
    m_LowPowerPenaltyModifier : number;
    // public float MultipleFactory
    m_MultipleFactory : number;
    // public int MaximumCheerRate
    m_MaximumCheerRate : number;
    // public double TreeFlammability
    m_TreeFlammability : number;
    // public double MissileSpeedVar
    m_MissileSpeedVar : number;
    // public double MissileROTVar
    m_MissileROTVar : number;
    // public int MissileSafetyAltitude
    m_MissileSafetyAltitude : number;
    // public WeaponTypeClass * DropPodWeapon
    m_DropPodWeapon : WeaponTypeClass;
    // public int DropPodHeight
    m_DropPodHeight : number;
    // public int DropPodSpeed
    m_DropPodSpeed : number;
    // public double DropPodAngle
    m_DropPodAngle : number;
    // public double ScrollMultiplier
    m_ScrollMultiplier : number;
    // public double CrewEscape
    m_CrewEscape : number;
    // public int ShakeScreen
    m_ShakeScreen : number;
    // public int HoverHeight
    m_HoverHeight : number;
    // public double HoverBob
    m_HoverBob : number;
    // public double HoverBoost
    m_HoverBoost : number;
    // public double HoverAcceleration
    m_HoverAcceleration : number;
    // public double HoverBrake
    m_HoverBrake : number;
    // public double HoverDampen
    m_HoverDampen : number;
    // public double PlacementDelay
    m_PlacementDelay : number;
    // public TypeList<VoxelAnimTypeClass *> ExplosiveVoxelDebris
    m_ExplosiveVoxelDebris : TypeList<VoxelAnimTypeClass>;
    // public VoxelAnimTypeClass * TireVoxelDebris
    m_TireVoxelDebris : VoxelAnimTypeClass;
    // public VoxelAnimTypeClass * ScrapVoxelDebris
    m_ScrapVoxelDebris : VoxelAnimTypeClass;
    // public int BridgeVoxelMax
    m_BridgeVoxelMax : number;
    // public int CloakingStages
    m_CloakingStages : number;
    // public int RevealTriggerRadius
    m_RevealTriggerRadius : number;
    // public double ShipSinkingWeight
    m_ShipSinkingWeight : number;
    // public double IceCrackingWeight
    m_IceCrackingWeight : number;
    // public double IceBreakingWeight
    m_IceBreakingWeight : number;
    // public TypeList<int> IceCrackSounds
    m_IceCrackSounds : TypeList<number>;
    // public unsigned char CliffBackImpassability
    m_CliffBackImpassability : number;
    // public double VeteranRatio
    m_VeteranRatio : number;
    // public double VeteranCombat
    m_VeteranCombat : number;
    // public double VeteranSpeed
    m_VeteranSpeed : number;
    // public double VeteranSight
    m_VeteranSight : number;
    // public double VeteranArmor
    m_VeteranArmor : number;
    // public double VeteranROF
    m_VeteranROF : number;
    // public double VeteranCap
    m_VeteranCap : number;
    // public int CloakSound
    m_CloakSound : number;
    // public int SellSound
    m_SellSound : number;
    // public int GameClosed
    m_GameClosed : number;
    // public int IncomingMessage
    m_IncomingMessage : number;
    // public int SystemError
    m_SystemError : number;
    // public int OptionsChanged
    m_OptionsChanged : number;
    // public int GameForming
    m_GameForming : number;
    // public int PlayerLeft
    m_PlayerLeft : number;
    // public int PlayerJoined
    m_PlayerJoined : number;
    // public int MessageCharTyped
    m_MessageCharTyped : number;
    // public int Construction
    m_Construction : number;
    // public TypeList<int> CreditTicks
    m_CreditTicks : TypeList<number>;
    // public int BuildingDieSound
    m_BuildingDieSound : number;
    // public int BuildingSlam
    m_BuildingSlam : number;
    // public int RadarOn
    m_RadarOn : number;
    // public int RadarOff
    m_RadarOff : number;
    // public int MovieOn
    m_MovieOn : number;
    // public int MovieOff
    m_MovieOff : number;
    // public int ScoldSound
    m_ScoldSound : number;
    // public int TeslaCharge
    m_TeslaCharge : number;
    // public int TeslaZap
    m_TeslaZap : number;
    // public int GenericClick
    m_GenericClick : number;
    // public int GenericBeep
    m_GenericBeep : number;
    // public int BuildingDamageSound
    m_BuildingDamageSound : number;
    // also "healing unit" sound, old hospital mode
    // public int HealCrateSound
    m_HealCrateSound : number;
    // public int ChuteSound
    m_ChuteSound : number;
    // public int StopSound
    m_StopSound : number;
    // public int GuardSound
    m_GuardSound : number;
    // public int ScatterSound
    m_ScatterSound : number;
    // TS leftover! Never read from the INI.
    // public int DeploySound
    m_DeploySound : number;
    // public int StormSound
    m_StormSound : number;
    // public TypeList<int> LightningSounds
    m_LightningSounds : TypeList<number>;
    // public int ShellButtonSlideSound
    m_ShellButtonSlideSound : number;
    // public double WallBuildSpeedCoefficient
    m_WallBuildSpeedCoefficient : number;
    // public double ChargeToDrainRatio
    m_ChargeToDrainRatio : number;
    // public double TrackedUphill
    m_TrackedUphill : number;
    // public double TrackedDownhill
    m_TrackedDownhill : number;
    // public double WheeledUphill
    m_WheeledUphill : number;
    // public double WheeledDownhill
    m_WheeledDownhill : number;
    // public int SpotlightMovementRadius
    m_SpotlightMovementRadius : number;
    // public int SpotlightLocationRadius
    m_SpotlightLocationRadius : number;
    // public double SpotlightSpeed
    m_SpotlightSpeed : number;
    // public double SpotlightAcceleration
    m_SpotlightAcceleration : number;
    // public double SpotlightAngle
    m_SpotlightAngle : number;
    // public int SpotlightRadius
    m_SpotlightRadius : number;
    // public int WindDirection
    m_WindDirection : number;
    // public int CameraRange
    m_CameraRange : number;
    // public int FlightLevel
    m_FlightLevel : number;
    // public int ParachuteMaxFallRate
    m_ParachuteMaxFallRate : number;
    // public int NoParachuteMaxFallRate
    m_NoParachuteMaxFallRate : number;
    // public int BuildingDrop
    m_BuildingDrop : number;
    // public TypeList<SmudgeTypeClass *> Scorches
    m_Scorches : TypeList<SmudgeTypeClass>;
    // public TypeList<SmudgeTypeClass *> Scorches1
    m_Scorches1 : TypeList<SmudgeTypeClass>;
    // public TypeList<SmudgeTypeClass *> Scorches2
    m_Scorches2 : TypeList<SmudgeTypeClass>;
    // public TypeList<SmudgeTypeClass *> Scorches3
    m_Scorches3 : TypeList<SmudgeTypeClass>;
    // public TypeList<SmudgeTypeClass *> Scorches4
    m_Scorches4 : TypeList<SmudgeTypeClass>;
    // public TypeList<BuildingTypeClass *> RepairBay
    m_RepairBay : TypeList<BuildingTypeClass>;
    // public BuildingTypeClass * GDIGateOne
    m_GDIGateOne : BuildingTypeClass;
    // public BuildingTypeClass * GDIGateTwo
    m_GDIGateTwo : BuildingTypeClass;
    // public BuildingTypeClass * NodGateOne
    m_NodGateOne : BuildingTypeClass;
    // public BuildingTypeClass * NodGateTwo
    m_NodGateTwo : BuildingTypeClass;
    // public BuildingTypeClass * WallTower
    m_WallTower : BuildingTypeClass;
    // public TypeList<BuildingTypeClass *> Shipyard
    m_Shipyard : TypeList<BuildingTypeClass>;
    // public BuildingTypeClass * GDIPowerPlant
    m_GDIPowerPlant : BuildingTypeClass;
    // public BuildingTypeClass * NodRegularPower
    m_NodRegularPower : BuildingTypeClass;
    // public BuildingTypeClass * NodAdvancedPower
    m_NodAdvancedPower : BuildingTypeClass;
    // public BuildingTypeClass * ThirdPowerPlant
    m_ThirdPowerPlant : BuildingTypeClass;
    // public TypeList<BuildingTypeClass *> BuildConst
    m_BuildConst : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildPower
    m_BuildPower : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildRefinery
    m_BuildRefinery : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildBarracks
    m_BuildBarracks : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildTech
    m_BuildTech : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildWeapons
    m_BuildWeapons : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> AlliedBaseDefenses
    m_AlliedBaseDefenses : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> SovietBaseDefenses
    m_SovietBaseDefenses : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> ThirdBaseDefenses
    m_ThirdBaseDefenses : TypeList<BuildingTypeClass>;
    // public TypeList<int> AIForcePredictionFudge
    m_AIForcePredictionFudge : TypeList<number>;
    // public TypeList<BuildingTypeClass *> BuildDefense
    m_BuildDefense : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildPDefense
    m_BuildPDefense : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildAA
    m_BuildAA : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildHelipad
    m_BuildHelipad : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildRadar
    m_BuildRadar : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> ConcreteWalls
    m_ConcreteWalls : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> NSGates
    m_NSGates : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> EWGates
    m_EWGates : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildNavalYard
    m_BuildNavalYard : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> BuildDummy
    m_BuildDummy : TypeList<BuildingTypeClass>;
    // public TypeList<BuildingTypeClass *> NeutralTechBuildings
    m_NeutralTechBuildings : TypeList<BuildingTypeClass>;
    // public double GDIWallDefense
    m_GDIWallDefense : number;
    // public double GDIWallDefenseCoefficient
    m_GDIWallDefenseCoefficient : number;
    // public double NodBaseDefenseCoefficient
    m_NodBaseDefenseCoefficient : number;
    // public double GDIBaseDefenseCoefficient
    m_GDIBaseDefenseCoefficient : number;
    // public int ComputerBaseDefenseResponse
    m_ComputerBaseDefenseResponse : number;
    // public int MaximumBaseDefenseValue
    m_MaximumBaseDefenseValue : number;
    // public TypeList<UnitTypeClass *> BaseUnit
    m_BaseUnit : TypeList<UnitTypeClass>;
    // public TypeList<UnitTypeClass *> HarvesterUnit
    m_HarvesterUnit : TypeList<UnitTypeClass>;
    // public TypeList<AircraftTypeClass *> PadAircraft
    m_PadAircraft : TypeList<AircraftTypeClass>;
    // public TypeList<AnimTypeClass *> OnFire
    m_OnFire : TypeList<AnimTypeClass>;
    // public TypeList<AnimTypeClass *> TreeFire
    m_TreeFire : TypeList<AnimTypeClass>;
    // public AnimTypeClass * Smoke
    m_Smoke : AnimTypeClass;
    // exists twice
    // public AnimTypeClass * Smoke_
    m_Smoke_ : AnimTypeClass;
    // public AnimTypeClass * MoveFlash
    m_MoveFlash : AnimTypeClass;
    // public AnimTypeClass * BombParachute
    m_BombParachute : AnimTypeClass;
    // public AnimTypeClass * Parachute
    m_Parachute : AnimTypeClass;
    // public TypeList<AnimTypeClass *> SplashList
    m_SplashList : TypeList<AnimTypeClass>;
    // public AnimTypeClass * SmallFire
    m_SmallFire : AnimTypeClass;
    // public AnimTypeClass * LargeFire
    m_LargeFire : AnimTypeClass;
    // public InfantryTypeClass * Paratrooper
    m_Paratrooper : InfantryTypeClass;
    // public int EliteFlashTimer
    m_EliteFlashTimer : number;
    // public int ChronoDelay
    m_ChronoDelay : number;
    // public int ChronoReinfDelay
    m_ChronoReinfDelay : number;
    // public int ChronoDistanceFactor
    m_ChronoDistanceFactor : number;
    // public bool ChronoTrigger
    m_ChronoTrigger : boolean;
    // public int ChronoMinimumDelay
    m_ChronoMinimumDelay : number;
    // public int ChronoRangeMinimum
    m_ChronoRangeMinimum : number;
    // public TypeList<InfantryTypeClass *> AmerParaDropInf
    m_AmerParaDropInf : TypeList<InfantryTypeClass>;
    // public TypeList<int> AmerParaDropNum
    m_AmerParaDropNum : TypeList<number>;
    // public TypeList<InfantryTypeClass *> AllyParaDropInf
    m_AllyParaDropInf : TypeList<InfantryTypeClass>;
    // public TypeList<int> AllyParaDropNum
    m_AllyParaDropNum : TypeList<number>;
    // public TypeList<InfantryTypeClass *> SovParaDropInf
    m_SovParaDropInf : TypeList<InfantryTypeClass>;
    // public TypeList<int> SovParaDropNum
    m_SovParaDropNum : TypeList<number>;
    // public TypeList<InfantryTypeClass *> YuriParaDropInf
    m_YuriParaDropInf : TypeList<InfantryTypeClass>;
    // public TypeList<int> YuriParaDropNum
    m_YuriParaDropNum : TypeList<number>;
    // public TypeList<InfantryTypeClass *> AnimToInfantry
    m_AnimToInfantry : TypeList<InfantryTypeClass>;
    // public TypeList<InfantryTypeClass *> SecretInfantry
    m_SecretInfantry : TypeList<InfantryTypeClass>;
    // public TypeList<UnitTypeClass *> SecretUnits
    m_SecretUnits : TypeList<UnitTypeClass>;
    // public TypeList<BuildingTypeClass *> SecretBuildings
    m_SecretBuildings : TypeList<BuildingTypeClass>;
    // public int SecretSum
    m_SecretSum : number;
    // public InfantryTypeClass * AlliedDisguise
    m_AlliedDisguise : InfantryTypeClass;
    // public InfantryTypeClass * SovietDisguise
    m_SovietDisguise : InfantryTypeClass;
    // public InfantryTypeClass * ThirdDisguise
    m_ThirdDisguise : InfantryTypeClass;
    // public int SpyPowerBlackout
    m_SpyPowerBlackout : number;
    // public float SpyMoneyStealPercent
    m_SpyMoneyStealPercent : number;
    // public bool AttackCursorOnDisguise
    m_AttackCursorOnDisguise : boolean;
    // public float AIMinorSuperReadyPercent
    m_AIMinorSuperReadyPercent : number;
    // public int AISafeDistance
    m_AISafeDistance : number;
    // public int HarvesterTooFarDistance
    m_HarvesterTooFarDistance : number;
    // public int ChronoHarvTooFarDistance
    m_ChronoHarvTooFarDistance : number;
    // public TypeList<int> AlliedBaseDefenseCounts
    m_AlliedBaseDefenseCounts : TypeList<number>;
    // public TypeList<int> SovietBaseDefenseCounts
    m_SovietBaseDefenseCounts : TypeList<number>;
    // public TypeList<int> ThirdBaseDefenseCounts
    m_ThirdBaseDefenseCounts : TypeList<number>;
    // public TypeList<int> AIPickWallDefensePercent
    m_AIPickWallDefensePercent : TypeList<number>;
    // public int AIRestrictReplaceTime
    m_AIRestrictReplaceTime : number;
    // public int ThreatPerOccupant
    m_ThreatPerOccupant : number;
    // public int ApproachTargetResetMultiplier
    m_ApproachTargetResetMultiplier : number;
    // public int CampaignMoneyDeltaEasy
    m_CampaignMoneyDeltaEasy : number;
    // public int CampaignMoneyDeltaHard
    m_CampaignMoneyDeltaHard : number;
    // public int GuardAreaTargetingDelay
    m_GuardAreaTargetingDelay : number;
    // public int NormalTargetingDelay
    m_NormalTargetingDelay : number;
    // public int AINavalYardAdjacency
    m_AINavalYardAdjacency : number;
    // public TypeList<int> DisabledDisguiseDetectionPercent
    m_DisabledDisguiseDetectionPercent : TypeList<number>;
    // public TypeList<int> AIAutoDeployFrameDelay
    m_AIAutoDeployFrameDelay : TypeList<number>;
    // public int MaximumBuildingPlacementFailures
    m_MaximumBuildingPlacementFailures : number;
    // public TypeList<int> AICaptureNormal
    m_AICaptureNormal : TypeList<number>;
    // public TypeList<int> AICaptureWounded
    m_AICaptureWounded : TypeList<number>;
    // public TypeList<int> AICaptureLowPower
    m_AICaptureLowPower : TypeList<number>;
    // public TypeList<int> AICaptureLowMoney
    m_AICaptureLowMoney : TypeList<number>;
    // public int AICaptureLowMoneyMark
    m_AICaptureLowMoneyMark : number;
    // public int AICaptureWoundedMark
    m_AICaptureWoundedMark : number;
    // public TypeList<int> AISuperDefenseProbability
    m_AISuperDefenseProbability : TypeList<number>;
    // public int AISuperDefenseFrames
    m_AISuperDefenseFrames : number;
    // public float AISuperDefenseDistance
    m_AISuperDefenseDistance : number;
    // public TypeList<int> OverloadCount
    m_OverloadCount : TypeList<number>;
    // public TypeList<int> OverloadDamage
    m_OverloadDamage : TypeList<number>;
    // public TypeList<int> OverloadFrames
    m_OverloadFrames : TypeList<number>;
    // public float PurifierBonus
    m_PurifierBonus : number;
    // public float OccupyDamageMultiplier
    m_OccupyDamageMultiplier : number;
    // public float OccupyROFMultiplier
    m_OccupyROFMultiplier : number;
    // public int OccupyWeaponRange
    m_OccupyWeaponRange : number;
    // public int BunkerDamageMultiplier
    m_BunkerDamageMultiplier : number;
    // public float BunkerROFMultiplier
    m_BunkerROFMultiplier : number;
    // public int BunkerWeaponRangeBonus
    m_BunkerWeaponRangeBonus : number;
    // public float OpenToppedDamageMultiplier
    m_OpenToppedDamageMultiplier : number;
    // public int OpenToppedRangeBonus
    m_OpenToppedRangeBonus : number;
    // public int OpenToppedWarpDistance
    m_OpenToppedWarpDistance : number;
    // public float FallingDamageMultiplier
    m_FallingDamageMultiplier : number;
    // public bool CurrentStrengthDamage
    m_CurrentStrengthDamage : boolean;
    // public InfantryTypeClass * Technician
    m_Technician : InfantryTypeClass;
    // public InfantryTypeClass * Engineer
    m_Engineer : InfantryTypeClass;
    // public InfantryTypeClass * Pilot
    m_Pilot : InfantryTypeClass;
    // public InfantryTypeClass * AlliedCrew
    m_AlliedCrew : InfantryTypeClass;
    // public InfantryTypeClass * SovietCrew
    m_SovietCrew : InfantryTypeClass;
    // public InfantryTypeClass * ThirdCrew
    m_ThirdCrew : InfantryTypeClass;
    // public WarheadTypeClass * FlameDamage
    m_FlameDamage : WarheadTypeClass;
    // public WarheadTypeClass * FlameDamage2
    m_FlameDamage2 : WarheadTypeClass;
    // public WarheadTypeClass * NukeWarhead
    m_NukeWarhead : WarheadTypeClass;
    // public BulletTypeClass * NukeProjectile
    m_NukeProjectile : BulletTypeClass;
    // public BulletTypeClass * NukeDown
    m_NukeDown : BulletTypeClass;
    // public WarheadTypeClass * MutateWarhead
    m_MutateWarhead : WarheadTypeClass;
    // public WarheadTypeClass * MutateExplosionWarhead
    m_MutateExplosionWarhead : WarheadTypeClass;
    // public WarheadTypeClass * EMPulseWarhead
    m_EMPulseWarhead : WarheadTypeClass;
    // public WarheadTypeClass * EMPulseProjectile
    m_EMPulseProjectile : WarheadTypeClass;
    // public WarheadTypeClass * C4Warhead
    m_C4Warhead : WarheadTypeClass;
    // public WarheadTypeClass * CrushWarhead
    m_CrushWarhead : WarheadTypeClass;
    // public WarheadTypeClass * V3Warhead
    m_V3Warhead : WarheadTypeClass;
    // public WarheadTypeClass * DMislWarhead
    m_DMislWarhead : WarheadTypeClass;
    // public WarheadTypeClass * V3EliteWarhead
    m_V3EliteWarhead : WarheadTypeClass;
    // public WarheadTypeClass * DMislEliteWarhead
    m_DMislEliteWarhead : WarheadTypeClass;
    // public WarheadTypeClass * CMislWarhead
    m_CMislWarhead : WarheadTypeClass;
    // public WarheadTypeClass * CMislEliteWarhead
    m_CMislEliteWarhead : WarheadTypeClass;
    // public WarheadTypeClass * IvanWarhead
    m_IvanWarhead : WarheadTypeClass;
    // public int IvanDamage
    m_IvanDamage : number;
    // public int IvanTimedDelay
    m_IvanTimedDelay : number;
    // public bool CanDetonateTimeBomb
    m_CanDetonateTimeBomb : boolean;
    // public bool CanDetonateDeathBomb
    m_CanDetonateDeathBomb : boolean;
    // public int IvanIconFlickerRate
    m_IvanIconFlickerRate : number;
    // public WeaponTypeClass * DeathWeapon
    m_DeathWeapon : WeaponTypeClass;
    // public SHPStruct * BOMBCURS_SHP
    m_BOMBCURS_SHP : any;
    // public SHPStruct * CHRONOSK_SHP
    m_CHRONOSK_SHP : any;
    // public int IronCurtainDuration
    m_IronCurtainDuration : number;
    // public int PsychicRevealRadius
    m_PsychicRevealRadius : number;
    // public WarheadTypeClass * IonCannonWarhead
    m_IonCannonWarhead : WarheadTypeClass;
    // public TerrainTypeClass * VeinholeTypeClass
    m_VeinholeTypeClass : TerrainTypeClass;
    // public TypeList<TerrainTypeClass *> DefaultMirageDisguises
    m_DefaultMirageDisguises : TypeList<TerrainTypeClass>;
    // public int InfantryBlinkDisguiseTime
    m_InfantryBlinkDisguiseTime : number;
    // public ParticleSystemTypeClass * DefaultLargeGreySmokeSystem
    m_DefaultLargeGreySmokeSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultSmallGreySmokeSystem
    m_DefaultSmallGreySmokeSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultSparkSystem
    m_DefaultSparkSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultLargeRedSmokeSystem
    m_DefaultLargeRedSmokeSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultSmallRedSmokeSystem
    m_DefaultSmallRedSmokeSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultDebrisSmokeSystem
    m_DefaultDebrisSmokeSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultFireStreamSystem
    m_DefaultFireStreamSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultTestParticleSystem
    m_DefaultTestParticleSystem : ParticleSystemTypeClass;
    // public ParticleSystemTypeClass * DefaultRepairParticleSystem
    m_DefaultRepairParticleSystem : ParticleSystemTypeClass;
    // public double MyEffectivenessCoefficientDefault
    m_MyEffectivenessCoefficientDefault : number;
    // public double TargetEffectivenessCoefficientDefault
    m_TargetEffectivenessCoefficientDefault : number;
    // public double TargetSpecialThreatCoefficientDefault
    m_TargetSpecialThreatCoefficientDefault : number;
    // public double TargetStrengthCoefficientDefault
    m_TargetStrengthCoefficientDefault : number;
    // public double TargetDistanceCoefficientDefault
    m_TargetDistanceCoefficientDefault : number;
    // public double DumbMyEffectivenessCoefficient
    m_DumbMyEffectivenessCoefficient : number;
    // public double DumbTargetEffectivenessCoefficient
    m_DumbTargetEffectivenessCoefficient : number;
    // public double DumbTargetSpecialThreatCoefficient
    m_DumbTargetSpecialThreatCoefficient : number;
    // public double DumbTargetStrengthCoefficient
    m_DumbTargetStrengthCoefficient : number;
    // public double DumbTargetDistanceCoefficient
    m_DumbTargetDistanceCoefficient : number;
    // public double EnemyHouseThreatBonus
    m_EnemyHouseThreatBonus : number;
    // public double TurboBoost
    m_TurboBoost : number;
    // public double AttackInterval
    m_AttackInterval : number;
    // public double AttackDelay
    m_AttackDelay : number;
    // public double PowerEmergency
    m_PowerEmergency : number;
    // public double AirstripRatio
    m_AirstripRatio : number;
    // public int AirstripLimit
    m_AirstripLimit : number;
    // public double HelipadRatio
    m_HelipadRatio : number;
    // public int HelipadLimit
    m_HelipadLimit : number;
    // public double TeslaRatio
    m_TeslaRatio : number;
    // public int TeslaLimit
    m_TeslaLimit : number;
    // public double AARatio
    m_AARatio : number;
    // public int AALimit
    m_AALimit : number;
    // public double DefenseRatio
    m_DefenseRatio : number;
    // public int DefenseLimit
    m_DefenseLimit : number;
    // public double WarRatio
    m_WarRatio : number;
    // public int WarLimit
    m_WarLimit : number;
    // public double BarracksRatio
    m_BarracksRatio : number;
    // public int BarracksLimit
    m_BarracksLimit : number;
    // public int RefineryLimit
    m_RefineryLimit : number;
    // public double RefineryRatio
    m_RefineryRatio : number;
    // public int BaseSizeAdd
    m_BaseSizeAdd : number;
    // public int PowerSurplus
    m_PowerSurplus : number;
    // public int InfantryReserve
    m_InfantryReserve : number;
    // public int InfantryBaseMult
    m_InfantryBaseMult : number;
    // public int SoloCrateMoney
    m_SoloCrateMoney : number;
    // public int TreeStrength
    m_TreeStrength : number;
    // public UnitTypeClass * UnitCrateType
    m_UnitCrateType : UnitTypeClass;
    // public double PatrolScan
    m_PatrolScan : number;
    // public TypeList<int> TeamDelays
    m_TeamDelays : TypeList<number>;
    // public TypeList<int> AIHateDelays
    m_AIHateDelays : TypeList<number>;
    // public int DissolveUnfilledTeamDelay
    m_DissolveUnfilledTeamDelay : number;
    // public TypeList<int> AIIonCannonConYardValue
    m_AIIonCannonConYardValue : TypeList<number>;
    // public TypeList<int> AIIonCannonWarFactoryValue
    m_AIIonCannonWarFactoryValue : TypeList<number>;
    // public TypeList<int> AIIonCannonPowerValue
    m_AIIonCannonPowerValue : TypeList<number>;
    // public TypeList<int> AIIonCannonTechCenterValue
    m_AIIonCannonTechCenterValue : TypeList<number>;
    // public TypeList<int> AIIonCannonEngineerValue
    m_AIIonCannonEngineerValue : TypeList<number>;
    // public TypeList<int> AIIonCannonThiefValue
    m_AIIonCannonThiefValue : TypeList<number>;
    // public TypeList<int> AIIonCannonHarvesterValue
    m_AIIonCannonHarvesterValue : TypeList<number>;
    // public TypeList<int> AIIonCannonMCVValue
    m_AIIonCannonMCVValue : TypeList<number>;
    // public TypeList<int> AIIonCannonAPCValue
    m_AIIonCannonAPCValue : TypeList<number>;
    // public TypeList<int> AIIonCannonBaseDefenseValue
    m_AIIonCannonBaseDefenseValue : TypeList<number>;
    // public TypeList<int> AIIonCannonPlugValue
    m_AIIonCannonPlugValue : TypeList<number>;
    // public TypeList<int> AIIonCannonHelipadValue
    m_AIIonCannonHelipadValue : TypeList<number>;
    // public TypeList<int> AIIonCannonTempleValue
    m_AIIonCannonTempleValue : TypeList<number>;
    // public int AIAlternateProductionCreditCutoff
    m_AIAlternateProductionCreditCutoff : number;
    // public TypeList<int> MultiplayerAICM
    m_MultiplayerAICM : TypeList<number>;
    // public TypeList<int> AIVirtualPurifiers
    m_AIVirtualPurifiers : TypeList<number>;
    // public TypeList<int> AISlaveMinerNumber
    m_AISlaveMinerNumber : TypeList<number>;
    // public TypeList<int> HarvestersPerRefinery
    m_HarvestersPerRefinery : TypeList<number>;
    // public TypeList<int> AIExtraRefineries
    m_AIExtraRefineries : TypeList<number>;
    // public TypeList<int> MinimumAIDefensiveTeams
    m_MinimumAIDefensiveTeams : TypeList<number>;
    // public TypeList<int> MaximumAIDefensiveTeams
    m_MaximumAIDefensiveTeams : TypeList<number>;
    // public TypeList<int> TotalAITeamCap
    m_TotalAITeamCap : TypeList<number>;
    // public double AIUseTurbineUpgradeProbability
    m_AIUseTurbineUpgradeProbability : number;
    // public TypeList<int> FillEarliestTeamProbability
    m_FillEarliestTeamProbability : TypeList<number>;
    // public double CloakDelay
    m_CloakDelay : number;
    // public double GameSpeedBias
    m_GameSpeedBias : number;
    // public double BaseBias
    m_BaseBias : number;
    // public double ExpSpread
    m_ExpSpread : number;
    // public int FireSupress
    m_FireSupress : number;
    // public int MaxIQLevels
    m_MaxIQLevels : number;
    // public int SuperWeapons
    m_SuperWeapons : number;
    // public int Production
    m_Production : number;
    // public int GuardArea
    m_GuardArea : number;
    // public int RepairSell
    m_RepairSell : number;
    // public int AutoCrush
    m_AutoCrush : number;
    // public int Scatter
    m_Scatter : number;
    // public int ContentScan
    m_ContentScan : number;
    // public int Aircraft
    m_Aircraft : number;
    // public int Harvester
    m_Harvester : number;
    // public int SellBack
    m_SellBack : number;
    // public int AIBaseSpacing
    m_AIBaseSpacing : number;
    // public Powerup SilverCrate
    m_SilverCrate : Powerup;
    // public Powerup WoodCrate
    m_WoodCrate : Powerup;
    // public Powerup WaterCrate
    m_WaterCrate : Powerup;
    // public int CrateMinimum
    m_CrateMinimum : number;
    // public int CrateMaximum
    m_CrateMaximum : number;
    // defaults to 0x2000
    // public int unknown_int_1478
    m_unknown_int_1478 : number;
    // public AnimTypeClass * DropZoneAnim
    m_DropZoneAnim : AnimTypeClass;
    // public int MinMoney
    m_MinMoney : number;
    // public int Money
    m_Money : number;
    // public int MaxMoney
    m_MaxMoney : number;
    // public int MoneyIncrement
    m_MoneyIncrement : number;
    // public int MinUnitCount
    m_MinUnitCount : number;
    // public int UnitCount
    m_UnitCount : number;
    // public int MaxUnitCount
    m_MaxUnitCount : number;
    // public int TechLevel
    m_TechLevel : number;
    // public int GameSpeed
    m_GameSpeed : number;
    // public int AIDifficultyStruct
    m_AIDifficultyStruct : number;
    // public int AIPlayers
    m_AIPlayers : number;
    // public bool BridgeDestruction
    m_BridgeDestruction : boolean;
    // public bool ShadowGrow
    m_ShadowGrow : boolean;
    // public bool Shroud
    m_Shroud : boolean;
    // public bool Bases
    m_Bases : boolean;
    // public bool TiberiumGrows
    m_TiberiumGrows : boolean;
    // public bool Crates
    m_Crates : boolean;
    // public bool CaptureTheFlag
    m_CaptureTheFlag : boolean;
    // public bool HarvesterTruce
    m_HarvesterTruce : boolean;
    // public bool MultiEngineer
    m_MultiEngineer : boolean;
    // public bool AlliesAllowed
    m_AlliesAllowed : boolean;
    // public bool ShortGame
    m_ShortGame : boolean;
    // public bool FogOfWar
    m_FogOfWar : boolean;
    // public bool MCVRedeploys
    m_MCVRedeploys : boolean;
    // public bool SuperWeaponsAllowed
    m_SuperWeaponsAllowed : boolean;
    // public bool BuildOffAlly
    m_BuildOffAlly : boolean;
    // public bool AllyChangeAllowed
    m_AllyChangeAllowed : boolean;
    // public int DropZoneRadius
    m_DropZoneRadius : number;
    // public double MessageDelay
    m_MessageDelay : number;
    // public double SavourDelay
    m_SavourDelay : number;
    // public int Players
    m_Players : number;
    // public double BaseDefenseDelay
    m_BaseDefenseDelay : number;
    // public int SuspendPriority
    m_SuspendPriority : number;
    // public double SuspendDelay
    m_SuspendDelay : number;
    // public double SurvivorRate
    m_SurvivorRate : number;
    // public int AlliedSurvivorDivisor
    m_AlliedSurvivorDivisor : number;
    // public int SovietSurvivorDivisor
    m_SovietSurvivorDivisor : number;
    // public int ThirdSurvivorDivisor
    m_ThirdSurvivorDivisor : number;
    // public double ReloadRate
    m_ReloadRate : number;
    // public double AutocreateTime
    m_AutocreateTime : number;
    // public double BuildupTime
    m_BuildupTime : number;
    // public int HarvesterLoadRate
    m_HarvesterLoadRate : number;
    // public double HarvesterDumpRate
    m_HarvesterDumpRate : number;
    // public int AtomDamage
    m_AtomDamage : number;
    // public DifficultyStruct Easy
    m_Easy : DifficultyStruct;
    // public DifficultyStruct Normal
    m_Normal : DifficultyStruct;
    // public DifficultyStruct Difficult
    m_Difficult : DifficultyStruct;
    // public unsigned long[4] align_1628
    m_align_1628 : number;
    // public double GrowthRate
    m_GrowthRate : number;
    // public double ShroudRate
    m_ShroudRate : number;
    // public double FogRate
    m_FogRate : number;
    // public double IceGrowthRate
    m_IceGrowthRate : number;
    // public double VeinGrowthRate
    m_VeinGrowthRate : number;
    // public int IceSolidifyFrameTime
    m_IceSolidifyFrameTime : number;
    // public double AmbientChangeRate
    m_AmbientChangeRate : number;
    // public double AmbientChangeStep
    m_AmbientChangeStep : number;
    // public double CrateRegen
    m_CrateRegen : number;
    // public double TimerWarning
    m_TimerWarning : number;
    // public int TiberiumTransmogrify
    m_TiberiumTransmogrify : number;
    // 2.6875
    // public double unknown_double_1690
    m_unknown_double_1690 : number;
    // 2.3125
    // public double unknown_double_1698
    m_unknown_double_1698 : number;
    // 2.5625
    // public double unknown_double_16A0
    m_unknown_double_16A0 : number;
    // public double SpeakDelay
    m_SpeakDelay : number;
    // public double DamageDelay
    m_DamageDelay : number;
    // public int Gravity
    m_Gravity : number;
    // public int LeptonsPerSightIncrease
    m_LeptonsPerSightIncrease : number;
    // public int Incoming
    m_Incoming : number;
    // public int MinDamage
    m_MinDamage : number;
    // public int MaxDamage
    m_MaxDamage : number;
    // public int RepairStep
    m_RepairStep : number;
    // public double RepairPercent
    m_RepairPercent : number;
    // public int IRepairStep
    m_IRepairStep : number;
    // public double RepairRate
    m_RepairRate : number;
    // public double URepairRate
    m_URepairRate : number;
    // public double IRepairRate
    m_IRepairRate : number;
    // 1.875
    // public double unknown_double_16F8
    m_unknown_double_16F8 : number;
    // public double ConditionYellow
    m_ConditionYellow : number;
    // public double ConditionRed
    m_ConditionRed : number;
    // public double IdleActionFrequency
    m_IdleActionFrequency : number;
    // public int CloseEnough
    m_CloseEnough : number;
    // public int Stray
    m_Stray : number;
    // public int RelaxedStray
    m_RelaxedStray : number;
    // public int GuardModeStray
    m_GuardModeStray : number;
    // public int Crush
    m_Crush : number;
    // public int CrateRadius
    m_CrateRadius : number;
    // public int HomingScatter
    m_HomingScatter : number;
    // public int BallisticScatter
    m_BallisticScatter : number;
    // public double RefundPercent
    m_RefundPercent : number;
    // public int BridgeStrength
    m_BridgeStrength : number;
    // public double BuildSpeed
    m_BuildSpeed : number;
    // public double C4Delay
    m_C4Delay : number;
    // public int CreditReserve
    m_CreditReserve : number;
    // public double PathDelay
    m_PathDelay : number;
    // public int BlockagePathDelay
    m_BlockagePathDelay : number;
    // public double MovieTime
    m_MovieTime : number;
    // public int TiberiumShortScan
    m_TiberiumShortScan : number;
    // public int TiberiumLongScan
    m_TiberiumLongScan : number;
    // public int SlaveMinerShortScan
    m_SlaveMinerShortScan : number;
    // public int SlaveMinerSlaveScan
    m_SlaveMinerSlaveScan : number;
    // public int SlaveMinerLongScan
    m_SlaveMinerLongScan : number;
    // public int SlaveMinerScanCorrection
    m_SlaveMinerScanCorrection : number;
    // public int SlaveMinerKickFrameDelay
    m_SlaveMinerKickFrameDelay : number;
    // public int LightningDeferment
    m_LightningDeferment : number;
    // public int LightningDamage
    m_LightningDamage : number;
    // public int LightningStormDuration
    m_LightningStormDuration : number;
    // public int LightningHitDelay
    m_LightningHitDelay : number;
    // public int LightningScatterDelay
    m_LightningScatterDelay : number;
    // public int LightningCellSpread
    m_LightningCellSpread : number;
    // public int LightningSeparation
    m_LightningSeparation : number;
    // public bool LightningPrintText
    m_LightningPrintText : boolean;
    // public WarheadTypeClass * LightningWarhead
    m_LightningWarhead : WarheadTypeClass;
    // public int ForceShieldRadius
    m_ForceShieldRadius : number;
    // public int ForceShieldDuration
    m_ForceShieldDuration : number;
    // public int ForceShieldBlackoutDuration
    m_ForceShieldBlackoutDuration : number;
    // public int ForceShieldPlayFadeSoundTime
    m_ForceShieldPlayFadeSoundTime : number;
    // public bool MutateExplosion
    m_MutateExplosion : boolean;
    // public int CollapseChance
    m_CollapseChance : number;
    // public int WeedCapacity
    m_WeedCapacity : number;
    // public float ExtraUnitLight
    m_ExtraUnitLight : number;
    // public float ExtraInfantryLight
    m_ExtraInfantryLight : number;
    // public float ExtraAircraftLight
    m_ExtraAircraftLight : number;
    // public bool Paranoid
    m_Paranoid : boolean;
    // public bool CurleyShuffle
    m_CurleyShuffle : boolean;
    // public bool BlendedFog
    m_BlendedFog : boolean;
    // public bool CompEasyBonus
    m_CompEasyBonus : boolean;
    // public bool FineDiffControl
    m_FineDiffControl : boolean;
    // public bool TiberiumExplosive
    m_TiberiumExplosive : boolean;
    // public bool EnemyHealth
    m_EnemyHealth : boolean;
    // public bool AllyReveal
    m_AllyReveal : boolean;
    // public bool SeparateAircraft
    m_SeparateAircraft : boolean;
    // public bool TreeTargeting
    m_TreeTargeting : boolean;
    // public bool NamedCivilians
    m_NamedCivilians : boolean;
    // public bool PlayerAutoCrush
    m_PlayerAutoCrush : boolean;
    // public bool PlayerReturnFire
    m_PlayerReturnFire : boolean;
    // public bool PlayerScatter
    m_PlayerScatter : boolean;
    // public bool RevealByHeight
    m_RevealByHeight : boolean;
    // public bool AllowShroudedSubteranneanMoves
    m_AllowShroudedSubteranneanMoves : boolean;
    // public bool ShroudGrow
    m_ShroudGrow : boolean;
    // public bool NodAIBuildsWalls
    m_NodAIBuildsWalls : boolean;
    // public bool AIBuildsWalls
    m_AIBuildsWalls : boolean;
    // public bool UseMinDefenseRule
    m_UseMinDefenseRule : boolean;
    // public AnimTypeClass * EMPulseSparkles
    m_EMPulseSparkles : AnimTypeClass;
    // public float EngineerCaptureLevel
    m_EngineerCaptureLevel : number;
    // public float EngineerCaptureLevel_
    m_EngineerCaptureLevel_ : number;
    // public float TalkBubbleTime
    m_TalkBubbleTime : number;
    // public int RadDurationMultiple
    m_RadDurationMultiple : number;
    // public int RadApplicationDelay
    m_RadApplicationDelay : number;
    // public int RadLevelMax
    m_RadLevelMax : number;
    // public int RadLevelDelay
    m_RadLevelDelay : number;
    // public int RadLightDelay
    m_RadLightDelay : number;
    // public double RadLevelFactor
    m_RadLevelFactor : number;
    // public double RadLightFactor
    m_RadLightFactor : number;
    // public double RadTintFactor
    m_RadTintFactor : number;
    // public ColorStruct RadColor
    m_RadColor : ColorStruct;
    // public WarheadTypeClass * RadSiteWarhead
    m_RadSiteWarhead : WarheadTypeClass;
    // public int ElevationIncrement
    m_ElevationIncrement : number;
    // public double ElevationIncrementBonus
    m_ElevationIncrementBonus : number;
    // public double ElevationBonusCap
    m_ElevationBonusCap : number;
    // public bool AlliedWallTransparency
    m_AlliedWallTransparency : boolean;
    // public double WallPenetratorThreshold
    m_WallPenetratorThreshold : number;
    // public ColorStruct LocalRadarColor
    m_LocalRadarColor : ColorStruct;
    // public ColorStruct LineTrailColorOverride
    m_LineTrailColorOverride : ColorStruct;
    // public ColorStruct ChronoBeamColor
    m_ChronoBeamColor : ColorStruct;
    // public ColorStruct MagnaBeamColor
    m_MagnaBeamColor : ColorStruct;
    // public int OreTwinkleChance
    m_OreTwinkleChance : number;
    // public AnimTypeClass * OreTwinkle
    m_OreTwinkle : AnimTypeClass;
    // public ColorStruct[16] ColorAdd
    m_ColorAdd : ColorStruct;
    // public int LaserTargetColor
    m_LaserTargetColor : number;
    // public int IronCurtainColor
    m_IronCurtainColor : number;
    // public int BerserkColor
    m_BerserkColor : number;
    // public int ForceShieldColor
    m_ForceShieldColor : number;
    // public float DirectRockingCoefficient
    m_DirectRockingCoefficient : number;
    // public float FallBackCoefficient
    m_FallBackCoefficient : number;
}
// forward declarations
// LocomotionClass
class LocomotionClass
{
    // Constructors
    // public LocomotionClass()
    constructor();
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID) = 0
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long IsDirty()
    IsDirty() : number;
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // public virtual long GetSizeMax(_ULARGE_INTEGER * pcbSize)
    GetSizeMax(pcbSize_0 : any | any) : number;
    // public virtual int Size() = 0
    Size() : number;
    // ILocomotion
    // virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) { JMP_STD(0x4D0510); }
    // virtual ULONG __stdcall AddRef() { JMP_STD(0x4D0520); }
    // virtual ULONG __stdcall Release() { JMP_STD(0x4D0530); }
    // public virtual long Link_To_Object(void * pointer)
    Link_To_Object(pointer_0 : void | any) : number;
    // Sees if object is moving.
    // public virtual bool Is_Moving()
    Is_Moving() : boolean;
    // Fetches destination coordinate.
    // public virtual CoordStruct Destination()
    Destination() : CoordStruct;
    // Fetches immediate (next cell) destination coordinate.
    // public virtual CoordStruct Head_To_Coord()
    Head_To_Coord() : CoordStruct;
    // Determine if specific cell can be entered.
    // public virtual Move Can_Enter_Cell(CellStruct cell)
    Can_Enter_Cell(cell_0 : CellStruct | any) : Move;
    // Should object cast a shadow?
    // public virtual bool Is_To_Have_Shadow()
    Is_To_Have_Shadow() : boolean;
    // Fetch voxel draw matrix.
    // public virtual Matrix3D Draw_Matrix(VoxelIndexKey * pIndex)
    Draw_Matrix(pIndex_0 : any | any) : Matrix3D;
    // Fetch shadow draw matrix.
    // public virtual Matrix3D Shadow_Matrix(VoxelIndexKey * pIndex)
    Shadow_Matrix(pIndex_0 : any | any) : Matrix3D;
    // Draw point center location.
    // public virtual Point2D Draw_Point()
    Draw_Point() : Point2D;
    // Shadow draw point center location.
    // public virtual Point2D Shadow_Point()
    Shadow_Point() : Point2D;
    // Visual character for drawing.
    // public virtual VisualType Visual_Character(bool raw)
    Visual_Character(raw_0 : boolean | any) : VisualType;
    // Z adjust control value.
    // public virtual int Z_Adjust()
    Z_Adjust() : number;
    // Z gradient control value.
    // public virtual ZGradient Z_Gradient()
    Z_Gradient() : ZGradient;
    // Process movement of object.]
    // public virtual bool Process()
    Process() : boolean;
    // Instruct to move to location specified.
    // public virtual void Move_To(CoordStruct to)
    Move_To(to_0 : CoordStruct | any) : void;
    // Stop moving at first opportunity.
    // public virtual void Stop_Moving()
    Stop_Moving() : void;
    // Try to face direction specified.
    // public virtual void Do_Turn(DirStruct coord)
    Do_Turn(coord_0 : DirStruct | any) : void;
    // Object is appearing in the world.
    // public virtual void Unlimbo()
    Unlimbo() : void;
    // Special tilting AI function.
    // public virtual void Tilt_Pitch_AI()
    Tilt_Pitch_AI() : void;
    // Locomotor becomes powered.
    // public virtual bool Power_On()
    Power_On() : boolean;
    // Locomotor loses power.
    // public virtual bool Power_Off()
    Power_Off() : boolean;
    // Is locomotor powered?
    // public virtual bool Is_Powered()
    Is_Powered() : boolean;
    // Is locomotor sensitive to ion storms?
    // public virtual bool Is_Ion_Sensitive()
    Is_Ion_Sensitive() : boolean;
    // Push object in direction specified.
    // public virtual bool Push(DirStruct dir)
    Push(dir_0 : DirStruct | any) : boolean;
    // Shove object (with spin) in direction specified.
    // public virtual bool Shove(DirStruct dir)
    Shove(dir_0 : DirStruct | any) : boolean;
    // Force drive track -- special case only.
    // public virtual void Force_Track(int track, CoordStruct coord)
    Force_Track(track_0 : number | any, coord_1 : CoordStruct | any) : void;
    // What display layer is it located in.
    // public virtual Layer In_Which_Layer() = 0
    In_Which_Layer() : Layer;
    // Don't use this function.
    // public virtual void Force_Immediate_Destination(CoordStruct coord)
    Force_Immediate_Destination(coord_0 : CoordStruct | any) : void;
    // Force a voxel unit to a given slope. Used in cratering.
    // public virtual void Force_New_Slope(int ramp)
    Force_New_Slope(ramp_0 : number | any) : void;
    // Is it actually moving across the ground this very second?
    // public virtual bool Is_Moving_Now()
    Is_Moving_Now() : boolean;
    // Actual current speed of object expressed as leptons per game frame.
    // public virtual int Apparent_Speed()
    Apparent_Speed() : number;
    // Special drawing feedback code (locomotor specific meaning)
    // public virtual int Drawing_Code()
    Drawing_Code() : number;
    // Queries if any locomotor specific state prevents the object from firing.
    // public virtual FireError Can_Fire()
    Can_Fire() : FireError;
    // Queries the general state of the locomotor.
    // public virtual int Get_Status()
    Get_Status() : number;
    // Forces a hunter seeker droid to find a target.
    // public virtual void Acquire_Hunter_Seeker_Target()
    Acquire_Hunter_Seeker_Target() : void;
    // Is this object surfacing?
    // public virtual bool Is_Surfacing()
    Is_Surfacing() : boolean;
    // Lifts all occupation bits associated with the object off the map
    // public virtual void Mark_All_Occupation_Bits(MarkType mark)
    Mark_All_Occupation_Bits(mark_0 : MarkType | any) : void;
    // Is this object in the process of moving into this coord.
    // public virtual bool Is_Moving_Here(CoordStruct to)
    Is_Moving_Here(to_0 : CoordStruct | any) : boolean;
    // Will this object jump tracks?
    // public virtual bool Will_Jump_Tracks()
    Will_Jump_Tracks() : boolean;
    // Infantry moving query function.
    // public virtual bool Is_Really_Moving_Now()
    Is_Really_Moving_Now() : boolean;
    // Falsifies the IsReallyMoving flag in WalkLocomotionClass.
    // public virtual void Stop_Movement_Animation()
    Stop_Movement_Animation() : void;
    // Object is disappearing from the world.
    // Was added post TLB generation.
    // public virtual void Limbo()
    Limbo() : void;
    // Locks the locomotor from being deleted.
    // public virtual void Lock()
    Lock() : void;
    // Unlocks the locomotor from being deleted.
    // public virtual void Unlock()
    Unlock() : void;
    // Queries internal variables.
    // public virtual int Get_Track_Number()
    Get_Track_Number() : number;
    // Queries internal variables.
    // public virtual int Get_Track_Index()
    Get_Track_Index() : number;
    // Queries internal variables.
    // public virtual int Get_Speed_Accum()
    Get_Speed_Accum() : number;
    // Non virtuals
    // public static long TryPiggyback(IPiggyback * * Piggy, ILocomotion * * Loco)
    static TryPiggyback(Piggy_0 : IPiggyback, Loco_1 : ILocomotion) : number;
    // public static long CreateInstance(ILocomotion * * ppv, _GUID const * rclsid, IUnknown * pUnkOuter, unsigned long dwClsContext)
    static CreateInstance(ppv_0 : ILocomotion, rclsid_1 : any, pUnkOuter_2 : any, dwClsContext_3 : number) : number;
    // these two are identical, why do they both exist...
    // public static void AddRef1(LocomotionClass * * Loco)
    static AddRef1(Loco_0 : LocomotionClass) : void;
    // public static void AddRef2(LocomotionClass * * Loco)
    static AddRef2(Loco_0 : LocomotionClass) : void;
    // public static void ChangeLocomotorTo(FootClass * Object, _GUID const& clsid)
    static ChangeLocomotorTo(Object_0 : FootClass, clsid_1 : any) : void;
    // creates a new instance by class ID. returns a pointer to ILocomotion
    // public static ILocomotionPtr CreateInstance(_GUID const& rclsid)
    static CreateInstance(rclsid_0 : any) : any;
    // finds out whether a locomotor is currently piggybacking and restores
    // the original locomotor. this function ignores Is_Ok_To_End().
    // public static bool End_Piggyback(ILocomotionPtr& pLoco)
    static End_Piggyback(pLoco_0 : any) : boolean;
    // Properties
    // public FootClass * Owner
    m_Owner : FootClass;
    // public FootClass * LinkedTo
    m_LinkedTo : FootClass;
    // public bool Powered
    m_Powered : boolean;
    // public bool Dirty
    m_Dirty : boolean;
    // public int RefCount
    m_RefCount : number;
}
// Variable
class Variable
{
    // public char[40] Name
    m_Name : string;
    // public char Value
    m_Value : number;
}
// LightingStruct
class LightingStruct
{
    // public TintStruct Tint
    m_Tint : TintStruct;
    // all these are stored as ini value * 100 + 0.01
    // public int Ground
    m_Ground : number;
    // this one is stored as ini value * 1000 + 0.01
    // public int Level
    m_Level : number;
}
// ScenarioFlags
class ScenarioFlags
{
    // public bool bit00
    m_bit00 : boolean;
    // public bool bit01
    m_bit01 : boolean;
    // public bool bit02
    m_bit02 : boolean;
    // public bool bit03
    m_bit03 : boolean;
    // the base for it does exist...
    // public bool CTFMode
    m_CTFMode : boolean;
    // public bool Inert
    m_Inert : boolean;
    // public bool TiberiumGrows
    m_TiberiumGrows : boolean;
    // public bool TiberiumSpreads
    m_TiberiumSpreads : boolean;
    // public bool MCVDeploy
    m_MCVDeploy : boolean;
    // public bool InitialVeteran
    m_InitialVeteran : boolean;
    // public bool FixedAlliance
    m_FixedAlliance : boolean;
    // public bool HarvesterImmune
    m_HarvesterImmune : boolean;
    // public bool FogOfWar
    m_FogOfWar : boolean;
    // public bool bit13
    m_bit13 : boolean;
    // public bool TiberiumExplosive
    m_TiberiumExplosive : boolean;
    // public bool DestroyableBridges
    m_DestroyableBridges : boolean;
    // public bool Meteorites
    m_Meteorites : boolean;
    // public bool IonStorms
    m_IonStorms : boolean;
    // public bool Visceroids
    m_Visceroids : boolean;
    // public bool bit19
    m_bit19 : boolean;
    // public bool bit20
    m_bit20 : boolean;
    // public bool bit21
    m_bit21 : boolean;
    // public bool bit22
    m_bit22 : boolean;
    // public bool bit23
    m_bit23 : boolean;
    // public bool bit24
    m_bit24 : boolean;
    // public bool bit25
    m_bit25 : boolean;
    // public bool bit26
    m_bit26 : boolean;
    // public bool bit27
    m_bit27 : boolean;
    // public bool bit28
    m_bit28 : boolean;
    // public bool bit29
    m_bit29 : boolean;
    // public bool bit30
    m_bit30 : boolean;
    // public bool bit31
    m_bit31 : boolean;
}
// ScenarioClass
class ScenarioClass
{
    // CTOR / DTOR
    // public ScenarioClass()
    constructor();
    // public static void UpdateCellLighting()
    static UpdateCellLighting() : void;
    // public static void UpdateLighting()
    static UpdateLighting() : void;
    // this function is only being inlined in RecalcLighting, but we can call it for just updating the hashpals
    // public static void UpdateHashPalLighting(int R, int G, int B, bool tint)
    static UpdateHashPalLighting(R_0 : number, G_1 : number, B_2 : number, tint_3 : boolean) : void;
    // public static void ScenarioLighting(int * r, int * g, int * b)
    static ScenarioLighting(r_0 : number, g_1 : number, b_2 : number) : void;
    // this calls UpdateCellLighting() from above and does other good stuff
    // initializers call it with -1, -1, -1, 0 , map retint actions use current tint * 10, 0
    // public static void RecalcLighting(int R, int G, int B, bool tint)
    static RecalcLighting(R_0 : number, G_1 : number, B_2 : number, tint_3 : boolean) : void;
    // public static bool SaveGame(char const * FileName, wchar_t const * Description, bool BarGraph = false)
    static SaveGame(FileName_0 : string, Description_1 : number, BarGraph_2 : boolean) : boolean;
    // public static bool LoadGame(char const * FileName)
    static LoadGame(FileName_0 : string) : boolean;
    // public static bool StartScenario(char const * FileName, bool Briefing, int CampaignIndex)
    static StartScenario(FileName_0 : string, Briefing_1 : boolean, CampaignIndex_2 : number) : boolean;
    // public static void PauseGame()
    static PauseGame() : void;
    // public static void ResumeGame()
    static ResumeGame() : void;
    // public static void AssignHouses()
    static AssignHouses() : void;
    // public void ReadStartPoints(INIClass& ini)
    ReadStartPoints(ini_0 : INIClass) : void;
    // valid range [0..701]
    // public bool IsDefinedWaypoint(int idx)
    IsDefinedWaypoint(idx_0 : number) : boolean;
    // public CellStruct * GetWaypointCoords(CellStruct * dest, int idx)
    GetWaypointCoords(dest_0 : CellStruct, idx_1 : number) : CellStruct;
    // public CellStruct GetWaypointCoords(int idx)
    GetWaypointCoords(idx_0 : number) : CellStruct;
    // Static
    // public static reference<ScenarioClass *, 11055664, 0> const Instance = 0xA8B230u
    static s_Instance : ScenarioClass;
    // public static reference<int, 11070844, 0> const NewINIFormat = 0xA8ED7Cu
    static s_NewINIFormat : number;
    // public static reference<TheaterType, 8531192, 0> const LastTheater = 0x822CF8
    static s_LastTheater : TheaterType;
    // Properties
    // public ScenarioFlags SpecialFlags
    m_SpecialFlags : ScenarioFlags;
    // public char[260] NextScenario
    m_NextScenario : string;
    // public char[260] AltNextScenario
    m_AltNextScenario : string;
    // CellStruct?
    // public int HomeCell
    m_HomeCell : number;
    // CellStruct?
    // public int AltHomeCell
    m_AltHomeCell : number;
    // defaults to 1,000,000 - random salt for this game's communications
    // public int UniqueID
    m_UniqueID : number;
    // 218
    // public Randomizer Random
    m_Random : Randomizer;
    // public unsigned long Difficulty1
    m_Difficulty1 : number;
    // 2 - Difficulty1
    // public unsigned long Difficulty2
    m_Difficulty2 : number;
    // public CDTimerClass ElapsedTimer
    m_ElapsedTimer : CDTimerClass;
    // public CDTimerClass PauseTimer
    m_PauseTimer : CDTimerClass;
    // public unsigned long unknown_62C
    m_unknown_62C : number;
    // public bool IsGamePaused
    m_IsGamePaused : boolean;
    // public CellStruct[702] Waypoints
    m_Waypoints : CellStruct;
    // Map Header
    // public int StartX
    m_StartX : number;
    // public int StartY
    m_StartY : number;
    // public int Width
    m_Width : number;
    // public int Height
    m_Height : number;
    // public int NumberStartingPoints
    m_NumberStartingPoints : number;
    // public Point2D[8] StartingPoints
    m_StartingPoints : Point2D;
    // starting position => HouseClass::Array->GetItem(#)
    // public int[16] HouseIndices
    m_HouseIndices : number;
    // public CellStruct[8] HouseHomeCells
    m_HouseHomeCells : CellStruct;
    // public bool TeamsPresent
    m_TeamsPresent : boolean;
    // public int NumCoopHumanStartSpots
    m_NumCoopHumanStartSpots : number;
    // public CDTimerClass MissionTimer
    m_MissionTimer : CDTimerClass;
    // public wchar_t * MissionTimerTextCSF
    m_MissionTimerTextCSF : number;
    // public char[32] MissionTimerText
    m_MissionTimerText : string;
    // public CDTimerClass ShroudRegrowTimer
    m_ShroudRegrowTimer : CDTimerClass;
    // public CDTimerClass FogTimer
    m_FogTimer : CDTimerClass;
    // public CDTimerClass IceTimer
    m_IceTimer : CDTimerClass;
    // public CDTimerClass unknown_timer_123c
    m_unknown_timer_123c : CDTimerClass;
    // public CDTimerClass AmbientTimer
    m_AmbientTimer : CDTimerClass;
    // public int TechLevel
    m_TechLevel : number;
    // public TheaterType Theater
    m_Theater : TheaterType;
    // public char[260] FileName
    m_FileName : string;
    // public wchar_t[45] Name
    m_Name : number;
    // public char[32] UIName
    m_UIName : string;
    // public wchar_t[45] UINameLoaded
    m_UINameLoaded : number;
    // Movie name
    // public char const * Intro
    m_Intro : string;
    // public char const * Brief
    m_Brief : string;
    // public char const * Win
    m_Win : string;
    // public char const * Lose
    m_Lose : string;
    // public char const * Action
    m_Action : string;
    // public char const * PostScore
    m_PostScore : string;
    // public char const * PreMapSelect
    m_PreMapSelect : string;
    // public wchar_t[1024] Briefing
    m_Briefing : number;
    // public char[32] BriefingCSF
    m_BriefingCSF : string;
    // public int ThemeIndex
    m_ThemeIndex : number;
    // public int HumanPlayerHouseTypeIndex
    m_HumanPlayerHouseTypeIndex : number;
    // public double CarryOverMoney
    m_CarryOverMoney : number;
    // public int CarryOverCap
    m_CarryOverCap : number;
    // public int Percent
    m_Percent : number;
    // public Variable[50] GlobalVariables
    m_GlobalVariables : Variable;
    // public Variable[100] LocalVariables
    m_LocalVariables : Variable;
    // public CellStruct View1
    m_View1 : CellStruct;
    // public CellStruct View2
    m_View2 : CellStruct;
    // public CellStruct View3
    m_View3 : CellStruct;
    // public CellStruct View4
    m_View4 : CellStruct;
    // public unsigned long unknown_34A0
    m_unknown_34A0 : number;
    // 34A4
    // public bool FreeRadar
    m_FreeRadar : boolean;
    // public bool TrainCrate
    m_TrainCrate : boolean;
    // public bool TiberiumGrowthEnabled
    m_TiberiumGrowthEnabled : boolean;
    // public bool VeinGrowthEnabled
    m_VeinGrowthEnabled : boolean;
    // 34A8
    // public bool IceGrowthEnabled
    m_IceGrowthEnabled : boolean;
    // RA1 leftover, no logic attached
    // public bool BridgeDestroyed
    m_BridgeDestroyed : boolean;
    // global or local has been updated 34AA
    // public bool VariablesChanged
    m_VariablesChanged : boolean;
    // ambient has been changed 34AB
    // public bool AmbientChanged
    m_AmbientChanged : boolean;
    // 34AC
    // public bool EndOfGame
    m_EndOfGame : boolean;
    // public bool TimerInherit
    m_TimerInherit : boolean;
    // public bool SkipScore
    m_SkipScore : boolean;
    // public bool OneTimeOnly
    m_OneTimeOnly : boolean;
    // 34B0
    // public bool SkipMapSelect
    m_SkipMapSelect : boolean;
    // public bool TruckCrate
    m_TruckCrate : boolean;
    // public bool FillSilos
    m_FillSilos : boolean;
    // public bool TiberiumDeathToVisceroid
    m_TiberiumDeathToVisceroid : boolean;
    // 34B4
    // public bool IgnoreGlobalAITriggers
    m_IgnoreGlobalAITriggers : boolean;
    // public bool unknown_bool_34B5
    m_unknown_bool_34B5 : boolean;
    // public bool unknown_bool_34B6
    m_unknown_bool_34B6 : boolean;
    // public bool unknown_bool_34B7
    m_unknown_bool_34B7 : boolean;
    // 34B8
    // public int PlayerSideIndex
    m_PlayerSideIndex : number;
    // 34BC
    // public bool MultiplayerOnly
    m_MultiplayerOnly : boolean;
    // public bool IsRandom
    m_IsRandom : boolean;
    // public bool PickedUpAnyCrate
    m_PickedUpAnyCrate : boolean;
    // public CDTimerClass unknown_timer_34C0
    m_unknown_timer_34C0 : CDTimerClass;
    // public int CampaignIndex
    m_CampaignIndex : number;
    // public int StartingDropships
    m_StartingDropships : number;
    // public TypeList<TechnoTypeClass *> AllowableUnits
    m_AllowableUnits : TypeList<TechnoTypeClass>;
    // public TypeList<int> AllowableUnitMaximums
    m_AllowableUnitMaximums : TypeList<number>;
    // public TypeList<int> DropshipUnitCounts
    m_DropshipUnitCounts : TypeList<number>;
    // set at map creation
    // public int AmbientOriginal
    m_AmbientOriginal : number;
    // current ambient
    // public int AmbientCurrent
    m_AmbientCurrent : number;
    // target ambient (while changing)
    // public int AmbientTarget
    m_AmbientTarget : number;
    // public LightingStruct NormalLighting
    m_NormalLighting : LightingStruct;
    // Ion lighting
    // public int IonAmbient
    m_IonAmbient : number;
    // public LightingStruct IonLighting
    m_IonLighting : LightingStruct;
    // Nuke flash lighting
    // public int NukeAmbient
    m_NukeAmbient : number;
    // public LightingStruct NukeLighting
    m_NukeLighting : LightingStruct;
    // public int NukeAmbientChangeRate
    m_NukeAmbientChangeRate : number;
    // Dominator lighting
    // public int DominatorAmbient
    m_DominatorAmbient : number;
    // public LightingStruct DominatorLighting
    m_DominatorLighting : LightingStruct;
    // public int DominatorAmbientChangeRate
    m_DominatorAmbientChangeRate : number;
    // public unsigned long unknown_3598
    m_unknown_3598 : number;
    // public int InitTime
    m_InitTime : number;
    // public short Stage
    m_Stage : number;
    // public bool UserInputLocked
    m_UserInputLocked : boolean;
    // public bool unknown_35A3
    m_unknown_35A3 : boolean;
    // public int ParTimeEasy
    m_ParTimeEasy : number;
    // public int ParTimeMedium
    m_ParTimeMedium : number;
    // public int ParTimeDifficult
    m_ParTimeDifficult : number;
    // 35B0
    // public char[31] UnderParTitle
    m_UnderParTitle : string;
    // 35CF
    // public char[31] UnderParMessage
    m_UnderParMessage : string;
    // 35EE
    // public char[31] OverParTitle
    m_OverParTitle : string;
    // 360D
    // public char[31] OverParMessage
    m_OverParMessage : string;
    // 362C
    // public char[31] LSLoadMessage
    m_LSLoadMessage : string;
    // 364B
    // public char[31] LSBrief
    m_LSBrief : string;
    // public int LS640BriefLocX
    m_LS640BriefLocX : number;
    // public int LS640BriefLocY
    m_LS640BriefLocY : number;
    // public int LS800BriefLocX
    m_LS800BriefLocX : number;
    // public int LS800BriefLocY
    m_LS800BriefLocY : number;
    // public char[64] LS640BkgdName
    m_LS640BkgdName : string;
    // public char[64] LS800BkgdName
    m_LS800BkgdName : string;
    // public char[64] LS800BkgdPal
    m_LS800BkgdPal : string;
}
// forward declarations
// OverlayClass
class OverlayClass
    extends ObjectClass
{
    // Constructor
    // public OverlayClass(OverlayTypeClass * pType, CellStruct const& mapCoord, int flag)
    constructor(pType_0 : OverlayTypeClass, mapCoord_1 : CellStruct, flag_2 : number);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // Gets overlay's tiberium type
    // public static int GetTiberiumType(int overlayTypeIndex)
    static GetTiberiumType(overlayTypeIndex_0 : number) : number;
    // public static AbstractType const AbsID = AbstractType::Overlay
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<OverlayClass *>, 11070544> const Array = 0xA8EC50u
    static s_Array : DynamicVectorClass<OverlayClass>;
    // public OverlayTypeClass * Type
    m_Type : OverlayTypeClass;
}
// forward declarations
// SmudgeClass
class SmudgeClass
    extends ObjectClass
{
    // Constructor
    // public SmudgeClass(SmudgeTypeClass * pType)
    constructor(pType_0 : SmudgeTypeClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::Smudge
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<SmudgeClass *>, 11055584> const Array = 0xA8B1E0u
    static s_Array : DynamicVectorClass<SmudgeClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public SmudgeTypeClass * Type
    m_Type : SmudgeTypeClass;
}
// forward declarations
// VoxelAnimClass
class VoxelAnimClass
    extends ObjectClass
{
    // Constructor
    // public VoxelAnimClass(VoxelAnimTypeClass * pVoxelAnimType, CoordStruct * pLocation, HouseClass * pOwnerHouse)
    constructor(pVoxelAnimType_0 : VoxelAnimTypeClass, pLocation_1 : CoordStruct, pOwnerHouse_2 : HouseClass);
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // AbstractClass
    // public virtual AbstractType WhatAmI() const
    WhatAmI() : AbstractType;
    // public virtual int Size() const
    Size() : number;
    // public static AbstractType const AbsID = AbstractType::VoxelAnim
    static s_AbsID : AbstractType;
    // Static
    // public static constant_ptr<DynamicVectorClass<VoxelAnimClass *>, 8942472> const Array = 0x887388u
    static s_Array : DynamicVectorClass<VoxelAnimClass>;
    // public int unknown_int_100
    m_unknown_int_100 : number;
    // public VoxelAnimTypeClass * Type
    m_Type : VoxelAnimTypeClass;
    // public ParticleSystemClass * AttachedSystem
    m_AttachedSystem : ParticleSystemClass;
    // public HouseClass * OwnerHouse
    m_OwnerHouse : HouseClass;
    // remove on next update
    // public bool TimeToDie
    m_TimeToDie : boolean;
    // don't draw, but Update state anyway
    // public bool Invisible
    m_Invisible : boolean;
    // counting down to zero
    // public int Duration
    m_Duration : number;
    // public BounceClass Bounce
    m_Bounce : BounceClass;
    // public char[80] __Bounce
    m___Bounce : string;
    // public AudioController Audio3
    m_Audio3 : any;
    // public char[20] __Audio3
    m___Audio3 : string;
    // public AudioController Audio4
    m_Audio4 : any;
    // public char[20] __Audio4
    m___Audio4 : string;
}
// forward declarations
// FlyLocomotionClass
class FlyLocomotionClass
    extends LocomotionClass
{
    // Constructor
    // public FlyLocomotionClass()
    constructor();
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // ILocomotion
    // public virtual bool Is_Moving()
    Is_Moving() : boolean;
    // Fetches destination coordinate.
    // public virtual CoordStruct Destination()
    Destination() : CoordStruct;
    // Process movement of object.]
    // public virtual bool Process()
    Process() : boolean;
    // Instruct to move to location specified.
    // public virtual void Move_To(CoordStruct to)
    Move_To(to_0 : CoordStruct | any) : void;
    // Stop moving at first opportunity.
    // public virtual void Stop_Moving()
    Stop_Moving() : void;
    // Try to face direction specified.
    // public virtual void Do_Turn(DirStruct coord)
    Do_Turn(coord_0 : DirStruct | any) : void;
    // What display layer is it located in.
    // public virtual Layer In_Which_Layer()
    In_Which_Layer() : Layer;
    // Lifts all occupation bits associated with the object off the map
    // public virtual void Mark_All_Occupation_Bits(MarkType mark)
    Mark_All_Occupation_Bits(mark_0 : MarkType | any) : void;
    // Object is disappearing from the world.
    // Was added post TLB generation.
    // public virtual void Limbo()
    Limbo() : void;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // LocomotionClass
    // public virtual int Size()
    Size() : number;
    // public static unsigned int const ILocoVTable = 0x7E89F4
    static s_ILocoVTable : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public bool AirportBound
    m_AirportBound : boolean;
    // public CoordStruct MovingDestination
    m_MovingDestination : CoordStruct;
    // public CoordStruct XYZ2
    m_XYZ2 : CoordStruct;
    // public bool HasMoveOrder
    m_HasMoveOrder : boolean;
    // public int FlightLevel
    m_FlightLevel : number;
    // public double TargetSpeed
    m_TargetSpeed : number;
    // public double CurrentSpeed
    m_CurrentSpeed : number;
    // public char IsTakingOff
    m_IsTakingOff : number;
    // public bool IsLanding
    m_IsLanding : boolean;
    // public bool WasLanding
    m_WasLanding : boolean;
    // public bool unknown_bool_53
    m_unknown_bool_53 : boolean;
    // public unsigned long unknown_54
    m_unknown_54 : number;
    // public unsigned long unknown_58
    m_unknown_58 : number;
    // public bool IsElevating
    m_IsElevating : boolean;
    // public bool unknown_bool_5D
    m_unknown_bool_5D : boolean;
    // public bool unknown_bool_5E
    m_unknown_bool_5E : boolean;
    // public bool unknown_bool_5F
    m_unknown_bool_5F : boolean;
}
// forward declarations
// RocketLocomotionClass
class RocketLocomotionClass
    extends LocomotionClass
{
    // Constructor
    // public RocketLocomotionClass()
    constructor();
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // ILocomotion
    // public virtual bool Is_Moving()
    Is_Moving() : boolean;
    // Fetches destination coordinate.
    // public virtual CoordStruct Destination()
    Destination() : CoordStruct;
    // Process movement of object.]
    // public virtual bool Process()
    Process() : boolean;
    // Instruct to move to location specified.
    // public virtual void Move_To(CoordStruct to)
    Move_To(to_0 : CoordStruct | any) : void;
    // Stop moving at first opportunity.
    // public virtual void Stop_Moving()
    Stop_Moving() : void;
    // Try to face direction specified.
    // public virtual void Do_Turn(DirStruct coord)
    Do_Turn(coord_0 : DirStruct | any) : void;
    // What display layer is it located in.
    // public virtual Layer In_Which_Layer()
    In_Which_Layer() : Layer;
    // Lifts all occupation bits associated with the object off the map
    // public virtual void Mark_All_Occupation_Bits(MarkType mark)
    Mark_All_Occupation_Bits(mark_0 : MarkType | any) : void;
    // Object is disappearing from the world.
    // Was added post TLB generation.
    // public virtual void Limbo()
    Limbo() : void;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // LocomotionClass
    // public virtual int Size()
    Size() : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public CoordStruct MovingDestination
    m_MovingDestination : CoordStruct;
    // public RateTimer MissionTimer
    m_MissionTimer : RateTimer;
    // public CDTimerClass TrailerTimer
    m_TrailerTimer : CDTimerClass;
    // public int MissionState
    m_MissionState : number;
    // public unsigned long unknown_44
    m_unknown_44 : number;
    // public double CurrentSpeed
    m_CurrentSpeed : number;
    // public bool unknown_bool_4C
    m_unknown_bool_4C : boolean;
    // public bool SpawnerIsElite
    m_SpawnerIsElite : boolean;
    // public float CurrentPitch
    m_CurrentPitch : number;
    // public unsigned long unknown_58
    m_unknown_58 : number;
    // public unsigned long unknown_5C
    m_unknown_5C : number;
}
// forward declarations
// TeleportLocomotionClass
class TeleportLocomotionClass
    extends LocomotionClass
{
    // Constructor
    // public TeleportLocomotionClass()
    constructor();
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // IPiggyback
    // public virtual long Begin_Piggyback(ILocomotion * pointer)
    Begin_Piggyback(pointer_0 : ILocomotion | any) : number;
    // End piggyback process and restore locomotor interface pointer.
    // public virtual long End_Piggyback(ILocomotion * * pointer)
    End_Piggyback(pointer_0 : ILocomotion | any) : number;
    // Determines when should the piggybacking be ended (done automatically in FootClass::AI).
    // public virtual bool Is_Ok_To_End()
    Is_Ok_To_End() : boolean;
    // Fetches piggybacked locomotor class ID.
    // public virtual long Piggyback_CLSID(_GUID * classid)
    Piggyback_CLSID(classid_0 : any | any) : number;
    // Is it currently piggybacking another locomotor?
    // public virtual bool Is_Piggybacking()
    Is_Piggybacking() : boolean;
    // ILocomotion
    // public virtual bool Is_Moving()
    Is_Moving() : boolean;
    // Fetches destination coordinate.
    // public virtual CoordStruct Destination()
    Destination() : CoordStruct;
    // Process movement of object.]
    // public virtual bool Process()
    Process() : boolean;
    // Instruct to move to location specified.
    // public virtual void Move_To(CoordStruct to)
    Move_To(to_0 : CoordStruct | any) : void;
    // Stop moving at first opportunity.
    // public virtual void Stop_Moving()
    Stop_Moving() : void;
    // Try to face direction specified.
    // public virtual void Do_Turn(DirStruct coord)
    Do_Turn(coord_0 : DirStruct | any) : void;
    // What display layer is it located in.
    // public virtual Layer In_Which_Layer()
    In_Which_Layer() : Layer;
    // Lifts all occupation bits associated with the object off the map
    // public virtual void Mark_All_Occupation_Bits(MarkType mark)
    Mark_All_Occupation_Bits(mark_0 : MarkType | any) : void;
    // Object is disappearing from the world.
    // Was added post TLB generation.
    // public virtual void Limbo()
    Limbo() : void;
    // IPersist
    // public virtual long GetClassID(_GUID * pClassID)
    GetClassID(pClassID_0 : any | any) : number;
    // IPersistStream
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any | any) : number;
    // public virtual long Save(IStream * pStm, int fClearDirty)
    Save(pStm_0 : any | any, fClearDirty_1 : number | any) : number;
    // LocomotionClass
    // public virtual int Size()
    Size() : number;
    // TeleportLocomotionClass
    // public virtual void vt_entry_28(unsigned long dwUnk)
    vt_entry_28(dwUnk_0 : number) : void;
    // public virtual bool IsStill()
    IsStill() : boolean;
    // public static unsigned int const ILocoVTable = 0x7F5000
    static s_ILocoVTable : number;
    // Current destination
    // public CoordStruct MovingDestination
    m_MovingDestination : CoordStruct;
    // Marked occupation bits there
    // public CoordStruct LastCoords
    m_LastCoords : CoordStruct;
    // Is currently moving
    // public bool Moving
    m_Moving : boolean;
    // public bool unknown_bool_35
    m_unknown_bool_35 : boolean;
    // public bool unknown_bool_36
    m_unknown_bool_36 : boolean;
    // public int State
    m_State : number;
    // public CDTimerClass Timer
    m_Timer : CDTimerClass;
    // public ILocomotion * Piggybackee
    m_Piggybackee : ILocomotion;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// GScreenClass
class GScreenClass
{
    // public static void DoBlit(bool mouseCaptured, DSurface * surface, RectangleStruct * rect = nullptr)
    static DoBlit(mouseCaptured_0 : boolean, surface_1 : DSurface, rect_2 : RectangleStruct) : void;
    // IUnknown
    // public virtual long QueryInterface(_GUID const& iid, void * * ppvObject)
    QueryInterface(iid_0 : any | any, ppvObject_1 : void | any) : number;
    // public virtual unsigned long AddRef()
    AddRef() : number;
    // public virtual unsigned long Release()
    Release() : number;
    // GScreenClass
    // public virtual void One_Time()
    One_Time() : void;
    // public virtual void Init()
    Init() : void;
    // public virtual void Init_Clear()
    Init_Clear() : void;
    // public virtual void Init_IO()
    Init_IO() : void;
    // public virtual void GetInputAndUpdate(unsigned long& outKeyCode, int& outMouseX, int& outMouseY)
    GetInputAndUpdate(outKeyCode_0 : number, outMouseX_1 : number, outMouseY_2 : number) : void;
    // public virtual void Update(int const& keyCode, Point2D const& mouseCoords)
    Update(keyCode_0 : number, mouseCoords_1 : Point2D) : void;
    // public virtual bool SetButtons(GadgetClass * pGadget)
    SetButtons(pGadget_0 : GadgetClass) : boolean;
    // public virtual bool AddButton(GadgetClass * pGadget)
    AddButton(pGadget_0 : GadgetClass) : boolean;
    // public virtual bool RemoveButton(GadgetClass * pGadget)
    RemoveButton(pGadget_0 : GadgetClass) : boolean;
    // public virtual void MarkNeedsRedraw(int dwUnk)
    MarkNeedsRedraw(dwUnk_0 : number) : void;
    // public virtual void DrawOnTop()
    DrawOnTop() : void;
    // public virtual void Draw(unsigned long dwUnk)
    Draw(dwUnk_0 : number) : void;
    // public virtual void vt_entry_44()
    vt_entry_44() : void;
    // public virtual bool SetCursor(MouseCursorType idxCursor, bool miniMap) = 0
    SetCursor(idxCursor_0 : MouseCursorType, miniMap_1 : boolean) : boolean;
    // public virtual bool UpdateCursor(MouseCursorType idxCursor, bool miniMap) = 0
    UpdateCursor(idxCursor_0 : MouseCursorType, miniMap_1 : boolean) : boolean;
    // public virtual bool RestoreCursor() = 0
    RestoreCursor() : boolean;
    // public virtual void UpdateCursorMinimapState(bool miniMap) = 0
    UpdateCursorMinimapState(miniMap_0 : boolean) : void;
    // public void Render()
    Render() : void;
    // Static
    // public static constant_ptr<GScreenClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : GScreenClass;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public int ScreenShakeX
    m_ScreenShakeX : number;
    // public int ScreenShakeY
    m_ScreenShakeY : number;
    // default is 2
    // public int Bitfield
    m_Bitfield : number;
}
// Powerup crates
// Crate
class Crate
{
    // Properties
    // public CDTimerClass CrateTimer
    m_CrateTimer : CDTimerClass;
    // public CellStruct Location
    m_Location : CellStruct;
}
// ========================================================================
// === DynamicVectorClass =================================================
// ========================================================================
// LayerClass
class LayerClass
    extends DynamicVectorClass<ObjectClass>
{
    // public virtual bool AddObject(ObjectClass * pObject, bool sorted)
    AddObject(pObject_0 : ObjectClass, sorted_1 : boolean) : boolean;
    // public virtual void RemoveAll()
    RemoveAll() : void;
    // public virtual void vt_entry_24()
    vt_entry_24() : void;
    // public void Load(IStream * pStm)
    Load(pStm_0 : any) : void;
    // public void Save(IStream * pStm)
    Save(pStm_0 : any) : void;
    // public void Sort()
    Sort() : void;
}
// ========================================================================
// === DynamicVectorClass =================================================
// ========================================================================
// LogicClass
class LogicClass
    extends LayerClass
{
    // public virtual bool AddObject(ObjectClass * pObject, bool sorted)
    AddObject(pObject_0 : ObjectClass | any, sorted_1 : boolean | any) : boolean;
    // public virtual void PointerGotInvalid(AbstractClass * pInvalid, bool removed)
    PointerGotInvalid(pInvalid_0 : AbstractClass, removed_1 : boolean) : void;
    // public void RemoveObject(ObjectClass * pObject)
    RemoveObject(pObject_0 : ObjectClass) : void;
    // public void Update()
    Update() : void;
    // public static reference<LogicClass, 8910712, 0> const Instance = 0x87F778u
    static s_Instance : LogicClass;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// MapClass
class MapClass
    extends GScreenClass
{
    // public static LayerClass * GetLayer(Layer lyr)
    static GetLayer(lyr_0 : Layer) : LayerClass;
    // IGameMap
    // public virtual long Is_Visible(CellStruct cell)
    Is_Visible(cell_0 : CellStruct | any) : number;
    // MapClass
    // public virtual void AllocateCells()
    AllocateCells() : void;
    // public virtual void DestructCells()
    DestructCells() : void;
    // public virtual void ConstructCells()
    ConstructCells() : void;
    // public virtual void PointerGotInvalid(AbstractClass * ptr, bool bUnk)
    PointerGotInvalid(ptr_0 : AbstractClass, bUnk_1 : boolean) : void;
    // public virtual bool DraggingInProgress()
    DraggingInProgress() : boolean;
    // public virtual void UpdateCrates()
    UpdateCrates() : void;
    // public virtual void CreateEmptyMap(RectangleStruct const& mapRect, bool reuse, char nLevel, bool bUnk2)
    CreateEmptyMap(mapRect_0 : RectangleStruct, reuse_1 : boolean, nLevel_2 : number, bUnk2_3 : boolean) : void;
    // public virtual void SetVisibleRect(RectangleStruct const& mapRect)
    SetVisibleRect(mapRect_0 : RectangleStruct) : void;
    // Non-virtual
    // public CellClass * TryGetCellAt(CellStruct const& MapCoords) const
    TryGetCellAt(MapCoords_0 : CellStruct) : CellClass;
    // public CellClass * TryGetCellAt(CoordStruct const& Crd) const
    TryGetCellAt(Crd_0 : CoordStruct) : CellClass;
    // public CellClass * GetCellAt(CellStruct const& MapCoords) const
    GetCellAt(MapCoords_0 : CellStruct) : CellClass;
    // public CellClass * GetCellAt(CoordStruct const& Crd) const
    GetCellAt(Crd_0 : CoordStruct) : CellClass;
    // public CellClass * GetTargetCell(Point2D& location)
    GetTargetCell(location_0 : Point2D) : CellClass;
    // public bool CellExists(CellStruct const& MapCoords) const
    CellExists(MapCoords_0 : CellStruct) : boolean;
    // public int GetThreatPosed(CellStruct const& cell, HouseClass * pHouse) const
    GetThreatPosed(cell_0 : CellStruct, pHouse_1 : HouseClass) : number;
    // public bool IsLocationShrouded(CoordStruct const& crd) const
    IsLocationShrouded(crd_0 : CoordStruct) : boolean;
    // public static int GetCellIndex(CellStruct const& MapCoords)
    static GetCellIndex(MapCoords_0 : CellStruct) : number;
    // gets a coordinate in a random direction a fixed distance in leptons away from coords
    // public static CoordStruct * GetRandomCoordsNear(CoordStruct& outBuffer, CoordStruct const& coords, int distance, bool center)
    static GetRandomCoordsNear(outBuffer_0 : CoordStruct, coords_1 : CoordStruct, distance_2 : number, center_3 : boolean) : CoordStruct;
    // gets a coordinate in a random direction a fixed distance in leptons away from coords
    // public static CoordStruct GetRandomCoordsNear(CoordStruct const& coords, int distance, bool center)
    static GetRandomCoordsNear(coords_0 : CoordStruct, distance_1 : number, center_2 : boolean) : CoordStruct;
    // public static CoordStruct * PickInfantrySublocation(CoordStruct& outBuffer, CoordStruct const& coords, bool ignoreContents = false)
    static PickInfantrySublocation(outBuffer_0 : CoordStruct, coords_1 : CoordStruct, ignoreContents_2 : boolean) : CoordStruct;
    // public static CoordStruct PickInfantrySublocation(CoordStruct const& coords, bool ignoreContents = false)
    static PickInfantrySublocation(coords_0 : CoordStruct, ignoreContents_1 : boolean) : CoordStruct;
    // public static void UnselectAll()
    static UnselectAll() : void;
    // public void CenterMap()
    CenterMap() : void;
    // public void CellIteratorReset()
    CellIteratorReset() : void;
    // public CellClass * CellIteratorNext()
    CellIteratorNext() : CellClass;
    // public int GetMovementZoneType(CellStruct const& MapCoords, MovementZone movementZone, bool isBridge)
    GetMovementZoneType(MapCoords_0 : CellStruct, movementZone_1 : MovementZone, isBridge_2 : boolean) : number;
    // the key damage delivery
    // The key damage delivery function.
    // 
    // @param Coords Location of the impact/center of damage.
    // @param Damage Amount of damage to deal.
    // @param SourceObject The object which caused the damage to be delivered (iow, the shooter).
    // @param WH The warhead to use to apply the damage.
    // @param AffectsTiberium If this is false, Tiberium=yes is ignored.
    // @param SourceHouse The house to which SourceObject belongs, the owner/bringer of damage.
    // public static DamageAreaResult DamageArea(CoordStruct const& Coords, int Damage, TechnoClass * SourceObject, WarheadTypeClass * WH, bool AffectsTiberium, HouseClass * SourceHouse)
    static DamageArea(Coords_0 : CoordStruct, Damage_1 : number, SourceObject_2 : TechnoClass, WH_3 : WarheadTypeClass, AffectsTiberium_4 : boolean, SourceHouse_5 : HouseClass) : DamageAreaResult;
    // Picks the appropriate anim from WH's AnimList= based on damage dealt and land type (Conventional= )
    // so after DamageArea:
    // if(AnimTypeClass *damageAnimType = SelectDamageAnimation(...)) {
    // GameCreate
    // <AnimClass
    // >(damageAnimType, location);
    // }
    // public static AnimTypeClass * SelectDamageAnimation(int Damage, WarheadTypeClass * WH, LandType LandType, CoordStruct const& coords)
    static SelectDamageAnimation(Damage_0 : number, WH_1 : WarheadTypeClass, LandType_2 : LandType, coords_3 : CoordStruct) : AnimTypeClass;
    // public static void FlashbangWarheadAt(int Damage, WarheadTypeClass * WH, CoordStruct coords, bool Force = 0, SpotlightFlags CLDisableFlags = SpotlightFlags::None)
    static FlashbangWarheadAt(Damage_0 : number, WH_1 : WarheadTypeClass, coords_2 : CoordStruct, Force_3 : boolean, CLDisableFlags_4 : SpotlightFlags) : void;
    // get the damage a warhead causes to specific armor
    // public static int GetTotalDamage(int damage, WarheadTypeClass const * pWarhead, Armor armor, int distance)
    static GetTotalDamage(damage_0 : number, pWarhead_1 : WarheadTypeClass, armor_2 : Armor, distance_3 : number) : number;
    // public int GetCellFloorHeight(CoordStruct const& crd) const
    GetCellFloorHeight(crd_0 : CoordStruct) : number;
    // public CellStruct * PickCellOnEdge(CellStruct& buffer, Edge Edge, CellStruct const& CurrentLocation, CellStruct const& Fallback, SpeedType SpeedType, bool ValidateReachability, MovementZone MovZone) const
    PickCellOnEdge(buffer_0 : CellStruct, Edge_1 : Edge, CurrentLocation_2 : CellStruct, Fallback_3 : CellStruct, SpeedType_4 : SpeedType, ValidateReachability_5 : boolean, MovZone_6 : MovementZone) : CellStruct;
    // public CellStruct PickCellOnEdge(Edge Edge, CellStruct const& CurrentLocation, CellStruct const& Fallback, SpeedType SpeedType, bool ValidateReachability, MovementZone MovZone) const
    PickCellOnEdge(Edge_0 : Edge, CurrentLocation_1 : CellStruct, Fallback_2 : CellStruct, SpeedType_3 : SpeedType, ValidateReachability_4 : boolean, MovZone_5 : MovementZone) : CellStruct;
    // Pathfinding voodoo
    // do not touch them, mmkay, they trigger ZoneConnection recalc which is a MUST for firestorm to work
    // public void Update_Pathfinding_1()
    Update_Pathfinding_1() : void;
    // public void Update_Pathfinding_2(DynamicVectorClass<Vector2D<short>> const& where)
    Update_Pathfinding_2(where_0 : DynamicVectorClass<Vector2D>) : void;
    // Find nearest spot
    // public CellStruct * NearByLocation(CellStruct& outBuffer, CellStruct const& position, SpeedType SpeedType, int a5, MovementZone MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, CellStruct const& closeTo, bool a15, bool buildable)
    NearByLocation(outBuffer_0 : CellStruct, position_1 : CellStruct, SpeedType_2 : SpeedType, a5_3 : number, MovementZone_4 : MovementZone, alt_5 : boolean, SpaceSizeX_6 : number, SpaceSizeY_7 : number, disallowOverlay_8 : boolean, a11_9 : boolean, requireBurrowable_10 : boolean, allowBridge_11 : boolean, closeTo_12 : CellStruct, a15_13 : boolean, buildable_14 : boolean) : CellStruct;
    // public CellStruct NearByLocation(CellStruct const& position, SpeedType SpeedType, int a5, MovementZone MovementZone, bool alt, int SpaceSizeX, int SpaceSizeY, bool disallowOverlay, bool a11, bool requireBurrowable, bool allowBridge, CellStruct const& closeTo, bool a15, bool buildable)
    NearByLocation(position_0 : CellStruct, SpeedType_1 : SpeedType, a5_2 : number, MovementZone_3 : MovementZone, alt_4 : boolean, SpaceSizeX_5 : number, SpaceSizeY_6 : number, disallowOverlay_7 : boolean, a11_8 : boolean, requireBurrowable_9 : boolean, allowBridge_10 : boolean, closeTo_11 : CellStruct, a15_12 : boolean, buildable_13 : boolean) : CellStruct;
    // public void AddContentAt(CellStruct * coords, TechnoClass * Content)
    AddContentAt(coords_0 : CellStruct, Content_1 : TechnoClass) : void;
    // public void RemoveContentAt(CellStruct * coords, TechnoClass * Content)
    RemoveContentAt(coords_0 : CellStruct, Content_1 : TechnoClass) : void;
    // public bool IsWithinUsableArea(CellStruct const& cell, bool checkLevel) const
    IsWithinUsableArea(cell_0 : CellStruct, checkLevel_1 : boolean) : boolean;
    // public bool IsWithinUsableArea(CellClass * pCell, bool checkLevel) const
    IsWithinUsableArea(pCell_0 : CellClass, checkLevel_1 : boolean) : boolean;
    // public bool IsWithinUsableArea(CoordStruct const& coords) const
    IsWithinUsableArea(coords_0 : CoordStruct) : boolean;
    // public bool CoordinatesLegal(CellStruct const& cell) const
    CoordinatesLegal(cell_0 : CellStruct) : boolean;
    // public bool IsLinkedBridgeDestroyed(CellStruct const& cell) const
    IsLinkedBridgeDestroyed(cell_0 : CellStruct) : boolean;
    // public bool PlacePowerupCrate(CellStruct cell, Powerup type)
    PlacePowerupCrate(cell_0 : CellStruct, type_1 : Powerup) : boolean;
    // ====================================
    // FIRESTORM RELATED
    // ====================================
    // public CoordStruct * FindFirstFirestorm(CoordStruct * pOutBuffer, CoordStruct const& start, CoordStruct const& end, HouseClass const * pHouse = nullptr) const
    FindFirstFirestorm(pOutBuffer_0 : CoordStruct, start_1 : CoordStruct, end_2 : CoordStruct, pHouse_3 : HouseClass) : CoordStruct;
    // public CoordStruct FindFirstFirestorm(CoordStruct const& start, CoordStruct const& end, HouseClass const * pHouse = nullptr) const
    FindFirstFirestorm(start_0 : CoordStruct, end_1 : CoordStruct, pHouse_2 : HouseClass) : CoordStruct;
    // TechnoClass::Fire uses this for RevealOnFire on player's own units (radius = 3)
    // TechnoClass::See uses this on all (singleCampaign || !MultiplayPassive) units
    // TalkBubble uses this to display the unit to the player
    // public void RevealArea1(CoordStruct * Coords, int Radius, HouseClass * OwnerHouse, CellStruct arg4, unsigned char RevealByHeight, unsigned char arg6, unsigned char arg7, unsigned char arg8)
    RevealArea1(Coords_0 : CoordStruct, Radius_1 : number, OwnerHouse_2 : HouseClass, arg4_3 : CellStruct, RevealByHeight_4 : number, arg6_5 : number, arg7_6 : number, arg8_7 : number) : void;
    // these come in pairs - first the last argument is 0 and then 1
    // AircraftClass::Fire - reveal the target area to the owner (0,0,0,1,x)
    // AircraftClass::See - reveal shroud when on the ground (arg,arg,0,1,x), and fog always (0,0,1,(height 
    // <
    // flightlevel/2),x)
    // AnimClass::AnimClass - reveal area to player if anim->Type = [General]DropZoneAnim= (radius = Rules->DropZoneRadius /256) (0,0,0,1,x)
    // BuildingClass::Place - reveal (r = 1) to player if this is ToTile and owned by player (0,0,0,1,x)
    // BuildingClass::Unlimbo - reveal (radius = this->Type->Sight ) to owner (0,0,0,1,x)
    // PsychicReveal launch - reveal to user (0,0,0,0,x)
    // ActionClass::RevealWaypoint - reveal RevealTriggerRadius= to player (0,0,0,1,x)
    // ActionClass::RevealZoneOfWaypoint - reveal (r = 2) to player (0,0,0,1,x)
    // public void RevealArea2(CoordStruct * Coords, int Radius, HouseClass * OwnerHouse, unsigned long arg4, unsigned char RevealByHeight, unsigned char arg6, unsigned char arg7, unsigned char arg8)
    RevealArea2(Coords_0 : CoordStruct, Radius_1 : number, OwnerHouse_2 : HouseClass, arg4_3 : number, RevealByHeight_4 : number, arg6_5 : number, arg7_6 : number, arg8_7 : number) : void;
    // AircraftClass::SpyPlaneApproach
    // AircraftClass::SpyPlaneOverfly
    // AircraftClass::Carryall_Unload
    // BuildingClass::Place - RevealToAll
    // Foot/Infantry Class::Update/UpdatePosition
    // MapClass::RevealArea0 calls this to do the work
    // ParasiteClass::Infect/PointerGotInvalid
    // TechnoClass::Unlimbo
    // TechnoClass::Fire uses this (r = 4) right after using RevealArea0, wtfcock
    // public void RevealArea3(CoordStruct * Coords, int Height, int Radius, bool SkipReveal)
    RevealArea3(Coords_0 : CoordStruct, Height_1 : number, Radius_2 : number, SkipReveal_3 : boolean) : void;
    // public void Reveal(HouseClass * pHouse)
    Reveal(pHouse_0 : HouseClass) : void;
    // public void Reshroud(HouseClass * pHouse)
    Reshroud(pHouse_0 : HouseClass) : void;
    // public int GetZPos(CoordStruct * Coords)
    GetZPos(Coords_0 : CoordStruct) : number;
    // these two VERY slowly reprocess the map after gapgen state changes
    // public void sub_657CE0()
    sub_657CE0() : void;
    // public void RedrawSidebar(int mode)
    RedrawSidebar(mode_0 : number) : void;
    // public ObjectClass * NextObject(ObjectClass * pCurrentObject)
    NextObject(pCurrentObject_0 : ObjectClass) : ObjectClass;
    // public void SetTogglePowerMode(int mode)
    SetTogglePowerMode(mode_0 : number) : void;
    // public void SetPlaceBeaconMode(int mode)
    SetPlaceBeaconMode(mode_0 : number) : void;
    // public void SetSellMode(int mode)
    SetSellMode(mode_0 : number) : void;
    // public void SetWaypointMode(int mode, bool somebool)
    SetWaypointMode(mode_0 : number, somebool_1 : boolean) : void;
    // public void SetRepairMode(int mode)
    SetRepairMode(mode_0 : number) : void;
    // public void DestroyCliff(CellClass * Cell)
    DestroyCliff(Cell_0 : CellClass) : void;
    // public bool IsLocationFogged(CoordStruct const& coord)
    IsLocationFogged(coord_0 : CoordStruct) : boolean;
    // bool IsLocationFogged(CoordStruct
    // &
    // &
    // coord)
    // { return IsLocationFogged(coord); }
    // public void RevealCheck(CellClass * pCell, HouseClass * pHouse, bool bUnk)
    RevealCheck(pCell_0 : CellClass, pHouse_1 : HouseClass, bUnk_2 : boolean) : void;
    // returns false if visitor should wait for a gate to open, true otherwise
    // public bool MakeTraversable(ObjectClass const * pVisitor, CellStruct const& cell) const
    MakeTraversable(pVisitor_0 : ObjectClass, cell_1 : CellStruct) : boolean;
    // public void BuildingToFirestormWall(CellStruct const& cell, HouseClass * pHouse, BuildingTypeClass * pBldType)
    BuildingToFirestormWall(cell_0 : CellStruct, pHouse_1 : HouseClass, pBldType_2 : BuildingTypeClass) : void;
    // public void BuildingToWall(CellStruct const& cell, HouseClass * pHouse, BuildingTypeClass * pBldType)
    BuildingToWall(cell_0 : CellStruct, pHouse_1 : HouseClass, pBldType_2 : BuildingTypeClass) : void;
    // Called on wall state updates etc. when the wall hasn't been removed.
    // public void RecalculateZones(CellStruct const& cell)
    RecalculateZones(cell_0 : CellStruct) : void;
    // Called on wall state updates etc. when the wall HAS been removed.
    // public void ResetZones(CellStruct const& cell)
    ResetZones(cell_0 : CellStruct) : void;
    // Called on wall state updates etc
    // public void RecalculateSubZones(CellStruct const& cell)
    RecalculateSubZones(cell_0 : CellStruct) : void;
    // Static
    // public static constant_ptr<MapClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : MapClass;
    // public static reference<CellClass, 11263056, 0> const InvalidCell = 0xABDC50u
    static s_InvalidCell : CellClass;
    // public static int const MaxCells = 0x40000
    static s_MaxCells : number;
    // this actually points to 5 vectors, one for each layer
    // public static reference<LayerClass, 9044832, 5> const ObjectsInLayers = 0x8A0360u
    static s_ObjectsInLayers : LayerClass;
    // <summary
    // >
    // Some sort of hardcoded constant lookup matrix with rows (0-8) representing CellClass Passability(Type) and columns are MovementZones, used to determine pathfinding behaviour.
    // </summary
    // >
    // public static reference<int[13], 8562068, 8> const MovementAdjustArray = 13u
    static s_MovementAdjustArray : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public unsigned long unknown_10
    m_unknown_10 : number;
    // public HashTable<unsigned long, unsigned long> * unknown_pointer_14
    m_unknown_pointer_14 : any;
    // public void *[13] MovementZones
    m_MovementZones : void;
    // public unsigned long somecount_4C
    m_somecount_4C : number;
    // public DynamicVectorClass<ZoneConnectionClass> ZoneConnections
    m_ZoneConnections : DynamicVectorClass<any>;
    // public CellLevelPassabilityStruct * LevelAndPassability
    m_LevelAndPassability : any;
    // public int ValidMapCellCount
    m_ValidMapCellCount : number;
    // public LevelAndPassabilityStruct2 * LevelAndPassabilityStruct2pointer_70
    m_LevelAndPassabilityStruct2pointer_70 : any;
    // public unsigned long unknown_74
    m_unknown_74 : number;
    // public unsigned long unknown_78
    m_unknown_78 : number;
    // public unsigned long unknown_7C
    m_unknown_7C : number;
    // somehow connected to the 3 vectors below
    // public HashTable<unsigned long, SubzoneConnectionStruct> *[3] unknown_80
    m_unknown_80 : any;
    // public DynamicVectorClass<SubzoneTrackingStruct>[3] SubzoneTracking
    m_SubzoneTracking : DynamicVectorClass<any>;
    // public DynamicVectorClass<Vector2D<short>> CellStructs1
    m_CellStructs1 : DynamicVectorClass<Vector2D>;
    // public RectangleStruct MapRect
    m_MapRect : RectangleStruct;
    // public RectangleStruct VisibleRect
    m_VisibleRect : RectangleStruct;
    // public int CellIterator_NextX
    m_CellIterator_NextX : number;
    // public int CellIterator_NextY
    m_CellIterator_NextY : number;
    // public int CellIterator_CurrentY
    m_CellIterator_CurrentY : number;
    // public CellClass * CellIterator_NextCell
    m_CellIterator_NextCell : CellClass;
    // public int ZoneIterator_X
    m_ZoneIterator_X : number;
    // public int ZoneIterator_Y
    m_ZoneIterator_Y : number;
    // the minimum and maximum cell struct values
    // public LTRBStruct MapCoordBounds
    m_MapCoordBounds : LTRBStruct;
    // public int TotalValue
    m_TotalValue : number;
    // public VectorClass<CellClass *> Cells
    m_Cells : VectorClass<CellClass>;
    // public int MaxLevel
    m_MaxLevel : number;
    // public int MaxWidth
    m_MaxWidth : number;
    // public int MaxHeight
    m_MaxHeight : number;
    // public int MaxNumCells
    m_MaxNumCells : number;
    // public Crate[256] Crates
    m_Crates : Crate;
    // public int Redraws
    m_Redraws : number;
    // public DynamicVectorClass<Vector2D<short>> TaggedCells
    m_TaggedCells : DynamicVectorClass<Vector2D>;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// DisplayClass
class DisplayClass
    extends MapClass
{
    // WIP: DisplayClass::TacticalClass goes HERE
    // public bool ProcessClickCoords(Point2D * src, CellStruct * XYdst, CoordStruct * XYZdst, ObjectClass * * Target, unsigned char * a5, unsigned char * a6)
    ProcessClickCoords(src_0 : Point2D, XYdst_1 : CellStruct, XYZdst_2 : CoordStruct, Target_3 : ObjectClass, a5_4 : number, a6_5 : number) : boolean;
    // the foundation for placement with green/red
    // public void SetActiveFoundation(CellStruct const * Coords)
    SetActiveFoundation(Coords_0 : CellStruct) : void;
    // GScreenClass
    // MapClass
    // DisplayClass
    // public virtual long Load(IStream * pStm)
    Load(pStm_0 : any) : number;
    // public virtual long Save(IStream * pStm)
    Save(pStm_0 : any) : number;
    // public virtual void LoadFromINI(CCINIClass * pINI)
    LoadFromINI(pINI_0 : CCINIClass) : void;
    // public virtual wchar_t const * GetToolTip(unsigned int nDlgID)
    GetToolTip(nDlgID_0 : number) : number;
    // public virtual void CloseWindow()
    CloseWindow() : void;
    // public virtual void ClearDragBand()
    ClearDragBand() : void;
    // public virtual bool MapCell(CellStruct * pMapCoord, HouseClass * pHouse)
    MapCell(pMapCoord_0 : CellStruct, pHouse_1 : HouseClass) : boolean;
    // public virtual bool RevealFogShroud(CellStruct * pMapCoord, HouseClass * pHouse, bool bIncreaseShroudCounter)
    RevealFogShroud(pMapCoord_0 : CellStruct, pHouse_1 : HouseClass, bIncreaseShroudCounter_2 : boolean) : boolean;
    // public virtual bool MapCellFoggedness(CellStruct * pMapCoord, HouseClass * pHouse)
    MapCellFoggedness(pMapCoord_0 : CellStruct, pHouse_1 : HouseClass) : boolean;
    // public virtual bool MapCellVisibility(CellStruct * pMapCoord, HouseClass * pHouse)
    MapCellVisibility(pMapCoord_0 : CellStruct, pHouse_1 : HouseClass) : boolean;
    // public virtual MouseCursorType GetLastMouseCursor() = 0
    GetLastMouseCursor() : MouseCursorType;
    // public virtual bool ScrollMap(unsigned long dwUnk1, unsigned long dwUnk2, unsigned long dwUnk3)
    ScrollMap(dwUnk1_0 : number, dwUnk2_1 : number, dwUnk3_2 : number) : boolean;
    // public virtual void Set_View_Dimensions(RectangleStruct const& rect)
    Set_View_Dimensions(rect_0 : RectangleStruct) : void;
    // public virtual void vt_entry_AC(unsigned long dwUnk)
    vt_entry_AC(dwUnk_0 : number) : void;
    // public virtual void RightMouseButtonClick(Point2D * pPoint)
    RightMouseButtonClick(pPoint_0 : Point2D) : void;
    // public virtual void LeftMouseButtonClick(Point2D * pPoint)
    LeftMouseButtonClick(pPoint_0 : Point2D) : void;
    // Decides which mouse pointer to set and then does it.
    // Mouse is over cell pMapCoords which is bShrouded and holds pObject.
    // public virtual bool ConvertAction(CellStruct const& cell, bool bShrouded, ObjectClass * pObject, Action action, bool dwUnk)
    ConvertAction(cell_0 : CellStruct, bShrouded_1 : boolean, pObject_2 : ObjectClass, action_3 : Action, dwUnk_4 : boolean) : boolean;
    // public virtual void LeftMouseButtonDown(Point2D const& point)
    LeftMouseButtonDown(point_0 : Point2D) : void;
    // public virtual void LeftMouseButtonUp(CoordStruct const& coords, CellStruct const& cell, ObjectClass * pObject, Action action, unsigned long dwUnk2)
    LeftMouseButtonUp(coords_0 : CoordStruct, cell_1 : CellStruct, pObject_2 : ObjectClass, action_3 : Action, dwUnk2_4 : number) : void;
    // public virtual void RightMouseButtonUp(unsigned long dwUnk)
    RightMouseButtonUp(dwUnk_0 : number) : void;
    // Non-virtual
    // public Action DecideAction(CellStruct const& cell, ObjectClass * pObject, unsigned long dwUnk)
    DecideAction(cell_0 : CellStruct, pObject_1 : ObjectClass, dwUnk_2 : number) : Action;
    // pass in CurrentFoundationData and receive the width/height of a bounding rectangle in cells
    // public CellStruct * FoundationBoundsSize(CellStruct& outBuffer, CellStruct const * const pFoundationData) const
    FoundationBoundsSize(outBuffer_0 : CellStruct, pFoundationData_1 : CellStruct) : CellStruct;
    // public CellStruct FoundationBoundsSize(CellStruct const * const pFoundationData) const
    FoundationBoundsSize(pFoundationData_0 : CellStruct) : CellStruct;
    // marks or unmarks the cells pointed to by CurrentFoundationData as containing a building
    // public void MarkFoundation(CellStruct * BaseCell, bool Mark)
    MarkFoundation(BaseCell_0 : CellStruct, Mark_1 : boolean) : void;
    // Submit object to layer.
    // public void Submit(ObjectClass * pObject)
    Submit(pObject_0 : ObjectClass) : void;
    // Remove object from layer.
    // public void Remove(ObjectClass * pObject)
    Remove(pObject_0 : ObjectClass) : void;
    // Static
    // public static constant_ptr<DisplayClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : DisplayClass;
    // Currently placing the building here
    // public CellStruct CurrentFoundation_CenterCell
    m_CurrentFoundation_CenterCell : CellStruct;
    // offset from center cell of the current foundation (under the mouse) to the top left cell
    // public CellStruct CurrentFoundation_TopLeftOffset
    m_CurrentFoundation_TopLeftOffset : CellStruct;
    // Foundation data of the building we're currently placing (note: limited to 120 cells)
    // public CellStruct * CurrentFoundation_Data
    m_CurrentFoundation_Data : CellStruct;
    // public bool unknown_1180
    m_unknown_1180 : boolean;
    // public bool unknown_1181
    m_unknown_1181 : boolean;
    // All the Copies are used in the time between clicking and actual execution
    // public CellStruct CurrentFoundationCopy_CenterCell
    m_CurrentFoundationCopy_CenterCell : CellStruct;
    // public CellStruct CurrentFoundationCopy_TopLeftOffset
    m_CurrentFoundationCopy_TopLeftOffset : CellStruct;
    // (note: limited to 50 [!] cells)
    // public CellStruct * CurrentFoundationCopy_Data
    m_CurrentFoundationCopy_Data : CellStruct;
    // public ObjectClass * CurrentBuildingCopy
    m_CurrentBuildingCopy : ObjectClass;
    // public ObjectTypeClass * CurrentBuildingTypeCopy
    m_CurrentBuildingTypeCopy : ObjectTypeClass;
    // public int CurrentBuildingOwnerArrayIndexCopy
    m_CurrentBuildingOwnerArrayIndexCopy : number;
    // public bool FollowObject
    m_FollowObject : boolean;
    // public ObjectClass * ObjectToFollow
    m_ObjectToFollow : ObjectClass;
    // Building we're currently placing
    // public ObjectClass * CurrentBuilding
    m_CurrentBuilding : ObjectClass;
    // Type of that building
    // public ObjectTypeClass * CurrentBuildingType
    m_CurrentBuildingType : ObjectTypeClass;
    // public int CurrentBuildingOwnerArrayIndex
    m_CurrentBuildingOwnerArrayIndex : number;
    // public bool RepairMode
    m_RepairMode : boolean;
    // public bool SellMode
    m_SellMode : boolean;
    // public bool PowerToggleMode
    m_PowerToggleMode : boolean;
    // public bool PlanningMode
    m_PlanningMode : boolean;
    // public bool PlaceBeaconMode
    m_PlaceBeaconMode : boolean;
    // Index of the SuperWeaponType we have currently selected
    // public int CurrentSWTypeIndex
    m_CurrentSWTypeIndex : number;
    // public unsigned long unknown_11BC
    m_unknown_11BC : number;
    // public Point2D unknown_11C0
    m_unknown_11C0 : Point2D;
    // public unsigned long unknown_11C8
    m_unknown_11C8 : number;
    // public bool unknown_bool_11CC
    m_unknown_bool_11CC : boolean;
    // public bool unknown_bool_11CD
    m_unknown_bool_11CD : boolean;
    // public bool unknown_bool_11CE
    m_unknown_bool_11CE : boolean;
    // public bool DraggingRectangle
    m_DraggingRectangle : boolean;
    // public bool unknown_bool_11D0
    m_unknown_bool_11D0 : boolean;
    // public bool unknown_bool_11D1
    m_unknown_bool_11D1 : boolean;
    // public Point2D unknown_11D4
    m_unknown_11D4 : Point2D;
    // public Point2D unknown_11DC
    m_unknown_11DC : Point2D;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// RadarClass
class RadarClass
    extends DisplayClass
{
    // MapClass
    // public virtual void CreateEmptyMap(RectangleStruct const& pMapRect, bool reuse, char nLevel, bool bUnk2)
    CreateEmptyMap(pMapRect_0 : RectangleStruct | any, reuse_1 : boolean | any, nLevel_2 : number | any, bUnk2_3 : boolean | any) : void;
    // public virtual void SetVisibleRect(RectangleStruct const& mapRect)
    SetVisibleRect(mapRect_0 : RectangleStruct | any) : void;
    // RadarClass
    // public virtual void DisposeOfArt()
    DisposeOfArt() : void;
    // public virtual void * vt_entry_CC(void * out_pUnk, Point2D * pPoint)
    vt_entry_CC(out_pUnk_0 : void, pPoint_1 : Point2D) : void;
    // public virtual void vt_entry_D0(unsigned long dwUnk)
    vt_entry_D0(dwUnk_0 : number) : void;
    // public virtual void Init_For_House()
    Init_For_House() : void;
    // Static
    // public static constant_ptr<RadarClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : RadarClass;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public unsigned long unknown_11E8
    m_unknown_11E8 : number;
    // public unsigned long unknown_11EC
    m_unknown_11EC : number;
    // public unsigned long unknown_11F0
    m_unknown_11F0 : number;
    // public unsigned long unknown_11F4
    m_unknown_11F4 : number;
    // public unsigned long unknown_11F8
    m_unknown_11F8 : number;
    // public unsigned long unknown_11FC
    m_unknown_11FC : number;
    // public unsigned long unknown_1200
    m_unknown_1200 : number;
    // public unsigned long unknown_1204
    m_unknown_1204 : number;
    // public unsigned long unknown_1208
    m_unknown_1208 : number;
    // public RectangleStruct unknown_rect_120C
    m_unknown_rect_120C : RectangleStruct;
    // public unsigned long unknown_121C
    m_unknown_121C : number;
    // public unsigned long unknown_1220
    m_unknown_1220 : number;
    // public DynamicVectorClass<Vector2D<short>> unknown_cells_1124
    m_unknown_cells_1124 : DynamicVectorClass<Vector2D>;
    // public unsigned long unknown_123C
    m_unknown_123C : number;
    // public unsigned long unknown_1240
    m_unknown_1240 : number;
    // public unsigned long unknown_1244
    m_unknown_1244 : number;
    // public unsigned long unknown_1248
    m_unknown_1248 : number;
    // public unsigned long unknown_124C
    m_unknown_124C : number;
    // public unsigned long unknown_1250
    m_unknown_1250 : number;
    // public unsigned long unknown_1254
    m_unknown_1254 : number;
    // public HashTable<RadarTrackingStruct, TechnoClass *> * unknown_1258
    m_unknown_1258 : any;
    // public DynamicVectorClass<Vector2D<int>> unknown_points_125C
    m_unknown_points_125C : DynamicVectorClass<Vector2D>;
    // public unsigned long unknown_1274
    m_unknown_1274 : number;
    // public DynamicVectorClass<Vector2D<int>>[22] FoundationTypePixels
    m_FoundationTypePixels : DynamicVectorClass<Vector2D>;
    // public float RadarSizeFactor
    m_RadarSizeFactor : number;
    // public int unknown_int_148C
    m_unknown_int_148C : number;
    // public unsigned long unknown_1490
    m_unknown_1490 : number;
    // public unsigned long unknown_1494
    m_unknown_1494 : number;
    // public unsigned long unknown_1498
    m_unknown_1498 : number;
    // public RectangleStruct unknown_rect_149C
    m_unknown_rect_149C : RectangleStruct;
    // public unsigned long unknown_14AC
    m_unknown_14AC : number;
    // public unsigned long unknown_14B0
    m_unknown_14B0 : number;
    // public unsigned long unknown_14B4
    m_unknown_14B4 : number;
    // public unsigned long unknown_14B8
    m_unknown_14B8 : number;
    // public bool unknown_bool_14BC
    m_unknown_bool_14BC : boolean;
    // public bool unknown_bool_14BD
    m_unknown_bool_14BD : boolean;
    // public unsigned long unknown_14C0
    m_unknown_14C0 : number;
    // public unsigned long unknown_14C4
    m_unknown_14C4 : number;
    // public unsigned long unknown_14C8
    m_unknown_14C8 : number;
    // public unsigned long unknown_14CC
    m_unknown_14CC : number;
    // public unsigned long unknown_14D0
    m_unknown_14D0 : number;
    // public int unknown_int_14D4
    m_unknown_int_14D4 : number;
    // public bool IsAvailableNow
    m_IsAvailableNow : boolean;
    // public bool unknown_bool_14D9
    m_unknown_bool_14D9 : boolean;
    // public bool unknown_bool_14DA
    m_unknown_bool_14DA : boolean;
    // public RectangleStruct unknown_rect_14DC
    m_unknown_rect_14DC : RectangleStruct;
    // public unsigned long unknown_14EC
    m_unknown_14EC : number;
    // public unsigned long unknown_14F0
    m_unknown_14F0 : number;
    // public unsigned long unknown_14F4
    m_unknown_14F4 : number;
    // public unsigned long unknown_14F8
    m_unknown_14F8 : number;
    // public unsigned long unknown_14FC
    m_unknown_14FC : number;
    // public CDTimerClass unknown_timer_1500
    m_unknown_timer_1500 : CDTimerClass;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// PowerClass
class PowerClass
    extends RadarClass
{
    // Static
    // public static constant_ptr<PowerClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : PowerClass;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public bool PowerNeedRedraw
    m_PowerNeedRedraw : boolean;
    // public CDTimerClass unknown_timer_1510
    m_unknown_timer_1510 : CDTimerClass;
    // public unsigned long unknown_151C
    m_unknown_151C : number;
    // public CDTimerClass unknown_timer_1520
    m_unknown_timer_1520 : CDTimerClass;
    // public unsigned long unknown_152C
    m_unknown_152C : number;
    // public unsigned long unknown_1530
    m_unknown_1530 : number;
    // public unsigned long unknown_1534
    m_unknown_1534 : number;
    // public bool unknown_bool_1538
    m_unknown_bool_1538 : boolean;
    // public int PowerOutput
    m_PowerOutput : number;
    // public int PowerDrain
    m_PowerDrain : number;
}
// SidebarClass::StripClass::BuildType
// BuildType
class BuildType
{
    // public BuildType()
    constructor();
    // public BuildType(int itemIndex, AbstractType itemType)
    constructor(itemIndex_0 : number, itemType_1 : AbstractType);
    // public bool operator==(BuildType const& rhs) const
    op_Equality(rhs_0 : BuildType) : boolean;
    // public bool operator!=(BuildType const& rhs) const
    op_Inequality(rhs_0 : BuildType) : boolean;
    // public bool operator<(BuildType const& rhs) const
    op_LessThan(rhs_0 : BuildType) : boolean;
    // public static bool SortsBefore(AbstractType leftType, int leftIndex, AbstractType rightType, int rightIndex)
    static SortsBefore(leftType_0 : AbstractType, leftIndex_1 : number, rightType_2 : AbstractType, rightIndex_3 : number) : boolean;
    // public int ItemIndex
    m_ItemIndex : number;
    // public AbstractType ItemType
    m_ItemType : AbstractType;
    // set on buildings that go on tab 2
    // public bool IsAlt
    m_IsAlt : boolean;
    // public FactoryClass * CurrentFactory
    m_CurrentFactory : FactoryClass;
    // public unsigned long unknown_10
    m_unknown_10 : number;
    // 0 to 54, how much of this object is constructed (gclock anim level)
    // public StageClass Progress
    m_Progress : StageClass;
    // public int FlashEndFrame
    m_FlashEndFrame : number;
}
// SidebarClass::StripClass
// StripClass
class StripClass
{
    // public StageClass Progress
    m_Progress : StageClass;
    // prevents redrawing when layouting the list
    // public bool AllowedToDraw
    m_AllowedToDraw : boolean;
    // public Point2D Location
    m_Location : Point2D;
    // public RectangleStruct Bounds
    m_Bounds : RectangleStruct;
    // the index of this tab
    // public int Index
    m_Index : number;
    // public bool NeedsRedraw
    m_NeedsRedraw : boolean;
    // public unsigned char unknown_3D
    m_unknown_3D : number;
    // public unsigned char unknown_3E
    m_unknown_3E : number;
    // public unsigned char unknown_3F
    m_unknown_3F : number;
    // public unsigned long unknown_40
    m_unknown_40 : number;
    // scroll position, which row is topmost visible
    // public int TopRowIndex
    m_TopRowIndex : number;
    // public unsigned long unknown_48
    m_unknown_48 : number;
    // public unsigned long unknown_4C
    m_unknown_4C : number;
    // public unsigned long unknown_50
    m_unknown_50 : number;
    // filled cameos
    // public int CameoCount
    m_CameoCount : number;
    // public BuildType[75] Cameos
    m_Cameos : BuildType;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// SidebarClass
class SidebarClass
    extends PowerClass
{
    // public void SidebarNeedsRepaint(int mode = 0)
    SidebarNeedsRepaint(mode_0 : number) : void;
    // public void RepaintSidebar(int tab = 0)
    RepaintSidebar(tab_0 : number) : void;
    // public bool AddCameo(AbstractType absType, int idxType)
    AddCameo(absType_0 : AbstractType, idxType_1 : number) : boolean;
    // public virtual void Draw(unsigned long dwUnk)
    Draw(dwUnk_0 : number | any) : void;
    // SidebarClass
    // public virtual bool vt_entry_D8(int nUnknown)
    vt_entry_D8(nUnknown_0 : number) : boolean;
    // which tab does the 'th object of that type belong in?
    // public static int GetObjectTabIdx(AbstractType abs, int idxType, int unused)
    static GetObjectTabIdx(abs_0 : AbstractType, idxType_1 : number, unused_2 : number) : number;
    // which tab does the 'th object of that type belong in?
    // public static int GetObjectTabIdx(AbstractType abs, BuildCat buildCat, bool isNaval)
    static GetObjectTabIdx(abs_0 : AbstractType, buildCat_1 : BuildCat, isNaval_2 : boolean) : number;
    // public bool Scroll(bool up, int column)
    Scroll(up_0 : boolean, column_1 : number) : boolean;
    // Static
    // public static constant_ptr<SidebarClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : SidebarClass;
    // public static reference<wchar_t, 11566020, 66> const TooltipBuffer = 0xB07BC4u
    static s_TooltipBuffer : number;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public StripClass[4] Tabs
    m_Tabs : StripClass;
    // public unsigned long unknown_5394
    m_unknown_5394 : number;
    // public unsigned long unknown_5398
    m_unknown_5398 : number;
    // public int ActiveTabIndex
    m_ActiveTabIndex : number;
    // public unsigned long unknown_53A0
    m_unknown_53A0 : number;
    // see 0x6A9343
    // public bool HideObjectNameInTooltip
    m_HideObjectNameInTooltip : boolean;
    // public bool IsSidebarActive
    m_IsSidebarActive : boolean;
    // public bool SidebarNeedsRedraw
    m_SidebarNeedsRedraw : boolean;
    // public bool SidebarBackgroundNeedsRedraw
    m_SidebarBackgroundNeedsRedraw : boolean;
    // public bool unknown_bool_53A8
    m_unknown_bool_53A8 : boolean;
    // 8 players max!
    // public HouseClass *[8] DiplomacyHouses
    m_DiplomacyHouses : HouseClass;
    // total amount of kills per house
    // public int[8] DiplomacyKills
    m_DiplomacyKills : number;
    // total amount of currently owned unit/buildings per house
    // public int[8] DiplomacyOwned
    m_DiplomacyOwned : number;
    // current power drain per house
    // public int[8] DiplomacyPowerDrain
    m_DiplomacyPowerDrain : number;
    // color scheme per house
    // public ColorScheme *[8] DiplomacyColors
    m_DiplomacyColors : ColorScheme;
    // ??? per house - unused
    // public unsigned long[8] unknown_544C
    m_unknown_544C : number;
    // ??? per house - unused
    // public unsigned long[8] unknown_546C
    m_unknown_546C : number;
    // ??? per house - unused
    // public unsigned long[8] unknown_548C
    m_unknown_548C : number;
    // ??? per house - unused
    // public unsigned long[8] unknown_54AC
    m_unknown_54AC : number;
    // ??? per house - unused
    // public unsigned long[8] unknown_54CC
    m_unknown_54CC : number;
    // ??? per house - unused
    // public unsigned long[8] unknown_54EC
    m_unknown_54EC : number;
    // public unsigned char unknown_550C
    m_unknown_550C : number;
    // possibly?
    // public int DiplomacyNumHouses
    m_DiplomacyNumHouses : number;
    // public bool unknown_bool_5514
    m_unknown_bool_5514 : boolean;
    // public bool unknown_bool_5515
    m_unknown_bool_5515 : boolean;
}
// TabDataClass
class TabDataClass
{
    // public int TargetValue
    m_TargetValue : number;
    // public int LastValue
    m_LastValue : number;
    // public bool NeedsRedraw
    m_NeedsRedraw : boolean;
    // public bool ValueIncreased
    m_ValueIncreased : boolean;
    // public bool ValueChanged
    m_ValueChanged : boolean;
    // public int ValueDelta
    m_ValueDelta : number;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// TabClass
class TabClass
    extends SidebarClass
{
    // non-virtual
    // public void Activate(int control = 1)
    Activate(control_0 : number) : void;
    // Static
    // public static constant_ptr<TabClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : TabClass;
    // public TabDataClass TabData
    m_TabData : TabDataClass;
    // public CDTimerClass unknown_timer_552C
    m_unknown_timer_552C : CDTimerClass;
    // public CDTimerClass InsufficientFundsBlinkTimer
    m_InsufficientFundsBlinkTimer : CDTimerClass;
    // public unsigned char unknown_byte_5544
    m_unknown_byte_5544 : number;
    // public bool MissionTimerPinged
    m_MissionTimerPinged : boolean;
    // public unsigned char unknown_byte_5546
    m_unknown_byte_5546 : number;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// ScrollClass
class ScrollClass
    extends TabClass
{
    // Static
    // public static constant_ptr<ScrollClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : ScrollClass;
    // public unsigned long unknown_int_5548
    m_unknown_int_5548 : number;
    // public unsigned char unknown_byte_554C
    m_unknown_byte_554C : number;
    // public unsigned long unknown_int_5550
    m_unknown_int_5550 : number;
    // public unsigned long unknown_int_5554
    m_unknown_int_5554 : number;
    // public unsigned char unknown_byte_5548
    m_unknown_byte_5548 : number;
    // public unsigned char unknown_byte_5549
    m_unknown_byte_5549 : number;
    // public unsigned char unknown_byte_554A
    m_unknown_byte_554A : number;
}
// typedef struct tagCONNECTDATA
// {
// IUnknown* pUnk;
// unsigned long dwCookie;
// }	CONNECTDATA;
// __interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnections : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
// };
// __interface IConnectionPointContainer;
// __interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPoint : IUnknown
// {
// virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
// virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
// virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
// virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
// virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
// };
// __interface IEnumConnectionPoints;
// __interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
// IConnectionPointContainer : IUnknown
// {
// virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
// virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
// };
// __interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
// IEnumConnectionPoints : IUnknown
// {
// virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
// virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
// virtual HRESULT __stdcall Reset() = 0;
// virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
// };
// MouseClass
class MouseClass
    extends ScrollClass
{
    // GScreenClass
    // public virtual bool SetCursor(MouseCursorType idxCursor, bool miniMap)
    SetCursor(idxCursor_0 : MouseCursorType | any, miniMap_1 : boolean | any) : boolean;
    // public virtual bool UpdateCursor(MouseCursorType idxCursor, bool miniMap)
    UpdateCursor(idxCursor_0 : MouseCursorType | any, miniMap_1 : boolean | any) : boolean;
    // public virtual bool RestoreCursor()
    RestoreCursor() : boolean;
    // public virtual void UpdateCursorMinimapState(bool miniMap)
    UpdateCursorMinimapState(miniMap_0 : boolean | any) : void;
    // DisplayClass
    // public virtual MouseCursorType GetLastMouseCursor()
    GetLastMouseCursor() : MouseCursorType;
    // Static
    // public static constant_ptr<MouseClass, 8910824> const Instance = 0x87F7E8u
    static s_Instance : MouseClass;
    // public bool MouseCursorIsMini
    m_MouseCursorIsMini : boolean;
    // public MouseCursorType MouseCursorIndex
    m_MouseCursorIndex : MouseCursorType;
    // public MouseCursorType MouseCursorLastIndex
    m_MouseCursorLastIndex : MouseCursorType;
    // public int MouseCursorCurrentFrame
    m_MouseCursorCurrentFrame : number;
}
// SpotlightClass
class SpotlightClass
{
    // Constructor
    // public SpotlightClass(CoordStruct coords, int size)
    constructor(coords_0 : CoordStruct, size_1 : number);
    // public void Draw()
    Draw() : void;
    // public void Update()
    Update() : void;
    // public static void DrawAll()
    static DrawAll() : void;
    // skip operator new
    // skip operator delete
    // Static
    // public static constant_ptr<DynamicVectorClass<SpotlightClass *>, 11277944> const Array = 0xAC1678u
    static s_Array : DynamicVectorClass<SpotlightClass>;
    // ===========================================================================
    // ===== Properties ==========================================================
    // ===========================================================================
    // public CoordStruct Coords
    m_Coords : CoordStruct;
    // public int MovementRadius
    m_MovementRadius : number;
    // public int Size
    m_Size : number;
    // public SpotlightFlags DisableFlags
    m_DisableFlags : SpotlightFlags;
}
// ThemeControl
class ThemeControl
{
    // public FixedString<256, char> ID
    m_ID : any;
    // public FixedString<256, char> Sound
    m_Sound : any;
    // public FixedString<64, wchar_t> UIName
    m_UIName : any;
    // public int Scenario
    m_Scenario : number;
    // public float Length
    m_Length : number;
    // public bool Normal
    m_Normal : boolean;
    // public bool Repeat
    m_Repeat : boolean;
    // public bool Exists
    m_Exists : boolean;
    // public int Side
    m_Side : number;
}
// ThemeClass
class ThemeClass
{
    // public char const * GetID(unsigned int index) const
    GetID(index_0 : number) : string;
    // public char const * GetName(unsigned int index) const
    GetName(index_0 : number) : string;
    // public char const * GetFilename(unsigned int index) const
    GetFilename(index_0 : number) : string;
    // public wchar_t const * GetUIName(unsigned int index) const
    GetUIName(index_0 : number) : number;
    // public int GetLength(unsigned int index) const
    GetLength(index_0 : number) : number;
    // public bool IsAvailable(int index) const
    IsAvailable(index_0 : number) : boolean;
    // public bool IsNormal(int index) const
    IsNormal(index_0 : number) : boolean;
    // public int FindIndex(char const * pID) const
    FindIndex(pID_0 : string) : number;
    // public int GetRandomIndex(unsigned int lastTheme) const
    GetRandomIndex(lastTheme_0 : number) : number;
    // public void Queue(int index)
    Queue(index_0 : number) : void;
    // public int Play(int index)
    Play(index_0 : number) : number;
    // public void Stop(bool fade = false)
    Stop(fade_0 : boolean) : void;
    // public void Suspend()
    Suspend() : void;
    // public void AI()
    AI() : void;
    // public void Scan()
    Scan() : void;
    // public static reference<ThemeClass, 11025680, 0> const Instance = 0xA83D10
    static s_Instance : ThemeClass;
    // public static reference<bool, 11070580, 0> const ScoresPresen = 0xA8EC74
    static s_ScoresPresen : boolean;
    // the playing theme's index
    // public int CurrentTheme
    m_CurrentTheme : number;
    // the theme that cannot be selected randomly
    // public int LastTheme
    m_LastTheme : number;
    // the next theme to be played
    // public int QueuedTheme
    m_QueuedTheme : number;
    // public int Volume
    m_Volume : number;
    // public bool IsScoreRepeat
    m_IsScoreRepeat : boolean;
    // public bool IsFading
    m_IsFading : boolean;
    // public bool IsScoreShuffle
    m_IsScoreShuffle : boolean;
    // the list of all themes
    // public DynamicVectorClass<ThemeControl *> Themes
    m_Themes : DynamicVectorClass<ThemeControl>;
    // public AudioStream * Stream
    m_Stream : any;
}
// SlaveManagerClass::SlaveControl
class SlaveManagerClass__SlaveControl
{
    // public InfantryClass * Slave
    m_Slave : InfantryClass;
    // public SlaveControlStatus State
    m_State : SlaveControlStatus;
    // public CDTimerClass RespawnTimer
    m_RespawnTimer : CDTimerClass;
}

class YRpp {
    static s_Unsorted__CurrentFrame : number;
    static s_Unsorted__CellHeight : number;
    static s_Unsorted__LevelHeight : number;
    static s_Unsorted__LeptonsPerCell : number;
    static s_Unsorted__CellWidthInPixels : number;
    static s_Unsorted__CellHeightInPixels : number;
    static s_Unsorted__CurrentSWType : number;
    static s_Unsorted__IKnowWhatImDoing : number;
}
// DirType
enum DirType {
    // North = 0<<5
    North = 0,
    // NorthEast = 1<<5
    NorthEast = 32,
    // East = 2<<5
    East = 64,
    // SouthEast = 3<<5
    SouthEast = 96,
    // South = 4<<5
    South = -128,
    // SouthWest = 5<<5
    SouthWest = -96,
    // West = 6<<5
    West = -64,
    // NorthWest = 7<<5
    NorthWest = -32,
    // Max = 255
    Max = -1,
}
// AbstractFlags
enum AbstractFlags {
    // None = 0x0
    None = 0,
    // Techno = 0x1
    Techno = 1,
    // Object = 0x2
    Object = 2,
    // Foot = 0x4
    Foot = 4,
}
// AbstractType
enum AbstractType {
    // None = 0
    None = 0,
    // Unit = 1
    Unit = 1,
    // Aircraft = 2
    Aircraft = 2,
    // AircraftType = 3
    AircraftType = 3,
    // Anim = 4
    Anim = 4,
    // AnimType = 5
    AnimType = 5,
    // Building = 6
    Building = 6,
    // BuildingType = 7
    BuildingType = 7,
    // Bullet = 8
    Bullet = 8,
    // BulletType = 9
    BulletType = 9,
    // Campaign = 10
    Campaign = 10,
    // Cell = 11
    Cell = 11,
    // Factory = 12
    Factory = 12,
    // House = 13
    House = 13,
    // HouseType = 14
    HouseType = 14,
    // Infantry = 15
    Infantry = 15,
    // InfantryType = 16
    InfantryType = 16,
    // Isotile = 17
    Isotile = 17,
    // IsotileType = 18
    IsotileType = 18,
    // BuildingLight = 19
    BuildingLight = 19,
    // Overlay = 20
    Overlay = 20,
    // OverlayType = 21
    OverlayType = 21,
    // Particle = 22
    Particle = 22,
    // ParticleType = 23
    ParticleType = 23,
    // ParticleSystem = 24
    ParticleSystem = 24,
    // ParticleSystemType = 25
    ParticleSystemType = 25,
    // Script = 26
    Script = 26,
    // ScriptType = 27
    ScriptType = 27,
    // Side = 28
    Side = 28,
    // Smudge = 29
    Smudge = 29,
    // SmudgeType = 30
    SmudgeType = 30,
    // Special = 31
    Special = 31,
    // SuperWeaponType = 32
    SuperWeaponType = 32,
    // TaskForce = 33
    TaskForce = 33,
    // Team = 34
    Team = 34,
    // TeamType = 35
    TeamType = 35,
    // Terrain = 36
    Terrain = 36,
    // TerrainType = 37
    TerrainType = 37,
    // Trigger = 38
    Trigger = 38,
    // TriggerType = 39
    TriggerType = 39,
    // UnitType = 40
    UnitType = 40,
    // VoxelAnim = 41
    VoxelAnim = 41,
    // VoxelAnimType = 42
    VoxelAnimType = 42,
    // Wave = 43
    Wave = 43,
    // Tag = 44
    Tag = 44,
    // TagType = 45
    TagType = 45,
    // Tiberium = 46
    Tiberium = 46,
    // Action = 47
    Action = 47,
    // Event = 48
    Event = 48,
    // WeaponType = 49
    WeaponType = 49,
    // WarheadType = 50
    WarheadType = 50,
    // Waypoint = 51
    Waypoint = 51,
    // Abstract = 52
    Abstract = 52,
    // Tube = 53
    Tube = 53,
    // LightSource = 54
    LightSource = 54,
    // EMPulse = 55
    EMPulse = 55,
    // TacticalMap = 56
    TacticalMap = 56,
    // Super = 57
    Super = 57,
    // AITrigger = 58
    AITrigger = 58,
    // AITriggerType = 59
    AITriggerType = 59,
    // Neuron = 60
    Neuron = 60,
    // FoggedObject = 61
    FoggedObject = 61,
    // AlphaShape = 62
    AlphaShape = 62,
    // VeinholeMonster = 63
    VeinholeMonster = 63,
    // NavyType = 64
    NavyType = 64,
    // SpawnManager = 65
    SpawnManager = 65,
    // CaptureManager = 66
    CaptureManager = 66,
    // Parasite = 67
    Parasite = 67,
    // Bomb = 68
    Bomb = 68,
    // RadSite = 69
    RadSite = 69,
    // Temporal = 70
    Temporal = 70,
    // Airstrike = 71
    Airstrike = 71,
    // SlaveManager = 72
    SlaveManager = 72,
    // DiskLaser = 73
    DiskLaser = 73,
}
// RecordFlag
enum RecordFlag {
    // I am recording the game now
    // Write = 0x1
    Write = 1,
    // I am playing a recorded game now
    // Read = 0x2
    Read = 2,
    // Recording enabled by commmand line
    // Attract = 0x4
    Attract = 4,
}
// Action
enum Action {
    // None = 0
    None = 0,
    // Move = 1
    Move = 1,
    // NoMove = 2
    NoMove = 2,
    // Enter = 3
    Enter = 3,
    // Self_Deploy = 4
    Self_Deploy = 4,
    // Attack = 5
    Attack = 5,
    // Harvest = 6
    Harvest = 6,
    // Select = 7
    Select = 7,
    // ToggleSelect = 8
    ToggleSelect = 8,
    // Capture = 9
    Capture = 9,
    // Eaten = 10
    Eaten = 10,
    // Repair = 11
    Repair = 11,
    // Sell = 12
    Sell = 12,
    // SellUnit = 13
    SellUnit = 13,
    // NoSell = 14
    NoSell = 14,
    // NoRepair = 15
    NoRepair = 15,
    // Sabotage = 16
    Sabotage = 16,
    // Tote = 17
    Tote = 17,
    // DontUse2 = 18
    DontUse2 = 18,
    // DontUse3 = 19
    DontUse3 = 19,
    // Nuke = 20
    Nuke = 20,
    // DontUse4 = 21
    DontUse4 = 21,
    // DontUse5 = 22
    DontUse5 = 22,
    // DontUse6 = 23
    DontUse6 = 23,
    // DontUse7 = 24
    DontUse7 = 24,
    // DontUse8 = 25
    DontUse8 = 25,
    // GuardArea = 26
    GuardArea = 26,
    // Heal = 27
    Heal = 27,
    // Damage = 28
    Damage = 28,
    // GRepair = 29
    GRepair = 29,
    // NoDeploy = 30
    NoDeploy = 30,
    // NoEnter = 31
    NoEnter = 31,
    // NoGRepair = 32
    NoGRepair = 32,
    // TogglePower = 33
    TogglePower = 33,
    // NoTogglePower = 34
    NoTogglePower = 34,
    // EnterTunnel = 35
    EnterTunnel = 35,
    // NoEnterTunnel = 36
    NoEnterTunnel = 36,
    // IronCurtain = 37
    IronCurtain = 37,
    // LightningStorm = 38
    LightningStorm = 38,
    // ChronoSphere = 39
    ChronoSphere = 39,
    // ChronoWarp = 40
    ChronoWarp = 40,
    // ParaDrop = 41
    ParaDrop = 41,
    // PlaceWaypoint = 42
    PlaceWaypoint = 42,
    // TibSunBug = 43
    TibSunBug = 43,
    // EnterWaypointMode = 44
    EnterWaypointMode = 44,
    // FollowWaypoint = 45
    FollowWaypoint = 45,
    // SelectWaypoint = 46
    SelectWaypoint = 46,
    // LoopWaypointPath = 47
    LoopWaypointPath = 47,
    // DragWaypoint = 48
    DragWaypoint = 48,
    // AttackWaypoint = 49
    AttackWaypoint = 49,
    // EnterWaypoint = 50
    EnterWaypoint = 50,
    // PatrolWaypoint = 51
    PatrolWaypoint = 51,
    // AreaAttack = 52
    AreaAttack = 52,
    // IvanBomb = 53
    IvanBomb = 53,
    // NoIvanBomb = 54
    NoIvanBomb = 54,
    // Detonate = 55
    Detonate = 55,
    // DetonateAll = 56
    DetonateAll = 56,
    // DisarmBomb = 57
    DisarmBomb = 57,
    // SelectNode = 58
    SelectNode = 58,
    // AttackSupport = 59
    AttackSupport = 59,
    // PlaceBeacon = 60
    PlaceBeacon = 60,
    // SelectBeacon = 61
    SelectBeacon = 61,
    // AttackMoveNav = 62
    AttackMoveNav = 62,
    // AttackMoveTar = 63
    AttackMoveTar = 63,
    // Demolish = 64
    Demolish = 64,
    // AmerParaDrop = 65
    AmerParaDrop = 65,
    // PsychicDominator = 66
    PsychicDominator = 66,
    // SpyPlane = 67
    SpyPlane = 67,
    // GeneticConverter = 68
    GeneticConverter = 68,
    // ForceShield = 69
    ForceShield = 69,
    // NoForceShield = 70
    NoForceShield = 70,
    // Airstrike = 71
    Airstrike = 71,
    // PsychicReveal = 72
    PsychicReveal = 72,
}
// Ability
enum Ability {
    // Faster = 0
    Faster = 0,
    // Stronger = 1
    Stronger = 1,
    // Firepower = 2
    Firepower = 2,
    // Scatter = 3
    Scatter = 3,
    // ROF = 4
    ROF = 4,
    // Sight = 5
    Sight = 5,
    // Cloak = 6
    Cloak = 6,
    // TiberiumProof = 7
    TiberiumProof = 7,
    // VeinProof = 8
    VeinProof = 8,
    // SelfHeal = 9
    SelfHeal = 9,
    // Explodes = 10
    Explodes = 10,
    // RadarInvisible = 11
    RadarInvisible = 11,
    // Sensors = 12
    Sensors = 12,
    // Fearless = 13
    Fearless = 13,
    // C4 = 14
    C4 = 14,
    // TiberiumHeal = 15
    TiberiumHeal = 15,
    // GuardArea = 16
    GuardArea = 16,
    // Crusher = 17
    Crusher = 17,
}
// AIDifficulty
enum AIDifficulty {
    // Hard = 0
    Hard = 0,
    // Normal = 1
    Normal = 1,
    // Easy = 2
    Easy = 2,
}
// TextPrintType
enum TextPrintType {
    // *
    // LASTPOINT = 0x0
    LASTPOINT = 0,
    // *
    // LASTSHADOW = 0x0
    LASTSHADOW = 0,
    // *
    // Point6 = 0x1
    Point6 = 1,
    // Point8 = 0x2
    Point8 = 2,
    // *
    // Point3 = 0x3
    Point3 = 3,
    // *
    // Led = 0x4
    Led = 4,
    // *
    // Vcr = 0x5
    Vcr = 5,
    // Point6Grad = 0x6
    Point6Grad = 6,
    // *
    // Map = 0x7
    Map = 7,
    // Metal12 = 0x8
    Metal12 = 8,
    // *
    // Efnt = 0x9
    Efnt = 9,
    // *
    // Type = 0xA
    Type = 10,
    // *
    // Score = 0xB
    Score = 11,
    // *
    // Fonts = 0xF
    Fonts = 15,
    // NoShadow = 0x10
    NoShadow = 16,
    // DropShadow = 0x20
    DropShadow = 32,
    // FullShadow = 0x40
    FullShadow = 64,
    // LightShadow = 0x80
    LightShadow = 128,
    // Center = 0x100
    Center = 256,
    // Right = 0x200
    Right = 512,
    // Background = 0x400
    Background = 1024,
    // MediumColor = 0x1000
    MediumColor = 4096,
    // BrightColor = 0x2000
    BrightColor = 8192,
    // UseGradPal = 0x4000
    UseGradPal = 16384,
    // UnknownColor = 0x8000
    UnknownColor = 32768,
    // GradAll = 0xF000
    GradAll = 61440,
}
// TriggerPersistence
enum TriggerPersistence {
    // trigger for the first object whose events fired, then disable
    // Volatile = 0
    Volatile = 0,
    // trigger after all object's events fired, then disable
    // SemiPersistant = 1
    SemiPersistant = 1,
    // trigger every time events fire for any object, never disable
    // Persistent = 2
    Persistent = 2,
}
// TriggerEvent
enum TriggerEvent {
    // None = 0x0
    None = 0,
    // EnteredBy = 0x1
    EnteredBy = 1,
    // SpiedBy = 0x2
    SpiedBy = 2,
    // ThievedBy = 0x3
    ThievedBy = 3,
    // DiscoveredByPlayer = 0x4
    DiscoveredByPlayer = 4,
    // HouseDiscovered = 0x5
    HouseDiscovered = 5,
    // AttackedByAnybody = 0x6
    AttackedByAnybody = 6,
    // DestroyedByAnybody = 0x7
    DestroyedByAnybody = 7,
    // AnyEvent = 0x8
    AnyEvent = 8,
    // DestroyedUnitsAll = 0x9
    DestroyedUnitsAll = 9,
    // DestroyedBuildingsAll = 0xA
    DestroyedBuildingsAll = 10,
    // DestroyedAll = 0xB
    DestroyedAll = 11,
    // CreditsExceed = 0xC
    CreditsExceed = 12,
    // ElapsedTime = 0xD
    ElapsedTime = 13,
    // MissionTimerExpired = 0xE
    MissionTimerExpired = 14,
    // DestroyedBuildingsNum = 0xF
    DestroyedBuildingsNum = 15,
    // DestroyedUnitsNum = 0x10
    DestroyedUnitsNum = 16,
    // NoFactoriesLeft = 0x11
    NoFactoriesLeft = 17,
    // CiviliansEvacuated = 0x12
    CiviliansEvacuated = 18,
    // BuildBuildingType = 0x13
    BuildBuildingType = 19,
    // BuildUnitType = 0x14
    BuildUnitType = 20,
    // BuildInfantryType = 0x15
    BuildInfantryType = 21,
    // BuildAircraftType = 0x16
    BuildAircraftType = 22,
    // TeamLeavesMap = 0x17
    TeamLeavesMap = 23,
    // ZoneEntryBy = 0x18
    ZoneEntryBy = 24,
    // CrossesHorizontalLine = 0x19
    CrossesHorizontalLine = 25,
    // CrossesVerticalLine = 0x1A
    CrossesVerticalLine = 26,
    // GlobalSet = 0x1B
    GlobalSet = 27,
    // GlobalCleared = 0x1C
    GlobalCleared = 28,
    // DestroyedFakesAll = 0x1D
    DestroyedFakesAll = 29,
    // LowPower = 0x1E
    LowPower = 30,
    // AllBridgesDestroyed = 0x1F
    AllBridgesDestroyed = 31,
    // BuildingExists = 0x20
    BuildingExists = 32,
    // SelectedByPlayer = 0x21
    SelectedByPlayer = 33,
    // ComesNearWaypoint = 0x22
    ComesNearWaypoint = 34,
    // EnemyInSpotlight = 0x23
    EnemyInSpotlight = 35,
    // LocalSet = 0x24
    LocalSet = 36,
    // LocalCleared = 0x25
    LocalCleared = 37,
    // FirstDamaged_combatonly = 0x26
    FirstDamaged_combatonly = 38,
    // HalfHealth_combatonly = 0x27
    HalfHealth_combatonly = 39,
    // QuarterHealth_combatonly = 0x28
    QuarterHealth_combatonly = 40,
    // FirstDamaged_anysource = 0x29
    FirstDamaged_anysource = 41,
    // HalfHealth_anysource = 0x2A
    HalfHealth_anysource = 42,
    // QuarterHealth_anysource = 0x2B
    QuarterHealth_anysource = 43,
    // AttackedByHouse = 0x2C
    AttackedByHouse = 44,
    // AmbientLightBelow = 0x2D
    AmbientLightBelow = 45,
    // AmbientLightAbove = 0x2E
    AmbientLightAbove = 46,
    // ElapsedScenarioTime = 0x2F
    ElapsedScenarioTime = 47,
    // DestroyedByAnything = 0x30
    DestroyedByAnything = 48,
    // PickupCrate = 0x31
    PickupCrate = 49,
    // PickupCrate_any = 0x32
    PickupCrate_any = 50,
    // RandomDelay = 0x33
    RandomDelay = 51,
    // CreditsBelow = 0x34
    CreditsBelow = 52,
    // SpyAsHouse = 0x35
    SpyAsHouse = 53,
    // SpyAsInfantry = 0x36
    SpyAsInfantry = 54,
    // DestroyedUnitsNaval = 0x37
    DestroyedUnitsNaval = 55,
    // DestroyedUnitsLand = 0x38
    DestroyedUnitsLand = 56,
    // BuildingDoesNotExist = 0x39
    BuildingDoesNotExist = 57,
    // PowerFull = 0x3A
    PowerFull = 58,
    // EnteredOrOverflownBy = 0x3B
    EnteredOrOverflownBy = 59,
    // TechTypeExists = 0x3C
    TechTypeExists = 60,
    // TechTypeDoesntExist = 0x3D
    TechTypeDoesntExist = 61,
}
// TriggerAction
enum TriggerAction {
    // None = 0x0
    None = 0,
    // Win = 0x1
    Win = 1,
    // Lose = 0x2
    Lose = 2,
    // ProductionBegins = 0x3
    ProductionBegins = 3,
    // CreateTeam = 0x4
    CreateTeam = 4,
    // DestroyTeam = 0x5
    DestroyTeam = 5,
    // AllToHunt = 0x6
    AllToHunt = 6,
    // Reinforcement = 0x7
    Reinforcement = 7,
    // DropZoneFlare = 0x8
    DropZoneFlare = 8,
    // FireSale = 0x9
    FireSale = 9,
    // PlayMovie = 0xA
    PlayMovie = 10,
    // TextTrigger = 0xB
    TextTrigger = 11,
    // DestroyTrigger = 0xC
    DestroyTrigger = 12,
    // AutocreateBegins = 0xD
    AutocreateBegins = 13,
    // ChangeHouse = 0xE
    ChangeHouse = 14,
    // AllowWin = 0xF
    AllowWin = 15,
    // RevealAllMap = 0x10
    RevealAllMap = 16,
    // RevealAroundWaypoint = 0x11
    RevealAroundWaypoint = 17,
    // RevealWaypointZone = 0x12
    RevealWaypointZone = 18,
    // PlaySoundEffect = 0x13
    PlaySoundEffect = 19,
    // PlayMusicTheme = 0x14
    PlayMusicTheme = 20,
    // PlaySpeech = 0x15
    PlaySpeech = 21,
    // ForceTrigger = 0x16
    ForceTrigger = 22,
    // TimerStart = 0x17
    TimerStart = 23,
    // TimerStop = 0x18
    TimerStop = 24,
    // TimerExtend = 0x19
    TimerExtend = 25,
    // TimerShorten = 0x1A
    TimerShorten = 26,
    // TimerSet = 0x1B
    TimerSet = 27,
    // GlobalSet = 0x1C
    GlobalSet = 28,
    // GlobalClear = 0x1D
    GlobalClear = 29,
    // AutoBaseBuilding = 0x1E
    AutoBaseBuilding = 30,
    // GrowShroud = 0x1F
    GrowShroud = 31,
    // DestroyAttachedObject = 0x20
    DestroyAttachedObject = 32,
    // AddOneTimeSuperWeapon = 0x21
    AddOneTimeSuperWeapon = 33,
    // AddRepeatingSuperWeapon = 0x22
    AddRepeatingSuperWeapon = 34,
    // PreferredTarget = 0x23
    PreferredTarget = 35,
    // AllChangeHouse = 0x24
    AllChangeHouse = 36,
    // MakeAlly = 0x25
    MakeAlly = 37,
    // MakeEnemy = 0x26
    MakeEnemy = 38,
    // ChangeZoomLevel = 0x27
    ChangeZoomLevel = 39,
    // ResizePlayerView = 0x28
    ResizePlayerView = 40,
    // PlayAnimAt = 0x29
    PlayAnimAt = 41,
    // DoExplosionAt = 0x2A
    DoExplosionAt = 42,
    // CreateVoxelAnim = 0x2B
    CreateVoxelAnim = 43,
    // IonStormStart = 0x2C
    IonStormStart = 44,
    // IonStormStop = 0x2D
    IonStormStop = 45,
    // LockInput = 0x2E
    LockInput = 46,
    // UnlockInput = 0x2F
    UnlockInput = 47,
    // MoveCameraToWaypoint = 0x30
    MoveCameraToWaypoint = 48,
    // ZoomIn = 0x31
    ZoomIn = 49,
    // ZoomOut = 0x32
    ZoomOut = 50,
    // ReshroudMap = 0x33
    ReshroudMap = 51,
    // ChangeLightBehavior = 0x34
    ChangeLightBehavior = 52,
    // EnableTrigger = 0x35
    EnableTrigger = 53,
    // DisableTrigger = 0x36
    DisableTrigger = 54,
    // CreateRadarEvent = 0x37
    CreateRadarEvent = 55,
    // LocalSet = 0x38
    LocalSet = 56,
    // LocalClear = 0x39
    LocalClear = 57,
    // MeteorShower = 0x3A
    MeteorShower = 58,
    // ReduceTiberium = 0x3B
    ReduceTiberium = 59,
    // SellBuilding = 0x3C
    SellBuilding = 60,
    // TurnOffBuilding = 0x3D
    TurnOffBuilding = 61,
    // TurnOnBuilding = 0x3E
    TurnOnBuilding = 62,
    // Apply100Damage = 0x3F
    Apply100Damage = 63,
    // SmallLightFlash = 0x40
    SmallLightFlash = 64,
    // MediumLightFlash = 0x41
    MediumLightFlash = 65,
    // LargeLightFlash = 0x42
    LargeLightFlash = 66,
    // AnnounceWin = 0x43
    AnnounceWin = 67,
    // AnnounceLose = 0x44
    AnnounceLose = 68,
    // ForceEnd = 0x45
    ForceEnd = 69,
    // DestroyTag = 0x46
    DestroyTag = 70,
    // SetAmbientStep = 0x47
    SetAmbientStep = 71,
    // SetAmbientRate = 0x48
    SetAmbientRate = 72,
    // SetAmbientLight = 0x49
    SetAmbientLight = 73,
    // AITriggersBegin = 0x4A
    AITriggersBegin = 74,
    // AITriggersStop = 0x4B
    AITriggersStop = 75,
    // RatioOfAITriggerTeams = 0x4C
    RatioOfAITriggerTeams = 76,
    // RatioOfTeamAircraft = 0x4D
    RatioOfTeamAircraft = 77,
    // RatioOfTeamInfantry = 0x4E
    RatioOfTeamInfantry = 78,
    // RatioOfTeamUnits = 0x4F
    RatioOfTeamUnits = 79,
    // ReinforcementAt = 0x50
    ReinforcementAt = 80,
    // WakeupSelf = 0x51
    WakeupSelf = 81,
    // WakeupAllSleepers = 0x52
    WakeupAllSleepers = 82,
    // WakeupAllHarmless = 0x53
    WakeupAllHarmless = 83,
    // WakeupGroup = 0x54
    WakeupGroup = 84,
    // VeinGrowth = 0x55
    VeinGrowth = 85,
    // TiberiumGrowth = 0x56
    TiberiumGrowth = 86,
    // IceGrowth = 0x57
    IceGrowth = 87,
    // ParticleAnim = 0x58
    ParticleAnim = 88,
    // RemoveParticleAnim = 0x59
    RemoveParticleAnim = 89,
    // LightningStrike = 0x5A
    LightningStrike = 90,
    // GoBerzerk = 0x5B
    GoBerzerk = 91,
    // ActivateFirestorm = 0x5C
    ActivateFirestorm = 92,
    // DeactivateFirestorm = 0x5D
    DeactivateFirestorm = 93,
    // IonCannonStrike = 0x5E
    IonCannonStrike = 94,
    // NukeStrike = 0x5F
    NukeStrike = 95,
    // ChemMissileStrike = 0x60
    ChemMissileStrike = 96,
    // ToggleTrainCargo = 0x61
    ToggleTrainCargo = 97,
    // PlaySoundEffectRandom = 0x62
    PlaySoundEffectRandom = 98,
    // PlaySoundEffectAtWaypoint = 0x63
    PlaySoundEffectAtWaypoint = 99,
    // PlayIngameMovie = 0x64
    PlayIngameMovie = 100,
    // ReshroudMapAtWaypoint = 0x65
    ReshroudMapAtWaypoint = 101,
    // LightningStormStrike = 0x66
    LightningStormStrike = 102,
    // TimerText = 0x67
    TimerText = 103,
    // FlashTeam = 0x68
    FlashTeam = 104,
    // TalkBubble = 0x69
    TalkBubble = 105,
    // SetObjectTechLevel = 0x6A
    SetObjectTechLevel = 106,
    // ReinforcementByChrono = 0x6B
    ReinforcementByChrono = 107,
    // CreateCrate = 0x6C
    CreateCrate = 108,
    // IronCurtain = 0x6D
    IronCurtain = 109,
    // PauseGame = 0x6E
    PauseGame = 110,
    // EvictOccupiers = 0x6F
    EvictOccupiers = 111,
    // CenterCameraAtWaypoint = 0x70
    CenterCameraAtWaypoint = 112,
    // MakeHouseCheer = 0x71
    MakeHouseCheer = 113,
    // SetTabTo = 0x72
    SetTabTo = 114,
    // FlashCameo = 0x73
    FlashCameo = 115,
    // StopSounds = 0x74
    StopSounds = 116,
    // PlayIngameMovieAndPause = 0x75
    PlayIngameMovieAndPause = 117,
    // ClearAllSmudges = 0x76
    ClearAllSmudges = 118,
    // DestroyAll = 0x77
    DestroyAll = 119,
    // DestroyAllBuildings = 0x78
    DestroyAllBuildings = 120,
    // DestroyAllLandUnits = 0x79
    DestroyAllLandUnits = 121,
    // DestroyAllNavalUnits = 0x7A
    DestroyAllNavalUnits = 122,
    // MindControlBase = 0x7B
    MindControlBase = 123,
    // RestoreMindControlledBase = 0x7C
    RestoreMindControlledBase = 124,
    // CreateBuilding = 0x7D
    CreateBuilding = 125,
    // RestoreStartingUnits = 0x7E
    RestoreStartingUnits = 126,
    // StartChronoScreenEffect = 0x7F
    StartChronoScreenEffect = 127,
    // TeleportAll = 0x80
    TeleportAll = 128,
    // SetSuperWeaponCharge = 0x81
    SetSuperWeaponCharge = 129,
    // RestoreStartingBuildings = 0x82
    RestoreStartingBuildings = 130,
    // FlashBuildingsOfType = 0x83
    FlashBuildingsOfType = 131,
    // SuperWeaponSetRechargeTime = 0x84
    SuperWeaponSetRechargeTime = 132,
    // SuperWeaponResetRechargeTime = 0x85
    SuperWeaponResetRechargeTime = 133,
    // SuperWeaponReset = 0x86
    SuperWeaponReset = 134,
    // SetPreferredTargetCell = 0x87
    SetPreferredTargetCell = 135,
    // ClearPreferredTargetCell = 0x88
    ClearPreferredTargetCell = 136,
    // SetBaseCenterCell = 0x89
    SetBaseCenterCell = 137,
    // ClearBaseCenterCell = 0x8A
    ClearBaseCenterCell = 138,
    // BlackoutRadar = 0x8B
    BlackoutRadar = 139,
    // SetDefensiveTargetCell = 0x8C
    SetDefensiveTargetCell = 140,
    // ClearDefensiveTargetCell = 0x8D
    ClearDefensiveTargetCell = 141,
    // RetintRed = 0x8E
    RetintRed = 142,
    // RetintGreen = 0x8F
    RetintGreen = 143,
    // RetintBlue = 0x90
    RetintBlue = 144,
    // JumpCameraHome = 0x91
    JumpCameraHome = 145,
}
// TriggerAttachType
enum TriggerAttachType {
    // Global = 0x1
    Global = 1,
    // Object = 0x2
    Object = 2,
    // Map = 0x4
    Map = 4,
    // House = 0x8
    House = 8,
    // Logic = 0x10
    Logic = 16,
}
// LogicNeedType
enum LogicNeedType {
    // None = 0
    None = 0,
    // Theme = 
    Theme = 1,
    // Movie = 
    Movie = 2,
    // Sound = 
    Sound = 3,
    // Speech = 
    Speech = 4,
    // Infantry = 
    Infantry = 5,
    // Unit = 
    Unit = 6,
    // Aircraft = 
    Aircraft = 7,
    // Structure = 
    Structure = 8,
    // Waypoint = 
    Waypoint = 9,
    // Number = 
    Number = 10,
    // Trigger = 
    Trigger = 11,
    // Team = 
    Team = 12,
    // House = 
    House = 13,
    // Time = 
    Time = 14,
    // Quarry = 
    Quarry = 15,
    // Bool = 
    Bool = 16,
    // Special = 
    Special = 17,
    // Mission = 
    Mission = 18,
    // Cell = 
    Cell = 19,
    // Script = 
    Script = 20,
    // Rectangle = 
    Rectangle = 21,
    // Global = 
    Global = 22,
    // AnimNWaypoint = 
    AnimNWaypoint = 23,
    // WaypointNWeapon = 
    WaypointNWeapon = 24,
    // LightBehavior = 
    LightBehavior = 25,
    // Tag = 
    Tag = 26,
    // MeteorSize = 
    MeteorSize = 27,
    // RadarEventNWaypoint = 
    RadarEventNWaypoint = 28,
    // Local = 
    Local = 29,
    // VelocityNWaypoint = 
    VelocityNWaypoint = 30,
    // ShowerNWaypoint = 
    ShowerNWaypoint = 31,
    // Velocity = 
    Velocity = 32,
    // Float = 
    Float = 33,
    // TeamNWaypoint = 
    TeamNWaypoint = 34,
    // ParticleNWaypoint = 
    ParticleNWaypoint = 35,
    // BuildingNProperty = 
    BuildingNProperty = 36,
    // SplitType = 
    SplitType = 37,
    // SoundNWaypoint = 
    SoundNWaypoint = 38,
    // Text = 
    Text = 39,
    // Team2 = 
    Team2 = 40,
    // Anim = 
    Anim = 41,
    // SpeechBubble = 
    SpeechBubble = 42,
    // NumberNTech = 
    NumberNTech = 43,
    // CrateNWaypoint = 
    CrateNWaypoint = 44,
    // BuildingNWaypoint = 
    BuildingNWaypoint = 45,
    // NumberNSuper = 
    NumberNSuper = 46,
    // BuildingNNumber = 
    BuildingNNumber = 47,
}
// AIMode
enum AIMode {
    // General = 0
    General = 0,
    // if HouseClass::AvailableMoney 
    // <
    // 25 ! stupidly low value
    // LowOnCash = 1
    LowOnCash = 1,
    // BuildBase = 3
    BuildBase = 3,
    // SellAll = 4
    SellAll = 4,
}
// AITriggerCondition
enum AITriggerCondition {
    // Pool = -1
    Pool = -1,
    // AIOwns = 0
    AIOwns = 0,
    // EnemyOwns = 1
    EnemyOwns = 1,
    // EnemyYellowPowe = 2
    EnemyYellowPowe = 2,
    // EnemyRedPower = 3
    EnemyRedPower = 3,
    // EnemyCashExceeds = 4
    EnemyCashExceeds = 4,
    // IronCharged = 5
    IronCharged = 5,
    // ChronoCharged = 6
    ChronoCharged = 6,
    // NeutralOwns = 7
    NeutralOwns = 7,
}
// AITriggerHouseType
enum AITriggerHouseType {
    // None = 0
    None = 0,
    // Single = 1
    Single = 1,
    // Any = 2
    Any = 2,
}
// Armor
enum Armor {
    // None = 0
    None = 0,
    // Flak = 1
    Flak = 1,
    // Plate = 2
    Plate = 2,
    // Light = 3
    Light = 3,
    // Medium = 4
    Medium = 4,
    // Heavy = 5
    Heavy = 5,
    // Wood = 6
    Wood = 6,
    // Steel = 7
    Steel = 7,
    // Concrete = 8
    Concrete = 8,
    // Special_1 = 9
    Special_1 = 9,
    // Special_2 = 10
    Special_2 = 10,
}
// spotlight behaviour
// SpotlightBehaviour
enum SpotlightBehaviour {
    // None = 0
    None = 0,
    // Sweep = 1
    Sweep = 1,
    // Circle = 2
    Circle = 2,
    // Follow = 3
    Follow = 3,
}
// SpotlightFlags
enum SpotlightFlags {
    // None = 0x0
    None = 0,
    // NoColor = 0x1
    NoColor = 1,
    // NoRed = 0x2
    NoRed = 2,
    // NoGreen = 0x4
    NoGreen = 4,
    // NoBlue = 0x8
    NoBlue = 8,
}
// BehavesLike
enum BehavesLike {
    // Smoke = 0
    Smoke = 0,
    // Gas = 1
    Gas = 1,
    // Fire = 2
    Fire = 2,
    // Spark = 3
    Spark = 3,
    // Railgun = 4
    Railgun = 4,
}
// ParticleSystemTypeClass->HoldsWhat, almost, but not entirely, unlike eBehavesLike above
// ParticleSystemHoldsWhat
enum ParticleSystemHoldsWhat {
    // Gas = 0
    Gas = 0,
    // Smoke = 1
    Smoke = 1,
    // Fire = 2
    Fire = 2,
    // Spark = 3
    Spark = 3,
    // Railgun = 4
    Railgun = 4,
}
// BuildCat
enum BuildCat {
    // DontCare = 0
    DontCare = 0,
    // Tech = 1
    Tech = 1,
    // Resoure = 2
    Resoure = 2,
    // Power = 3
    Power = 3,
    // Infrastructure = 4
    Infrastructure = 4,
    // Combat = 5
    Combat = 5,
}
// BuildingAnimSlot
enum BuildingAnimSlot {
    // All = -2
    All = -2,
    // None = -1
    None = -1,
    // Upgrade1 = 0
    Upgrade1 = 0,
    // Upgrade2 = 1
    Upgrade2 = 1,
    // Upgrade3 = 2
    Upgrade3 = 2,
    // Active = 3
    Active = 3,
    // ActiveTwo = 4
    ActiveTwo = 4,
    // ActiveThree = 5
    ActiveThree = 5,
    // ActiveFour = 6
    ActiveFour = 6,
    // PreProduction = 7
    PreProduction = 7,
    // Production = 8
    Production = 8,
    // Turret = 9
    Turret = 9,
    // Special = 10
    Special = 10,
    // SpecialTwo = 11
    SpecialTwo = 11,
    // SpecialThree = 12
    SpecialThree = 12,
    // SpecialFour = 13
    SpecialFour = 13,
    // Super = 14
    Super = 14,
    // SuperTwo = 15
    SuperTwo = 15,
    // SuperThree = 16
    SuperThree = 16,
    // SuperFour = 17
    SuperFour = 17,
    // Idle = 18
    Idle = 18,
    // LowPower = 19
    LowPower = 19,
    // SuperLowPower = 20
    SuperLowPower = 20,
}
// Category
enum Category {
    // Invalid = -1
    Invalid = -1,
    // Soldier = 0
    Soldier = 0,
    // Civilian = 1
    Civilian = 1,
    // VIP = 2
    VIP = 2,
    // Recon = 3
    Recon = 3,
    // AFV = 4
    AFV = 4,
    // IFV = 5
    IFV = 5,
    // LRFS = 6
    LRFS = 6,
    // Support = 7
    Support = 7,
    // Transport = 8
    Transport = 8,
    // AirPower = 9
    AirPower = 9,
    // AirLift = 10
    AirLift = 10,
}
// CellFlags
enum CellFlags {
    // Empty = 0x0
    Empty = 0,
    // CenterRevealed = 0x1
    CenterRevealed = 1,
    // EdgeRevealed = 0x2
    EdgeRevealed = 2,
    // IsWaypoint = 0x4
    IsWaypoint = 4,
    // this means no shroud
    // Explored = 0x8
    Explored = 8,
    // FlagPresent = 0x10
    FlagPresent = 16,
    // FlagToShroud = 0x20
    FlagToShroud = 32,
    // IsPlot = 0x40
    IsPlot = 64,
    // where the repair hut should be put, see 571FEB
    // BridgeOwner = 0x80
    BridgeOwner = 128,
    // Bridge head, not sure if its just the owner, see 570254
    // BridgeHead = 0x100
    BridgeHead = 256,
    // Unknown_200 = 0x200
    Unknown_200 = 512,
    // BridgeBody = 0x400
    BridgeBody = 1024,
    // see 570288 and 57036D
    // BridgeDir = 0x800
    BridgeDir = 2048,
    // see 6D7A91
    // PixelFX = 0x1000
    PixelFX = 4096,
    // Unknown_2000 = 0x2000
    Unknown_2000 = 8192,
    // Unknown_4000 = 0x4000
    Unknown_4000 = 16384,
    // see 74E4A3
    // Veinhole = 0x8000
    Veinhole = 32768,
    // see 51936F and 73D084
    // DrawDarkenIfInAir = 0x10000
    DrawDarkenIfInAir = 65536,
    // AnimAttached = 0x20000
    AnimAttached = 131072,
    // see 42B5B8
    // Tube = 0x40000
    Tube = 262144,
    // EMPPresent = 0x80000
    EMPPresent = 524288,
    // HorizontalLineEventTag = 0x100000
    HorizontalLineEventTag = 1048576,
    // VerticalLineEventTag = 0x200000
    VerticalLineEventTag = 2097152,
    // Fogged = 0x400000
    Fogged = 4194304,
    // Revealed = CenterRevealed | EdgeRevealed
    Revealed = 3,
    // Bridge = BridgeHead | BridgeBody
    Bridge = 1280,
}
// AltCellFlags
enum AltCellFlags {
    // 487720 check_obstacle?
    // Unknown_1 = 0x1
    Unknown_1 = 1,
    // ContainsBuilding = 0x2
    ContainsBuilding = 2,
    // 47EED4 PlaceShape related
    // Unknown_4 = 0x4
    Unknown_4 = 4,
    // Mapped = 0x8
    Mapped = 8,
    // NoFog = 0x10
    NoFog = 16,
    // Unknown_20 = 0x20
    Unknown_20 = 32,
    // Unknown_40 = 0x40
    Unknown_40 = 64,
    // Unknown_80 = 0x80
    Unknown_80 = 128,
    // Unknown_100 = 0x100
    Unknown_100 = 256,
    // Clear = Mapped | NoFog
    Clear = 24,
}
// PassabilityType
enum PassabilityType {
    // Passable = 0
    Passable = 0,
    // Crushable = 1
    Crushable = 1,
    // Tree or wall
    // Destroyable = 2
    Destroyable = 2,
    // Beach = 3
    Beach = 3,
    // Water = 4
    Water = 4,
    // HasFreeSpots = 5
    HasFreeSpots = 5,
    // Impassable = 6
    Impassable = 6,
    // OutsideMap = 7
    OutsideMap = 7,
}
// FacingType
enum FacingType {
    // North = 0
    North = 0,
    // NorthEast = 1
    NorthEast = 1,
    // East = 2
    East = 2,
    // SouthEast = 3
    SouthEast = 3,
    // South = 4
    South = 4,
    // SouthWest = 5
    SouthWest = 5,
    // West = 6
    West = 6,
    // NorthWest = 7
    NorthWest = 7,
    // Count = 8
    Count = 8,
    // None = -1
    None = -1,
}
// CloakState
enum CloakState {
    // Uncloaked = 0
    Uncloaked = 0,
    // Cloaking = 1
    Cloaking = 1,
    // Cloaked = 2
    Cloaked = 2,
    // Uncloaking = 3
    Uncloaking = 3,
}
// DamageState
enum DamageState {
    // Unaffected = 0
    Unaffected = 0,
    // Unchanged = 1
    Unchanged = 1,
    // NowYellow = 2
    NowYellow = 2,
    // NowRed = 3
    NowRed = 3,
    // NowDead = 4
    NowDead = 4,
    // PostMortem = 5
    PostMortem = 5,
}
// DamageAreaResult
enum DamageAreaResult {
    // Hit = 0
    Hit = 0,
    // Missed = 1
    Missed = 1,
    // Nullified = 2
    Nullified = 2,
}
// KickOutResult
enum KickOutResult {
    // Failed = 0
    Failed = 0,
    // Busy = 1
    Busy = 1,
    // Succeeded = 2
    Succeeded = 2,
}
// CanBuildResult
enum CanBuildResult {
    // black out cameo
    // TemporarilyUnbuildable = -1
    TemporarilyUnbuildable = -1,
    // permanently; remove cameo
    // Unbuildable = 0
    Unbuildable = 0,
    // can build
    // Buildable = 1
    Buildable = 1,
}
// this is how game's enums are to be defined from now on
// FireError
enum FireError {
    // no valid value
    // NONE = -1
    NONE = -1,
    // no problem, can fire
    // OK = 0
    OK = 0,
    // no ammo
    // AMMO = 1
    AMMO = 1,
    // bad facing
    // FACING = 2
    FACING = 2,
    // still reloading
    // REARM = 3
    REARM = 3,
    // busy rotating
    // ROTATING = 4
    ROTATING = 4,
    // can't fire
    // ILLEGAL = 5
    ILLEGAL = 5,
    // I'm sorry Dave, I can't do that
    // CANT = 6
    CANT = 6,
    // moving, can't fire
    // MOVING = 7
    MOVING = 7,
    // out of range
    // RANGE = 8
    RANGE = 8,
    // need to decloak
    // CLOAKED = 9
    CLOAKED = 9,
    // busy, please hold
    // BUSY = 10
    BUSY = 10,
    // deploy first!
    // MUST_DEPLOY = 11
    MUST_DEPLOY = 11,
}
// HealthState
enum HealthState {
    // Red = 0
    Red = 0,
    // Yellow = 1
    Yellow = 1,
    // Green = 2
    Green = 2,
}
// Foundation
enum Foundation {
    // _1x1 = 0
    _1x1 = 0,
    // _2x1 = 1
    _2x1 = 1,
    // _1x2 = 2
    _1x2 = 2,
    // _2x2 = 3
    _2x2 = 3,
    // _2x3 = 4
    _2x3 = 4,
    // _3x2 = 5
    _3x2 = 5,
    // _3x3 = 6
    _3x3 = 6,
    // _3x5 = 7
    _3x5 = 7,
    // _4x2 = 8
    _4x2 = 8,
    // _3x3Refinery = 9
    _3x3Refinery = 9,
    // _1x3 = 10
    _1x3 = 10,
    // _3x1 = 11
    _3x1 = 11,
    // _4x3 = 12
    _4x3 = 12,
    // _1x4 = 13
    _1x4 = 13,
    // _1x5 = 14
    _1x5 = 14,
    // _2x6 = 15
    _2x6 = 15,
    // _2x5 = 16
    _2x5 = 16,
    // _5x3 = 17
    _5x3 = 17,
    // _4x4 = 18
    _4x4 = 18,
    // _3x4 = 19
    _3x4 = 19,
    // _6x4 = 20
    _6x4 = 20,
    // _0x0 = 21
    _0x0 = 21,
}
// GameMode
enum GameMode {
    // Campaign = 0x0
    Campaign = 0,
    // LAN = 0x3
    LAN = 3,
    // Internet = 0x4
    Internet = 4,
    // Skirmish = 0x5
    Skirmish = 5,
}
// InfDeath
enum InfDeath {
    // None = 0
    None = 0,
    // Die1 = 1
    Die1 = 1,
    // Die2 = 2
    Die2 = 2,
    // Explode = 3
    Explode = 3,
    // Flames = 4
    Flames = 4,
    // Electro = 5
    Electro = 5,
    // HeadPop = 6
    HeadPop = 6,
    // Nuked = 7
    Nuked = 7,
    // Virus = 8
    Virus = 8,
    // Mutate = 9
    Mutate = 9,
    // Brute = 10
    Brute = 10,
}
// LandType
enum LandType {
    // Clear = 0
    Clear = 0,
    // Road = 1
    Road = 1,
    // Water = 2
    Water = 2,
    // Rock = 3
    Rock = 3,
    // Wall = 4
    Wall = 4,
    // Tiberium = 5
    Tiberium = 5,
    // Beach = 6
    Beach = 6,
    // Rough = 7
    Rough = 7,
    // Ice = 8
    Ice = 8,
    // Railroad = 9
    Railroad = 9,
    // Tunnel = 10
    Tunnel = 10,
    // Weeds = 11
    Weeds = 11,
}
// Some helpers
// let W = a result of creepy maths = 104 (leptons)
// let GH = this->GetHeight()
// ObjectClass::InWhichLayer, used by practically all ObjectClass derivates except Foot, returns
// Ground if GH 
// <
// 2*W leptons
// Air if it returns 
// <
// Rules->CruiseHeight leptons
// Top otherwise
// FootClass::InWhichLayer, used by Infantry, Unit and Aircraft, returns results depending on the locomotor
// Drive         : Ground
// DropPod       : Air
// Fly           : Ground if GH 
// <
// = 0, Top otherwise
// Hover         : Ground
// Jumpjet       : Ground if GH 
// <
// = 2*W, Air if it's not at the height of its flight (rising/landing), Top otherwise
// Mech          : Ground
// Rocket        : Air
// Ship          : Ground
// Subterrannean : Underground if really underground, Ground if on ground, diving or elevating
// Walk          : Ground
// Layer
enum Layer {
    // None = -1
    None = -1,
    // Underground = 0
    Underground = 0,
    // Surface = 1
    Surface = 1,
    // Ground = 2
    Ground = 2,
    // Air = 3
    Air = 3,
    // Top = 4
    Top = 4,
}
// MarkType
enum MarkType {
    // Up = 0
    Up = 0,
    // Down = 1
    Down = 1,
    // Change = 2
    Change = 2,
    // ChangeRedraw = 3
    ChangeRedraw = 3,
    // OverlapDown = 4
    OverlapDown = 4,
    // OverlapUp = 5
    OverlapUp = 5,
}
// MouseHotSpotX
enum MouseHotSpotX {
    // Left = 0
    Left = 0,
    // Center = 12345
    Center = 12345,
    // Right = 54321
    Right = 54321,
}
// MouseHotSpotY
enum MouseHotSpotY {
    // Top = 0
    Top = 0,
    // Middle = 12345
    Middle = 12345,
    // Bottom = 54321
    Bottom = 54321,
}
// Mission
enum Mission {
    // None = -1
    None = -1,
    // Sleep = 0
    Sleep = 0,
    // Attack = 1
    Attack = 1,
    // Move = 2
    Move = 2,
    // QMove = 3
    QMove = 3,
    // Retreat = 4
    Retreat = 4,
    // Guard = 5
    Guard = 5,
    // Sticky = 6
    Sticky = 6,
    // Enter = 7
    Enter = 7,
    // Capture = 8
    Capture = 8,
    // Eaten = 9
    Eaten = 9,
    // Harvest = 10
    Harvest = 10,
    // Area_Guard = 11
    Area_Guard = 11,
    // Return = 12
    Return = 12,
    // Stop = 13
    Stop = 13,
    // Ambush = 14
    Ambush = 14,
    // Hunt = 15
    Hunt = 15,
    // Unload = 16
    Unload = 16,
    // Sabotage = 17
    Sabotage = 17,
    // Construction = 18
    Construction = 18,
    // Selling = 19
    Selling = 19,
    // Repair = 20
    Repair = 20,
    // Rescue = 21
    Rescue = 21,
    // Missile = 22
    Missile = 22,
    // Harmless = 23
    Harmless = 23,
    // Open = 24
    Open = 24,
    // Patrol = 25
    Patrol = 25,
    // ParadropApproach = 26
    ParadropApproach = 26,
    // ParadropOverfly = 27
    ParadropOverfly = 27,
    // Wait = 28
    Wait = 28,
    // AttackMove = 29
    AttackMove = 29,
    // SpyplaneApproach = 30
    SpyplaneApproach = 30,
    // SpyplaneOverfly = 31
    SpyplaneOverfly = 31,
}
// MovementZone
enum MovementZone {
    // None = -1
    None = -1,
    // Normal = 0
    Normal = 0,
    // Crusher = 1
    Crusher = 1,
    // Destroyer = 2
    Destroyer = 2,
    // AmphibiousDestroyer = 3
    AmphibiousDestroyer = 3,
    // AmphibiousCrusher = 4
    AmphibiousCrusher = 4,
    // Amphibious = 5
    Amphibious = 5,
    // Subterrannean = 6
    Subterrannean = 6,
    // Infantry = 7
    Infantry = 7,
    // InfantryDestroyer = 8
    InfantryDestroyer = 8,
    // Fly = 9
    Fly = 9,
    // Water = 10
    Water = 10,
    // WaterBeach = 11
    WaterBeach = 11,
    // CrusherAll = 12
    CrusherAll = 12,
}
// PipIndex
enum PipIndex {
    // Empty = 0
    Empty = 0,
    // Green = 1
    Green = 1,
    // Yellow = 2
    Yellow = 2,
    // White = 3
    White = 3,
    // Red = 4
    Red = 4,
    // Blue = 5
    Blue = 5,
    // PersonEmpty = 6
    PersonEmpty = 6,
    // PersonGreen = 7
    PersonGreen = 7,
    // PersonYellow = 8
    PersonYellow = 8,
    // PersonWhite = 9
    PersonWhite = 9,
    // PersonRed = 10
    PersonRed = 10,
    // PersonBlue = 11
    PersonBlue = 11,
    // PersonPurple = 12
    PersonPurple = 12,
}
// PipScale
enum PipScale {
    // None = 0
    None = 0,
    // Ammo = 1
    Ammo = 1,
    // Tiberium = 2
    Tiberium = 2,
    // Passengers = 3
    Passengers = 3,
    // Power = 4
    Power = 4,
    // MindControl = 5
    MindControl = 5,
}
// Powerup
enum Powerup {
    // Money = 0
    Money = 0,
    // Unit = 1
    Unit = 1,
    // HealBase = 2
    HealBase = 2,
    // Cloak = 3
    Cloak = 3,
    // Explosion = 4
    Explosion = 4,
    // Napalm = 5
    Napalm = 5,
    // Squad = 6
    Squad = 6,
    // Darkness = 7
    Darkness = 7,
    // Reveal = 8
    Reveal = 8,
    // Armor = 9
    Armor = 9,
    // Speed = 10
    Speed = 10,
    // Firepower = 11
    Firepower = 11,
    // ICBM = 12
    ICBM = 12,
    // Invulnerability = 13
    Invulnerability = 13,
    // Veteran = 14
    Veteran = 14,
    // IonStorm = 15
    IonStorm = 15,
    // Gas = 16
    Gas = 16,
    // Tiberium = 17
    Tiberium = 17,
    // Pod = 18
    Pod = 18,
}
// Prerequisite
enum Prerequisite {
    // Proc = -6
    Proc = -6,
    // Tech = -5
    Tech = -5,
    // Radar = -4
    Radar = -4,
    // Barracks = -3
    Barracks = -3,
    // Factory = -2
    Factory = -2,
    // Power = -1
    Power = -1,
}
// PrismChargeState
enum PrismChargeState {
    // Idle = 0
    Idle = 0,
    // Master = 1
    Master = 1,
    // Slave = 2
    Slave = 2,
}
// RadarEventType
enum RadarEventType {
    // Combat = 0
    Combat = 0,
    // Noncombat = 1
    Noncombat = 1,
    // DropZone = 2
    DropZone = 2,
    // BaseAttacked = 3
    BaseAttacked = 3,
    // HarvesterAttacked = 4
    HarvesterAttacked = 4,
    // EnemySensed = 5
    EnemySensed = 5,
    // UnitProduced = 6
    UnitProduced = 6,
    // UnitLost = 7
    UnitLost = 7,
    // UnitRepaired = 8
    UnitRepaired = 8,
    // BuildingInfiltrated = 9
    BuildingInfiltrated = 9,
    // BuildingCaptured = 10
    BuildingCaptured = 10,
    // BeaconPlaced = 11
    BeaconPlaced = 11,
    // SuperweaponDetected = 12
    SuperweaponDetected = 12,
    // SuperweaponActivated = 13
    SuperweaponActivated = 13,
    // BridgeRepaired = 14
    BridgeRepaired = 14,
    // GarrisonAbandoned = 15
    GarrisonAbandoned = 15,
    // AllyBaseAttacked = 16
    AllyBaseAttacked = 16,
}
// PsychicDominatorStatus
enum PsychicDominatorStatus {
    // Inactive = 0
    Inactive = 0,
    // FirstAnim = 1
    FirstAnim = 1,
    // Fire = 2
    Fire = 2,
    // SecondAnim = 3
    SecondAnim = 3,
    // Reset = 4
    Reset = 4,
    // Over = 5
    Over = 5,
}
// NukeFlashStatus
enum NukeFlashStatus {
    // Inactive = 0
    Inactive = 0,
    // FadeIn = 1
    FadeIn = 1,
    // FadeOut = 2
    FadeOut = 2,
}
// ChargeDrainState
enum ChargeDrainState {
    // None = -1
    None = -1,
    // Charging = 0
    Charging = 0,
    // Ready = 1
    Ready = 1,
    // Draining = 2
    Draining = 2,
}
// SuperWeaponType
enum SuperWeaponType {
    // Invalid = -1
    Invalid = -1,
    // Nuke = 0
    Nuke = 0,
    // IronCurtain = 1
    IronCurtain = 1,
    // LightningStorm = 2
    LightningStorm = 2,
    // ChronoSphere = 3
    ChronoSphere = 3,
    // ChronoWarp = 4
    ChronoWarp = 4,
    // ParaDrop = 5
    ParaDrop = 5,
    // AmerParaDrop = 6
    AmerParaDrop = 6,
    // PsychicDominator = 7
    PsychicDominator = 7,
    // SpyPlane = 8
    SpyPlane = 8,
    // GeneticMutator = 9
    GeneticMutator = 9,
    // ForceShield = 10
    ForceShield = 10,
    // PsychicReveal = 11
    PsychicReveal = 11,
}
// MouseCursorType
enum MouseCursorType {
    // Default = 0x0
    Default = 0,
    // Move_N = 0x1
    Move_N = 1,
    // Move_NE = 0x2
    Move_NE = 2,
    // Move_E = 0x3
    Move_E = 3,
    // Move_SE = 0x4
    Move_SE = 4,
    // Move_S = 0x5
    Move_S = 5,
    // Move_SW = 0x6
    Move_SW = 6,
    // Move_W = 0x7
    Move_W = 7,
    // Move_NW = 0x8
    Move_NW = 8,
    // NoMove_N = 0x9
    NoMove_N = 9,
    // NoMove_NE = 0xA
    NoMove_NE = 10,
    // NoMove_E = 0xB
    NoMove_E = 11,
    // NoMove_SE = 0xC
    NoMove_SE = 12,
    // NoMove_S = 0xD
    NoMove_S = 13,
    // NoMove_SW = 0xE
    NoMove_SW = 14,
    // NoMove_W = 0xF
    NoMove_W = 15,
    // NoMove_NW = 0x10
    NoMove_NW = 16,
    // Select = 0x11
    Select = 17,
    // Move = 0x12
    Move = 18,
    // NoMove = 0x13
    NoMove = 19,
    // Attack = 0x14
    Attack = 20,
    // AttackOutOfRange = 0x15
    AttackOutOfRange = 21,
    // Protect = 0x16
    Protect = 22,
    // DesolatorDeploy = 0x17
    DesolatorDeploy = 23,
    // Cursor_18 = 0x18
    Cursor_18 = 24,
    // Enter = 0x19
    Enter = 25,
    // NoEnter = 0x1A
    NoEnter = 26,
    // Deploy = 0x1B
    Deploy = 27,
    // NoDeploy = 0x1C
    NoDeploy = 28,
    // Cursor_1D = 0x1D
    Cursor_1D = 29,
    // Sell = 0x1E
    Sell = 30,
    // SellUnit = 0x1F
    SellUnit = 31,
    // NoSell = 0x20
    NoSell = 32,
    // Repair = 0x21
    Repair = 33,
    // EngineerRepair = 0x22
    EngineerRepair = 34,
    // NoRepair = 0x23
    NoRepair = 35,
    // Waypoint = 0x24
    Waypoint = 36,
    // Disguise = 0x25
    Disguise = 37,
    // IvanBomb = 0x26
    IvanBomb = 38,
    // MindControl = 0x27
    MindControl = 39,
    // RemoveSquid = 0x28
    RemoveSquid = 40,
    // Crush = 0x29
    Crush = 41,
    // SpyTech = 0x2A
    SpyTech = 42,
    // SpyPower = 0x2B
    SpyPower = 43,
    // Cursor_2C = 0x2C
    Cursor_2C = 44,
    // GIDeploy = 0x2D
    GIDeploy = 45,
    // Cursor_2E = 0x2E
    Cursor_2E = 46,
    // ParaDrop = 0x2F
    ParaDrop = 47,
    // RallyPoint
    // Cursor_30 = 0x30
    Cursor_30 = 48,
    // ???
    // CloseWaypoint = 0x31
    CloseWaypoint = 49,
    // LightningStorm = 0x32
    LightningStorm = 50,
    // Detonate = 0x33
    Detonate = 51,
    // Demolish = 0x34
    Demolish = 52,
    // Nuke = 0x35
    Nuke = 53,
    // BlueMove
    // Cursor_36 = 0x36
    Cursor_36 = 54,
    // Power = 0x37
    Power = 55,
    // NoBlueMove
    // Cursor_38 = 0x38
    Cursor_38 = 56,
    // IronCurtain = 0x39
    IronCurtain = 57,
    // Chronosphere = 0x3A
    Chronosphere = 58,
    // Disarm = 0x3B
    Disarm = 59,
    // Disallowed = 0x3C
    Disallowed = 60,
    // Scroll = 0x3D
    Scroll = 61,
    // Scroll_ESW = 0x3E
    Scroll_ESW = 62,
    // Scroll_SW = 0x3F
    Scroll_SW = 63,
    // Scroll_NSW = 0x40
    Scroll_NSW = 64,
    // Scroll_NW = 0x41
    Scroll_NW = 65,
    // Scroll_NEW = 0x42
    Scroll_NEW = 66,
    // Scroll_NE = 0x43
    Scroll_NE = 67,
    // Scroll_NES = 0x44
    Scroll_NES = 68,
    // Scroll_ES = 0x45
    Scroll_ES = 69,
    // Protect2 = 0x46
    Protect2 = 70,
    // AttackOutOfRange2 = 0x47
    AttackOutOfRange2 = 71,
    // LeaveBuilding
    // Cursor_48 = 0x48
    Cursor_48 = 72,
    // InfantryAbsorb = 0x49
    InfantryAbsorb = 73,
    // NoMindControl = 0x4A
    NoMindControl = 74,
    // NoRallyPoint
    // Cursor_4B = 0x4B
    Cursor_4B = 75,
    // Cursor_4C = 0x4C
    Cursor_4C = 76,
    // Cursor_4D = 0x4D
    Cursor_4D = 77,
    // Beacon = 0x4E
    Beacon = 78,
    // ForceShield = 0x4F
    ForceShield = 79,
    // NoForceShield = 0x50
    NoForceShield = 80,
    // GeneticMutator = 0x51
    GeneticMutator = 81,
    // AirStrike = 0x52
    AirStrike = 82,
    // PsychicDominator = 0x53
    PsychicDominator = 83,
    // PsychicReveal = 0x54
    PsychicReveal = 84,
    // SpyPlane = 0x55
    SpyPlane = 85,
}
// RadBeamType
enum RadBeamType {
    // Temporal = 0
    Temporal = 0,
    // RadBeam = 1
    RadBeam = 1,
    // this sets the beam color to MagnaBeamColor! There probably was no reason for that whatsoever.
    // Eruption = 2
    Eruption = 2,
}
// Rank
enum Rank {
    // Invalid = -1
    Invalid = -1,
    // Elite = 0
    Elite = 0,
    // Veteran = 1
    Veteran = 1,
    // Rookie = 2
    Rookie = 2,
}
// Sequence
enum Sequence {
    // Ready = 0
    Ready = 0,
    // Guard = 1
    Guard = 1,
    // Prone = 2
    Prone = 2,
    // Walk = 3
    Walk = 3,
    // FireUp = 4
    FireUp = 4,
    // Down = 5
    Down = 5,
    // Crawl = 6
    Crawl = 6,
    // Up = 7
    Up = 7,
    // FireProne = 8
    FireProne = 8,
    // Idle1 = 9
    Idle1 = 9,
    // Idle2 = 10
    Idle2 = 10,
    // Die1 = 11
    Die1 = 11,
    // Die2 = 12
    Die2 = 12,
    // Die3 = 13
    Die3 = 13,
    // Die4 = 14
    Die4 = 14,
    // Die5 = 15
    Die5 = 15,
    // Tread = 16
    Tread = 16,
    // Swim = 17
    Swim = 17,
    // WetIdle1 = 18
    WetIdle1 = 18,
    // WetIdle2 = 19
    WetIdle2 = 19,
    // WetDie1 = 20
    WetDie1 = 20,
    // WetDie2 = 21
    WetDie2 = 21,
    // WetAttack = 22
    WetAttack = 22,
    // Hover = 23
    Hover = 23,
    // Fly = 24
    Fly = 24,
    // Tumble = 25
    Tumble = 25,
    // FireFly = 26
    FireFly = 26,
    // Deploy = 27
    Deploy = 27,
    // Deployed = 28
    Deployed = 28,
    // DeployedFire = 29
    DeployedFire = 29,
    // DeployedIdle = 30
    DeployedIdle = 30,
    // Undeploy = 31
    Undeploy = 31,
    // Cheer = 32
    Cheer = 32,
    // Paradrop = 33
    Paradrop = 33,
    // AirDeathStart = 34
    AirDeathStart = 34,
    // AirDeathFalling = 35
    AirDeathFalling = 35,
    // AirDeathFinish = 36
    AirDeathFinish = 36,
    // Panic = 37
    Panic = 37,
    // Shovel = 38
    Shovel = 38,
    // Carry = 39
    Carry = 39,
    // SecondaryFire = 40
    SecondaryFire = 40,
    // SecondaryProne = 41
    SecondaryProne = 41,
    // Nothing = -1
    Nothing = -1,
}
// SequenceFacing
enum SequenceFacing {
    // N = 0
    N = 0,
    // NE = 1
    NE = 1,
    // E = 2
    E = 2,
    // SE = 3
    SE = 3,
    // S = 4
    S = 4,
    // SW = 5
    SW = 5,
    // W = 6
    W = 6,
    // NW = 7
    NW = 7,
}
// SpeedType
enum SpeedType {
    // None = -1
    None = -1,
    // Foot = 0
    Foot = 0,
    // Track = 1
    Track = 1,
    // Wheel = 2
    Wheel = 2,
    // Hover = 3
    Hover = 3,
    // Winged = 4
    Winged = 4,
    // Float = 5
    Float = 5,
    // Amphibious = 6
    Amphibious = 6,
    // FloatBeach = 7
    FloatBeach = 7,
}
// TheaterType
enum TheaterType {
    // None = -1
    None = -1,
    // Temperate = 0
    Temperate = 0,
    // Snow = 1
    Snow = 1,
    // Urban = 2
    Urban = 2,
    // Desert = 3
    Desert = 3,
    // NewUrban = 4
    NewUrban = 4,
    // Lunar = 5
    Lunar = 5,
}
// typedef int eVisualType;
// VisualType
enum VisualType {
    // Normal = 0
    Normal = 0,
    // Indistinct = 1
    Indistinct = 1,
    // Darken = 2
    Darken = 2,
    // Shadowy = 3
    Shadowy = 3,
    // Ripple = 4
    Ripple = 4,
    // Hidden = 5
    Hidden = 5,
}
// RadioCommand
enum RadioCommand {
    // static (no message)
    // AnswerInvalid = 0
    AnswerInvalid = 0,
    // Roger.
    // AnswerPositive = 1
    AnswerPositive = 1,
    // Come in.
    // RequestLink = 2
    RequestLink = 2,
    // Over and out.
    // NotifyUnlink = 3
    NotifyUnlink = 3,
    // Requesting transport.
    // unknown_4 = 4
    unknown_4 = 4,
    // Attach to transport.
    // unknown_5 = 5
    unknown_5 = 5,
    // I've got a delivery for you.
    // unknown_6 = 6
    unknown_6 = 6,
    // I'm performing load/unload maneuver. Be careful.
    // NotifyBeginLoad = 7
    NotifyBeginLoad = 7,
    // I'm clear.
    // NotifyUnloaded = 8
    NotifyUnloaded = 8,
    // You are clear to unload. Driving away now.
    // RequestUnload = 9
    RequestUnload = 9,
    // Am unable to comply.
    // AnswerNegative = 10
    AnswerNegative = 10,
    // I'm starting construction now... act busy.
    // RequestBeginProduction = 11
    RequestBeginProduction = 11,
    // I've finished construction. You are free.
    // RequestEndProduction = 12
    RequestEndProduction = 12,
    // We bumped, redraw yourself please.
    // RequestRedraw = 13
    RequestRedraw = 13,
    // I'm trying to load up now.
    // RequestLoading = 14
    RequestLoading = 14,
    // Loading up now.
    // AnswerLoading = 14
    AnswerLoading = 14,
    // May I become a passenger?
    // QueryCanEnter = 15
    QueryCanEnter = 15,
    // Are you ready to receive shipment?
    // QueryCanUnload = 16
    QueryCanUnload = 16,
    // Are you trying to become a passenger?
    // QueryWantEnter = 17
    QueryWantEnter = 17,
    // Move to location X.
    // RequestMoveTo = 18
    RequestMoveTo = 18,
    // Do you need to move?
    // QueryMoving = 19
    QueryMoving = 19,
    // All right already. Now what?
    // AnswerAwaiting = 20
    AnswerAwaiting = 20,
    // I'm a passenger now.
    // RequestCompleteEnter = 21
    RequestCompleteEnter = 21,
    // Backup into refinery now.
    // RequestDockRefinery = 22
    RequestDockRefinery = 22,
    // Run away!
    // AnswerLeave = 23
    AnswerLeave = 23,
    // Running away.
    // NotifyLeave = 23
    NotifyLeave = 23,
    // Tether established.
    // RequestTether = 24
    RequestTether = 24,
    // Tether broken.
    // RequestUntether = 25
    RequestUntether = 25,
    // Alternative tether established.
    // RequestAlternativeTether = 26
    RequestAlternativeTether = 26,
    // Alternative tether broken.
    // RequestAlternativeUntether = 27
    RequestAlternativeUntether = 27,
    // Repair one step.
    // RequestRepair = 28
    RequestRepair = 28,
    // Are you prepared to fight?
    // QueryReadiness = 29
    QueryReadiness = 29,
    // Attack this target please.
    // RequestAttack = 30
    RequestAttack = 30,
    // Reload one step.
    // RequestReload = 31
    RequestReload = 31,
    // Circumstances prevent success.
    // AnswerBlocked = 32
    AnswerBlocked = 32,
    // All done with the request?
    // QueryDone = 33
    QueryDone = 33,
    // All done with the request.
    // AnswerDone = 33
    AnswerDone = 33,
    // Do you need service depot work?
    // QueryNeedRepair = 34
    QueryNeedRepair = 34,
    // Are you located on top of me?
    // QueryOnBuilding = 35
    QueryOnBuilding = 35,
    // Want ride
    // QueryCanTote = 36
    QueryCanTote = 36,
}
// EventType
enum EventType {
    // Empty = 0x0
    Empty = 0,
    // PowerOn = 0x1
    PowerOn = 1,
    // PowerOff = 0x2
    PowerOff = 2,
    // Ally = 0x3
    Ally = 3,
    // MegaMission = 0x4
    MegaMission = 4,
    // MegaMissionF = 0x5
    MegaMissionF = 5,
    // Idle = 0x6
    Idle = 6,
    // Scatter = 0x7
    Scatter = 7,
    // Destruct = 0x8
    Destruct = 8,
    // Deploy = 0x9
    Deploy = 9,
    // Detonate = 0xA
    Detonate = 10,
    // Place = 0xB
    Place = 11,
    // Options = 0xC
    Options = 12,
    // GameSpeed = 0xD
    GameSpeed = 13,
    // Produce = 0xE
    Produce = 14,
    // Suspend = 0xF
    Suspend = 15,
    // Abandon = 0x10
    Abandon = 16,
    // Primary = 0x11
    Primary = 17,
    // SpecialPlace = 0x12
    SpecialPlace = 18,
    // Exit = 0x13
    Exit = 19,
    // Animation = 0x14
    Animation = 20,
    // Repair = 0x15
    Repair = 21,
    // Sell = 0x16
    Sell = 22,
    // SellCell = 0x17
    SellCell = 23,
    // Special = 0x18
    Special = 24,
    // FrameSync = 0x19
    FrameSync = 25,
    // Message = 0x1A
    Message = 26,
    // ResponseTime = 0x1B
    ResponseTime = 27,
    // FrameInfo = 0x1C
    FrameInfo = 28,
    // SaveGame = 0x1D
    SaveGame = 29,
    // Archive = 0x1E
    Archive = 30,
    // AddPlayer = 0x1F
    AddPlayer = 31,
    // Timing = 0x20
    Timing = 32,
    // ProcessTime = 0x21
    ProcessTime = 33,
    // PageUser = 0x22
    PageUser = 34,
    // RemovePlayer = 0x23
    RemovePlayer = 35,
    // LatencyFudge = 0x24
    LatencyFudge = 36,
    // MegaFrameInfo = 0x25
    MegaFrameInfo = 37,
    // PacketTiming = 0x26
    PacketTiming = 38,
    // AboutToExit = 0x27
    AboutToExit = 39,
    // FallbackHost = 0x28
    FallbackHost = 40,
    // AddressChange = 0x29
    AddressChange = 41,
    // PlanConnect = 0x2A
    PlanConnect = 42,
    // PlanCommit = 0x2B
    PlanCommit = 43,
    // PlanNodeDelete = 0x2C
    PlanNodeDelete = 44,
    // AllCheer = 0x2D
    AllCheer = 45,
    // AbandonAll = 0x2E
    AbandonAll = 46,
    // LAST_EVENT = 47
    LAST_EVENT = 47,
}
// Sound specific
// SoundPriority
enum SoundPriority {
    // Lowest = 0
    Lowest = 0,
    // Low = 1
    Low = 1,
    // Normal = 2
    Normal = 2,
    // High = 3
    High = 3,
    // Critical = 4
    Critical = 4,
}
// SoundType
enum SoundType {
    // Normal = 0x0
    Normal = 0,
    // Violent = 0x1
    Violent = 1,
    // Movement = 0x2
    Movement = 2,
    // Quiet = 0x4
    Quiet = 4,
    // Loud = 0x8
    Loud = 8,
    // Global = 0x10
    Global = 16,
    // Screen = 0x20
    Screen = 32,
    // Local = 0x40
    Local = 64,
    // Player = 0x80
    Player = 128,
    // NoiseShy = 0x100
    NoiseShy = 256,
    // GunShy = 0x200
    GunShy = 512,
    // Unshroud = 0x400
    Unshroud = 1024,
    // Shroud = 0x800
    Shroud = 2048,
    // Ambient = 0x1000
    Ambient = 4096,
}
// SoundControl
enum SoundControl {
    // None = 0x0
    None = 0,
    // Loop = 0x1
    Loop = 1,
    // Random = 0x2
    Random = 2,
    // All = 0x4
    All = 4,
    // Predelay = 0x8
    Predelay = 8,
    // Interrupt = 0x10
    Interrupt = 16,
    // Attack = 0x20
    Attack = 32,
    // Decay = 0x40
    Decay = 64,
    // Ambient = 0x80
    Ambient = 128,
}
// VoxType
enum VoxType {
    // Standard = 0
    Standard = 0,
    // Queue = 1
    Queue = 1,
    // Interrupt = 2
    Interrupt = 2,
    // QueuedInterrupt = 3
    QueuedInterrupt = 3,
}
// VoxPriority
enum VoxPriority {
    // Low = 0
    Low = 0,
    // Normal = 1
    Normal = 1,
    // Important = 2
    Important = 2,
    // Critical = 3
    Critical = 3,
}
// WaveType
enum WaveType {
    // Sonic = 0
    Sonic = 0,
    // BigLaser = 1
    BigLaser = 1,
    // Laser = 2
    Laser = 2,
    // Magnetron = 3
    Magnetron = 3,
}
// QuarryType
enum QuarryType {
    // None = 
    None = 0,
    // Attack any enemy (same as "hunt").
    // Anything = 
    Anything = 1,
    // Attack buildings (in general).
    // Buildings = 
    Buildings = 2,
    // Attack harvesters or refineries.
    // Harvesters = 
    Harvesters = 3,
    // Attack infantry.
    // Infantry = 
    Infantry = 4,
    // Attack combat vehicles.
    // Vehicles = 
    Vehicles = 5,
    // Attack factories (all types).
    // Factories = 
    Factories = 6,
    // Attack base defense buildings.
    // Defenses = 
    Defenses = 7,
    // Attack enemies near friendly base.
    // Threats = 
    Threats = 8,
    // Attack power facilities.
    // Power = 
    Power = 9,
    // Prefer to attack occupiable buildings.
    // OccupiableBuildings = 
    OccupiableBuildings = 10,
    // Prefer to attack tech buildings.
    // TechBuildings = 
    TechBuildings = 11,
}
// ThreatType
enum ThreatType {
    // Normal = 0x0
    Normal = 0,
    // Range = 0x1
    Range = 1,
    // Area = 0x2
    Area = 2,
    // Air = 0x4
    Air = 4,
    // Infantry = 0x8
    Infantry = 8,
    // Vehicles = 0x10
    Vehicles = 16,
    // Buildings = 0x20
    Buildings = 32,
    // Tiberium = 0x40
    Tiberium = 64,
    // Boats = 0x80
    Boats = 128,
    // Civilians = 0x100
    Civilians = 256,
    // Capture = 0x200
    Capture = 512,
    // Fakes = 0x400
    Fakes = 1024,
    // Power = 0x800
    Power = 2048,
    // Factories = 0x1000
    Factories = 4096,
    // BaseDefense = 0x2000
    BaseDefense = 8192,
    // Friendlies = 0x4000
    Friendlies = 16384,
    // OccupiableBuildings = 0x8000
    OccupiableBuildings = 32768,
    // TechBuildings = 0x10000
    TechBuildings = 65536,
}
// BlitterFlags
enum BlitterFlags {
    // None = 0x0
    None = 0,
    // Darken = 0x1
    Darken = 1,
    // TransLucent25 = 0x2
    TransLucent25 = 2,
    // TransLucent50 = 0x4
    TransLucent50 = 4,
    // TransLucent75 = 0x6
    TransLucent75 = 6,
    // Warp = 0x8
    Warp = 8,
    // ZRemap = 0x10
    ZRemap = 16,
    // Plain = 0x20
    Plain = 32,
    // bf_040 = 0x40
    bf_040 = 64,
    // bf_080 = 0x80
    bf_080 = 128,
    // MultiPass = 0x100
    MultiPass = 256,
    // Centered = 0x200
    Centered = 512,
    // bf_400 = 0x400
    bf_400 = 1024,
    // Alpha = 0x800
    Alpha = 2048,
    // bf_1000 = 0x1000
    bf_1000 = 4096,
    // Flat = 0x2000
    Flat = 8192,
    // ZRead = 0x3000
    ZRead = 12288,
    // ZReadWrite = 0x4000
    ZReadWrite = 16384,
    // bf_8000 = 0x8000
    bf_8000 = 32768,
    // Zero = 0x10000
    Zero = 65536,
    // Nonzero = 0x20000
    Nonzero = 131072,
}
// UI
// MouseEvent
enum MouseEvent {
    // None = 0x0
    None = 0,
    // LeftDown = 0x1
    LeftDown = 1,
    // LeftHeld = 0x2
    LeftHeld = 2,
    // LeftUp = 0x4
    LeftUp = 4,
    // Move = 0x8
    Move = 8,
    // RightDown = 0x10
    RightDown = 16,
    // RightHeld = 0x20
    RightHeld = 32,
    // RightUp = 0x40
    RightUp = 64,
}
// Edge
enum Edge {
    // None = -1
    None = -1,
    // North = 0
    North = 0,
    // East = 1
    East = 1,
    // South = 2
    South = 2,
    // West = 3
    West = 3,
    // Air = 4
    Air = 4,
}
// Move
enum Move {
    // OK = 0
    OK = 0,
    // Cloak = 1
    Cloak = 1,
    // MovingBlock = 2
    MovingBlock = 2,
    // ClosedGate = 3
    ClosedGate = 3,
    // FriendlyDestroyable = 4
    FriendlyDestroyable = 4,
    // Destroyable = 5
    Destroyable = 5,
    // Temp = 6
    Temp = 6,
    // No = 7
    No = 7,
}
// ZGradient
enum ZGradient {
    // None = -1
    None = -1,
    // Ground = 0
    Ground = 0,
    // Deg45 = 1
    Deg45 = 1,
    // Deg90 = 2
    Deg90 = 2,
    // Deg135 = 3
    Deg135 = 3,
}
// ParasiteState
enum ParasiteState {
    // creates grab animation
    // Start = 0
    Start = 0,
    // wait for the grab anim
    // Grab = 1
    Grab = 1,
    // push the victim, variant A
    // PushLeft = 2
    PushLeft = 2,
    // push the victim, variant B
    // PushRight = 3
    PushRight = 3,
    // wait until rocking stops; deliver damage
    // Damage = 4
    Damage = 4,
}
// WWKey
enum WWKey {
    // Shift = 0x100
    Shift = 256,
    // Ctrl = 0x200
    Ctrl = 512,
    // Alt = 0x400
    Alt = 1024,
    // Release = 0x800
    Release = 2048,
    // VirtualKey = 0x1000
    VirtualKey = 4096,
    // DoubleClick = 0x2000
    DoubleClick = 8192,
    // Button = 0x8000
    Button = 32768,
}
// AircraftClass Attack Mission status codes
// AirAttackStatus
enum AirAttackStatus {
    // ValidateAZ = 0
    ValidateAZ = 0,
    // PickAttackLocation = 1
    PickAttackLocation = 1,
    // TakeOff = 2
    TakeOff = 2,
    // FlyToPosition = 3
    FlyToPosition = 3,
    // FireAtTarget = 4
    FireAtTarget = 4,
    // FireAtTarget2 = 5
    FireAtTarget2 = 5,
    // FireAtTarget2_Strafe = 6
    FireAtTarget2_Strafe = 6,
    // FireAtTarget3_Strafe = 7
    FireAtTarget3_Strafe = 7,
    // FireAtTarget4_Strafe = 8
    FireAtTarget4_Strafe = 8,
    // FireAtTarget5_Strafe = 9
    FireAtTarget5_Strafe = 9,
    // ReturnToBase = 10
    ReturnToBase = 10,
}
// LandTargetingType
enum LandTargetingType {
    // Land_OK = 0
    Land_OK = 0,
    // Land_Not_OK = 1
    Land_Not_OK = 1,
    // Land_Secondary = 2
    Land_Secondary = 2,
}
// NavalTargetingType
enum NavalTargetingType {
    // Underwater_Never = 0
    Underwater_Never = 0,
    // Underwater_Secondary = 1
    Underwater_Secondary = 1,
    // Underwater_Only = 2
    Underwater_Only = 2,
    // Organic_Secondary = 3
    Organic_Secondary = 3,
    // SEAL_Special = 4
    SEAL_Special = 4,
    // Naval_All = 5
    Naval_All = 5,
    // Naval_None = 6
    Naval_None = 6,
    // Naval_Primary = 7
    Naval_Primary = 7,
}
// RGBMode
enum RGBMode {
    // RGB555 = 0
    RGB555 = 0,
    // RGB556 = 1
    RGB556 = 1,
    // RGB565 = 2
    RGB565 = 2,
    // RGB655 = 3
    RGB655 = 3,
    // Invalid = 0x0FFFFFFFF
    Invalid = -1,
}
// ZoneType
enum ZoneType {
    // None = -1
    None = -1,
    // Core = 0
    Core = 0,
    // North = 1
    North = 1,
    // East = 2
    East = 2,
    // South = 3
    South = 3,
    // West = 4
    West = 4,
}
// PCPType
enum PCPType {
    // When sitting in place and performing rotations.
    // Rotation = 0
    Rotation = 0,
    // While moving between two cells. Is this ever used? Tell me if you found any
    // During = 1
    During = 1,
    // When the 'center' of a cell is reached during movement.
    // End = 2
    End = 2,
}
// tagTYPEKIND
enum tagTYPEKIND {
    // TKIND_ENUM = 0
    TKIND_ENUM = 0,
    // TKIND_RECORD = (TKIND_ENUM + 1)
    TKIND_RECORD = 1,
    // TKIND_MODULE = (TKIND_RECORD + 1)
    TKIND_MODULE = 2,
    // TKIND_INTERFACE = (TKIND_MODULE + 1)
    TKIND_INTERFACE = 3,
    // TKIND_DISPATCH = (TKIND_INTERFACE + 1)
    TKIND_DISPATCH = 4,
    // TKIND_COCLASS = (TKIND_DISPATCH + 1)
    TKIND_COCLASS = 5,
    // TKIND_ALIAS = (TKIND_COCLASS + 1)
    TKIND_ALIAS = 6,
    // TKIND_UNION = (TKIND_ALIAS + 1)
    TKIND_UNION = 7,
    // TKIND_MAX = (TKIND_UNION + 1)
    TKIND_MAX = 8,
}
// tagDESCKIND
enum tagDESCKIND {
    // DESCKIND_NONE = 0
    DESCKIND_NONE = 0,
    // DESCKIND_FUNCDESC = (DESCKIND_NONE + 1)
    DESCKIND_FUNCDESC = 1,
    // DESCKIND_VARDESC = (DESCKIND_FUNCDESC + 1)
    DESCKIND_VARDESC = 2,
    // DESCKIND_TYPECOMP = (DESCKIND_VARDESC + 1)
    DESCKIND_TYPECOMP = 3,
    // DESCKIND_IMPLICITAPPOBJ = (DESCKIND_TYPECOMP + 1)
    DESCKIND_IMPLICITAPPOBJ = 4,
    // DESCKIND_MAX = (DESCKIND_IMPLICITAPPOBJ + 1)
    DESCKIND_MAX = 5,
}
// tagFUNCKIND
enum tagFUNCKIND {
    // FUNC_VIRTUAL = 0
    FUNC_VIRTUAL = 0,
    // FUNC_PUREVIRTUAL = (FUNC_VIRTUAL + 1)
    FUNC_PUREVIRTUAL = 1,
    // FUNC_NONVIRTUAL = (FUNC_PUREVIRTUAL + 1)
    FUNC_NONVIRTUAL = 2,
    // FUNC_STATIC = (FUNC_NONVIRTUAL + 1)
    FUNC_STATIC = 3,
    // FUNC_DISPATCH = (FUNC_STATIC + 1)
    FUNC_DISPATCH = 4,
}
// tagINVOKEKIND
enum tagINVOKEKIND {
    // INVOKE_FUNC = 1
    INVOKE_FUNC = 1,
    // INVOKE_PROPERTYGET = 2
    INVOKE_PROPERTYGET = 2,
    // INVOKE_PROPERTYPUT = 4
    INVOKE_PROPERTYPUT = 4,
    // INVOKE_PROPERTYPUTREF = 8
    INVOKE_PROPERTYPUTREF = 8,
}
// tagCALLCONV
enum tagCALLCONV {
    // CC_FASTCALL = 0
    CC_FASTCALL = 0,
    // CC_CDECL = 1
    CC_CDECL = 1,
    // CC_MSCPASCAL = (CC_CDECL + 1)
    CC_MSCPASCAL = 2,
    // CC_PASCAL = CC_MSCPASCAL
    CC_PASCAL = 2,
    // CC_MACPASCAL = (CC_PASCAL + 1)
    CC_MACPASCAL = 3,
    // CC_STDCALL = (CC_MACPASCAL + 1)
    CC_STDCALL = 4,
    // CC_FPFASTCALL = (CC_STDCALL + 1)
    CC_FPFASTCALL = 5,
    // CC_SYSCALL = (CC_FPFASTCALL + 1)
    CC_SYSCALL = 6,
    // CC_MPWCDECL = (CC_SYSCALL + 1)
    CC_MPWCDECL = 7,
    // CC_MPWPASCAL = (CC_MPWCDECL + 1)
    CC_MPWPASCAL = 8,
    // CC_MAX = (CC_MPWPASCAL + 1)
    CC_MAX = 9,
}
// tagVARKIND
enum tagVARKIND {
    // VAR_PERINSTANCE = 0
    VAR_PERINSTANCE = 0,
    // VAR_STATIC = (VAR_PERINSTANCE + 1)
    VAR_STATIC = 1,
    // VAR_CONST = (VAR_STATIC + 1)
    VAR_CONST = 2,
    // VAR_DISPATCH = (VAR_CONST + 1)
    VAR_DISPATCH = 3,
}
// tagSYSKIND
enum tagSYSKIND {
    // SYS_WIN16 = 0
    SYS_WIN16 = 0,
    // SYS_WIN32 = (SYS_WIN16 + 1)
    SYS_WIN32 = 1,
    // SYS_MAC = (SYS_WIN32 + 1)
    SYS_MAC = 2,
    // SYS_WIN64 = (SYS_MAC + 1)
    SYS_WIN64 = 3,
}
// BStateType
enum BStateType {
    // Construction = 0x0
    Construction = 0,
    // Idle = 0x1
    Idle = 1,
    // Active = 0x2
    Active = 2,
    // Full = 0x3
    Full = 3,
    // Aux1 = 0x4
    Aux1 = 4,
    // Aux2 = 0x5
    Aux2 = 5,
    // Count = 0x6
    Count = 6,
    // None = 0xFFFFFFFF
    None = -1,
}
// FileAccessMode
enum FileAccessMode {
    // None = 0
    None = 0,
    // Read = 1
    Read = 1,
    // Write = 2
    Write = 2,
    // ReadWrite = Read | Write
    ReadWrite = 3,
}
// FileSeekMode
enum FileSeekMode {
    // SEEK_SET
    // Set = 0
    Set = 0,
    // SEEK_CUR
    // Current = 1
    Current = 1,
    // SEEK_END
    // End = 2
    End = 2,
}
// SpawnNodeStatus
enum SpawnNodeStatus {
    // docked, waiting for target
    // Idle = 0
    Idle = 0,
    // missile tilting and launch
    // TakeOff = 1
    TakeOff = 1,
    // gathering, waiting
    // Preparing = 2
    Preparing = 2,
    // attacking until no ammo
    // Attacking = 3
    Attacking = 3,
    // return to carrier
    // Returning = 4
    Returning = 4,
    // docked, reloading ammo and health
    // Reloading = 6
    Reloading = 6,
    // respawning
    // Dead = 7
    Dead = 7,
}
// SpawnManagerStatus
enum SpawnManagerStatus {
    // no target or out of range
    // Idle = 0
    Idle = 0,
    // one launch in progress
    // Launching = 1
    Launching = 1,
    // waiting for launch to complete
    // CoolDown = 2
    CoolDown = 2,
}
// SlaveControlStatus
enum SlaveControlStatus {
    // Unknown = 0
    Unknown = 0,
    // ScanningForTiberium = 1
    ScanningForTiberium = 1,
    // MovingToTiberium = 2
    MovingToTiberium = 2,
    // Harvesting = 3
    Harvesting = 3,
    // BringingItBack = 4
    BringingItBack = 4,
    // Respawning = 5
    Respawning = 5,
    // Dead = 6
    Dead = 6,
}
// SlaveManagerStatus
enum SlaveManagerStatus {
    // Ready = 0
    Ready = 0,
    // Scanning = 1
    Scanning = 1,
    // Travelling = 2
    Travelling = 2,
    // Deploying = 3
    Deploying = 3,
    // Working = 4
    Working = 4,
    // ScanningAgain = 5
    ScanningAgain = 5,
    // PackingUp = 6
    PackingUp = 6,
}
// CSFLanguages
enum CSFLanguages {
    // US = 0
    US = 0,
    // UK = 1
    UK = 1,
    // German = 2
    German = 2,
    // French = 3
    French = 3,
    // Spanish = 4
    Spanish = 4,
    // Italian = 5
    Italian = 5,
    // Japanese = 6
    Japanese = 6,
    // Jabberwockie = 7
    Jabberwockie = 7,
    // Korean = 8
    Korean = 8,
    // Chinese = 9
    Chinese = 9,
    // Unknown = 10
    Unknown = 10,
}
// KeyModifier
enum KeyModifier {
    // None = 0
    None = 0,
    // Shift = 1
    Shift = 1,
    // Ctrl = 2
    Ctrl = 2,
    // Alt = 4
    Alt = 4,
}
// GadgetFlag
enum GadgetFlag {
    // LeftPress = 0x1
    LeftPress = 1,
    // LeftHeld = 0x2
    LeftHeld = 2,
    // LeftRelease = 0x4
    LeftRelease = 4,
    // LeftUp = 0x8
    LeftUp = 8,
    // RightPress = 0x10
    RightPress = 16,
    // RightHeld = 0x20
    RightHeld = 32,
    // RightRelease = 0x40
    RightRelease = 64,
    // RightUp = 0x80
    RightUp = 128,
    // Keyboard = 0x100
    Keyboard = 256,
}
}
