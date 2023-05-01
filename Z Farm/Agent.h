#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>

#include "GameObject.h"

class PhysicsComponent;

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
		Agent(GameDataRef InData, b2World* InWorldRef);
		~Agent();

		virtual void Update(float dT) override;
		virtual void Draw() override;


		virtual void FlipSprite();

		virtual void Hit() = 0;
		virtual void Hit(sf::Vector2f playerPos) = 0;

		sf::RectangleShape hitbox;
		bool isFlipped;
		bool isMarked = false;

		void MarkForDeath() { isMarked = true; };

		class PhysicsComponent* GetPhysicsComponent() { return m_PhysicsComponent; }

		AgentType type;

		//b2Body* body = nullptr;

		b2World* worldRef = nullptr;

		int footContacts = 0;

	protected:
		class PhysicsComponent* m_PhysicsComponent;

	private:
	};


}
