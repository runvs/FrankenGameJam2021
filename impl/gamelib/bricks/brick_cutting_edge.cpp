#include "brick_cutting_edge.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "math_helper.hpp"

BrickCuttingEdge::BrickCuttingEdge(
    std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickCuttingEdge::doCreate()
{
    auto sprite = std::make_shared<jt::Sprite>();
    sprite->loadSprite("assets/brick_l.png");
    m_drawable = sprite;

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[5];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(0.0f, 16.0f);
    vertices[2].Set(16.0f, 16.0f);
    vertices[3].Set(16.0f, 8.0f);
    vertices[4].Set(8.0f, 0.0f);
    int32 count = 5;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}

void BrickCuttingEdge::doUpdate(float const elapsed)
{
    m_drawable->setPosition(getPosition());
    m_drawable->setRotation(-jt::MathHelper::rad2deg(getRotation()));
    m_drawable->update(elapsed);
}

void BrickCuttingEdge::doDraw() const { m_drawable->draw(getGame()->getRenderTarget()); }
