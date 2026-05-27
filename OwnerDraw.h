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
	void* ShortDictNext;
	int Unknown_008;
	HWND Hwnd_00C;
	Surface* CacheSurface;
	Surface* ControlImage;
	Surface* StateImageSurface;
	int ComboHeightInitialized;
	int NeedsControlImage;
	LPARAM Erase1;
	wchar_t* TextBuffer;
	int HasText;
	WPARAM Erase2;
	void* TextEntries;
	int HasFocus;
	WideWstring* WideString;
	int Unknown_040;
	int AnimationStart;
	int Unknown_048;
	int Unknown_04C;
	LPARAM LParam3;
	int UserDataAux;
	int Unknown_058;
	int Unknown_05C;
	int Unknown_060;
	void* Font;
	WWControlType ControlType;
	int DialogID;
	int DrawMode;
	void* BKDrawer;
	Surface* CampaignImage;
	int CampaignImageLoadedFlag;
	int HasCustomTextMetrics;
	int TextHeightOrOffset;
	void* TextStyleClass;
	int TextRenderFlags;
	int CharTypedSound;
	int CurrentFrameHeight;
	int AnimationState;
	int LastTick;
	int TimerInterval;
	int Unknown_0A4;
	bool AnimationActive;
	bool Unknown_A9;
	bool Unknown_AA;
	bool Unknown_AB;
	int Unknown_0AC;
	int LayoutBand;
	int Unknown_0B4;
	int TransitionFlags;
	bool SkipDraw;
	bool HasOpenAnimation;
	bool HasFadeAnimation;
	bool Unknown_BF;
	int TooltipVariant;
	int HoverTimerFlags;
	int Alpha;
	int ComboVisualFlags;
	int RuntimeFlags;
	bool Unknown_D4;
	bool HasTopPanelAnimation;
	bool HasButtonAnimation;
	bool HasMainScreenAnimation;
	bool FlagD8;
	bool Unknown_D9;
	bool Unknown_DA;
	bool Unknown_DB;
	int ExtraWidth;
	Surface* DialogBackground;
	Surface* DialogBackgroundEx;
	int DrawItemState;
	int Unknown_0EC;
	int FocusRestorePending;
	int EditFocusRestoreReady;
	LPARAM LParam;
	WNDPROC PrevWndProc;
	LPARAM LParam1;
	LPARAM LParam2;
	int Extra[62];

private:
	void CopyFrom(const OwnerDrawDialogElement& rhs)
	{
		auto* const pOwnedTextBuffer = this->TextBuffer;
		auto* const pOwnedTextEntries = this->TextEntries;
		auto* const pOwnedWideString = this->WideString;

		std::memcpy(this, &rhs, sizeof(*this));

		this->TextBuffer = pOwnedTextBuffer;
		this->TextEntries = pOwnedTextEntries;
		this->WideString = pOwnedWideString;

		this->SetTextBufferCopy(rhs.TextBuffer);
		this->SetTextEntriesCopy(rhs.TextEntries);
		this->SetWideStringCopy(rhs.WideString);
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
		while (this->TextEntries)
		{
			auto* const pEntry = static_cast<WWUIComboBoxItem*>(this->TextEntries);
			this->TextEntries = pEntry->Next;
			YRMemory::Deallocate(pEntry);
		}
	}

	void SetTextEntriesCopy(void* pSource)
	{
		this->ClearTextEntries();

		for (auto* pEntry = static_cast<WWUIComboBoxItem*>(pSource); pEntry; pEntry = pEntry->Next)
		{
			const auto* const pText = pEntry->Text ? pEntry->Text : L"";
			const auto bytes = sizeof(WWUIComboBoxItem) + (std::wcslen(pText) + 1) * sizeof(wchar_t);
			auto* const pCopy = static_cast<WWUIComboBoxItem*>(YRMemory::Allocate(bytes));

			if (!pCopy)
				continue;

			pCopy->Next = static_cast<WWUIComboBoxItem*>(this->TextEntries);
			pCopy->ItemData = pEntry->ItemData;
			pCopy->Text = reinterpret_cast<wchar_t*>(reinterpret_cast<char*>(pCopy) + sizeof(WWUIComboBoxItem));
			pCopy->IsWideText = pEntry->IsWideText;
			std::wcscpy(pCopy->Text, pText);

			this->TextEntries = pCopy;
		}
	}

	void ClearWideString()
	{
		if (this->WideString)
		{
			this->WideString->~WideWstring();
			YRMemory::Deallocate(this->WideString);
			this->WideString = nullptr;
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

		this->WideString = new (pCopy) WideWstring(*pSource);
	}

	template<typename T>
	T& FieldAt(size_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + offset);
	}

