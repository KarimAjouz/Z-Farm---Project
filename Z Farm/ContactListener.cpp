#include "ContactListener.h"

ContactListener::ContactListener(Player* player) :
    playerRef(player)
{
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    int fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    int fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;

    if (fixtureAUserData == static_cast<int>(CollisionTag::playerFoot) && fixtureBUserData == static_cast<int>(CollisionTag::level))
        playerRef->footContacts++;
    else if (fixtureBUserData == static_cast<int>(CollisionTag::playerFoot) && fixtureAUserData == static_cast<int>(CollisionTag::level))
        playerRef->footContacts++;

}

void ContactListener::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    int fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    int fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;
    if (fixtureAUserData == static_cast<int>(CollisionTag::playerFoot) && fixtureBUserData == static_cast<int>(CollisionTag::level))
        playerRef->footContacts--;
    else if (fixtureBUserData == static_cast<int>(CollisionTag::playerFoot) && fixtureAUserData == static_cast<int>(CollisionTag::level))
        playerRef->footContacts--;
}