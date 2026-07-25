//Locomotor = {4A582742-9839-11d1-B709-00A024DDAFD1}

#pragma once

#include <LocomotionClass.h>

class NOVTABLE HoverLocomotionClass : public LocomotionClass
{
public:
	static constexpr uintptr_t ILocoVTable = 0x7EACFC;

	// TODO stub virtuals implementations

	//Destructor
	virtual ~HoverLocomotionClass() RX;

	void sub_514F70(bool arg)
		{ JMP_THIS(0x514F70); }

	void sub_5164D0(bool arg)
		{ JMP_THIS(0x5164D0); }

	//Constructor
	HoverLocomotionClass()
		: LocomotionClass(noinit_t())
	{ JMP_THIS(0x513C20); }

protected:
	explicit __forceinline HoverLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct Destination;
	CoordStruct HeadToCoord;
	FacingClass LocomotionFacing;
	double MaxSpeed;
	double CurrentSpeed;
	double BoostSpeed;
	double CurrentWobbles;
	bool unknown_bool_68;
	int unknown_int_6C;
	bool unknown_bool_70;
};
