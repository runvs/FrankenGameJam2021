﻿#include "state_game.hpp"
#include "animation.hpp"
#include "brick_contact_listener.hpp"
#include "bricks/brick_factory.hpp"
#include "bricks/brick_provider_random.hpp"
#include "color.hpp"
#include "conversions.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "hud/hud.hpp"
#include "math_helper.hpp"
#include "random.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "state_menu.hpp"
#include "tweens/tween_alpha.hpp"
#include "tweens/tween_position.hpp"
#include "tweens/tween_scale.hpp"

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

    m_background->setPosition(jt::Vector2 { 0.0f, -600.0f });
    m_background->update(0.0f);

    m_tiledBackground1 = std::make_shared<jt::Sprite>();
    m_tiledBackground1->loadSprite("assets/tiled_space.png");
    m_tiledBackground1->setPosition(jt::Vector2 { 0.0f, -1560.0f });
    m_tiledBackground1->update(0.0f);

    m_tiledBackground2 = std::make_shared<jt::Sprite>();
    m_tiledBackground2->loadSprite("assets/tiled_space.png");
    m_tiledBackground2->setPosition(jt::Vector2 { 0.0f, -1560.0f - 480.0f });
    m_tiledBackground2->update(0.0f);

    m_miniBirds = std::make_shared<jt::Animation>();
    m_miniBirds->add(
        "assets/minibirds.png", "idle", jt::Vector2u { 32, 32 }, { 0, 1, 2, 3 }, 0.25f);
    m_miniBirds->play("idle");
    m_miniBirds->setPosition(jt::Vector2 { 45.0f, -240.0f });

    m_singleBird1 = std::make_shared<jt::Animation>();
    m_singleBird1->add(
        "assets/singlebird.png", "idle", jt::Vector2u { 6, 7 }, { 0, 1, 2, 3 }, 0.25f);
    m_singleBird1->play("idle");
    m_singleBird1->setPosition(jt::Vector2 { 185.0f, -200.0f });

    m_singleBird2 = std::make_shared<jt::Animation>();
    m_singleBird2->add(
        "assets/singlebird.png", "idle", jt::Vector2u { 6, 7 }, { 0, 1, 2, 3 }, 0.25f);
    m_singleBird2->play("idle");
    m_singleBird2->setPosition(jt::Vector2 { 25.0f, -170.0f });

    m_frog = std::make_shared<jt::Animation>();
    m_frog->add("assets/frog.png", "idle", jt::Vector2u { 14, 7 },
        jt::MathHelper::vectorBetween<unsigned int>(0U, 6U), 0.2f);
    m_frog->play("idle");
    m_frog->setPosition(jt::Vector2 { 140, 250 });
    m_frog->update(0.0f);

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
        [this](auto p1, auto p2) { handleCurrentBrickCollision(p1, p2); });

    m_world->setContactListener(contactListener);
    m_brickProvider = std::make_shared<BrickProviderRandom>();

    m_soundBrickSpawn = std::make_shared<jt::Sound>();
    m_soundBrickSpawn->load("assets/sfx/brick_spawn.ogg");

    m_soundGroupBrickContact = std::make_shared<jt::SoundGroup>(
        std::vector<std::string> { "assets/sfx/brick_contact_1.ogg",
            "assets/sfx/brick_contact_2.ogg", "assets/sfx/brick_contact_3.ogg",
            "assets/sfx/brick_contact_4.ogg", "assets/sfx/brick_contact_5.ogg" });

    m_soundGameOver = std::make_shared<jt::Sound>();
    m_soundGameOver->load("assets/sfx/gameover.ogg");

    m_soundAtmospheric1 = std::make_shared<jt::Sound>();
    m_soundAtmospheric1->load("assets/sfx/atmosphere/01_birds_and_frogs_at_forest_pond.ogg");
    m_soundAtmospheric1->setLoop(true);
    m_soundAtmospheric1->setVolume(50.0f);
    m_soundAtmospheric1->play();

    m_soundAtmospheric2 = std::make_shared<jt::Sound>();
    m_soundAtmospheric2->load("assets/sfx/atmosphere/02_wind_in_forest.ogg");
    m_soundAtmospheric2->setLoop(true);
    m_soundAtmospheric2->setVolume(0.0f);
    m_soundAtmospheric2->play();

    m_soundAtmospheric3 = std::make_shared<jt::Sound>();
    m_soundAtmospheric3->load("assets/sfx/atmosphere/03_strong_wind.ogg");
    m_soundAtmospheric3->setLoop(true);
    m_soundAtmospheric3->setVolume(0.0f);
    m_soundAtmospheric3->play();

    m_soundBrickFreeze1 = std::make_shared<jt::Sound>();
    m_soundBrickFreeze1->load("assets/sfx/block_freeze_1_high.wav");
    m_soundBrickFreeze2 = std::make_shared<jt::Sound>();
    m_soundBrickFreeze2->load("assets/sfx/block_freeze_2_high.wav");
    m_soundBrickFreeze3 = std::make_shared<jt::Sound>();
    m_soundBrickFreeze3->load("assets/sfx/block_freeze_3_high.wav");
    m_soundBrickFreeze4 = std::make_shared<jt::Sound>();
    m_soundBrickFreeze4->load("assets/sfx/block_freeze_4_high.wav");

    m_sound1Up = std::make_shared<jt::Sound>();
    m_sound1Up->load("assets/sfx/1up_pling.ogg");

    createParticleSystems();

    auto t = std::make_shared<jt::Timer>(
        1.5f, [this]() { spawnNewBrick(); }, -1);
    add(t);

    m_hud->getObserverLife()->notify(m_extra_lifes);
}

