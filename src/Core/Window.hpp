#pragma once
#include "../Common.hpp"

namespace Window {

    void Init();

    GLFWwindow* GetWindowPointer();
    const WindowedMode& GetWindowMode();
    void SetWindowPointer(GLFWwindow* window);
    void CreateGLFWWindow(const WindowedMode& windowedMode);
    void SetWindowMode(const WindowedMode& windowedMode);
    void ToggleFullscreen();
    void ToggleCursor();
    void ForceCloseWindow();
    bool WindowIsOpen();
    bool WindowHasFocus();

    int GetCurrentWindowWidth();
    int GetCurrentWindowHeight();
    int GetWindowedWidth();
    int GetWindowedHeight();
    int GetFullScreenWidth();
    int GetFullScreenHeight();
    float GetCurrentAspectRatio();

}