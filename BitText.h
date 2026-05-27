#pragma once

#include <YRPP.h>

class BitFont;
class Surface;

class BitText
{
public:
	DEFINE_REFERENCE(BitText*, Instance, 0x89C4B8)

private:
	BitText() { JMP_THIS(0x434AD0); }
public:
	virtual ~BitText() RX;

	// Seems like draw in a single line
	void Print(BitFont pFont, Surface* pSurface, const wchar_t* pWideString, int X, int Y, int W, int H)
	{
		JMP_THIS(0x434B90);
	}

	void DrawText(BitFont* pFont, Surface* pSurface, const wchar_t* pWideString, int X, int Y, int W, int H, char a8, int a9, int nColorAdjust)
	{
		JMP_THIS(0x434CD0);
	}
};
