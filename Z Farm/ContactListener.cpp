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
    if (IsContact(ECollisionTag::level, ECollisionTag::playerFoot))
        playerRef->footContacts++;
    else if (IsContact(ECollisionTag::box, ECollisionTag::playerFoot))
        playerRef->footContacts++;

    if (IsContact(ECollisionTag::level, ECollisionTag::enemyFoot))
    {
        if(fixtureAUserData == static_cast<int>(ECollisionTag::enemyFoot))
            reinterpret_cast<ZEngine::Agent*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer)->footContacts++;
        else
            reinterpret_cast<ZEngine::Agent*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer)->footContacts++;
    }

    /*if (IsContact(ECollisionTag::interactable, ECollisionTag::playerFoot))
    {
        if (fixtureAUserData == static_cast<int>(ECollisionTag::interactable))
        {
            playerRef->SetInteractable(reinterpret_cast<RopeSegment*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer));
            std::cout << "ROPESEGMENT SET FAM" << std::endl;

        }
        else
        {
            playerRef->SetInteractable(reinterpret_cast<RopeSegment*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer));
            std::cout << "ROPESEGMENT SET FAM" << std::endl;

        }

    }*/

    // Handles Spike Collisions with Player
    if (IsContact(ECollisionTag::player, ECollisionTag::spike))
        playerRef->Hit();
}

void ContactListener::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;


    if (IsContact(ECollisionTag::playerFoot, ECollisionTag::level) || IsContact(ECollisionTag::playerFoot, ECollisionTag::box))
        playerRef->footContacts--;


    if (IsContact(ECollisionTag::level, ECollisionTag::enemyFoot))
    {
        if (fixtureAUserData == static_cast<int>(ECollisionTag::enemyFoot))
            reinterpret_cast<ZEngine::Agent*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer)->footContacts--;
        else
            reinterpret_cast<ZEngine::Agent*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer)->footContacts--;
    }

   /* if (IsContact(ECollisionTag::interactable, ECollisionTag::playerFoot))
    {
        if (fixtureAUserData == static_cast<int>(ECollisionTag::interactable))
            playerRef->SetInteractable(nullptr);
        else
            playerRef->SetInteractable(nullptr);

        std::cout << "ROPESEGMENT UNSET FAM" << std::endl;
    }*/

    if (IsContact(ECollisionTag::player, ECollisionTag::room))
        playerRef->SetView();
}

bool ContactListener::IsContact(ECollisionTag aTag, ECollisionTag bTag)
{
    if (fixtureAUserData == static_cast<int>(aTag) && fixtureBUserData == static_cast<int>(bTag) || fixtureBUserData == static_cast<int>(aTag) && fixtureAUserData == static_cast<int>(bTag))
        return true;

    return false;
}