#include "Timer.h"

using namespace misc;

Timer::Timer()
{
	_pausedTime = 0.0;
	_elapsedTime = 0.0;
}


Timer::~Timer()
{
}

void Timer::reset()
{
	_paused = false;
	clock_gettime(CLOCK_REALTIME, &_timeSpec);
	_start = (_timeSpec.tv_sec * 1000 + _timeSpec.tv_nsec / 1e6);
}
void Timer::start()
{
	_paused = false;
	clock_gettime(CLOCK_REALTIME, &_timeSpec);
	_start = (_timeSpec.tv_sec * 1000 + _timeSpec.tv_nsec / 1e6);
}
void Timer::pause()
{
	if (!_paused)
	{
		_paused = true;
		clock_gettime(CLOCK_REALTIME, &_timeSpec);
		_pause = (_timeSpec.tv_sec * 1000 + _timeSpec.tv_nsec / 1e6);
	}
}

void Timer::resume()
{
	if (_paused)
	{
		_paused = false;
		clock_gettime(CLOCK_REALTIME, &_timeSpec);
		_pausedTime += ((_timeSpec.tv_sec * 1000 + _timeSpec.tv_nsec / 1e6) - _pause);
	}
}
double Timer::getElapsedTime(TIME time)
{
	if (_paused)
	{
		switch (time)
		{
		case SECONDS:
			return _elapsedTime / 1e3;
			break;

		case MILLISECONDS:
			return _elapsedTime;
			break;

		case MICROSECONDS:
			return _elapsedTime * 1e3;
			break;
		case NANOSECONDS:
			return _elapsedTime * 1e6;
			break;
		}
	}
	else
	{
		clock_gettime(CLOCK_REALTIME, &_timeSpec);
		_elapsedTime = ((_timeSpec.tv_sec*1000 + _timeSpec.tv_nsec/1e6) - _start - _pausedTime);
		switch (time)
		{
		case SECONDS:
			return _elapsedTime / 1e3;
			break;

		case MILLISECONDS:
			return _elapsedTime;
			break;

		case MICROSECONDS:
			return _elapsedTime * 1e3;
			break;
		case NANOSECONDS:
			return _elapsedTime * 1e6;
			break;
		}
	}
}

