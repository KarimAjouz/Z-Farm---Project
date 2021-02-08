#include "GameState_Shop.h"

#include "GameState_Gameplay.h"

#include "Definitions.h"

GameState_Shop::GameState_Shop(ZEngine::GameDataRef data, Gun* g) :
	_data(data),
	_gun(g),
	_damageScale("Damage", 1, 30, 1, _gun->bulletDamage, sf::Vector2f(400.0f, 50.0f), _data),
	_speedScale("Speed", 1, 30, 1, _gun->bulletSpeed, sf::Vector2f(400.0f, 100.0f), _data),
	_numPerShotScale("Rounds Per Shot", 1, 10, 1, _gun->bulletsPerShot, sf::Vector2f(400.0f, 150.0f), _data),
	_spreadScale("Spread", 1, 30, 1, _gun->bulletSpread, sf::Vector2f(400.0f, 200.0f), _data),
	_ammoCountScale("Ammo Count", 1, 30, 1, _gun->ammoCount, sf::Vector2f(400.0f, 250.0f), _data),
	_quitShopButton("Exit Shop", _data, sf::Vector2f(600.0f, 500.0f), sf::Color::Black, MENU_BUTTON_FOLDER_FILEPATH, "Menu Button")
{
	_data->assetManager.LoadTexture("Shop BG", SHOP_SCREEN_BACKGROUND_FILEPATH);
	_bgSprite.setTexture(_data->assetManager.GetTexture("Shop BG"));
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
				_data->window.close();
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

	_damageScale.Update(dT);
	_speedScale.Update(dT);
	_numPerShotScale.Update(dT);
	_spreadScale.Update(dT);
	_ammoCountScale.Update(dT);

	_quitShopButton.Update(dT);
}

void GameState_Shop::Draw()
{
	_data->window.clear();

	_data->window.draw(_bgSprite);

	_damageScale.Draw();
	_speedScale.Draw();
	_numPerShotScale.Draw();
	_spreadScale.Draw();
	_ammoCountScale.Draw();

	_quitShopButton.Draw();

	_data->window.display();
}

void GameState_Shop::QuitShop()
{
	_gun->bulletDamage = _damageScale.GetValue();
	_gun->bulletSpeed = _speedScale.GetValue();
	_gun->bulletsPerShot = _numPerShotScale.GetValue();
	_gun->bulletSpread = _spreadScale.GetValue();
	_gun->ammoCount = _ammoCountScale.GetValue();


	_data->stateMachine.RemoveState();
}