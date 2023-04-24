#pragma once

#include <box2d.h>
#include "Player.h"
#include "PhysicsComponent.h"

class ContactListener : public b2ContactListener
{
public:

    ContactListener(Player* player, Level* level);
    ~ContactListener();

    Player* playerRef;
    Level* levelRef;

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);


private:
    bool IsContact(ECollisionTag aTag, ECollisionTag bTag);
};

