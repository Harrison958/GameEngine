#pragma once
#include "../Common.hpp"

#include <map>
#include <queue>

class Input {
public:

    static void Init(GLFWwindow* window);
    static void Update();

    static bool KeyPressed(unsigned int key);
    static bool KeyDown(unsigned int key);

    static bool MouseButtonPressed(unsigned int button);
    static bool MouseButtonDown(unsigned int button);

    static double GetMouseX();
    static double GetMouseY();
    static double GetMouseOffsetX();
    static double GetMouseOffsetY();
    static bool HasMouseMoved();

    static float GetScrollWheelOffset();
    static bool IsScrollWheelUp();
    static bool IsScrollWheelDown();

private:

    struct KeyPress {
        bool current, previous;
    };

    struct Event {
        enum Type { Key, MouseButton, ScrollWheel, MousePos } type;
        int key;
        int action;
        double xoffset;
        double yoffset;
        double xpos;
        double ypos;
    };

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    static GLFWwindow* _window;
    static std::map<int, KeyPress> KeyPresses;
    static std::map<int, KeyPress> MouseButtons;
    static std::queue<Event> EventQueue;

    static double _currentMouseX;
    static double _currentMouseY;
    static double _lastMouseX;
    static double _lastMouseY;
    static double _mouseOffsetX;
    static double _mouseOffsetY;
    static bool _mouseMoved;

    static float _scrollWheelOffset;
    static bool _scrollWheelUp;
    static bool _scrollWheelDown;
};