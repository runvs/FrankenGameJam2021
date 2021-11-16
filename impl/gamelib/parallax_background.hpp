#ifndef GEMGA_PARALLAX_BACKGROUND_HPP
#define GEMGA_PARALLAX_BACKGROUND_HPP

#include "game_object.hpp"
#include "sprite.hpp"
#include <memory>
#include <vector>

class ParallaxBackground : public jt::GameObject {
    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;
    void doKill() override;

    std::vector<std::shared_ptr<jt::Sprite>> m_backgroundSprites;
};

#endif // GEMGA_PARALLAX_BACKGROUND_HPP
