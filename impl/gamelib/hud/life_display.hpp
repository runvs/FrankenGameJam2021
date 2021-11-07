
#ifndef MYAWESOMEGAME_LIFE_DISPLAY_HPP
#define MYAWESOMEGAME_LIFE_DISPLAY_HPP

#include "drawable_interface.hpp"
#include "observer_interface.hpp"
#include <memory>
#include <vector>

class LifeDisplay : public ObserverInterface<int> {
public:
    explicit LifeDisplay(std::vector<std::shared_ptr<jt::DrawableInterface>> drawables);
    void notify(int value) override;

private:
    std::vector<std::shared_ptr<jt::DrawableInterface>> m_drawables;
};

#endif // MYAWESOMEGAME_LIFE_DISPLAY_HPP
