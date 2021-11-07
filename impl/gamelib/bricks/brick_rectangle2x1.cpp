#include "brick_rectangle2x1.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include <drawable_helpers.hpp>
#include <math_helper.hpp>

BrickRectangle2x1::BrickRectangle2x1(
    std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickRectangle2x1::doCreate()
{
    auto sprite = std::make_shared<jt::Sprite>();
    sprite->loadSprite("assets/brick_rect.png");
    m_drawable = sprite;

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity() * 0.75f;
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[4];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(0.0f, 32.0f);
    vertices[2].Set(16.0f, 32.0f);
    vertices[3].Set(16.0f, 0.0f);
    int32 count = 4;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
