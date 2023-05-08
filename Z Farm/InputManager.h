#pragma once

#include <SFML/Graphics.hpp>

#include "Utilities.h"

//using namespace ZEngine;

class InputManager
{
public:
	InputManager(class Player* InPlayer, class GameState_Gameplay* InGameplayState);
	~InputManager();

	bool IsSpriteClicked(sf::Sprite object, sf::RenderWindow& InWindow);
	bool IsSpriteReleased(sf::Sprite object, sf::RenderWindow& InWindow);

	sf::Vector2i GetMousePosition(sf::RenderWindow& InWIndow);

	//An input axis for WSAD/Arrow-Key controls
	sf::Vector2f GetInputAxis() { return m_InputAxis; }
	void SetInputAxis(sf::Vector2f InputAxis)
	{
		m_InputAxis.x = ZEngine::Utilities::ClampFloat(InputAxis.x, -1.0f, 1.0f);
		m_InputAxis.y = ZEngine::Utilities::ClampFloat(InputAxis.y, -1.0f, 1.0f);
	};

	void HandleInputEvents(sf::RenderWindow& InWIndow);

private:
	sf::Vector2f m_InputAxis;

	class Player* m_Player;

	class GameState_Gameplay* m_GameplayState;

	void HandleGamestateInputs(std::vector<sf::Event>* InEventQueue);
	void HandlePlayerInputs(std::vector<sf::Event>* InEventQueue);

	void PollInputAxis();
};