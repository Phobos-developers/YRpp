#pragma once
#include <GeneralDefinitions.h>

namespace System
{
	static inline const DWORD EntryPoint = 0x7CD80F;

	DEFINE_REFERENCE(WORD, SystemVersionLow, 0xB781CC);
	DEFINE_REFERENCE(WORD, SystemVersionHigh, 0xB781C8);

	DEFINE_REFERENCE(LPCSTR, CommandLine, 0xB78BA8);
	DEFINE_REFERENCE(LPCSTR, EnvironmentString, 0xB78228);
	DEFINE_REFERENCE(int, argc, 0xB781D8);
	DEFINE_REFERENCE(char**, argv, 0xB781DC);
	DEFINE_REFERENCE(char**, envp, 0xB781E4);

	using initterm_t = void (*)();
	static void __cdecl _initterm(initterm_t* First, initterm_t* Last) 
		JMP_STD(0x7CBED3);

	DEFINE_REFERENCE(initterm_t, SystemInitTermsBegin, 0x815DA8);
	DEFINE_REFERENCE(initterm_t, SystemInitTermsEnd, 0x815DBC);

	//GlobalConstructorsBegin~End : all constructors and destructor registers of GLOBAL objects
	DEFINE_REFERENCE(initterm_t, GlobalConstructorsBegin, 0x812000);
	DEFINE_REFERENCE(initterm_t, GlobalConstructorsEnd, 0x815DA4);

	static int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
		JMP_STD(0x6BB9A0);

	//NOTE : All used functions can be reached through either GlobalConstructors or WinMain
}

