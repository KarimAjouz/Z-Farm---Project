#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
namespace ZEngine
{

	class GameObject
	{
	public:
		GameObject();
		GameObject(GameDataRef InData);
		GameObject(sf::Vector2f InPosition, GameDataRef InData);

		//Constructor for a non-physics GameObject
		GameObject(sf::Vector2f InPosition, GameDataRef InData, std::string TextureName, std::string SpritePath);

		~GameObject();

		virtual void Update(float dT);
		virtual void Draw(sf::RenderWindow* InWindow);

		sf::Sprite* GetSprite() { return &m_Sprite; };

	protected:

		std::vector<class ObjectComponent*> _Components;
		ZEngine::GameDataRef m_data;
		sf::Sprite m_Sprite;
	};
}

