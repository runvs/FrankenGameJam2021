#include "life_display.hpp"

LifeDisplay::LifeDisplay(std::vector<std::shared_ptr<jt::DrawableInterface>> drawables)
    : m_drawables { drawables }
{
}
void LifeDisplay::notify(int value)
{
    //    std::cout << "lifedisplay notify: " << value << std::endl;
    for (std::size_t i = 0u; i != m_drawables.size(); ++i) {
        auto color = (i < value) ? jt::colors::White : jt::colors::Transparent;
        if (value <= 0) {
            color = jt::colors::Transparent;
        }
        m_drawables.at(i)->setColor(color);
    }
}
