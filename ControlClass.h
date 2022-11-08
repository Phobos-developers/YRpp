#pragma once

#include <GadgetClass.h>

class NOVTABLE ControlClass : public GadgetClass
{
public:
	//Non virtual

	//Statics

	//Constructors
	ControlClass(unsigned int nID, int nX, int nY, int nWidth, int nHeight, GadgetFlag eFlag, bool bSticky) noexcept
		: ControlClass(noinit_t()) { JMP_THIS(0x48E520); }

	ControlClass(ControlClass& another) noexcept
		: ControlClass(noinit_t()) { JMP_THIS(0x48E570); }

protected:
	explicit __forceinline ControlClass(noinit_t)  noexcept
		: GadgetClass(noinit_t())
	{
	}

	//Properties
public:

	int ID;
	GadgetClass* SendTo; // Peer
};
