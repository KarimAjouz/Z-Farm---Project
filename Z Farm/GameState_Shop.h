#pragma once
#include "GameState.h"
#include "Game.h"
#include "Gun.h"

#include "Menu_Scale.h"
#include "ShopGunScale.h"

class GameState_Shop : public ZEngine::GameState
{

public:
	GameState_Shop(ZEngine::GameDataRef _data, Gun* g, int* zombits);
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

	sf::Sprite _bgSprite;

	ShopGunScale _damageScale;
	ShopGunScale _speedScale;
	ShopGunScale _numPerShotScale;
	ShopGunScale _spreadScale;
	ShopGunScale _ammoCountScale;

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

