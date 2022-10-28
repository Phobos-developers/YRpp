/*
	Drawing related static class.
	This provides access to the game's Surfaces, color value conversion
	and text aligning helpers.
*/

#pragma once

#include <ColorScheme.h>
#include <GeneralDefinitions.h>
#include <Helpers/CompileTime.h>
#include <Surface.h>

#pragma pack(push, 1)
class RGBClass
{
public:
	static constexpr reference<RGBClass, 0xA80220> White {};
	static constexpr reference<int, 0x8A0DD0> const RedShiftLeft {};
	static constexpr reference<int, 0x8A0DD4> const RedShiftRight {};
	static constexpr reference<int, 0x8A0DE0> const GreenShiftLeft {};
	static constexpr reference<int, 0x8A0DE4> const GreenShiftRight {};
	static constexpr reference<int, 0x8A0DD8> const BlueShiftLeft {};
	static constexpr reference<int, 0x8A0DDC> const BlueShiftRight {};

	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;

	RGBClass()
	{
		Red = Green = Blue = 0;
	}

	RGBClass(int rgb, bool wordcolor = false)
	{
		if (!wordcolor)
		{
			Red = GetRValue(rgb);
			Green = GetGValue(rgb);
			Blue = GetBValue(rgb);
		}
		else
		{
			Red = (unsigned char)((unsigned short)rgb >> RedShiftLeft) << RedShiftRight;
			Green = (unsigned char)((unsigned short)rgb>> GreenShiftLeft) << GreenShiftRight;
			Blue = (unsigned char)((unsigned short)rgb>> BlueShiftLeft) << BlueShiftRight;
		}
	}

	void Adjust(int ratio, RGBClass const& rgb)
	{
		ratio &= 0x00FF;

		int value = (int)rgb.Red - (int)Red;
		Red = static_cast<unsigned char>((int)Red + (value * ratio) / 256);

		value = (int)rgb.Green - (int)Green;
		Green = static_cast<unsigned char>((int)Green + (value * ratio) / 256);

		value = (int)rgb.Blue - (int)Blue;
		Blue = static_cast<unsigned char>((int)Blue + (value * ratio) / 256);
	}

	int Difference(RGBClass const& rgb) const
	{
		int r = (int)Red - (int)rgb.Red;
		if (r < 0) r = -r;

		int g = (int)Green - (int)rgb.Green;
		if (g < 0) g = -g;

		int b = (int)Blue - (int)rgb.Blue;
		if (b < 0) b = -b;

		return(r * r + g * g + b * b);
	}

	int ToInt()
	{
		return
			(Red >> RedShiftRight << RedShiftLeft) |
			(Green >> GreenShiftRight << GreenShiftLeft) |
			(Blue >> BlueShiftRight << BlueShiftLeft) ;
	}
};
#pragma pack(pop)

struct DirtyAreaStruct
{
	RectangleStruct Rect;
	bool alphabool10;

	bool operator==(const DirtyAreaStruct& another) const
	{
		return
			Rect.X == another.Rect.X &&
			Rect.Y == another.Rect.Y &&
			Rect.Width == another.Rect.Width &&
			Rect.Height == another.Rect.Height &&
			alphabool10 == another.alphabool10;
	};
};

class Drawing
{
public:
	constexpr static reference<DynamicVectorClass<DirtyAreaStruct>, 0xB0CE78> DirtyAreas {};
	static constexpr reference<ColorStruct, 0xB0FA1C> const TooltipColor {};
	static constexpr int RedShiftLeft = 11;
	static constexpr int RedShiftRight = 3;
	static constexpr int GreenShiftLeft = 5;
	static constexpr int GreenShiftRight = 2;
	static constexpr int BlueShiftLeft = 0;
	static constexpr int BlueShiftRight = 3;

	//TextBox dimensions for tooltip-style boxes
	static RectangleStruct* __fastcall GetTextDimensions(
		RectangleStruct* pOutBuffer, wchar_t const* pText, Point2D location,
		WORD flags, int marginX = 0, int marginY = 0)
			{ JMP_STD(0x4A59E0); }

	static RectangleStruct __fastcall GetTextDimensions(
		wchar_t const* pText, Point2D location, WORD flags, int marginX = 0,
		int marginY = 0)
	{
		RectangleStruct buffer;
		GetTextDimensions(&buffer, pText, location, flags, marginX, marginY);
		return buffer;
	}

	// Rectangles
	static RectangleStruct* __fastcall Intersect(
		RectangleStruct* pOutBuffer, RectangleStruct const& rect1,
		RectangleStruct const& rect2, int* delta_left = nullptr,
		int* delta_top = nullptr)
			{ JMP_STD(0x421B60); }

	static RectangleStruct __fastcall Intersect(
		RectangleStruct const& rect1, RectangleStruct const& rect2,
		int* delta_left = nullptr, int* delta_top = nullptr)
	{
		RectangleStruct buffer;
		Intersect(&buffer, rect1, rect2, delta_left, delta_top);
		return buffer;
	}

	// Rect1 will be changed, notice that - secsome
	static RectangleStruct* __fastcall Union(
		RectangleStruct* pOutBuffer,
		const RectangleStruct& rect1,
		const RectangleStruct& rect2)
			{ JMP_STD(0x487F40); }

	// Rect1 will be changed, notice that - secsome
	static RectangleStruct __fastcall Union(
		const RectangleStruct& rect1,
		const RectangleStruct& rect2)
	{
		RectangleStruct buffer;
		Union(&buffer, rect1, rect2);
		return buffer;
	}

