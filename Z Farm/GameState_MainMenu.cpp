#include "GameState_MainMenu.h"
#include "Definitions.h"


#include "GameState_Gameplay.h"




GameState_MainMenu::GameState_MainMenu(ZEngine::GameDataRef data) :
	_data(data),
	_playButton("Play", _data, sf::Vector2f(400.0f, 300.0f), sf::Color::Red, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button"),
	_quitButton("Quit", _data, sf::Vector2f(400.0f, 400.0f), sf::Color::Red, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button"),
	_testScale("Test", 1, 100, 1, 5, sf::Vector2f(400.0f, 500.0f), _data)
{
	_data->assetManager.LoadTexture("Menu BG", MENU_SCREEN_BACKGROUND_FILEPATH);

	_bgSprite.setTexture(_data->assetManager.GetTexture("Menu BG"));
}


GameState_MainMenu::~GameState_MainMenu()
{
}

void GameState_MainMenu::Init()
{
}

void GameState_MainMenu::PollEvents()
{
	sf::Event e;

	while(_data->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			_data->window.close();
			break;
		}
	}
}

void GameState_MainMenu::Update(float dT)
{
	if (_playButton.Active)
		_data->stateMachine.AddState(ZEngine::StateRef(new GameState_Gameplay(_data)), true);

	if (_quitButton.Active)
		_data->window.close();


	_playButton.Update(dT);
	_quitButton.Update(dT);

	_testScale.Update(dT);
}

void GameState_MainMenu::Draw(float dT)
{
	_data->window.clear();

	_data->window.draw(_bgSprite);

	_playButton.Draw(dT);
	_quitButton.Draw(dT);

	_testScale.Draw(dT);
	
	_data->window.display();
}