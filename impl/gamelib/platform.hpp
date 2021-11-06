#ifndef MYAWESOMEGAME_PLATFORM_HPP
#define MYAWESOMEGAME_PLATFORM_HPP

#include "game_object.hpp"
#include "box2d_object.hpp"
#include "shape.hpp"
#include <memory>

class Platform : public jt::Box2DObject {
public:
    Platform(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);
private:

    std::shared_ptr<jt::Shape> m_shape;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
    void doKill() override;
    void doDestroy() override;

};

#endif // MYAWESOMEGAME_PLATFORM_HPP
