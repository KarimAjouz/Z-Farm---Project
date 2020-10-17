#pragma once
#include "Bullet.h"
#include "Timer.h"
#include "ResourceBar.h"
#include "Definitions.h"

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class Gun
{
public:
	Gun(ZEngine::GameDataRef data);
	~Gun();

	void Shoot(std::vector<Bullet*>* bullets, ZEngine::GameDataRef data, sf::Vector2f pos);

	int bulletDamage;
	int bulletSpeed;
	int bulletsPerShot;
	int bulletSpread;
	int ammoCount;
	int bulletsRemaining;

	void Reload();

	void Update(float dT);
	void Draw(float dT);
	
	void DrawAmmoCount();
	void DrawReloadBar(float dT);

private:
	sf::Vector2f _pos;
	bool _reloading;

	ZEngine::ResourceBar _reloadBar;

	ZEngine::GameDataRef _data;

	ZEngine::Timer _reloadTimer;
};

