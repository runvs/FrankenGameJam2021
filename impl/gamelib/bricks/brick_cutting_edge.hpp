#ifndef MYAWESOMEGAME_BRICK_CUTTING_EDGE_HPP
#define MYAWESOMEGAME_BRICK_CUTTING_EDGE_HPP

#include "brick_impl.hpp"
#include "sprite.hpp"

class BrickCuttingEdge : public BrickImpl {
public:
    BrickCuttingEdge(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_CUTTING_EDGE_HPP
