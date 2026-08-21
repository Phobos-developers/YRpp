/*
	Weapons
*/

#pragma once

#include <AbstractTypeClass.h>

//forward declarations
class AnimTypeClass;
class BulletTypeClass;
class ParticleSystemTypeClass;
class WarheadTypeClass;

class NOVTABLE WeaponTypeClass : public AbstractTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::WeaponType;

	//Array
	ABSTRACTTYPE_ARRAY(WeaponTypeClass, 0x887568u);

	static WeaponTypeClass* __fastcall FindOrAllocate(const char* id)
	{ JMP_STD(0x772FA0); }

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~WeaponTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//AbstractTypeClass

	void CalculateSpeed()
		{ JMP_THIS(0x7729F0); }

	int GetSpeed(int distance)
		{ JMP_THIS(0x773070); }

	ThreatType AllowedThreats()
		{ JMP_THIS(0x772A90); }

	//Constructor
	WeaponTypeClass(const char* pID = nullptr)
		: WeaponTypeClass(noinit_t())
	{ JMP_THIS(0x771C70); }

protected:
	explicit __forceinline WeaponTypeClass(noinit_t)
		: AbstractTypeClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int AmbientDamage;
	int Burst;
	BulletTypeClass* Projectile;
	int Damage;
	int Speed;
	WarheadTypeClass* Warhead;
	int ROF;
	int Range; // int(256 * ini value)
	int MinimumRange; // int(256 * ini value)
	DECLARE_PROPERTY(TypeList<int>, Report);		//sound indices
	DECLARE_PROPERTY(TypeList<int>, DownReport);	//sound indices
	DECLARE_PROPERTY(TypeList<AnimTypeClass*>, Anim);
	AnimTypeClass* OccupantAnim;
	AnimTypeClass* AssaultAnim;
	AnimTypeClass* OpenToppedAnim;
	ParticleSystemTypeClass* AttachedParticleSystem;
	ColorStruct LaserInnerColor;
	ColorStruct LaserOuterColor;
	ColorStruct LaserOuterSpread;
	bool UseFireParticles;
	bool UseSparkParticles;
	bool OmniFire;
	bool DistributedWeaponFire;
	bool IsRailgun;
	bool Lobber;
	bool Bright;
	bool IsSonic;
	bool Spawner;
	bool LimboLaunch;
	bool DecloakToFire;
	bool CellRangefinding;
	bool FireOnce;
	bool NeverUse;
	bool RevealOnFire;
	bool TerrainFire;
	bool SabotageCursor;
	bool MigAttackCursor;
	bool DisguiseFireOnly;
	int DisguiseFakeBlinkTime;
	bool InfiniteMindControl;
	bool FireWhileMoving;
	bool DrainWeapon;
	bool FireInTransport;
	bool Suicide;
	bool TurboBoost;
	bool Supress;
	bool Camera;
	bool Charges;
	bool IsLaser;
	bool DiskLaser;
	bool IsLine;
	bool IsBigLaser;
	bool IsHouseColor;
	char LaserDuration;
	bool IonSensitive;
	bool AreaFire;
	bool IsElectricBolt;
	bool DrawBoltAsLaser;
	bool IsAlternateColor;
	bool IsRadBeam;
	bool IsRadEruption;
	int RadLevel;
	bool IsMagBeam;
};
