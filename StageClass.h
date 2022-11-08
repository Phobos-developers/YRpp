/*
	Staged timer used by various animations etc.

	This class uses a timer set to a specified interval (rate) to increase the current
	value by a specified amount (step).
*/

#pragma once

#include <GeneralStructures.h>

class StageClass
{
public:
	constexpr StageClass() = default;
	StageClass(int rate) { this->Rate = rate; this->Start(rate); }

	void Start(int rate)
	{
		this->Rate = rate;
		this->Timer.Start(rate);
	}

	void Start(int rate, int step)
	{
		this->Rate = rate;
		this->Step = step;
		this->Start(rate);
	}

	// returns whether the value changed.
	bool Update()
	{
		if (Timer.Expired() && Rate != 0)
		{
			// timer expired. move one step forward.
			this->Value += this->Step;
			this->HasChanged = true;
			this->Timer.Start(Rate);
		}
		else
		{
			// timer is still running or hasn't been set yet.
			this->HasChanged = false;
		}

		return this->HasChanged;
	}

	int Value { 0 }; // the current stage value
	bool HasChanged { false }; // if the timer expired this frame and the stage value changed
	CDTimerClass Timer {};
	int Rate { 0 }; // how many frames it takes to increment the stage value
	int Step { 1 }; // added to the stage value every time the timer expires
};
