#pragma once
// #include "winnt.h"
#include "Windows.h"
#include "stdint.h"

class Timer
{

public:
#define DESIRED_FRAMERATE		60.0f
#define DESIRED_FRAMETIME_MS	(1000.0f / DESIRED_FRAMERATE)
#define MAX_FRAMETIME_MS		(2.0f * DESIRED_FRAMETIME_MS)

	// Timer(); // constructor
	
	// INitialize the timer
	void Initialize();


	/* Returns a long value representing the ms value for frametime. 
	Returns 0 if something in the function didn't work*/
	float GetLatFrameTimeMS();


private:
	LARGE_INTEGER PerformaceFrequency = { 0 };
	uint64_t LastFrameStartTick = 0;
	uint64_t CurrentTick = 0;
	float LastFrameTimeMS = 0;
};