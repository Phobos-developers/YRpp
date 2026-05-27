#pragma once

// Westwood owner draw and dialog hell

#include <Helpers/CompileTime.h>

#include <BasicStructures.h>
#include <Dictionary.h>
#include <Surface.h>
#include <Unsorted.h>
#include <Wstring.h>

#include <cstddef>
#include <cstring>
#include <cwchar>
#include <new>

class BitFont;

struct OwnerDrawTooltipRequest
{
	HWND ControlHwnd;
	LPARAM HitCode;
	WideWstring Text;
};

static_assert(sizeof(OwnerDrawTooltipRequest) == 0xC, "OwnerDrawTooltipRequest size mismatch");

struct OwnerDrawLayoutSize
{
	int Width;
	int Height;
};

static_assert(sizeof(OwnerDrawLayoutSize) == 0x8, "OwnerDrawLayoutSize size mismatch");

struct OwnerDrawHWNDVector
{
	int Count;
	int Capacity;
	HWND* Items;
};

static_assert(sizeof(OwnerDrawHWNDVector) == 0xC, "OwnerDrawHWNDVector size mismatch");

struct OwnerDrawWindowMessageKey
{
	UINT Message;
	HWND Hwnd;

	bool operator==(const OwnerDrawWindowMessageKey& rhs) const
	{
		return Message == rhs.Message && Hwnd == rhs.Hwnd;
	}
};

static_assert(sizeof(OwnerDrawWindowMessageKey) == 0x8, "OwnerDrawWindowMessageKey size mismatch");

struct OwnerDrawTooltipBlitState
{
	RectangleStruct Rect;
	Surface* BackingSurface;
	wchar_t Text[0x80];
	int Active;
	int BackgroundRestored;
	HWND OwnerHwnd;
};

static_assert(sizeof(OwnerDrawTooltipBlitState) == 0x120, "OwnerDrawTooltipBlitState size mismatch");

struct WWUIIntArray
{
	int Count;
	int Capacity;
	int* Items;
};

static_assert(sizeof(WWUIIntArray) == 0xC, "WWUIIntArray size mismatch");

enum class WWUIListBoxCellFormat : int
{
	Empty = 0,
	Text = 1,
	Image = 2,
	Progress = 3,
	ItemText = 4
};

struct WWUIListBoxCell
{
	WWUIListBoxCellFormat Format;
	WideWstring PrimaryText;
	WideWstring SecondaryText;
	COLORREF TextColor;
	Surface* Image;
	int Value;
};

static_assert(sizeof(WWUIListBoxCell) == 0x18, "WWUIListBoxCell size mismatch");
static_assert(offsetof(WWUIListBoxCell, PrimaryText) == 0x04, "WWUIListBoxCell::PrimaryText offset mismatch");
static_assert(offsetof(WWUIListBoxCell, SecondaryText) == 0x08, "WWUIListBoxCell::SecondaryText offset mismatch");
static_assert(offsetof(WWUIListBoxCell, TextColor) == 0x0C, "WWUIListBoxCell::TextColor offset mismatch");
static_assert(offsetof(WWUIListBoxCell, Image) == 0x10, "WWUIListBoxCell::Image offset mismatch");
static_assert(offsetof(WWUIListBoxCell, Value) == 0x14, "WWUIListBoxCell::Value offset mismatch");

struct WWUIListBoxColumn
{
	int X;
	int Width;
	int CellCount;
	int CellCapacity;
	WWUIListBoxCell* Cells;
};

static_assert(sizeof(WWUIListBoxColumn) == 0x14, "WWUIListBoxColumn size mismatch");
static_assert(offsetof(WWUIListBoxColumn, CellCount) == 0x08, "WWUIListBoxColumn::CellCount offset mismatch");
static_assert(offsetof(WWUIListBoxColumn, Cells) == 0x10, "WWUIListBoxColumn::Cells offset mismatch");

struct WWUIListBoxColumnArray
{
	int Count;
	int Capacity;
	WWUIListBoxColumn* Items;
};

static_assert(sizeof(WWUIListBoxColumnArray) == 0xC, "WWUIListBoxColumnArray size mismatch");

struct WWUIListBoxTextEntry
{
	WWUIListBoxTextEntry* Next;
	int ItemData;
	wchar_t* Text;
	int IsWide;
};

static_assert(sizeof(WWUIListBoxTextEntry) == 0x10, "WWUIListBoxTextEntry size mismatch");

struct WWUIComboBoxItem
{
	WWUIComboBoxItem* Next;
	int ItemData;
	wchar_t* Text;
	int IsWideText;
};

static_assert(sizeof(WWUIComboBoxItem) == 0x10, "WWUIComboBoxItem size mismatch");

enum class WWControlType : int
{
	Button = 0,
	Edit = 1,
	Static = 2,
	ComboBox = 3,
	ListBox = 4,
	SysListView = 5,	// SysListView32 reaches the fallback handler at 0x612A60 for label-edit coloring.
	Progress = 6,
	TrackBar = 7,
	ScrollBar = 8,
	Hotkey = 9,
	SysTab = 10,
	Default = 11
};

enum class WWUIStaticDrawMode : int
{
	Text = 0,
	TypewriterText = 1,
	PCX = 2,
	Shape = 3,
	AnimatedShape = 4
};

struct WWMovieHandle;

struct WWMovieHandleVTable
{
	void(__thiscall* Destructor)(WWMovieHandle* pThis, int deleting);
	bool(__thiscall* AdvanceFrame)(WWMovieHandle* pThis);
	bool(__thiscall* Waiting)(WWMovieHandle* pThis);
	void(__thiscall* Pause)(WWMovieHandle* pThis, int pause);
	void(__thiscall* Stop)(WWMovieHandle* pThis);
	bool(__thiscall* FramesLeft)(WWMovieHandle* pThis);
	void(__thiscall* SetPosition)(WWMovieHandle* pThis, int x, int y);
	void(__thiscall* SeekToFrame)(WWMovieHandle* pThis, int frame);
	void(__thiscall* InitSubtitles)(WWMovieHandle* pThis);
	int(__thiscall* Timing)(WWMovieHandle* pThis);
	void(__thiscall* Blit)(WWMovieHandle* pThis);
};

