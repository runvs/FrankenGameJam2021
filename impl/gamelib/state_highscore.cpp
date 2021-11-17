#include "state_highscore.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "game_properties.hpp"
#include "highscore.hpp"
#include "parallax_background.hpp"
#include "state_menu.hpp"
#include <algorithm>
#include <tweens/tween_alpha.hpp>

void StateHighscore::doInternalCreate()
{
    add(std::make_shared<ParallaxBackground>());

    auto highscores = loadHighscores();
    highscores.push_back(m_newScore);

    std::sort(highscores.rbegin(), highscores.rend());

    for (int i = 0; i != 5; ++i) {
        auto currentScore = highscores.at(i);
        auto text = jt::dh::createText(
            getGame()->getRenderTarget(), std::to_string(currentScore), 12U, GP::PaletteColor3());
        text->setPosition(jt::Vector2 { 100.0f, 100.0f + i * 20.0f });

        m_texts.push_back(text);
    }
    saveHighscores(highscores);

    m_vignette = jt::dh::createVignette(GP::GetScreenSize());
    m_vignette->setColor({ 255, 255, 255, 110 });

    m_overlay = jt::dh::createRectShape(GP::GetScreenSize(), jt::colors::Black);

    auto tween = jt::TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tween->setSkipFrames();
    add(tween);
}
void StateHighscore::doInternalUpdate(float elapsed)
{
    for (auto t : m_texts) {
        t->update(elapsed);
    }

    m_vignette->update(elapsed);
    m_overlay->update(elapsed);

    if (getAge() > 0.5f) {
        if (getGame()->input()->keyboard()->justReleased(jt::KeyCode::Space)
            || getGame()->input()->mouse()->justReleased(jt::MouseButtonCode::MBLeft)) {
            getGame()->switchState(std::make_shared<StateMenu>());
        }
    }
}
void StateHighscore::doInternalDraw() const
{
    for (auto t : m_texts) {
        t->draw(getGame()->getRenderTarget());
    }

    m_vignette->draw(getGame()->getRenderTarget());
    m_overlay->draw(getGame()->getRenderTarget());
}

void StateHighscore::setScore(int newScore) { m_newScore = newScore; }
