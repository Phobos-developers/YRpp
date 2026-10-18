#pragma once

#include <AbstractClass.h>

class TechnoClass;
class EventClass;

class PlanningBranchClass;
// static_assert(sizeof(PlanningBranchClass) == 0x78);

class PlanningMemberClass
{
public:
	TechnoClass* Owner;
	EventClass* Order;
	int field_8;
	char field_C;
};
static_assert(sizeof(PlanningMemberClass) == 0x10);

class PlanningNodeClass
{
public:
	DEFINE_REFERENCE(DynamicVectorClass<PlanningNodeClass*>, Unknown1, 0xAC4B30u)
	DEFINE_REFERENCE(DynamicVectorClass<PlanningNodeClass*>, Unknown2, 0xAC4C18u)
	DEFINE_REFERENCE(DynamicVectorClass<PlanningNodeClass*>, Unknown3, 0xAC4C98u)

	DEFINE_REFERENCE(bool, PlanningModeActive, 0xAC4CF4u)

	static void __cdecl DrawAllBackground()
		JMP_STD(0x63B0A0);

	static void __cdecl DrawAllForeground()
		JMP_STD(0x63B150);

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DynamicVectorClass<PlanningMemberClass*> PlanningMembers;
	int field_18;
	bool field_1C;
	DynamicVectorClass<PlanningBranchClass*> PlanningBranches;
	//...
};

class PlanningTokenClass
{
public:
	DEFINE_REFERENCE(DynamicVectorClass<PlanningTokenClass*>, Array, 0xAC4C78u)

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	TechnoClass* OwnerUnit;
	DynamicVectorClass<PlanningNodeClass*> PlanningNodes;
	bool field_1C;
	bool field_1D;

	DECLARE_PROPERTY_ARRAY(DWORD, unknown_20_88, 0x1B);

	int field_8C;
	int ClosedLoopNodeCount;
	int StepsToClosedLoop;
	bool field_98;
	bool field_99;
};
static_assert(sizeof(PlanningTokenClass) == 0x9C);
