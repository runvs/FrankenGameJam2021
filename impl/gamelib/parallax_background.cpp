#include "parallax_background.hpp"
#include "game_interface.hpp"

void ParallaxBackground::doCreate()
{
    m_backgroundSprites = {};
    std::vector<std::string> backgroundSpriteList = { "assets/menu_bg/01_background.png",
        "assets/menu_bg/02_trees_back.png", "assets/menu_bg/03_trees_mid.png",
        "assets/menu_bg/04_trees_front.png", "assets/menu_bg/05_bushes.png",
        "assets/menu_bg/06_grass.png", "assets/menu_bg/07_flies_dust.png" };

    for (auto backgroundSprite : backgroundSpriteList) {
        auto sprite = std::make_shared<jt::Sprite>();
        sprite->loadSprite(backgroundSprite);
        m_backgroundSprites.emplace_back(sprite);
    }
}
void ParallaxBackground::doUpdate(float const elapsed)
{
    for (int i = 0; i < m_backgroundSprites.size(); ++i) {
        const auto sprite = m_backgroundSprites.at(i);
        const jt::Vector2 currentPosition = sprite->getPosition();

        float newX = currentPosition.x() - 0.1f * i;
        newX = newX <= -240.0f ? newX + 240.0f : newX;
        sprite->setPosition(jt::Vector2 { newX, currentPosition.y() });
        sprite->update(elapsed);
    }
}
void ParallaxBackground::doDraw() const
{
    for (auto backgroundSprite : m_backgroundSprites) {
        backgroundSprite->draw(getGame()->getRenderTarget());
    }
}
void ParallaxBackground::doKill() { }
