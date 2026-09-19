#pragma once

#include <GeneralStructures.h>
#include <Surface.h>

class BeaconClass
{
public:
	enum class Flag : byte
	{
		// Set by BeaconManagerClass::PlaceBeacon once the beacon has been given a house, which
		// it is for any house index below 8. VisibleToPlayer tests it first.
		Assigned = 0x1,

		// Set by BeaconManagerClass::SelectBeacon on the beacon the local player clicked to type
		// a message into, and cleared again when it is deselected. It is the beacon that
		// DeleteBeacon and EditBeaconMessage resolve a -1 house / -1 slot to.
		Selected = 0x2,
	};

	BeaconClass() JMP_THIS(0x430210)

	void Draw(Surface* pSurface, RectangleStruct bounds) JMP_THIS(0x430250)
	void SetCoordAndHouse(CoordStruct coord, int houseId) JMP_THIS(0x430590)
	void SetText(const wchar_t* pText) JMP_THIS(0x430620)
	void DrawRadar(Surface* pSurface, RectangleStruct bounds, bool toClear = false) JMP_THIS(0x430650)
	bool VisibleToPlayer() const JMP_THIS(0x4308B0)

	bool HasFlag(Flag flag) const
	{
		return (this->Bitfield & static_cast<byte>(flag)) != 0;
	}

	bool IsAssigned() const
	{
		return this->HasFlag(Flag::Assigned);
	}

	bool IsSelected() const
	{
		return this->HasFlag(Flag::Selected);
	}

	CoordStruct Coord;
	byte Bitfield;
	byte gapD[1];
	wchar_t Text[128];
	byte field_10E;
	byte field_10F;
	int HouseID;
};

static_assert(sizeof(BeaconClass) == 0x114, "BeaconClass size is incorrect");
