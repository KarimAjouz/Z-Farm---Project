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

		float GetPercentageRemaining();


	private:
		float _length;
		sf::Clock _clock;
		bool _running;

		bool _autoRestart;
		
	};

}