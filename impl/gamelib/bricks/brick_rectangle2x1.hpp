#ifndef MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP
#define MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP

#include "brick_impl.hpp"
#include <shape.hpp>

class BrickRectangle2x1 : public BrickImpl {
public:
    BrickRectangle2x1(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
};

#endif // MYAWESOMEGAME_BRICK_RECTANGLE2X1_HPP
