#pragma once
#include "GameState_Gameplay.h"
#include "Game.h"
#include "Gun.h"

#include "Menu_Scale.h"
#include "ShopGunScale.h"

class GameState_Shop : public ZEngine::GameState
{

public:
	GameState_Shop(ZEngine::GameDataRef _data, GameState_Gameplay* gameplayStateRef);
	~GameState_Shop();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw();

private:
	ZEngine::GameDataRef _data;
	ZEngine::StateRef _gameplayState;

	void QuitShop();

};