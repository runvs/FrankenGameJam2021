#ifndef GEMGA_SCREEN_RECORDER_INTERFACE_HPP
#define GEMGA_SCREEN_RECORDER_INTERFACE_HPP

namespace jt {
class ScreenRecorderInterface {
public:
    virtual ~ScreenRecorderInterface() = default;

    virtual void toggleRecording() = 0;
    virtual void startRecording() = 0;
    virtual void stopRecording() = 0;
    virtual void takeScreenshot() = 0;
};
} // namespace jt

#endif // GEMGA_SCREEN_RECORDER_INTERFACE_HPP
