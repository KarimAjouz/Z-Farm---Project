#pragma once
#include "GameState.h"
#include "Game.h"
#include "Gun.h"

#include "Menu_Scale.h"

class GameState_Shop : public ZEngine::GameState
{

public:
	GameState_Shop(ZEngine::GameDataRef _data, Gun* g);
	~GameState_Shop();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw();

private:
	ZEngine::GameDataRef _data;
	ZEngine::StateRef _gameplayState;

	Gun* _gun;

	sf::Sprite _bgSprite;

	ZEngine::Menu_Scale _damageScale;
	ZEngine::Menu_Scale _speedScale;
	ZEngine::Menu_Scale _numPerShotScale;
	ZEngine::Menu_Scale _spreadScale;
	ZEngine::Menu_Scale _ammoCountScale;

	ZEngine::Button _quitShopButton;

	void QuitShop();

	/*
	int bulletDamage;
	int bulletSpeed;
	int bulletsPerShot;
	int bulletSpread;
	int ammoCount;
	*/

};

