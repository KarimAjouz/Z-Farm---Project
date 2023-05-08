#include "Box.h"
#include "Definitions.h"
#include "PhysicsComponent.h"

#include <iostream>

Box::Box(ZEngine::GameDataRef data, b2World* world, sf::Vector2f pos) :
	Obstacle::Obstacle(data, pos, world),
	_data(data)

{
	_data->assetManager.LoadTexture("Box", BOX_OBSTACLE);
	_data->assetManager.LoadTexture("BoxHit", BOX_OBSTACLE_HIT);

	m_Sprite.setTexture(_data->assetManager.GetTexture("Box"));
	m_Sprite.setPosition(pos);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, 22, 16));
	m_Sprite.setOrigin(11, 8);
	m_Sprite.setScale(1, 1);

	m_Hitbox.setPosition(m_Sprite.getPosition());
	m_Hitbox.setSize(sf::Vector2f(11, 8) * m_Sprite.getScale().x);
	m_Hitbox.setOrigin(11, 8);
	m_Hitbox.setScale(m_Sprite.getScale());

	type = Obstacle::Type::box;

	m_PhysicsComponent->MakeAsBoxBody(
		pos,
		sf::IntRect(0, 0, m_Hitbox.getSize().x, m_Hitbox.getSize().y),
		nullptr,
		true,
		false,
		EEntityCategory::OBSTACLES,
		EEntityCategory::LEVEL
		| EEntityCategory::OBSTACLES
		| EEntityCategory::AGENTS
		| EEntityCategory::DAMAGE
		| EEntityCategory::INTERACTOR
	);

	m_PhysicsComponent->SetBodyUserData(this, ECollisionTag::CT_Box);
}

Box::~Box()
{
	//worldRef->DestroyBody(body);
}

void Box::Update(float dT)
{
	if (!_shattered)
	{
		m_Sprite.setPosition(sf::Vector2f(m_PhysicsComponent->GetBody()->GetPosition().x * SCALE, m_PhysicsComponent->GetBody()->GetPosition().y * SCALE));
		m_Hitbox.setPosition(m_Sprite.getPosition());
	}
	else
	{
		for (int i = 0; i < m_Fragments.size(); i++)
		{
			m_Fragments[i].Update(dT);
		}
	}
}

void Box::Draw()
{
	if (!_shattered)
		Obstacle::Draw();

	else
	{
		for (int i = 0; i < m_Fragments.size(); i++)
		{
			m_Fragments[i].Draw();
		}
	}
}

void Box::InitPhysics()
{
	//Obstacle::InitPhysics(sf::IntRect(0, 0, 22, 16), true, true, worldRef);
}

void Box::Shatter(sf::Vector2f InDamageSourcePos)
{
	m_WorldRef->DestroyBody(m_PhysicsComponent->GetBody());

	sf::Vector2f forceDir = m_Sprite.getPosition() - InDamageSourcePos;

	std::cout << "Box::Shatter --> ForceDir = (" << std::to_string(forceDir.x) << ", " << std::to_string(forceDir.y) << ")" << std::endl;

	sf::IntRect texRect = sf::IntRect(0, 0, 8, 7);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(0, 7, 6, 9);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(6, 7, 9, 9);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(8, 0, 7, 7);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(15, 0, 6, 7);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	texRect = sf::IntRect(15, 7, 6, 9);
	m_Fragments.push_back(Fragment(_data, m_WorldRef, texRect, sf::Vector2f(m_Sprite.getPosition().x + texRect.left, m_Sprite.getPosition().y + texRect.top), forceDir));

	_shattered = true;
}

void Box::Hit()
{
	if (!_shattered)
		Shatter(m_Sprite.getPosition());
}

void Box::Hit(sf::Vector2f InDamageSourcePos)
{
	if (!_shattered)
		Shatter(InDamageSourcePos);
}