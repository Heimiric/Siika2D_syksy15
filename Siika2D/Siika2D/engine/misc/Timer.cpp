#include "Timer.h"

using namespace misc;

Timer::Timer(std::clock_t start)
{
	start = _start;
}


Timer::~Timer()
{
}

void Timer::reset()
{
	_start = std::clock();
}
void Timer::start()
{
	_start = std::clock();
}
double Timer::getElapsedTime(TIME time)
{
	double elapsed;
	switch (time)
	{

	case SECONDS:
		elapsed = (std::clock() - _start) / (double)CLOCKS_PER_SEC;
		return elapsed;
		break;
	
	case MILLISECONDS:
		elapsed = (std::clock() - _start) / (double)(CLOCKS_PER_SEC/1000);
		return elapsed;
		break;

	case MICROSECONDS:
		elapsed = (std::clock() - _start) / (double)(CLOCKS_PER_SEC / 1000000);
		return elapsed;
		break;
	}

}

