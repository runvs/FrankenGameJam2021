#include "brick_interface.hpp"


BrickInterface::BrickInterface(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : Box2DObject(world, def)
{
}
