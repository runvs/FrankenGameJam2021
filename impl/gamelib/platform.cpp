#include "platform.hpp"
#include "conversions.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"

using namespace jt::Conversion;

Platform::Platform(
    std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def, const bool anchor)
    : Box2DObject(world, def)
    , m_anchor(anchor)
{
}

void Platform::doCreate()
{
    // TODO: Anchors should be their own class if they work.
    m_sprite = std::make_shared<jt::Sprite>();
    if (!m_anchor) {
        m_sprite->loadSprite("assets/platform_gold.png");
    }

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1000.0f;
    fixtureDef.friction = 0.99f;
    fixtureDef.restitution = 0.0f;

    b2PolygonShape boxCollider {};
    if (!m_anchor) {
        boxCollider.SetAsBox(m_platformSize.x() * 0.5f, m_platformSize.y() * 0.5f);
    }
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
    // TODO: Anchors should be their own class if they work.
    if (!m_anchor) {
        auto pos = getPosition();
        pos -= m_platformSize * 0.5f;
        m_sprite->setPosition(pos);
        m_sprite->update(elapsed);
    }
}

void Platform::doDraw() const { m_sprite->draw(getGame()->getRenderTarget()); }
void Platform::doKill() { }
void Platform::doDestroy() { }
