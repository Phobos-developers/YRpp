#pragma once

#include <GeneralDefinitions.h>
#include <YRPPCore.h>

#include <Helpers/CompileTime.h>

struct Theater //US English spelling to keep it consistent with the game
{
public:
	static constexpr reference<Theater, 0x7E1B78u, 6u> const Array {};

	static void __fastcall Init(TheaterType theater)
	{
		JMP_STD(0x5349C0);
	}

	static Theater* Get(TheaterType theater)
	{
		return &Array[static_cast<int>(theater)];
	}

	static Theater& GetTheater(TheaterType theater)
	{
		return Array[static_cast<int>(theater)];
	}

	[[deprecated]]
	static int __fastcall FindIndex(const char* pName)
	{ JMP_STD(0x48DBE0); }

	static inline TheaterType& LastTheater = *reinterpret_cast<TheaterType*>(0x822CF8);

	char	ID[0x10];               //e.g. "TEMPERATE"
	char	UIName[0x20];           //e.g. "Name:Temperate"
	char	ControlFileName[0xA];   //e.g. "TEMPERAT" -> INI and MIX
	char	ArtFileName[0xA];       //e.g. "ISOTEMP" -> MIX
	char	PaletteFileName[0xA];   //e.g. "ISOTEM" -> PAL
	char	Extension[0x4];         //e.g. "TEM" -> Iso tile file extension
	char	MMExtension[0x4];       //e.g. "MMT" -> Marble Madness tile file extension
	char	Letter[0x2];            //e.g. "T" -> Theater specific IDs (GTCNST, NTWEAP, YTBARRACKS)

	//unused, was probably lighting stuff once
	float	RadarTerrainBrightness; // 0.0 to 1.0
	float	unknown_float_5C;
	float	unknown_float_60;
	float	unknown_float_64;
	int		unknown_int_68;
	int		unknown_int_6C;
};
