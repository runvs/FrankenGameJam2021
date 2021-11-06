#include "brick_factory.hpp"
#include "brick_cutting_edge.hpp"
#include "brick_diamond.hpp"
#include "brick_droplet.hpp"
#include "brick_hexagon.hpp"
#include "brick_octagon.hpp"
#include "brick_quadratic.hpp"
#include "brick_rectangle2x1.hpp"
#include "brick_triangle.hpp"
#include "math_helper.hpp"
#include "random.hpp"

std::shared_ptr<BrickInterface> BrickFactory::createBrickQuadratic(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickQuadratic>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickRectangle2x1(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickRectangle2x1>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickCuttingEdge(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickCuttingEdge>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickTriangle(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickTriangle>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickDroplet(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickDroplet>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickDiamond(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickDiamond>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickOctagon(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickOctagon>(world, &bodyDef);
}

std::shared_ptr<BrickInterface> BrickFactory::createBrickHexagon(
    std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef = getBodyDef(spawnPosition);
    return std::make_shared<BrickHexagon>(world, &bodyDef);
}

b2BodyDef BrickFactory::getBodyDef(jt::Vector2 const& spawnPosition)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = false;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.9f;
    bodyDef.angularDamping = 5.0f;
    bodyDef.position.Set(spawnPosition.x(), spawnPosition.y());
    bodyDef.angle = jt::Random::getFloat(0, jt::MathHelper::deg2rad(360.0f));
    return bodyDef;
}
