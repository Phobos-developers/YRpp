#pragma once

#include <YRPP.h>

class NOVTABLE BitFont
{
public:
	static constexpr reference<BitFont*, 0x89C4D0> Instance {};

private:
	BitFont(const char* pFileName) { JMP_THIS(0x433880); }
public:
	virtual ~BitFont() RX;

	bool GetTextDimension(const wchar_t* pText, int* pWidth, int* pHeight, int nMaxWidth) { JMP_THIS(0x433CF0); }
	int Blit(wchar_t wch, int X, int Y, int nColor) { JMP_THIS(0x434120); }

	bool Lock(Surface* pSurface) { JMP_THIS(0x4348F0); }
	bool UnLock(Surface* pSurface) { JMP_THIS(0x434990); }
	unsigned char* GetCharacterBitmap(wchar_t wch) { JMP_THIS(0x4346C0); }

	void SetBounds(LTRBStruct* pBound)
	{
		if (pBound)
			this->Bounds = *pBound;
		else
			this->Bounds = { 0,0,0,0 };
	}

	void SetColor(WORD nColor)
	{
		this->Color = nColor;
	}

	void SetField20(int x)
	{
		this->field_20 = x;
	}

	void SetField41(char flag)
	{
		this->field_41 = flag;
	}

	/// Properties
	struct InternalData
	{
		int FontWidth;
		int Stride;
		int FontHeight;
		int Lines;
		int Count;
		int SymbolDataSize;
		short* SymbolTable;
		char* Bitmaps;
		int ValidSymbolCount;
	};

	static InternalData* __fastcall LoadInternalData(const char* pFileName)
		{ JMP_STD(0x433990); }

	InternalData* InternalPTR;
	void* Pointer_8;
	short* pGraphBuffer;
	int PitchDiv2;
	int Unknown_14;
	wchar_t* field_18;
	int field_1C;
	int field_20;
	WORD Color;
	short DefaultColor2;
	int Unknown_28;
	int State_2C;
	LTRBStruct Bounds;
	bool Bool_40;
	bool field_41;
	bool field_42;
	bool field_43;
};