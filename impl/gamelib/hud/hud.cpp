#include "hud.hpp"
#include "../game_properties.hpp"
#include "color.hpp"
#include "game_interface.hpp"
#include "score_display.hpp"

std::shared_ptr<ObserverInterface<int>> Hud::getObserverScore() const { return m_scoreP1Display; }

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
}

void Hud::doUpdate(float const elapsed) { m_scoreP1Text->update(elapsed); }

void Hud::doDraw() const { m_scoreP1Text->draw(getGame()->getRenderTarget()); }
