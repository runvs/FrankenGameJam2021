#ifndef GEMGA_ATMOSPHERIC_SOUNDS_HPP
#define GEMGA_ATMOSPHERIC_SOUNDS_HPP

#include "game_object.hpp"
#include "sound.hpp"
#include "sound_group.hpp"

class AtmosphericSounds : public jt::GameObject {
private:
    std::shared_ptr<jt::Sound> m_soundAtmospheric1;
    std::shared_ptr<jt::Sound> m_soundAtmospheric2;
    std::shared_ptr<jt::Sound> m_soundAtmospheric3;

    std::shared_ptr<jt::SoundGroup> m_soundCrows;
    std::shared_ptr<jt::SoundGroup> m_soundSatelliteBeeps;
    std::shared_ptr<jt::SoundGroup> m_soundIntercom;

    void doCreate() override;
    void doUpdate(float elapsed) override;

    float m_crowTimer { 0.0f };
    float m_satelliteBeepTimer { 0.0f };
    float m_intercomTimer { 0.0f };

public:
    void handleVolumes(float yPos);
};

#endif // GEMGA_ATMOSPHERIC_SOUNDS_HPP
