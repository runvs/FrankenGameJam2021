#include "state_game.hpp"
#include "bricks/brick_factory.hpp"
#include "color.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "hud/hud.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "state_menu.hpp"
#include "tweens/tween_alpha.hpp"

void StateGame::doInternalCreate()
{
    m_worldImpl = std::make_shared<b2World>(b2Vec2 { 0.0f, 100.0f });
    m_world = std::make_shared<jt::Box2DWorldWrapper>(m_worldImpl);

    float const w = static_cast<float>(GP::GetWindowSize().x());
    float const h = static_cast<float>(GP::GetWindowSize().y());

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h });
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_overlay = std::make_shared<Shape>();
    m_overlay->makeRect(jt::Vector2 { w, h });
    m_overlay->setColor(jt::Color { 0, 0, 0 });
    m_overlay->setIgnoreCamMovement(true);
    m_overlay->update(0);
    auto tw = TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tw->setSkipFrames();
    tw->addCompleteCallback([this]() { m_running = true; });
    add(tw);

    m_vignette = std::make_shared<jt::Sprite>();
    m_vignette->loadSprite("#v#" + std::to_string(static_cast<int>(GP::GetScreenSize().x())) + "#"
        + std::to_string(static_cast<int>(GP::GetScreenSize().y())));
    m_vignette->setIgnoreCamMovement(true);
    m_vignette->setColor({ 255, 255, 255, 100 });

    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);

    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(135, 280.0f);
    m_platform = std::make_shared<Platform>(m_world, &bodyDef);
    add(m_platform);

    m_bricks = std::make_shared<jt::ObjectGroup<BrickInterface>>();
    add(m_bricks);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::M)) {
            auto brick = BrickFactory::createBrickQuadratic(m_world);
            add(brick);
            m_bricks->push_back(brick);
        }
        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::N)) {
            auto brick = BrickFactory::createBrickRectangle2x1(m_world);
            add(brick);
            m_bricks->push_back(brick);
        }

        // TODO: WIP: Revolute Joint with the platform
        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::R)) {
            for (auto brick : *m_bricks) {
                b2RevoluteJointDef jointDef;
                jointDef.Initialize(m_platform->getB2Body(), brick.lock()->getB2Body(),
                    m_platform->getB2Body()->GetWorldCenter());
                jointDef.lowerAngle = -0.001f;
                jointDef.upperAngle = 0.001f;
                jointDef.enableLimit = true;
                jointDef.maxMotorTorque = 10.0f;
                jointDef.motorSpeed = 0.0f;
                jointDef.enableMotor = true;
                m_world->createJoint(&jointDef);
            }
        }

        // TODO: WIP: Distance Joint with the platform
        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::T)) {
            for (auto brick : *m_bricks) {
                b2DistanceJointDef jointDef;
                jointDef.Initialize(m_platform->getB2Body(), brick.lock()->getB2Body(),
                    m_platform->getB2Body()->GetWorldCenter(),
                    brick.lock()->getB2Body()->GetWorldCenter());
                jointDef.collideConnected = true;
                jointDef.frequencyHz = 30.0f;
                jointDef.dampingRatio = 0.5f;
                m_world->createJoint(&jointDef);
            }
        }

        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::L)) {
            auto brick = BrickFactory::createBrickL(m_world);
            add(brick);
            m_bricks->push_back(brick);
        }

        removeBricksOutOfScreen();
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
    m_overlay->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());
    drawObjects();
    m_vignette->draw(getGame()->getRenderTarget());
    m_hud->draw();
    m_overlay->draw(getGame()->getRenderTarget());
}

void StateGame::removeBricksOutOfScreen()
{
    for (auto b : *m_bricks) {
        if (b.expired()) {
            continue;
        }

        auto brick = b.lock();
        auto position = brick->getPosition();

        if (position.y() > GP::GetScreenSize().y() + GP::RemoveBrickDeadzone()) {
            brick->kill();
        }
    }
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    auto tw = jt::TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 0 }, std::uint8_t { 255 });
    tw->setSkipFrames();
    tw->addCompleteCallback([this]() { getGame()->switchState(std::make_shared<StateMenu>()); });
    add(tw);
}
