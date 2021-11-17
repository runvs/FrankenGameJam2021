#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include "animation.hpp"
#include "game_state.hpp"
#include "parallax_background.hpp"

namespace jt {

class Text;
class Shape;
class Animation;
class Sprite;

} // namespace jt

class StateMenu : public jt::GameState {
public:
    StateMenu();

    void setScore(int /*s*/) {};

private:
    std::shared_ptr<jt::Animation> m_logo;
    std::shared_ptr<jt::Sprite> m_logoGlow;

    std::shared_ptr<jt::Text> m_text_Explanation;
    std::shared_ptr<jt::Text> m_text_Credits;

    std::shared_ptr<jt::Shape> m_overlay;
    std::shared_ptr<jt::Sprite> m_vignette;

    bool m_started { false };

    void doInternalCreate() override;

    void createVignette();
    void createShapes();
    void createBackground();

    void createMenuText();
    void createTextCredits();
    void createTextExplanation();
    void createLogo();

    void createTweens();
    void createInstructionTweenScaleUp();
    void createInstructionTweenScaleDown();
    void createTweenOverlayAlpha();
    void createTweenCreditsPosition();
    void createTweenExplanationScale();

    void createTweenTransition();

    void doInternalUpdate(float const elapsed) override;
    void updateDrawables(const float& elapsed);
    void checkForTransitionToStateGame();
    void startTransitionToStateGame();

    void doInternalDraw() const override;
};

#endif
