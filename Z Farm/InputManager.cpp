#include "InputManager.h"

namespace ZEngine
{

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}


	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::RenderWindow &window)
	{
		sf::IntRect rect(object.getPosition().x - object.getGlobalBounds().width / 2, object.getPosition().y - object.getGlobalBounds().height / 2, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (rect.contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return true;
		}

		return false;
	}

	bool InputManager::IsSpriteReleased(sf::Sprite object, sf::RenderWindow &window)
	{
		sf::IntRect rect(object.getPosition().x - object.getGlobalBounds().width / 2, object.getPosition().y - object.getGlobalBounds().height / 2, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (rect.contains(sf::Mouse::getPosition(window)) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return true;
		}

		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}