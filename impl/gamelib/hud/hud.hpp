#ifndef GAME_HUD_HPP_INCLUDEGUARD
#define GAME_HUD_HPP_INCLUDEGUARD

#include "game_object.hpp"
#include "observer_interface.hpp"
#include "sprite.hpp"
#include "text.hpp"

class ScoreDisplay;
class LifeDisplay;

class Hud : public jt::GameObject {
public:
    std::shared_ptr<ObserverInterface<int>> getObserverScore() const;
    std::shared_ptr<ObserverInterface<int>> getObserverLife() const;

private:
    std::shared_ptr<ScoreDisplay> m_scoreP1Display;

    std::shared_ptr<LifeDisplay> m_lifeDisplay;

    jt::Text::Sptr m_scoreP1Text;

    jt::Sprite::Sptr m_life1;
    jt::Sprite::Sptr m_life2;
    jt::Sprite::Sptr m_life3;
    jt::Sprite::Sptr m_life4;

    jt::Sprite::Sptr m_lifeShadow1;
    jt::Sprite::Sptr m_lifeShadow2;
    jt::Sprite::Sptr m_lifeShadow3;
    jt::Sprite::Sptr m_lifeShadow4;

    void doCreate() override;

    void doUpdate(float const elapsed) override;

    void doDraw() const override;
    std::shared_ptr<jt::Sprite> setUpLife(int i);
    jt::Sprite::Sptr setUpLifeShadow(int i);
};

#endif
