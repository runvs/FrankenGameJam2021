#ifndef GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD
#define GAME_GAMEPROPERTIES_HPP_INCLUDEGUARD

#include "color.hpp"
#include "vector.hpp"
#include <string>

class GP {
public:
    GP() = delete;

    static std::string GameName() { return "Gemga"; }
    static std::string AuthorName()
    {
        return "adkiem, Aneira, BloodyOrange,\nLaguna, Synchronleuchter, Thunraz\n";
    }
    static std::string JamName() { return "Frankengamejam 2021"; }
    static std::string JamDate() { return "November 2021"; }

    static jt::Vector2 GetWindowSize() { return jt::Vector2 { 720, 900 }; }
    static float GetZoom() { return 3.0f; }
    static jt::Vector2 GetScreenSize() { return GetWindowSize() * (1.0f / GetZoom()); }

    static jt::Color PaletteBackground() { return GP::PaletteColor6(); }
    static jt::Color PaletteFontFront() { return GP::PaletteColor4(); }
    static jt::Color PaletteFontShadow();

    static jt::Color PaletteColor1() { return jt::Color { 5, 64, 71 }; }
    static jt::Color PaletteColor2() { return jt::Color { 32, 142, 68 }; }
    static jt::Color PaletteColor3() { return jt::Color { 223, 123, 0 }; }
    static jt::Color PaletteColor4();
    static jt::Color PaletteColor5();
    static jt::Color PaletteColor6();
    static jt::Color PaletteColor7();
    static jt::Color PaletteColor8();

    static int PhysicVelocityIterations();
    static int PhysicPositionIterations();

    static int RemoveBrickDeadzone();

    static float AtmosphericSoundBreakpoint1();
    static float AtmosphericSoundBreakpoint2();
    static float AtmosphericSoundBreakpoint3();

    static float PlatformMovementSpeed();
    static float PhysicsBrickDensity();
    static float BrickFixVelocityThreshold();
    static float PhysicsBrickRestitution();

    static float GemDelayMin();
    static float GemDelayMax();

    static bool& MuteAudio();
    static float MaxMusicVolume();
    static int AnchorHeight();
};

#endif
