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

    bool isFixated() const override;
    void fixate() override;

    void freeze() override;
    bool isFrozen() const override;

protected:
    std::shared_ptr<jt::DrawableInterface> m_drawable;
    bool m_isFrozen { false };
    bool m_isFixated { false };

private:
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
};

#endif // MYAWESOMEGAME_BRICK_IMPL_HPP
