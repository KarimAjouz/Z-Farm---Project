#pragma once

#include <SFML/System.hpp>


namespace ZEngine
{
	class Timer
	{
	public:
		Timer(float length, bool autoRestart);
		~Timer();

		void Start();
		bool Complete();

		void Pause();
		void Resume();

		float GetPercentageRemaining();

		float GetSecondsRemaining();

		void SetTimer(float seconds);

	private:
		float _length;
		
		sf::Clock _clock;
		sf::Clock _pauseClock;

		float _pauseTime;

		bool _running;
		bool _autoRestart;
		
	};

}