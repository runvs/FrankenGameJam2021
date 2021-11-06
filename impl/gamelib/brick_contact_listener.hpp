#ifndef MYAWESOMEGAME_BRICK_CONTACT_LISTENER_HPP
#define MYAWESOMEGAME_BRICK_CONTACT_LISTENER_HPP

#include "Box2D/Box2D.h"

class BrickContactListener : public b2ContactListener {
public:
    BrickContactListener();
    virtual void BeginContact(b2Contact* contact) override;
};

#endif
