#pragma once

#include <AbstractClass.h>

class NOVTABLE TubeClass : public AbstractClass
{
public:
	static const AbstractType AbsID = AbstractType::Tube;
	static constexpr uintptr_t AbsVTable = 0x7F59B0;

	DEFINE_REFERENCE(DynamicVectorClass<TubeClass*>, Array, 0x8B4138u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//Destructor
	virtual ~TubeClass() RX;

	//Constructor
	TubeClass(CellStruct* a2, int a3) noexcept
		: TubeClass(noinit_t())
	{ JMP_THIS(0x727FD0); }

protected:
	explicit __forceinline TubeClass(noinit_t) noexcept
		: AbstractClass(noinit_t())
	{ }

public:
	CellStruct EnterCell;
	CellStruct ExitCell;
	int ExitFace;
	int Faces[100];
	int FaceCount;
};
