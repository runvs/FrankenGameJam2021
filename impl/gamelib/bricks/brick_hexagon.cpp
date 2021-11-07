#include "brick_hexagon.hpp"
#include "animation.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "math_helper.hpp"
#include "random.hpp"
#include "timer.hpp"

BrickHexagon::BrickHexagon(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickHexagon::doCreate()
{
    m_drawable = std::make_shared<jt::Animation>();
    m_drawable->add("assets/gems/turquoise.png", "idle", jt::Vector2u { 18, 32 }, { 0 }, 0.1f);
    m_drawable->add("assets/gems/turquoise.png", "shine", jt::Vector2u { 18, 32 },
        { 0, 1, 2, 3, 4, 5, 6 }, 0.1f);
    m_drawable->play("idle");

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[6];
    vertices[0].Set(8.5f, 0.0f);
    vertices[1].Set(0.0f, 8.0f);
    vertices[2].Set(0.0f, 23.0f);
    vertices[3].Set(9.0f, 31.5f);
    vertices[4].Set(17.0f, 23.0f);
    vertices[5].Set(17.0f, 8.0f);
    int32 count = 6;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
