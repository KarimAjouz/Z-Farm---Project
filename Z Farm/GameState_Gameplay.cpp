#include "GameState_Gameplay.h"
#include "Definitions.h"
#include "Utilities.h"

#include "GameState_Shop.h"

#include <iostream>


/// <summary>
/// Creates the Gameplay Gamestate.
/// </summary>
/// <param name="data"></param>
GameState_Gameplay::GameState_Gameplay(ZEngine::GameDataRef data) :
	_data(data),
	_player(PLAYER_FILEPATH, sf::Vector2f(400.0f, 300.0f), data),
	_bullets(new std::vector<Bullet*>()),
	_zombies(new std::vector<Zombie*>()),
	_zombieSpawner(3.0f, true),
	_paused(false),
	zombits(0)
{
	_zombitsText.setFont(_data->assetManager.GetFont("Menu Button Font"));
	_zombitsText.setPosition(sf::Vector2f(50.0f, 20.0f));
	_zombitsText.setString("Zb: " + std::to_string(zombits));
	_zombitsText.setFillColor(sf::Color::White);

	_zombieSpawner.Start();
	_player.Init();

}


GameState_Gameplay::~GameState_Gameplay()
{
}

void GameState_Gameplay::Init()
{
}

/// <summary>
/// Handles Input Events.
/// </summary>
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
			case sf::Keyboard::I:
				_data->stateMachine.AddState(ZEngine::StateRef(new GameState_Shop(_data, &_player.gun)), false);
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


/// <summary>
/// Updates all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
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

/// <summary>
/// Draws all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Draw(float dT)
{
	_data->window.clear();

	_player.Draw(dT);

	_data->window.draw(_zombitsText);

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

/// <summary>
/// Updates all bullets.
/// </summary>
/// <param name="dT"></param>
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

/// <summary>
/// Draws all bullets.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::DrawBullets(float dT)
{
	for (int i = 0; i < _bullets->size(); i++)
	{
		_bullets->at(i)->Draw(dT);
	}
}

/// <summary>
/// Tests for collisions on all bullets.
/// </summary>
void GameState_Gameplay::CollideBullets()
{
	for (int b = 0; b < _bullets->size(); b++)
	{
		for (int z = 0; z < _zombies->size(); z++)
		{
			if (ZEngine::Utilities::CircleCollider(_bullets->at(b)->sprite, _zombies->at(z)->sprite))
			{
				_zombies->at(z)->DamageZombie(_bullets->at(b)->damage);
				_bullets->at(b)->MarkForDeath();
			}
		}
	}
}

/// <summary>
/// Spawns zombies based on a timer.
/// </summary>
void GameState_Gameplay::SpawnZombies()
{
	if (_zombieSpawner.Complete())
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

		_zombies->push_back(new Zombie(ZOMBIE_FILEPATH, spawnPos, _data, &_player));
	}
}

/// <summary>
/// Updates all of the zombies in the game.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::UpdateZombies(float dT)
{
	for (int i = 0; i < _zombies->size(); i++)
	{
		_zombies->at(i)->Update(dT);

		if (_zombies->at(i)->IsMarked())
		{
			zombits += 5;
			_zombitsText.setString("Zb: " + std::to_string(zombits));

			Zombie* zed = _zombies->at(i);
			_zombies->erase(_zombies->begin() + i);
			delete zed;
		}
	}
}

/// <summary>
/// Draws all of the zombies in the game.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::DrawZombies(float dT)
{
	for (int i = 0; i < _zombies->size(); i++)
		_zombies->at(i)->Draw(dT);
}

/// <summary>
/// Exits the game, clearing loaded memory.
/// </summary>
void GameState_Gameplay::Exit()
{
	delete _bullets;
	delete _zombies;
	_data->window.close();
}