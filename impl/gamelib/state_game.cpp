#include "state_game.hpp"
#include "brick_contact_listener.hpp"
#include "bricks/brick_factory.hpp"
#include "bricks/brick_provider_random.hpp"
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

    m_background = std::make_shared<jt::Sprite>();
    m_background->loadSprite("assets/background.png");

    m_background->setPosition(jt::Vector2 { 0.0f, -330.0f });
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

    auto contactListener = std::make_shared<BrickContactListener>();
    contactListener->addContactCallback(
        [this](auto p1, auto p2) { handleCurrentBlockCollision(p1, p2); });
    m_world->setContactListener(contactListener);
    m_brickProvider = std::make_shared<BrickProviderRandom>();

    m_soundBrickSpawn = std::make_shared<jt::Sound>();
    m_soundBrickSpawn->load("assets/sfx/block_spawn.ogg");

    m_soundBrickContact = std::make_shared<jt::Sound>();
    m_soundBrickContact->load("assets/sfx/block_contact.ogg");

    m_soundGameOver = std::make_shared<jt::Sound>();
    m_soundGameOver->load("assets/sfx/gameover.ogg");

    auto t = std::make_shared<jt::Timer>(
        1.5f, [this]() { spawnNewBrick(); }, 1);
    add(t);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        spawnBricks();
        rotateCurrentBrick(elapsed);
        moveCamera(elapsed);
        checkForGameOver();
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
    m_overlay->update(elapsed);
}

void StateGame::moveCamera(float const elapsed)
{
    float const camPosY = getGame()->getCamera()->getCamOffset().y();
    float const scrollTo = m_maxHeight - 220;
    //    std::cout << camPosY << " " << scrollTo << std::endl;
    if (camPosY > scrollTo) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, -elapsed * 4.0f });
    }
}

void StateGame::addJointToPlatform(std::shared_ptr<BrickInterface> brick, b2Body* other)
{
    // RevolutionJoint
#if false
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(
            m_platform->getB2Body(), brick->getB2Body(),
            m_platform->getB2Body()->GetWorldCenter());
        jointDef.lowerAngle = -0.001f;
        jointDef.upperAngle = 0.001f;
        jointDef.enableLimit = true;
        jointDef.maxMotorTorque = 10.0f;
        jointDef.motorSpeed = 0.0f;
        jointDef.enableMotor = true;
        m_world->createJoint(&jointDef);
#else

    // two DistanceJoints
    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(other, brick->getB2Body(),
            other->GetWorldCenter() + b2Vec2 { 16.0f, 0.0f },
            brick->getB2Body()->GetWorldCenter() + b2Vec2 { -16.0f, 0.0f });
        jointDef.collideConnected = true;
        jointDef.frequencyHz = 10.0f;
        jointDef.dampingRatio = 0.02f;
        m_world->createJoint(&jointDef);
    }

    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(other, brick->getB2Body(),
            other->GetWorldCenter() + b2Vec2 { -16.0f, 0.0f },
            brick->getB2Body()->GetWorldCenter() + b2Vec2 { 16.0f, 0.0f });
        jointDef.collideConnected = true;
        jointDef.frequencyHz = 10.0f;
        jointDef.dampingRatio = 0.02f;
        m_world->createJoint(&jointDef);
    }
#endif
}

void StateGame::rotateCurrentBrick(float const elapsed)
{
    if (!m_currentBrick) {
        return;
    }

    if (getGame()->input()->keyboard()->pressed(jt::KeyCode::Q)) {
        m_currentBrick->getB2Body()->ApplyTorque(-5000000.0f * elapsed, true);
    }
    if (getGame()->input()->keyboard()->pressed(jt::KeyCode::E)) {
        m_currentBrick->getB2Body()->ApplyTorque(5000000.0f * elapsed, true);
    }
}

void StateGame::spawnBricks()
{
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::M)) {
        spawnNewBrick();
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::N)) {
        m_currentBrick
            = BrickFactory::createBrickRectangle2x1(m_world, jt::Vector2 { 250.0f, 20.0f });
        add(m_currentBrick);
        m_bricks->push_back(m_currentBrick);
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::L)) {
        m_currentBrick
            = BrickFactory::createBrickCuttingEdge(m_world, jt::Vector2 { 250.0f, 20.0f });
        add(m_currentBrick);
        m_bricks->push_back(m_currentBrick);
    }
}
void StateGame::spawnNewBrick()
{
    m_currentBrick = m_brickProvider->getNextBrickFunction()(m_world, m_maxHeight - 280);
    add(m_currentBrick);
    m_bricks->push_back(m_currentBrick);

    m_soundBrickSpawn->play();
}

void StateGame::doInternalDraw() const
{
    m_background->draw(getGame()->getRenderTarget());
    drawObjects();
    if (m_currentBrick != nullptr) {
        m_currentBrick->drawPreview();
    }
    m_vignette->draw(getGame()->getRenderTarget());
    m_hud->draw();
    m_overlay->draw(getGame()->getRenderTarget());
}

void StateGame::checkForGameOver()
{
    for (auto b : *m_bricks) {
        if (b.expired()) {
            continue;
        }

        auto brick = b.lock();
        auto position = brick->getPosition();

        if (position.y() > GP::GetScreenSize().y() + GP::RemoveBrickDeadzone()) {
            endGame();
        }
    }
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_soundGameOver->play();
    m_hasEnded = true;
    m_running = false;

    auto tw = jt::TweenAlpha::create(m_overlay, 3.2f, std::uint8_t { 0 }, std::uint8_t { 255 });
    tw->setSkipFrames();
    tw->addCompleteCallback([this]() { getGame()->switchState(std::make_shared<StateMenu>()); });
    add(tw);
}

bool StateGame::isCurrentBrick(b2Body const* const bodyPtr) const
{
    if (!m_currentBrick) {
        return false;
    }
    return bodyPtr == m_currentBrick->getB2Body();
}

void StateGame::handleCurrentBlockCollision(b2Body* p1, b2Body* p2)
{
    if (isCurrentBrick(p1) || isCurrentBrick(p2)) {
        auto other = isCurrentBrick(p1) ? p2 : p1;

        auto t2 = std::make_shared<jt::Timer>(
            1.5f,
            [this, currentPendingBrick = m_currentBrick, other]() {
                fixCurrentBrick(currentPendingBrick, other);
            },
            1);
        add(t2);

        m_currentBrick = nullptr;
        m_soundBrickContact->play();

        auto t = std::make_shared<jt::Timer>(
            1.5f, [this]() { spawnNewBrick(); }, 1);
        add(t);
    }
}
void StateGame::fixCurrentBrick(std::shared_ptr<BrickInterface> currentPendingBrick, b2Body* other)
{

    float const ypos = currentPendingBrick->getPosition().y();
    if (ypos < m_maxHeight) {
        m_maxHeight = ypos;
    }
    // TODO Add check for velocity of brick
    addJointToPlatform(currentPendingBrick, m_platform->getB2Body());
    addJointToPlatform(currentPendingBrick, other);
}
