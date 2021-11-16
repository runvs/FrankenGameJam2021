#ifndef MYAWESOMEGAME_PLATFORM_HPP
#define MYAWESOMEGAME_PLATFORM_HPP

#include "box2d_object.hpp"
#include "game_object.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include <memory>

class Platform : public jt::Box2DObject {
public:
    Platform(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def,
        const bool anchor = false);

private:
    jt::Vector2 m_platformSize { 64, 6 };
    std::shared_ptr<jt::Sprite> m_sprite;
    bool m_anchor;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
    void doKill() override;
    void doDestroy() override;

    bool mouseLeft();
    bool mouseRight();
};

#endif // MYAWESOMEGAME_PLATFORM_HPP
