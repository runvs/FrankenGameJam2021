﻿#ifndef JAMTEMPLATE_UNITTEST_MOCKWINDOW_HPP_INCLUDEGUARD
#define JAMTEMPLATE_UNITTEST_MOCKWINDOW_HPP_INCLUDEGUARD

#include "render_window_interface.hpp"
#include "sprite.hpp"
#include <gmock/gmock.h>

class MockWindow : public ::jt::RenderWindowInterface {
public:
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(void, checkForClose, (), (override));
    MOCK_METHOD(jt::Vector2, getSize, (), (const, override));
    MOCK_METHOD(void, draw, (std::unique_ptr<jt::Sprite>&), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePosition, (), (override));
    MOCK_METHOD(std::shared_ptr<jt::renderTarget>, createRenderTarget, (), (override));
    MOCK_METHOD(void, setMouseCursorVisible, (bool), (override));
    MOCK_METHOD(bool, getMouseCursorVisible, (), (const, override));
};

#endif
