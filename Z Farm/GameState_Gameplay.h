#pragma once
#include "GameState.h"

#include <vector>

#include "Game.h"
#include "Timer.h"
#include "SaveDataManager.h"

#include <box2d.h>

#include "Player.h"



class GameState_Gameplay : public ZEngine::GameState
{
public:
	GameState_Gameplay(ZEngine::GameDataRef _data);
	~GameState_Gameplay();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw();

	void Pause();
	void Resume();

	BalanceSheet balanceSheet;
	SaveDataManager::SaveData saveData;



private:

	b2Vec2 _gravity;
	b2World _world;

	SaveDataManager _saveManager;
	ZEngine::GameDataRef _data;

	Player _player;

	bool _paused;

	void Exit();

	void CreateGround(b2World& world, float x, float y);
	void CreateBox(b2World& World, int MouseX, int MouseY);

};

