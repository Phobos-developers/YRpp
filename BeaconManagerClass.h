#pragma once

#include <GeneralStructures.h>
#include <BeaconClass.h>
#include <FileFormats/SHP.h>
#include <Surface.h>

class __declspec(align(4)) BeaconManagerClass
{
public:
	DEFINE_REFERENCE(BeaconManagerClass, Instance, 0x89C3B0)
	DEFINE_REFERENCE(SHPStruct*, BeaconArt, 0x89C474)
	DEFINE_REFERENCE(SHPStruct*, RadarBeaconArt, 0x89C478)

	BeaconManagerClass() JMP_THIS(0x430910)

	~BeaconManagerClass() JMP_THIS(0x430930) // just an inlined Reset

	void Reset() JMP_THIS(0x430980)
	void LoadArt() JMP_THIS(0x4309D0)
	void Draw(Surface* pSurface, RectangleStruct bounds) JMP_THIS(0x430AC0)
	void PlaceBeacon(int houseId, CoordStruct coord, int houseBeaconId = -1) JMP_THIS(0x430BA0)
	bool CanPlaceBeacon(int houseId) JMP_THIS(0x430F30)
	void DeleteBeacon(int houseId, int houseBeaconId) JMP_THIS(0x4311C0)
	void DeleteAllBeacons(int houseId) JMP_THIS(0x431410)
	bool SelectBeacon(int X, int Y, int Z) JMP_THIS(0x430F70)
	void EditBeaconMessage(const wchar_t* message, int houseId, int houseBeaconId, bool shouldBroadcast) JMP_THIS(0x431450)

	// TODO rest of the functions

	void DrawRadar(Surface* surface, RectangleStruct bounds) JMP_THIS(0x431700)

	// TODO rest of the functions


    BeaconClass* Beacons[8][3];
    int AllocatedCount;
    Point2D BeaconSize;
    int BeaconFrameCount;
    Point2D RadarBeaconSize;
    int RadarBeaconFrameCount;
    int RadarBeaconAnimPeriod;
};

static_assert(sizeof(BeaconManagerClass) == 0x80, "BeaconManagerClass is the wrong size.");
