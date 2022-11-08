//Locomotor = {4A582743-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include <LocomotionClass.h>

class __declspec(align(4)) NOVTABLE TunnelLocomotionClass : public LocomotionClass
{
public:

	enum State
	{
		Idle = 0,
		PreDigIn = 1,
		DiggingIn = 2,
		DugIn = 3,
		Digging = 4,
		PreDigOut = 5,
		DiggingOut = 6,
		DugOut = 7
	};

	// TODO stub virtuals implementations

	bool ProcessPreDigIn()
		{ JMP_THIS(0x7291F0); }

	bool ProcessDiggingIn()
		{ JMP_THIS(0x729370); }

	bool ProcessDugIn()
		{ JMP_THIS(0x7294E0); }

	bool ProcessDigging()
		{ JMP_THIS(0x729580); }

	bool ProcessPreDigOut()
		{ JMP_THIS(0x7298F0); }

	bool ProcessDiggingOut()
		{ JMP_THIS(0x729AA0); }

	bool ProcessDugOut()
		{ JMP_THIS(0x729480); }

	TunnelLocomotionClass()
		: TunnelLocomotionClass(noinit_t())
	{ JMP_THIS(0x728A00); }

protected:
	explicit __forceinline TunnelLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	TunnelLocomotionClass::State State;
	CoordStruct Coords;
	RateTimer DigTimer;
	bool bool38;
};

static_assert(sizeof(TunnelLocomotionClass) == 0x3C);

