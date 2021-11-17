#ifndef GEMGA_STATE_HIGHSCORE_HPP
#define GEMGA_STATE_HIGHSCORE_HPP

#include "game_state.hpp"
#include <shape.hpp>
#include <sprite.hpp>
#include <text.hpp>

class StateHighscore : public jt::GameState {

public:
    void setScore(int newScore);

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    std::vector<std::shared_ptr<jt::Text>> m_texts;
    int m_newScore { 0 };

    std::shared_ptr<jt::Shape> m_overlay;
    std::shared_ptr<jt::Sprite> m_vignette;
};

#endif // GEMGA_STATE_HIGHSCORE_HPP