static_assert(sizeof(WWMovieHandleVTable) == 0x2C, "WWMovieHandleVTable size mismatch");

struct WWMovieHandle
{
	WWMovieHandleVTable* VTable;
	bool State;
	char Padding[3];
	int Width;
	int Height;
	void* Player;
};

static_assert(sizeof(WWMovieHandle) == 0x14, "WWMovieHandle size mismatch");
static_assert(offsetof(WWMovieHandle, Width) == 0x8, "WWMovieHandle::Width offset mismatch");
static_assert(offsetof(WWMovieHandle, Height) == 0xC, "WWMovieHandle::Height offset mismatch");

struct OwnerDrawDialogElement
{
	OwnerDrawDialogElement() { JMP_THIS(0x623340); }

	OwnerDrawDialogElement(const OwnerDrawDialogElement& rhs) : OwnerDrawDialogElement()
	{
		this->CopyFrom(rhs);
	}

	OwnerDrawDialogElement& operator=(const OwnerDrawDialogElement& rhs)
	{
		if (this != &rhs)
			this->CopyFrom(rhs);

		return *this;
	}

	~OwnerDrawDialogElement() { JMP_THIS(0x6233A0); }

	int EnumParam;

private:
	char TypeSpecific_004[0x0C];

public:
	Surface* CacheSurface;
	Surface* ControlImage;
	Surface* StateImageSurface;

private:
	int ComboBoxHeightInitialized;

public:
	int NeedsControlImage;

private:
	LPARAM Unknown_024;

public:
	wchar_t* TextBuffer;
	int HasText;

private:
	int NewEditAsciiOnly;
	char TypeSpecific_034[0x04];

public:
	int HasFocus;

private:
	WideWstring* NewEditText;
	int NewEditCaretIndex;
	int EditTextScrollStart;
	int NewEditTextLimit;
	int NewEditCaretBlinkState;
	wchar_t* NewEditRejectChars;
	int NewEditStyleFlags;
	WWMovieHandle* StaticMovieHandle;
	int StaticLoopMovie;
	void* StaticMovieAuxHandle;
	void* Font;

public:
	WWControlType ControlType;
	int DialogID;

private:
	WWUIStaticDrawMode StaticDrawMode;
	ConvertClass* StaticShapeDrawer;
	SHPStruct* StaticShape;
	int StaticShapeFlags;
	int StaticTextRevealCount;
	int StaticTextRevealDelay;
	int StaticTextRevealStep;
	int StaticColorAdjust;
	int StaticSoundIndex;
	int StaticFrameCount;
	int StaticCurrentFrame;
	int StaticLastFrameTick;
	int StaticFrameDelayMs;
	HWND StaticFrameNotifyHwnd;
	bool StaticAnimationRunning;
	char Unknown_0A9[0x03];
	int StaticTextFlags;

public:
	int LayoutBand;

private:
	bool StaticFillBackground;
	char Unknown_0B5[0x03];
	COLORREF StaticFillColor;

public:
	bool SkipDraw;
	bool HasOpenAnimation;
	bool HasFadeAnimation;

private:
	bool Unknown_0BF;

public:
	int TooltipVariant;

private:
	bool ButtonTimerActive;
	bool ButtonAlternateFrame;
	char Unknown_0C6[0x02];

public:
	int Alpha;

private:
	char TypeSpecific_0CC[0x04];
	int ComboBoxMaxVisibleDropItems;
	bool Unknown_0D4;

public:
	bool HasTopPanelAnimation;
	bool HasButtonAnimation;
	bool HasMainScreenAnimation;
	bool FlagD8;

private:
	bool CheckboxUseExtendedArt;
	bool CheckboxArtVariant;
	bool Unknown_0DB;

public:
	int ExtraWidth;
	Surface* DialogBackground;
	Surface* DialogBackgroundEx;

private:
	char TypeSpecific_0E8[0x20];

public:
	int Extra[62];

private:
	template<typename T>
	T& FieldAt(size_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + offset);
	}

	template<typename T>
	const T& FieldAt(size_t offset) const
	{
		return *reinterpret_cast<const T*>(reinterpret_cast<const char*>(this) + offset);
	}

	void CopyFrom(const OwnerDrawDialogElement& rhs)
	{
		auto* const pOwnedTextBuffer = this->TextBuffer;
		auto* const pOwnedTextEntries = this->FieldAt<void*>(0x34);
		auto* const pOwnedWideString = this->FieldAt<WideWstring*>(0x3C);

		std::memcpy(this, &rhs, sizeof(*this));

		this->TextBuffer = pOwnedTextBuffer;
		this->FieldAt<void*>(0x34) = pOwnedTextEntries;
		this->FieldAt<WideWstring*>(0x3C) = pOwnedWideString;

		this->SetTextBufferCopy(rhs.TextBuffer);
		this->SetTextEntriesCopy(rhs.FieldAt<void*>(0x34));
		this->SetWideStringCopy(rhs.FieldAt<WideWstring*>(0x3C));
	}

	void ClearTextBuffer()
	{
		if (this->TextBuffer)
		{
			YRMemory::Deallocate(this->TextBuffer);
			this->TextBuffer = nullptr;
		}
	}

	void SetTextBufferCopy(const wchar_t* pSource)
	{
		this->ClearTextBuffer();

		if (!pSource || !pSource[0])
			return;

		const auto bytes = (std::wcslen(pSource) + 1) * sizeof(wchar_t);
		this->TextBuffer = static_cast<wchar_t*>(YRMemory::Allocate(bytes));
		std::wcscpy(this->TextBuffer, pSource);
	}

	void ClearTextEntries()
	{
		auto& pTextEntries = this->FieldAt<void*>(0x34);

		while (pTextEntries)
		{
			auto* const pEntry = static_cast<WWUIComboBoxItem*>(pTextEntries);
			pTextEntries = pEntry->Next;
			YRMemory::Deallocate(pEntry);
		}
	}

	void SetTextEntriesCopy(void* pSource)
	{
		this->ClearTextEntries();
		auto& pTextEntries = this->FieldAt<void*>(0x34);

		for (auto* pEntry = static_cast<WWUIComboBoxItem*>(pSource); pEntry; pEntry = pEntry->Next)
		{
			const auto* const pText = pEntry->Text ? pEntry->Text : L"";
			const auto bytes = sizeof(WWUIComboBoxItem) + (std::wcslen(pText) + 1) * sizeof(wchar_t);
			auto* const pCopy = static_cast<WWUIComboBoxItem*>(YRMemory::Allocate(bytes));

			if (!pCopy)
				continue;

			pCopy->Next = static_cast<WWUIComboBoxItem*>(pTextEntries);
			pCopy->ItemData = pEntry->ItemData;
			pCopy->Text = reinterpret_cast<wchar_t*>(reinterpret_cast<char*>(pCopy) + sizeof(WWUIComboBoxItem));
			pCopy->IsWideText = pEntry->IsWideText;
			std::wcscpy(pCopy->Text, pText);

			pTextEntries = pCopy;
		}
	}

	void ClearWideString()
	{
		auto& pWideString = this->FieldAt<WideWstring*>(0x3C);

		if (pWideString)
		{
			pWideString->~WideWstring();
			YRMemory::Deallocate(pWideString);
			pWideString = nullptr;
		}
	}

	void SetWideStringCopy(const WideWstring* pSource)
	{
		this->ClearWideString();

		if (!pSource)
			return;

		auto* const pCopy = static_cast<WideWstring*>(YRMemory::Allocate(sizeof(WideWstring)));
		if (!pCopy)
			return;

		this->FieldAt<WideWstring*>(0x3C) = new (pCopy) WideWstring(*pSource);
	}

	friend struct OwnerDrawDialogElementLayoutVerifier;

	struct ScrollBarData
	{
		OwnerDrawDialogElement& Data;

		HWND& NotifyHwnd() { return this->Data.FieldAt<HWND>(0x08); }
		bool& Disabled() { return this->Data.FieldAt<bool>(0xCD); }
		int& IsMouseTracking() { return this->Data.FieldAt<int>(0xE8); }
		int& IsThumbDragging() { return this->Data.FieldAt<int>(0xEC); }
		int& RangeMax() { return this->Data.FieldAt<int>(0xF0); }
		int& Position() { return this->Data.FieldAt<int>(0xF4); }
		int& UpButtonPressed() { return this->Data.FieldAt<int>(0xF8); }
		int& DownButtonPressed() { return this->Data.FieldAt<int>(0xFC); }
		int& RestoreCaptureToNotifyHwnd() { return this->Data.FieldAt<int>(0x100); }
	};

	struct ListBoxData
	{
		OwnerDrawDialogElement& Data;

		HWND& ScrollBarHwnd() { return this->Data.FieldAt<HWND>(0x0C); }
		int& ScrollBarWidth() { return this->Data.FieldAt<int>(0x04); }
		WWUIListBoxTextEntry*& TextEntries() { return this->Data.FieldAt<WWUIListBoxTextEntry*>(0x34); }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		WWUIIntArray*& ItemData() { return this->Data.FieldAt<WWUIIntArray*>(0xE8); }
		WWUIIntArray*& SelectionStates() { return this->Data.FieldAt<WWUIIntArray*>(0xEC); }
		int& TopIndex() { return this->Data.FieldAt<int>(0xF0); }
		int& CurrentSelection() { return this->Data.FieldAt<int>(0xF4); }
		WWUIListBoxColumnArray*& Columns() { return this->Data.FieldAt<WWUIListBoxColumnArray*>(0xF8); }
		int& SavedFont() { return this->Data.Extra[56]; }
	};

	struct ComboBoxData
	{
		OwnerDrawDialogElement& Data;

		WWUIComboBoxItem*& TextEntries() { return this->Data.FieldAt<WWUIComboBoxItem*>(0x34); }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		int& HeightInitialized() { return this->Data.FieldAt<int>(0x1C); }
		bool& UseItemColorOverrides() { return this->Data.FieldAt<bool>(0xCC); }
		bool& UseAlternatePalette() { return this->Data.FieldAt<bool>(0xCD); }
		int& MaxVisibleDropItems() { return this->Data.FieldAt<int>(0xD0); }
		HWND& DropDownHwnd() { return this->Data.FieldAt<HWND>(0xF4); }
		int& CurrentSelection() { return this->Data.FieldAt<int>(0xF8); }
		int* ItemColorOverrides() { return &this->Data.Extra[2]; }
	};

	struct NewEditData
	{
		OwnerDrawDialogElement& Data;

		WideWstring*& Text() { return this->Data.FieldAt<WideWstring*>(0x3C); }
		int& CaretIndex() { return this->Data.FieldAt<int>(0x40); }
		int& ScrollStart() { return this->Data.FieldAt<int>(0x44); }
		int& TextLimit() { return this->Data.FieldAt<int>(0x48); }
		int& CaretBlinkState() { return this->Data.FieldAt<int>(0x4C); }
		wchar_t*& RejectChars() { return this->Data.FieldAt<wchar_t*>(0x50); }
		int& AsciiOnly() { return this->Data.FieldAt<int>(0x30); }
		int& StyleFlags() { return this->Data.FieldAt<int>(0x54); }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
	};

	struct EditData
	{
		OwnerDrawDialogElement& Data;

		int& TextScrollStart() { return this->Data.FieldAt<int>(0x44); }
		BitFont*& TextFont() { return this->Data.FieldAt<BitFont*>(0x64); }
		int& FocusRestorePendingFlag() { return this->Data.FieldAt<int>(0xF0); }
		int& FocusRestoreReadyFlag() { return this->Data.FieldAt<int>(0xF4); }
		int& RestoreTabStopFlag() { return this->Data.FieldAt<int>(0xF8); }
	};

	struct StaticData
	{
		OwnerDrawDialogElement& Data;

		Surface*& CachedBackground() { return this->Data.CacheSurface; }
		Surface*& ImageSurface() { return this->Data.ControlImage; }
		wchar_t*& Text() { return this->Data.TextBuffer; }
		WWMovieHandle*& MovieHandle() { return this->Data.FieldAt<WWMovieHandle*>(0x58); }
		int& LoopMovie() { return this->Data.FieldAt<int>(0x5C); }
		void*& MovieAuxHandle() { return this->Data.FieldAt<void*>(0x60); }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		WWUIStaticDrawMode& DrawMode() { return this->Data.FieldAt<WWUIStaticDrawMode>(0x70); }
		ConvertClass*& ShapeDrawer() { return this->Data.FieldAt<ConvertClass*>(0x74); }
		SHPStruct*& Shape() { return this->Data.FieldAt<SHPStruct*>(0x78); }
		bool& OwnsShape() { return this->Data.FieldAt<bool>(0x7C); }
		int& TextRevealCount() { return this->Data.FieldAt<int>(0x80); }
		int& TextRevealDelay() { return this->Data.FieldAt<int>(0x84); }
		int& TextRevealStep() { return this->Data.FieldAt<int>(0x88); }
		int& ColorAdjust() { return this->Data.FieldAt<int>(0x8C); }
		int& SoundIndex() { return this->Data.FieldAt<int>(0x90); }
		int& FrameCount() { return this->Data.FieldAt<int>(0x94); }
		int& CurrentFrame() { return this->Data.FieldAt<int>(0x98); }
		int& LastFrameTick() { return this->Data.FieldAt<int>(0x9C); }
		int& FrameDelayMs() { return this->Data.FieldAt<int>(0xA0); }
		HWND& FrameNotifyHwnd() { return this->Data.FieldAt<HWND>(0xA4); }
		bool& AnimationRunning() { return this->Data.FieldAt<bool>(0xA8); }
		int& TextFlags() { return this->Data.FieldAt<int>(0xAC); }
		bool& FillBackground() { return this->Data.FieldAt<bool>(0xB4); }
		COLORREF& FillColor() { return this->Data.FieldAt<COLORREF>(0xB8); }
		bool& SuppressPaint() { return this->Data.SkipDraw; }
		COLORREF& TextColor() { return this->Data.FieldAt<COLORREF>(0xEC); }
	};

	struct GroupBoxData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
	};

	struct ButtonData
	{
		OwnerDrawDialogElement& Data;

		bool& TimerActive() { return this->Data.FieldAt<bool>(0xC4); }
		bool& AlternateFrame() { return this->Data.FieldAt<bool>(0xC5); }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		int& DrawItemState() { return this->Data.FieldAt<int>(0xE8); }
	};

	struct CheckboxData
	{
		OwnerDrawDialogElement& Data;

		int& UseNativePaint() { return this->Data.NeedsControlImage; }
		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		bool& UseExtendedArt() { return this->Data.FieldAt<bool>(0xD9); }
		bool& ArtVariant() { return this->Data.FieldAt<bool>(0xDA); }
		int& CheckState() { return this->Data.FieldAt<int>(0xE8); }
	};

	struct RadioData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		int& CheckState() { return this->Data.FieldAt<int>(0xE8); }
	};

	struct InputData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
	};

	struct TabData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
	};

	struct SliderData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return this->Data.FieldAt<BitFont*>(0x64); }
		int& IsMouseTracking() { return this->Data.FieldAt<int>(0xE8); }
		int& IsThumbDragging() { return this->Data.FieldAt<int>(0xEC); }
		int& RangeSpan() { return this->Data.FieldAt<int>(0xF0); }
		int& PositionOffset() { return this->Data.FieldAt<int>(0xF4); }
		int& RangeMin() { return this->Data.FieldAt<int>(0xF8); }
		int& ThumbOffsetPixels() { return this->Data.FieldAt<int>(0xFC); }
		int& StepValue() { return this->Data.FieldAt<int>(0x100); }
		int& ShowValueLabel() { return this->Data.FieldAt<int>(0x104); }
		int& SuppressClickSound() { return this->Data.Extra[0]; }
	};

	struct ProgressData
	{
		OwnerDrawDialogElement& Data;

		int& MinValue() { return this->Data.FieldAt<int>(0xE8); }
		int& MaxValue() { return this->Data.FieldAt<int>(0xEC); }
		int& Position() { return this->Data.FieldAt<int>(0xF0); }
	};

