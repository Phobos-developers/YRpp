/*
	Base class for buildable objects
*/

#pragma once

#include <Matrix3D.h>
#include <RadioClass.h>
#include <RadBeam.h>
#include <TechnoTypeClass.h>
#include <CaptureManagerClass.h>
#include <SlaveManagerClass.h>
#include <TeamClass.h>
#include <TemporalClass.h>
#include <LaserDrawClass.h>
#include <Helpers/Template.h>
#include <StageClass.h>
#include <PlanningTokenClass.h>

//forward declarations
class AirstrikeClass;
class AnimClass;
class BulletClass;
class BuildingClass;
class CellClass;
class HouseClass;
class FootClass;
class HouseClass;
class InfantryTypeClass;
class ObjectTypeClass;
class ParticleSystemClass;
class SpawnManagerClass;
class WaveClass;

class EventClass;

#include <TransitionTimer.h>

struct VeterancyStruct
{
	VeterancyStruct() = default;

	explicit VeterancyStruct(double value) noexcept
	{
		this->Add(value);
	}

	void Add(int ownerCost, int victimCost) noexcept
	{
		this->Add(static_cast<double>(victimCost)
			/ (ownerCost * RulesClass::Instance->VeteranRatio));
	}

	void Add(double value) noexcept
	{
		auto val = this->Veterancy + value;

		if (val > RulesClass::Instance->VeteranCap)
		{
			val = RulesClass::Instance->VeteranCap;
		}

		this->Veterancy = static_cast<float>(val);
	}

	Rank GetRemainingLevel() const noexcept
	{
		if (this->Veterancy >= 2.0f)
		{
			return Rank::Elite;
		}

		if (this->Veterancy >= 1.0f)
		{
			return Rank::Veteran;
		}

		return Rank::Rookie;
	}

	bool IsNegative() const noexcept
	{
		return this->Veterancy < 0.0f;
	}

	bool IsRookie() const noexcept
	{
		return this->Veterancy >= 0.0f && this->Veterancy < 1.0f;
	}

	bool IsVeteran() const noexcept
	{
		return this->Veterancy >= 1.0f && this->Veterancy < 2.0f;
	}

	bool IsElite() const noexcept
	{
		return this->Veterancy >= 2.0f;
	}

	void Reset() noexcept
	{
		this->Veterancy = 0.0f;
	}

	void SetRookie(bool notReally = true) noexcept
	{
		this->Veterancy = notReally ? -0.25f : 0.0f;
	}

	void SetVeteran(bool yesReally = true) noexcept
	{
		this->Veterancy = yesReally ? 1.0f : 0.0f;
	}

	void SetElite(bool yesReally = true) noexcept
	{
		this->Veterancy = yesReally ? 2.0f : 0.0f;
	}

	float Veterancy { 0.0f };
};

class PassengersClass
{
public:
	int NumPassengers;
	FootClass* FirstPassenger;

	void AddPassenger(FootClass* pPassenger)
	{ JMP_THIS(0x4733A0); }

	void RemovePassenger(FootClass* pPassenger)
	{ JMP_THIS(0x4734B0); }

	FootClass* GetFirstPassenger() const
	{ return this->FirstPassenger; }

	FootClass* RemoveFirstPassenger()
	{ JMP_THIS(0x473430); }

	int GetTotalSize() const
	{ JMP_THIS(0x473460); }

	int IndexOf(FootClass* candidate) const
	{ JMP_THIS(0x473500); }

	PassengersClass() : NumPassengers(0), FirstPassenger(nullptr) { };

	~PassengersClass() { };
};

struct FlashData
{
	int DurationRemaining;
	bool FlashingNow;

	bool Update()
	{ JMP_THIS(0x4CC770); }
};

struct RecoilData
{
	enum class RecoilState : unsigned int
	{
		Inactive = 0,
		Compressing = 1,
		Holding = 2,
		Recovering = 3,
	};

	TurretControl Turret;
	float TravelPerFrame;
	float TravelSoFar;
	RecoilState State;
	int TravelFramesLeft;

	void Update()
	{ JMP_THIS(0x70ED10); }

	void Fire()
	{ JMP_THIS(0x70ECE0); }
};

class NOVTABLE TechnoClass : public RadioClass
{
public:
	static const auto AbsDerivateID = AbstractFlags::Techno;

	DEFINE_REFERENCE(DynamicVectorClass<TechnoClass*>, Array, 0xA8EC78u)

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~TechnoClass() RX;

	//ObjectClass
	virtual bool Limbo() override JMP_THIS(0x6F6AC0);

