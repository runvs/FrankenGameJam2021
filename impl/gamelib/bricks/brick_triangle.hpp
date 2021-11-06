#ifndef MYAWESOMEGAME_BRICK_TRIANGLE_HPP
#define MYAWESOMEGAME_BRICK_TRIANGLE_HPP

#include "brick_impl.hpp"
#include "sprite.hpp"

class BrickTriangle : public BrickImpl {
public:
    BrickTriangle(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_TRIANGLE_HPP
