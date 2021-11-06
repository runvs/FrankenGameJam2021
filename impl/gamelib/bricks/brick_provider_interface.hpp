#ifndef MYAWESOMEGAME_BRICK_PROVIDER_INTERFACE_HPP
#define MYAWESOMEGAME_BRICK_PROVIDER_INTERFACE_HPP

#include "brick_interface.hpp"
#include <memory>

class BrickProviderInterface {
public:
    virtual ~BrickProviderInterface() = default;

    virtual std::function<std::shared_ptr<BrickInterface>(std::shared_ptr<jt::Box2DWorldInterface>)>
    getNextBrickFunction() = 0;
};

#endif // MYAWESOMEGAME_BRICK_PROVIDER_INTERFACE_HPP
