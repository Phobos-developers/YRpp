#pragma once

#include <AbstractClass.h>

class TechnoClass;

class PlanningNode
{
public:
	DWORD field_0;
	DWORD field_4;
	DWORD field_8;
	DWORD field_C;
	int field_10;
	DWORD field_14;
};

class PlanningTokenClass
{
public:
	void Clear()
	{
		JMP_THIS(0x636310);
	}

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	TechnoClass *OwnerUnit;
	DynamicVectorClass<PlanningNode *> PlanningNodes;

	DECLARE_PROPERTY_ARRAY(DWORD, unknown, 0x1C);

	int field_8C;
	int ClosedLoopNodeCount;
	int StepsToClosedLoop;

	DECLARE_PROPERTY(DWORD, field_98);
};
static_assert(sizeof(PlanningTokenClass) == 0x9C);