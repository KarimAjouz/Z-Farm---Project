#include "Spawner.h"
#include "Utilities.h"


Spawner::Spawner(float spawnTime, ZEngine::GameDataRef data, Player* playerRef, std::vector<Zombie*>* zombies) :
	_spawnTime(spawnTime),
	_data(data),
	_playerRef(playerRef),
	_timer(spawnTime, true),
	_zombieList(zombies)
{
	_timer.Start();
}

Spawner::~Spawner()
{
}

void Spawner::Update(float dT)
{
	Spawn();
}

void Spawner::Spawn()
{
	if (_timer.Complete())
	{
		sf::Vector2f spawnPos = sf::Vector2f(0.0f, 0.0f);

		// 50/50 chance of spawning either NS/EW
		if (ZEngine::Utilities::Random(0.0f, 1.0f) > 0.5f)
		{
			// Spawns North/South
			if (ZEngine::Utilities::Random(0.0f, 1.0f) > 0.5f)
				spawnPos = sf::Vector2f(ZEngine::Utilities::Random(0.0f, SCREEN_WIDTH), SCREEN_HEIGHT + 32.0f);
			else
				spawnPos = sf::Vector2f(ZEngine::Utilities::Random(0.0f, SCREEN_WIDTH), 0 - 32.0f);
		}
		else
		{
			// Spawns East/West
			if (ZEngine::Utilities::Random(0.0f, 1.0f) > 0.5f)
				spawnPos = sf::Vector2f(SCREEN_WIDTH + 32.0f, ZEngine::Utilities::Random(0.0f, SCREEN_WIDTH));
			else
				spawnPos = sf::Vector2f(0 - 32.0f, ZEngine::Utilities::Random(0.0f, SCREEN_WIDTH));
		}

		_zombieList->push_back(new Zombie(ZOMBIE_FILEPATH, spawnPos, _data, _playerRef));
	}
}
