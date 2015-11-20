#pragma once
#include <ctime>
enum TIME
{SECONDS, MILLISECONDS, MICROSECONDS, NANOSECONDS};

namespace misc
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		/**
		Function for reseting the start time
		*/
		void reset();
		/**
		Function for starting timer
		*/
		void start();
		/**
		Pauses the timer
		*/
		void pause();
		/**
		Resumes the timer
		*/
		void resume();

		/**
		Gets time in desired units enum TIME{SECONDS, MILLISECONDS, MICROSECONDS};
		*/
		double getElapsedTime(TIME time);
		bool operator==(const Timer rhs)
		{
			if(this->_start == rhs._start)
				return true;
			return false;
		}
	private:
		struct timespec _timeSpec;
		double _start, _pause;
		double _pausedTime, _elapsedTime;
		bool _paused;
	};
}
