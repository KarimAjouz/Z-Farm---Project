#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"



namespace ZEngine
{
	class Button
	{
	public:
		enum Type { loadScene, quit };

		Button(std::string text, GameDataRef data, sf::Vector2f pos, sf::Color textColour, Type t);
		~Button();



		sf::Sprite sprite;
		
		void Init();
		void Update(float dT);
		void Draw(float dT);

		bool Engaged;

		void Activate();

	private:
		GameDataRef _data;
		sf::Font _font;
		sf::Text _text;
		sf::Color _textColour;

		Type _type;

		void SetDefault();
		void SetHovered();
		void SetClicked();


	};


}