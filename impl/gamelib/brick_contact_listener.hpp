#ifndef MYAWESOMEGAME_BRICK_CONTACT_LISTENER_HPP
#define MYAWESOMEGAME_BRICK_CONTACT_LISTENER_HPP

#include "Box2D/Box2D.h"
#include <functional>
#include <vector>

class BrickContactListener : public b2ContactListener {
public:
    BrickContactListener();
    virtual void BeginContact(b2Contact* contact) override;

    void addContactCallback(std::function<void(b2Body*, b2Body*)> cb);

private:
    std::vector<std::function<void(b2Body*, b2Body*)>> m_callbacks;
};

#endif