public:
	auto AsScrollBar() { return ScrollBarData { *this }; }
	auto AsListBox() { return ListBoxData { *this }; }
	auto AsComboBox() { return ComboBoxData { *this }; }
	auto AsNewEdit() { return NewEditData { *this }; }
	auto AsEdit() { return EditData { *this }; }
	auto AsStatic() { return StaticData { *this }; }
	auto AsGroupBox() { return GroupBoxData { *this }; }
	auto AsButton() { return ButtonData { *this }; }
	auto AsOwnerDrawButton() { return this->AsButton(); }
	auto AsCheckbox() { return CheckboxData { *this }; }
	auto AsRadio() { return RadioData { *this }; }
	auto AsInput() { return InputData { *this }; }
	auto AsTab() { return TabData { *this }; }
	auto AsSlider() { return SliderData { *this }; }
	auto AsProgress() { return ProgressData { *this }; }

	HWND& LinkedHwnd() { return this->FieldAt<HWND>(0x0C); }
	LPARAM& UnknownProp24() { return this->FieldAt<LPARAM>(0x24); }
};

using WWWinData = OwnerDrawDialogElement;

static_assert(sizeof(OwnerDrawDialogElement) == 0x200, "OwnerDrawDialogElement size mismatch");
static_assert(sizeof(WWWinData) == 0x200, "WWWinData size mismatch");
static_assert(offsetof(OwnerDrawDialogElement, EnumParam) == 0x00, "OwnerDrawDialogElement::EnumParam offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, CacheSurface) == 0x10, "OwnerDrawDialogElement::CacheSurface offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, ControlImage) == 0x14, "OwnerDrawDialogElement::ControlImage offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, StateImageSurface) == 0x18, "OwnerDrawDialogElement::StateImageSurface offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, NeedsControlImage) == 0x20, "OwnerDrawDialogElement::NeedsControlImage offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, TextBuffer) == 0x28, "OwnerDrawDialogElement::TextBuffer offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasText) == 0x2C, "OwnerDrawDialogElement::HasText offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasFocus) == 0x38, "OwnerDrawDialogElement::HasFocus offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, ControlType) == 0x68, "OwnerDrawDialogElement::ControlType offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DialogID) == 0x6C, "OwnerDrawDialogElement::DialogID offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, LayoutBand) == 0xB0, "OwnerDrawDialogElement::LayoutBand offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, SkipDraw) == 0xBC, "OwnerDrawDialogElement::SkipDraw offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasOpenAnimation) == 0xBD, "OwnerDrawDialogElement::HasOpenAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasFadeAnimation) == 0xBE, "OwnerDrawDialogElement::HasFadeAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, TooltipVariant) == 0xC0, "OwnerDrawDialogElement::TooltipVariant offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Alpha) == 0xC8, "OwnerDrawDialogElement::Alpha offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasTopPanelAnimation) == 0xD5, "OwnerDrawDialogElement::HasTopPanelAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasButtonAnimation) == 0xD6, "OwnerDrawDialogElement::HasButtonAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasMainScreenAnimation) == 0xD7, "OwnerDrawDialogElement::HasMainScreenAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, FlagD8) == 0xD8, "OwnerDrawDialogElement::FlagD8 offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, ExtraWidth) == 0xDC, "OwnerDrawDialogElement::ExtraWidth offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DialogBackground) == 0xE0, "OwnerDrawDialogElement::DialogBackground offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DialogBackgroundEx) == 0xE4, "OwnerDrawDialogElement::DialogBackgroundEx offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Extra) == 0x108, "OwnerDrawDialogElement::Extra offset mismatch");

