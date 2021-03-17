#pragma once
#include "GameState.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Timer.h"
#include "Zombie.h"
#include "Pickup.h"
#include "Spawner.h"
#include "ShopGunScale.h"
#include "SaveDataManager.h"

#include <vector>

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
	SaveDataManager::SaveData _saveData;
	int zombits;
	int gameTier;
	Player player;


private:

	SaveDataManager _saveManager;


	ZEngine::GameDataRef _data;

	std::vector<Bullet*>* _bullets;
	std::vector<Zombie*>* _zombies;
	std::vector<Pickup*>* _pickups;
	std::vector<ShopGunScale*>* _shopScales;

	Spawner _zombieSpawner;

	sf::Text _zombitsText;


	bool _paused;

	void UpdateBullets(float dT);
	void DrawBullets();
	void CollideBullets();

	void UpdateZombies(float dT);
	void DrawZombies();
	void CollideZombies();

	void UpdatePickups(float dT);
	void DrawPickups();
	void CollidePickups();

	void CollidePlayerZombies();

	void InitShopScales();

	void RespawnPlayer();

	void Exit();
};

