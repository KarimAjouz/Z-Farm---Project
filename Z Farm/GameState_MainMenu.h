#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Game.h"
#include "Button.h"
#include "Menu_Scale.h"


class GameState_MainMenu : public ZEngine::GameState
{
public:
	GameState_MainMenu(ZEngine::GameDataRef data);
	~GameState_MainMenu();

	void Init();
	
	void PollEvents();
	void Update(float dT);
	void Draw(float dT);

private:
	ZEngine::GameDataRef _data;

	sf::Sprite _bgSprite;

	ZEngine::Button _playButton;
	ZEngine::Button _quitButton;

	
};

