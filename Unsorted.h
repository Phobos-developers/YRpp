#pragma once

#include <ArrayClasses.h>
#include <GeneralDefinitions.h>
#include <CCFileClass.h>
#include <Helpers/CompileTime.h>

struct TacticalSelectableStruct;
class SideClass;
class ObjectClass;

// things that I can't put into nice meaningful classes
class Game
{
public:
	// the magic checksum for version validation - linked in StaticInits
	static constexpr reference<DWORD, 0x83D560u> const Savegame_Magic {};

	static constexpr reference<DynamicVectorClass<ULONG>, 0xB0BC88u> const COMClasses {};

	static constexpr reference<HWND, 0xB73550u> const hWnd {};
	static constexpr reference<HINSTANCE, 0xB732F0u> const hInstance {};

	static constexpr reference<bool, 0x887418u> const bVPLRead {};
	static constexpr reference<bool, 0x840A6Cu> const bVideoBackBuffer {};
	static constexpr reference<bool, 0xA8EB96u> const bAllowVRAMSidebar {};

	static constexpr reference<RecordFlag, 0xA8D5F8u> const RecordingFlag {};
	static constexpr reference<CCFileClass, 0xA8D58Cu> const RecordFile {};

	static constexpr reference<bool, 0x822CF1u> const bDrawShadow {};
	static constexpr reference<bool, 0x8A0DEFu> const bAllowDirect3D {};
	static constexpr reference<bool, 0x8A0DF0u> const bDirect3DIsUseable {};

	static constexpr reference<bool, 0xA8E9A0u> const IsActive {};
	static constexpr reference<bool, 0xA8ED80u> const IsFocused {};
	static constexpr reference<int, 0xA8EDA0u> const SpecialDialog {};
	static constexpr reference<bool, 0xAC48D4> const PCXInitialized {};

	static constexpr reference<int, 0xA8ED94u> const Seed {};
	static constexpr reference<int, 0x822CF4u> const TechLevel {};
	static constexpr reference<int, 0xA8B54Cu> const PlayerCount {};
	static constexpr reference<int, 0xA8B394u> const PlayerColor {};
	static constexpr reference<bool, 0xAC10C8u> const ObserverMode {};
	static constexpr reference<char, 0xA8B8E0u> const ScenarioName {};
	static constexpr reference<bool, 0xA8F7ACu> const DontSetExceptionHandler {};
	static constexpr reference<bool, 0xB04880u> const EnableMPSyncDebug {};

	static constexpr reference<Vector3D<float>, 0x887470> const VoxelLightSource { };
	static constexpr reference<Vector3D<float>, 0x887420> const VoxelShadowLightSource { };

	static struct Network
	{
	public:
		static constexpr reference<int, 0xB779C4u> const Tournament {};
		static constexpr reference<DWORD, 0xB779D4u> const WOLGameID {};
		static constexpr reference<time_t, 0xB77788u> const PlanetWestwoodStartTime {};
		static constexpr reference<int, 0xB73814u> const GameStockKeepingUnit {};
		static constexpr reference<int, 0xA8B24Cu> const ProtocolVersion {};
		static constexpr reference<int, 0xA8B554u> const FrameSendRate {};
		static constexpr reference<int, 0x83737Cu> const ReconnectTimeout {};
		static constexpr reference<int, 0xA8B550u> const MaxAhead {};
		static constexpr reference<int, 0xA8B568u> const MaxMaxAhead {};
		static constexpr reference<int, 0xA8DB9Cu> const LatencyFudge {};
		static constexpr reference<int, 0xA8B558u> const RequestedFPS {};

		static bool Init()
		{ JMP_STD(0x5DA6C0); }
	} Network;

	// the game's own rounding function
	// infamous for true'ing (F2I(-5.00) == -4.00)
	static __int64 F2I64(double val)
	{
#ifdef _MSVC
		double something = val;
		__asm { fld something };
		CALL(0x7C5F00);
#endif
	}

