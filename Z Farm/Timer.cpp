#include "Timer.h"
#include <iostream>

namespace ZEngine
{


	Timer::Timer(float length, bool autoRestart) :
		_length(length),
		_autoRestart(autoRestart),
		_pauseTime(0.0f)
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
		if (_clock.getElapsedTime().asSeconds() - _pauseTime > _length && _running)
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

	void Timer::Pause()
	{
		_pauseClock.restart();
		_running = false;
	}

	void Timer::Resume()
	{
		_pauseTime += _pauseClock.getElapsedTime().asSeconds();
		_running = true;
	}

	float Timer::GetSecondsRemaining()
	{
		return _clock.getElapsedTime().asSeconds();
	}
	
	void Timer::SetTimer(float seconds)
	{
		_length = seconds;
	}
}