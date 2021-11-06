#include "brick_contact_listener.hpp"
#include <iostream>

BrickContactListener::BrickContactListener(/*std::function<void(b2Body*, b2Body*)> callback*/)
    : b2ContactListener()
{
    // TODO: We get pointers to the bodies of the collidees, so we need backwards resolution.
    // StateGame should do that, I think.

    // TODO: Callback like in TT: tell StateGame that these two pointers have collided.
    // StateGame will set them to "collided" and, in its update loop, check for low speed and
    // certain age to solidify.
}

void BrickContactListener::BeginContact(b2Contact* contact)
{
    std::cout << "Collision detected between " << contact->GetFixtureA()->GetBody() << " and "
              << contact->GetFixtureB()->GetBody() << std::endl;
    // TODO: Call callback with the two body ptrs
}