	// the game's own rounding function
	// infamous for true'ing (F2I(-5.00) == -4.00)
	static int F2I(double val)
	{
		return static_cast<int>(F2I64(val));
	}

	[[noreturn]] static void RaiseError(HRESULT err)
	{ JMP_STD(0x7DC720); }

	// actually is SessionClass::Callback
	static void SetProgress(int progress)
	{ SET_REG32(ECX, 0xA8B238); JMP_STD(0x69AE90); }

	static void CallBack()
	{ JMP_STD(0x48D080); }

	static int __fastcall GetResource(int ID, int Type)
	{ JMP_STD(0x4A3B40); }

	static void __fastcall CenterWindowIn(HWND Child, HWND Parent)
	{ JMP_STD(0x777080); }

	static void __fastcall sub_53E420(HWND hWindow)
	{ JMP_STD(0x53E420); }

	static void __fastcall sub_53E3C0(HWND hWindow)
	{ JMP_STD(0x53E3C0); }

	static void __stdcall OnWindowMoving(tagRECT* Rect)
	{ JMP_STD(0x776D80); }

	static void __stdcall PlanningManager_WM_RBUTTONUP_63AB00(Point2D XY)
	{ JMP_STD(0x63AB00); }

	static HRESULT __fastcall Save_Sides(LPSTREAM pStm, DynamicVectorClass<SideClass*>* pVector)
	{ JMP_STD(0x6805F0); }

	static void StreamerThreadFlush()
	{ JMP_STD(0x53E6B0); }

	static void __fastcall UICommands_TypeSelect_7327D0(const char* iniName)
	{ JMP_STD(0x7327D0); }

	static bool IsTypeSelecting()
	{ JMP_STD(0x732D00); }

	static double GetFloaterGravity()
	{ JMP_STD(0x48ACF0); }

	static void __fastcall KeyboardProcess(DWORD& input)
	{ JMP_STD(0x55DEE0); }

	static LARGE_INTEGER __fastcall AudioGetTime()
	{ JMP_STD(0x4093B0); }

	static void InitRandom()
	{ JMP_STD(0x52FC20); }

	static void ShowSpecialDialog()
	{ JMP_STD(0x48C8B0); }

	static void __fastcall DestroyVoxelCaches()
	{ JMP_STD(0x755C50); }

	static void InitUIStuff()
	{
		CALL(0x600560); // InitCommonDialogStuff()

		if (!PCXInitialized)
		{
			PCXInitialized = true;
			CALL(0x61F190); // InitUIColorShifts()
			CALL(0x61F210); // LoadPCXFiles()
		}
	}

	static void __fastcall DrawRadialIndicator(bool drawLine, bool adjustColor, const CoordStruct pCoord, ColorStruct color, float lineMultiplier, bool unknown1, bool unknown2)
	{ JMP_STD(0x456980); }

	static void __fastcall PlayMovie(
		const char* movieName,
		int queue_theme = -1,
		char use_hidden_surface1 = -1,
		char stretch_movie = -1,
		char use_hidden_surface2 = -1,
		char set_state_1 = -1
	)
	{
		JMP_STD(0x5BED40);
	}

	static void __fastcall ComputeFrameCRC()
	{ JMP_STD(0x64DAB0); }

	static void __fastcall LogFrameCRC(int frameIndex)
	{ JMP_STD(0x650A90); }
};

