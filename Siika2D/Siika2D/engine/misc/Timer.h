#pragma once
#include <ctime>
enum TIME
{SECONDS, MILLISECONDS, MICROSECONDS};

namespace misc
{
	class Timer
	{
	public:
		Timer(void){};
		Timer(std::clock_t start);
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
		std::clock_t _start, _pause;
		double _pausedTime, _elapsedTime;
		bool _paused;
	};
}
