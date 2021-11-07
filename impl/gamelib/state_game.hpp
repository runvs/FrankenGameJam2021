#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include "box2d_wrapper.hpp"
#include "bricks/brick_interface.hpp"
#include "bricks/brick_provider_interface.hpp"
#include "game_state.hpp"
#include "object_group.hpp"
#include "particle_system.hpp"
#include "platform.hpp"
#include "sound.hpp"
#include "sound_group.hpp"
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
    std::shared_ptr<jt::Sprite> m_background;
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

    std::shared_ptr<jt::Sound> m_soundBrickSpawn;
    std::shared_ptr<jt::SoundGroup> m_soundGroupBrickContact;
    std::shared_ptr<jt::Sound> m_soundGameOver;
    std::shared_ptr<jt::Sound> m_soundAtmospheric1;
    std::shared_ptr<jt::Sound> m_soundAtmospheric2;
    std::shared_ptr<jt::Sound> m_soundAtmospheric3;

    std::shared_ptr<jt::Sound> m_soundBrickFreeze1;
    std::shared_ptr<jt::Sound> m_soundBrickFreeze2;
    std::shared_ptr<jt::Sound> m_soundBrickFreeze3;
    std::shared_ptr<jt::Sound> m_soundBrickFreeze4;

    std::shared_ptr<jt::ParticleSystem<jt::Shape, 64>> m_brickFixateParticles;

    bool m_running { false };
    bool m_hasEnded { false };

    int m_score { 0 };
    int m_lifeCounter { 0 };

    int m_extra_lifes { 1 };

    float m_maxHeight { 300 };

    bool m_canSpawnNewBrick { true };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void checkForGameOver();

    void endGame();
    void spawnNewBrick();
    void rotateCurrentBrick(float const elapsed);

    bool isCurrentBrick(b2Body const* const bodyPtr) const;

    void handleCurrentBrickCollision(b2Body* p1, b2Body* p2);
    void addDistanceJointsTo(std::shared_ptr<BrickInterface> brick, b2Body* other);
    void fixCurrentBrick(std::shared_ptr<BrickInterface> currentPendingBrick, b2Body* other);
    void moveCamera(float const elapsed);
    void addRevoluteJointTo(std::shared_ptr<BrickInterface> brick);
    void freezeBricks();
    void loseLife();
    float m_loseLifeTimer { 1.0f };
};

#endif
