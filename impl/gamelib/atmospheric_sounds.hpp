#ifndef GEMGA_ATMOSPHERIC_SOUNDS_HPP
#define GEMGA_ATMOSPHERIC_SOUNDS_HPP

#include "game_object.hpp"
#include "sound.hpp"

class AtmosphericSounds : public jt::GameObject {
private:
    std::shared_ptr<jt::Sound> m_soundAtmospheric1;
    std::shared_ptr<jt::Sound> m_soundAtmospheric2;
    std::shared_ptr<jt::Sound> m_soundAtmospheric3;

    virtual void doCreate();

public:
    void handleVolumes(float yPos);
};

#endif // GEMGA_ATMOSPHERIC_SOUNDS_HPP
