#pragma once

// Timer that counts down from specified value towards zero, counted in frames.
class CDTimerClass
{
public:
	int StartTime { -1 };
	int : 32; // timer
	int TimeLeft { 0 };

	constexpr CDTimerClass() = default;
	CDTimerClass(int duration) { this->Start(duration); }

	void Start(int duration)
	{
		this->StartTime = Unsorted::CurrentFrame;
		this->TimeLeft = duration;
	}

	void Stop()
	{
		this->StartTime = -1;
		this->TimeLeft = 0;
	}

	void Pause()
	{
		if (this->IsTicking())
		{
			this->TimeLeft = this->GetTimeLeft();
			this->StartTime = -1;
		}
	}

	void Resume()
	{
		if (!this->IsTicking())
		{
			this->StartTime = Unsorted::CurrentFrame;
		}
	}

	int GetTimeLeft() const
	{
		if (!this->IsTicking())
		{
			return this->TimeLeft;
		}

		auto passed =  Unsorted::CurrentFrame - this->StartTime;
		auto left = this->TimeLeft - passed;

		return (left <= 0) ? 0 : left;
	}

	// returns whether a ticking timer has finished counting down.
	bool Completed() const
	{
		return this->IsTicking() && !this->HasTimeLeft();
	}

	// Returns whether a delay is active or a timer is still counting down.
	// this is the 'opposite' of Completed() (meaning: incomplete / still busy)
	// and logically the same as !Expired() (meaning: blocked / delay in progress)
	bool InProgress() const
	{
		return this->IsTicking() && this->HasTimeLeft();
	}

	// Returns whether a delay is inactive. same as !InProgress().
	bool Expired() const
	{
		return !this->IsTicking() || !this->HasTimeLeft();
	}

	// Sometimes I want to know if the timer has ever started
	bool HasStarted() const
	{
		return this->IsTicking() || this->HasTimeLeft();
	}

	// Returns whether or not the timer is currently ticking (started but not stopped or paused),
	// regardless of if there is time left or not.
	bool IsTicking() const
	{
		return this->StartTime != -1;
	}

	// Returns whether or not the timer has time left.
	bool HasTimeLeft() const
	{
		return this->GetTimeLeft() > 0;
	}
};

// Timer that counts down towards zero at specified rate, counted in frames.
class RateTimer : public CDTimerClass
{
public:
	int Rate { 0 };

	constexpr RateTimer() = default;
	RateTimer(int rate) { this->Rate = rate; this->Start(rate); }

	void Start(int rate)
	{
		this->Rate = rate;
		this->CDTimerClass::Start(rate);
	}
};
