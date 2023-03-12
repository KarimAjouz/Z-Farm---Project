#pragma once
#include "GameState.h"

#include <vector>

#include "Game.h"
#include "Timer.h"
#include "SaveDataManager.h"
#include "ContactListener.h"
#include "Tile.h"
#include "PhysicsDebugDraw.h"
#include "LevelBuilder.h"
#include "AlarmPig.h"
#include "SwordPickup.h"

#include <box2d.h>

#include "Spike.h"
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

	void SetViewCenter(sf::Vector2f newCenter) { _viewTarget = newCenter; }



private:
	b2Vec2 _gravity;
	b2World _world;

	SaveDataManager _saveManager;
	ZEngine::GameDataRef _data;


	PhysicsDebugDraw _debugDraw;
	bool _paused;

	bool _debugMode = false;

	Level* _level;
	ContactListener _contactListener;

	Player _player;

	SwordPickup _testSword;
	sf::Vector2f _viewTarget = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	void Exit();

	void CreateGround(b2World& world, float x, float y);

	void LerpView(float dT);

	void HandleKeyboardInputs(sf::Event* e);

	float physicsAccumulator = 0.0f;
};

