#pragma once
#include <Helpers/CompileTime.h>
/*
These globals are so important and fundamental that no other files should be
included for them to be available.
*/
namespace Unsorted
{
	static constexpr reference<int, 0xA8ED84> const CurrentFrame { };

	// The length of a cell in its isometric projection
	// If an object's Height is above this value it's considered as in-air
	constexpr int CellHeight = 208;
	// Leptons of a cell's diagonal /2 /sin(60deg)
	// LeptonsPerCell *sqrt(2) /2 */ (sqrt(3)/2)
	// 256 * sqrt(2/3)

	// The height in the middle of a cell, which is therefore CellHeight/2
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
}
