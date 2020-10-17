#include "GameState_Splash.h"

#include <iostream>
#include <sstream>

#include "Definitions.h"
#include "GameState_MainMenu.h"


GameState_Splash::GameState_Splash(ZEngine::GameDataRef data) :
	_data(data)
{

}


GameState_Splash::~GameState_Splash()
{
	std::cout << "Splash Screen exit" << std::endl;
}


void GameState_Splash::Init()
{
	_data->assetManager.LoadTexture("Splash_BG", SPLASH_SCREEN_BACKGROUND_FILEPATH);

	_bgSprite.setTexture(_data->assetManager.GetTexture("Splash_BG"));
}

void GameState_Splash::PollEvents()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}
	}
}

void GameState_Splash::Update(float dT)
{
	if (_clock.getElapsedTime().asSeconds() > SPLASH_SCREEN_SHOW_TIME)
	{
		_data->stateMachine.AddState(ZEngine::StateRef(new GameState_MainMenu(this->_data)), true);
	}
}

void GameState_Splash::Draw(float dT)
{
	_data->window.clear();
	_data->window.draw(_bgSprite);
	_data->window.display();
}