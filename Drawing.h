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

/*
----------------------------------------------------------------------------------------------------
> Jul 13, 2025 - CrimRecya
> How does WW generate a VoxelIndexKey:
----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------
> Unit:
>
> 0x73B59D :  key = Game::bVPLRead - 1;
>                                                                           ···· ····  ···· ····  ···· ····  ···· ····
>
> 0x73B5CB :  loco->Draw_Matrix(&mtx, &key);
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ····  ···· ·rrr  rrrb bbbb
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ····  ···· ·000  000b bbbb
>        Tunnel(State)                                                      ···· ····  ···· ····  ···b bbbb  00dd dddd
>        Fly                                                                ···· ····  ···· ····  ···· ····  bbbb bplr
>        Rocket                                                             ···· ····  ···· ····  ···· ····  ·fib bbbb
>
> 0x73B607 :  key = (((this->WalkedFramesSoFar % Type->MainVoxel.HVA->FrameCount) & 0x1F) | (key << 5));
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ····  rrrr  rrbb  bbbf ffff
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ····  0000  00bb  bbbf ffff
>        Tunnel(State)                                                      ···· ····  ···· ··bb  bbb0  0ddd  dddf ffff
>        Fly                                                                ···· ····  ···· ····  ···b  bbbb  plrf ffff
>        Rocket                                                             ···· ····  ···· ····  ····  fibb  bbbf ffff
>
> 0x73B6AA :  key = key | (1 << 16);  (if (this->Type->NoSpawnAlt && !this->SpawnManager->CountDockedSpawns()))
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ···a  rrrr  rrbb  bbbf ffff
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ···a  0000  00bb  bbbf ffff
>        Tunnel(State)                                                      ···· ····  ···· ··b?  bbb0  0ddd  dddf ffff
>        Fly                                                                ···· ····  ···· ···a  ···b  bbbb  plrf ffff
>        Rocket                                                             ···· ····  ···· ···a  ····  fibb  bbbf ffff
>
> Obtain main result
>
> Draw main
>
> 0x73B778 :  key = (this->SecondaryFacing.Current().GetFacing<32>() | (key & ~0x1F));
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ····  rrrr  rrbb  bbbt tttt
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ····  0000  00bb  bbbt tttt
>        Tunnel(State)                                                      ···· ····  ···· ··bb  bbb0  0ddd  dddt tttt
>        Fly                                                                ···· ····  ···· ····  ···b  bbbb  plrt tttt
>        Rocket                                                             ···· ····  ···· ····  ····  fibb  bbbt tttt
>
> 0x73B78A :  key = key & ~0x3E0;  (if (!this->Type->TurretOffset))
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ····  rrrr  rr00  000t tttt
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ····  0000  0000  000t tttt
>        Tunnel(State)                                                      ···· ····  ···· ··bb  bbb0  0d??  ???t tttt
>        Fly                                                                ···· ····  ···· ····  ···b  bb??  ???t tttt
>        Rocket                                                             ···· ····  ···· ····  ····  fi00  000t tttt
>
> 0x73B79F :  key = key | ((this->TurretAnimFrame % Type->TurretVoxel.HVA->FrameCount) << 16);
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  iiii iiii  rrrr  rrbb  bbbt tttt
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  iiii iiii  0000  00bb  bbbt tttt
>        Tunnel(State)                                                      ···· ····  iiii ii??  bbb0  0ddd  dddt tttt
>        Fly                                                                ···· ····  iiii iiii  ···b  bbbb  plrt tttt
>        Rocket                                                             ···· ····  iiii iiii  ····  fibb  bbbt tttt
>
> Draw barrel if no turret
>
> 0x73B917 :  key = key | (this->CurrentTurretNumber << 24);
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) cccc cccc  iiii iiii  rrrr  rrbb  bbbt tttt
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    cccc cccc  iiii iiii  0000  00bb  bbbt tttt
>        Tunnel(State)                                                      cccc cccc  iiii ii??  bbb0  0ddd  dddt tttt
>        Fly                                                                cccc cccc  iiii iiii  ···b  bbbb  plrt tttt
>        Rocket                                                             cccc cccc  iiii iiii  ····  fibb  bbbt tttt
>
> Obtain minor result
>
> Draw minor
>
> ... Then shadow ...
----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------
> Aircraft:
>
> 0x41470F :  key = 0;
>                                                                           ···· ····  ···· ····  ···· ····  ···· ····
>
> ... Draw Shadow ...
>
> 0x414943 :  key = ((this->WalkedFramesSoFar % Type->MainVoxel.HVA->FrameCount) & 0x1F);
>                                                                           ···· ····  ···· ····  ···· ····  ···f ffff
>
> 0x414969 :  loco->Draw_Matrix(&mtx, &key);
>        Drive/Ship/Teleport/Hover(!Powered)/Jumpjet(!State)/Tunnel(!State) ···· ····  ···· ····  ffff frrr  rrrb bbbb
>        Hover(Powered)/Jumpjet(State)/DropPod/Mech/Walk                    ···· ····  ···· ····  ffff f000  000b bbbb
>        Tunnel(State)                                                      ···· ····  ···· ··ff  fffb bbbb  00dd dddd
>        Fly                                                                ···· ····  ···· ····  ···· ····  bbb? ????
>        Rocket                                                             ···· ····  ···· ····  ···· ····  ·fi? ????
>
> Obtain main result
>
> Draw main
----------------------------------------------------------------------------------------------------

----------------------------------------------------------------------------------------------------
> Draw_Matrix:
>
> Drive/Ship/Teleport/Hover/Jumpjet/Tunnel(!State)/DropPod/Mech/Walk:       <<= 6 , += , <<= 5 , |=
>
> Tunnel(State)                                                             <<= 5 , |= , <<= 8 , |=
>
> Fly/Rocket:                                                               |= , |= (No shift)
>
> Return
----------------------------------------------------------------------------------------------------
*/

