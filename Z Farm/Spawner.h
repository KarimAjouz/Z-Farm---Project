#pragma once

#include "Timer.h"
#include "Zombie.h"
#include <vector>


class Spawner
{
public:
	
	Spawner(float spawnTimer, ZEngine::GameDataRef data, Player* playerRef, std::vector<Zombie*>* zombies);
	~Spawner();


	void Update(float dT);


private:
	ZEngine::Timer _timer;
	ZEngine::GameDataRef _data;
	Player* _playerRef;

	std::vector<Zombie*>* _zombieList;
	float _spawnTime;


	void Spawn();



};

