#include "game_properties.hpp"

int GP::RemoveBrickDeadzone() { return 16; }
int GP::PhysicPositionIterations() { return 10; }
int GP::PhysicVelocityIterations() { return 6; }

float GP::PlatformMovementSpeed() { return 65.0f; }
float GP::PhysicsBrickDensity() { return 0.1f; }
float GP::BrickFixVelocityThreshold() { return 42.0f; }
float GP::PhysicsBrickRestitution() { return -0.4f; }
float GP::AtmosphericSoundBreakpoint1() { return 0.0f; }
float GP::AtmosphericSoundBreakpoint2() { return -300.0f; }
float GP::AtmosphericSoundBreakpoint3() { return -600.0f; }
