#pragma once
#include "GameState_Gameplay.h"
#include "Game.h"
#include "Gun.h"

#include "Menu_Scale.h"
#include "ShopGunScale.h"

class GameState_Shop : public ZEngine::GameState
{

public:
	GameState_Shop(ZEngine::GameDataRef _data, GameState_Gameplay* gameplayStateRef, std::vector<ShopGunScale*>* scales);
	~GameState_Shop();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw();

private:
	ZEngine::GameDataRef _data;
	ZEngine::StateRef _gameplayState;

	Gun* _gun;
	int* _zombits;

	std::vector<ShopGunScale*>* _scales;

	sf::Sprite _bgSprite;
	sf::Text _zbitsText;

	ZEngine::Button _quitShopButton;

	void QuitShop();

};