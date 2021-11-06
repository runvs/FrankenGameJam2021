#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include "box2d_wrapper.hpp"
#include "bricks/brick_interface.hpp"
#include "bricks/brick_provider_interface.hpp"
#include "game_state.hpp"
#include "object_group.hpp"
#include "platform.hpp"
#include "timer.hpp"
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
} // namespace jt
class b2World;

class Hud;

class StateGame : public jt::GameState {

private:
    std::shared_ptr<jt::Shape> m_background;
    std::shared_ptr<jt::Shape> m_overlay;
    std::shared_ptr<jt::Sprite> m_vignette;
    std::shared_ptr<Hud> m_hud;
    std::shared_ptr<b2World> m_worldImpl { nullptr };
    std::shared_ptr<jt::Box2DWorldInterface> m_world { nullptr };

    std::shared_ptr<Platform> m_platform { nullptr };

    std::shared_ptr<jt::ObjectGroup<BrickInterface>> m_bricks { nullptr };
    std::shared_ptr<BrickInterface> m_currentBrick { nullptr };
    std::shared_ptr<BrickInterface> m_currentPendingBrick { nullptr };

    std::shared_ptr<BrickProviderInterface> m_brickProvider { nullptr };

    bool m_running { false };
    bool m_hasEnded { false };

    int m_score { 0 };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void checkForGameOver();

    void endGame();
    void spawnBricks();
    void spawnNewBrick();
    void rotateCurrentBrick(float const elapsed);

    bool isCurrentBrick(b2Body const* const bodyPtr) const;

    void handleCurrentBlockCollision(b2Body* p1, b2Body* p2);
    void addJointToPlatform(std::shared_ptr<BrickInterface> brick);
};

#endif
