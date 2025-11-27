#pragma once

#include <ScenarioClass.h>
#include <QueueClass.h>
#include <TargetClass.h>
#include <Unsorted.h>

#pragma pack(push, 1)
class EventClass
{
public:
	DEFINE_ARRAY_REFERENCE(const char*, [47], EventNames, 0x0082091C)

	enum { MAX_EVENTS = 128 };

	DEFINE_REFERENCE((QueueClass<EventClass, MAX_EVENTS>), OutList, 0x00A802C8)
	DEFINE_REFERENCE((QueueClass<EventClass, MAX_EVENTS * 128>), DoList, 0x008B41F8)

	DEFINE_REFERENCE((QueueClass<EventClass, MAX_EVENTS * 2>), MegaMissionList, 0x00A83ED0)
	// 8 houses, 8-time cache targets
	DEFINE_ARRAY_REFERENCE(DWORD, [8 * 8], MegaMissionTargetNum, 0x00AC50FC)
	DEFINE_ARRAY_REFERENCE(TargetClass, [8 * 8][MAX_EVENTS], MegaMissionTargets, 0x00AFA468)

	// this points to CRCs from 0x100 last frames
	DEFINE_ARRAY_REFERENCE(DWORD, [256], LatestFramesCRC, 0x00B04474)
	DEFINE_REFERENCE(DWORD, CurrentFrameCRC, 0x00AC51FC)

	[[deprecated("Use OutList.Add() instead.")]]
	static bool AddEvent(const EventClass& event)
	{
		return OutList.Add(event);
	}

	explicit EventClass(int houseIndex, EventType eventType)
	{
		JMP_THIS(0x4C66C0);
	}

	// Special
	explicit EventClass(int houseIndex, int id)
	{
		JMP_THIS(0x4C65A0);
	}

	// Target
	explicit EventClass(int houseIndex, EventType eventType, int id, int rtti)
	{
		JMP_THIS(0x4C65E0);
	}

	// Sellcell
	explicit EventClass(int houseIndex, EventType eventType, const CellStruct& cell)
	{
		JMP_THIS(0x4C6650);
	}

	// Archive & Planning_Connect
	explicit EventClass(int houseIndex, EventType eventType, TargetClass src, TargetClass dest)
	{
		JMP_THIS(0x4C6780);
	}

	// Anim
	explicit EventClass(int houseIndex, int anim_id, HouseClass* pHouse, const CellStruct& cell)
	{
		JMP_THIS(0x4C6800);
	}

	// MegaMission
	explicit EventClass(int houseIndex, TargetClass src, Mission mission, TargetClass target, TargetClass dest, TargetClass follow)
	{
		JMP_THIS(0x4C6860);
	}

	// MegaMission_F
	explicit EventClass(int houseIndex, TargetClass src, Mission mission, TargetClass target, TargetClass dest, SpeedType speed, int/*MPHType*/ maxSpeed)
	{
		JMP_THIS(0x4C68E0);
	}

	// Production
	explicit EventClass(int houseIndex, EventType eventType, int rtti_id, int heap_id, BOOL is_naval)
	{
		JMP_THIS(0x4C6970);
	}

	// Unknown_LongLong
	explicit EventClass(int houseIndex, EventType eventType, int unknown_0, const int& unknown_c)
	{
		JMP_THIS(0x4C69E0);
	}

	// Unknown_Tuple
	explicit EventClass(int houseIndex, EventType eventType, int unknown_0, int unknown_4, int& unknown_c)
	{
		JMP_THIS(0x4C6A60);
	}

	// Place
	explicit EventClass(int houseIndex, EventType eventType, AbstractType rttitype, int heapid, int is_naval, const CellStruct& cell)
	{
		JMP_THIS(0x4C6AE0);
	}

	// SpecialPlace
	explicit EventClass(int houseIndex, EventType eventType, int id, const CellStruct& cell)
	{
		JMP_THIS(0x4C6B60);
	}

	// Specific?, maybe int[2] otherwise
	explicit EventClass(int houseIndex, EventType eventType, AbstractType rttitype, int id)
	{
		JMP_THIS(0x4C6BE0);
	}

	// Address Change
	explicit EventClass(int houseIndex, void* /*IPAddressClass*/ ip, char unknown_0)
	{
		JMP_THIS(0x4C6C50);
	}

	explicit EventClass(const EventClass& another)
	{
		memcpy(this, &another, sizeof(*this));
	}

	EventClass& operator=(const EventClass& another)
	{
		if (this != &another)
			memcpy(this, &another, sizeof(*this));

		return *this;
	}

	bool operator==(const EventClass& q) const
	{
		return memcmp(this, &q, sizeof(q)) == 0;
	};

	// ========================
	EventType Type;
	bool IsExecuted;
	char HouseIndex; // '-1' stands for not a valid house
	unsigned int Frame; // 'Frame' is the frame that the command should execute on.

	union
	{
		char DataBuffer[104];

		struct EMPTY
		{ } Empty;

		struct POWERON
		{
			TargetClass Target;
		} Poweron;

		struct POWEROFF
		{
			TargetClass Target;
		} Poweroff;

