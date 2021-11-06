#ifndef MYAWESOMEGAME_BRICK_HPP
#define MYAWESOMEGAME_BRICK_HPP

#include "box2d_object.hpp"
#include "shape.hpp"

class Brick : public jt::Box2DObject {
public:
    Brick(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    std::shared_ptr<jt::Shape> m_shape;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
    void doKill() override;
    void doDestroy() override;
};

#endif // MYAWESOMEGAME_BRICK_HPP
