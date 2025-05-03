#pragma once
#include <Helpers/CompileTime.h>
/*
These globals are so important and fundamental that no other files should be
included for them to be available.
*/
namespace Unsorted
{
	DEFINE_REFERENCE(int, CurrentFrame, 0xA8ED84)

	// The length of a cell in its isometric projection
	// If an object's Height is above this value it's considered as in-air
	constexpr int CellHeight = 208;
	// Leptons of a cell's diagonal /2 /sin(60deg)
	// LeptonsPerCell *sqrt(2) /2 */ (sqrt(3)/2)
	// 256 * sqrt(2/3)

	// The height in the middle of a cell, which is therefore CellHeight/2
	// see ABC5E8, AC13C8
	constexpr int LevelHeight = 104;
	// The game actually calculated this one and multiply it by 2 for CellHeight
	// cot(deg2rad(60)) * leptonsOfCellDiagonal /2
	// tan(pi/2-pi/3) * sqrt(2 * 256^2) * 0.5
	// sqrt(3)/3 * 362.03 *0.5

	// Leptons per cell.
	constexpr int LeptonsPerCell = 256;

	// Cell width in pixels.
	constexpr int CellWidthInPixels = 60;

	// Cell height in pixels.
	constexpr int CellHeightInPixels = 30;

	// Sections in health bars.
	constexpr int HealthBarSectionsInfantry = 8;

	// Sections in health bars.
	constexpr int HealthBarSectionsOther = 17;

	// Health bars vertical offset.
	constexpr int HealthBarYOffsetInfantry = 25;

	// Health bars vertical offset.
	constexpr int HealthBarYOffsetOther = 26;
}
