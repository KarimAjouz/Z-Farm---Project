#include "FootContactListener.h"

FootContactListener::FootContactListener(bool& ground) :
    grounded(ground)
{
}

FootContactListener::~FootContactListener()
{
}

void FootContactListener::BeginContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    int fixtureUserData = contact->GetFixtureA()->GetUserData().pointer;
    if (fixtureUserData == 3)
        grounded = true;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData().pointer;
    if ((int)fixtureUserData == 3)
        grounded = true;
}

void FootContactListener::EndContact(b2Contact* contact)
{
    //check if fixture A was the foot sensor
    int fixtureUserData = contact->GetFixtureA()->GetUserData().pointer;
    if (fixtureUserData == 3)
        grounded = false;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData().pointer;
    if ((int)fixtureUserData == 3)
        grounded = false;

}