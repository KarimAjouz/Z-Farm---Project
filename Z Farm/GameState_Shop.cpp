#include "GameState_Shop.h"

#include "Definitions.h"

GameState_Shop::GameState_Shop(ZEngine::GameDataRef data, GameState_Gameplay* gameplayState) :
	_data(data),
	_gameplayState(gameplayState)
{

}

GameState_Shop::~GameState_Shop()
{

}


void GameState_Shop::Init()
{

}

void GameState_Shop::PollEvents()
{
	sf::Event e;

	while (_data->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			_data->window.close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Key::Escape:
				QuitShop();
				break;
			case sf::Keyboard::Key::I:
				QuitShop();
				break;
			}
		}
	}
}

void GameState_Shop::Update(float dT)
{
	
}

void GameState_Shop::Draw()
{
}


/// <summary>
/// Pushes shop values to the game.
/// </summary>
void GameState_Shop::QuitShop()
{
}