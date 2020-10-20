#pragma once
#include "Button.h"



namespace ZEngine
{
	class Menu_Scale
	{
	public:
		Menu_Scale(std::string name, int min, int max, int interval, int currentVal, sf::Vector2f pos, GameDataRef data);
		~Menu_Scale();

		void Update(float dT);
		void Draw(float dT);

		int GetValue();

	private:
		Button _lArrow;
		Button _rArrow;

		sf::Text _scaleText;

		std::string _name;
		int _min;
		int _max;
		int _interval;
		int _currentVal;

		GameDataRef _data;

		sf::Vector2f _pos;


		int _steps;


	};

}