	//TechnoClass
	virtual bool IsUnitFactory() const R0;
	virtual bool IsCloakable() const R0;
	virtual bool CanScatter() const R0;
	virtual bool BelongsToATeam() const R0;
	virtual bool ShouldSelfHealOneStep() const R0;
	virtual bool IsVoxel() const R0;
	virtual bool vt_entry_29C() R0;
	virtual bool IsReadyToCloak() const JMP_THIS(0x6FBDC0);
	virtual bool ShouldNotBeCloaked() const JMP_THIS(0x6FBC90);
	virtual DirStruct* TurretFacing(DirStruct* pBuffer) const R0;
	virtual bool IsArmed() const R0; // GetWeapon(primary) && GetWeapon(primary)->WeaponType
	virtual bool vt_entry_2B0() const R0;
	virtual double GetStoragePercentage() const R0;
	virtual int GetPipFillLevel() const R0;
	virtual int GetRefund() const R0;
	virtual int GetThreatValue() const R0;
	virtual bool IsInSameZoneAs(AbstractClass* pTarget) R0;          // Is the target reachable?
	virtual DWORD vt_entry_2C8(DWORD dwUnk, DWORD dwUnk2) R0;
	virtual bool IsInSameZoneAsCoords(const CoordStruct& coord) R0;  // Are the coords reachable?
	virtual int GetCrewCount() const JMP_THIS(0x6F3950);
	virtual int GetAntiAirValue() const R0;
	virtual int GetAntiArmorValue() const R0;
	virtual int GetAntiInfantryValue() const R0;
	virtual void GotHijacked() RX;
	virtual int SelectWeapon(AbstractClass* pTarget) const R0;
	virtual int SelectNavalTargeting(AbstractClass* pTarget) const R0;
	virtual int GetZAdjustment() const R0;
	virtual ZGradient GetZGradient() const RT(ZGradient);
	virtual CellStruct GetLastFlightMapCoords() const RT(CellStruct);
	virtual void SetLastFlightMapCoords(CellStruct coord) RX;
	virtual CellStruct* vt_entry_2FC(CellStruct* Buffer, DWORD dwUnk2, DWORD dwUnk3) const R0;
	virtual CoordStruct* vt_entry_300(CoordStruct* Buffer, DWORD dwUnk2) const R0;
	virtual DWORD vt_entry_304(DWORD dwUnk, DWORD dwUnk2) const R0;
	virtual DirStruct* GetRealFacing(DirStruct* pBuffer) const R0;
	virtual InfantryTypeClass* GetCrew() const R0;
	virtual bool vt_entry_310() const R0;
	virtual bool CanDeploySlashUnload() const R0;
	virtual int GetROF(int nWeapon) const R0;
	// Parameter controls behaviour. Unlisted values behave same as 1.
	// -1 = returns -1 as range
	// 0  = uses GuardRange/weapon range as is
	// 1  = doubles range, if less than 0 increase to 0, if more than 4096 leptons cap it at that
	// 2  = doubles range, if less than 1792 leptons increase to 1792, if more than that return as is unless more than 4096 in which case cap at 4096.
	virtual int GetGuardRange(int control) const R0;
	virtual bool vt_entry_320() const R0;
	virtual bool IsRadarVisible(int* pOutDetection) const R0; // out value will be set to 1 if unit is cloaked and 2 if it is subterranean, otherwise it's unchanged
	virtual bool IsSensorVisibleToPlayer() const R0;
	virtual bool IsSensorVisibleToHouse(HouseClass* House) const R0;
	virtual bool IsEngineer() const R0;
	virtual void ProceedToNextPlanningWaypoint() RX;
	virtual CellStruct* ScanForTiberium(CellStruct*, int range, DWORD dwUnk3) const R0;
	virtual bool EnterGrinder() R0;
	virtual bool EnterBioReactor() R0;
	virtual bool EnterTankBunker() R0;
	virtual bool EnterBattleBunker() R0;
	virtual bool GarrisonStructure() R0;
	virtual bool IsPowerOnline() const R0;
	virtual void QueueVoice(int idxVoc) RX;
	virtual int VoiceEnter() R0;
	virtual int VoiceHarvest() R0;
	virtual int VoiceSelect() R0;
	virtual int VoiceCapture() R0;
	virtual int VoiceMove() R0;
	virtual int VoiceDeploy() R0;
	virtual int VoiceAttack(ObjectClass* pTarget) R0;
	virtual bool ClickedEvent(EventType event) R0;

