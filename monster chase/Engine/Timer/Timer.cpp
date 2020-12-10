#include "Timer/Timer.h"
#include "Windows.h"
#include "iostream"

//Timer::Timer()
//{
//	LastFrameStartTick.QuadPart = 0;
//}

void Timer::Initialize()
{
	QueryPerformanceFrequency(&PerformaceFrequency);
}

float Timer::GetLatFrameTimeMS()
{
	LARGE_INTEGER LocalCurrentTick;

	// getting the current CPU tick as LARGE_INTEGER
	QueryPerformanceCounter(&LocalCurrentTick);
	this->CurrentTick = LocalCurrentTick.QuadPart;

	if (this->LastFrameStartTick) // check if the LastFrameStartTick is non-zero
	{

		this->LastFrameTimeMS = (1000.0f * static_cast<float>(this->CurrentTick - this->LastFrameStartTick)) / PerformaceFrequency.QuadPart;

		// check if the frame time exceeds twice the desired frame time. ie the user is debuggung
		if (this->LastFrameTimeMS > MAX_FRAMETIME_MS)
			this->LastFrameTimeMS = DESIRED_FRAMETIME_MS; // assume 60 fps	

	}

	else // If lastFrameTick was 0 ie this is the first iteration thus assume 60 fps
	{
		this->LastFrameTimeMS = DESIRED_FRAMETIME_MS;
	}

	// update last frame start tick
	this->LastFrameStartTick = this->CurrentTick;

	return this->LastFrameTimeMS;

}