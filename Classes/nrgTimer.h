#pragma once
#include "pch.h"

class nrgTimer
{
public:
	nrgTimer();

	void Start(); //Starts timer
	void Stop(); //Stops timer
	void Pause(bool unpauseOnResumeInput = false); //Pauses timer (same as stop, but can be unpaused)
	bool IsUnpauseOnResume();
	void Unpause(); //Resumes ticking, but only if previous paused
	bool IsRunning(); //Returns true if timer has started
	bool IsPaused(); //Returns whether clock has been stopped after starting
	long long GetElapsedTime(); //Returns time clocked
	long long GetElapsedSeconds(); //Returns time elapsed in seconds
	long long GetStartTime(); //Returns clock value when timer started
	long long GetStopTime(); //Returns clock value when timer stopped
	void Reset(); //Resets startTime, stopTime, and timeElapsed to 0			  
	void Restart(); //Resets startTime, stopTime, and timeElapsed to 0, clock continues running
	void DecreaseTimeElapsed(long long); //Subtract ms from timeElapsed			  
	void IncreaseTimeElapsed(long long); //Add ms to timeElapsed
	void SetMark(long long value = -1); //Set time marker to value + current time, or current time if no value given
	long long GetMark(); //Get the latest mark set
	void AddTimeToMark(int moreTime);
	bool IsMarkSet(); //Check whether mark has been set
	void ResetMark(); //Reset time marker
	~nrgTimer();

protected:

	bool isTicking = false; //Has clock started
	bool isPaused = false; //Whether clock has been stopped after starting
	bool markSet = false; //Has mark been set
	bool unpauseOnResume = true; //Whether to unpause time when app enters foreground
	long long startTime = 0; //Clock value at Start
	long long stopTime = 0; //Clock value at Stop
	long long elapsedTime = 0; //stopTime - startTime
	long long increasedTime = 0; //How much time was added to stop time to increase time elapsed
	long long decreasedTime = 0; //How much time was subtracted from stop time to decrease time elapsed
	long long mark = -1; //Time marked for reference in future
};

