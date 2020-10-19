#pragma once
#include "GameState.h"
#include "Game.h"

class GameState_Shop : public ZEngine::GameState
{

public:
	GameState_Shop(ZEngine::GameDataRef _data);
	~GameState_Shop();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw(float dT);

private:
	ZEngine::GameDataRef _data;

};

