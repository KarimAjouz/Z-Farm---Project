#pragma once
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Timer.h"
#include "Zombie.h"

class GameState_Gameplay : public ZEngine::GameState
{
public:
	GameState_Gameplay(ZEngine::GameDataRef _data);
	~GameState_Gameplay();

	void Init();

	void PollEvents();
	void Update(float dT);
	void Draw(float dT);

	void Pause();
	void Resume();

	int zombits;

private:
	Player _player;

	ZEngine::GameDataRef _data;

	std::vector<Bullet*>* _bullets;
	std::vector<Zombie*>* _zombies;

	ZEngine::Timer _zombieSpawner;

	sf::Text _zombitsText;

	bool _paused;

	void UpdateBullets(float dT);
	void DrawBullets(float dT);
	void CollideBullets();


	void UpdateZombies(float dT);
	void DrawZombies(float dT);

	void SpawnZombies();

	void Exit();
};

