#include "Input.hpp"
#include "Window.hpp"

// static member initialization
GLFWwindow* Input::_window = nullptr;
std::map<int, Input::KeyPress> Input::KeyPresses;
std::map<int, Input::KeyPress> Input::MouseButtons;
std::queue<Input::Event> Input::EventQueue;

double Input::_currentMouseX = 0;
double Input::_currentMouseY = 0;
double Input::_lastMouseX = 0;
double Input::_lastMouseY = 0;
double Input::_mouseOffsetX = 0;
double Input::_mouseOffsetY = 0;
bool Input::_mouseMoved = false;
float Input::_scrollWheelOffset = 0;
bool Input::_scrollWheelUp = false;
bool Input::_scrollWheelDown = false;

void Input::Init(GLFWwindow* window) {
    _window = window;
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
}

void Input::Update() {

    _scrollWheelOffset = 0;
    _scrollWheelUp = false;
    _scrollWheelDown = false;
    _mouseMoved = false;

    while (!EventQueue.empty()) {
        Event event = EventQueue.front();
        EventQueue.pop();

        switch (event.type) {
        case Event::Key:
            KeyPresses[event.key].previous = KeyPresses[event.key].current;
            KeyPresses[event.key].current = (event.action == GLFW_PRESS || event.action == GLFW_REPEAT);
            if (event.key == GLFW_KEY_ESCAPE && event.action == GLFW_PRESS) {
                Window::ForceCloseWindow();
            }
            if (event.key == GLFW_KEY_F11 && event.action == GLFW_PRESS) {
                Window::ToggleFullscreen();
            }
            if (event.key == GLFW_KEY_TAB && event.action == GLFW_PRESS) {
                Window::ToggleCursor();
            }
            break;
        case Event::MouseButton:
            MouseButtons[event.key].previous = MouseButtons[event.key].current;
            MouseButtons[event.key].current = (event.action == GLFW_PRESS);
            break;
        case Event::ScrollWheel:
            _scrollWheelOffset = (float)event.yoffset;
            if (_scrollWheelOffset > 0) {
                _scrollWheelUp = true;
            }
            if (_scrollWheelOffset < 0) {
                _scrollWheelDown = true;
            }
            break;
        case Event::MousePos:
            _currentMouseX = event.xpos;
            _currentMouseY = event.ypos;
            _mouseOffsetX = _currentMouseX - _lastMouseX;
            _mouseOffsetY = _lastMouseY - _currentMouseY;
            _lastMouseX = _currentMouseX;
            _lastMouseY = _currentMouseY;
            _mouseMoved = true;
            break;
        }
    }
}

// check key states
bool Input::KeyPressed(unsigned int key) {
    return KeyPresses[key].current;
}

bool Input::KeyDown(unsigned int key) {
    return KeyPresses[key].current && !KeyPresses[key].previous;
}

bool Input::MouseButtonPressed(unsigned int button) {
    return MouseButtons[button].current;
}

bool Input::MouseButtonDown(unsigned int button) {
    return MouseButtons[button].current && !MouseButtons[button].previous;
}

double Input::GetMouseX() {
    return _currentMouseX;
}

double Input::GetMouseY() {
    return _currentMouseY;
}

double Input::GetMouseOffsetX() {
    return _mouseOffsetX;
}

double Input::GetMouseOffsetY() {
    return _mouseOffsetY;
}

bool Input::HasMouseMoved() {
    return _mouseMoved;
}

float Input::GetScrollWheelOffset() {
    return _scrollWheelOffset;
}

bool Input::IsScrollWheelUp() {
    return _scrollWheelUp;
}

bool Input::IsScrollWheelDown() {
    return _scrollWheelDown;
}

// Callbacks
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    EventQueue.push({ Event::Key, key, action, 0, 0, 0, 0 });
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    EventQueue.push({ Event::MouseButton, button, action, 0, 0, 0, 0 });
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    EventQueue.push({ Event::ScrollWheel, 0, 0, xoffset, yoffset, 0, 0 });
}

void Input::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    EventQueue.push({ Event::MousePos, 0, 0, 0, 0, xpos, ypos });
}