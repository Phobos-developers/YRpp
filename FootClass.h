/*
	Base class for units that can move (that have "feet")
*/

#pragma once

#include <TechnoClass.h>
#include <ParasiteClass.h>

//forward declarations
class LocomotionClass;
class TeamClass;

class NOVTABLE FootClass : public TechnoClass
{
public:
	static const auto AbsDerivateID = AbstractFlags::Foot;

	DEFINE_REFERENCE(DynamicVectorClass<FootClass*>, Array, 0x8B3DC0u)

	//IPersistStream
	//Destructor
	virtual ~FootClass() RX;

	//AbstractClass
	//ObjectClass
	//MissionClass

	virtual int Mission_AreaGuard() override { JMP_THIS(0x4D6AA0); }

	//TechnoClass
	virtual void Destroyed(ObjectClass *Killer) RX;
	virtual bool ForceCreate(CoordStruct& coord, DWORD dwUnk = 0) R0;
	virtual AbstractClass* GreatestThreat(ThreatType threat, CoordStruct* pCoord, bool onlyTargetHouseEnemy) override { JMP_THIS(0x4D9920) };

	//FootClass
	virtual void ReceiveGunner(FootClass* Gunner) RX;
	virtual void RemoveGunner(FootClass* Gunner) RX;
	virtual bool IsLeavingMap() const R0;
	virtual bool vt_entry_4E0() const R0;
	virtual bool CanDeployNow() const R0;
	virtual void AddSensorsAt(CellStruct cell) RX;
	virtual void RemoveSensorsAt(CellStruct cell) RX;
	virtual CoordStruct* vt_entry_4F0(CoordStruct* pCrd) R0;
	virtual void vt_entry_4F4() RX;
	virtual bool vt_entry_4F8() R0;
	virtual bool MoveTo(CoordStruct* pCrd) R0;
	virtual bool StopMoving() R0;
	virtual bool TryEnterIdle() R0;
	virtual bool ChronoWarpTo(CoordStruct pDest) R0; // fsds... only implemented for one new YR map trigger, other chrono events repeat the code...
	virtual void Draw_A_SHP(
		SHPStruct *SHP, int idxFacing, Point2D * Coords, RectangleStruct *Rectangle,
		DWORD dwUnk5, DWORD dwUnk6, DWORD dwUnk7, ZGradient ZGradient,
		DWORD dwUnk9, int extraLight, DWORD dwUnk11, DWORD dwUnk12,
		DWORD dwUnk13, DWORD dwUnk14, DWORD dwUnk15, DWORD dwUnk16) RX;

	virtual void Draw_A_VXL(
		VoxelStruct *VXL, int HVAFrameIndex, int Flags, IndexClass<int, int> *Cache, RectangleStruct *Rectangle,
		Point2D *CenterPoint, Matrix3D *Matrix, DWORD dwUnk8, DWORD DrawFlags, DWORD dwUnk10) RX;

	virtual void GoBerzerk() RX;
	virtual void Panic() RX;
	virtual void UnPanic() RX; //never
	virtual void PlayIdleAnim(int nIdleAnimNumber) RX;
	virtual DWORD vt_entry_524() R0;
	virtual BuildingClass* TryNearestDockBuilding(TypeList<BuildingTypeClass*>* bList, DWORD dwUnk2, DWORD dwUnk3) const R0;
	virtual BuildingClass* FindCloserDockBuilding(BuildingTypeClass* bType, DWORD dwUnk2, DWORD dwUnk3, int* pDistance) const R0;
	virtual BuildingClass* FindNearestDockBuilding(BuildingTypeClass* bType, DWORD dwUnk2, DWORD dwUnk3) const R0;
	virtual void TryCrushCell(const CellStruct& cell, bool warn) RX;
	virtual int GetCurrentSpeed() const R0;
	virtual AbstractClass* vt_entry_53C(DWORD dwUnk) R0;
	virtual void vt_entry_540(DWORD dwUnk) RX;
	virtual void SetSpeedPercentage(double percentage) RX;
	virtual void vt_entry_548() RX;
	virtual void vt_entry_54C() RX;
	virtual bool IsLandZoneClear(AbstractClass* pDestination) R0;

	bool CanBeRecruited(HouseClass *ByWhom) const
		{ JMP_THIS(0x4DA230); }

	// non-virtual

	// only used by squid damage routines, normal wakes are created differently it seems
	// creates 3 wake animations behind the unit
	void CreateWakes(CoordStruct coords)
		{ JMP_THIS(0x629E90); }

	// can this jumpjet stay in this cell or not? (two jumpjets in one cell are not okay, locomotor kicks one of them out in the next frame)
	bool Jumpjet_LocationClear() const
		{ JMP_THIS(0x4135A0); }

	void Jumpjet_OccupyCell(CellStruct Cell)
		{ JMP_THIS(0x4E00B0); }

	// changes locomotor to the given one, Magnetron style
	// mind that this locks up the source too, Magnetron style
	void FootClass_ImbueLocomotor(FootClass *target, CLSID clsid)
		{ JMP_THIS(0x710000); }

	// var $this = this; $.each($this.Passengers, function(ix, p) { p.Location = $this.Location; });
	void UpdatePassengerCoords()
		{ JMP_THIS(0x7104F0); }

	void AbortMotion()
		{ JMP_THIS(0x4DF0D0); }

	bool UpdatePathfinding(CellStruct destinationCell, BOOL restart, int mode)
		{ JMP_THIS(0x4D3920); }

	// Removes the first passenger and updates the Gunner.
	FootClass* RemoveFirstPassenger()
		{ JMP_THIS(0x4DE710); }