	// depending on the mission you click, cells/Target are not always needed
	virtual bool ClickedMission(Mission Mission, ObjectClass* pTarget, CellClass* TargetCell, CellClass* NearestTargetCellICanEnter) R0;
	virtual bool IsUnderEMP() const R0;
	virtual bool IsParalyzed() const R0;
	virtual bool CanCheer() const R0;
	virtual void Cheer(bool Force) RX;
	virtual int GetDefaultSpeed() const R0;
	virtual void DecreaseAmmo() RX;
	virtual void AddPassenger(FootClass* pPassenger) RX;
	virtual bool CanDisguiseAs(AbstractClass* pTarget) const R0;
	virtual bool TargetAndEstimateDamage(CoordStruct& coord, ThreatType threat) R0;
	virtual void Stun() RX;
	virtual bool TriggersCellInset(AbstractClass* pTarget) R0;
	virtual bool IsCloseEnough(AbstractClass* pTarget, int idxWeapon) const R0;
	virtual bool IsCloseEnoughToAttack(AbstractClass* pTarget) const R0;
	virtual bool IsCloseEnoughToAttackCoords(const CoordStruct& Coords) const R0;
	virtual bool InAuxiliarySearchRange(AbstractClass* pTarget) const R0;
	virtual void Destroyed(ObjectClass* Killer) = 0;
	virtual FireError GetFireErrorWithoutRange(AbstractClass* pTarget, int nWeaponIndex) const RT(FireError);
	virtual FireError GetFireError(AbstractClass* pTarget, int nWeaponIndex, bool ignoreRange) const RT(FireError);
	virtual AbstractClass* GreatestThreat(ThreatType threat, CoordStruct* pCoord, bool onlyTargetHouseEnemy) JMP_THIS(0x6F8DF0);
	virtual void SetTarget(AbstractClass* pTarget) JMP_THIS(0x6FCDB0);
	virtual BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) R0;
	virtual void Guard() RX; // clears target and destination and puts in guard mission
	virtual bool SetOwningHouse(HouseClass* pHouse, bool announce = true) R0;
	virtual void vt_entry_3D8(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3) RX;
	virtual bool Crash(ObjectClass* Killer) R0;
	virtual bool IsAreaFire() const R0;
	virtual int IsNotSprayAttack() const R0;
	virtual int GetSecondaryWeaponIndex() const R0;
	virtual int IsNotSprayAttack2() const R0;
	virtual WeaponStruct* GetDeployWeapon() const R0;
	virtual WeaponStruct* GetTurretWeapon() const JMP_THIS(0x70E1A0);
	virtual WeaponStruct* GetWeapon(int nWeaponIndex) const R0;
	virtual bool HasTurret() const R0;
	virtual bool CanOccupyFire() const R0;
	virtual int GetOccupyRangeBonus() const R0;
	virtual int GetOccupantCount() const R0;
	virtual void OnFinishRepair() RX;
	virtual void UpdateCloak(bool bUnk = 1) RX;
	virtual void CreateGap() RX;
	virtual void DestroyGap() RX;
	virtual void vt_entry_41C() RX;
	virtual void Sensed() RX;
	virtual void Reload() RX;
	virtual void vt_entry_428() RX;
	// Returns target's coordinates if on attack mission & have target, otherwise own coordinates.
	virtual CoordStruct* GetAttackCoordinates(CoordStruct* pCrd) const R0;
	virtual bool IsNotWarpingIn() const R0;
	virtual bool vt_entry_434(DWORD dwUnk) const R0;
	virtual void DrawActionLines(bool Force, DWORD dwUnk2) RX;
	virtual DWORD GetDisguiseFlags(DWORD existingFlags) const R0;
	virtual bool IsClearlyVisibleTo(HouseClass* House) const R0; // can House see right through my disguise?
	virtual void DrawVoxel(const VoxelStruct& Voxel, DWORD dwUnk2, short Facing,
		const IndexClass<int, int>& VoxelIndex, const RectangleStruct& Rect, const Point2D& Location,
		const Matrix3D& Matrix, int Intensity, DWORD dwUnk9, DWORD dwUnk10) RX;
	virtual void vt_entry_448(DWORD dwUnk, DWORD dwUnk2) RX;
	virtual void DrawHealthBar(Point2D* pLocation, RectangleStruct* pBounds, bool bUnk3) const RX;
	virtual void DrawPipScalePips(Point2D* pLocation, Point2D* pOriginalLocation, RectangleStruct* pBounds) const RX;
	virtual void DrawVeterancyPips(Point2D* pLocation, RectangleStruct* pBounds) const RX;
	virtual void DrawExtraInfo(Point2D const& location, Point2D const& originalLocation, RectangleStruct const& bounds) const RX;
	virtual void Uncloak(bool bPlaySound) RX;
	virtual void Cloak(bool bPlaySound) RX;
	virtual int GetFlashingIntensity(int currentIntensity) const R0;
	virtual void UpdateRefinerySmokeSystems() RX;
	virtual DWORD DisguiseAs(AbstractClass* pTarget) JMP_THIS(0x70E280);
	virtual void ClearDisguise() RX;
	virtual bool IsItTimeForIdleActionYet() const R0;
	virtual bool UpdateIdleAction() R0;
	virtual void vt_entry_47C(DWORD dwUnk) RX;
	virtual void SetDestination(AbstractClass* pDest, bool bUnk) RX;
	virtual bool EnterIdleMode(bool initial, bool unused) R0;
	virtual void UpdateSight(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3, DWORD dwUnk4, DWORD dwUnk5) RX;
	virtual void vt_entry_48C(DWORD dwUnk, DWORD dwUnk2, DWORD dwUnk3, DWORD dwUnk4) RX;
	virtual bool ForceCreate(CoordStruct& coord, DWORD dwUnk = 0) R0;
	virtual void RadarTrackingStart() RX;
	virtual void RadarTrackingStop() RX;
	virtual void RadarTrackingFlash() RX;
	virtual void RadarTrackingUpdate(bool bUnk) RX;
	virtual Mission RespondMegaEventMission(EventClass* pRespondTo) RT(Mission);
	virtual void ClearMegaMissionData() RX;
	virtual bool HaveMegaMission() const R0;
	virtual bool HaveAttackMoveTarget() const R0;
	virtual Mission GetMegaMission() const RT(Mission);
	virtual CoordStruct* GetAttackMoveCoords(CoordStruct* pBuffer) R0;
	virtual bool CanUseWaypoint() const R0;
	virtual bool CanAttackOnTheMove() const R0;
	virtual bool MegaMissionIsAttackMove() const R0;
	virtual bool ContinueMegaMission() R0;
	virtual void UpdateAttackMove() RX;
	virtual bool RefreshMegaMission() R0;

	//non-virtual

	// (re-)starts the reload timer
	void StartReloading()
	{ JMP_THIS(0x6FB080); }

	bool ShouldSuppress(CellStruct* coords) const
	{ JMP_THIS(0x6F79A0); }

	// smooth operator
	const char* get_ID() const
	{
		auto const pType = this->GetType();
		return pType ? pType->get_ID() : nullptr;
	}

	int TimeToBuild() const
	{ JMP_THIS(0x6F47A0); }

	bool IsMindControlled() const
	{ JMP_THIS(0x7105E0); }

	bool CanBePermaMindControlled() const
	{ JMP_THIS(0x53C450); }

	LaserDrawClass* CreateLaser(ObjectClass* pTarget, int idxWeapon, WeaponTypeClass* pWeapon, const CoordStruct& Coords)
	{ JMP_THIS(0x6FD210); }

	/*
	 *  Cell->AddThreat(this->Owner, -this->ThreatPosed);
	 *  this->ThreatPosed = 0;
	 *  int Threat = this->CalculateThreat(); // this is another gem of a function, to be revealed another time...
	 *  this->ThreatPosed = Threat;
	 *  Cell->AddThreat(this->Owner, Threat);
	 */
	void UpdateThreatInCell(CellClass* Cell)
	{ JMP_THIS(0x70F6E0); }

	// CanTargetWhatAmI is a bitfield, if(!(CanTargetWhatAmI & (1 << tgt->WhatAmI())) { fail; }

	// slave of the next one
	bool CanAutoTargetObject(
		ThreatType targetFlags,
		int canTargetWhatAmI,
		int wantedDistance,
		TechnoClass* pTarget,
		int* pThreatPosed,
		DWORD dwUnk,
		CoordStruct* pSourceCoords) const
	{
		JMP_THIS(0x6F7CA0);
	}

	// called by AITeam Attack Target Type and autoscan
	bool TryAutoTargetObject(
		ThreatType targetFlags,
		int canTargetWhatAmI,
		CellStruct* pCoords,
		DWORD dwUnk1,
		DWORD* dwUnk2,
		int* pThreatPosed,
		DWORD dwUnk3)
	{
		JMP_THIS(0x6F8960);
	}

	void Reactivate()
	{ JMP_THIS(0x70FBE0); }

	void Deactivate()
	{ JMP_THIS(0x70FC90); }


	// this should be the transport, but it's unused
	// marks passenger as "InOpenTopped" for targeting, range scanning and other purposes
	void EnteredOpenTopped(TechnoClass* pWho)
	{ JMP_THIS(0x710470); }

	// this should be the transport, but it's unused
	// reverses the above
	void ExitedOpenTopped(TechnoClass* pWho)
	{ JMP_THIS(0x7104A0); }

	// called when the source unit dies - passengers are about to get kicked out, this basically calls ->ExitedOpenTransport on each passenger
	void MarkPassengersAsExited()
	{ JMP_THIS(0x7104C0); }

	bool IsAbsorbAllowed() const
	{ JMP_THIS(0x4598A0); }

	// for gattlings
	void SetCurrentWeaponStage(int idx)
	{ JMP_THIS(0x70DDD0); }

	void SetArchiveTarget(AbstractClass* pTarget)
	{ JMP_THIS(0x70C610); }

	void DrawVoxelShadow(VoxelStruct* vxl, int shadow_index, VoxelIndexKey vxl_index_key, IndexClass<ShadowVoxelIndexKey, VoxelCacheStruct*>* shadow_cache,
		RectangleStruct* bound, Point2D* a3, Matrix3D* matrix, bool again, Surface* surface, Point2D shadow_point)
	{
		JMP_THIS(0x706BD0);
	}

	void DrawObject(SHPStruct* pSHP, int nFrame, Point2D* pLocation, RectangleStruct* pBounds,
		int, int, int nZAdjust, ZGradient eZGradientDescIdx, int, int nBrightness, int TintColor,
		SHPStruct* pZShape, int nZFrame, int nZOffsetX, int nZOffsetY, int);

	double ThreatCoeffients(const ObjectClass* pTarget, const CoordStruct* pLocation) const
	{ JMP_THIS(0x70CD10); }

	int sub_70DE00(int State)
	{ JMP_THIS(0x70DE00); }

	int __fastcall ClearPlanningTokens(EventClass* pEvent)
	{ JMP_STD(0x6386E0); }

	void SetTargetForPassengers(AbstractClass* pTarget)
	{ JMP_THIS(0x710550); }

	void KillPassengers(TechnoClass* pSource)
	{ JMP_THIS(0x707CB0); }

	// returns the house that created this object (factoring in Mind Control)
	HouseClass* GetOriginalOwner() const
	{ JMP_THIS(0x70F820); }

	// returns the house that controls this techno (replaces the ID with player's ID if needed)
	int GetControllingHouse() const
	{ JMP_THIS(0x6339B0); }

	void FireDeathWeapon(int additionalDamage)
	{ JMP_THIS(0x70D690); }

	bool HasAbility(Ability ability) const
	{ JMP_THIS(0x70D0D0); }

	void ClearSidebarTabObject() const
	{ JMP_THIS(0x734270); }

	LightConvertClass* GetDrawer() const
	{ JMP_THIS(0x705D70); }

	int GetEffectTintIntensity(int currentIntensity) const
	{ JMP_THIS(0x70E360); }

	int GetInvulnerabilityTintIntensity(int currentIntensity) const
	{ JMP_THIS(0x70E380); }

	int GetAirstrikeTintIntensity(int currentIntensity) const
	{ JMP_THIS(0x70E4B0); }

	int CombatDamage(int nWeaponIndex) const
	{ JMP_THIS(0x6F3970); }

	WeaponStruct* GetPrimaryWeapon() const
	{ JMP_THIS(0x70E1A0); }

	bool TryNextPlanningTokenNode()
	{ JMP_THIS(0x6385C0); }

	int GetIonCannonValue(AIDifficulty difficulty) const;

	int GetIonCannonValue(AIDifficulty difficulty, int maxHealth) const
	{
		// what TS does
		if (maxHealth > 0 && this->Health > maxHealth)
		{
			return (this->WhatAmI() == AbstractType::Building) ? 3 : 1;
		}

		return this->GetIonCannonValue(difficulty);
	}

	DirStruct TurretFacing() const
	{
		DirStruct ret;
		this->TurretFacing(&ret);
		return ret;
	}

	DirStruct GetRealFacing() const
	{
		DirStruct ret;
		this->GetRealFacing(&ret);
		return ret;
	}

	// Invokes AI response on their 'base' being attacked. Used by buildings, ToProtect=true technos and Whiner=true team members.
	void BaseIsAttacked(TechnoClass* pEnemy)
	{ JMP_THIS(0x708080); }

	bool CanRetaliateToAttacker(ObjectClass* pAttacker, WarheadTypeClass* pWH)
	{ JMP_THIS(0x7087C0); }

	void GattlingRateUp(int value)
	{ JMP_THIS(0x70DE70); }

	void GattlingRateDown(int value)
	{ JMP_THIS(0x70E000); }

	void ReleaseLocomotor(bool setTarget)
	{ JMP_THIS(0x70FEE0); }

	// changes locomotor to the given one, Magnetron style
	// mind that this locks up the source too, Magnetron style
	void ImbueLocomotor(FootClass* target, CLSID clsid)
	{ JMP_THIS(0x710000); }

	CellStruct* NearbyLocation(CellStruct* pCell, AbstractClass* pDest)
		{ JMP_THIS(0x703590); }

	bool CanPassiveAcquireTargets()
		{ JMP_THIS(0x7091D0); }

	bool TargetingTimerFinished()
		{ JMP_THIS(0x70F7E0); }

	bool CanOpportunityFire()
	{ JMP_THIS(0x709290); }

	//Constructor
	TechnoClass(HouseClass* pOwner) noexcept
		: TechnoClass(noinit_t())
	{
		JMP_THIS(0x6F2B40);
	}

