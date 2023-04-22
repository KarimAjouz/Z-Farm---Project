#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>

#include "GameObject.h"

namespace ZEngine
{

	enum class AgentType
	{
		AT_Player,
		AT_AlarmPig,
		AT_Baldy,
		count
	};



	class Agent :
		public GameObject
	{
	public:
		Agent(GameDataRef InData);
		~Agent();

		virtual void Update(float dT) = 0;
		virtual void Draw() = 0;


		virtual void FlipSprite();

		virtual void Hit() = 0;
		virtual void Hit(sf::Vector2f playerPos) = 0;

		sf::RectangleShape hitbox;
		bool isFlipped;
		bool isMarked = false;

		void MarkForDeath() { isMarked = true; };

		AgentType type;

		//b2Body* body = nullptr;

		b2World* worldRef = nullptr;

		int footContacts = 0;

	private:
	};


}
