#include "Window.hpp"
#include "../Engine.hpp"

namespace Window {

    GLFWwindow* _window = NULL;
    WindowedMode _windowedMode = WindowedMode::WINDOWED;
    GLFWmonitor* _monitor;
    const GLFWvidmode* _mode;
    bool _forceCloseWindow = false;
    bool _windowHasFocus = true;
    int _windowedWidth = 0;
    int _windowedHeight = 0;
    int _fullscreenWidth = 0;
    int _fullscreenHeight = 0;
    int _currentWindowWidth = 0;
    int _currentWindowHeight = 0;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void window_focus_callback(GLFWwindow* window, int focused);

    void Init() {

        int width = 1280;
        int height = 720;

        // initialize GLFW and OpenGL context
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n"; });

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // resolution and window size
        _monitor = glfwGetPrimaryMonitor();
        _mode = glfwGetVideoMode(_monitor);
        glfwWindowHint(GLFW_RED_BITS, _mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, _mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, _mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, _mode->refreshRate);
        _fullscreenWidth = _mode->width;
        _fullscreenHeight = _mode->height;
        _windowedWidth = width;
        _windowedHeight = height;
        CreateGLFWWindow(WindowedMode::WINDOWED);
        if (_window == NULL) {
            std::cout << "Failed to create GLFW window\n";
            glfwTerminate();
            return;
        }
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
        glfwSetWindowFocusCallback(_window, window_focus_callback);

        glfwMakeContextCurrent(_window);
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD\n";
            glfwTerminate();
            return;
        }
    }

    GLFWwindow* GetWindowPointer() {
        return _window;
    }

    void SetWindowPointer(GLFWwindow* window) {
        _window = window;
    }

    void CreateGLFWWindow(const WindowedMode& windowedMode) {
        if (windowedMode == WindowedMode::WINDOWED) {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight;
            _window = glfwCreateWindow(_windowedWidth, _windowedHeight, "OpenGL Engine", NULL, NULL);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            _window = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, "OpenGL Engine", _monitor, NULL);
        }
        _windowedMode = windowedMode;
    }

    void SetWindowMode(const WindowedMode& windowedMode) {
        if (windowedMode == WindowedMode::WINDOWED) {
            _currentWindowWidth = _windowedWidth;
            _currentWindowHeight = _windowedHeight;
            glfwSetWindowMonitor(_window, nullptr, 100, 100, _windowedWidth, _windowedHeight, _mode->refreshRate);
        }
        else if (windowedMode == WindowedMode::FULLSCREEN) {
            _currentWindowWidth = _fullscreenWidth;
            _currentWindowHeight = _fullscreenHeight;
            glfwSetWindowMonitor(_window, _monitor, 0, 0, _fullscreenWidth, _fullscreenHeight, _mode->refreshRate);
        }
        _windowedMode = windowedMode;
    }

    void ToggleFullscreen() {
        if (_windowedMode == WindowedMode::WINDOWED) {
            SetWindowMode(WindowedMode::FULLSCREEN);
        }
        else {
            SetWindowMode(WindowedMode::WINDOWED);
        }
    }

    void ToggleCursor() {
        if (glfwGetInputMode(_window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            // set player control true
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else {
            // set player control false
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    void ForceCloseWindow() {
        _forceCloseWindow = true;
    }

    bool WindowHasFocus() {
        return _windowHasFocus;
    }

    bool WindowIsOpen() {
        return !(glfwWindowShouldClose(_window) || _forceCloseWindow);
    }

    const WindowedMode& GetWindowMode() {
        return _windowedMode;
    }

    // window size queries
    int GetCurrentWindowWidth() {
        return _currentWindowWidth;
    }

    int GetCurrentWindowHeight() {
        return _currentWindowHeight;
    }

    int GetWindowedWidth() {
        return _windowedWidth;
    }

    int GetWindowedHeight() {
        return _windowedHeight;
    }

    int GetFullScreenWidth() {
        return _fullscreenWidth;
    }

    int GetFullScreenHeight() {
        return _fullscreenHeight;
    }

    float GetCurrentAspectRatio() {
        return ((float)_currentWindowWidth / (float)_currentWindowHeight);
    }

    // callbacks
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void window_focus_callback(GLFWwindow* window, int focused) {
        if (focused) {
            _windowHasFocus = true;
        }
        else {
            _windowHasFocus = false;
        }
    }

}