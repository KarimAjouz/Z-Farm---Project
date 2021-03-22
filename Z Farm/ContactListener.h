#pragma once

#include <box2d.h>
#include "Player.h"

class ContactListener : public b2ContactListener
{
public:

    ContactListener(Player* player);
    ~ContactListener();

    Player* playerRef;

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);
};

