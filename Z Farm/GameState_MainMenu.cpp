#include "GameState_MainMenu.h"
#include "Definitions.h"

#include "GameState_Gameplay.h"

GameState_MainMenu::GameState_MainMenu(ZEngine::GameDataRef data) :
	_data(data),
	_playButton("Play", _data, sf::Vector2f(400.0f, 300.0f), sf::Color::Red, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button"),
	_quitButton("Quit", _data, sf::Vector2f(400.0f, 400.0f), sf::Color::Red, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button")
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

	while (_data->GameWindow.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			_data->GameWindow.close();
			break;
		}
	}
}

void GameState_MainMenu::Update(float dT)
{
	if (_playButton.Active)
		_data->stateMachine.AddState(ZEngine::StateRef(new GameState_Gameplay(_data)), true);

	if (_quitButton.Active)
		_data->GameWindow.close();

	_playButton.Update(dT);
	_quitButton.Update(dT);
}

void GameState_MainMenu::Draw()
{
	_data->GameWindow.clear();

	_data->GameWindow.draw(_bgSprite);

	_playButton.Draw();
	_quitButton.Draw();

	_data->GameWindow.display();
}