#pragma once
#include "TraversalState.h"

class GroundedState :
    public TraversalState
{
public:
    virtual ~GroundedState();
    virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InEvent) override;
    virtual void Update(float dT, Player& InPlayer) override;

    virtual void Enter(Player& InPlayer) override;
    virtual void Exit(Player& InPlayer) override;

private:
};