struct MainVoxelIndexKey
{
	/*
		pUnit->WalkedFramesSoFar % pType->MainVoxel.HVA->FrameCount
	*/
	unsigned FrameIndex : 5;

	/*
		pUnit->PrimaryFacing.Current().GetFacing<32>()
	*/
	unsigned BodyFacing : 5;

	/*
		Drive : Loco->Ramp
		Ship : Loco->Ramp
		Hover (!loco->Is_Powered()): pUnit->GetCell()->SlopeIndex
		Jumpjet (!loco->State): pUnit->GetCell()->SlopeIndex
		Tunnel (!loco->State): pUnit->GetCell()->SlopeIndex
		Teleport (Fixed) : pUnit->GetCell()->SlopeIndex
		DropPod / Mech / Walk : Not set
	*/
	unsigned RampType : 6;

	/*
		pUnit->Type->NoSpawnAlt && !pUnit->SpawnManager->CountDockedSpawns()
	*/
	unsigned AuxVoxel : 1;

	/*
		No use
	*/
	unsigned Reserved : 15;
};

struct MinorVoxelIndexKey
{
	/*
		pUnit->SecondaryFacing.Current().GetFacing<32>()
	*/
	unsigned TurretFacing : 5;

	/*
		Inherit from MainVoxelIndexKey

		Reset to 0 if TurretOffset=0
	*/
	unsigned BodyFacing : 5;

	/*
		Inherit from MainVoxelIndexKey
	*/
	unsigned RampType : 6;

	/*
		pUnit->TurretAnimFrame % pType->TurretVoxel.HVA->FrameCount

		Not set if have MainVoxelIndexKey.FrameIndex
	*/
	unsigned TurretFrameIndex : 8;

	/*
		pUnit->CurrentTurretNumber

		Not set if no turret but have barrel
	*/
	unsigned TurretWeaponIndex : 8;
};

struct AircraftVoxelIndexKey
{
	unsigned BodyFacing : 5;
	unsigned RampType : 6;
	unsigned FrameIndex : 5;
	unsigned Reserved : 16;
};

struct FlyVoxelIndexKey
{
	unsigned FrameIndex : 5;
	unsigned RollRight : 1;
	unsigned RollLeft : 1;
	unsigned PitchState : 1;
	unsigned BodyFacing : 5;
	unsigned Reserved : 19;
};

struct RocketVoxelIndexKey
{
	unsigned FrameIndex : 5;
	unsigned BodyFacing : 5;
	unsigned InitialPitch : 1;
	unsigned FinalPitch : 1;
	unsigned Reserved : 20;
};

struct TunnelVoxelIndexKey
{
	unsigned FrameIndex : 5;
	unsigned DigState : 6;
	unsigned Empty : 2;
	unsigned BodyFacing : 5;
	unsigned Reserved : 14;
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

	MainVoxelIndexKey MainVoxel;  // (Unit) For body to use
	MinorVoxelIndexKey MinorVoxel;  // (Unit) For turret/barrel to use
	AircraftVoxelIndexKey AircraftVoxel;
	FlyVoxelIndexKey FlyVoxel; // (Unit)
	RocketVoxelIndexKey RocketVoxel; // (Unit)
	TunnelVoxelIndexKey UndergroundVoxel; // (Unit) loco->State != 0
	ShadowVoxelIndexKey Shadow;
	ReservedVoxelIndexKey Reserved;
	int Value;
};

static_assert(sizeof(VoxelIndexKey) == sizeof(int));
