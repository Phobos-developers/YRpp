#pragma once

#include <YRPPCore.h>
#include <GenericList.h>
#include <ArrayClasses.h>
#include <CCFileClass.h>
#include <IndexClass.h>
#include <Helpers/CompileTime.h>

struct ColorStruct;
class TechnoTypeClass;

//Basic INI class
class NOVTABLE INIClass
{
public:
	struct INIComment
	{
		char* Value;
		INIComment* Next;
	};

	class INIEntry : public Node<INIEntry>
	{
		public:
			virtual ~INIEntry() {}

			char* Key;
			char* Value;
			INIComment* Comments;
			char* CommentString;
			int PreIndentCursor;
			int PostIndentCursor;
			int CommentCursor;
	};

	class INISection : public Node<INISection>
	{
		public:

			virtual ~INISection() {}

			char* Name;
			List<INIEntry*> Entries;
			IndexClass <int, INIEntry*> EntryIndex;
			INIComment* Comments;
	};

	INIClass()
		{ JMP_THIS(0x535AA0); }

protected:
	INIClass(bool) { }

public:
	virtual ~INIClass() JMP_THIS(0x5256F0);

	void Reset()
		{ JMP_THIS(0x526B00); }

	void Clear(const char *s1, char *s2)
		{ JMP_THIS(0x5257C0); }

	INISection* GetSection(const char* pSection)
		{ JMP_THIS(0x526810); }

	int GetKeyCount(const char* pSection) //Get the amount of keys in a section.
		{ JMP_THIS(0x526960); }
	const char* GetKeyName(const char* pSection, int nKeyIndex) //Get the name of a key number in a section.
		{ JMP_THIS(0x526CC0); }

	//Reads an ANSI string. Returns the string's length.
	int ReadString(const char* pSection, const char* pKey, const char* pDefault, char* pBuffer, size_t szBufferSize)
		{ JMP_THIS(0x528A10); }
	int GetString(const char* pSection, const char* pKey, char* pBuffer,size_t szBufferSize)
		{ return ReadString(pSection, pKey, pBuffer, pBuffer, szBufferSize); }

	//Writes an ANSI string.
	bool WriteString(const char* pSection, const char* pKey, const char* pString)
		{ JMP_THIS(0x528660); }

	//Reads an escaped Unicode string. Returns the string's length.
	int ReadUnicodeString(const char* pSection, const char* pKey, const wchar_t* pDefault, wchar_t* pBuffer, size_t szBufferSize)
		{ JMP_THIS(0x528F00); }
	//Writes an escaped Unicode string.
	bool WriteUnicodeString(const char* pSection, const char* pKey, const wchar_t* pString)
		{ JMP_THIS(0x528E00); }

	//Reads an boolean value.
	bool ReadBool(const char* pSection, const char* pKey, bool bDefault)
		{ JMP_THIS(0x5295F0); }
	void GetBool(const char* pSection, const char* pKey, bool& bValue)
		{ bValue = ReadBool(pSection, pKey, bValue); }
	//Writes an boolean value.
	bool WriteBool(const char* pSection, const char* pKey, bool bValue)
		{ JMP_THIS(0x529560); }

	//Reads an integer value.
	int ReadInteger(const char* pSection, const char* pKey, int nDefault)
		{ JMP_THIS(0x5276D0); }
	void GetInteger(const char* pSection, const char* pKey, int& nValue)
		{ nValue = ReadInteger(pSection, pKey, nValue); }
	//Writes an integer value.
	bool WriteInteger(const char* pSection, const char* pKey, int nValue, bool bHex)
		{ JMP_THIS(0x5275C0); }

	//Reads a decimal value.
	double ReadDouble(const char* pSection, const char* pKey, double dDefault)
	{
		double* pdDefault = &dDefault;
		PUSH_VAR64(pdDefault); PUSH_VAR32(pKey); PUSH_VAR32(pSection); THISCALL(0x5283D0);
		_asm {fstp dDefault};
		return dDefault;
	}
	void GetDouble(const char* pSection, const char* pKey, double& nValue)
		{ nValue = ReadDouble(pSection, pKey, nValue); }

	//Writes a decimal value.
	bool WriteDouble(const char* pSection, const char* pKey, double dValue)
	{
		double* pdValue=&dValue;
		PUSH_VAR64(pdValue); PUSH_VAR32(pKey); PUSH_VAR32(pSection); THISCALL(0x5285B0);
	}

	int ReadRate(const char* pSection, const char* pKey, int nDefault)
	{
		double buffer = nDefault / 900.0;
		GetDouble(pSection, pKey, buffer);
		return static_cast<int>(buffer * 900.0);
	}
	void GetRate(const char* pSection, const char* pKey, int& nValue)
		{ nValue = ReadRate(pSection, pKey, nValue); }
	bool WriteRate(const char* pSection, const char* pKey, int nValue)
	{
		double dValue = nValue / 900.0;
		return WriteDouble(pSection, pKey, dValue);
	}

