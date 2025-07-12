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
	DEFINE_REFERENCE(RGBClass, White, 0xA80220)
	DEFINE_REFERENCE(int, RedShiftLeft, 0x8A0DD0)
	DEFINE_REFERENCE(int, RedShiftRight, 0x8A0DD4)
	DEFINE_REFERENCE(int, GreenShiftLeft, 0x8A0DE0)
	DEFINE_REFERENCE(int, GreenShiftRight, 0x8A0DE4)
	DEFINE_REFERENCE(int, BlueShiftLeft, 0x8A0DD8)
	DEFINE_REFERENCE(int, BlueShiftRight, 0x8A0DDC)

	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;

	explicit RGBClass() noexcept
		: Red { 0 }
		, Green { 0 }
		, Blue { 0 }
	{
	}

	explicit RGBClass(int r, int g, int b) noexcept
		: Red { static_cast<unsigned char>(r) }
		, Green { static_cast<unsigned char>(g) }
		, Blue { static_cast<unsigned char>(b) }
	{
	}


	explicit RGBClass(int rgb, bool wordcolor = false) noexcept
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
	DEFINE_REFERENCE(DynamicVectorClass<DirtyAreaStruct>, DirtyAreas, 0xB0CE78)
	DEFINE_REFERENCE(ColorStruct, TooltipColor, 0xB0FA1C)
	// RGB color mode currently in use, determined by primary drawing surface. The bitshift values below can change depending on this.
	DEFINE_REFERENCE(RGBMode, ColorMode, 0x8205D0)
	DEFINE_REFERENCE(int, RedShiftLeft, 0x8A0DD0)
	DEFINE_REFERENCE(int, RedShiftRight, 0x8A0DD4)
	DEFINE_REFERENCE(int, GreenShiftLeft, 0x8A0DE0)
	DEFINE_REFERENCE(int, GreenShiftRight, 0x8A0DE4)
	DEFINE_REFERENCE(int, BlueShiftLeft, 0x8A0DD8)
	DEFINE_REFERENCE(int, BlueShiftRight, 0x8A0DDC)

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
	static int RGB_To_Int(int red, int green, int blue)
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
	DEFINE_REFERENCE(ABuffer*, Instance, 0x87E8A4)

	ABuffer(RectangleStruct Rect) { JMP_THIS(0x410CE0); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x410DC0); }
	void ReleaseSurface() { JMP_THIS(0x410E50); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x410E70); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x410ED0); }
	bool Fill(unsigned short Color) { JMP_THIS(0x4112D0); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x411310); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x411330); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x4114B0); }

	template<typename T>
	void AdjustPointer(T*& ptr)
	{
		if (ptr >= BufferTail)
			reinterpret_cast<char*&>(ptr) -= BufferSize;
	}

	RectangleStruct Bounds;
	int BufferPosition;
	BSurface* Surface;
	void* BufferHead;
	void* BufferTail;
	int BufferSize;
	int MaxValue;
	int Width;
	int Height;
};

class NOVTABLE ZBuffer
{
public:
	DEFINE_REFERENCE(ZBuffer*, Instance, 0x887644)

	ZBuffer(RectangleStruct Rect) { JMP_THIS(0x7BC970); }
	bool BlitTo(Surface* pSurface, int X, int Y, int Offset, int Size) { JMP_THIS(0x7BCA50); }
	void ReleaseSurface() { JMP_THIS(0x7BCAE0); }
	void Blitter(unsigned short* Data, int Length, unsigned short Value) { JMP_THIS(0x7BCAF0); }
	void BlitAt(int X, int Y, COLORREF Color) { JMP_THIS(0x7BCB50); }
	bool Fill(unsigned short Color) { JMP_THIS(0x7BCF50); }
	bool FillRect(unsigned short Color, RectangleStruct Rect) { JMP_THIS(0x7BCF90); }
	void BlitRect(RectangleStruct Rect) { JMP_THIS(0x7BCFB0); }
	void* GetBuffer(int X, int Y) { JMP_THIS(0x7BD130); }

	template<typename T>
	void AdjustPointer(T*& ptr)
	{
		if (ptr >= BufferTail)
			reinterpret_cast<char*&>(ptr) -= BufferSize;
	}

	RectangleStruct Bounds;
	int BufferOffset;
	BSurface* Surface;
	void* BufferHead;
	void* BufferTail;
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
	unsigned FrameIndex : 5;
	unsigned BodyFacing : 5;
	unsigned RampType : 6;
	unsigned UseAuxVoxel : 1; // !(!pUnit->Type->NoSpawnAlt || pUnit->SpawnManager->Draw_State())
	unsigned Reserved : 15;
};

struct MinorVoxelIndexKey
{
	unsigned TurretFacing : 5;
	unsigned BodyFacing : 5; // Reset to 0 when TurretOffset=0
	unsigned RampType : 6;
	unsigned TurretFrameIndex : 8;
	unsigned TurretWeaponIndex : 8; // Not set if no turret but have barrel
};

struct ShadowVoxelIndexKey
{
public:
	unsigned Data : 32;
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
	constexpr VoxelIndexKey(int val = 0) noexcept
	{
		Value = val;
	}

	constexpr operator int () const
	{
		return Value;
	}

	constexpr bool Is_Valid_Key() const
	{
		return Value != -1;
	}

	constexpr void Invalidate()
	{
		Value = -1;
	}

	MainVoxelIndexKey MainVoxel; // For body to use
	MinorVoxelIndexKey MinorVoxel; // For turret/barrel to use
	ShadowVoxelIndexKey Shadow;
	ReservedVoxelIndexKey Reserved;
	int Value;
};

static_assert(sizeof(VoxelIndexKey) == sizeof(int));