struct OwnerDrawDialogElementLayoutVerifier
{
	static_assert(offsetof(OwnerDrawDialogElement, TypeSpecific_004) == 0x04, "OwnerDrawDialogElement::TypeSpecific_004 offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, ComboBoxHeightInitialized) == 0x1C, "OwnerDrawDialogElement::ComboBoxHeightInitialized offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, Unknown_024) == 0x24, "OwnerDrawDialogElement::Unknown_024 offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, NewEditAsciiOnly) == 0x30, "OwnerDrawDialogElement::NewEditAsciiOnly offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, TypeSpecific_034) == 0x34, "OwnerDrawDialogElement::TypeSpecific_034 offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, NewEditText) == 0x3C, "OwnerDrawDialogElement::NewEditText offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, StaticDrawMode) == 0x70, "OwnerDrawDialogElement::StaticDrawMode offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, StaticFillBackground) == 0xB4, "OwnerDrawDialogElement::StaticFillBackground offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, Unknown_0BF) == 0xBF, "OwnerDrawDialogElement::Unknown_0BF offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, ButtonTimerActive) == 0xC4, "OwnerDrawDialogElement::ButtonTimerActive offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, TypeSpecific_0CC) == 0xCC, "OwnerDrawDialogElement::TypeSpecific_0CC offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, ComboBoxMaxVisibleDropItems) == 0xD0, "OwnerDrawDialogElement::ComboBoxMaxVisibleDropItems offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, CheckboxUseExtendedArt) == 0xD9, "OwnerDrawDialogElement::CheckboxUseExtendedArt offset mismatch");
	static_assert(offsetof(OwnerDrawDialogElement, TypeSpecific_0E8) == 0xE8, "OwnerDrawDialogElement::TypeSpecific_0E8 offset mismatch");
};

