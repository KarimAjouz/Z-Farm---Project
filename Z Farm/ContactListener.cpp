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

    if (IsContact(CollisionTag::level, CollisionTag::enemyFoot))
    {
        if(fixtureAUserData == static_cast<int>(CollisionTag::enemyFoot))
            reinterpret_cast<Agent*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer)->footContacts++;
        else
            reinterpret_cast<Agent*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer)->footContacts++;
    }

    if (IsContact(CollisionTag::interactable, CollisionTag::playerFoot))
    {
        if (fixtureAUserData == static_cast<int>(CollisionTag::interactable))
        {
            playerRef->SetInteractable(reinterpret_cast<RopeSegment*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer));
            std::cout << "ROPESEGMENT SET FAM" << std::endl;

        }
        else
        {
            playerRef->SetInteractable(reinterpret_cast<RopeSegment*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer));
            std::cout << "ROPESEGMENT SET FAM" << std::endl;

        }

    }

    // Handles Spike Collisions with Player
    if (IsContact(CollisionTag::player, CollisionTag::spike))
        playerRef->Hit();
}

void ContactListener::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    fixtureAUserData = contact->GetFixtureA()->GetUserData().pointer;
    fixtureBUserData = contact->GetFixtureB()->GetUserData().pointer;


    if (IsContact(CollisionTag::playerFoot, CollisionTag::level) || IsContact(CollisionTag::playerFoot, CollisionTag::box))
        playerRef->footContacts--;


    if (IsContact(CollisionTag::level, CollisionTag::enemyFoot))
    {
        if (fixtureAUserData == static_cast<int>(CollisionTag::enemyFoot))
            reinterpret_cast<Agent*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer)->footContacts--;
        else
            reinterpret_cast<Agent*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer)->footContacts--;
    }

    if (IsContact(CollisionTag::interactable, CollisionTag::playerFoot))
    {
        if (fixtureAUserData == static_cast<int>(CollisionTag::interactable))
            playerRef->SetInteractable(nullptr);
        else
            playerRef->SetInteractable(nullptr);

        std::cout << "ROPESEGMENT UNSET FAM" << std::endl;
    }

    if (IsContact(CollisionTag::player, CollisionTag::room))
        playerRef->SetView();
}

bool ContactListener::IsContact(CollisionTag aTag, CollisionTag bTag)
{
    if (fixtureAUserData == static_cast<int>(aTag) && fixtureBUserData == static_cast<int>(bTag) || fixtureBUserData == static_cast<int>(aTag) && fixtureAUserData == static_cast<int>(bTag))
        return true;

    return false;
}