// this fake class contains the IIDs used by the game
// no comments because the IIDs suck
class IIDs
{
public:
	static constexpr reference<IID const, 0x7F7C90u> const IUnknown {};
	static constexpr reference<IID const, 0x7F7C80u> const IPersistStream {};
	static constexpr reference<IID const, 0x7F7C70u> const IPersist {};
	static constexpr reference<IID const, 0x7E9AE0u> const IRTTITypeInfo {};
	static constexpr reference<IID const, 0x7EA768u> const IHouse {};
	static constexpr reference<IID const, 0x7E9B00u> const IPublicHouse {};
	static constexpr reference<IID const, 0x7F7CB0u> const IEnumConnections {};
	static constexpr reference<IID const, 0x7F7CC0u> const IConnectionPoint {};
	static constexpr reference<IID const, 0x7F7CD0u> const IConnectionPointContainer {};
	static constexpr reference<IID const, 0x7F7CE0u> const IEnumConnectionPoints {};
	static constexpr reference<IID const, 0x7E36C0u> const IApplication {};
	static constexpr reference<IID const, 0x7EA6E8u> const IGameMap {};
	static constexpr reference<IID const, 0x7ED358u> const ILocomotion {};
	static constexpr reference<IID const, 0x7E9B10u> const IPiggyback {};
	static constexpr reference<IID const, 0x7E9B40u> const IFlyControl {};
	static constexpr reference<IID const, 0x7E9B20u> const ISwizzle {};
};

// this class links to functions gamemd imports
// to avoid having to link to their DLLs ourselves
class Imports
{
#define ALIAS(Obj, Addr)\
static constexpr reference<FP_##Obj const, Addr> const Obj{}

public:
	// OleLoadFromStream
	typedef HRESULT(__stdcall* FP_OleSaveToStream)(LPPERSISTSTREAM pPStm, LPSTREAM pStm);
	ALIAS(OleSaveToStream, 0x7E15F4);

	typedef HRESULT(__stdcall* FP_OleLoadFromStream)(LPSTREAM pStm, const IID* const iidInterface, LPVOID* ppvObj);
	ALIAS(OleLoadFromStream, 0x7E15F8);

	typedef HRESULT(__stdcall* FP_CoRegisterClassObject)(const IID& rclsid, LPUNKNOWN pUnk, DWORD dwClsContext, DWORD flags, LPDWORD lpdwRegister);
	ALIAS(CoRegisterClassObject, 0x7E15D8);

	typedef HRESULT(__stdcall* FP_CoRevokeClassObject)(DWORD dwRegister);
	ALIAS(CoRevokeClassObject, 0x7E15CC);

	typedef DWORD(*FP_TimeGetTime)();
	ALIAS(TimeGetTime, 0x7E1530);