enum WWControlMessage : UINT
{
	WW_GETITEMDATA = 0x199,
	WW_SETITEMDATA = 0x19A,
	WW_SLIDER_GETPOS = 0x400,
	WW_SLIDER_GETRANGEMIN = 0x401,
	WW_SLIDER_GETRANGEMAX = 0x402,
	WW_PROGRESS_SETRANGE = 0x401,
	WW_PROGRESS_SETPOS = 0x402,
	WW_INPUT_GETKEY = 0x402,
	WW_SLIDER_SETPOS = 0x405,
	WW_SLIDER_SETRANGE = 0x406,
	WW_INITDIALOG = 0x497,
	WW_SETCOLOR = 0x498,
	WW_SETUNKNOWNPROP24 = 0x49A,
	WW_UNKNOWN49B = 0x49B,
	WW_SETIMAGE = 0x49C,
	WW_SETHASIMAGE = 0x49D,
	WW_SETGDIPROPS = 0x49E,
	WW_GETGDIPROPS = 0x49F,
	WW_GETHWND = 0x4A0,
	WW_SCROLLBAR_UPDATETHUMB = 0x4A5,
	WW_LB_ADDCOLUMN = 0x4A6,
	WW_LB_REMOVECOLUMN = 0x4A7,
	WW_LB_SETCELLTEXT = 0x4A8,
	WW_BRINGTOTOP = 0x4A9,
	WW_SETACTIVEIMAGE = 0x4AA,
	WW_SLIDER_SETSTEP = 0x4AB,
	WW_SLIDER_SHOWVALUE = 0x4AC,
	WW_LB_GETCELLTEXT = 0x4AD,
	WW_SLIDER_SUPPRESSCLICK = 0x4AE,
	WW_EDIT_RESTOREFOCUS = 0x4AF,
	WW_EDIT_DEFERFOCUSRESTORE = 0x4B0,
	WW_SETFILLCOLOR = 0x4B1,
	WW_SETTEXTW = 0x4B2,
	WW_GETTEXTW = 0x4B3,
	WW_SETTEXTA = 0x4B4,
	WW_GETTEXTA = 0x4B5,
	WW_LB_GETTEXTW = 0x4B6,
	WW_LB_GETTEXTA = 0x4B7,
	WW_CB_FINDSTRINGA = 0x4B8,
	WW_CB_FINDSTRINGEXACTA = 0x4B9,
	WW_CB_SELECTSTRINGA = 0x4BA,
	WW_CB_INSERTSTRINGA = 0x4BB,
	WW_CB_ADDSTRINGA = 0x4BC,
	WW_CB_GETLBTEXTA = 0x4BD,
	WW_CB_FINDSTRINGW = 0x4BE,
	WW_CB_FINDSTRINGEXACTW = 0x4BF,
	WW_CB_SELECTSTRINGW = 0x4C0,
	WW_CB_INSERTSTRINGW = 0x4C1,
	WW_CB_ADDSTRINGW = 0x4C2,
	WW_CB_GETLBTEXTW = 0x4C3,
	WW_LB_FINDSTRINGA = 0x4C4,
	WW_LB_FINDSTRINGEXACTA = 0x4C5,
	WW_LB_SELECTSTRINGA = 0x4C6,
	WW_LB_INSERTSTRINGA = 0x4C7,
	WW_LB_ADDSTRINGA = 0x4C8,
	WW_LB_FINDSTRINGW = 0x4C9,
	WW_LB_FINDSTRINGEXACTW = 0x4CA,
	WW_LB_SELECTSTRINGW = 0x4CB,
	WW_LB_INSERTSTRINGW = 0x4CC,
	WW_LB_ADDSTRINGW = 0x4CD,
	WW_SETHASTEXT = 0x4CE,
	WW_LB_GETITEMTEXTFORMAT = 0x4CF,
	WW_CB_GETITEMTEXTFORMAT = 0x4D0,
	WW_SETUNKNOWNPROP30 = 0x4D1,
	WW_DROPDOWN_SETACTIVE = 0x4D2,
	WW_RESETANIMTIMER = 0x4D3,
	WW_STATIC_STOPANIM = 0x4D4,
	WW_STATIC_SETANIMFRAME = 0x4D5,
	WW_STATIC_GETANIMFRAME = 0x4D6,
	WW_STATIC_SETANIMFRAMENOTIFYHWND = 0x4D7,
	WW_STATIC_ANIMFRAMENOTIFY = 0x4D8,
	WW_EDIT_INPUTCHARW = 0x4D9,
	WW_EDIT_ENTERPRESSED = 0x4DA,
	WW_EDIT_TABNAV = 0x4DB,
	WW_BUTTON_SETANIMATED = 0x4DC,
	WW_CB_ENABLEITEMCOLORS = 0x4DD,
	WW_CB_SETMAXVISIBLEDROPITEMS = 0x4DE,
	WW_STATIC_SETCURRENTMOVIEBYINDEX = 0x4DF,
	WW_STATIC_PAUSEMOVIE = 0x4E0,
	WW_STATIC_CONTINUEMOVIE = 0x4E1,
	WW_STATIC_DETACHMOVIE = 0x4E2,
	WW_STATIC_SETLOOPMOVIE = 0x4E3,
	WW_STATIC_SETCURRENTMOVIEBYNAME = 0x4E4,
	WW_CHECKBOX_ENABLEEXTENDEDART = 0x4E5,
	WW_CHECKBOX_SETARTVARIANT = 0x4E6,
	WW_CHECKBOX_GETARTVARIANT = 0x4E7,
	WW_QUERYTOOLTIPHIT = 0x4E8,
	WW_GETTOOLTIPTEXT = 0x4E9,
	WW_DROPDOWN_UNKNOWN4EA = 0x4EA,
	WW_SETUNKNOWNPROP50 = 0x4EB,
	WW_TRANSITION_COMPLETE = 0x4EC,
	WW_TRANSITION_CLOSED = 0x4ED,
	WW_STATIC_REVEALTEXTS = 0x4EE,
	WW_LB_GETSCROLLBARHWND = 0x4EF,
	WW_STATIC_BLITMOVIE = 0x4F0,
	WW_CB_SETALTERNATEPALETTE = 0x4F1,
	WW_DROPDOWN_INITIALIZE = 0x7E8
};

