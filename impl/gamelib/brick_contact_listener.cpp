#include "brick_contact_listener.hpp"
#include <iostream>

BrickContactListener::BrickContactListener()
    : b2ContactListener()
{
}

void BrickContactListener::BeginContact(b2Contact* contact)
{
    std::cout << "Collision detected!" << std::endl;
}
