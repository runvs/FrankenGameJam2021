#ifndef GUARD_JAMTEMPLATE_BOX2DWRAPPER_HPP_GUARD
#define GUARD_JAMTEMPLATE_BOX2DWRAPPER_HPP_GUARD

#include "Box2D/Box2D.h"
#include <cassert>

namespace jt {
/// Interface for box2World
class Box2DWorldInterface {
public:
    /// Create a physics body
    /// \param definition the definition describing the body
    /// \return the created body
    virtual b2Body* createBody(const b2BodyDef* definition) = 0;

    /// Destroy a physics body
    /// \param body pointer to the body to be destroyed
    virtual void destroyBody(b2Body* body) = 0;

    /// <summary>
    /// Create a Box2D joint
    /// </summary>
    /// <param name="defintion">The definition describing the joint</param>
    /// <returns>The created joint</returns>
    virtual b2Joint* createJoint(const b2JointDef* defintion) = 0;

    /// <summary>
    /// Destory a Box2D joint
    /// </summary>
    /// <param name="joint">Pointer to the joint to be destroyed</param>
    virtual void destroyJoint(b2Joint* joint) = 0;

    virtual void step(float elapsed, int velocityIterations, int positionIterations) = 0;

    /// Destructor
    virtual ~Box2DWorldInterface() = default;
};

/// Implementation of the Box2DWorldInterface
class Box2DWorldWrapper : public Box2DWorldInterface {
public:
    Box2DWorldWrapper(const std::shared_ptr<b2World> world)
        : m_world { world }
    {
    }

    b2Body* createBody(const b2BodyDef* defintion) override
    {
        assert(!m_world.expired());
        return m_world.lock()->CreateBody(defintion);
    }

    void destroyBody(b2Body* body) override
    {
        if (m_world.expired()) {
            return;
        }
        m_world.lock()->DestroyBody(body);
    }

    b2Joint* createJoint(const b2JointDef* defintion) override
    {
        assert(!m_world.expired());
        return m_world.lock()->CreateJoint(defintion);
    }

    void destroyJoint(b2Joint* joint) override
    {
        if (m_world.expired()) {
            return;
        }
        m_world.lock()->DestroyJoint(joint);
    }

    void step(float elapsed, int velocityIterations, int positionIterations) override
    {
        if (m_world.expired()) {
            return;
        }
        m_world.lock()->Step(elapsed, velocityIterations, positionIterations);
    }

private:
    // TODO
    std::weak_ptr<b2World> m_world;
};
} // namespace jt

#endif
