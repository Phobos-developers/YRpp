#pragma once

#include <Helpers/CompileTime.h>

#include <TargetClass.h>
#include <Unsorted.h>

enum class EventType : unsigned char
{
	EMPTY = 0,
	POWERON = 1,
	POWEROFF = 2,
	ALLY = 3,
	MEGAMISSION = 4,
	MEGAMISSION_F = 5,
	IDLE = 6,
	SCATTER = 7,
	DESTRUCT = 8,
	DEPLOY = 9,
	DETONATE = 10,
	PLACE = 11,
	OPTIONS = 12,
	GAMESPEED = 13,
	PRODUCE = 14,
	SUSPEND = 15,
	ABANDON = 16,
	PRIMARY = 17,
	SPECIAL_PLACE = 18,
	EXIT = 19,
	ANIMATION = 20,
	REPAIR = 21,
	SELL = 22,
	SELLCELL = 23,
	SPECIAL = 24,
	FRAMESYNC = 25,
	MESSAGE = 26,
	RESPONSE_TIME = 27,
	FRAMEINFO = 28,
	SAVEGAME = 29,
	ARCHIVE = 30,
	ADDPLAYER = 31,
	TIMING = 32,
	PROCESS_TIME = 33,
	PAGEUSER = 34,
	REMOVEPLAYER = 35,
	LATENCYFUDGE = 36,
	MEGAFRAMEINFO = 37,
	PACKETTIMING = 38,
	ABOUTTOEXIT = 39,
	FALLBACKHOST = 40,
	ADDRESSCHANGE = 41,
	PLANCONNECT = 42,
	PLANCOMMIT = 43,
	PLANNODEDELETE = 44,
	ALLCHEER = 45,
	ABANDON_ALL = 46,
	LAST_EVENT = 47,
};

#pragma pack(push, 1)
union EventData
{
	EventData()
	{

	}

	struct
	{
		char Data[104];
	} SpaceGap; // Just a space gap to align the struct

	struct
	{
		int ID; // Anim ID
		int AnimOwner; // House ID
		CellStruct Location;
	} Animation;

	struct
	{
		unsigned int CRC;
		unsigned short CommandCount;
		unsigned char Delay;
	} FrameInfo;

	struct
	{
		TargetClass Whom;
	} Target;

	struct
	{
		TargetClass Whom;
		unsigned char Mission; // Mission but should be byte
		char _gap_;
		TargetClass Target;
		TargetClass Destination;
		TargetClass Follow;
		bool IsPlanningEvent;
	} MegaMission;

	struct
	{
		TargetClass Whom;
		unsigned char Mission;
		TargetClass Target;
		TargetClass Destination;
		int Speed;
		int MaxSpeed;
	} MegaMission_F; // Seems unused in YR?

	struct
	{
		int RTTI_ID;
		int Heap_ID;
		int IsNaval;
	} Production;

	struct
	{
		int Unknown_0;
		long long Data;
		int Unknown_C;
	} Unknown_LongLong;

	struct
	{
		int Unknown_0;
		int Unknown_4;
		int Data;
		int Unknown_C;
	} Unknown_Tuple;

	struct
	{
		AbstractType RTTIType;
		int HeapID;
		int IsNaval;
		CellStruct Location;
	} Place;

	struct
	{
		int ID;
		CellStruct Location;
	} SpecialPlace;

	struct
	{
		AbstractType RTTIType;
		int ID;
	} Specific;
};

class EventClass;

template<size_t Length>
struct EventList
{
public:
	int Count;
	int Head;
	int Tail;
	EventClass List[Length];
	int Timings[Length];
};

class EventClass
{
public:
	static constexpr reference<const char*, 0x82091C, 47> const EventNames{};

	static constexpr reference<EventList<0x80>, 0xA802C8> OutList{};
	static constexpr reference<EventList<0x4000>, 0x8B41F8> DoList{};
	// If the event is a MegaMission, then add it to this list
	static constexpr reference<EventList<0x100>, 0xA83ED0> MegaMissionList{};

	// this points to CRCs from 0x100 last frames
	static constexpr reference<DWORD, 0xB04474, 256> const LatestFramesCRC{};
	static constexpr reference<DWORD, 0xAC51FC> const CurrentFrameCRC{};

	static bool AddEvent(const EventClass& event)
	{
		if (OutList->Count >= 128)
			return false;

		OutList->List[OutList->Tail] = event;

		OutList->Timings[OutList->Tail] = static_cast<int>(Imports::TimeGetTime());

		++OutList->Count;
		OutList->Tail = (OutList->Tail + 1) & 127;
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
	explicit EventClass(int houseIndex, EventType eventType, int unknown_0, int unknown_4, int unknown_c)
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
	explicit EventClass(int houseIndex, void*/*IPAddressClass*/ ip, char unknown_0)
	{
		JMP_THIS(0x4C6C50);
	}

	explicit EventClass(const EventClass& another)
	{
		memcpy(this, &another, sizeof(*this));
	}

	EventClass& operator=(const EventClass& another)
	{
		memcpy(this, &another, sizeof(*this));
	}

	EventType Type;
	bool IsExecuted;
	char HouseIndex; // '-1' stands for not a valid house
	unsigned int Frame; // 'Frame' is the frame that the command should execute on.

	EventData Data;

	bool operator==(const EventClass& q) const
	{
		return memcmp(this, &q, sizeof(q)) == 0;
	};
};
#pragma pack(pop)

static_assert(sizeof(EventClass) == 111);
