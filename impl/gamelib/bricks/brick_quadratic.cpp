#include "brick_quadratic.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"

BrickQuadratic::BrickQuadratic(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : BrickInterface(world, def)
{
}

void BrickQuadratic::doCreate()
{
    m_shape = jt::dh::createRectShape(jt::Vector2 { 16, 16 }, jt::colors::Black);
    m_shape->setOrigin(jt::Vector2 { 8, 8 });
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.01f;
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = -0.1f;

    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(8, 8);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}

void BrickQuadratic::doUpdate(float const elapsed)
{
    auto pos = getPosition();
    //    pos -= jt::Vector2 { 8.0f, 8.0f };
    m_shape->setPosition(pos);
    m_shape->setRotation(-jt::MathHelper::rad2deg(getRotation()));
    m_shape->update(elapsed);
}

void BrickQuadratic::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }
