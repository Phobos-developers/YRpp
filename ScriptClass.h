/*
	Actual AI Team Scripts
*/

#pragma once

#include <AbstractClass.h>

//forward declarations
#include <ScriptTypeClass.h>

class NOVTABLE ScriptClass : public AbstractClass
{
public:
	static const AbstractType AbsID = AbstractType::Script;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ScriptClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	ScriptActionNode* GetCurrentAction(ScriptActionNode *buffer) const
		{ JMP_THIS(0x691500); }

	ScriptActionNode* GetNextAction(ScriptActionNode *buffer) const
		{ JMP_THIS(0x691540); }

	bool ClearMission()
		{ JMP_THIS(0x691590); }

	bool SetMission(int nLine)
		{ JMP_THIS(0x6915A0); }

	bool NextMission()
		{ ++this->CurrentMission; return this->HasNextMission(); }

	bool HasNextMission() const
		{ JMP_THIS(0x6915B0); }

	//Constructor
	ScriptClass(ScriptTypeClass* pType) noexcept
		: AbstractClass(noinit_t())
	{ JMP_THIS(0x6913C0); }

protected:
	explicit __forceinline ScriptClass(noinit_t) noexcept
		: AbstractClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ScriptTypeClass * Type;
	int field_28;
	int CurrentMission;
};
