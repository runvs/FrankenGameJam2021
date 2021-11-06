#ifndef MYAWESOMEGAME_BRICK_INTERFACE_HPP
#define MYAWESOMEGAME_BRICK_INTERFACE_HPP

#include "box2d_object.hpp"

class BrickInterface : public jt::Box2DObject
{
public:
    BrickInterface(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);
    virtual ~BrickInterface() = default;

};

#endif // MYAWESOMEGAME_BRICK_INTERFACE_HPP
