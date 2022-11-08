#pragma once

#include <ASMMacros.h>
#include <YRPPCore.h>
#include <YRMath.h>
#include <YRMathVector.h>
#include <BasicStructures.h>

#include <Facing.h>

//used for cell coordinates/vectors
using CellStruct = Vector2D<short>;
using Point2D = Vector2D<int>;
using CoordStruct = Vector3D<int>;

struct BasePlanningCell {
	int Weight;
	CellStruct Position;
};

// this crap is used in several Base planning routines
struct BasePlanningCellContainer {
	BasePlanningCell * Items;
	int Count;
	int Capacity;
	bool Sorted;
	DWORD Unknown_10;

	bool AddCapacity(int AdditionalCapacity)
		{ JMP_THIS(0x510860); }

	// for qsort
	static int __cdecl Comparator(const void *, const void *)
		{ JMP_STD(0x5108F0); }
};

// combines number and a string
struct NamedValue {
	const char* Name;
	int Value;

	bool operator == (int value) const {
		return this->Value == value;
	}

	bool operator == (const char* name) const {
		return !_strcmpi(this->Name, name);
	}

	bool operator == (const NamedValue& other) const {
		return this->Value == other.Value && *this == other.Name;
	}
};
