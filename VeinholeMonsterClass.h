#pragma once

#include <FootClass.h>
#include <PriorityQueueClass.h>
#include <RulesClass.h>
#include <CRT.h>

class VeinholeLogic
{
public:

	//74DFAF
	void Construct(int nCount = RulesClass::Instance->MaxVeinholeGrowth)
	{
		Nodes = (PriorityQueueClassNode*)YRMemory::Allocate(sizeof(PriorityQueueClassNode) * nCount);
		CellIndexesWithVeins = (bool*)YRMemory::Allocate(sizeof(bool) * nCount);
		CRT::_memset(CellIndexesWithVeins, 0, sizeof(bool) * nCount); //0x7D75E0 reserve ?
		Queue = GameCreate<PriorityQueueClass<PriorityQueueClassNode>>(nCount);
	}

	//74E8A0 Delete SpreadData
	void Destruct()
	{
		if (Queue)
		{
			GameDelete(Queue);
			Queue = nullptr;
		}

		if (Nodes)
		{
			YRMemory::Deallocate(Nodes);
			Nodes = nullptr;
		}

		if (CellIndexesWithVeins)
		{
			YRMemory::Deallocate(CellIndexesWithVeins);
			CellIndexesWithVeins = nullptr;
		}

		NextFreeNodeIndex = 0;
	}

	int NextFreeNodeIndex;
	PriorityQueueClass<PriorityQueueClassNode>* Queue;
	PriorityQueueClassNode* Nodes;
	CDTimerClass VeinTimer;
	bool* CellIndexesWithVeins;
};

class NOVTABLE VeinholeMonsterClass : public ObjectClass
{
public:
	static const AbstractType AbsID = AbstractType::VeinholeMonster;

	static constexpr reference<bool*, 0xA83DC8u> const IsCurrentPosAffected {};
	static constexpr reference<SHPStruct*, 0xB1D2ECu> const VeinSHPData {};
	static constexpr constant_ptr<DynamicVectorClass<VeinholeMonsterClass*>, 0xB1D290u> const Array {};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) override JMP_THIS(0x74F2D0);

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0; //none
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_THIS(0x74EEE0);
	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	//Destructor
	virtual ~VeinholeMonsterClass() JMP_THIS(0x74C9F0);

	//AbstractClass
	virtual AbstractType WhatAmI() const override JMP_THIS(0x74F310);
	virtual int Size() const override JMP_THIS(0x74F320);
	virtual void Update() override JMP_THIS(0x74CE50);

	//ObjectClass
	virtual void DrawIt(Point2D* pLocation, RectangleStruct* pBounds) const override JMP_THIS(0x74D490); //114
	virtual DamageState ReceiveDamage(int* pDamage, int DistanceFromEpicenter, WarheadTypeClass* pWH,
  ObjectClass* Attacker, bool IgnoreDefenses, bool PreventPassengerEscape, HouseClass* pAttackingHouse) override JMP_THIS(0x74D5D0);

	static VeinholeMonsterClass* __fastcall GetVeinholeMonsterAt(CellStruct* pCell)
	{ JMP_STD(0x74CDB0); }

	static VeinholeMonsterClass* __fastcall GetVeinholeMonsterFrom(CellStruct* pCell)
	{ JMP_STD(0x74CD60); }

	void RemoveFrom(CellClass* pCell) const
	{ JMP_THIS(0x74EF10); }

	void ClearVector() const
	{ JMP_THIS(0x74EA30); }

	void ClearGrowthData()
	{ GrowthLogic.Destruct(); }

	void Recalculate() const
	{ JMP_THIS(0x74E930); }

	void RecalculateSpread() const
	{ JMP_THIS(0x74E6B0); }

	void Func_74E1C0_RecalculateCellVector() const
	{ JMP_THIS(0x74E1C0); }

	void Func_74DC00() const
	{ JMP_THIS(0x74DC00); }

	void UpdateGrowth() const
	{ JMP_THIS(0x74D7C0); }

	static void __fastcall ClearVeinGrowthData()
	{
		JMP_STD(0x74E100);

		/*
		//pop back ?
		for (int i = Array->Count - 1; i >= 0; --i)
		{
			auto pVeinholes = Array->GetItem(i);
			pVeinholes->ClearGrowthData();
		}

		if (IsCurrentPosAffected())
		{
			YRMemory::Deallocate(Make_Pointer<bool>(0xA83DC8u));
			IsCurrentPosAffected = nullptr;
		}*/
	}

	//called 687A80
	static void __fastcall InitVeinGrowthData(bool bAllocate = true)
	{ JMP_STD(0x74DE90); }

	static bool __fastcall IsCellEligibleForVeinHole(CellStruct& nWhere)
	{ JMP_STD(0x74D670); }

	static void __fastcall TheaterInit(TheaterType nType)
	{ JMP_STD(0x74D450); }

	static TerrainTypeClass* __fastcall GetTerrainType()
	{ JMP_STD(0x74EF00); }

	static HRESULT __fastcall SaveVector(void* stream, DynamicVectorClass<VeinholeMonsterClass*>* a2)
	{ JMP_STD(0x74ED60); }

	static HRESULT __fastcall LoadVector(LPSTREAM a1)
	{ JMP_STD(0x74EA70); }

	static void __fastcall DestroyAll()
	{ JMP_STD(0x74EA30); }

	static void __fastcall DrawAll()
	{ JMP_STD(0x74D430); }

	static void __fastcall DeleteAll()
	{ JMP_STD(0x74D760); }

	static void __fastcall DeleteVeinholeGrowthData()
	{ JMP_STD(0x74E880); }

	static void __fastcall LoadVeinholeArt(int idxTheatre)
	{ JMP_STD(0x74D450); }

	static void __cdecl UpdateAllVeinholes()
	{ JMP_STD(0x74CDF0); }

	static void __fastcall UpdateAll()
	{
		for (auto const& pVeins : *Array())
		{
			if (!pVeins->InLimbo)
				pVeins->Update();
		}
	}

	VeinholeMonsterClass(CellStruct* pWhere) noexcept
		: VeinholeMonsterClass(noinit_t())
	{
		JMP_THIS(0x74C5B0);
	}

protected:
	explicit __forceinline VeinholeMonsterClass(noinit_t) noexcept
		: ObjectClass(noinit_t()) { }
public:

	DECLARE_PROPERTY(VeinholeLogic, GrowthLogic);
	int CurrentState;
	int NextState;
	int MonsterFrameIdx;
	char IsAnimationUpToDate;
	CDTimerClass UpdateAnimationFrameTimer;
	int AnimationUpdatePeriod;
	int MonsterFrameIdxChange;
	CDTimerClass UpdateStateTimer;
	CellStruct Position;
	int MonsterFrameToDraw;
	char IsDead;
	char DontPuffGas;
	int VeinCount;
};

static_assert(sizeof(VeinholeMonsterClass) == 0x108); //264
