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
    m_drawable = std::make_shared<jt::Animation>();
    m_drawable->add("assets/gems/diamond.png", "idle", jt::Vector2u { 16, 16 }, { 0 }, 0.1f);
    m_drawable->add(
        "assets/gems/diamond.png", "shine", jt::Vector2u { 16, 16 }, { 0, 1, 2, 3, 4, 5, 6 }, 0.1f);
    m_drawable->play("idle");

    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = GP::PhysicsBrickRestitution();

    b2PolygonShape boxCollider {};
    b2Vec2 vertices[5];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(0.0f, 16.0f);
    vertices[2].Set(16.0f, 16.0f);
    vertices[3].Set(16.0f, 10.0f);
    vertices[4].Set(6.0f, 0.0f);
    int32 count = 5;
    boxCollider.Set(vertices, count);

    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