public:
	struct ScrollBarData
	{
		OwnerDrawDialogElement& Data;

		HWND& NotifyHwnd() { return this->Data.FieldAt<HWND>(0x08); }
		bool& Disabled() { return this->Data.FieldAt<bool>(0xCD); }
		int& IsMouseTracking() { return this->Data.DrawItemState; }
		int& IsThumbDragging() { return this->Data.Unknown_0EC; }
		int& RangeMax() { return this->Data.FocusRestorePending; }
		int& Position() { return this->Data.EditFocusRestoreReady; }
		int& UpButtonPressed() { return reinterpret_cast<int&>(this->Data.LParam); }
		int& DownButtonPressed() { return reinterpret_cast<int&>(this->Data.PrevWndProc); }
		int& RestoreCaptureToNotifyHwnd() { return reinterpret_cast<int&>(this->Data.LParam1); }
	};

	struct ListBoxData
	{
		OwnerDrawDialogElement& Data;

		HWND& ScrollBarHwnd() { return this->Data.Hwnd_00C; }
		int& ScrollBarWidth() { return reinterpret_cast<int&>(this->Data.ShortDictNext); }
		WWUIListBoxTextEntry*& TextEntries() { return reinterpret_cast<WWUIListBoxTextEntry*&>(this->Data.TextEntries); }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		WWUIIntArray*& ItemData() { return reinterpret_cast<WWUIIntArray*&>(this->Data.DrawItemState); }
		WWUIIntArray*& SelectionStates() { return reinterpret_cast<WWUIIntArray*&>(this->Data.Unknown_0EC); }
		int& TopIndex() { return this->Data.FocusRestorePending; }
		int& CurrentSelection() { return this->Data.EditFocusRestoreReady; }
		WWUIListBoxColumnArray*& Columns() { return reinterpret_cast<WWUIListBoxColumnArray*&>(this->Data.LParam); }
	};

	struct ComboBoxData
	{
		OwnerDrawDialogElement& Data;

		WWUIComboBoxItem*& TextEntries() { return reinterpret_cast<WWUIComboBoxItem*&>(this->Data.TextEntries); }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		bool& UseItemColorOverrides() { return this->Data.FieldAt<bool>(0xCC); }
		bool& UseAlternatePalette() { return this->Data.FieldAt<bool>(0xCD); }
		int& MaxVisibleDropItems() { return this->Data.RuntimeFlags; }
		HWND& DropDownHwnd() { return reinterpret_cast<HWND&>(this->Data.EditFocusRestoreReady); }
		int& CurrentSelection() { return reinterpret_cast<int&>(this->Data.LParam); }
		int* ItemColorOverrides() { return &this->Data.Extra[2]; }
	};

	struct NewEditData
	{
		OwnerDrawDialogElement& Data;

		WideWstring*& Text() { return this->Data.WideString; }
		int& CaretIndex() { return this->Data.Unknown_040; }
		int& ScrollStart() { return this->Data.AnimationStart; }
		int& TextLimit() { return this->Data.Unknown_048; }
		int& CaretBlinkState() { return this->Data.Unknown_04C; }
		wchar_t*& RejectChars() { return reinterpret_cast<wchar_t*&>(this->Data.LParam3); }
		int& AsciiOnly() { return reinterpret_cast<int&>(this->Data.Erase2); }
		int& StyleFlags() { return this->Data.UserDataAux; }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
	};

	struct EditData
	{
		OwnerDrawDialogElement& Data;

		int& TextScrollStart() { return this->Data.AnimationStart; }
		BitFont*& TextFont() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		int& FocusRestorePendingFlag() { return this->Data.FocusRestorePending; }
		int& FocusRestoreReadyFlag() { return this->Data.EditFocusRestoreReady; }
		int& RestoreTabStopFlag() { return reinterpret_cast<int&>(this->Data.LParam); }
	};

	struct StaticData
	{
		OwnerDrawDialogElement& Data;

		Surface*& CachedBackground() { return this->Data.CacheSurface; }
		Surface*& ImageSurface() { return this->Data.ControlImage; }
		wchar_t*& Text() { return this->Data.TextBuffer; }
		WWMovieHandle*& MovieHandle() { return reinterpret_cast<WWMovieHandle*&>(this->Data.Unknown_058); }
		int& LoopMovie() { return this->Data.Unknown_05C; }
		void*& MovieAuxHandle() { return reinterpret_cast<void*&>(this->Data.Unknown_060); }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		WWUIStaticDrawMode& DrawMode() { return reinterpret_cast<WWUIStaticDrawMode&>(this->Data.DrawMode); }
		ConvertClass*& ShapeDrawer() { return reinterpret_cast<ConvertClass*&>(this->Data.BKDrawer); }
		SHPStruct*& Shape() { return reinterpret_cast<SHPStruct*&>(this->Data.CampaignImage); }
		bool& OwnsShape() { return this->Data.FieldAt<bool>(0x7C); }
		int& TextRevealCount() { return this->Data.HasCustomTextMetrics; }
		int& TextRevealDelay() { return this->Data.TextHeightOrOffset; }
		int& TextRevealStep() { return reinterpret_cast<int&>(this->Data.TextStyleClass); }
		int& ColorAdjust() { return this->Data.TextRenderFlags; }
		int& SoundIndex() { return this->Data.CharTypedSound; }
		int& FrameCount() { return this->Data.CurrentFrameHeight; }
		int& CurrentFrame() { return this->Data.AnimationState; }
		int& LastFrameTick() { return this->Data.LastTick; }
		int& FrameDelayMs() { return this->Data.TimerInterval; }
		HWND& FrameNotifyHwnd() { return reinterpret_cast<HWND&>(this->Data.Unknown_0A4); }
		bool& AnimationRunning() { return this->Data.AnimationActive; }
		int& TextFlags() { return this->Data.Unknown_0AC; }
		bool& FillBackground() { return this->Data.FieldAt<bool>(0xB4); }
		COLORREF& FillColor() { return reinterpret_cast<COLORREF&>(this->Data.TransitionFlags); }
		bool& SuppressPaint() { return this->Data.SkipDraw; }
		COLORREF& TextColor() { return reinterpret_cast<COLORREF&>(this->Data.Unknown_0EC); }
	};

	struct GroupBoxData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
	};

	struct OwnerDrawButtonData
	{
		OwnerDrawDialogElement& Data;

		bool& TimerActive() { return this->Data.FieldAt<bool>(0xC4); }
		bool& AlternateFrame() { return this->Data.FieldAt<bool>(0xC5); }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
	};

	struct CheckboxData
	{
		OwnerDrawDialogElement& Data;

		int& UseNativePaint() { return this->Data.NeedsControlImage; }
		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		bool& UseExtendedArt() { return this->Data.Unknown_D9; }
		bool& ArtVariant() { return this->Data.Unknown_DA; }
		int& CheckState() { return this->Data.DrawItemState; }
	};

	struct RadioData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		int& CheckState() { return this->Data.DrawItemState; }
	};

	struct InputData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
	};

	struct TabData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
	};

	struct SliderData
	{
		OwnerDrawDialogElement& Data;

		BitFont*& Font() { return reinterpret_cast<BitFont*&>(this->Data.Font); }
		int& IsMouseTracking() { return this->Data.DrawItemState; }
		int& IsThumbDragging() { return this->Data.Unknown_0EC; }
		int& RangeSpan() { return this->Data.FocusRestorePending; }
		int& PositionOffset() { return this->Data.EditFocusRestoreReady; }
		int& RangeMin() { return reinterpret_cast<int&>(this->Data.LParam); }
		int& ThumbOffsetPixels() { return reinterpret_cast<int&>(this->Data.PrevWndProc); }
		int& StepValue() { return reinterpret_cast<int&>(this->Data.LParam1); }
		int& ShowValueLabel() { return reinterpret_cast<int&>(this->Data.LParam2); }
		int& SuppressClickSound() { return this->Data.Extra[0]; }
	};

	struct ProgressData
	{
		OwnerDrawDialogElement& Data;

		int& MinValue() { return this->Data.DrawItemState; }
		int& MaxValue() { return this->Data.Unknown_0EC; }
		int& Position() { return this->Data.FocusRestorePending; }
	};

	ScrollBarData AsScrollBar() { return { *this }; }
	ListBoxData AsListBox() { return { *this }; }
	ComboBoxData AsComboBox() { return { *this }; }
	NewEditData AsNewEdit() { return { *this }; }
	EditData AsEdit() { return { *this }; }
	StaticData AsStatic() { return { *this }; }
	GroupBoxData AsGroupBox() { return { *this }; }
	OwnerDrawButtonData AsOwnerDrawButton() { return { *this }; }
	CheckboxData AsCheckbox() { return { *this }; }
	RadioData AsRadio() { return { *this }; }
	InputData AsInput() { return { *this }; }
	TabData AsTab() { return { *this }; }
	SliderData AsSlider() { return { *this }; }
	ProgressData AsProgress() { return { *this }; }

	HWND& ScrollBarNotifyHwnd() { return this->AsScrollBar().NotifyHwnd(); }
	bool& ScrollBarDisabled() { return this->AsScrollBar().Disabled(); }
	int& ScrollBarIsMouseTracking() { return this->AsScrollBar().IsMouseTracking(); }
	int& ScrollBarIsThumbDragging() { return this->AsScrollBar().IsThumbDragging(); }
	int& ScrollBarRangeMax() { return this->AsScrollBar().RangeMax(); }
	int& ScrollBarPosition() { return this->AsScrollBar().Position(); }
	int& ScrollBarUpButtonPressed() { return this->AsScrollBar().UpButtonPressed(); }
	int& ScrollBarDownButtonPressed() { return this->AsScrollBar().DownButtonPressed(); }
	int& ScrollBarRestoreCaptureToNotifyHwnd() { return this->AsScrollBar().RestoreCaptureToNotifyHwnd(); }

	HWND& ListBoxScrollBarHwnd() { return this->AsListBox().ScrollBarHwnd(); }
	int& ListBoxScrollBarWidth() { return this->AsListBox().ScrollBarWidth(); }
	WWUIListBoxTextEntry*& ListBoxTextEntries() { return this->AsListBox().TextEntries(); }
	BitFont*& ListBoxFont() { return this->AsListBox().Font(); }
	WWUIIntArray*& ListBoxItemData() { return this->AsListBox().ItemData(); }
	WWUIIntArray*& ListBoxSelectionStates() { return this->AsListBox().SelectionStates(); }
	int& ListBoxTopIndex() { return this->AsListBox().TopIndex(); }
	int& ListBoxCurrentSelection() { return this->AsListBox().CurrentSelection(); }
	WWUIListBoxColumnArray*& ListBoxColumns() { return this->AsListBox().Columns(); }

	WWUIComboBoxItem*& ComboBoxTextEntries() { return this->AsComboBox().TextEntries(); }
	BitFont*& ComboBoxFont() { return this->AsComboBox().Font(); }
	bool& ComboBoxUseItemColorOverrides() { return this->AsComboBox().UseItemColorOverrides(); }
	bool& ComboBoxUseAlternatePalette() { return this->AsComboBox().UseAlternatePalette(); }
	int& ComboBoxMaxVisibleDropItems() { return this->AsComboBox().MaxVisibleDropItems(); }
	HWND& ComboBoxDropDownHwnd() { return this->AsComboBox().DropDownHwnd(); }
	int& ComboBoxCurrentSelection() { return this->AsComboBox().CurrentSelection(); }
	int* ComboBoxItemColorOverrides() { return this->AsComboBox().ItemColorOverrides(); }

	WideWstring*& NewEditText() { return this->AsNewEdit().Text(); }
	int& NewEditCaretIndex() { return this->AsNewEdit().CaretIndex(); }
	int& NewEditScrollStart() { return this->AsNewEdit().ScrollStart(); }
	int& NewEditTextLimit() { return this->AsNewEdit().TextLimit(); }
	int& NewEditCaretBlinkState() { return this->AsNewEdit().CaretBlinkState(); }
	wchar_t*& NewEditRejectChars() { return this->AsNewEdit().RejectChars(); }
	int& NewEditAsciiOnly() { return this->AsNewEdit().AsciiOnly(); }
	int& NewEditStyleFlags() { return this->AsNewEdit().StyleFlags(); }
	BitFont*& NewEditFont() { return this->AsNewEdit().Font(); }

	int& EditTextScrollStart() { return this->AsEdit().TextScrollStart(); }
	BitFont*& EditTextFont() { return this->AsEdit().TextFont(); }
	int& EditFocusRestorePendingFlag() { return this->AsEdit().FocusRestorePendingFlag(); }
	int& EditFocusRestoreReadyFlag() { return this->AsEdit().FocusRestoreReadyFlag(); }
	int& EditRestoreTabStopFlag() { return this->AsEdit().RestoreTabStopFlag(); }

	Surface*& StaticCachedBackground() { return this->AsStatic().CachedBackground(); }
	Surface*& StaticImageSurface() { return this->AsStatic().ImageSurface(); }
	wchar_t*& StaticText() { return this->AsStatic().Text(); }
	WWMovieHandle*& StaticMovieHandle() { return this->AsStatic().MovieHandle(); }
	int& StaticLoopMovie() { return this->AsStatic().LoopMovie(); }
	void*& StaticMovieAuxHandle() { return this->AsStatic().MovieAuxHandle(); }
	BitFont*& StaticFont() { return this->AsStatic().Font(); }
	WWUIStaticDrawMode& StaticDrawMode() { return this->AsStatic().DrawMode(); }
	ConvertClass*& StaticShapeDrawer() { return this->AsStatic().ShapeDrawer(); }
	SHPStruct*& StaticShape() { return this->AsStatic().Shape(); }
	bool& StaticOwnsShape() { return this->AsStatic().OwnsShape(); }
	int& StaticTextRevealCount() { return this->AsStatic().TextRevealCount(); }
	int& StaticTextRevealDelay() { return this->AsStatic().TextRevealDelay(); }
	int& StaticTextRevealStep() { return this->AsStatic().TextRevealStep(); }
	int& StaticColorAdjust() { return this->AsStatic().ColorAdjust(); }
	int& StaticSoundIndex() { return this->AsStatic().SoundIndex(); }
	int& StaticFrameCount() { return this->AsStatic().FrameCount(); }
	int& StaticCurrentFrame() { return this->AsStatic().CurrentFrame(); }
	int& StaticLastFrameTick() { return this->AsStatic().LastFrameTick(); }
	int& StaticFrameDelayMs() { return this->AsStatic().FrameDelayMs(); }
	HWND& StaticFrameNotifyHwnd() { return this->AsStatic().FrameNotifyHwnd(); }
	bool& StaticAnimationRunning() { return this->AsStatic().AnimationRunning(); }
	int& StaticTextFlags() { return this->AsStatic().TextFlags(); }
	bool& StaticFillBackground() { return this->AsStatic().FillBackground(); }
	COLORREF& StaticFillColor() { return this->AsStatic().FillColor(); }
	bool& StaticSuppressPaint() { return this->AsStatic().SuppressPaint(); }
	COLORREF& StaticTextColor() { return this->AsStatic().TextColor(); }

	BitFont*& GroupBoxFont() { return this->AsGroupBox().Font(); }

	bool& OwnerDrawButtonTimerActive() { return this->AsOwnerDrawButton().TimerActive(); }
	bool& OwnerDrawButtonAlternateFrame() { return this->AsOwnerDrawButton().AlternateFrame(); }
	BitFont*& OwnerDrawButtonFont() { return this->AsOwnerDrawButton().Font(); }

	int& CheckboxUseNativePaint() { return this->AsCheckbox().UseNativePaint(); }
	BitFont*& CheckboxFont() { return this->AsCheckbox().Font(); }
	bool& CheckboxUseExtendedArt() { return this->AsCheckbox().UseExtendedArt(); }
	bool& CheckboxArtVariant() { return this->AsCheckbox().ArtVariant(); }
	int& CheckboxCheckState() { return this->AsCheckbox().CheckState(); }

	BitFont*& RadioFont() { return this->AsRadio().Font(); }
	int& RadioCheckState() { return this->AsRadio().CheckState(); }

	BitFont*& InputFont() { return this->AsInput().Font(); }

	BitFont*& TabFont() { return this->AsTab().Font(); }

	BitFont*& SliderFont() { return this->AsSlider().Font(); }
	int& SliderIsMouseTracking() { return this->AsSlider().IsMouseTracking(); }
	int& SliderIsThumbDragging() { return this->AsSlider().IsThumbDragging(); }
	int& SliderRangeSpan() { return this->AsSlider().RangeSpan(); }
	int& SliderPositionOffset() { return this->AsSlider().PositionOffset(); }
	int& SliderRangeMin() { return this->AsSlider().RangeMin(); }
	int& SliderThumbOffsetPixels() { return this->AsSlider().ThumbOffsetPixels(); }
	int& SliderStepValue() { return this->AsSlider().StepValue(); }
	int& SliderShowValueLabel() { return this->AsSlider().ShowValueLabel(); }
	int& SliderSuppressClickSound() { return this->AsSlider().SuppressClickSound(); }

	int& ProgressMinValue() { return this->AsProgress().MinValue(); }
	int& ProgressMaxValue() { return this->AsProgress().MaxValue(); }
	int& ProgressPosition() { return this->AsProgress().Position(); }
};

