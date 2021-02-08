#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"



namespace ZEngine
{
	class Button
	{
	public:

		Button(std::string text, GameDataRef data, sf::Vector2f pos, sf::Color textColour, std::string filePath, std::string fileName);
		~Button();



		sf::Sprite sprite;
		
		void Init();
		void Update(float dT);
		void Draw();

		bool Engaged;
		bool Active;

		void Activate();

	private:
		GameDataRef _data;
		sf::Font _font;
		sf::Text _text;
		sf::Color _textColour;

		std::string _fileName;

		void SetDefault();
		void SetHovered();
		void SetClicked();


	};


}