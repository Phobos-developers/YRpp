#pragma once

#include <GenericList.h>
#include <ArrayClasses.h>
#include <Helpers/CompileTime.h>

struct MixHeaderData
{
	DWORD ID;
	DWORD Offset;
	DWORD Size;
};

class MixFileClass : public Node<MixFileClass>
{
	struct GenericMixFiles
	{
		MixFileClass* RA2MD;
		MixFileClass* RA2;
		MixFileClass* LANGUAGE;
		MixFileClass* LANGMD;
		MixFileClass* THEATER_TEMPERAT;
		MixFileClass* THEATER_TEMPERATMD;
		MixFileClass* THEATER_TEM;
		MixFileClass* GENERIC;
		MixFileClass* GENERMD;
		MixFileClass* THEATER_ISOTEMP;
		MixFileClass* THEATER_ISOTEM;
		MixFileClass* ISOGEN;
		MixFileClass* ISOGENMD;
		MixFileClass* MOVIES02D;
		MixFileClass* UNKNOWN_1;
		MixFileClass* MAIN;
		MixFileClass* CONQMD;
		MixFileClass* CONQUER;
		MixFileClass* CAMEOMD;
		MixFileClass* CAMEO;
		MixFileClass* CACHEMD;
		MixFileClass* CACHE;
		MixFileClass* LOCALMD;
		MixFileClass* LOCAL;
		MixFileClass* NTRLMD;
		MixFileClass* NEUTRAL;
		MixFileClass* MAPSMD02D;
		MixFileClass* MAPS02D;
		MixFileClass* UNKNOWN_2;
		MixFileClass* UNKNOWN_3;
		MixFileClass* SIDEC02DMD;
		MixFileClass* SIDEC02D;
	};

public:
	DEFINE_REFERENCE(List<MixFileClass*>, MIXes, 0xABEFD8u)

	DEFINE_REFERENCE(DynamicVectorClass<MixFileClass*>, Array, 0x884D90u)
	DEFINE_REFERENCE(DynamicVectorClass<MixFileClass*>, Array_Alt, 0x884DC0u)
	DEFINE_REFERENCE(DynamicVectorClass<MixFileClass*>, Maps, 0x884DA8u)
	DEFINE_REFERENCE(DynamicVectorClass<MixFileClass*>, Movies, 0x884DE0u)

	DEFINE_REFERENCE(MixFileClass*, MULTIMD, 0x884DD8u)
	DEFINE_REFERENCE(MixFileClass*, MULTI, 0x884DDCu)

	DEFINE_REFERENCE(GenericMixFiles, Generics, 0x884DF8u)

	static void Bootstrap()
		{ JMP_THIS(0x5301A0); }

	virtual ~MixFileClass() RX;

	MixFileClass(const char* pFileName)
		: Node<MixFileClass>()
	{
		PUSH_IMM(0x886980);
		PUSH_VAR32(pFileName);
		THISCALL(0x5B3C20);
	}

	static void* Retrieve(char* name, bool forceShapeCache)
		{ JMP_STD(0x5B40B0); }

	static bool __fastcall Offset(const char* filename, void*& data,
		MixFileClass*& mixfile, int& offset, int& length)
	{ JMP_STD(0x5B4430); }

	static void DestroyCache()
	{ CALL(0x5B4310); }

protected:
	/*PROPERTY(MixFileClass*, Next);
	MixFileClass* Prev;*/

public:

	const char* FileName;
	bool Blowfish;
	bool Encryption;
	int CountFiles;
	int FileSize;
	int FileStartOffset;
	MixHeaderData* Headers;
	int field_24;
};
