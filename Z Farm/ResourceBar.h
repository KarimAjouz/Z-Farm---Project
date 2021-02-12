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
		void Draw();

		void ResizeForeground(float per);

		void Move(sf::Vector2f pos);

		void Centralise();

		void ReScaleWidth(float sf);

	private:
		GameDataRef _data;

		float _scaleFactor;

		sf::Sprite _background;
		sf::Sprite _foreground;

		std::string _texName;

		bool _centralised;

	};

}