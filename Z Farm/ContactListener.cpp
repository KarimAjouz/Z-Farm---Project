#include "ContactListener.h"

ContactListener::ContactListener(Player* player, Level* level) :
    playerRef(player),
    levelRef(level)
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    // Get the fixture tags.
    fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;

    // Handles grounding the player.
    if (IsContact(CollisionTag::level, CollisionTag::playerFoot))
        playerRef->footContacts++;
    else if (IsContact(CollisionTag::box, CollisionTag::playerFoot))
        playerRef->footContacts++;

    // Handles Spike Collisions with Player
    if (IsContact(CollisionTag::player, CollisionTag::spike))
        playerRef->Hit();

    // Handles Spike Collisions with enemies.
    if (IsContact(CollisionTag::enemy, CollisionTag::spike))
        levelRef->SpikeAgents();
}

void ContactListener::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;


    if (IsContact(CollisionTag::playerFoot, CollisionTag::level) || IsContact(CollisionTag::playerFoot, CollisionTag::box))
        playerRef->footContacts--;

    if (IsContact(CollisionTag::player, CollisionTag::room))
        playerRef->SetView();
}

bool ContactListener::IsContact(CollisionTag aTag, CollisionTag bTag)
{
    if (fixtureAUserData == static_cast<int>(aTag) && fixtureBUserData == static_cast<int>(bTag) || fixtureBUserData == static_cast<int>(aTag) && fixtureAUserData == static_cast<int>(bTag))
        return true;

    return false;
}