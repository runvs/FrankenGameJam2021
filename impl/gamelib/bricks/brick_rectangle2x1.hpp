#ifndef MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP
#define MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP

#include "brick_interface.hpp"
#include <shape.hpp>

class BrickRectangle2x1 : public BrickInterface {
public:
    BrickRectangle2x1(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    std::shared_ptr<jt::Shape> m_shape;

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP
