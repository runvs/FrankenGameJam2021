#ifndef MYAWESOMEGAME_BRICK_QUADRATIC_HPP
#define MYAWESOMEGAME_BRICK_QUADRATIC_HPP

#include "brick_impl.hpp"
#include "shape.hpp"

class BrickQuadratic : public BrickImpl {
public:
    BrickQuadratic(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
};

#endif // MYAWESOMEGAME_BRICK_QUADRATIC_HPP
