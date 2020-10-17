#pragma once

#include <SFML/Graphics.hpp>

namespace ZEngine
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		bool IsSpriteClicked(sf::Sprite object, sf::RenderWindow &window);
		bool IsSpriteReleased(sf::Sprite object, sf::RenderWindow &window);


		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	private:


	};

}