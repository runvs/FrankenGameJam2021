#ifndef MYAWESOMEGAME_BRICK_OCTAGON_HPP
#define MYAWESOMEGAME_BRICK_OCTAGON_HPP

#include "brick_impl.hpp"
#include "sprite.hpp"

class BrickOctagon : public BrickImpl {
public:
    BrickOctagon(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
};

#endif // MYAWESOMEGAME_BRICK_OCTAGON_HPP
