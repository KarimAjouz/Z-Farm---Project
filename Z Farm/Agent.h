#pragma once
#include <SFML/Graphics.hpp>
#include <box2d.h>

#include "GameObject.h"

class PhysicsComponent;
class EquipmentComponent;

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

		PhysicsComponent* GetPhysicsComponent() { return m_PhysicsComponent; }
		EquipmentComponent* GetEquipmentComponent() { return m_EquipmentComponent; }

		AgentType type;

		//b2Body* body = nullptr;

		b2World* worldRef = nullptr;

		int footContacts = 0;

	protected:
		PhysicsComponent* m_PhysicsComponent;
		EquipmentComponent* m_EquipmentComponent;

	private:
	};
}