	//Reads two integer values.
	int* Read2Integers(int* pBuffer, const char* pSection, const char* pKey, int* pDefault)
		{ JMP_THIS(0x529880); }
	Point2D* ReadPoint2D(Point2D& ret, const char* pSection, const char* pKey, Point2D& defValue)
		{ JMP_THIS(0x529880); }
	void GetPoint2D(const char* pSection, const char* pKey, Point2D& value)
		{ ReadPoint2D(value, pSection, pKey, value); }
	//Writes two integer values.
	bool Write2Integers(const char* pSection, const char* pKey, int* pValues)
		{ JMP_THIS(0x5297E0); }

	//Reads three integer values.
	int* Read3Integers(int* pBuffer, const char* pSection, const char* pKey, int* pDefault)
		{ JMP_THIS(0x529CA0); }
	CoordStruct* ReadPoint3D(CoordStruct& ret, const char* pSection, const char* pKey, CoordStruct& defValue)
		{ JMP_THIS(0x529CA0); }
	void GetPoint3D(const char* pSection, const char* pKey, CoordStruct& value)
		{ ReadPoint3D(value, pSection, pKey, value); }

	//Reads three byte values.
	byte* Read3Bytes(byte* pBuffer, const char* pSection, const char* pKey, byte* pDefault)
		{ JMP_THIS(0x474B50); }
	//Writes three byte values.
	bool Write3Bytes(const char* pSection, const char* pKey, byte* pValues)
		{ JMP_THIS(0x474C20); }

	//Tests whether the given section and key exists. If key is NULL, only the section will be looked for.
	bool Exists(const char* pSection, const char* pKey)
		{ JMP_THIS(0x679F40); }

	int ReadTime(const char* pSection, const char* pKey, int nDefault)
		{ JMP_THIS(0x52A760); }

	bool WriteTime(const char* pSection, const char* pKey, int nValue)
		{ JMP_THIS(0x52A940); }

	// C&C helpers

#define INI_READ(item, addr) \
	int Read ## item(const char* pSection, const char* pKey, int pDefault) \
		{ JMP_THIS(addr); }

	// Pip= to idx ( pip strings with index < pDefault are not even scanned! )
	INI_READ(Pip, 0x4748A0);

	// PipScale= to idx
	INI_READ(PipScale, 0x474940);

	// Category= to idx
	INI_READ(Category, 0x4749E0);

	// Color=%s to idx
	INI_READ(ColorString, 0x474A90);

	// Foundation= to idx
	INI_READ(Foundation, 0x474DA0);

	// MovementZone= to idx
	INI_READ(MovementZone, 0x474E40);

	// SpeedType= to idx
	INI_READ(SpeedType, 0x476FC0);

	// [SW]Action= to idx
	INI_READ(SWAction, 0x474EE0);

	// [SW]Type= to idx
	INI_READ(SWType, 0x474F50);

	// EVA Event name to idx
	INI_READ(VoxName, 0x474FA0);

	// Factory= to idx
	INI_READ(Factory, 0x474FF0);

	INI_READ(BuildCat, 0x475060);

	// Parses a list of Countries and returns a bitfield, i.e. Owner= or RequiredHouses=
	INI_READ(HouseTypesList, 0x4750D0);

	// Parses a list of Houses and returns a bitfield, i.e. Allies= in map
	INI_READ(HousesList, 0x475260);

	INI_READ(ArmorType, 0x4753F0);

	INI_READ(LandType, 0x4754B0);

	// supports MP names (<Player @ X>) too, wtf
	// ALLOCATES if country name is not found
	// returns idx of country it reads
	INI_READ(HouseType, 0x475540);

	// ALLOCATES if name is not found
	INI_READ(Side, 0x4756F0);

	// returns index of movie with this filename
	INI_READ(Movie, 0x4757D0);

	// map theater
	INI_READ(Theater, 0x475870);

	INI_READ(Theme, 0x4758F0);

	INI_READ(Edge, 0x475980);

	INI_READ(Powerup, 0x4759F0);

	// [Anim]Layer= to idx
	INI_READ(Layer, 0x477050);

	INI_READ(VHPScan, 0x477590);

	// Color=%d,%d,%d to idx , used to parse [Colors]
	ColorStruct* ReadColor(ColorStruct* pBuffer, const char* pSection, const char* pKey, ColorStruct const& defValue)
		{ JMP_THIS(0x474C70); }

	ColorStruct ReadColor(const char* const pSection, const char* const pKey, ColorStruct const& defValue) {
		ColorStruct outBuffer;
		this->ReadColor(&outBuffer, pSection, pKey, defValue);
		return outBuffer;
	}

	void GetColor(const char* const pSection, const char* const pKey, ColorStruct& value)
	{
		ReadColor(&value, pSection, pKey, value);
	}

	bool WriteColor(const char* const pSection, const char* const pKey, ColorStruct const& color)
		{ JMP_THIS(0x474D50); }

