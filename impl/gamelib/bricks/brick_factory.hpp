#ifndef MYAWESOMEGAME_BRICK_FACTORY_HPP
#define MYAWESOMEGAME_BRICK_FACTORY_HPP

#include "brick_interface.hpp"
#include <memory>

class BrickFactory {
public:
    static std::shared_ptr<BrickInterface> createBrickQuadratic(
        std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition);

    static std::shared_ptr<BrickInterface> createBrickRectangle2x1(
        std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition);

    static std::shared_ptr<BrickInterface> createBrickCuttingEdge(
        std::shared_ptr<jt::Box2DWorldInterface> world, jt::Vector2 const& spawnPosition);

    static b2BodyDef getBodyDef(jt::Vector2 const& spawnPosition);
};

#endif // MYAWESOMEGAME_BRICK_FACTORY_HPP
