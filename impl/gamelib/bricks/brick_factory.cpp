#include "brick_factory.hpp"
#include "brick_quadratic.hpp"
#include "brick_rectangle2x1.hpp"
std::shared_ptr<BrickInterface> BrickFactory::createBrickQuadratic(
    std::shared_ptr<jt::Box2DWorldInterface> world)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.9f;
    bodyDef.angularDamping = 1.0f;
    bodyDef.position.Set(135, 20);
    return std::make_shared<BrickQuadratic>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickRectangle2x1(
    std::shared_ptr<jt::Box2DWorldInterface> world)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.9f;
    bodyDef.angularDamping = 1.0f;
    bodyDef.position.Set(135, 20);
    return std::make_shared<BrickRectangle2x1>(world, &bodyDef);
}
