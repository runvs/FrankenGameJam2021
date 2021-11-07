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
    m_drawable = std::make_shared<jt::Animation>();
    m_drawable->add("assets/gems/garnet.png", "idle", jt::Vector2u { 32, 32 }, { 0 }, 0.1f);
    m_drawable->add("assets/gems/garnet.png", "shine", jt::Vector2u { 32, 32 },
        { 0, 1, 2, 3, 4, 5, 6, 0 }, 0.1f);
    m_drawable->play("idle");
    m_drawable->setLooping(false);

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution() * 0.75f;

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