void StateGame::createParticleSystems()
{
    m_brickFixateParticles = jt::ParticleSystem<jt::Shape, 64>::createPS(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect(jt::Vector2 { 4, 4 });
            auto const v = static_cast<uint8_t>(jt::Random::getInt(240, 255));
            s->setColor(jt::Color(v, v, v, 255));
            s->setOrigin({ 2, 2 });
            return s;
        },
        [this](auto s) {
            s->setPosition(m_currentPendingBrick->getPosition());

            auto twa = jt::TweenAlpha::create(
                s, 0.5f, static_cast<uint8_t>(jt::Random::getInt(220, 255)), 0);
            twa->setSkipFrames(1);
            add(twa);

            auto center = jt::Conversion::vec(m_currentPendingBrick->getB2Body()->GetWorldCenter());
            float particleRadius = 450.0f;
            auto twp = jt::TweenPosition::create(s, 1, center,
                center
                    + jt::Random::getRandomPointIn(jt::Rect(-particleRadius / 2.0f,
                        -particleRadius / 2.0f, particleRadius, particleRadius)));
            add(twp);

            auto tws = jt::TweenScale::create(s, jt::Random::getFloatGauss(0.5f, 0.07f),
                jt::Vector2 { 2.5f, 2.5f }, jt::Vector2 { 0.0f, 0.0f });
            tws->setSkipFrames(1);
            add(tws);
        });

    add(m_brickFixateParticles);

    m_backgroundDustParticles = jt::ParticleSystem<jt::Shape, 128>::createPS(
        []() {
            auto s = std::make_shared<jt::Shape>();
            s->makeRect(jt::Vector2 { 2, 2 });
            auto const v = static_cast<uint8_t>(jt::Random::getInt(240, 255));
            s->setColor(jt::Color(v, v, v, 255));
            s->setOrigin({ 1, 1 });
            return s;
        },
        [this](auto s) {
            auto start = jt::Random::getRandomPointIn(jt::Rect { 0, -700, 240, 1000 });
            s->setPosition(start);
            auto col = s->getColor();
            col.a() = 0;
            s->setColor(col);

            auto maxAlpha = static_cast<uint8_t>(jt::Random::getInt(30, 65));
            auto twa1 = jt::TweenAlpha::create(s, 0.5f, 0, maxAlpha);
            twa1->setSkipFrames(1);
            add(twa1);

            auto twa2 = jt::TweenAlpha::create(s, 0.5f, maxAlpha, 0);
            twa2->setSkipFrames(1);
            twa2->setStartDelay(4.5f);
            add(twa2);

            auto twp = jt::TweenPosition::create(s, 4.5f, start,
                start + jt::Random::getRandomPointIn(jt::Rect { -200, -200, 200, 200 }));
            add(twp);
        });

    add(m_backgroundDustParticles);
    m_backgroundDustParticles->Fire(20);
    auto dustTimer
        = std::make_shared<jt::Timer>(0.5f, [this]() { m_backgroundDustParticles->Fire(4); });
    add(dustTimer);
}

