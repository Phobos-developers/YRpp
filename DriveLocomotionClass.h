//Locomotor = {4A582741-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include <Helpers/CompileTime.h>
#include <LocomotionClass.h>

class NOVTABLE DriveLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	static constexpr uintptr_t ILocoVTable = 0x7E7EB0;

	DEFINE_ARRAY_REFERENCE(const TurnTrackType, [72], TurnTrack, 0x7E7B28)
	DEFINE_ARRAY_REFERENCE(const RawTrackType, [16], RawTrack, 0x7E7A28)

	// TODO stub virtuals implementations

	//Destructor
	virtual ~DriveLocomotionClass() RX;

	//Constructor
	DriveLocomotionClass()
		: DriveLocomotionClass(noinit_t())
	{ JMP_THIS(0x4AF540); }

protected:
	explicit __forceinline DriveLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DWORD PreviousRamp;
	DWORD CurrentRamp;
	RateTimer SlopeTimer;
	CoordStruct Destination;
	CoordStruct HeadToCoord;
	int SpeedAccum;
	double movementspeed_50;
	DWORD TrackNumber;
	int TrackIndex;
	bool IsOnShortTrack;
	BYTE IsTurretLockedDown;
	bool IsRotating;
	bool IsDriving;
	bool IsRocking;
	bool IsLocked;
	ILocomotion* Piggybackee;
	int field_6C;
};

static_assert(sizeof(DriveLocomotionClass) == 0x70);
