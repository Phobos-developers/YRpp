/*
	Tiberiums are initialized by INI files.
*/

#pragma once

#include <AbstractTypeClass.h>
#include <HeapClass.h>

//forward declarations
class AnimTypeClass;
class OverlayTypeClass;

struct MapSurfaceData
{
	static int __fastcall SurfaceDataCount() JMP_STD(0x42B1F0);
	static int __fastcall ToSurfaceIndex(const CellStruct& mapCoord) JMP_STD(0x42B1C0);

	int ToSurfaceIndex()
	{
		return ToSurfaceIndex(MapCoord);
	}

	CellStruct MapCoord;
	float Score;

	bool operator<(const MapSurfaceData& another) const
	{
		return Score < another.Score;
	}
};

class TiberiumLogic
{
public:
	void Construct(int nCount = MapSurfaceData::SurfaceDataCount())
	{
		Datas = (MapSurfaceData*)YRMemory::Allocate(sizeof(MapSurfaceData) * nCount);
		States = (bool*)YRMemory::Allocate(sizeof(bool) * nCount);

		Heap = GameCreate<PointerHeapClass<MapSurfaceData>>(nCount);
	}

	void Destruct()
	{
		GameDelete(Heap);
		Heap = nullptr;

		if (Datas)
		{
			YRMemory::Deallocate(Datas);
			Datas = nullptr;
		}

		if (States)
		{
			YRMemory::Deallocate(States);
			States = nullptr;
		}
	}

	int Count;
	PointerHeapClass<MapSurfaceData>* Heap;
	bool* States;
	MapSurfaceData* Datas;
	CDTimerClass Timer;
};

class NOVTABLE TiberiumClass : public AbstractTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::Tiberium;

	//Array
	ABSTRACTTYPE_ARRAY(TiberiumClass, 0xB0F4E8u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	//Destructor
	virtual ~TiberiumClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//TiberiumClass

	void RegisterForGrowth(CellStruct* cell)
		{ JMP_THIS(0x7235A0); }

	//Static helpers

	static int FindIndex(int idxOverlayType) {
		SET_REG32(ecx, idxOverlayType);
		CALL(0x5FDD20);
	}

	static TiberiumClass* Find(int idxOverlayType) {
		int idx = FindIndex(idxOverlayType);
		return Array->GetItemOrDefault(idx);
	}

	//Constructor
	TiberiumClass(const char* pID)
		: TiberiumClass(noinit_t())
	{ JMP_THIS(0x7216C0); }

protected:
	explicit __forceinline TiberiumClass(noinit_t)
		: AbstractTypeClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	int Spread;
	double SpreadPercentage;
	int Growth;
	double GrowthPercentage;
	int Value;
	int Power;
	int Color;
	DECLARE_PROPERTY(TypeList<AnimTypeClass*>, Debris);
	OverlayTypeClass* Image;
	int NumFrames;
	int NumImages;
	int field_EC;
	DECLARE_PROPERTY(TiberiumLogic, SpreadLogic);
	DECLARE_PROPERTY(TiberiumLogic, GrowthLogic);
};
