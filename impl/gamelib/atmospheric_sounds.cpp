#include "atmospheric_sounds.hpp"
#include "game_properties.hpp"
#include <cmath>

void AtmosphericSounds::doCreate()
{
    m_soundAtmospheric1 = std::make_shared<jt::Sound>();
    m_soundAtmospheric1->load("assets/sfx/atmosphere/01_birds_and_frogs_at_forest_pond.ogg");
    m_soundAtmospheric1->setLoop(true);
    m_soundAtmospheric1->setVolume(0.0f);
    m_soundAtmospheric1->play();

    m_soundAtmospheric2 = std::make_shared<jt::Sound>();
    m_soundAtmospheric2->load("assets/sfx/atmosphere/02_wind_in_forest.ogg");
    m_soundAtmospheric2->setLoop(true);
    m_soundAtmospheric2->setVolume(0.0f);
    m_soundAtmospheric2->play();

    m_soundAtmospheric3 = std::make_shared<jt::Sound>();
    m_soundAtmospheric3->load("assets/sfx/atmosphere/03_strong_wind.ogg");
    m_soundAtmospheric3->setLoop(true);
    m_soundAtmospheric3->setVolume(0.0f);
    m_soundAtmospheric3->play();
}

void AtmosphericSounds::handleVolumes(float camPosY)
{
    if (GP::MuteAudio()) {
        m_soundAtmospheric1->setVolume(0.0f);
        m_soundAtmospheric2->setVolume(0.0f);
        m_soundAtmospheric3->setVolume(0.0f);
        return;
    }

    float volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint1() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric1->setVolume(volume);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint2() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric2->setVolume(volume);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint3() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric3->setVolume(volume);
}
