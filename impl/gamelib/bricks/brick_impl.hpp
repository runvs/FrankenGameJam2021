#ifndef MYAWESOMEGAME_BRICK_IMPL_HPP
#define MYAWESOMEGAME_BRICK_IMPL_HPP

#include "brick_interface.hpp"
#include "shape.hpp"
#include <memory>

class BrickImpl : public BrickInterface {
public:
    BrickImpl(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def);
    void drawPreview() const override;
    std::shared_ptr<jt::DrawableInterface> getDrawable() override;

protected:
    std::shared_ptr<jt::DrawableInterface> m_drawable;
};

#endif MYAWESOMEGAME_BRICK_IMPL_HPP
