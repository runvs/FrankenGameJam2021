#include "brick_octagon.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "math_helper.hpp"

BrickOctagon::BrickOctagon(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickOctagon::doCreate()
{
    m_drawable = std::make_shared<jt::Animation>();
    m_drawable->add("assets/gems/citrin.png", "idle", jt::Vector2u { 32, 32 }, { 0 }, 0.1f);
    m_drawable->add("assets/gems/citrin.png", "shine", jt::Vector2u { 32, 32 },
        { 0, 1, 2, 3, 4, 5, 6, 0 }, 0.1f);
    m_drawable->play("idle");
    m_drawable->setLooping(false);

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity() * 0.15f;
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[8];
    vertices[0].Set(10.0f, 0.0f);
    vertices[1].Set(0.0f, 10.0f);
    vertices[2].Set(0.0f, 21.0f);
    vertices[3].Set(10.0f, 31.0f);
    vertices[4].Set(21.0f, 31.0f);
    vertices[5].Set(31.0f, 21.0f);
    vertices[6].Set(31.0f, 10.0f);
    vertices[7].Set(21.0f, 0.0f);
    int32 count = 8;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
