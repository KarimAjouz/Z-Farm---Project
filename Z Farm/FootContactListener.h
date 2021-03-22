#pragma once

#include <box2d.h>

class FootContactListener : public b2ContactListener
{
public:

    FootContactListener(bool& ground);
    ~FootContactListener();

    bool& grounded;

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);
};

