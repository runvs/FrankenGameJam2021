#ifndef MYAWESOMEGAME_BRICK_HPP
#define MYAWESOMEGAME_BRICK_HPP

#include "brick_interface.hpp"
#include "shape.hpp"

class Brick : public BrickInterface {
public:
    Brick(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    std::shared_ptr<jt::Shape> m_shape;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_HPP
