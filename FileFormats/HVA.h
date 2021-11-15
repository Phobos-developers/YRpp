#pragma once

// HVA file

class CCFileClass;
class Matrix3D;

class MotLib {
public:
	bool LoadedFailed;
	int LayerCount;
	int FrameCount;
	Matrix3D* Matrixes;

	MotLib(CCFileClass* Source)
	{
		JMP_THIS(0x5BD570);
	}

	~MotLib()
	{
		JMP_THIS(0x5BD5A0);
	}

	// 0 for valid, non 0 for invalid
	signed int ReadFile(CCFileClass* ccFile)
	{
		JMP_THIS(0x5BD5C0);
	}

	void Scale(float scale)
	{
		JMP_THIS(0x5BD730);
	}

};
