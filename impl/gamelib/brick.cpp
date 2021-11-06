//
// Created by Laguna_HP on 06.11.2021.
//

#include "brick.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"

Brick::Brick(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
    : Box2DObject(world, def)
{
}

void Brick::doCreate()
{
    m_shape = jt::dh::createRectShape(jt::Vector2 { 16, 16 }, jt::colors::Black);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 20.0f;
    fixtureDef.friction = 1.0f;

    b2PolygonShape boxCollider {};
    boxCollider.SetAsBox(8, 8);
    fixtureDef.shape = &boxCollider;
    getB2Body()->CreateFixture(&fixtureDef);
}

void Brick::doUpdate(float const elapsed)
{
    auto pos = getPosition();
    pos -= jt::Vector2 { 8.0f, 8.0f };
    m_shape->setPosition(pos);
    m_shape->update(elapsed);
}

void Brick::doDraw() const { m_shape->draw(getGame()->getRenderTarget()); }

void Brick::doKill() { }

void Brick::doDestroy() { }
