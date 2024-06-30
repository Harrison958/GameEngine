#pragma once
#include "../Common.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90;
const float PITCH = 0;
const float SPEED = 7.5;
const float SENSITIVITY = 0.05f;
const float FOV = 45;
const bool constrainPitch = true;

class Player {
public:

    struct Keybinds {
        static const unsigned int WALK_FOWARD = GLFW_KEY_W;
        static const unsigned int WALK_BACKWARD = GLFW_KEY_S;
        static const unsigned int WALK_LEFT = GLFW_KEY_A;
        static const unsigned int WALK_RIGHT = GLFW_KEY_D;
        static const unsigned int FLY_UP = GLFW_KEY_SPACE;
        static const unsigned int FLY_DOWN = GLFW_KEY_LEFT_CONTROL;
        static const unsigned int EXIT_APPLICATION = GLFW_KEY_ESCAPE;
        static const unsigned int TOGGLE_CURSOR = GLFW_KEY_TAB;
        static const unsigned int TOGGLE_FULLSCREEN = GLFW_KEY_F;
    };

    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = NRM_Y_UP, float yaw = YAW, float pitch = PITCH)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    bool _ignoreControl = false;
    float Yaw = YAW;
    float Pitch = PITCH;
    float MovementSpeed;
    float MouseSensitivity;

    void Update(float deltaTime);

    void ProcessKeyboard(float deltaTime);
    void ProcessMouseMovement();

    glm::mat4 GetViewMatrix();

private:

    void updateCameraVectors();

};