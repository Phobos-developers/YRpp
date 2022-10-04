#pragma once

#if _HAS_CXX20
#message "Please update this file with STL library <bit>!"
#endif

enum class DirType : unsigned char;

// North -> 0x0000
// South -> 0x8000
// ...
// Just a very simple BAM
struct DirStruct
{
public:
	explicit DirStruct() noexcept : Raw { 0 } { }
	explicit DirStruct(int raw) noexcept : Raw { static_cast<unsigned short>(raw) } { }
	explicit DirStruct(double rad) noexcept { SetRadian<65536>(rad); }
	explicit DirStruct(const DirType dir) noexcept { SetDir(dir); }
	explicit DirStruct(const noinit_t& noinit) noexcept { }

	bool operator==(const DirStruct& another) const
	{
		return Raw == another.Raw;
	}

	bool operator!=(const DirStruct& another) const
	{
		return Raw != another.Raw;
	}

	void SetDir(DirType dir)
	{
		Raw = static_cast<unsigned short>(static_cast<unsigned char>(dir) * 256);
	}

	DirType GetDir() const
	{
		return static_cast<DirType>(Raw / 256);
	}

	// If you want to divide it into 32 facings, as 32 has 5 bits
	// then you should type <5> here.
	// So does the others.
	template<size_t Bits>
	constexpr size_t GetValue(size_t offset = 0) const
	{
		return TranslateFixedPoint<16, Bits>(Raw, offset);
	}

	template<size_t Bits>
	constexpr void SetValue(size_t value, size_t offset = 0)
	{
		Raw = static_cast<unsigned short>(TranslateFixedPoint<Bits, 16>(value, offset));
	}

	template<size_t Count>
	constexpr size_t GetFacing(size_t offset = 0) const
	{
		static_assert(HasSingleBit(Count));

		constexpr size_t Bits = BitWidth<Count - 1>();
		return GetValue<Bits>(offset);
	}

	template<size_t Count>
	constexpr void SetFacing(size_t value, size_t offset = 0)
	{
		static_assert(HasSingleBit(Count));

		constexpr size_t Bits = BitWidth<Count - 1>();
		SetValue<Bits>(value, offset);
	}

	template<size_t FacingCount>
	double GetRadian()
	{
		static_assert(HasSingleBit(FacingCount));

		constexpr size_t Bits = BitWidth<FacingCount - 1>();
		constexpr size_t Max = (1 << Bits) - 1;

		size_t value = GetValue<Bits>();
		int dir = static_cast<int>(value) - FacingCount / 4; // LRotate 90 degrees
		return dir * (-Math::TwoPi / FacingCount);
	}

	template<size_t FacingCount>
	void SetRadian(double rad)
	{
		static_assert(HasSingleBit(FacingCount));

		constexpr size_t Bits = BitWidth<FacingCount - 1>();
		constexpr size_t Max = (1 << Bits) - 1;

		int dir = static_cast<int>(rad / (-Math::TwoPi / FacingCount));
		size_t value = dir + FacingCount / 4; // RRotate 90 degrees
		SetValue<Bits>(value & Max);
	}

private:
	constexpr static bool HasSingleBit(size_t x) noexcept
	{
		return x != 0 && (x & (x - 1)) == 0;
	}

	template<size_t X>
	constexpr static size_t BitWidth() noexcept
	{
		if constexpr (X == 0)
			return 0;

		size_t T = X;
		size_t cnt = 0;
		while (T)
		{
			T >>= 1;
			++cnt;
		}

		return cnt;
	}

	template<size_t BitsFrom, size_t BitsTo>
	constexpr static size_t TranslateFixedPoint(size_t value, size_t offset = 0)
	{
		constexpr size_t MaskIn = ((1u << BitsFrom) - 1);
		constexpr size_t MaskOut = ((1u << BitsTo) - 1);

		if constexpr (BitsFrom > BitsTo)
			return (((((value & MaskIn) >> (BitsFrom - BitsTo - 1)) + 1) >> 1) + offset) & MaskOut;
		else if constexpr (BitsFrom < BitsTo)
			return (((value - offset) & MaskIn) << (BitsTo - BitsFrom)) & MaskOut;
		else
			return value & MaskOut;
	}

public:
	unsigned short Raw;
private:
	unsigned short Padding;
};

static_assert(sizeof(DirStruct) == 4);
