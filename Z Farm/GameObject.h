#pragma once

#include "Game.h"
#include "box2d.h"
#include <SFML/Graphics.hpp>

struct PhysicsUserData;
enum ECollisionTag;

namespace ZEngine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject(GameDataRef InData, class b2World* InWorldRef);
		GameObject(GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef);

		//Constructor for a non-physics GameObject
		GameObject(sf::Vector2f InPosition, GameDataRef InData, std::string TextureName, std::string SpritePath);

		~GameObject();

		virtual void Update(float dT);
		virtual void Draw();


		virtual void Hit();
		virtual void Hit(sf::Vector2f InDamageSourcePos);

		virtual void HandleContactBegin(PhysicsUserData* InCollidingUserData, ECollisionTag InMyCollidedFixture) {};
		virtual void HandleContactEnd(PhysicsUserData* InCollidingUserData, ECollisionTag InMyCollidedFixture) {};

		sf::Sprite* GetSprite() { return &m_Sprite; };

		ZEngine::GameDataRef GetData() { return m_Data; };
		b2World* GetWorldRef() { return m_WorldRef; };


	protected:

		std::vector<class ObjectComponent*> _Components;
		ZEngine::GameDataRef m_Data;
		class b2World* m_WorldRef;
		sf::Sprite m_Sprite;

		sf::RectangleShape m_Hitbox;
	};
}