	// OverlayPack, OverlayDataPack, IsoMapPack5
	// Those uses 1=xxxx, 2=xxxx, 3=xxxx .etc.
	size_t ReadUUBlock(const char* const pSection, void* pBuffer, size_t length)
		{ JMP_THIS(0x526FB0); }

	bool WriteUUBlock(const char* const pSection, void* pBuffer, size_t length)
		{ JMP_THIS(0x526E80); }

	// 18 bytes
	byte* ReadAbilities(byte* pBuffer, const char* pSection, const char* pKey, byte* pDefault)
		{ JMP_THIS(0x477640); }


	TechnoTypeClass* GetTechnoType(const char* pSection, const char* pKey)
		{ JMP_THIS(0x476EB0); }

	// safer and more convenient overload for string reading
	template <size_t Size>
	constexpr int ReadString(const char* pSection, const char* pKey, const char* pDefault, char(&pBuffer)[Size])
	{
		return this->ReadString(pSection, pKey, pDefault, pBuffer, Size);
	}

	template <size_t Size>
	constexpr int GetString(const char* pSection, const char* pKey, char(&pBuffer)[Size])
	{
		return ReadString(pSection, pKey, pBuffer, pBuffer);
	}

	// safer and more convenient overload for escaped unicode string reading
	template <size_t Size>
	constexpr int ReadUnicodeString(const char* pSection, const char* pKey, const wchar_t* pDefault, wchar_t(&pBuffer)[Size])
	{
		return this->ReadUnicodeString(pSection, pKey, pDefault, pBuffer, Size);
	}


	// fsldargh who the fuck decided to pass structures by value here
	static TypeList<int>* __fastcall GetPrerequisites(TypeList<int>* pBuffer, INIClass* pINI,
		const char* pSection, const char* pKey, TypeList<int> Defaults)

			{ JMP_STD(0x4770E0); }

	static bool IsBlank(const char *pValue) {
		return !_strcmpi(pValue, "<none>") || !_strcmpi(pValue, "none");
	}

	//Properties

public:
	using IndexType = IndexClass<int, INISection*>;

	char* CurrentSectionName;
	INISection* CurrentSection;
	DECLARE_PROPERTY(List<INISection>, Sections);
	DECLARE_PROPERTY(IndexType, SectionIndex); // <CRCValue of the Name, Pointer to the section>
	INIComment* LineComments;
};

//Extended INI class specified for C&C use
class NOVTABLE CCINIClass : public INIClass
{
public:
	//STATIC
	DEFINE_REFERENCE(DWORD, RulesHash, 0xB77E00u)
	DEFINE_REFERENCE(DWORD, ArtHash, 0xB77E04u)
	DEFINE_REFERENCE(DWORD, AIHash, 0xB77E08u)

	// westwood genius shines again

	// this is a pointer in the class
	DEFINE_REFERENCE(CCINIClass*, INI_Rules, 0x887048u)

	// these are static class variables, why the fuck did you differentiate them, WW?
	DEFINE_REFERENCE(CCINIClass, INI_AI, 0x887128u)
	DEFINE_REFERENCE(CCINIClass, INI_Art, 0x887180u)
	DEFINE_REFERENCE(CCINIClass, INI_UIMD, 0x887208u)
	DEFINE_REFERENCE(CCINIClass, INI_RA2MD, 0x8870C0u)

	//non-static
	CCINIClass() : INIClass(false)
	{
		THISCALL(0x535AA0);
		Digested = false;
		*reinterpret_cast<DWORD*>(this) = 0x7E1AF4;
	}

	virtual ~CCINIClass() RX;

	void LoadFromFile(const char* filename)
	{
		CCFileClass file { filename };
		if (file.Exists())
			this->ReadCCFile(&file);
	}

	static CCINIClass* LoadINIFile(const char* pFileName)
	{
		CCINIClass* pINI = GameCreate<CCINIClass>();
		pINI->LoadFromFile(pFileName);
		return pINI;
	}

	static void UnloadINIFile(CCINIClass*& pINI)
 	{
 		if (pINI)
 		{
 			GameDelete(pINI);
 			pINI = nullptr;
 		}
 	}

	//Parses an INI file from a CCFile
	CCINIClass* ReadCCFile(FileClass* pCCFile, bool bDigest = false, bool bLoadComments = false)
		{ JMP_THIS(0x4741F0); }

	void WriteCCFile(FileClass *pCCFile, bool bDigest = false)
		{ JMP_THIS(0x474430); }

	//Copies the string table entry pointed to by the INI value into pBuffer.
	int ReadStringtableEntry(const char* pSection, const char* pKey, wchar_t* pBuffer, size_t szBufferSize)
		{ JMP_THIS(0x0529160); }

	template <size_t Size>
	int ReadStringtableEntry(const char* pSection, const char* pKey, wchar_t(&pBuffer)[Size])
	{
		return this->ReadStringtableEntry(pSection, pKey, pBuffer, Size);
	}

	DWORD GetCRC()
		{ JMP_THIS(0x476D80); }

	//Properties

public:

	bool Digested : 1;
	byte Digest[20];
};
