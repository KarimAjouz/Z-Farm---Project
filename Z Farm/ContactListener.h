#pragma once

#include <box2d.h>
#include "Player.h"

class ContactListener : public b2ContactListener
{
public:

    ContactListener(Player* player, Level* level);
    ~ContactListener();

    Player* playerRef;
    Level* levelRef;

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    int fixtureAUserData = 0;
    int fixtureBUserData = 0;

private:
    bool IsContact(CollisionTag aTag, CollisionTag bTag);
};

