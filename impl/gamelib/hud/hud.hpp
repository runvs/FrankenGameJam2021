#ifndef GAME_HUD_HPP_INCLUDEGUARD
#define GAME_HUD_HPP_INCLUDEGUARD

#include "game_object.hpp"
#include "observer_interface.hpp"
#include "sprite.hpp"
#include "text.hpp"

class ScoreDisplay;

class Hud : public jt::GameObject {
public:
    std::shared_ptr<ObserverInterface<int>> getObserverScore() const;

private:
    std::shared_ptr<ScoreDisplay> m_scoreP1Display;

    jt::Text::Sptr m_scoreP1Text;

    void doCreate() override;

    void doUpdate(float const elapsed) override;

    void doDraw() const override;
};

#endif
