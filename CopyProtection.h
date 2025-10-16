#pragma once
#include <GeneralDefinitions.h>

namespace CopyProtection
{
	/*
	Shared Memory for Copy Protection Interprocess.
	*/
	DEFINE_REFERENCE(char*, _mProtectedData, 0x89F75C);

	bool IsLauncherRunning() JMP_STD(0x49F5C0);

	bool NotifyLauncher() JMP_STD(0x49F620);

	bool CheckVersion() JMP_STD(0x49F920);

	bool CheckProtectedData() JMP_STD(0x49F7A0);

	void __fastcall DispatchLauncherMessage(MSG* pMsg) JMP_STD(0x49F740);

	LSTATUS ShutDown() JMP_STD(0x49F8B0);
}