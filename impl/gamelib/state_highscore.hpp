#ifndef GEMGA_STATE_HIGHSCORE_HPP
#define GEMGA_STATE_HIGHSCORE_HPP

#include "game_state.hpp"

class StateHighscore : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // GEMGA_STATE_HIGHSCORE_HPP
