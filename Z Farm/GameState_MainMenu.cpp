#include "GameState_MainMenu.h"
#include "Definitions.h"


#include "GameState_Gameplay.h"




GameState_MainMenu::GameState_MainMenu(ZEngine::GameDataRef data) :
	_data(data),
	_playButton("Play", _data, sf::Vector2f(400.0f, 300.0f), sf::Color::Red, ZEngine::Button::Type::loadScene),
	_quitButton("Quit", _data, sf::Vector2f(400.0f, 400.0f), sf::Color::Red, ZEngine::Button::Type::quit)
{
	_data->assetManager.LoadTexture("Menu BG", MENU_SCREEN_BACKGROUND_FILEPATH);

	std::string buttonFilePath = static_cast<std::string>(BUTTON_FOLDER_FILEPATH);

	_data->assetManager.LoadTexture("Button Default", buttonFilePath + "Default.png");
	_data->assetManager.LoadTexture("Button Hovered", buttonFilePath + "Hovered.png");
	_data->assetManager.LoadTexture("Button Clicked", buttonFilePath + "Clicked.png");
	_data->assetManager.LoadFont("Button Font", buttonFilePath + "Font.ttf");

	_bgSprite.setTexture(_data->assetManager.GetTexture("Menu BG"));
}


GameState_MainMenu::~GameState_MainMenu()
{
}

void GameState_MainMenu::Init()
{
	_playButton.Init();
	_quitButton.Init();
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
		case sf::Event::MouseButtonPressed:
			if (_data->inputManager.IsSpriteClicked(_playButton.sprite, _data->window))
				_playButton.Engaged = true;
			if (_data->inputManager.IsSpriteClicked(_quitButton.sprite, _data->window))
				_quitButton.Engaged = true;
			break;
		case sf::Event::MouseButtonReleased:

			if (_data->inputManager.IsSpriteReleased(_playButton.sprite, _data->window) && _playButton.Engaged)
				_data->stateMachine.AddState(ZEngine::StateRef(new GameState_Gameplay(_data)), true);
			else
				_playButton.Engaged = false;

			if (_data->inputManager.IsSpriteReleased(_quitButton.sprite, _data->window) && _quitButton.Engaged)
				_data->window.close();
			else
				_quitButton.Engaged = false;

			break;
		}
	}
}

void GameState_MainMenu::Update(float dT)
{
	_playButton.Update(dT);
	_quitButton.Update(dT);
}

void GameState_MainMenu::Draw(float dT)
{
	_data->window.clear();

	_data->window.draw(_bgSprite);

	_playButton.Draw(dT);
	_quitButton.Draw(dT);
	
	_data->window.display();
}