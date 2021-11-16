#ifndef GEMGA_SCREEN_RECORDER_HPP
#define GEMGA_SCREEN_RECORDER_HPP

#include "screen_recorder_interface.hpp"

namespace jt {
class ScreenRecorder : public ScreenRecorderInterface {
public:
    void toggleRecording() override;
    void startRecording() override;
    void stopRecording() override;

private:
    bool m_isRecording { false };
};

} // namespace jt
#endif // GEMGA_SCREEN_RECORDER_HPP
