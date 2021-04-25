#include "Box.h"
#include "Definitions.h"

Box::Box(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos) :
	_data(data)
{
	_data->assetManager.LoadTexture("Box", BOX_OBSTACLE);
	_data->assetManager.LoadTexture("BoxHit", BOX_OBSTACLE_HIT);
	worldRef = world;

	sprite.setTexture(_data->assetManager.GetTexture("Box"));
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(0, 0, 22, 16));
	sprite.setOrigin(11, 8);
	sprite.setScale(2, 2);
	

	hitbox.setPosition(sprite.getPosition());
	hitbox.setSize(sf::Vector2f(22, 16));
	hitbox.setOrigin(11, 8);
	hitbox.setScale(sprite.getScale());

	type = Obstacle::Type::box;

	InitPhysics();
}


Box::~Box()
{
	worldRef->DestroyBody(body);
}

void Box::Update(float dT)
{
	if (!_shattered)
	{
		sprite.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y) * SCALE);
		hitbox.setPosition(sprite.getPosition());
	}
	else
	{
		for (int i = 0; i < _fragments.size(); i++)
		{
			_fragments[i].Update(dT);
		}
	}
}

void Box::Draw()
{
	if(!_shattered)
		_data->window.draw(sprite);
	else
	{
		for (int i = 0; i < _fragments.size(); i++)
		{
			_fragments[i].Draw();
		}
	}
}

void Box::InitPhysics()
{
	Obstacle::InitPhysics(sf::IntRect(0, 0, 22, 16), true, true, worldRef);
	body->GetFixtureList()->GetUserData().pointer = static_cast<int>(CollisionTag::box);
}

void Box::Shatter(sf::Vector2f playerPos)
{
	worldRef->DestroyBody(body);

	sf::Vector2f forceDir = sprite.getPosition() - playerPos;

	sf::IntRect texRect = sf::IntRect(0, 0, 8, 7);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(0, 7, 6, 9);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(6, 7, 9, 9);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));
	
	texRect = sf::IntRect(8, 0, 7, 7);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(15, 0, 6, 7);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));
	
	texRect = sf::IntRect(15, 7, 6, 9);
	_fragments.push_back(Fragment(_data, worldRef, texRect, sf::Vector2f(sprite.getPosition().x + texRect.left, sprite.getPosition().y + texRect.top), forceDir));

	_shattered = true;
}

void Box::Hit(sf::Vector2f playerPos)
{
	if(!_shattered)
		Shatter(playerPos);
}

void Box::Hit()
{
}
