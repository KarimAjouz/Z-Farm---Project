#include "GameState_Shop.h"

#include "Definitions.h"

GameState_Shop::GameState_Shop(ZEngine::GameDataRef data, GameState_Gameplay* gameplayState, std::vector<ShopGunScale*>* scales) :
	_data(data),
	_gun(&gameplayState->player.gun),
	_zombits(&gameplayState->zombits),
	_scales(scales),
	_quitShopButton("Exit Shop", _data, sf::Vector2f(600.0f, 500.0f), sf::Color::Black, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button")
{
	_data->assetManager.LoadTexture("Shop BG", SHOP_SCREEN_BACKGROUND_FILEPATH);
	_bgSprite.setTexture(_data->assetManager.GetTexture("Shop BG"));

	_zbitsText.setFont(_data->assetManager.GetFont("Menu Button Font"));
	_zbitsText.setPosition(sf::Vector2f(50.0f, 20.0f));
	_zbitsText.setString("Zb: " + std::to_string(*_zombits));
	_zbitsText.setFillColor(sf::Color::Red);

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
	if (_quitShopButton.Active)
		QuitShop();

	for (int i = 0; i < _scales->size(); i++)
	{
		_scales->at(i)->Update(dT);
	}

	_zbitsText.setString("Zb: " + std::to_string(*_zombits));


	_quitShopButton.Update(dT);
}

void GameState_Shop::Draw()
{
	_data->window.clear();

	_data->window.draw(_bgSprite);

	for (int i = 0; i < _scales->size(); i++)
	{
		_scales->at(i)->Draw();
	}

	_quitShopButton.Draw();
	_data->window.draw(_zbitsText);

	_data->window.display();
}

void GameState_Shop::QuitShop()
{
	_gun->bulletDamage = _scales->at(0)->GetValue();
	_gun->bulletSpeed = _scales->at(1)->GetValue();
	_gun->bulletsPerShot = _scales->at(2)->GetValue();
	_gun->bulletSpread = _scales->at(3)->GetValue();
	_gun->ammoCount = _scales->at(4)->GetValue();

	_data->stateMachine.RemoveState();
}