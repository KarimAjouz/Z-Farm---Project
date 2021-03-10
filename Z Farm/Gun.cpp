#include "Gun.h"

#include "Utilities.h"

#include <iostream>


/// <summary>
/// The constructor for the players gun.
/// </summary>
/// <param name="data"> A reference to the game data. </param>
Gun::Gun(ZEngine::GameDataRef data, SaveDataManager::SaveData saveData, BalanceSheet* b) :
	_reloadTimer(5.0f, false),
	bulletSpeed(b->speed.at(saveData.speedIndex).value),
	bulletSpread(b->spread.at(saveData.spreadIndex).value),
	bulletDamage(b->damage.at(saveData.damIndex).value),
	bulletsPerShot(b->roundsPerShot.at(saveData.bulletsPerShotIndex).value),
	ammoCount(b->ammoCount.at(saveData.ammoCountIndex).value),
	_reloadBar(data, UI_RELOADBAR, "Ammobar", sf::Vector2f(SCREEN_WIDTH - 124.0f, 48)),
	_reloading(false),
	_data(data)
{
	bulletsRemaining = ammoCount;
	_data->assetManager.LoadTexture("Bullet", BULLET_FILEPATH);
}


Gun::~Gun()
{
}


/// <summary>
/// Update loop for the gun.
/// </summary>
/// <param name="dT"></param>
void Gun::Update(float dT)
{
	if (_reloading)
	{
		if (_reloadTimer.Complete())
		{
			_reloading = false;
			bulletsRemaining = ammoCount;
		}
		else
		{
			_reloadBar.ResizeForeground(1.0f - _reloadTimer.GetPercentageRemaining());
		}
	}
	else if (bulletsRemaining < ammoCount)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
			Reload();
	}
}

void Gun::Draw()
{
	DrawAmmoCount();

	if (_reloading)
		DrawReloadBar();
}

/// <summary>
/// Fires the gun, spawning a number of bullets with randomised spread. 
/// </summary>
/// <param name="_bullets"> A pointer to the vector of bullets to spawn the bullets into. </param>
/// <param name="data"> Reference to the game data. </param>
/// <param name="pos"> Sets the position to spawn the bullet in. </param>
void Gun::Shoot(std::vector<Bullet*>* _bullets, ZEngine::GameDataRef data, sf::Vector2f pos)
{
	if (!_reloading && bulletsRemaining > 0)
	{
		sf::Vector2f target = static_cast<sf::Vector2f>(sf::Mouse::getPosition(data->window));

		float spreadRad = (20 - bulletSpread) * 10 / 4;
		float distanceMult = sqrt((target.x - pos.x) * (target.x - pos.x) + (target.y - pos.y) * (target.y - pos.y)) / 200.0f;

		spreadRad *= distanceMult;

		for (int i = 0; i < bulletsPerShot; i++)
		{
			if (bulletsRemaining > 0)
			{
				target.x += ZEngine::Utilities::Random(-spreadRad, spreadRad);
				target.y += ZEngine::Utilities::Random(-spreadRad, spreadRad);

				Bullet* b = new Bullet(data, pos, target, bulletSpeed, bulletDamage);
				_bullets->push_back(b);
				bulletsRemaining--;
			}
		}
	}
}

/// <summary>
/// Sets the reloading flag to true, also starts the reload timer.
/// </summary>
void Gun::Reload()
{
	if (!_reloading)
	{
		_reloadTimer.Start();
		_reloading = true;
	}
}

/// <summary>
/// Draws the number of rounds remaining in the gun.
/// </summary>
void Gun::DrawAmmoCount()
{
	sf::Vector2f ammoCountPosition = sf::Vector2f(SCREEN_WIDTH - 24, 24);
	for (int i = 0; i < bulletsRemaining; i++)
	{
		sf::Sprite b;
		b.setTexture(_data->assetManager.GetTexture("Bullet"));
		b.setPosition(ammoCountPosition);

		_data->window.draw(b);

		ammoCountPosition.x -= 16.0f;
	}
}

/// <summary>
/// Draws the reload bar.
/// </summary>
void Gun::DrawReloadBar()
{
	_reloadBar.Draw();
}