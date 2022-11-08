//Locomotor = {2BEA74E1-7CCA-11d3-BE14-00104B62A16C}

#pragma once

#include <LocomotionClass.h>

class __declspec(align(4)) NOVTABLE ShipLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	// TODO stub virtuals implementations

	//Destructor
	virtual ~ShipLocomotionClass() RX;

	//Constructor
	ShipLocomotionClass()
		: ShipLocomotionClass(noinit_t())
	{ JMP_THIS(0x69EC50); }

protected:
	explicit __forceinline ShipLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DWORD Ramp1;
	DWORD Ramp2;
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
	DWORD field_68;
};

static_assert(sizeof(ShipLocomotionClass) == 0x70);

