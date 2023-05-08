#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "Game.h"

class GameState_Splash : public ZEngine::GameState
{
public:
	GameState_Splash(ZEngine::GameDataRef data);
	~GameState_Splash();

	void Init();

	void PollEvents();

	void Update(float dT);

	void Draw();

private:

	ZEngine::GameDataRef _data;

	sf::Clock _clock;

	sf::Sprite _bgSprite;
};