#include "atmospheric_sounds.hpp"
#include "game_properties.hpp"
#include "random.hpp"
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

    m_soundCrows = std::make_shared<jt::SoundGroup>();
    m_soundCrows->load("assets/sfx/crow1.ogg");
    m_soundCrows->load("assets/sfx/crow2.ogg");
    m_soundCrows->load("assets/sfx/crow3.ogg");
    m_soundCrows->load("assets/sfx/crow4.ogg");
    m_soundCrows->load("assets/sfx/crow5.ogg");
    m_soundCrows->setVolume(0.0f);

    m_soundSatelliteBeeps = std::make_shared<jt::SoundGroup>();
    m_soundSatelliteBeeps->load("assets/sfx/beep_pattern1.ogg");
    m_soundSatelliteBeeps->load("assets/sfx/beep_pattern2.ogg");
    m_soundSatelliteBeeps->load("assets/sfx/beep_pattern3.ogg");
    m_soundSatelliteBeeps->setVolume(0.0f);

    m_soundIntercom = std::make_shared<jt::SoundGroup>();
    m_soundIntercom->load("assets/sfx/intercom1.ogg");
    m_soundIntercom->load("assets/sfx/intercom2.ogg");
    m_soundIntercom->load("assets/sfx/intercom3.ogg");
    m_soundIntercom->load("assets/sfx/intercom4.ogg");
    m_soundIntercom->setVolume(0.0f);
}

void AtmosphericSounds::handleVolumes(float camPosY)
{
    if (GP::MuteAudio()) {
        m_soundAtmospheric1->setVolume(0.0f);
        m_soundAtmospheric2->setVolume(0.0f);
        m_soundAtmospheric3->setVolume(0.0f);
        m_soundCrows->setVolume(0.0f);
        m_soundSatelliteBeeps->setVolume(0.0f);
        m_soundIntercom->setVolume(0.0f);
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
    m_soundCrows->setVolume(volume * 0.5f);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint3() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundAtmospheric3->setVolume(volume);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint4() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundSatelliteBeeps->setVolume(volume * 0.1f);

    volume = (1.0f - fabs(GP::AtmosphericSoundBreakpoint5() - camPosY) / 300.0f) * 50.0f;
    if (volume < 0.0f)
        volume = 0.0f;
    m_soundIntercom->setVolume(volume * 0.1f);
}

void AtmosphericSounds::doUpdate(float elapsed)
{
    m_crowTimer -= elapsed;
    m_satelliteBeepTimer -= elapsed;
    m_intercomTimer -= elapsed;

    if (m_crowTimer <= 0.0f) {
        m_crowTimer += jt::Random::getFloatGauss(6.0f, 1.0f);
        m_soundCrows->play();
    }

    if (m_satelliteBeepTimer <= 0.0f) {
        m_satelliteBeepTimer += jt::Random::getFloatGauss(10.f, 1.0f);
        m_soundSatelliteBeeps->play();
    }

    if (m_intercomTimer <= 0.0f) {
        m_intercomTimer += jt::Random::getFloatGauss(5.f, 2.0f);
        m_soundIntercom->play();
    }
}