		struct ALLY
		{
			int HouseID;
		} Ally;

		struct MEGAMISSION
		{
			TargetClass Whom;
			unsigned char Mission;
			char _gap_;
			TargetClass Target;
			TargetClass Destination;
			TargetClass Follow;
			bool IsPlanningEvent;
		} MegaMission;

		struct MEGAMISSION_F
		{
			TargetClass Whom;
			unsigned char Mission;
			TargetClass Target;
			TargetClass Destination;
			int Speed;
			int MaxSpeed;
		} MegaMissionF;

		struct IDLE
		{
			TargetClass Whom;
		} Idle;

		struct SCATTER
		{
			TargetClass Whom;
		} Scatter;

		struct DESTRUCT
		{ } Destruct;

		struct DEPLOY
		{
			TargetClass Whom;
		} Deploy;

		struct DETONATE
		{
			TargetClass Whom;
		} Detonate;

		struct PLACE
		{
			AbstractType RTTIType;
			int HeapID;
			int IsNaval;
			CellStruct Location;
		} Place;

		struct OPTIONS
		{ } Options;

		struct GAMESPEED
		{
			int GameSpeed;
		} GameSpeed;

		// This event starts production of the specified object type. The house can
		// determine from the type and ID value, what object to begin production on and
		// what factory to use.
		struct PRODUCE
		{
			AbstractType RTTIType;
			int HeapID;
			int IsNaval;
		} Produce;

		struct SUSPEND
		{
			AbstractType RTTIType;
			int HeapID;
			int IsNaval;
		} Suspend;

		// This event is generated when the player cancels production of the specified
		// object type. From the object type, the exact factory can be inferred.
		struct ABANDON
		{
			AbstractType RTTIType;
			int HeapID;
			int IsNaval;
		} Abandon;

		// Toggles the primary factory state of the specified building.
		struct PRIMARY
		{
			TargetClass Whom;

		} Primary;

		struct SPECIAL_PLACE
		{
			int ID;
			CellStruct Location;
		} SpecialPlace;

		struct EXIT
		{ } Exit;

		struct ANIMATION
		{
			int AnimID;
			int HouseID;
			Point2D Location;
		} Animation;

		// Starts or stops repair on the specified object. This event is triggered by the
		// player clicking the repair wrench on a building.
		struct REPAIR
		{
			TargetClass Whom;
		} Repair;

		// Tells a building/unit to sell. This event is triggered by the player clicking the
		// sell animating cursor over the building or unit.
		struct SELL
		{
			TargetClass Whom;
		} Sell;

		// Used to sell walls
		struct SELLCELL
		{
			CellStruct Location;
		} SellCell;

		// Update the special control flags. This is necessary so that in a multiplayer
		// game, all machines will agree on the rules. If these options change during
		// game play, then all players are informed that options have changed.
		struct SPECIAL
		{
			ScenarioFlags SpecialFlags;
		} Special;

		struct FRAMESYNC
		{ } FrameSync;

		struct MESSAGE
		{ } Message;

		struct RESPONSE_TIME
		{
			char unknown;
		} ResponseTime;

		struct FRAMEINFO
		{
			unsigned int CRC;
			unsigned short CommandCount;
			unsigned char Delay;
		} FrameInfo;

		struct SAVEGAME
		{ } SaveGame;

		// Update the archive target for this building.
		struct ARCHIVE
		{
			TargetClass Whom1;
			TargetClass Whom2;
		} Archive;

		struct ADDPLAYER
		{
			void* unknownPointer;
		} AddPlayer;

		struct TIMING
		{
			unsigned short RequestedFPS;
			unsigned short MaxAhead;
			unsigned char FrameSendRate;
		} Timing;

		struct PROCESS_TIME
		{
			unsigned short Time;
		} ProcessTime;

		struct PAGEUSER
		{ } PageUser;

		struct REMOVEPLAYER
		{
			int HouseID;
		} RemovePlayer;

		struct LATENCYFUDGE
		{
			int LatencyFudge;
		} LatencyFudge;

		struct MEGAFRAMEINFO
		{
			char Unknown[104];
		} MegafFameInfo;

		struct PACKETTIMING
		{
			char Unknown[64];
		} PacketTiming;

		struct ABOUTTOEXIT
		{ } AboutToExit;

		struct FALLBACKHOST
		{
			int FallbackHost;
		} FallbackHost;

		struct ADDRESSCHANGE
		{
			char PlayerID;
			DWORD Address;
		} AddressChange;

		struct PLANCONNECT
		{
			TargetClass Target1;
			TargetClass Target2;
		} PlanConnect;

		struct PLANCOMMIT
		{ } PlanCommit;

		struct PLANNODEDELETE
		{
			TargetClass Target;
		} PlanNodeDelete;

		struct ALLCHEER
		{
			char Unknown[4];
		} AllCheer;

		struct ABANDON_ALL
		{
			char Unknown[12];
		} AbandonAll;
	};
};
#pragma pack(pop)

static_assert(sizeof(EventClass) == 111);
static_assert(offsetof(EventClass, DataBuffer) == 7);
