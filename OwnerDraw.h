#pragma once

// Westwood owner draw and dialog hell

#include <Helpers/CompileTime.h>

#include <Dictionary.h>
#include <Unsorted.h>
#include <Wstring.h>

#include <cstddef>
#include <cstring>

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

enum class WWControlType : int
{
	Button = 0,
	Edit = 1,
	Static = 2,
	ComboBox = 3,
	ListBox = 4,
	ColorTextInput = 5,	// Not seen anywhere but 11 seems to be default value and has same behavior as this one, leave 5 skipped seems weird so maybe this is it
	Progress = 6,
	TrackBar = 7,
	ScrollBar = 8,
	Hotkey = 9,
	SysTab = 10,
	Default = 11
};

struct WWWinData
{
	WWWinData() { JMP_THIS(0x623340); }

	~WWWinData() { JMP_THIS(0x6233A0); }

	BYTE Unknown_00[0x6C];
	int DialogID;
	BYTE Unknown_70[0x40];
	int LayoutBand;
	BYTE Unknown_B4[0x8];
	bool SkipDraw;
	bool HasOpenAnimation;
	bool HasFadeAnimation;
	BYTE Unknown_BF[0x1];
	int TooltipVariant;
	BYTE Unknown_C4[0x11];
	bool HasTopPanelAnimation;
	bool HasButtonAnimation;
	bool HasMainScreenAnimation;
	bool FlagD8;
	BYTE Unknown_D9[0x127];
};

static_assert(sizeof(WWWinData) == 0x200, "WWWinData size mismatch");
static_assert(offsetof(WWWinData, DialogID) == 0x6C, "WWWinData::DialogID offset mismatch");
static_assert(offsetof(WWWinData, LayoutBand) == 0xB0, "WWWinData::LayoutBand offset mismatch");
static_assert(offsetof(WWWinData, SkipDraw) == 0xBC, "WWWinData::SkipDraw offset mismatch");
static_assert(offsetof(WWWinData, HasOpenAnimation) == 0xBD, "WWWinData::HasOpenAnimation offset mismatch");
static_assert(offsetof(WWWinData, HasFadeAnimation) == 0xBE, "WWWinData::HasFadeAnimation offset mismatch");
static_assert(offsetof(WWWinData, TooltipVariant) == 0xC0, "WWWinData::TooltipVariant offset mismatch");
static_assert(offsetof(WWWinData, HasTopPanelAnimation) == 0xD5, "WWWinData::HasTopPanelAnimation offset mismatch");
static_assert(offsetof(WWWinData, HasButtonAnimation) == 0xD6, "WWWinData::HasButtonAnimation offset mismatch");
static_assert(offsetof(WWWinData, HasMainScreenAnimation) == 0xD7, "WWWinData::HasMainScreenAnimation offset mismatch");
static_assert(offsetof(WWWinData, FlagD8) == 0xD8, "WWWinData::FlagD8 offset mismatch");

enum WWControlMessage : UINT
{
	WW_GETITEMDATA = 0x199,
	WW_SETITEMDATA = 0x19A,
	WW_SLIDER_GETPOS = 0x400,
	WW_PROGRESS_SETRANGE = 0x401,
	WW_PROGRESS_SETPOS = 0x402,
	WW_INPUT_GETKEY = 0x402,
	WW_SLIDER_SETPOS = 0x405,
	WW_SLIDER_SETRANGE = 0x406,
	WW_INITDIALOG = 0x497,
	WW_SETCOLOR = 0x498,
	WW_SETUNKNOWNPROP24 = 0x49A,
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

	using HwndProcDict = Dictionary<HWND, WNDPROC>;
	struct MsgInProcessGuard
	{
		HWND Hwnd;
		bool InProcess;
	};
	using MsgInProcessDict = Dictionary<UINT, MsgInProcessGuard>;
	using HwndWinDataDict = Dictionary<HWND, WWWinData>;

	DEFINE_REFERENCE(HwndProcDict, DialogProcs, 0xAC1B48); // Windows control's default window procedures 
	DEFINE_REFERENCE(HwndProcDict, SubclassProcs, 0xAC18C0); // Custom subclass procedures for owner-draw controls, 
	DEFINE_REFERENCE(MsgInProcessDict, MessageProcessedGuard, 0xAC18C0); // generic OwnerDraw::WindowProc preventing a message being processed multiple times
	DEFINE_REFERENCE(HwndWinDataDict, Dialogs, 0xAC1B00); // Primary owner-draw dialog/control table keyed by HWND.
	DEFINE_REFERENCE(HwndWinDataDict, WinData, 0xAC1B00); // Backward-compatible alias for Dialogs.

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
	// WWControlType::ColorTextInput
	DEFINE_REFERENCE(WNDPROC, ColorTextInputHandler, 0x612A60);

	// Westwood Registered extra handlers
	// ComboDropWin
	DEFINE_REFERENCE(WNDPROC, ComboDropWindowHandler, 0x60D540);
	// NewEdit uses DefWindowProcA here, doesnt matter cause OwnerDraw above did it
	DEFINE_REFERENCE(WNDPROC, NewEditDefaultHandler, 0x60D520);

	DEFINE_REFERENCE(WNDPROC, DefaultHandler, 0x610CA0); // Generic handler which call the handles above

	// Get rectangle relative to game main window's client area
	static int __fastcall GetRectangle(HWND hWnd, LPRECT lpRect) { JMP_STD(0x775690); }

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
	static void __fastcall Paint(HWND hWnd) { JMP_STD(0x621E90); }
	static const char* __fastcall GetTooltipStringLabel(HWND dialogHwnd, HWND controlHwnd) { JMP_STD(0x6040B0); }
	static void __fastcall DrawCampaignMenuTransition(HWND dialogHwnd, bool isOpening) { JMP_STD(0x6071E0); }
};

namespace SessionIpb
{
	inline void __fastcall RegisterHwnd(HWND hWnd) { JMP_STD(0x53E3C0); }
	inline void __fastcall UnregisterHwnd(HWND hWnd) { JMP_STD(0x53E420); }
}