void StateGame::freezeBricks()
{
    for (auto const b : *m_bricks) {
        if (b.expired()) {
            continue;
        }
        auto brick = b.lock();
        if (brick->isFrozen()) {
            continue;
        }
        if (!brick->isFixated()) {
            continue;
        }
        if (brick == m_currentBrick || brick == m_currentPendingBrick) {
            continue;
        }

        auto const pos = brick->getPosition();
        if (pos.y() > m_maxHeight + 108.0f) {
            std::cout << "freeze brick at: " << pos.y() << std::endl;
            addRevoluteJointTo(brick);
            brick->freeze();
        }
    }
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        m_world->step(elapsed, GP::PhysicVelocityIterations(), GP::PhysicPositionIterations());
        // update game logic here

        // TODO remove this
        if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::F9)
            && getGame()->input()->keyboard()->pressed(jt::KeyCode::LShift)
            && getGame()->input()->keyboard()->pressed(jt::KeyCode::LControl)) {
            getGame()->getCamera()->move(jt::Vector2 { 0.0f, -100.0f });
        }

        rotateCurrentBrick(elapsed);
        checkForGameOver();
        freezeBricks();
        m_loseLifeTimer -= elapsed;
    } else if (m_hasEnded) {
        auto camOff = getGame()->getCamera()->getCamOffset().y();
        static bool first = true;
        if (camOff >= -32.0f && first) {
            auto tw
                = jt::TweenAlpha::create(m_overlay, 3.2f, std::uint8_t { 0 }, std::uint8_t { 255 });
            tw->setSkipFrames();
            tw->addCompleteCallback(
                [this]() { getGame()->switchState(std::make_shared<StateMenu>()); });
            add(tw);
            first = false;
        }
    }
    moveCamera(elapsed);
    m_background->update(elapsed);

    auto tiledBackgroundPosition = m_tiledBackground1->getPosition();
    if (getGame()->getCamera()->getCamOffset().y() - tiledBackgroundPosition.y() <= -480.0f) {
        m_tiledBackground1->setPosition(
            jt::Vector2 { tiledBackgroundPosition.x(), tiledBackgroundPosition.y() - 960.0f });
    }

    m_tiledBackground2->setPosition(
        m_tiledBackground1->getPosition() + jt::Vector2 { 0.0f, -480.0f });

    m_tiledBackground1->update(elapsed);
    m_tiledBackground2->update(elapsed);
    m_frog->update(elapsed);
    m_miniBirds->update(elapsed);
    m_singleBird1->update(elapsed);
    m_singleBird2->update(elapsed);
    m_vignette->update(elapsed);
    m_overlay->update(elapsed);
}

void StateGame::moveCamera(float const elapsed)
{
    float const camPosY = getGame()->getCamera()->getCamOffset().y();
    float const scrollTo = m_maxHeight - 120;

    if (m_hasEnded && camPosY < 0.0f) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, -elapsed * 4.0f + elapsed * 40.0f });
    } else if (!m_hasEnded && camPosY > scrollTo) {
        getGame()->getCamera()->move(jt::Vector2 { 0.0f, -elapsed * 4.0f });
    }

    float volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint1() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric1->setVolume(volume);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint2() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric2->setVolume(volume);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint3() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric3->setVolume(volume);
}

void StateGame::addDistanceJointsTo(std::shared_ptr<BrickInterface> brick, b2Body* other)
{
    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(other, brick->getB2Body(),
            other->GetWorldCenter() + b2Vec2 { 13.0f, 0.0f },
            brick->getB2Body()->GetWorldCenter() + b2Vec2 { -16.0f, 0.0f });
        jointDef.collideConnected = true;
        jointDef.frequencyHz = 15.0f;
        jointDef.dampingRatio = 0.04f;
        m_world->createJoint(&jointDef);
    }

    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(other, brick->getB2Body(),
            other->GetWorldCenter() + b2Vec2 { -13.0f, 0.0f },
            brick->getB2Body()->GetWorldCenter() + b2Vec2 { 16.0f, 0.0f });
        jointDef.collideConnected = true;
        jointDef.frequencyHz = 15.0f;
        jointDef.dampingRatio = 0.04f;
        m_world->createJoint(&jointDef);
    }
}

