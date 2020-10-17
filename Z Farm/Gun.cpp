#include "Gun.h"

#include "Utilities.h"

#include <iostream>



Gun::Gun(ZEngine::GameDataRef data) :
	_reloadTimer(3.0f, false),
	bulletSpeed(500.0f),
	bulletSpread(15.0f),
	bulletDamage(20.0f),
	bulletsPerShot(3),
	ammoCount(30),
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

void Gun::Shoot(std::vector<Bullet*>* _bullets, ZEngine::GameDataRef data, sf::Vector2f pos)
{
	if (!_reloading && bulletsRemaining > 0)
	{
		sf::Vector2f target = static_cast<sf::Vector2f>(sf::Mouse::getPosition(data->window));

		float spreadRad = bulletSpread * 10 / 2;

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

void Gun::Reload()
{
	if (!_reloading)
	{
		_reloadTimer.Start();
		_reloading = true;
	}
}

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

void Gun::Draw(float dT)
{
	DrawAmmoCount();

	if (_reloading)
		DrawReloadBar(dT);
}

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

void Gun::DrawReloadBar(float dT)
{
	_reloadBar.Draw(dT);
}