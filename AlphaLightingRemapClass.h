#pragma once

#include <YRPP.h>
#include <Helpers/CompileTime.h>

class AlphaLightingRemapClass
{
public:
	constexpr static reference<DynamicVectorClass<AlphaLightingRemapClass*>, 0x88A080> const Array{};

	// Notice:
	// When a ConvertClass is constructed by the game, it will generate [IntensityCount] color
	// tables from dark to bright. Each of them just changes the intensity of the source palette.
	//
	// If we have a point, whose value in ABuffer is A
	static AlphaLightingRemapClass* FindOrAllocate(int intensityCount)
	{
		JMP_STD(0x420140);
	}

	static void Release(AlphaLightingRemapClass* pItem)
	{
		JMP_STD(0x420270);
	}

	explicit AlphaLightingRemapClass(int intensityCount) noexcept
	{
		JMP_THIS(0x4202F0);
	}

	union
	{
		// Intensity - AlphaValue
		WORD Table[256][256];
		WORD Array[65536];
	};
	int IntensityCount;
	int RefCount;
};
