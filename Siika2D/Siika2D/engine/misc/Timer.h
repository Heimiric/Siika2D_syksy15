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
		Gets time in seconds
		*/
		double getElapsedTime(TIME time);
		bool operator==(const Timer rhs)
		{
			if(this->_start == rhs._start)
				return true;
			return false;
		}
	private:
		std::clock_t _start;
	};
}
