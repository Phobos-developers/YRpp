/*
	SmudgeTypes are initialized by INI files.
*/

#pragma once

#include <ObjectTypeClass.h>

class NOVTABLE SmudgeTypeClass : public ObjectTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::SmudgeType;

	//Array
	ABSTRACTTYPE_ARRAY(SmudgeTypeClass, 0xA8EC18u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~SmudgeTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//SmudgeTypeClass
	virtual void DrawIt(const Point2D& Point, const RectangleStruct& Rect, int SmudgeData, int Height, const CellStruct& MapCoords) RX;

	static void __fastcall LoadFromIniList(int idxTheatre)
		{ JMP_STD(0x6B5490); }

	//Constructor
	SmudgeTypeClass(const char* pID) noexcept
		: SmudgeTypeClass(noinit_t())
	{ JMP_THIS(0x6B5260); }

protected:
	explicit __forceinline SmudgeTypeClass(noinit_t) noexcept
		: ObjectTypeClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	int Width;
	int Height;
	bool Crater;
	bool Burn;
};
