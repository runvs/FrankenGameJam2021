#include "brick_provider_random.hpp"
#include "brick_factory.hpp"
#include "random.hpp"
#include "system_helper.hpp"

BrickProviderRandom::BrickProviderRandom()
{
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world, float yPos) {
        jt::Vector2 spawnPosition { jt::Random::getFloat(40.0f, 200.0f), yPos };

        return BrickFactory::createBrickQuadratic(world, spawnPosition);
    });
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world, float yPos) {
        jt::Vector2 spawnPosition { jt::Random::getFloat(40.0f, 200.0f), yPos };
        return BrickFactory::createBrickCuttingEdge(world, spawnPosition);
    });
    m_functions.emplace_back([](std::shared_ptr<jt::Box2DWorldInterface> world, float yPos) {
        jt::Vector2 spawnPosition { jt::Random::getFloat(40.0f, 200.0f), yPos };
        return BrickFactory::createBrickRectangle2x1(world, spawnPosition);
    });
}

std::function<std::shared_ptr<BrickInterface>(std::shared_ptr<jt::Box2DWorldInterface>, float)>
BrickProviderRandom::getNextBrickFunction()
{
    return *jt::SystemHelper::select_randomly(m_functions.begin(), m_functions.end());
}
