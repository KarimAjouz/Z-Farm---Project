#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

namespace ZEngine
{

	class ResourceBar
	{
	public:
		ResourceBar(GameDataRef data, std::string filepath, std::string texName, sf::Vector2f pos);
		~ResourceBar();

		void Update(float dT);
		void Draw(float dT);

		void ResizeForeground(float per);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _foreground;

		std::string _texName;

		void Move(sf::Vector2f pos);

	};

}