#include "platform.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"

using namespace jt::Conversion;

Platform::Platform(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : Box2DObject(world, def)
{
}

void Platform::doCreate()
{
    m_shape = jt::dh::createRectShape(m_platformSize);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1000.0f;
    fixtureDef.friction = 0.99f;
    fixtureDef.restitution = 0.0f;

    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(m_platformSize.x() * 0.5f, m_platformSize.y() * 0.5f);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}

void Platform::doUpdate(float const elapsed)
{
    getB2Body()->SetLinearVelocity(vec(jt::Vector2 { 0.0f, 0.0f }));
    auto kbd = getGame()->input()->keyboard();
    if (kbd->pressed(jt::KeyCode::A) || kbd->pressed(jt::KeyCode::Left)) {
        getB2Body()->SetLinearVelocity(vec(jt::Vector2 { -GP::PlatformMovementSpeed(), 0.0f }));
    } else if (kbd->pressed(jt::KeyCode::D) || kbd->pressed(jt::KeyCode::Right)) {
        getB2Body()->SetLinearVelocity(vec(jt::Vector2 { GP::PlatformMovementSpeed(), 0.0f }));
    }
    auto pos = getPosition();
    pos -= m_platformSize * 0.5f;
    m_shape->setPosition(pos);
    m_shape->update(elapsed);
}

void Platform::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }
void Platform::doKill() { }
void Platform::doDestroy() { }
