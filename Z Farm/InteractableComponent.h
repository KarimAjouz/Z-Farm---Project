#pragma once

#include "PhysicsComponent.h"
#include "GameObject.h"

using namespace ZEngine;

class InteractableComponent :
	public PhysicsComponent
{
public:
	InteractableComponent(ZEngine::GameDataRef InData, b2World* InWorldRef);
	InteractableComponent(ZEngine::GameDataRef InData, b2World* InWorldRef, class GameObject* InGameObject, float InRadius);

	~InteractableComponent();

	virtual void Init() override;

	virtual void Update(float dT) override;

	virtual void InitPhysics() override;

	virtual void Interact();

protected:
	class GameObject* m_GameObject;

	float m_Radius;
};
