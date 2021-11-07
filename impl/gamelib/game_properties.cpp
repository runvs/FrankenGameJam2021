#include "game_properties.hpp"

int GP::RemoveBrickDeadzone() { return 32; }
int GP::PhysicPositionIterations() { return 10; }
int GP::PhysicVelocityIterations() { return 6; }

float GP::PlatformMovementSpeed() { return 65.0f; }
float GP::PhysicsBrickDensity() { return 0.1f; }
float GP::BrickFixVelocityThreshold() { return 42.0f; }
float GP::PhysicsBrickRestitution() { return -0.4f; }
float GP::AtmosphericSoundBreakpoint1() { return 0.0f; }
float GP::AtmosphericSoundBreakpoint2() { return -300.0f; }
float GP::AtmosphericSoundBreakpoint3() { return -600.0f; }

float GP::GemDelayMin() { return 0.8f; }
float GP::GemDelayMax() { return 10.0f; }
jt::Color GP::PaletteFontShadow() { return GP::PaletteColor7(); }
jt::Color GP::PaletteColor4() { return jt::Color { 239, 255, 124 }; }
jt::Color GP::PaletteColor5() { return jt::Color { 220, 220, 220 }; }
jt::Color GP::PaletteColor6() { return jt::Color { 184, 39, 45 }; }
jt::Color GP::PaletteColor7() { return jt::Color { 64, 64, 64 }; }
jt::Color GP::PaletteColor8() { return jt::Color { 157, 64, 43 }; }
