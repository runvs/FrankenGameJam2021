#ifndef MYAWESOMEGAME_BRICK_DIAMOND_HPP
#define MYAWESOMEGAME_BRICK_DIAMOND_HPP

#include "brick_impl.hpp"
#include "sprite.hpp"
// No, not that diamond! That's a "cutting edge brick". We mean geometrical diamonds, like in <>.
class BrickDiamond : public BrickImpl {
public:
    BrickDiamond(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);

private:
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_DIAMOND_HPP
