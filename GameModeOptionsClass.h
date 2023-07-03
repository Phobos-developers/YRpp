#pragma once

#include <wchar.h>
#include <Helpers/CompileTime.h>


struct AISlotsStruct
{
	int Difficulties[8];
	int Countries[8];
	int Colors[8];
	int Starts[8];
	int Allies[8];
};

class GameModeOptionsClass
{
public:
	// this is the same as SessionClass::Instance.Config
	DEFINE_REFERENCE(GameModeOptionsClass, Instance, 0xA8B250u)

	int MPModeIndex;
	int ScenarioIndex;
	bool Bases;
	int Money;
	bool BridgeDestruction;
	bool Crates;
	bool ShortGame;
	bool SWAllowed;
	bool BuildOffAlly;
	int GameSpeed;
	bool MultiEngineer;
	int UnitCount;
	int AIPlayers;
	int AIDifficulty;
	AISlotsStruct AISlots;
	bool AlliesAllowed;
	bool HarvesterTruce;
	bool CaptureTheFlag;
	bool FogOfWar;
	bool MCVRedeploy;
	wchar_t MapDescription[45];
};
