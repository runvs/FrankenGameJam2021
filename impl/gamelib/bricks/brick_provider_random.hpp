#ifndef MYAWESOMEGAME_BRICK_PROVIDER_RANDOM_HPP
#define MYAWESOMEGAME_BRICK_PROVIDER_RANDOM_HPP

#include "box2d_world_interface.hpp"
#include "brick_interface.hpp"
#include "brick_provider_interface.hpp"
#include <functional>
#include <vector>

class BrickProviderRandom : public BrickProviderInterface {
public:
    BrickProviderRandom();
    std::function<std::shared_ptr<BrickInterface>(std::shared_ptr<jt::Box2DWorldInterface>, float)>
    getNextBrickFunction() override;

private:
    std::vector<std::function<std::shared_ptr<BrickInterface>(
        std::shared_ptr<jt::Box2DWorldInterface>, float)>>
        m_functions;
};

#endif // MYAWESOMEGAME_BRICK_PROVIDER_RANDOM_HPP