protected:
	explicit __forceinline TechnoClass(noinit_t) noexcept
		: RadioClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
public:
	DECLARE_PROPERTY(FlashData, Flashing);
	DECLARE_PROPERTY(StageClass, Animation); // how the unit animates
	DECLARE_PROPERTY(PassengersClass, Passengers);
	TechnoClass*     Transporter; // unit carrying me
	int              LastFireBulletFrame;
	int              CurrentTurretNumber; // for IFV/gattling/charge turrets
	int              unknown_int_128;
	AnimClass*       BehindAnim;
	AnimClass*       DeployAnim;
	bool             InAir;
	int              CurrentWeaponNumber; // for IFV/gattling
	Rank             CurrentRanking; // only used for promotion detection
	int              CurrentGattlingStage;
	int              GattlingValue; // sum of RateUps and RateDowns
	int              TurretAnimFrame;
	HouseClass* InitialOwner; // only set in ctor
	DECLARE_PROPERTY(VeterancyStruct, Veterancy);
	DWORD            align_154;
	double           ArmorMultiplier;
	double           FirepowerMultiplier;
	DECLARE_PROPERTY(CDTimerClass, IdleActionTimer); // MOO
	DECLARE_PROPERTY(CDTimerClass, RadarFlashTimer);
	DECLARE_PROPERTY(CDTimerClass, TargetingTimer); //Duration = 45 on init!
	DECLARE_PROPERTY(CDTimerClass, IronCurtainTimer);
	DECLARE_PROPERTY(CDTimerClass, IronTintTimer); // how often to alternate the effect color
	int              IronTintStage; // ^
	DECLARE_PROPERTY(CDTimerClass, AirstrikeTimer);
	DECLARE_PROPERTY(CDTimerClass, AirstrikeTintTimer); // tracks alternation of the effect color
	DWORD            AirstrikeTintStage; //  ^
	int              ForceShielded;	//0 or 1, NOT a bool - is this under ForceShield as opposed to IC?
	bool             Deactivated; //Robot Tanks without power for instance
	TechnoClass*     DrainTarget; // eg Disk -> PowerPlant, this points to PowerPlant
	TechnoClass*     DrainingMe;  // eg Disk -> PowerPlant, this points to Disk
	AnimClass*       DrainAnim;
	bool             Disguised;
	DWORD            DisguiseCreationFrame;
	DECLARE_PROPERTY(CDTimerClass, InfantryBlinkTimer); // Rules->InfantryBlinkDisguiseTime , detects mirage firing per description
	DECLARE_PROPERTY(CDTimerClass, DisguiseBlinkTimer); // disguise disruption timer
	bool             UnlimboingInfantry;
	DECLARE_PROPERTY(CDTimerClass, ReloadTimer);
	Point2D          RadarPosition;

	// WARNING! this is actually an index of HouseTypeClass es, but it's being changed to fix typical WW bugs.
	DECLARE_PROPERTY(IndexBitfield<HouseClass*>, DisplayProductionTo); // each bit corresponds to one player on the map, telling us whether that player has (1) or hasn't (0) spied this building, and the game should display what's being produced inside it to that player. The bits are arranged by player ID, i.e. bit 0 refers to house #0 in HouseClass::Array, 1 to 1, etc.; query like ((1 << somePlayer->ArrayIndex) & someFactory->DisplayProductionToHouses) != 0

	int              Group; //0-9, assigned by CTRL+Number, these kinds // also set by aimd TeamType->Group !
	AbstractClass*   ArchiveTarget; // Set when told to guard a unit or such, or to distinguish undeploy and selling. Also used by rally points as well as harvesters for remembering ore fields etc.
	HouseClass*      Owner;
	CloakState       CloakState;
	DECLARE_PROPERTY(StageClass, CloakProgress); // phase from [opaque] -> [fading] -> [transparent] , [General]CloakingStages= long
	DECLARE_PROPERTY(CDTimerClass, CloakDelayTimer); // delay before cloaking again
	float            WarpFactor; // don't ask! set to 0 in CTOR, never modified, only used as ((this->Fetch_ID) + this->WarpFactor) % 400 for something in cloak ripple
	bool             unknown_bool_250;
	CoordStruct      LastSightCoords;
	int              LastSightRange;
	int              LastSightHeight;
	bool             GapSuperCharged; // GapGenerator, when SuperGapRadiusInCells != GapRadiusInCells, you can deploy the gap to boost radius
	bool             GeneratingGap; // is currently generating gap
	int              GapRadius;
	bool             BeingWarpedOut; // is being warped by CLEG
	bool             WarpingOut; // phasing in after chrono-jump
	bool             unknown_bool_272;
	BYTE             unused_273;
	TemporalClass*   TemporalImUsing; // CLEG attacking Power Plant : CLEG's this
	TemporalClass*   TemporalTargetingMe; 	// CLEG attacking Power Plant : PowerPlant's this
	bool             IsImmobilized; // by chrono aftereffects
	DWORD            unknown_280;
	int              ChronoLockRemaining; // countdown after chronosphere warps things around
	CoordStruct      ChronoDestCoords; // teleport loco and chsphere set this
	AirstrikeClass*  Airstrike; //Boris
	bool             Berzerk;
	int            BerzerkDurationLeft;
	DWORD            SprayOffsetIndex; // hardcoded array of xyz offsets for sprayattack, 0 - 7, see 6FE0AD
	bool             Uncrushable; // DeployedCrushable fiddles this, otherwise all 0

	// unless source is Pushy=
	// abs_Infantry source links with abs_Unit target and vice versa - can't attack others until current target flips
	// no checking whether source is Infantry, but no update for other types either
	// old Brute hack
	FootClass*       DirectRockerLinkedUnit;
	FootClass*       LocomotorTarget; // mag->LocoTarget = victim
	FootClass*       LocomotorSource; // victim->LocoSource = mag
	AbstractClass*   Target; //if attacking
	AbstractClass*   LastTarget;
	CaptureManagerClass* CaptureManager; //for Yuris
	TechnoClass*     MindControlledBy;
	bool             MindControlledByAUnit;
	AnimClass*       MindControlRingAnim;
	HouseClass*      MindControlledByHouse; //used for a TAction
	SpawnManagerClass* SpawnManager;
	TechnoClass*     SpawnOwner; // on DMISL , points to DRED and such
	SlaveManagerClass*   SlaveManager;
	TechnoClass*     SlaveOwner; // on SLAV, points to YAREFN
	HouseClass*      OriginallyOwnedByHouse; //used for mind control

	// units point to the Building bunkering them, building points to Foot contained within
	TechnoClass*     BunkerLinkedItem;

	float            PitchAngle; // not exactly, and it doesn't affect the drawing, only internal state of a dropship
	DECLARE_PROPERTY(CDTimerClass, RearmTimer); // Originally named Arm in RA1, but this is more descriptive name.
	int              ChargeTurretDelay;         // Set to same duration (frames) as RearmTimer when weapon is fired. Only used by IsChargeTurret to calculate timespan during which to display turret animation.
	int              Ammo;
	int              Value; // set to actual cost when this gets queued in factory, updated only in building's 42C

	ParticleSystemClass* FireParticleSystem;
	ParticleSystemClass* SparkParticleSystem;
	ParticleSystemClass* NaturalParticleSystem;
	ParticleSystemClass* DamageParticleSystem;
	ParticleSystemClass* RailgunParticleSystem;
	ParticleSystemClass* unk1ParticleSystem;
	ParticleSystemClass* unk2ParticleSystem;
	ParticleSystemClass* FiringParticleSystem;

	WaveClass* Wave; //Beams


	// rocking effect
	float            AngleRotatedSideways; // in this frame, in radians - if abs() exceeds pi/2, it dies
	float            AngleRotatedForwards; // same

	// set these and leave the previous two alone!
	// if these are set, the unit will roll up to pi/4, by this step each frame, and balance back
	float            RockingSidewaysPerFrame; // left to right - positive pushes left side up
	float            RockingForwardsPerFrame; // back to front - positive pushes ass up

	int              HijackerInfantryType; // mutant hijacker

	DECLARE_PROPERTY(StorageClass, Tiberium);
	DWORD            unknown_34C;

	DECLARE_PROPERTY(TransitionTimer, UnloadTimer); // times the deploy, unload, etc. cycles

	DECLARE_PROPERTY(FacingClass, BarrelFacing);
	DECLARE_PROPERTY(FacingClass, PrimaryFacing);
	DECLARE_PROPERTY(FacingClass, SecondaryFacing);
	int              CurrentBurstIndex;
	DECLARE_PROPERTY(CDTimerClass, TargetLaserTimer);
	short            unknown_short_3C8;
	WORD             unknown_3CA;
	bool             CountedAsOwned; // is this techno contained in OwningPlayer->Owned... counts?
	bool             IsSinking;
	bool             WasSinkingAlready; // if(IsSinking && !WasSinkingAlready) { play SinkingSound; WasSinkingAlready = 1; }
	bool             unknown_bool_3CF;
	bool             IsUseless; // Units that are considered to have fulfilled their purpose and useless. Harvesters that cannot do anything without player input are considered this. AI will sell these units on Service Depots.
	bool             HasBeenAttacked; // ReceiveDamage when not HouseClass_IsAlly
	bool             Cloakable;
	bool             IsPrimaryFactory; // doubleclicking a warfac/barracks sets it as primary
	bool             IsALoaner;
	bool             IsInPlayfield;
	DECLARE_PROPERTY(RecoilData, TurretRecoil);
	DECLARE_PROPERTY(RecoilData, BarrelRecoil);
	bool             IsTether;
	bool             IsAlternativeTether;
	bool             IsOwnedByCurrentPlayer; // Returns true if owned by the player on this computer
	bool             DiscoveredByCurrentPlayer;
	bool             DiscoveredByComputer;
	bool             unknown_bool_41D;
	bool             unknown_bool_41E;
	bool             unknown_bool_41F;
	char             SightIncrease; // used for LeptonsPerSightIncrease
	bool             RecruitableA; // these two are like Lenny and Carl, weird purpose and never seen separate
	bool             RecruitableB; // they're usually set on preplaced objects in maps
	bool             IsRadarTracked;
	bool             IsOnCarryall;
	bool             IsCrashing;
	bool             WasCrashingAlready;
	bool             IsBeingManipulated;
	TechnoClass*     BeingManipulatedBy; // set when something is being molested by a locomotor such as magnetron
	// the pointee will be marked as the killer of whatever the victim falls onto
	HouseClass*      ChronoWarpedByHouse;
	bool             unknown_bool_430;
	bool             IsMouseHovering;
	bool             ShouldBeReselectOnUnlimbo;
	TeamClass*       OldTeam;
	bool             CountedAsOwnedSpecial; // for absorbers, infantry uses this to manually control OwnedInfantry count
	bool             Absorbed; // in UnitAbsorb/InfantryAbsorb or smth, lousy memory
	bool             unknown_bool_43A;
	DWORD            unknown_43C;
	DECLARE_PROPERTY(DynamicVectorClass<int>, CurrentTargetThreatValues);
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, CurrentTargets);

	// if DistributedFire=yes, this is used to determine which possible targets should be ignored in the latest threat scan
	DECLARE_PROPERTY(DynamicVectorClass<AbstractClass*>, AttackedTargets);

	DECLARE_PROPERTY(AudioController, TurretRotateSoundController);

	BOOL            IsTurretRotateSoundPlaying;
	BOOL            TurretIsRotating;

	DECLARE_PROPERTY(AudioController, GattlingSoundController);

	bool             IsGattlingSoundPlaying;
	DWORD            unknown_4BC; // Set to 0 and loaded but never read/used

	DECLARE_PROPERTY(AudioController, UnusedGattlingSoundController); // Called to stop but never actually used to play anything

	bool             IsUnusedGattlingSoundPlaying; // Set to 0 and loaded but never read/used
	DWORD            unknown_4D8; // Set to 0 and loaded but never read/used

	DECLARE_PROPERTY(AudioController, QueuedVoiceSoundController); // Used by select/move/attack voices.

	DWORD            QueuedVoiceIndex;
	DWORD            unknown_4F4;
	bool             unknown_bool_4F8;
	DWORD            unknown_4FC;	//gets initialized with the current Frame, but this is NOT a TimerStruct!
	TechnoClass*     QueueUpToEnter;
	DWORD            EMPLockRemaining;
	DWORD            ThreatPosed; // calculated to include cargo etc
	DWORD            ShouldLoseTargetNow;
	RadBeam*         FiringRadBeam;
	PlanningTokenClass* PlanningToken;
	ObjectTypeClass* Disguise;
	HouseClass*      DisguisedAsHouse;
};

static_assert(sizeof(TechnoClass) == 0x520);