	/* user32.dll */
	typedef LRESULT(__stdcall* FP_DefWindowProcA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	ALIAS(DefWindowProcA, 0x7E1394);

	typedef BOOL(__stdcall* FP_MoveWindow)(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint);
	ALIAS(MoveWindow, 0x7E1398);

	typedef BOOL(__stdcall* FP_GetUpdateRect)(HWND hWnd, LPRECT lpRect, BOOL bErase);
	ALIAS(GetUpdateRect, 0x7E139C);

	typedef HWND(*FP_GetFocus)(void);
	ALIAS(GetFocus, 0x7E13A0);

	typedef HDC(__stdcall* FP_GetDC)(HWND hWnd);
	ALIAS(GetDC, 0x7E13A4);

	typedef SHORT(__stdcall* FP_GetKeyState)(int nVirtKey);
	ALIAS(GetKeyState, 0x7E13A8);

	typedef HWND(*FP_GetActiveWindow)(void);
	ALIAS(GetActiveWindow, 0x7E13AC);

	typedef HWND(*FP_GetCapture)(void);
	ALIAS(GetCapture, 0x7E13B0);

	typedef int(__stdcall* FP_GetDlgCtrlID)(HWND hWnd);
	ALIAS(GetDlgCtrlID, 0x7E13B4);

	typedef HWND(__stdcall* FP_ChildWindowFromPointEx)(HWND, POINT, UINT);
	ALIAS(ChildWindowFromPointEx, 0x7E13B8);

	typedef BOOL(__stdcall* FP_GetWindowRect)(HWND hWnd, LPRECT lpRect);
	ALIAS(GetWindowRect, 0x7E13BC);

	typedef BOOL(__stdcall* FP_GetCursorPos)(LPPOINT lpPoint);
	ALIAS(GetCursorPos, 0x7E13C0);

	typedef BOOL(__stdcall* FP_CloseWindow)(HWND hWnd);
	ALIAS(CloseWindow, 0x7E13C4);

	typedef BOOL(__stdcall* FP_EndDialog)(HWND hDlg, int nResult);
	ALIAS(EndDialog, 0x7E13C8);

	typedef HWND(__stdcall* FP_SetFocus)(HWND hWnd);
	ALIAS(SetFocus, 0x7E13CC);

	typedef BOOL(__stdcall* FP_SetDlgItemTextA)(HWND hDlg, int nIDDlgItem, LPCSTR lpString);
	ALIAS(SetDlgItemTextA, 0x7E13D0);

	typedef int(__stdcall* FP_DialogBoxParamA)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
	ALIAS(DialogBoxParamA, 0x7E13D4);

#ifdef _MSVC
	typedef int(__stdcall* FP_DialogBoxIndirectParamA)(HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
	ALIAS(DialogBoxIndirectParamA, 0x7E13D8);
#endif

	typedef int(__stdcall* FP_ShowCursor)(BOOL bShow);
	ALIAS(ShowCursor, 0x7E13DC);

	typedef SHORT(__stdcall* FP_GetAsyncKeyState)(int vKey);
	ALIAS(GetAsyncKeyState, 0x7E13E0);

	typedef int(__stdcall* FP_ToAscii)(UINT uVirtKey, UINT uScanCode, PBYTE lpKeyState, LPWORD lpChar, UINT uFlags);
	ALIAS(ToAscii, 0x7E13E4);

	typedef UINT(__stdcall* FP_MapVirtualKeyA)(UINT uCode, UINT uMapType);
	ALIAS(MapVirtualKeyA, 0x7E13E8);

	typedef int(__stdcall* FP_GetSystemMetrics)(int nIndex);
	ALIAS(GetSystemMetrics, 0x7E13EC);

	typedef BOOL(__stdcall* FP_SetWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);
	ALIAS(SetWindowPos, 0x7E13F0);

	typedef BOOL(__stdcall* FP_DestroyWindow)(HWND hWnd);
	ALIAS(DestroyWindow, 0x7E13F4);

	typedef BOOL(*FP_ReleaseCapture)(void);
	ALIAS(ReleaseCapture, 0x7E13F8);

	typedef HWND(__stdcall* FP_SetCapture)(HWND hWnd);
	ALIAS(SetCapture, 0x7E13FC);

	typedef BOOL(__stdcall* FP_AdjustWindowRectEx)(LPRECT lpRect, DWORD dwStyle, BOOL bMenu, DWORD dwExStyle);
	ALIAS(AdjustWindowRectEx, 0x7E1400);

	typedef HMENU(__stdcall* FP_GetMenu)(HWND hWnd);
	ALIAS(GetMenu, 0x7E1404);

	typedef BOOL(__stdcall* FP_AdjustWindowRect)(LPRECT lpRect, DWORD dwStyle, BOOL bMenu);
	ALIAS(AdjustWindowRect, 0x7E1408);

	typedef DWORD(__stdcall* FP_GetSysColor)(int nIndex);
	ALIAS(GetSysColor, 0x7E140C);

	typedef UINT(__stdcall* FP_IsDlgButtonChecked)(HWND hDlg, int nIDButton);
	ALIAS(IsDlgButtonChecked, 0x7E1410);

	typedef BOOL(__stdcall* FP_CheckDlgButton)(HWND hDlg, int nIDButton, UINT uCheck);
	ALIAS(CheckDlgButton, 0x7E1414);

	typedef DWORD(__stdcall* FP_WaitForInputIdle)(HANDLE hProcess, DWORD dwMilliseconds);
	ALIAS(WaitForInputIdle, 0x7E1418);

	typedef HWND(__stdcall* FP_GetTopWindow)(HWND hWnd);
	ALIAS(GetTopWindow, 0x7E141C);

	typedef HWND(*FP_GetForegroundWindow)(void);
	ALIAS(GetForegroundWindow, 0x7E1420);

	typedef HICON(__stdcall* FP_LoadIconA)(HINSTANCE hInstance, LPCSTR lpIconName);
	ALIAS(LoadIconA, 0x7E1424);

	typedef HWND(__stdcall* FP_SetActiveWindow)(HWND hWnd);
	ALIAS(SetActiveWindow, 0x7E1428);

	typedef BOOL(__stdcall* FP_RedrawWindow)(HWND hWnd, const RECT* lprcUpdate, HRGN hrgnUpdate, UINT flags);
	ALIAS(RedrawWindow, 0x7E142C);

	typedef DWORD(__stdcall* FP_GetWindowContextHelpId)(HWND);
	ALIAS(GetWindowContextHelpId, 0x7E1430);

	typedef BOOL(__stdcall* FP_WinHelpA)(HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, DWORD dwData);
	ALIAS(WinHelpA, 0x7E1434);

	typedef HWND(__stdcall* FP_ChildWindowFromPoint)(HWND hWndParent, POINT Point);
	ALIAS(ChildWindowFromPoint, 0x7E1438);

	typedef HCURSOR(__stdcall* FP_LoadCursorA)(HINSTANCE hInstance, LPCSTR lpCursorName);
	ALIAS(LoadCursorA, 0x7E143C);

	typedef HCURSOR(__stdcall* FP_SetCursor)(HCURSOR hCursor);
	ALIAS(SetCursor, 0x7E1440);

	typedef void(__stdcall* FP_PostQuitMessage)(int nExitCode);
	ALIAS(PostQuitMessage, 0x7E1444);

	typedef HWND(__stdcall* FP_FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName);
	ALIAS(FindWindowA, 0x7E1448);

	typedef BOOL(__stdcall* FP_SetCursorPos)(int X, int Y);
	ALIAS(SetCursorPos, 0x7E144C);

#ifdef _MSVC
	typedef HWND(__stdcall* FP_CreateDialogIndirectParamA)(HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
	ALIAS(CreateDialogIndirectParamA, 0x7E1450);
#endif

	typedef int(__stdcall* FP_GetKeyNameTextA)(LONG lParam, LPSTR lpString, int nSize);
	ALIAS(GetKeyNameTextA, 0x7E1454);

	typedef BOOL(__stdcall* FP_ScreenToClient)(HWND hWnd, LPPOINT lpPoint);
	ALIAS(ScreenToClient, 0x7E1458);

	typedef BOOL(__stdcall* FP_LockWindowUpdate)(HWND hWndLock);
	ALIAS(LockWindowUpdate, 0x7E145C);

	typedef int(__stdcall* FP_MessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);
	ALIAS(MessageBoxA, 0x7E1460);

	typedef int(__stdcall* FP_ReleaseDC)(HWND hWnd, HDC hDC);
	ALIAS(ReleaseDC, 0x7E1464);

	typedef HWND(__stdcall* FP_WindowFromPoint)(POINT Point);
	ALIAS(WindowFromPoint, 0x7E1468);

	typedef BOOL(__stdcall* FP_UpdateWindow)(HWND hWnd);
	ALIAS(UpdateWindow, 0x7E146C);

	typedef LONG(__stdcall* FP_SetWindowLongA)(HWND hWnd, int nIndex, LONG dwNewLong);
	ALIAS(SetWindowLongA, 0x7E1470);

	typedef LONG(__stdcall* FP_GetWindowLongA)(HWND hWnd, int nIndex);
	ALIAS(GetWindowLongA, 0x7E1474);

	typedef BOOL(__stdcall* FP_ValidateRect)(HWND hWnd, const RECT* lpRect);
	ALIAS(ValidateRect, 0x7E1478);

	typedef BOOL(__stdcall* FP_IntersectRect)(LPRECT lprcDst, const RECT* lprcSrc1, const RECT* lprcSrc2);
	ALIAS(IntersectRect, 0x7E147C);

	typedef int(__stdcall* FP_MessageBoxIndirectA)(LPMSGBOXPARAMSA);
	ALIAS(MessageBoxIndirectA, 0x7E1480);

	typedef BOOL(__stdcall* FP_PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
	ALIAS(PeekMessageA, 0x7E1484);

	typedef LRESULT(__stdcall* FP_CallWindowProcA)(WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	ALIAS(CallWindowProcA, 0x7E1488);

	typedef BOOL(__stdcall* FP_KillTimer)(HWND hWnd, UINT uIDEvent);
	ALIAS(KillTimer, 0x7E148C);

	typedef LONG(__stdcall* FP_SendDlgItemMessageA)(HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam);
	ALIAS(SendDlgItemMessageA, 0x7E1490);

	typedef UINT(__stdcall* FP_SetTimer)(HWND hWnd, UINT nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc);
	ALIAS(SetTimer, 0x7E1494);

	typedef BOOL(__stdcall* FP_ShowWindow)(HWND hWnd, int nCmdShow);
	ALIAS(ShowWindow, 0x7E1498);

	typedef BOOL(__stdcall* FP_InvalidateRect)(HWND hWnd, const RECT* lpRect, BOOL bErase);
	ALIAS(InvalidateRect, 0x7E149C);

	typedef BOOL(__stdcall* FP_EnableWindow)(HWND hWnd, BOOL bEnable);
	ALIAS(EnableWindow, 0x7E14A0);

	typedef LRESULT(__stdcall* FP_SendMessageA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	ALIAS(SendMessageA, 0x7E14A4);

	typedef HWND(__stdcall* FP_GetDlgItem)(HWND hDlg, int nIDDlgItem);
	ALIAS(GetDlgItem, 0x7E14A8);

	typedef BOOL(__stdcall* FP_PostMessageA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	ALIAS(PostMessageA, 0x7E14AC);

	typedef int (*FP_wsprintfA)(LPSTR, LPCSTR, ...);
	ALIAS(wsprintfA, 0x7E14B0);

	typedef BOOL(__stdcall* FP_SetRect)(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom);
	ALIAS(SetRect, 0x7E14B4);

	typedef BOOL(__stdcall* FP_ClientToScreen)(HWND hWnd, LPPOINT lpPoint);
	ALIAS(ClientToScreen, 0x7E14B8);

	typedef BOOL(__stdcall* FP_TranslateMessage)(const MSG* lpMsg);
	ALIAS(TranslateMessage, 0x7E14BC);

	typedef LONG(__stdcall* FP_DispatchMessageA)(const MSG* lpMsg);
	ALIAS(DispatchMessageA, 0x7E14C0);

	typedef BOOL(__stdcall* FP_GetClientRect)(HWND hWnd, LPRECT lpRect);
	ALIAS(GetClientRect, 0x7E14C4);

	typedef HWND(__stdcall* FP_GetWindow)(HWND hWnd, UINT uCmd);
	ALIAS(GetWindow, 0x7E14C8);

	typedef BOOL(__stdcall* FP_BringWindowToTop)(HWND hWnd);
	ALIAS(BringWindowToTop, 0x7E14CC);

	typedef BOOL(__stdcall* FP_SetForegroundWindow)(HWND hWnd);
	ALIAS(SetForegroundWindow, 0x7E14D0);

	typedef HWND(__stdcall* FP_CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	ALIAS(CreateWindowExA, 0x7E14D4);

	typedef ATOM(__stdcall* FP_RegisterClassA)(const WNDCLASSA* lpWndClass);
	ALIAS(RegisterClassA, 0x7E14D8);

	typedef int(__stdcall* FP_GetClassNameA)(HWND hWnd, LPSTR lpClassName, int nMaxCount);
	ALIAS(GetClassNameA, 0x7E14DC);

	typedef BOOL(__stdcall* FP_IsWindowVisible)(HWND hWnd);
	ALIAS(IsWindowVisible, 0x7E14E0);

	typedef BOOL(__stdcall* FP_EnumChildWindows)(HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam);
	ALIAS(EnumChildWindows, 0x7E14E4);

	typedef BOOL(__stdcall* FP_IsWindowEnabled)(HWND hWnd);
	ALIAS(IsWindowEnabled, 0x7E14E8);

	typedef HWND(__stdcall* FP_GetParent)(HWND hWnd);
	ALIAS(GetParent, 0x7E14EC);

	typedef HWND(__stdcall* FP_GetNextDlgTabItem)(HWND hDlg, HWND hCtl, BOOL bPrevious);
	ALIAS(GetNextDlgTabItem, 0x7E14F0);

	typedef BOOL(__stdcall* FP_IsDialogMessageA)(HWND hDlg, LPMSG lpMsg);
	ALIAS(IsDialogMessageA, 0x7E14F4);

	typedef int(__stdcall* FP_TranslateAcceleratorA)(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg);
	ALIAS(TranslateAcceleratorA, 0x7E14F8);

	typedef BOOL(__stdcall* FP_CharToOemBuffA)(LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength);
	ALIAS(CharToOemBuffA, 0x7E14FC);

	typedef HDC(__stdcall* FP_BeginPaint)(HWND hWnd, LPPAINTSTRUCT lpPaint);
	ALIAS(BeginPaint, 0x7E1500);

	typedef BOOL(__stdcall* FP_EndPaint)(HWND hWnd, const PAINTSTRUCT* lpPaint);
	ALIAS(EndPaint, 0x7E1504);

	typedef HWND(__stdcall* FP_CreateDialogParamA)(HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam);
	ALIAS(CreateDialogParamA, 0x7E1508);

	typedef int(__stdcall* FP_GetWindowTextA)(HWND hWnd, LPSTR lpString, int nMaxCount);
	ALIAS(GetWindowTextA, 0x7E150C);

	typedef BOOL(__stdcall* FP_RegisterHotKey)(HWND hWnd, int id, UINT fsModifiers, UINT vk);
	ALIAS(RegisterHotKey, 0x7E1510);

	typedef LONG(__stdcall* FP_InterlockedIncrement)(void* lpAddend);
	ALIAS(InterlockedIncrement, 0x7E11C8);

	typedef LONG(__stdcall* FP_InterlockedDecrement)(void* lpAddend);
	ALIAS(InterlockedDecrement, 0x7E11CC);
#undef ALIAS
};

class MovieInfo
{
public:
	// technically, this is a DVC<const char*>
	// and string management is done manually
	static constexpr reference<DynamicVectorClass<MovieInfo>, 0xABF390u> const Array {};

	bool operator== (MovieInfo const& rhs) const
	{
		return !_strcmpi(this->Name, rhs.Name);
	}

	explicit MovieInfo(const char* fname)
		: Name(fname ? _strdup(fname) : nullptr)
	{ }

	MovieInfo() : Name(nullptr)
	{ }

	~MovieInfo()
	{
		if (this->Name)
		{
			free(const_cast<char*>(this->Name));
		}
	}

	const char* Name; // yes, only that
};

struct MovieUnlockableInfo
{
	static constexpr reference<MovieUnlockableInfo, 0x832C20u, 1u> const Common {};
	static constexpr reference<MovieUnlockableInfo, 0x832C30u, 8u> const Allied {};
	static constexpr reference<MovieUnlockableInfo, 0x832CA0u, 8u> const Soviet {};

	MovieUnlockableInfo() = default;

	explicit MovieUnlockableInfo(const char* pFilename, const char* pDescription = nullptr, int disk = 2)
		: Filename(pFilename), Description(pDescription), DiskRequired(disk)
	{ }

	const char* Filename { nullptr };
	const char* Description { nullptr };
	int DiskRequired { 2 };
};

namespace Unsorted
{
	// if != 0, EVA_SWxxxActivated is skipped
	static constexpr reference<int, 0xA8B538> MuteSWLaunches {};

	// skip unit selection and move command voices?
	static constexpr reference<bool, 0x822CF2> MoveFeedback {};

	static constexpr reference<byte, 0xA8ED6B> ArmageddonMode {};
	static constexpr constant_ptr<DynamicVectorClass<ObjectClass*>, 0x8A0360> ObjectsInLayers {};

	// checkbox states, afaik
	static constexpr reference<byte, 0xA8B258> Bases {};
	static constexpr reference<byte, 0xA8B260> BridgeDestruction {};
	static constexpr reference<byte, 0xA8B261> Crates {};
	static constexpr reference<byte, 0xA8B262> ShortGame {};
	static constexpr reference<byte, 0xA8B263> SWAllowed {};
	static constexpr reference<byte, 0xA8B26C> MultiEngineer {};
	static constexpr reference<byte, 0xA8B31C> AlliesAllowed {};
	static constexpr reference<byte, 0xA8B31D> HarvesterTruce {};
	static constexpr reference<byte, 0xA8B31E> CTF {};
	static constexpr reference<byte, 0xA8B31F> FOW {};
	static constexpr reference<byte, 0xA8B320> MCVRedeploy {};

	static constexpr reference<TacticalSelectableStruct, 0xB0CEC8, 500> TacticalSelectables {};
	static constexpr reference<bool, 0xB0FE65> TypeSelecting {};

	struct ColorPacker
	{
		int _R_SHL;
		int _R_SHR;
		int _B_SHL;
		int _B_SHR;
		int _G_SHL;
		int _G_SHR;
	};

	static constexpr constant_ptr<ColorPacker, 0x8A0DD0> ColorPackData {};

	static constexpr constant_ptr<CellStruct, 0xABD490> CellSpreadTable {};

	static constexpr reference<int, 0x8809A0> CurrentSWType {};

	static const int except_txt_length = 0xFFFF;
	static constexpr constant_ptr<char, 0x8A3A08> except_txt_content {};

	/*
	 * This thing is ridiculous
	 * all xxTypeClass::Create functions use it:

		// doing this makes no sense - it's just a wrapper around CTOR, which doesn't call any Mutex'd functions... but who cares
		InfantryTypeClass *foo = something;
		++SomeMutex;
		InfantryClass *obj = foo->CreateObject();
		--SomeMutex;

		// XXX do not do this if you aren't sure if the object can exist in this place
		// - this flag overrides any placement checks so you can put Terror Drones into trees and stuff
		++SomeMutex;
		obj->Unlimbo(blah);
		--SomeMutex;

		AI base node generation uses it:
		int level = SomeMutex;
		SomeMutex = 0;
		House->GenerateAIBuildList();
		SomeMutex = level;

		Building destruction uses it:
		if(!SomeMutex) {
			Building->ShutdownSensorArray();
			Building->ShutdownDisguiseSensor();
		}

		Building placement uses it:
		if(!SomeMutex) {
			UnitTypeClass *freebie = Building->Type->FreeUnit;
			if(freebie) {
				freebie->CreateObject(blah);
			}
		}

		Building state animations use it:
		if(SomeMutex) {
			// foreach attached anim
			// update anim state (normal | damaged | garrisoned) if necessary, play anim
		}

		building selling uses it:
		if(blah) {
			++SomeMutex;
			this->Type->UndeploysInto->CreateAtMapCoords(blah);
			--SomeMutex;
		}

		Robot Control Centers use it:
		if ( !SomeMutex ) {
			VoxClass::PlayFromName("EVA_RobotTanksOffline/BackOnline", -1, -1);
	}

	and so on...
	*/
	// Note: SomeMutex has been renamed to this because it reflects the usage better
	static constexpr reference<int, 0xA8E7AC> IKnowWhatImDoing {}; // h2ik
};

struct CheatData
{
	bool* Destination;
	const char* TriggerString;
	DWORD unknown1;
	DWORD unknown2;
};

// this holds four original cheats, keep that limit in mind
static constexpr reference<CheatData, 0x825C28, 4> OriginalCheats {};