class OwnerDraw
{
public:
	enum ControlID : int
	{
		TooltipText = 1685,
		TransitionMovie = 1818
	};

	static constexpr OwnerDrawLayoutSize BaseLayoutSize { 640, 480 };

	DEFINE_REFERENCE(int, CachedSurfaceCount, 0xAC48B4);
	DEFINE_REFERENCE(WORD, ColorShiftRed, 0xAC48B8);
	DEFINE_REFERENCE(WORD, ColorShiftGreen, 0xAC48BA);
	DEFINE_REFERENCE(WORD, ColorShiftBlue, 0xAC48BC);
	DEFINE_REFERENCE(HWND, CurrentDialogHwnd, 0xAC48A8);

	// Default owner-draw/common-dialog style globals.
	DEFINE_REFERENCE(int, ControlInsetPx, 0xAC1DF0);
	DEFINE_REFERENCE(COLORREF, ListSelectionFillColor, 0xAC4604);
	DEFINE_REFERENCE(COLORREF, DefaultBorderColor, 0xAC4624);
	DEFINE_REFERENCE(int, ScrollButtonBevelAlpha, 0xAC1890);
	DEFINE_REFERENCE(COLORREF, PrimaryTextColor, 0xAC18A4);
	DEFINE_REFERENCE(COLORREF, AltComboTextColor, 0xAC1CB0);
	DEFINE_REFERENCE(COLORREF, ImeCompositionTextColor, 0xAC4618);
	DEFINE_REFERENCE(COLORREF, CaretColor, 0xAC184C);
	DEFINE_REFERENCE(COLORREF, UnusedMidGrayColor, 0xAC4628);
	DEFINE_REFERENCE(COLORREF, AltSelectionFillColor, 0xAC4880);
	DEFINE_REFERENCE(COLORREF, AltBorderColor, 0xAC1DD8);
	DEFINE_REFERENCE(COLORREF, BevelLightColor, 0xAC1B98);
	DEFINE_REFERENCE(COLORREF, BevelShadowColor, 0xAC1B94);
	DEFINE_REFERENCE(COLORREF, DisabledTextColor, 0xAC1CB4);
	DEFINE_REFERENCE(COLORREF, AltDisabledTextColor, 0xAC1AF8);
	DEFINE_REFERENCE(COLORREF, DisabledBorderColor, 0xAC1CA8);
	DEFINE_REFERENCE(COLORREF, AltDisabledBorderColor, 0xAC4620);
	DEFINE_REFERENCE(int, DisabledOverlayAlpha, 0xAC4898);
	DEFINE_REFERENCE(COLORREF, SelectedTabTextColor, 0xAC4608);
	DEFINE_REFERENCE(COLORREF, TooltipBackgroundColor, 0xAC48B0);
	DEFINE_REFERENCE(COLORREF, UnusedDarkAccentColor, 0xAC1B90);
	DEFINE_ARRAY_REFERENCE(wchar_t, [0x101], IMECompositionString, 0xB73318);
	DEFINE_REFERENCE(int, IMECompositionStringLength, 0xB73564);
	DEFINE_REFERENCE(int, IMECompositionCursorPos, 0xB73568);
	DEFINE_REFERENCE(int, IMEComposing, 0xB7356C);

	using HwndProcDict = Dictionary<HWND, WNDPROC>;
	using MsgInProcessDict = Dictionary<OwnerDrawWindowMessageKey, bool>;
	using HwndWinDataDict = Dictionary<HWND, OwnerDrawDialogElement>;

	DEFINE_REFERENCE(HwndProcDict, DialogProcs, 0xAC1B48); // Windows control's default window procedures 
	DEFINE_REFERENCE(HwndProcDict, SubclassProcs, 0xAC18C0); // Custom subclass procedures for owner-draw controls, 
	DEFINE_REFERENCE(MsgInProcessDict, MessageProcessedGuard, 0xAC1858); // Generic OwnerDraw::WindowProc recursion guard.
	DEFINE_REFERENCE(HwndWinDataDict, Dialogs, 0xAC1B00); // Primary owner-draw dialog/control table keyed by HWND.
	DEFINE_REFERENCE(HwndWinDataDict, WinData, 0xAC1B00); // Backward-compatible alias for Dialogs.
	DEFINE_REFERENCE(int, ActiveWindowStackCount, 0xAC1DE0);
	DEFINE_REFERENCE(int, ActiveWindowStackCapacity, 0xAC1DE4);
	DEFINE_REFERENCE(HWND*, ActiveWindowStack, 0xAC1DE8);
	DEFINE_REFERENCE(int, AboutToCallSetWindowPos, 0xAC48E8);
	DEFINE_REFERENCE(OwnerDrawTooltipBlitState, TooltipBlitState, 0xAC1CB8);
	DEFINE_REFERENCE(int, PaintDepth, 0xAC48DC);
	DEFINE_REFERENCE(int, PaintRight, 0xAC48E0);
	DEFINE_REFERENCE(int, PaintBottom, 0xAC48E4);
	DEFINE_REFERENCE(int, PaintLeft, 0x83367C);
	DEFINE_REFERENCE(int, PaintTop, 0x833680);
	DEFINE_REFERENCE(HWND, ComboDropActiveDropHwnd, 0xAC48C0);
	DEFINE_REFERENCE(HWND, ComboDropActiveParentHwnd, 0xAC48C4);
	DEFINE_REFERENCE(char, ButtonSliceVariant, 0x833684);
	DEFINE_REFERENCE(SHPStruct*, SideButtonShape, 0xB0F9EC);
	DEFINE_REFERENCE(BYTE, ButtonDisabledSide0Red, 0xB0F9FC);
	DEFINE_REFERENCE(WORD, ButtonDisabledSide0GreenBlue, 0xB0F9FD);
	DEFINE_REFERENCE(BYTE, ButtonDisabledSide1Red, 0xB0FB14);
	DEFINE_REFERENCE(WORD, ButtonDisabledSide1GreenBlue, 0xB0FB15);
	DEFINE_REFERENCE(BYTE, ButtonDisabledSideOtherRed, 0xB0FB19);
	DEFINE_REFERENCE(WORD, ButtonDisabledSideOtherGreenBlue, 0xB0FB1A);
	DEFINE_REFERENCE(SHPStruct*, SmallButtonAnimShape, 0xB0FAC4);
	DEFINE_REFERENCE(SHPStruct*, CloseButtonShape, 0xB0FACC);

	// WWControlType::Button
	DEFINE_REFERENCE(WNDPROC, CheckBoxButtonHandler, 0x6163A0);
	DEFINE_REFERENCE(WNDPROC, GroupBoxButtonHandler, 0x61E700);
	DEFINE_REFERENCE(WNDPROC, AutoRadioButtonHandler, 0x616980);
	DEFINE_REFERENCE(WNDPROC, OwnerDrawButtonHandler, 0x612B70);
	// WWControlType::Edit
	DEFINE_REFERENCE(WNDPROC, EditHandler, 0x614190);
	DEFINE_REFERENCE(WNDPROC, NewEditHandler, 0x614B30);
	// WWControlType::Static
	DEFINE_REFERENCE(WNDPROC, StaticHandler, 0x6153E0);
	// WWControlType::ComboBox
	DEFINE_REFERENCE(WNDPROC, ComboBoxHandler, 0x617250);
	// WWControlType::ListBox
	DEFINE_REFERENCE(WNDPROC, ListBoxHandler, 0x618D40);
	// WWControlType::Progress
	DEFINE_REFERENCE(WNDPROC, ProgressHandler, 0x61D6D0);
	// WWControlType::TrackBar
	DEFINE_REFERENCE(WNDPROC, TrackBarHandler, 0x61D950);
	// WWControlType::ScrollBar
	DEFINE_REFERENCE(WNDPROC, ScrollBarHandler, 0x61C690);
	// WWControlType::Hotkey
	DEFINE_REFERENCE(WNDPROC, HotkeyHandler, 0x61ECA0);
	// WWControlType::SysTab
	DEFINE_REFERENCE(WNDPROC, SysTabHandler, 0x6137D0);
	// WWControlType::SysListView
	DEFINE_REFERENCE(WNDPROC, SysListViewHandler, 0x612A60);

