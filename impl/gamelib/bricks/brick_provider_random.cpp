#include "brick_provider_random.hpp"
#include "brick_factory.hpp"
#include "system_helper.hpp"

BrickProviderRandom::BrickProviderRandom()
{
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world) {
        return BrickFactory::createBrickQuadratic(world);
    });
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world) {
        return BrickFactory::createBrickL(world);
    });
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world) {
        return BrickFactory::createBrickRectangle2x1(world);
    });
}

std::function<std::shared_ptr<BrickInterface>(std::shared_ptr<jt::Box2DWorldInterface>)>
BrickProviderRandom::getNextBrickFunction()
{
    return *jt::SystemHelper::select_randomly(m_functions.begin(), m_functions.end());
}