	// Removes a specific passenger and updates the Gunner.
	FootClass* RemovePassenger(FootClass* pPassenger)
		{ JMP_THIS(0x4DE670); }

	// Adds a specific passenger and updates the Gunner.
	void EnterAsPassenger(FootClass* pPassenger)
		{ JMP_THIS(0x4DE630); }

	// Adds to the NavQueue
	void QueueNavigationList(AbstractClass * target)
	{ JMP_THIS(0x4DA0E0); }

	// Clears NavQueue
	void ClearNavigationList()
		{ JMP_THIS(0x4DA1C0); }

	// searches cell, sets destination, and returns whether unit is on that cell
	bool MoveToTiberium(int radius, bool scanClose = false)
		{ JMP_THIS(0x4DCFE0); }

	// searches cell, sets destination, and returns whether unit is on that cell
	bool MoveToWeed(int radius)
		{ JMP_THIS(0x4DDB90); }

	//Constructor
	FootClass(HouseClass* pOwner) noexcept : FootClass(noinit_t())
		{ JMP_THIS(0x4D31E0); }

protected:
	explicit __forceinline FootClass(noinit_t) noexcept
		: TechnoClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int             PlanningPathIdx; // which planning path am I following?
	CellStruct      WaypointNearbyAccessibleCellDelta; // add to WaypointCell to get Nearby_Cell for this foot
	CellStruct      WaypointCell; // current waypoint cell
	DWORD           unknown_52C;	//unused?
	DWORD           unknown_530;
	DWORD           unknown_534;
	int				WalkedFramesSoFar;
	bool            IsMoveSoundPlaying;
	int             MoveSoundDelay;

	DECLARE_PROPERTY(AudioController, MoveSoundAudioController);

	CellStruct      CurrentMapCoords;
	CellStruct      LastMapCoords; // ::UpdatePosition uses this to remove threat from last occupied cell, etc
	CellStruct      LastFlightMapCoords; // which cell was I occupying previously? only for AircraftTracker-tracked stuff
	CellStruct      CurrentJumpjetMapCoords; // unconfirmed, which cell am I occupying? only for jumpjets
	CoordStruct     CurrentTunnelCoords;
	PROTECTED_PROPERTY(DWORD,   unused_574);
	double          SpeedPercentage;
	double          SpeedMultiplier;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, unknown_abstract_array_588);
	AbstractClass*  unknown_5A0;
	AbstractClass*  Destination; // possibly other objects as well
	AbstractClass*  LastDestination;
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, NavQueue); // Stores sequence of movement destinations
	Mission         MegaMission; // only Mission::AttackMove or Mission::None
	AbstractClass*  MegaDestination; // when AttackMove target is a cell
	AbstractClass*  MegaTarget; // when AttackMove target is an object
	BYTE            unknown_5D0;	//unused?
	bool            HaveAttackMoveTarget; // fighting an enemy on the way
	TeamClass*      Team;
	FootClass*      NextTeamMember;        //next unit in team
	DWORD           unknown_5DC;
	int             PathDirections[24]; // list of directions to move in next, like tube directions
	DECLARE_PROPERTY(CDTimerClass, PathDelayTimer);
	int             PathWaitTimes;
	DECLARE_PROPERTY(CDTimerClass, unknown_timer_650);
	DECLARE_PROPERTY(CDTimerClass, SightTimer);
	DECLARE_PROPERTY(CDTimerClass, BlockagePathTimer);
	DECLARE_PROPERTY(ILocomotionPtr, Locomotor);
	CoordStruct       unknown_point3d_678;
	signed char       TubeIndex;	//I'm in this tunnel
	signed char       TubeFaceIndex;
	signed char       WaypointIndex; // which waypoint in my planning path am I following?
	bool              ShouldScatterInNextIdle;
	bool              IsScanLimited;
	bool              IsInitiated; // Is a fully joined member of a team, used for regroup etc. checks
	bool              ShouldScanForTarget;
	bool              unknown_bool_68B; //unused?
	bool              IsDeploying;
	bool              IsFiring;
	bool              unknown_bool_68E;
	bool              ShouldEnterAbsorber; // orders the unit to enter the closest bio reactor
	bool              ShouldEnterOccupiable; // orders the unit to enter the closest battle bunker
	bool              ShouldGarrisonStructure; // orders the unit to enter the closest neutral building
	FootClass*        ParasiteEatingMe; // the tdrone/squid that's eating me
	int               LastBeParasitedStartFrame;
	ParasiteClass*    ParasiteImUsing;	// my parasitic half, nonzero for, eg, terror drone or squiddy
	DECLARE_PROPERTY(CDTimerClass, ParalysisTimer); // for squid victims
	bool              unknown_bool_6AC;
	bool              IsAttackedByLocomotor; // the unit's locomotor is jammed by a magnetron
	bool              IsLetGoByLocomotor; // a magnetron attacked this unit and let it go. falling, landing, or sitting on the ground
	bool              unknown_bool_6AF;
	bool              unknown_bool_6B0;
	bool              unknown_bool_6B1;
	bool              unknown_bool_6B2;
	bool              unknown_bool_6B3;
	bool              unknown_bool_6B4;
	bool              IsCrushingSomething;
	bool              FrozenStill; // frozen in first frame of the proper facing - when magnetron'd or warping
	bool              IsWaitingBlockagePath;
	bool              unknown_bool_6B8;
	PROTECTED_PROPERTY(DWORD,   unused_6BC);	//???
};

static_assert(sizeof(FootClass) == 0x6C0);
