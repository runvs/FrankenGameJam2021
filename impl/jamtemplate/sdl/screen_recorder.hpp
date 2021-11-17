#ifndef GEMGA_SCREEN_RECORDER_HPP
#define GEMGA_SCREEN_RECORDER_HPP

#include "screen_recorder_interface.hpp"

namespace jt {
class ScreenRecorder : public ScreenRecorderInterface {
public:
    virtual void toggleRecording() override;
    virtual void startRecording() override;
    virtual void stopRecording() override;
    virtual void takeScreenshot() override;
    virtual bool isRecording() override;

private:
    bool m_isRecording { false };
};

} // namespace jt
#endif // GEMGA_SCREEN_RECORDER_HPP
