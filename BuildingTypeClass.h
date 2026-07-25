#pragma once

#include <TechnoTypeClass.h>
class OverlayTypeClass;
class IsometricTileTypeClass;

struct BuildingAnimStruct
{
	char Anim[0x10];
	char Damaged[0x10];
	char Garrisoned[0x10];
	Point2D Position;
	int ZAdjust;
	int YSort;
	bool Powered;
	bool PoweredLight;
	bool PoweredEffect;
	bool PoweredSpecial;
};

struct BuildingAnimFrameStruct
{
	DWORD dwUnknown;
	int FrameCount;
	int FrameDuration;
};

class NOVTABLE BuildingTypeClass : public TechnoTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::BuildingType;
	static constexpr uintptr_t AbsVTable = 0x7E4570;

	//Array
	ABSTRACTTYPE_ARRAY(BuildingTypeClass, 0xA83C68u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	//Destructor
	virtual ~BuildingTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//AbstractTypeClass
	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//TechnoTypeClass
	//BuildingTypeClass
	virtual SHPStruct* LoadBuildup() R0;

	//non-virtual
	void ClearBuildUp()
		{ JMP_THIS(0x465AF0); }

	bool IsVehicle() const
		{ JMP_THIS(0x465D40); }

	short GetFoundationWidth() const
		{ JMP_THIS(0x45EC90); }
	short GetFoundationHeight(bool bIncludeBib) const
		{ JMP_THIS(0x45ECA0); }

	bool CanPlaceHere(CellStruct* cell, HouseClass* owner) const
		{ JMP_THIS(0x464AC0); }

	// helpers
	bool HasSuperWeapon(int index) const {
		return (this->SuperWeapon == index || this->SuperWeapon2 == index);
	}

	bool HasSuperWeapon() const {
		return (this->SuperWeapon != -1 || this->SuperWeapon2 != -1);
	}

	bool CanTogglePower() const {
		return this->TogglePower && (this->PowerDrain > 0 || this->Powered);
	}

	BuildingAnimStruct& GetBuildingAnim(BuildingAnimSlot slot) {
		return this->BuildingAnim[static_cast<int>(slot)];
	}

	const BuildingAnimStruct& GetBuildingAnim(BuildingAnimSlot slot) const {
		return this->BuildingAnim[static_cast<int>(slot)];
	}

	//Constructor
	BuildingTypeClass(const char* pID) noexcept
		: BuildingTypeClass(noinit_t())
	{ JMP_THIS(0x45DD90); }

protected:
	explicit __forceinline BuildingTypeClass(noinit_t) noexcept
		: TechnoTypeClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	CellStruct* FoundationData;
	SHPStruct* Buildup;
	bool BuildupLoaded;
	BuildCat BuildCat;
	CoordStruct HalfDamageSmokeLocation1;
	CoordStruct HalfDamageSmokeLocation2;
	DWORD align_E24;
	double GateCloseDelay;
	int LightVisibility;
	int LightIntensity;
	int LightRedTint;
	int LightGreenTint;
	int LightBlueTint;
	Point2D PrimaryFirePixelOffset;
	Point2D SecondaryFirePixelOffset;
	OverlayTypeClass* ToOverlay;
	IsometricTileTypeClass* ToTile;
	char BuildupFile [0x10];
	int BuildupSound;
	int PackupSound;
	int CreateUnitSound;
	int UnitEnterSound;
	int UnitExitSound;
	int WorkingSound;
	int NotWorkingSound;
	char PowersUpBuilding [0x18];
	UnitTypeClass* FreeUnit;
	InfantryTypeClass* SecretInfantry;
	UnitTypeClass* SecretUnit;
	BuildingTypeClass* SecretBuilding;
	int field_EB0;
	int Adjacent;
	AbstractType Factory;
	CoordStruct TargetCoordOffset;
	CoordStruct ExitCoord;
	CellStruct* FoundationOutside;
	int StartFacing;
	int DeployFacing;
	int PowerBonus;
	int PowerDrain;
	int ExtraPowerBonus;
	int ExtraPowerDrain;
	Foundation Foundation;
	int Height;
	int OccupyHeight;
	int MidPoint;
	int DoorStages;

	BuildingAnimFrameStruct BuildingAnimFrame[6];

	BuildingAnimStruct BuildingAnim[0x15];

	int Upgrades;
	SHPStruct* DeployingAnim;
	bool DeployingAnimLoaded;
	SHPStruct* UnderDoorAnim;
	bool UnderDoorAnimLoaded;
	SHPStruct* Rubble;
	bool RubbleLoaded;
	SHPStruct* RoofDeployingAnim;
	bool RoofDeployingAnimLoaded;
	SHPStruct* UnderRoofDoorAnim;
	bool UnderRoofDoorAnimLoaded;
	SHPStruct* DoorAnim;
	SHPStruct* SpecialZOverlay;
	int SpecialZOverlayZAdjust;
	SHPStruct* BibShape;
	bool BibShapeLoaded;
	int NormalZAdjust;
	int AntiAirValue;
	int AntiArmorValue;
	int AntiInfantryValue;
	Point2D ZShapePointMove;
	int unknown_1538;
	int unknown_153C;
	int unknown_1540;
	int unknown_1544;
	WORD ExtraLight;
	bool TogglePower;
	bool HasSpotlight;
	bool IsTemple;
	bool IsPlug;
	bool HoverPad;
	bool BaseNormal;
	bool EligibileForAllyBuilding;
	bool EligibleForDelayKill;
	bool NeedsEngineer;
	int CaptureEvaEvent;
	int ProduceCashStartup;
	int ProduceCashAmount;
	int ProduceCashDelay;
	int InfantryGainSelfHeal;
	int UnitsGainSelfHeal;
	int RefinerySmokeFrames;
	bool Bib;
	bool Wall;
	bool Capturable;
	bool Powered;
	bool PoweredSpecial;
	bool Overpowerable;
	bool Spyable;
	bool CanC4;
	bool WantsExtraSpace;
	bool Unsellable;
	bool ClickRepairable;
	bool CanBeOccupied;
	bool CanOccupyFire;
	int MaxNumberOccupants;
	bool ShowOccupantPips;

	Point2D MuzzleFlash[0xA];

	Point2D DamageFireOffset[8];

	Point2D QueueingCell;
	int NumberImpassableRows;

	Point2D RemoveOccupy[8];

	Point2D AddOccupy[8];

	bool Radar;
	bool SpySat;
	bool ChargeAnim;
	bool IsAnimDelayedFire;
	bool SiloDamage;
	bool UnitRepair;
	bool UnitReload;
	bool Bunker;
	bool Cloning;
	bool Grinding;
	bool UnitAbsorb;
	bool InfantryAbsorb;
	bool SecretLab;
	bool DoubleThick;
	bool Flat;
	bool DockUnload;
	bool Recoilless;
	bool HasStupidGuardMode;
	bool BridgeRepairHut;
	bool Gate;
	bool SAM;
	bool ConstructionYard;
	bool NukeSilo;
	bool Refinery;
	bool Weeder;
	bool WeaponsFactory;
	bool LaserFencePost;
	bool LaserFence;
	bool FirestormWall;
	bool Hospital;
	bool Armory;
	bool EMPulseCannon;
	bool TickTank;
	bool TurretAnimIsVoxel;
	bool BarrelAnimIsVoxel;
	bool CloakGenerator;
	bool SensorArray;
	bool ICBMLauncher;
	bool Artillary;
	bool Helipad;
	bool OrePurifier;
	bool FactoryPlant;
	float InfantryCostBonus;
	float UnitsCostBonus;
	float AircraftCostBonus;
	float BuildingsCostBonus;
	float DefensesCostBonus;
	bool GDIBarracks;
	bool NODBarracks;
	bool YuriBarracks;
	float ChargedAnimTime;
	int DelayedFireDelay;
	int SuperWeapon;
	int SuperWeapon2;
	int GateStages;
	int PowersUpToLevel;
	bool DamagedDoor;
	bool InvisibleInGame;
	bool TerrainPalette;
	bool PlaceAnywhere;
	bool ExtraDamageStage;
	bool AIBuildThis;
	bool IsBaseDefense;
	BYTE CloakRadiusInCells;
	bool ConcentricRadialIndicator;
	int PsychicDetectionRadius;
	int BarrelStartPitch;
	char VoxelBarrelFile [0x14];

	// NOTE (Antares): upstream declares VoxelBarrelFile as [0x1C], which swallows
	// this double. BuildingClass::GetBarrelMatrix (gamemd 0x458810) does
	// `fld qword ptr [ecx+1728h]` at 0045897B and feeds the result to
	// Matrix3D::Scale_X/Y/Z, so +0x1728 is a double and the name array ends at
	// +0x1714 + 0x14. The game reads it but never writes it -- neither the ctor
	// nor Read_INI touch it -- so vanilla leaves it zero. Splitting the array is
	// size-neutral: 0x14 + 8 == 0x1C.
	double VoxelBarrelScale;

	CoordStruct VoxelBarrelOffsetToPitchPivotPoint;
	CoordStruct VoxelBarrelOffsetToRotatePivotPoint;
	CoordStruct VoxelBarrelOffsetToBuildingPivotPoint;
	CoordStruct VoxelBarrelOffsetToBarrelEnd;
	bool DemandLoad;
	bool DemandLoadBuildup;
	bool FreeBuildup;
	bool IsThreatRatingNode;
	bool PrimaryFireDualOffset;
	bool ProtectWithWall;
	bool CanHideThings;
	bool CrateBeneath;
	bool LeaveRubble;
	bool CrateBeneathIsMoney;
	char TheaterSpecificID [0x13];
	int NumberOfDocks;
	VectorClass<CoordStruct> DockingOffsets;
private: DWORD align_1794;
};

// Antares: layout guards for the two additions above. The double at +0x1728 is
// read by BuildingClass::GetBarrelMatrix (gamemd 0x458810, `fld qword ptr [ecx+1728h]`).
static_assert(offsetof(BuildingTypeClass, VoxelBarrelScale) == 0x1728, "BuildingTypeClass::VoxelBarrelScale moved");
static_assert(offsetof(BuildingTypeClass, VoxelBarrelFile) == 0x1714, "BuildingTypeClass::VoxelBarrelFile moved");
