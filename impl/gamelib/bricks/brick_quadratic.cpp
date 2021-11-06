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
    m_drawable = jt::dh::createRectShape(jt::Vector2 { 16, 16 }, jt::colors::Black);
    m_drawable->setOrigin(jt::Vector2 { 8, 8 });
    b2FixtureDef fixtureDef;
    fixtureDef.density = GP::PhysicsBrickDensity();
    fixtureDef.friction = 1.1f;
    fixtureDef.restitution = -0.1f;

    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(8, 8);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}

void BrickQuadratic::doUpdate(float const elapsed)
{
    m_drawable->setPosition(getPosition());
    m_drawable->setRotation(-jt::MathHelper::rad2deg(getRotation()));
    m_drawable->update(elapsed);
}

void BrickQuadratic::doDraw() const { m_drawable->draw(getGame()->getRenderTarget()); }