using WWWinData = OwnerDrawDialogElement;

static_assert(sizeof(OwnerDrawDialogElement) == 0x200, "OwnerDrawDialogElement size mismatch");
static_assert(sizeof(WWWinData) == 0x200, "WWWinData size mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Hwnd_00C) == 0x0C, "OwnerDrawDialogElement::Hwnd_00C offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, CacheSurface) == 0x10, "OwnerDrawDialogElement::CacheSurface offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, NeedsControlImage) == 0x20, "OwnerDrawDialogElement::NeedsControlImage offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, TextBuffer) == 0x28, "OwnerDrawDialogElement::TextBuffer offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasFocus) == 0x38, "OwnerDrawDialogElement::HasFocus offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DialogID) == 0x6C, "OwnerDrawDialogElement::DialogID offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DrawMode) == 0x70, "OwnerDrawDialogElement::DrawMode offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, AnimationActive) == 0xA8, "OwnerDrawDialogElement::AnimationActive offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, LayoutBand) == 0xB0, "OwnerDrawDialogElement::LayoutBand offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, SkipDraw) == 0xBC, "OwnerDrawDialogElement::SkipDraw offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasOpenAnimation) == 0xBD, "OwnerDrawDialogElement::HasOpenAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasFadeAnimation) == 0xBE, "OwnerDrawDialogElement::HasFadeAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, TooltipVariant) == 0xC0, "OwnerDrawDialogElement::TooltipVariant offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Alpha) == 0xC8, "OwnerDrawDialogElement::Alpha offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, ComboVisualFlags) == 0xCC, "OwnerDrawDialogElement::ComboVisualFlags offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasTopPanelAnimation) == 0xD5, "OwnerDrawDialogElement::HasTopPanelAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasButtonAnimation) == 0xD6, "OwnerDrawDialogElement::HasButtonAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, HasMainScreenAnimation) == 0xD7, "OwnerDrawDialogElement::HasMainScreenAnimation offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, FlagD8) == 0xD8, "OwnerDrawDialogElement::FlagD8 offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, DrawItemState) == 0xE8, "OwnerDrawDialogElement::DrawItemState offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Unknown_0EC) == 0xEC, "OwnerDrawDialogElement::Unknown_0EC offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, FocusRestorePending) == 0xF0, "OwnerDrawDialogElement::FocusRestorePending offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, EditFocusRestoreReady) == 0xF4, "OwnerDrawDialogElement::EditFocusRestoreReady offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, LParam) == 0xF8, "OwnerDrawDialogElement::LParam offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, PrevWndProc) == 0xFC, "OwnerDrawDialogElement::PrevWndProc offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, LParam1) == 0x100, "OwnerDrawDialogElement::LParam1 offset mismatch");
static_assert(offsetof(OwnerDrawDialogElement, Extra) == 0x108, "OwnerDrawDialogElement::Extra offset mismatch");

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
