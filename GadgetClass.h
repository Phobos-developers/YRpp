#pragma once

#include <LinkClass.h>

enum class KeyModifier : int
{
	None = 0,
	Shift = 1,
	Ctrl = 2,
	Alt = 4
};

enum class GadgetFlag : int
{
	LeftPress = 0x1,
	LeftHeld = 0x2,
	LeftRelease = 0x4,
	LeftUp = 0x8,
	RightPress = 0x10,
	RightHeld = 0x20,
	RightRelease = 0x40,
	RightUp = 0x80,
	Keyboard = 0x100
};

MAKE_ENUM_FLAGS(GadgetFlag)

class NOVTABLE GadgetClass : public LinkClass
{
public:

	//Destructor
	virtual ~GadgetClass() RX;

	//LinkClass
	virtual GadgetClass* GetNext() override { JMP_THIS(0x4E14A0); }
	virtual GadgetClass* GetPrev() override { JMP_THIS(0x4E14B0); }
	virtual GadgetClass* Remove() override { JMP_THIS(0x4E1480); }

	//GadgetClass
	virtual DWORD Input() { JMP_THIS(0x4E1640); }
	virtual void DrawAll(bool bForced) { JMP_THIS(0x4E1570); }
	virtual void DeleteList() { JMP_THIS(0x4E14C0); }
	virtual GadgetClass* ExtractGadget(unsigned int nID) { JMP_THIS(0x4E1920); }
	virtual void MarkListToRedraw() { JMP_THIS(0x488690); }
	virtual void Disable() { JMP_THIS(0x4E1460); }
	virtual void Enable() { JMP_THIS(0x4E1450); }
	virtual unsigned int const GetID() { JMP_THIS(0x4AEBA0); }
	virtual void MarkRedraw() { JMP_THIS(0x4E1960); }
	virtual void PeerToPeer(unsigned int Flags, DWORD* pKey, GadgetClass* pSendTo) { JMP_THIS(0x48E650); }
	virtual void SetFocus() { JMP_THIS(0x4E19A0); }
	virtual void KillFocus() { JMP_THIS(0x4E19D0); }
	virtual bool IsFocused() { JMP_THIS(0x4E19F0); }
	virtual bool IsListToRedraw() { JMP_THIS(0x4E1A00); }
	virtual bool IsToRedraw() { JMP_THIS(0x4886A0); }
	virtual void SetPosition(int X, int Y) { JMP_THIS(0x4E1A20); }
	virtual void SetDimension(int Width, int Height) { JMP_THIS(0x4E1A40); }
	virtual bool Draw(bool bForced) { JMP_THIS(0x4E1550); }
	virtual void OnMouseEnter() { JMP_THIS(0x4E1510); }
	virtual void OnMouseLeave() { JMP_THIS(0x4E1520); }
	virtual void StickyProcess(GadgetFlag Flags) { JMP_THIS(0x4E1970); }
	virtual bool Action(GadgetFlag Flags, DWORD* pKey, KeyModifier Modifier) { JMP_THIS(0x4E1530); }
	virtual bool Clicked(DWORD* pKey, GadgetFlag Flags, int X, int Y, KeyModifier Modifier) { JMP_THIS(0x4E13F0); } // Clicked On

	//Non virtual
	GadgetClass& operator=(GadgetClass& another) { JMP_THIS(0x4B5780); }
	GadgetClass* ExtractGadgetAt(int X, int Y) { JMP_THIS(0x4E15A0); }

	//Statics
	static int __fastcall GetColorScheme() { JMP_STD(0x4E12D0); }

	//Constructors
	GadgetClass(int nX,int nY,int nWidth,int nHeight,GadgetFlag eFlag, bool bSticky) noexcept
		: GadgetClass(noinit_t()) { JMP_THIS(0x4E12F0); }

	GadgetClass(GadgetClass& another) noexcept
		: GadgetClass(noinit_t()) { JMP_THIS(0x4E1340); }

protected:
	explicit __forceinline GadgetClass(noinit_t)  noexcept
		: LinkClass(noinit_t())
	{
	}

	//Properties
public:

	int X;
	int Y;
	int Width;
	int Height;
	bool NeedsRedraw;
	bool IsSticky;
	bool Disabled;
	GadgetFlag Flags;
};
