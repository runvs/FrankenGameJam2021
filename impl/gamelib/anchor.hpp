#ifndef MYAWESOMEGAME_ANCHOR_HPP
#define MYAWESOMEGAME_ANCHOR_HPP

#include "box2d_object.hpp"
#include "game_object.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include <memory>

class Anchor : public jt::Box2DObject {
public:
    Anchor(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
    void doKill() override;
    void doDestroy() override;
};

#endif // MYAWESOMEGAME_ANCHOR_HPP
