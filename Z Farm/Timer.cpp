#include "Timer.h"
#include <iostream>

namespace ZEngine
{


	Timer::Timer(float length, bool autoRestart) :
		_length(length),
		_autoRestart(autoRestart)
	{
		_running = false;
	}


	Timer::~Timer()
	{
	}

	void Timer::Start()
	{
		_running = true;
		_clock.restart();
	}

	bool Timer::Complete()
	{
		float temp = _clock.getElapsedTime().asSeconds();
		if (temp > _length && _running)
		{
			if (_autoRestart)
				_clock.restart();

			return true;
		}
		return false;
	}

	float Timer::GetPercentageRemaining() 
	{
		return (_clock.getElapsedTime().asSeconds() / _length);
	}

}