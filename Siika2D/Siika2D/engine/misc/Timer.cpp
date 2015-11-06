#include "Timer.h"

using namespace misc;

Timer::Timer(std::clock_t start)
{
	_pausedTime = 0.0;
	_elapsedTime = 0.0;
	start = _start;
}


Timer::~Timer()
{
}

void Timer::reset()
{
	_paused = false;
	_start = std::clock();
}
void Timer::start()
{
	_paused = false;
	_start = std::clock();
}
void Timer::pause()
{
	if (!_paused)
	{
		_paused = true;
		_pause = std::clock();
	}
}

void Timer::resume()
{
	if (_paused)
	{
		_paused = false;
		_pausedTime += (std::clock() - _pause);
	}
}
double Timer::getElapsedTime(TIME time)
{
	if (_paused)
	{
		switch (time)
		{
		case SECONDS:
			return _elapsedTime/1000000;
			break;

		case MILLISECONDS:
			return _elapsedTime/1000;
			break;

		case MICROSECONDS:
			return _elapsedTime;
			break;
		}
	}
	else
	{
		_elapsedTime = (std::clock() - _start - _pausedTime) / (double)(CLOCKS_PER_SEC / 1000000);
		switch (time)
		{
		case SECONDS:
			return _elapsedTime/1000000;
			break;

		case MILLISECONDS:
			return _elapsedTime/1000;
			break;

		case MICROSECONDS:
			return _elapsedTime;
			break;
		}
	}
}