	// Westwood Registered extra handlers
	// ComboDropWin
	DEFINE_REFERENCE(WNDPROC, ComboDropWindowHandler, 0x60D540);
	// NewEdit uses DefWindowProcA here, doesnt matter cause OwnerDraw above did it
	DEFINE_REFERENCE(WNDPROC, NewEditDefaultHandler, 0x60D520);

	DEFINE_REFERENCE(WNDPROC, DefaultHandler, 0x610CA0); // Generic handler which call the handles above

	// Get rectangle relative to game main window's client area
	static int __fastcall GetRectangle(HWND hWnd, LPRECT lpRect) { JMP_STD(0x775690); }

	static bool __fastcall ServiceIMEMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { JMP_STD(0x778030); }
	static LRESULT __fastcall GetIMEResult() { JMP_STD(0x778120); }
	static void __fastcall CancelIMEComposition() { JMP_STD(0x777E00); }
	static void __fastcall UpdateIMECompositionString() { JMP_STD(0x777EA0); }
	static wchar_t __fastcall ConvertIMECharToWide(UINT wParam, LPARAM lParam) { JMP_STD(0x7781B0); }
	static bool __fastcall IsWebBrowserVisible() { JMP_STD(0x774070); }
	static void __fastcall WideToCharString(char* pBuffer, const wchar_t* pText, size_t bufferSize) { JMP_STD(0x735090); }
	static bool __fastcall RunOpenAnimationIfNeeded(HWND hWnd) { JMP_STD(0x608260); }
	static bool __fastcall DrawTooltip(bool captureBackground) { JMP_STD(0x610950); }
	static bool RestoreTooltipBackground() { JMP_STD(0x610B50); }
	static int __fastcall DrawBeveledBorder(Surface* pSurface, RectangleStruct* pRect, int thickness, int color) { JMP_STD(0x6208F0); }
	static int __fastcall PrintTextFixedLength(unsigned int color, BitFont* pFont, RectangleStruct* pRect, const wchar_t* pText, int length, int horizontalAlign, int verticalAlign, Surface* pSurface, int animPos) { JMP_STD(0x6211D0); }
	static bool __fastcall CopyDimmedBackground(RectangleStruct* pRect, HWND hWnd, unsigned int dimAlpha) { JMP_STD(0x6214B0); }
	static void __fastcall BlendGradientRect(RectangleStruct* pRect, Surface* pSurface, unsigned short color, int widthScale) { JMP_STD(0x6217E0); }
	static WWMovieHandle* __fastcall InitMovieHandle(const char* pMovieName, DSurface* pSurface, RectangleStruct* pBounds) { JMP_STD(0x5C07D0); }
	static BOOL CALLBACK CollectChildHwndProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x622470); }
	static BOOL CALLBACK SendTransitionCompleteToCustomTextChildProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x60AA60); }
	static BOOL CALLBACK InitCompactDialogControlsProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x60AAB0); }
	static BOOL CALLBACK ClassifyLayoutBand(HWND hWnd, LPARAM lParam) { JMP_STD(0x60A330); }
	static BOOL CALLBACK ResetControlDrawModeAndTimerProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x60A5B0); }
	static BOOL CALLBACK ReplaceEditWithListboxProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x60F320); }
	static BOOL CALLBACK SetNeedsControlImage(HWND hWnd, LPARAM lParam) { JMP_STD(0x60F760); }
	static BOOL CALLBACK RegisterChildControlProc(HWND hWnd, LPARAM lParam) { JMP_STD(0x60F9A0); }

	static void __fastcall PrepareDialogChildControls(HWND hWnd, int mode) { JMP_STD(0x60F4B0); }
	static void __fastcall ScaleControls(HWND hWnd) { JMP_STD(0x775BA0); }
	static void __fastcall SetDialogID(HWND hWnd, int dialogID) { JMP_STD(0x60D2C0); }
	static void __fastcall LoadNotInGameResources(HWND hWnd) { JMP_STD(0x60CF00); }
	static bool __fastcall UpdateTopPanelAnimationFlag(HWND hWnd) { JMP_STD(0x60CAF0); }
	static bool __fastcall UpdateButtonAnimationFlag(HWND hWnd) { JMP_STD(0x60C930); }
	static bool __fastcall UpdateMainScreenAnimationFlag(HWND hWnd) { JMP_STD(0x60CCC0); }
	static bool __fastcall UpdateFlagD8FromDialogID(HWND hWnd) { JMP_STD(0x60CDB0); }
	static bool __fastcall TrySetDialogLayoutBand1(HWND hWnd) { JMP_STD(0x60C540); }
	static bool __fastcall TrySetDialogLayoutBand2(HWND hWnd) { JMP_STD(0x60C7D0); }
	static void __fastcall UpdateControlPosition(HWND hWnd, OwnerDrawLayoutSize* pBaseSize) { JMP_STD(0x60C4A0); }
	static void __fastcall DrawItem(DRAWITEMSTRUCT* pDrawItem) { JMP_STD(0x6213A0); }
	static int __fastcall DrawWideText(Surface* pSurface, const wchar_t* pText, RECT* pRect, BitFont* pFont, COLORREF color, int style, int verticalAlign, int unused8, int backgroundMode, int colorAdjust) { JMP_STD(0x621040); }
	static void __fastcall Paint(HWND hWnd) { JMP_STD(0x621E90); }
	static const char* __fastcall GetTooltipStringLabel(HWND dialogHwnd, HWND controlHwnd) { JMP_STD(0x6040B0); }
	static void __fastcall DrawCampaignMenuTransition(HWND dialogHwnd, bool isOpening) { JMP_STD(0x6071E0); }
	static ConvertClass* __fastcall GetSmallButtonAnimConvert() { JMP_STD(0x72E2C0); }
	static ConvertClass* __fastcall GetSideButtonConvert() { JMP_STD(0x72F4B0); }
	static ConvertClass* __fastcall GetCloseButtonConvert() { JMP_STD(0x72B050); }
};

namespace SessionIpb
{
	inline void __fastcall RegisterHwnd(HWND hWnd) { JMP_STD(0x53E3C0); }
	inline void __fastcall UnregisterHwnd(HWND hWnd) { JMP_STD(0x53E420); }
}
