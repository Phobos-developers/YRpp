#pragma once

#include <GadgetClass.h>

class NOVTABLE TextLabelClass : public GadgetClass
{
public:
	//Non virtual

	//Statics

	//Constructors
	TextLabelClass(wchar_t* pText, int X, int Y, int ColorSchemeIndex, TextPrintType style) noexcept
		: GadgetClass(noinit_t()) { JMP_THIS(0x72A440); }
protected:
	explicit __forceinline TextLabelClass(noinit_t)  noexcept
		: GadgetClass(noinit_t())
	{
	}

	//Properties
public:

	void* UserData1;
	void* UserData2;
	DWORD Style;
	wchar_t* Text;
	int ColorSchemeIndex;
	DWORD PixWidth;
	DWORD anim_dword3C;
	bool SkipDraw;
	bool Animate;
	DWORD AnimPos;
	DWORD AnimTiming;
};
