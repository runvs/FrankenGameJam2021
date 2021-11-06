#include "brick_cutting_edge.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"

BrickCuttingEdge::BrickCuttingEdge(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickInterface(world, def)
{
}

/*
 *  _
 * | |
 * | |_
 * |___|
 *
 *
 *
 *
 */

void BrickCuttingEdge::doCreate()
{
    m_sprite = std::make_shared<jt::Sprite>();
    m_sprite->loadSprite("assets/brick_l.png");

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.01f;
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = -0.1f;

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
    m_sprite->setPosition(getPosition());
    m_sprite->setRotation(-jt::MathHelper::rad2deg(getRotation()));
    m_sprite->update(elapsed);
}

void BrickCuttingEdge::doDraw() const { m_sprite->draw(getGame()->getRenderTarget()); }
