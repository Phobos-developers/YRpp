#pragma once

#include <GeneralDefinitions.h>
#include <YRPPCore.h>

class LinkClass
{
public:
	//Destructor
	virtual ~LinkClass() RX;

	//LinkClass
	virtual LinkClass* GetNext() { JMP_THIS(0x556620); }
	virtual LinkClass* GetPrev() { JMP_THIS(0x556630); }
	virtual LinkClass* Add(LinkClass& another) { JMP_THIS(0x5566A0); }
	virtual LinkClass* AddTail(LinkClass& another) { JMP_THIS(0x556700); }
	virtual LinkClass* AddHead(LinkClass& another) { JMP_THIS(0x5566D0); }
	virtual LinkClass* HeadOfList(LinkClass& another) { JMP_THIS(0x556640); }
	virtual LinkClass* TailOfList(LinkClass& another) { JMP_THIS(0x556670); }
	virtual void Zap() { JMP_THIS(0x5565F0); }
	virtual LinkClass* Remove() { JMP_THIS(0x556730); }

	//Non virtual
	LinkClass& operator=(LinkClass& another) { JMP_THIS(0x556600); }

	//Constructors
	LinkClass(LinkClass& another) { JMP_THIS(0x556550); }

protected:
	explicit __forceinline LinkClass(noinit_t)  noexcept
	{
	}

	//Properties
public:

	LinkClass* Next;
	LinkClass* Previous;
};
