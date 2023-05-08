#pragma once

#include "TraversalState.h"

class AttackState
	:
	public TraversalState
{
public:
	virtual ~AttackState() override;
	virtual void Enter(Player& InPlayer) override;
	virtual void Exit(Player& InPlayer) override;

	virtual void Update(float dT, Player& InPlayer) override;
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent) override;

	virtual class Attack* GetCurrentSequenceItem();
private:
	std::vector<class Attack*>* m_AttackSequence;
	int m_SequenceIndex = 0;
	bool m_bIsNextAttackQueued = false;
	float m_RunningTime = 0.0f;
};