	/*
	static int __fastcall RGB_To_Int(int red, int green, int blue)
	{ JMP_STD(0x4355D0); }
	*/
	constexpr static int RGB_To_Int(int red, int green, int blue)
	{
		return (red >> RedShiftRight << RedShiftLeft) | (green >> GreenShiftRight << GreenShiftLeft) | (blue >> BlueShiftRight << BlueShiftLeft);
	}

	static int RGB_To_Int(const ColorStruct& Color)
	{
		return RGB_To_Int(Color.R, Color.G, Color.B);
	}

	static int RGB_To_Int(ColorStruct&& Color)
	{
		return RGB_To_Int(Color.R, Color.G, Color.B);
	}

	static void Int_To_RGB(int color, BYTE& red, BYTE& green, BYTE& blue)
	{
		red = static_cast<BYTE>(color >> RedShiftLeft << RedShiftRight);
		green = static_cast<BYTE>(color >> GreenShiftLeft << GreenShiftRight);
		blue = static_cast<BYTE>(color >> BlueShiftLeft << BlueShiftRight);
	}

	static void Int_To_RGB(int color, ColorStruct& buffer)
	{
		Int_To_RGB(color, buffer.R, buffer.G, buffer.B);
	}

	static ColorStruct Int_To_RGB(int color)
	{
		ColorStruct ret;
		Int_To_RGB(color, ret);
		return ret;
	}
};

//A few preset 16bit colors.
#define		COLOR_BLACK  0x0000
#define		COLOR_WHITE  0xFFFF

#define		COLOR_RED    0xF800
#define		COLOR_GREEN  0x07E0
#define		COLOR_BLUE   0x001F

#define		COLOR_YELLOW (COLOR_RED | COLOR_GREEN)
#define		COLOR_PURPLE (COLOR_RED | COLOR_BLUE)
#define		COLOR_CYAN   (COLOR_BLUE | COLOR_GREEN)

class NOVTABLE ABuffer
{
public:
	static constexpr reference<ABuffer*, 0x87E8A4> Instance {};

	ABuffer(RectangleStruct Rect) { JMP_THIS(0x410CE0); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x410DC0); }
	void ReleaseSurface() { JMP_THIS(0x410E50); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x410E70); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x410ED0); }
	bool Fill(unsigned short Color) { JMP_THIS(0x4112D0); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x411310); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x411330); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x4114B0); }

	RectangleStruct Bounds;
	int BufferPosition;
	BSurface* Surface;
	int BufferHead;
	int BufferTail;
	int BufferSize;
	int MaxValue;
	int Width;
	int Height;
};

class NOVTABLE ZBuffer
{
public:
	static constexpr reference<ZBuffer*, 0x887644> Instance {};

	ZBuffer(RectangleStruct Rect) { JMP_THIS(0x7BC970); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x7BCA50); }
	void ReleaseSurface() { JMP_THIS(0x7BCAE0); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x7BCAF0); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x7BCB50); }
	bool Fill(unsigned short Color) { JMP_THIS(0x7BCF50); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x7BCF90); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x7BCFB0); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x7BD130); }

	RectangleStruct Bounds;
	int BufferOffset;
	BSurface* Surface;
	int BufferHead;
	int BufferTail;
	int BufferSize;
	int MaxValue;
	int Width;
	int Height;
};

struct VoxelCacheStruct
{
	short X;
	short Y;
	unsigned short Width;
	unsigned short Height;
	void* Buffer;
};

struct MainVoxelIndexKey
{
public:
	unsigned FrameIndex : 5;
	unsigned RampType : 5;
private:
	unsigned bitfield_10 : 6;
public:
	unsigned UseAuxVoxel : 1; // !(!pUnit->Type->NoSpawnAlt || pUnit->SpawnManager->Draw_State())
private:
	unsigned bitfield_17 : 15;
};

struct TurretWeaponVoxelIndexKey
{
public:
	unsigned Facing : 5;
	unsigned HasTurretOffset : 5;
private:
	unsigned bitfield_10 : 6;
public:
	unsigned FrameIndex : 8;
	unsigned TurretWeaponIndex : 8;
};

struct ShadowVoxelIndexKey
{
public:
	unsigned Data : 32;
};

struct TurretBarrelVoxelIndexKey
{
public:
	unsigned Facing : 5;
	unsigned HasTurretOffset : 5;
private:
	unsigned bitfield_10 : 6;
public:
	unsigned FrameIndex : 8;
private:
	unsigned bitfield_24 : 8;
};

struct ReservedVoxelIndexKey
{
private:
	unsigned bitfield_0 : 10;
public:
	unsigned ReservedIndex : 6;
private:
	unsigned bitfield_16 : 16;
};

union VoxelIndexKey
{
	explicit VoxelIndexKey() noexcept
	{
		*reinterpret_cast<int*>(this) = 0;
	}

	int Get_Index_ID() const
	{
		return *reinterpret_cast<const int*>(this);
	}

	bool Is_Valid_Key() const
	{
		return Get_Index_ID() != -1;
	}

	MainVoxelIndexKey MainVoxel;
	TurretWeaponVoxelIndexKey TurretWeapon;
	ShadowVoxelIndexKey Shadow;
	TurretBarrelVoxelIndexKey TurretBarrel;
	ReservedVoxelIndexKey Reserved;
};

static_assert(sizeof(VoxelIndexKey) == sizeof(int));
