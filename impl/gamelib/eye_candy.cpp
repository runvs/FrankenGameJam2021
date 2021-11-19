#include "eye_candy.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include <math_helper.hpp>
#include <tweens/tween_position.hpp>
#include "random.hpp"

void EyeCandy::doCreate()
{
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

    m_trickyHeart = std::make_shared<jt::Animation>();
    m_trickyHeart->add("assets/tricky_heart.png", "idle", jt::Vector2u { 56, 86 },
        jt::MathHelper::vectorBetween<unsigned int>(0U, 19U), 0.1f);
    m_trickyHeart->play("idle");
    m_trickyHeart->setPosition(jt::Vector2 { 350.0f, -1600.0f });

    m_frog = std::make_shared<jt::Animation>();
    m_frog->add("assets/frog.png", "idle", jt::Vector2u { 14, 7 },
        jt::MathHelper::vectorBetween<unsigned int>(0U, 6U), 0.2f);
    m_frog->play("idle");
    m_frog->setPosition(jt::Vector2 { 140, 250 });
    m_frog->update(0.0f);

    m_sparklyStar1 = std::make_shared<jt::Animation>();
    m_sparklyStar1->add(
        "assets/sparkle1.png", "idle", jt::Vector2u { 7, 15 }, { 0, 1, 2, 3 }, 0.25f);
    m_sparklyStar1->play("idle");
    m_sparklyStar1->setPosition(jt::Vector2 { 130, -500 });

    m_sparklyStar2 = std::make_shared<jt::Animation>();
    m_sparklyStar2->add(
        "assets/sparkle2.png", "idle", jt::Vector2u { 7, 15 }, { 0, 1, 2, 3 }, 0.25f);
    m_sparklyStar2->play("idle");
    m_sparklyStar2->setPosition(jt::Vector2 { 70, -630 });

    m_sparklyStar3 = std::make_shared<jt::Animation>();
    m_sparklyStar3->add(
        "assets/sparkle3.png", "idle", jt::Vector2u { 7, 15 }, { 0, 1, 2, 3 }, 0.25f);
    m_sparklyStar3->play("idle");
    m_sparklyStar3->setPosition(jt::Vector2 { 230, -700 });
}
void EyeCandy::doUpdate(float const elapsed)
{
    m_frog->update(elapsed);

    auto p = m_miniBirds->getPosition();
    p += elapsed * jt::Vector2 { 10.0f, 0.0 };
    if (p.x() >= GP::GetScreenSize().x() + 50.0f) {
        p.x() = -50.0f;
        p.y() = -240.0f + jt::Random::getFloat(-32.0f, 32.0f);
    }
    m_miniBirds->setPosition(p);
    m_miniBirds->update(elapsed);

    p = m_singleBird1->getPosition();
    p += elapsed * jt::Vector2 { 20.0f, 0.0 };
    if (p.x() >= GP::GetScreenSize().x() + 50.0f) {
        p.x() = -50.0f;
        p.y() = -200.0f + jt::Random::getFloat(-24.0f, 24.0f);
    }
    m_singleBird1->setPosition(p);
    m_singleBird1->update(elapsed);

    p = m_singleBird2->getPosition();
    p += elapsed * jt::Vector2 { 30.0f, 0.0 };
    if (p.x() >= GP::GetScreenSize().x() + 50.0f) {
        p.x() = -50.0f;
        p.y() = -170.0f + jt::Random::getFloat(-24.0f, 24.0f);
    }
    m_singleBird2->setPosition(p);
    m_singleBird2->update(elapsed);

    p = m_trickyHeart->getPosition();
    p += elapsed * jt::Vector2 { -40.0f, 0.0 };
    if (p.x() <= -50) {
        p.x() = GP::GetScreenSize().x() + 50.0f;
    }
    m_trickyHeart->setPosition(p);

    m_trickyHeart->update(elapsed);
    m_sparklyStar1->update(elapsed);
    m_sparklyStar2->update(elapsed);
    m_sparklyStar3->update(elapsed);
}
void EyeCandy::doDraw() const
{
    m_frog->draw(getGame()->getRenderTarget());
    m_miniBirds->draw(getGame()->getRenderTarget());
    m_singleBird1->draw(getGame()->getRenderTarget());
    m_singleBird2->draw(getGame()->getRenderTarget());
    m_trickyHeart->draw(getGame()->getRenderTarget());
    m_sparklyStar1->draw(getGame()->getRenderTarget());
    m_sparklyStar2->draw(getGame()->getRenderTarget());
    m_sparklyStar3->draw(getGame()->getRenderTarget());
}
