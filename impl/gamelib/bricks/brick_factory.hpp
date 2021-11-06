#ifndef MYAWESOMEGAME_BRICK_FACTORY_HPP
#define MYAWESOMEGAME_BRICK_FACTORY_HPP

#include "brick_interface.hpp"
#include <memory>

class BrickFactory {
public:
    static std::shared_ptr<BrickInterface> createBrickQuadratic(
        std::shared_ptr<jt::Box2DWorldInterface> world);

    static std::shared_ptr<BrickInterface> createBrickRectangle2x1(
        std::shared_ptr<jt::Box2DWorldInterface> world);

    static std::shared_ptr<BrickInterface> createBrickL(
        std::shared_ptr<jt::Box2DWorldInterface> world);
};

#endif // MYAWESOMEGAME_BRICK_FACTORY_HPP
