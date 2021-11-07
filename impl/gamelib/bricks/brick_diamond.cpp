#include "brick_diamond.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "math_helper.hpp"

BrickDiamond::BrickDiamond(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickDiamond::doCreate()
{
    auto sprite = std::make_shared<jt::Sprite>();
    sprite->loadSprite("assets/brick_diamond.png");
    m_drawable = sprite;

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[4];
    vertices[0].Set(15.5f, 0.0f);
    vertices[1].Set(0.0f, 15.5f);
    vertices[2].Set(15.5f, 32.0f);
    vertices[3].Set(32.0f, 15.5f);
    int32 count = 4;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
