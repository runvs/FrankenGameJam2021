#include "hud.hpp"
#include "../game_properties.hpp"
#include "color.hpp"
#include "game_interface.hpp"
#include "life_display.hpp"
#include "random.hpp"
#include "score_display.hpp"
#include "texture_manager.hpp"

std::shared_ptr<ObserverInterface<int>> Hud::getObserverScore() const { return m_scoreP1Display; }

std::shared_ptr<ObserverInterface<int>> Hud::getObserverLife() const { return m_lifeDisplay; }

void Hud::doCreate()
{
    m_scoreP1Text = std::make_shared<jt::Text>();
    m_scoreP1Text->loadFont("assets/font.ttf", 14, getGame()->getRenderTarget());
    m_scoreP1Text->setColor(jt::Color { 248, 249, 254 });
    m_scoreP1Text->setIgnoreCamMovement(true);
    m_scoreP1Text->update(0.0f);
    m_scoreP1Text->setTextAlign(jt::Text::TextAlign::LEFT);
    m_scoreP1Text->setPosition({ 10, 4 });

    m_scoreP1Display = std::make_shared<ScoreDisplay>(m_scoreP1Text, "Height: ");

    m_life1 = setUpLife(0);
    m_life2 = setUpLife(1);
    m_life3 = setUpLife(2);
    m_life4 = setUpLife(3);

    m_lifeShadow1 = setUpLifeShadow(0);
    m_lifeShadow2 = setUpLifeShadow(1);
    m_lifeShadow3 = setUpLifeShadow(2);
    m_lifeShadow4 = setUpLifeShadow(3);

    std::vector<std::shared_ptr<jt::DrawableInterface>> lifeSprites { m_life1, m_life2, m_life3,
        m_life4 };
    m_lifeDisplay = std::make_shared<LifeDisplay>(lifeSprites);
}

std::shared_ptr<jt::Animation> Hud::setUpLife(int i)
{
    auto animation = std::make_shared<jt::Animation>();
    animation->add("assets/heart.png", "idle", jt::Vector2u { 16, 16 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
        0.075f + jt::Random::getFloatGauss(0, 0.01f));

    animation->play("idle", jt::Random::getInt(0, 16));
    animation->setIgnoreCamMovement(true);
    animation->setPosition(jt::Vector2 { 210.0f - i * 28.0f, 10.0f });
    animation->setColor(jt::colors::Transparent);
    return animation;
}

jt::Animation::Sptr Hud::setUpLifeShadow(int i)
{
    auto animation = std::make_shared<jt::Animation>();
    animation->add("assets/heart.png", "idle", jt::Vector2u { 16, 16 }, { 0 }, 0.15f);
    animation->play("idle");
    animation->setColor(jt::Color { 75, 75, 75, 100 });
    animation->setIgnoreCamMovement(true);
    animation->setPosition(jt::Vector2 { 210.0f - i * 28.0f, 10.0f });

    return animation;
}

void Hud::doUpdate(float const elapsed)
{
    m_scoreP1Text->update(elapsed);
    m_life1->update(elapsed);
    m_life2->update(elapsed);
    m_life3->update(elapsed);
    m_life4->update(elapsed);

    m_lifeShadow1->update(elapsed);
    m_lifeShadow2->update(elapsed);
    m_lifeShadow3->update(elapsed);
    m_lifeShadow4->update(elapsed);
}

void Hud::doDraw() const
{
    m_scoreP1Text->draw(getGame()->getRenderTarget());

    m_lifeShadow1->draw(getGame()->getRenderTarget());
    m_lifeShadow2->draw(getGame()->getRenderTarget());
    m_lifeShadow3->draw(getGame()->getRenderTarget());
    m_lifeShadow4->draw(getGame()->getRenderTarget());

    m_life1->draw(getGame()->getRenderTarget());
    m_life2->draw(getGame()->getRenderTarget());
    m_life3->draw(getGame()->getRenderTarget());
    m_life4->draw(getGame()->getRenderTarget());
}
