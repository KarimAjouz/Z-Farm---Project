#include "GameState_Gameplay.h"
#include "Definitions.h"
#include "Utilities.h"

#include <iostream>



GameState_Gameplay::GameState_Gameplay(ZEngine::GameDataRef data) :
	_data(data),
	_player(PLAYER_FILEPATH, sf::Vector2f(300.0f, 300.0f), data),
	_bullets(new std::vector<Bullet*>()),
	_zombies(new std::vector<Zombie*>()),
	_zombieSpawner(3.0f, true),
	_paused(false)
{
	_zombieSpawner.Start();
}


GameState_Gameplay::~GameState_Gameplay()
{
}

void GameState_Gameplay::Init()
{
	_player.Init();
}

void GameState_Gameplay::PollEvents()
{
	sf::Event e;
	while (_data->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				Exit();
				break;
			case sf::Keyboard::P:
				if (_paused)
					Resume();
				else
					Pause();
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button == sf::Mouse::Left && !_paused)
				_player.gun.Shoot(_bullets, _data, _player.GetPosition());
			break;
		case sf::Event::Closed:
			Exit();
			break;
		}
	}
}

void GameState_Gameplay::Update(float dT)
{
	if (!_paused)
	{
		_player.Update(dT);
		SpawnZombies();
		UpdateZombies(dT);
		UpdateBullets(dT);
		CollideBullets();
	}
}

void GameState_Gameplay::Draw(float dT)
{
	_data->window.clear();

	_player.Draw(dT);

	DrawZombies(dT);
	DrawBullets(dT);

	_data->window.display();
}

void GameState_Gameplay::Pause()
{
	_paused = true;
}

void GameState_Gameplay::Resume()
{
	_paused = false;
}

void GameState_Gameplay::UpdateBullets(float dT)
{
	for (int i = 0; i < _bullets->size(); i++)
	{
		_bullets->at(i)->Update(dT);

		if (_bullets->at(i)->IsMarked())
		{
			Bullet* bul = _bullets->at(i);
			_bullets->erase(_bullets->begin() + i);
			delete bul;
		}
	}
}

void GameState_Gameplay::DrawBullets(float dT)
{
	for (int i = 0; i < _bullets->size(); i++)
	{
		_bullets->at(i)->Draw(dT);
	}
}


void GameState_Gameplay::CollideBullets()
{
	for (int b = 0; b < _bullets->size(); b++)
	{
		for (int z = 0; z < _zombies->size(); z++)
		{
			if (ZEngine::Utilities::CircleCollider(_bullets->at(b)->sprite, _zombies->at(z)->sprite))
			{
				_zombies->at(z)->DamageZombie(_bullets->at(b)->damage);
				_bullets->at(b)->MarkForDeath(true);
			}
		}
	}
}

void GameState_Gameplay::SpawnZombies()
{
	if (_zombieSpawner.Complete())
	{
		sf::Vector2f spawnPos = sf::Vector2f(ZEngine::Utilities::Random(0.0f, SCREEN_WIDTH), ZEngine::Utilities::Random(0.0f, SCREEN_HEIGHT));
		_zombies->push_back(new Zombie(ZOMBIE_FILEPATH, spawnPos, _data, &_player));
	}
}

void GameState_Gameplay::UpdateZombies(float dT)
{
	for (int i = 0; i < _zombies->size(); i++)
	{
		_zombies->at(i)->Update(dT);

		if (_zombies->at(i)->IsMarked())
		{
			Zombie* zed = _zombies->at(i);
			_zombies->erase(_zombies->begin() + i);
			delete zed;
		}
	}
}


void GameState_Gameplay::DrawZombies(float dT)
{
	for (int i = 0; i < _zombies->size(); i++)
		_zombies->at(i)->Draw(dT);
}

void GameState_Gameplay::Exit()
{
	_data->window.close();
	delete _bullets;
	delete _zombies;
}