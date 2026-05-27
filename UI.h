#pragma once

#include <windows.h>
#include <GeneralDefinitions.h>
#include <Unsorted.h>

class UI {
public:
	typedef BOOL (CALLBACK *Callback)(HWND, UINT, WPARAM, LPARAM);

	static HGLOBAL __fastcall GetResource(LPCTSTR lpName, LPCTSTR lpType) JMP_STD(0x4A3B40)
	static void RegisterComboDropAndNewEditClasses() JMP_STD(0x60D450)
	static BOOL __fastcall StandardWndProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) JMP_STD(0x622B50)
	static HWND __fastcall BeginDialog(LPCTSTR lpName, Callback windProc, DWORD dwUnk) JMP_STD(0x622650)
	static void __fastcall EndDialog(HWND hDlg) JMP_STD(0x622720)
	static bool Updated() JMP_STD(0x623120)
	static void __fastcall FocusOnWindow(HWND hWnd) JMP_STD(0x622800)
	static void __fastcall RemoveModelessDialog(HWND hWnd) JMP_STD(0x5D4ED0)
	static void __fastcall CenterWindow(HWND hWnd) JMP_STD(0x777060)
	static void __fastcall RegisterWindow(HWND hWnd, LPARAM msg) JMP_STD(0x622820)
	static void __fastcall GetKeyboardKeyString(unsigned short key, wchar_t* buffer) JMP_STD(0x61EF70)
};
