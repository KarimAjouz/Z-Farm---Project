#pragma once

#include "Game.h"
#include "box2d.h"
#include <SFML/Graphics.hpp>
namespace ZEngine
{

	class GameObject
	{
	public:
		GameObject();
		GameObject(GameDataRef InData);
		GameObject(GameDataRef InData, sf::Vector2f InPosition, class b2World* InWorldRef);

		//Constructor for a non-physics GameObject
		GameObject(sf::Vector2f InPosition, GameDataRef InData, std::string TextureName, std::string SpritePath);

		~GameObject();

		virtual void Update(float dT);
		virtual void Draw();


		virtual void Hit();

		sf::Sprite* GetSprite() { return &m_Sprite; };

	protected:

		std::vector<class ObjectComponent*> _Components;
		ZEngine::GameDataRef m_Data;
		class b2World* m_WorldRef;
		sf::Sprite m_Sprite;
	};
}

