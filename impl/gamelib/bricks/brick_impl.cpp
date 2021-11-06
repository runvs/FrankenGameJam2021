#include "brick_impl.hpp"
#include "game_interface.hpp"

BrickImpl::BrickImpl(std::shared_ptr<jt::Box2DWorldInterface> world, const b2BodyDef* def)
    : BrickInterface(world, def)
{
}

void BrickImpl::drawPreview() const
{
    const float previewOffset = 20; // TODO put this in GP
    auto const initialPosition = m_drawable->getPosition();
    auto const initialColor = m_drawable->getColor();

    for (float i = 1.0f; i <= 4.0f; ++i) {

        m_drawable->setPosition(
            jt::Vector2 { initialPosition.x(), initialPosition.y() + i * previewOffset });
        m_drawable->setColor(jt::Color { initialColor.r(), initialColor.g(), initialColor.b(),
            static_cast<uint8_t>(80u * 1.0f / i) });
        m_drawable->update(0.0f);
        m_drawable->draw(getGame()->getRenderTarget());
    }

    m_drawable->setPosition(initialPosition);
    m_drawable->setColor(initialColor);
}
std::shared_ptr<jt::DrawableInterface> BrickImpl::getDrawable() { return m_drawable; }

bool BrickImpl::isFrozen() const { return m_isFrozen; }
void BrickImpl::freeze() { m_isFrozen = true; }

bool BrickImpl::isFixated() const { return m_isFixated; }
void BrickImpl::fixate() { m_isFixated = true; }
