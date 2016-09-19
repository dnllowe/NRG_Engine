#include "pch.h"
#include "nrgTimer.h"


nrgTimer::nrgTimer()
{
}

//Starts timer
void nrgTimer::Start()
{
	//Only start timer if not running
	if (!isTicking)
	{
		//Turn the timer on
		isTicking = true;

		auto epoch = std::chrono::steady_clock::now().time_since_epoch();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

		//Start time should equal global time passed
		startTime = time;
	}

	return;
}

//Stops timer
void nrgTimer::Stop()
{
	//Only stop the timer if running
	if (isTicking)
	{
		//Turn the timer off
		isTicking = false;

		auto epoch = std::chrono::steady_clock::now().time_since_epoch();
		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

		//Stop time should equal global time passed plus any time counted on timer
		stopTime = time + increasedTime - decreasedTime;

		//Count the time elapsed plus any previously recorded time
		elapsedTime += (stopTime - startTime);
		stopTime = 0;
		startTime = 0;
	}

	return;
}

void nrgTimer::Pause(bool unpauseOnResumeInput)
{
	if (isTicking)
	{
		Stop();
		isPaused = true;
		unpauseOnResume = unpauseOnResumeInput;
	}
	return;
}

bool nrgTimer::IsUnpauseOnResume()
{
	return unpauseOnResume;
}

void nrgTimer::Unpause()
{
	if (isPaused)
		Start();
	
	isPaused = false;
	unpauseOnResume = true;

	return;
}

//Returns true if timer has started
bool nrgTimer::IsRunning()
{
	return isTicking;
}

bool nrgTimer::IsPaused()
{
	return isPaused;
}

//Returns time clocked while running or while stopped/paused
long long nrgTimer::GetElapsedTime()
{
	auto epoch = std::chrono::steady_clock::now().time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
	long long elapse = time - startTime + increasedTime - decreasedTime;

	if (isTicking)
		return elapse + elapsedTime;
	else
		return elapsedTime;
}

//Returns time elapsed in seconds
long long nrgTimer::GetElapsedSeconds()
{
	auto epoch = std::chrono::steady_clock::now().time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
	long long elapse = time - startTime + increasedTime - decreasedTime;

	if (isTicking)
		return (elapse + elapsedTime) / 1000;
	else
		return (elapsedTime / 1000);
}

//Returns clock value when timer started
long long nrgTimer::GetStartTime()
{
	return startTime;
}

//Returns clock value when timer stopped
long long nrgTimer::GetStopTime()
{
	return stopTime + increasedTime - decreasedTime;
}

//Resets startTime, stopTime, and elapsedTime to 0, stops clock
void nrgTimer::Reset()
{
	auto epoch = std::chrono::steady_clock::now().time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

	startTime = time;
	stopTime = startTime;
	elapsedTime = 0;
	increasedTime = 0;
	decreasedTime = 0;
	isTicking = false;
	isPaused = false;
	markSet = false;
	unpauseOnResume = true;
	mark = 0;
	return;
}

//Resets startTime, stopTime, and elapsedTime to 0, clock continues running
void nrgTimer::Restart()
{
	auto epoch = std::chrono::steady_clock::now().time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

	startTime = time;
	stopTime = startTime;
	elapsedTime = 0;
	increasedTime = 0;
	decreasedTime = 0;
	isTicking = true;
	isPaused = false;
	markSet = false;
	mark = 0;
	unpauseOnResume = true;
	return;
}

//Add ms to timeElapsed
void nrgTimer::IncreaseTimeElapsed(long long ms)
{
	//elapsedTime += ms;
	//startTime -= ms; //Lower start time. Now, when checking elapsed time, the stoptime - starttime will have an increased value
	increasedTime += ms;

	return;
}

void nrgTimer::SetMark(long long value)
{
	if (value <= 0) //If no value set, set mark for current time
		mark = GetElapsedTime();
	else
		mark = GetElapsedTime() + value;
	markSet = true;
	return;
}

long long nrgTimer::GetMark()
{
	return mark;
}

void nrgTimer::AddTimeToMark(int moreTime)
{
	if (markSet)
		mark += moreTime;

	return;
}

bool nrgTimer::IsMarkSet()
{
	return markSet;
}

void nrgTimer::ResetMark()
{
	mark = -1;
	markSet = false;
	return;
}

//Subtract ms from timeElapsed
void nrgTimer::DecreaseTimeElapsed(long long ms)
{
	//elapsedTime -= ms;
	//startTime += ms; //Increase start time. Now, when checking elapsed time, the stoptime - starttime will have a lower (reversed) value
	decreasedTime += ms;

	return;
}

nrgTimer::~nrgTimer()
{
}
