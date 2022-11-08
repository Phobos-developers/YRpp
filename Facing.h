#pragma once

#include <Dir.h>
#include <Timer.h>

#include <algorithm>

class FacingClass
{
public:
	explicit FacingClass() noexcept { }

	explicit FacingClass(int rate) noexcept
	{
		SetROT(rate);
	}

	explicit FacingClass(const DirStruct& facing) noexcept
	{
		DesiredFacing = facing;
	}

	explicit FacingClass(DirType dir) noexcept
	{
		DesiredFacing.SetDir(dir);
	}

	explicit FacingClass(const FacingClass& another) noexcept
		: DesiredFacing { another.DesiredFacing }
		, StartFacing { another.StartFacing }
		, RotationTimer { another.RotationTimer }
		, ROT { another.ROT }
	{ }

	FacingClass& operator=(const FacingClass& another)
	{
		if (this != &another)
		{
			DesiredFacing = another.DesiredFacing;
			StartFacing = another.StartFacing;
			RotationTimer = another.RotationTimer;
			ROT = another.ROT;
		}

		return *this;
	}

	bool SetDesired(const DirStruct& facing) //JMP_THIS(0x4C9220)
	{
		if (DesiredFacing == facing)
			return false;

		StartFacing = Current();
		DesiredFacing = facing;

		if (static_cast<short>(ROT.Raw) > 0)
			RotationTimer.Start(NumSteps());

		return true;
	}

	bool SetCurrent(const DirStruct& facing)
	{
		bool ret = Current() != facing;
		if (ret)
		{
			DesiredFacing = facing;
			StartFacing = facing;
		}
		RotationTimer.Start(0);
		return ret;
	}

	DirStruct Desired() const
	{
		return DesiredFacing;
	}

	DirStruct Current() const //0x4C93D0
	{
		if (IsRotating())
		{
			const short diff = Difference().Raw;
			const short num_steps = static_cast<short>(NumSteps());
			if (num_steps > 0)
			{
				const int steps_left = RotationTimer.GetTimeLeft();
				return DirStruct { DesiredFacing.Raw - steps_left * diff / num_steps };
			}
		}
		return DesiredFacing;
	}

	bool IsRotating() const // JMP_THIS(0x4C9480)
	{
		return static_cast<short>(ROT.Raw) > 0 && RotationTimer.GetTimeLeft();
	}

	bool IsRotatingCCW() const // JMP_THIS(0x4C94F0) counter-clockwise
	{
		if (!IsRotating())
			return false;

		return static_cast<short>(Difference().Raw) < 0;
	}

	bool IsRotatingCW() const // JMP_THIS(0x4C94B0) clockwise
	{
		if (!IsRotating())
			return false;

		return static_cast<short>(Difference().Raw) > 0;
	}

	DirStruct Difference() const
	{
		return DirStruct { static_cast<short>(DesiredFacing.Raw) - static_cast<short>(StartFacing.Raw) };
	}

	void SetROT(int rate)
	{
		if (rate > 127)
			rate = 127;
		ROT.SetDir(static_cast<DirType>(rate));
	}

private:
	int NumSteps() const
	{
		return std::abs(static_cast<short>(Difference().Raw)) / ROT.Raw;
	}

public:

	DirStruct DesiredFacing;
	DirStruct StartFacing; // The starting direction from which to calcuate the rotation.
	CDTimerClass RotationTimer;
	DirStruct ROT;
};
