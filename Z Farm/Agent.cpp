#include "Agent.h"

#include "ObjectComponent.h"

namespace ZEngine
{
	Agent::Agent(GameDataRef InData, b2World* InWorldRef) :
		GameObject(InData, InWorldRef),
		isFlipped(false),
		type(AgentType::count)
	{
	}


	Agent::~Agent()
	{

	}

	void Agent::FlipSprite()
	{
		m_Sprite.setScale(m_Sprite.getScale().x * -1, m_Sprite.getScale().y);
		isFlipped = !isFlipped;
	}

	void Agent::Update(float dT)
	{
		for (ZEngine::ObjectComponent* Component : _Components)
		{
			Component->Update(dT);
		}
	}
	void Agent::Draw()
	{
		GameObject::Draw();
	}
}
