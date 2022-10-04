#pragma once

#include <Helpers/CompileTime.h>

#ifndef GAMEMD_STRING
#define GAMEMD_STRING(name,addr)\
static constexpr constant_ptr<const char,addr> const name;

namespace GameStrings
{
	// unsorted names
	GAMEMD_STRING(YURI_S_REVENGE, 0x849F48u);

	// ini file names
	GAMEMD_STRING(UIMD_INI    , 0x827DC8u);
	GAMEMD_STRING(THEMEMD_INI , 0x825D94u);
	GAMEMD_STRING(EVAMD_INI   , 0x825DF0u);
	GAMEMD_STRING(SOUNDMD_INI , 0x825E50u);
	GAMEMD_STRING(BATTLEMD_INI, 0x826198u);
	GAMEMD_STRING(AIMD_INI    , 0x82621Cu);
	GAMEMD_STRING(ARTMD_INI   , 0x826254u);
	GAMEMD_STRING(RULESMD_INI , 0x826260u);
	GAMEMD_STRING(RA2MD_INI   , 0x826444u);
	GAMEMD_STRING(MAPSELMD_INI, 0x830370u);

	// ini section names
	GAMEMD_STRING(General     , 0x826278u);
	GAMEMD_STRING(Basic       , 0x82BF9Cu);
	GAMEMD_STRING(AudioVisual , 0x839EA8u);
	GAMEMD_STRING(CombatDamage, 0x839E8Cu);
	GAMEMD_STRING(Radiation   , 0x839E80u);

	// EVA entry names
	GAMEMD_STRING(EVA_StructureSold      , 0x819030u);
	GAMEMD_STRING(EVA_UnitSold           , 0x822630u);
	GAMEMD_STRING(EVA_OreMinerUnderAttack, 0x824784u);
	//...
}

#undef GAMEMD_STRING
#endif
