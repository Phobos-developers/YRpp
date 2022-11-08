/*
	StringTable related stuff
*/

#pragma once

#include <GeneralDefinitions.h>
#include <Helpers/CompileTime.h>

#define CSF_SIGNATURE 0x43534620 //" FSC"
#define CSF_LABEL_SIGNATURE 0x4C424C20 //" LBL"
#define CSF_VALUE_SIGNATURE 0x53545220 //" RTS"
#define CSF_EXVALUE_SIGNATURE 0x53545257 //"WRTS"

enum class CSFLanguages : unsigned int {
	US = 0,
	UK = 1,
	German = 2,
	French = 3,
	Spanish = 4,
	Italian = 5,
	Japanese = 6,
	Jabberwockie = 7,
	Korean = 8,
	Chinese = 9,
	Unknown = 10
};

struct CSFHeader
{
	DWORD Signature; //should be CSF_SIGNATURE
	int CSFVersion; //RA2 uses 3
	int NumLabels;
	int NumValues;
	DWORD unused_0xC;
	CSFLanguages Language; //CSF_LANG_*, forced to US if CSFVersion < 2
};

struct CSFLabel
{
	char Name[0x20]; //limits the label name length to 31
	int NumValues; //one label can have multiple values attached, that's never used though
	int FirstValueIndex; //in the global StringTable::Values() array
};

struct CSFString
{
	CSFString *PreviousEntry;
	wchar_t Text[102];

	CSFString() : PreviousEntry(nullptr) {
		*Text = 0;
	}
};

struct CSFLanguage
{
	CSFLanguages Index; // one of the language constants
	char const* Name; // the display name
	char const* Short; // two letter language code
	char const* Letter; // one letter language code
};

class StringTable
{
public:
	static constexpr reference<CSFString*, 0xB1CF88u> const LastLoadedString{};
	static constexpr reference<int, 0xB1CF58u> const MaxLabelLen{};
	static constexpr reference<int, 0xB1CF6Cu> const LabelCount{};
	static constexpr reference<int, 0xB1CF70u> const ValueCount{};
	static constexpr reference<CSFLanguages, 0x845728u> const Language{};
	static constexpr reference<bool, 0xB1CF80u> const IsLoaded{};
	static constexpr reference<char*, 0xB1CF68u> const FileName{};
	static constexpr reference<CSFLabel*, 0xB1CF74u> const Labels{};
	static constexpr reference<wchar_t**, 0xB1CF78u> const Values{};
	static constexpr reference<char**, 0xB1CF7Cu> const ExtraValues{};

	static const wchar_t* __fastcall LoadString(
		const char* pLabel,
		char* pOutExtraData = nullptr,
		const char* pSourceCodeFileName = __FILE__,
		int nSourceCodeFileLine = __LINE__)
			{ JMP_STD(0x734E60); }

	static const wchar_t* FetchString(
		const char* pLabel,
		const wchar_t* pDefault = L"",
		char* pSpeech = nullptr, 
		const char* pFile = __FILE__, 
		int nLine = __LINE__)
	{
		if (pLabel && strlen(pLabel) && _strcmpi(pLabel, "<none>") && _strcmpi(pLabel, "none"))
			return LoadString(pLabel, pSpeech, pFile, nLine);
		else
			return pDefault;
	}

	static const wchar_t* TryFetchString(
		const char* pLabel,
		const wchar_t* pDefault = L"",
		char* pSpeech = nullptr,
		const char* pFile = __FILE__,
		int nLine = __LINE__)
	{
		if (pLabel && strlen(pLabel) && _strcmpi(pLabel, "<none>") && _strcmpi(pLabel, "none"))
		{
			auto lpValue = LoadString(pLabel, pSpeech, pFile, nLine);
			if (wcsncmp(lpValue, L"MISSING:", 8))
				return lpValue;
		}

		return pDefault;
	}

	static bool __fastcall LoadFile(const char* pFileName)
		{ JMP_STD(0x7346A0); }
	static bool __fastcall ReadFile(const char* pFileName)
		{ JMP_STD(0x734990); }

	static CSFLanguage const* __fastcall GetLanguage(CSFLanguages language)
		{ JMP_STD(0x734640); }
	static const char* __fastcall GetLanguageName(CSFLanguages language)
		{ JMP_STD(0x734670); }

	static void Unload()
		{ JMP_STD(0x734D30); }
};
