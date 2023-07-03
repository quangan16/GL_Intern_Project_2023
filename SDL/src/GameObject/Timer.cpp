#include "Timer.h"
#include <SDL_timer.h>

Timer::Timer()
{
	//Initialize the variable
	mStartTicks = 0;
	mPausedTicks = 0;
	mStarted = false;
	mPaused = false;
}
void Timer::Start()
{
	//Start the timer
	mStarted = true;
	//Unpause the timer
	mPaused = false;
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}
void Timer::Stop()
{
	//Stop the timer
	mStarted = false;
	//Unpaused the timer
	mPaused = false;
	//Clean tick variables
	mStartTicks = 0;
	mPausedTicks = 0;

}
void Timer::Pause()
{
	//IF the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;
		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}
void Timer::UnPause()
{
	//IF the timer is running and already paused
	if (mStarted && mPaused)
	{
		//Pause the timer
		mPaused = false;
		// Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
}
Uint32 Timer::GetTicks()
{
	//The actual timer time

	Uint32 time = 0;
	//If the timer is running
	if (mStarted)
	{
		//if the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}
bool Timer::IsStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}
bool Timer::IsPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}