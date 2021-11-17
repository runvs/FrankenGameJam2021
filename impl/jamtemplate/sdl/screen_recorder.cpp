#include "screen_recorder.hpp"
#ifdef ENABLE_WEB
#include <emscripten.h>
#endif

namespace jt {

void ScreenRecorder::toggleRecording()
{
    m_isRecording = !m_isRecording;
#ifdef ENABLE_WEB
    emscripten_run_script("recorder.toggleRecording()");
#endif
}
void ScreenRecorder::startRecording()
{
    m_isRecording = true;
#ifdef ENABLE_WEB
    emscripten_run_script("recorder.startRecording()");
#endif
}
void ScreenRecorder::stopRecording()
{
    m_isRecording = false;
#ifdef ENABLE_WEB
    emscripten_run_script("recorder.stopRecording()");
#endif
}

void ScreenRecorder::takeScreenshot()
{
#ifdef ENABLE_WEB
    emscripten_run_script("recorder.takeScreenshot()");
#endif
}

void ScreenRecorder::isRecording() { return m_isRecording; }

} // namespace jt
