/*
	Particles
*/

#pragma once

#include <ObjectClass.h>
#include <ParticleTypeClass.h>

//forward declarations
class ParticleSystemClass;

class NOVTABLE ParticleClass : public ObjectClass
{
public:
	static const AbstractType AbsID = AbstractType::Particle;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<ParticleClass*>, Array, 0xA83DC8u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ParticleClass
	virtual int GetShapeFrame() R0;

	//Constructor
	ParticleClass(
		ParticleTypeClass* pParticleType, CoordStruct* pCrd1,
		CoordStruct* pCrd2, ParticleSystemClass* pParticleSystem) noexcept
		: ParticleClass(noinit_t())
	{ JMP_THIS(0x62B5E0); }

protected:
	explicit __forceinline ParticleClass(noinit_t) noexcept
		: ObjectClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ParticleTypeClass*   Type;
	ColorStruct          Color;
	int                  ColorIndex;
	double               ColorAccum;
	CoordStruct          GasDrift;
	Vector3D<float>      GasVelocity;
	CoordStruct          unused_D8;
	float                Speed;
	CoordStruct          FireTarget;
	CoordStruct          FireOrigin;
	CoordStruct          FireMoveDelta;
	Vector3D<float>      MovementDirection;
	Vector3D<float>      PrecisePosition;
	ParticleSystemClass* ParticleSystem;
	WORD                 RemainingEC;
	WORD                 RemainingDC;
	BYTE                 StateAIAdvance;
	bool                 IsBelowGround;
	BYTE                 StartStateAI;
	BYTE                 Translucency;
	bool                 WasSaved; // Set to true after saving game but never read.
	bool                 IsToDie;
};

static_assert(sizeof(ParticleClass) == 0x138);
