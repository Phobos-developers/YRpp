#pragma once

/*
These globals are so important and fundamental that no other files should be
included for them to be available.
*/
namespace Unsorted
{
	static const int& CurrentFrame = *reinterpret_cast<int*>(0xA8ED84);

	// The length of a cell in isometric projection
	// If an object's Height is above this value it's considered as in-air
	constexpr int CellHeight = 208;
	// Leptons of a cell's diagonal /2 /sin(60deg)
	// LeptonsPerCell *sqrt(2) /2 */ (sqrt(3)/2)
	// 256 * sqrt(2/3) = 209
	// with some precision loss

	// The height in the middle of a cell, which is therefore CellHeight/2
	constexpr int LevelHeight = 104;

	// Leptons per cell.
	constexpr int LeptonsPerCell = 256;

	// Cell width in pixels.
	constexpr int CellWidthInPixels = 60;

	// Cell height in pixels.
	constexpr int CellHeightInPixels = 30;
}
