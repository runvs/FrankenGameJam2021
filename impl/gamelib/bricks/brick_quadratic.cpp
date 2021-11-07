#include "brick_quadratic.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "math_helper.hpp"

BrickQuadratic::BrickQuadratic(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickImpl(world, def)
{
}

void BrickQuadratic::doCreate()
{
    m_drawable = std::make_shared<jt::Animation>();
    m_drawable->add("assets/gems/amethyst.png", "idle", jt::Vector2u { 16, 16 }, { 0 }, 0.1f);
    m_drawable->add("assets/gems/amethyst.png", "shine", jt::Vector2u { 16, 16 },
        { 0, 1, 2, 3, 4, 5, 6 }, 0.1f);
    m_drawable->play("idle");

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[4];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(0.0f, 16.0f);
    vertices[2].Set(16.0f, 16.0f);
    vertices[3].Set(16.0f, 0.0f);
    int32 count = 4;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
