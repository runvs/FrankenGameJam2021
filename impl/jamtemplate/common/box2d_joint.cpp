#include "box2d_joint.hpp"

jt::Box2DJoint::Box2DJoint(std::shared_ptr<Box2DWorldInterface> world, const b2JointDef* def) { }

void jt::Box2DJoint::doDestroy() { }

void jt::Box2DJoint::setB2Joint(b2Joint* body) { }
