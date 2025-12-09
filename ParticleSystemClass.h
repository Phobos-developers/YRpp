/*
	ParticleSystems
*/

#pragma once

#include <ObjectClass.h>
#include <ParticleSystemTypeClass.h>
#include <ParticleClass.h>

class NOVTABLE ParticleSystemClass : public ObjectClass
{
public:
	static const AbstractType AbsID = AbstractType::ParticleSystem;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<ParticleSystemClass*>, Array, 0xA80208u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleSystemClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	ParticleClass* SpawnParticle(const CoordStruct& coords1, const CoordStruct& coords2)
		{ JMP_THIS(0x62E380); }

	ParticleClass* SpawnParticle(ParticleTypeClass* pType, const CoordStruct& coords)
		{ JMP_THIS(0x62E430); }

	//Constructor
	ParticleSystemClass(
		ParticleSystemTypeClass* pParticleSystemType,
		const CoordStruct& coords,
		AbstractClass* pTarget,
		ObjectClass* pOwner,
		const CoordStruct& targetCoords,
		HouseClass* pOwnerHouse) noexcept : ParticleSystemClass(noinit_t())
			{ JMP_THIS(0x62DC50); }

protected:
	explicit __forceinline ParticleSystemClass(noinit_t) noexcept
		: ObjectClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ParticleSystemTypeClass* Type;
	CoordStruct  SpawnDistanceToOwner;
	DECLARE_PROPERTY(DynamicVectorClass<ParticleClass*>, Particles);
	CoordStruct TargetCoords;
	ObjectClass* Owner;
	AbstractClass* Target; // CellClass or TechnoClass
	int          SpawnFrames; //from ParSysTypeClass
	int          Lifetime; //from ParSysTypeClass
	int          SparkSpawnFrames; //from ParSysTypeClass
	int          SpotlightRadius; //defaults to 29
	bool         TimeToDie;
	bool         unknown_bool_F9;
	HouseClass*  OwnerHouse;
};
