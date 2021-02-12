#include "GameState_Gameplay.h"
#include "Definitions.h"
#include "Utilities.h"
#include "math.h"

#include "GameState_Shop.h"

#include <iostream>


/// <summary>
/// Creates the Gameplay Gamestate.
/// </summary>
/// <param name="data"></param>
GameState_Gameplay::GameState_Gameplay(ZEngine::GameDataRef data) :
	_data(data),
	player(PLAYER_FILEPATH, sf::Vector2f(400.0f, 300.0f), data),
	_bullets(new std::vector<Bullet*>()),
	_zombies(new std::vector<Zombie*>()),
	_pickups(new std::vector<Pickup*>()),
	_shopScales(new std::vector<ShopGunScale*>()),
	_zombieSpawner(3.0f, true),
	_paused(false),
	zombits(10)
{
	_zombitsText.setFont(_data->assetManager.GetFont("Menu Button Font"));
	_zombitsText.setPosition(sf::Vector2f(50.0f, 20.0f));
	_zombitsText.setString("Zb: " + std::to_string(zombits));
	_zombitsText.setFillColor(sf::Color::White);

	InitShopScales();

	_zombieSpawner.Start();
	player.Init();
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
					_data->stateMachine.AddState(ZEngine::StateRef(new GameState_Shop(_data, this, _shopScales)), false);
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button == sf::Mouse::Left && !_paused)
				player.gun.Shoot(_bullets, _data, player.GetPosition());
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
		player.Update(dT);
		SpawnZombies();

		UpdatePickups(dT);
		CollidePickups();

		UpdateZombies(dT);
		CollideZombies();

		UpdateBullets(dT);
		CollideBullets();
	}
}

/// <summary>
/// Draws all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Draw()
{
	_data->window.clear();

	player.Draw();

	_data->window.draw(_zombitsText);

	DrawZombies();
	DrawBullets();
	DrawPickups();

	_data->window.display();
}

void GameState_Gameplay::Pause()
{
	_paused = true;
}

void GameState_Gameplay::Resume()
{
	_zombitsText.setString("Zb: " + std::to_string(zombits));
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
void GameState_Gameplay::DrawBullets()
{
	for (int i = 0; i < _bullets->size(); i++)
	{
		_bullets->at(i)->Draw();
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
/// Tests for collisions on zombies
/// </summary>
void GameState_Gameplay::CollideZombies()
{
	// For every zombie...
	for (int z1 = 0; z1 < _zombies->size(); z1++)
	{ 
		Zombie* zomA = _zombies->at(z1);

		// Test against every other zombie, ignoring tests that have already been conducted.
		for (int z2 = z1 + 1; z2 < _zombies->size(); z2++)
		{
			Zombie* zomB = _zombies->at(z2);

			// If they collide...
			if (ZEngine::Utilities::CircleCollider(zomA->sprite, zomB->sprite))
			{
				// Calculate overlapping distance.
				float overlap = ZEngine::Utilities::MinDist(zomA->sprite, zomB->sprite) - sqrt(ZEngine::Utilities::DistSq(zomA->sprite, zomB->sprite));

				// Calculate direction to move them.
				sf::Vector2f abVec = ZEngine::Utilities::NormaliseVector(zomB->sprite.getPosition() - zomA->sprite.getPosition());

				// Push them away from each other.
				zomA->CollideWithEntity(-abVec * (overlap / 2.0f));
				zomB->CollideWithEntity(abVec * (overlap / 2.0f));

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

		_zombies->push_back(new Zombie(ZOMBIE_FILEPATH, spawnPos, _data, &player));
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
			_pickups->push_back(new Pickup(1, PICKUP_FILEPATH, _zombies->at(i)->sprite.getPosition(), _data, _zombies->at(i)->sprite.getPosition() - player.sprite.getPosition()));


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
void GameState_Gameplay::DrawZombies()
{
	for (int i = 0; i < _zombies->size(); i++)
		_zombies->at(i)->Draw();
}


/// <summary>
/// Updates the Pickups.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::UpdatePickups(float dT)
{
	for (int i = 0; i < _pickups->size(); i++)
	{
		_pickups->at(i)->Update(dT);

		if (_pickups->at(i)->IsMarked())
		{
			Pickup* pic = _pickups->at(i);
			_pickups->erase(_pickups->begin() + i);
			delete pic;
		}
	}
}

/// <summary>
/// Handles collision between the player and the pickups.
/// </summary>
void GameState_Gameplay::CollidePickups()
{
	for (int i = 0; i < _pickups->size(); i++)
	{
		if (ZEngine::Utilities::CircleCollider(player.sprite, _pickups->at(i)->sprite))
		{
			zombits += _pickups->at(i)->Destroy(true);

			_zombitsText.setString("Zb: " + std::to_string(zombits));
		}
	}
}

/// <summary>
/// Draws Pickups
/// </summary>
void GameState_Gameplay::DrawPickups()
{
	for (int i = 0; i < _pickups->size(); i++)
		_pickups->at(i)->Draw();
}


void GameState_Gameplay::InitShopScales()
{
	_shopScales->push_back(new ShopGunScale("Damage", 1, 50, 1, player.gun.bulletDamage, sf::Vector2f(400.0f, 50.0f), _data, 1, 1, &zombits));
	_shopScales->push_back(new ShopGunScale("Speed", 1, 30, 1, player.gun.bulletSpeed, sf::Vector2f(400.0f, 100.0f), _data, 1, 1, &zombits));
	_shopScales->push_back(new ShopGunScale("Rounds Per Shot", 1, 10, 1, player.gun.bulletsPerShot, sf::Vector2f(400.0f, 150.0f), _data, 1, 1, &zombits));
	_shopScales->push_back(new ShopGunScale("Accuracy", 1, 30, 1, player.gun.bulletSpread, sf::Vector2f(400.0f, 200.0f), _data, 1, 1, &zombits));
	_shopScales->push_back(new ShopGunScale("Ammo Count", 1, 30, 1, player.gun.ammoCount, sf::Vector2f(400.0f, 250.0f), _data, 1, 1, &zombits));
}


/// <summary>
/// Exits the game, clearing loaded memory.
/// </summary>
void GameState_Gameplay::Exit()
{
	delete _bullets;
	delete _zombies;
	delete _pickups;
	delete _shopScales;

	_data->window.close();
}