void StateGame::addRevoluteJointTo(std::shared_ptr<BrickInterface> brick)
{
    b2RevoluteJointDef jointDef;
    jointDef.Initialize(
        m_platform->getB2Body(), brick->getB2Body(), m_platform->getB2Body()->GetWorldCenter());
    jointDef.lowerAngle = -0.001f;
    jointDef.upperAngle = 0.001f;
    jointDef.enableLimit = true;
    jointDef.maxMotorTorque = 10.0f;
    jointDef.motorSpeed = 0.0f;
    jointDef.enableMotor = true;
    m_world->createJoint(&jointDef);
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

void StateGame::spawnNewBrick()
{
    if (m_canSpawnNewBrick) {
        m_currentBrick = m_brickProvider->getNextBrickFunction()(m_world, m_maxHeight - 280);
        add(m_currentBrick);
        m_bricks->push_back(m_currentBrick);
        m_currentBrick->update(0.0f);

        m_soundBrickSpawn->play();
        m_canSpawnNewBrick = false;
    }
}

void StateGame::doInternalDraw() const
{
    m_tiledBackground1->draw(getGame()->getRenderTarget());
    m_tiledBackground2->draw(getGame()->getRenderTarget());
    m_background->draw(getGame()->getRenderTarget());
    m_frog->draw(getGame()->getRenderTarget());
    m_miniBirds->draw(getGame()->getRenderTarget());
    m_singleBird1->draw(getGame()->getRenderTarget());
    m_singleBird2->draw(getGame()->getRenderTarget());
    drawObjects();
    m_brickFixateParticles->draw();
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

        if (!brick->isAlive()) {
            continue;
        }
        if (brick == m_currentBrick || brick == m_currentPendingBrick) {
            auto position = brick->getPosition();
            float killThreshold = GP::GetScreenSize().y() + GP::RemoveBrickDeadzone();
            auto camOff = getGame()->getCamera()->getCamOffset().y();
            if (position.y() - camOff > killThreshold) {
                brick->kill();
                loseLife();
            }
        }
    }
}
void StateGame::loseLife()
{
    if (m_loseLifeTimer <= 0.0f) {
        m_loseLifeTimer = 0.5f;
        m_extra_lifes--;

        m_hud->getObserverLife()->notify(m_extra_lifes);
        if (m_extra_lifes < 0) {
            endGame();
        } else {
            m_canSpawnNewBrick = true;
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
}

bool StateGame::isCurrentBrick(b2Body const* const bodyPtr) const
{
    if (!m_currentBrick) {
        return false;
    }
    return bodyPtr == m_currentBrick->getB2Body();
}

void StateGame::handleCurrentBrickCollision(b2Body* p1, b2Body* p2)
{
    if (isCurrentBrick(p1) || isCurrentBrick(p2)) {
        auto other = isCurrentBrick(p1) ? p2 : p1;

        auto t2 = std::make_shared<jt::Timer>(
            0.9f,
            [this, currentPendingBrick = m_currentBrick, other]() {
                fixCurrentBrick(currentPendingBrick, other);
            },
            1);
        add(t2);
        m_currentPendingBrick = m_currentBrick;
        m_currentBrick = nullptr;
        m_soundGroupBrickContact->play();
    }
}

void StateGame::fixCurrentBrick(std::shared_ptr<BrickInterface> currentPendingBrick, b2Body* other)
{
    if (!currentPendingBrick->isAlive()) {
        return;
    }
    auto const v = currentPendingBrick->getVelocity() - m_platform->getVelocity();
    auto const l = jt::MathHelper::lengthSquared(v);

    if (l < GP::BrickFixVelocityThreshold()) {
        float const ypos = currentPendingBrick->getB2Body()->GetWorldCenter().y;
        if (ypos < m_maxHeight) {

            m_maxHeight = ypos;
            auto oldscore = m_score;
            m_score = 280 - (int)m_maxHeight;
            m_hud->getObserverScore()->notify(m_score);

            m_lifeCounter += (m_score - oldscore);
            if (m_lifeCounter >= 100) {
                m_lifeCounter = 0;
                m_extra_lifes++;
                if (m_extra_lifes >= 4) {
                    m_extra_lifes = 4;
                } else {
                    m_sound1Up->play();
                }
                m_hud->getObserverLife()->notify(m_extra_lifes);
            }
        }
        currentPendingBrick->getDrawable()->flash(1.25f);
        addDistanceJointsTo(currentPendingBrick, m_platform->getB2Body());
        addDistanceJointsTo(currentPendingBrick, other);
        currentPendingBrick->fixate();

        m_canSpawnNewBrick = true;

        // Sorry, can't be bothered to do this right right now.
        int rnd = jt::Random::getInt(0, 3);
        switch (rnd) {
        case 0:
            m_soundBrickFreeze1->play();
            break;
        case 1:
            m_soundBrickFreeze2->play();
            break;
        case 2:
            m_soundBrickFreeze3->play();
            break;
        case 3:
            m_soundBrickFreeze4->play();
            break;
        default:
            break;
        }

        m_brickFixateParticles->Fire(20);
    }

    else {
        auto t = std::make_shared<jt::Timer>(
            0.1f,
            [this, currentPendingBrick = currentPendingBrick, other]() {
                fixCurrentBrick(currentPendingBrick, other);
            },
            1);
        add(t);
    }
}
