#pragma once

#include <YRPP.h>

class DSurface;
class INIClass;

class PreviewClass
{
public:

	PreviewClass() JMP_THIS(0x6406E0);
	~PreviewClass() JMP_THIS(0x6406F0);

	void DrawStartPoints(HWND hWnd) JMP_THIS(0x640710);
	bool DrawMap(DSurface& surface) JMP_THIS(0x640A40);
	void GeneratePreviewImage() JMP_THIS(0x641140);
	bool WritePreviewPack(INIClass& ini) const JMP_THIS(0x6418B0);
	bool ReadPreviewPack(INIClass& ini) JMP_THIS(0x641B00);
	bool ReadPCXPreview(const char* lpFile) JMP_THIS(0x641DB0);
	bool ReadPreview(const char* lpFile) JMP_THIS(0x641EE0); // Stupid WestWood Optimization Here
	void* CreatePalettedPreview(int nResolution, int& BytesWritten) JMP_THIS(0x642130);
	void CreatePreviewSurface(void* pData) JMP_THIS(0x6425F0);

	DSurface* ImageSurface;
};