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
    jt::Vector2 const boxSize { 48, 6 };
    m_shape = jt::dh::createRectShape(jt::Vector2 { 48, 6 });

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.001f;
    fixtureDef.friction = 5.0f;

    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(boxSize.x(), boxSize.y());
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}
void Platform::doUpdate(float const elapsed)
{
    if (getGame()->input()->keyboard()->pressed(jt::KeyCode::A)) {
        getB2Body()->SetLinearVelocity(vec(jt::Vector2 { -GP::PlatformMovementSpeed(), 0 }));
    } else if (getGame()->input()->keyboard()->pressed(jt::KeyCode::D)) {
        getB2Body()->SetLinearVelocity(vec(jt::Vector2 { GP::PlatformMovementSpeed(), 0 }));
    }
    m_shape->setPosition(getPosition());
    m_shape->update(elapsed);
}

void Platform::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }
void Platform::doKill() { }
void Platform::doDestroy() { }
