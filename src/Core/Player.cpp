#include "Player.hpp"
#include "Window.hpp"
#include "Input.hpp"

void Player::Update(float deltaTime) {

    if (!_ignoreControl && Window::WindowHasFocus()) {

        ProcessKeyboard(deltaTime);

        if (Input::HasMouseMoved()) {
            ProcessMouseMovement();
        }
    }
}

glm::mat4 Player::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Player::ProcessKeyboard(float deltaTime) {

    float velocity = MovementSpeed * deltaTime;
    if (Input::KeyPressed(Keybinds::WALK_FOWARD)) {
        Position += Front * velocity;
    }
    if (Input::KeyPressed(Keybinds::WALK_BACKWARD)) {
        Position -= Front * velocity;
    }
    if (Input::KeyPressed(Keybinds::WALK_LEFT)) {
        Position -= Right * velocity;
    }
    if (Input::KeyPressed(Keybinds::WALK_RIGHT)) {
        Position += Right * velocity;
    }
    if (Input::KeyPressed(Keybinds::FLY_UP)) {
        Position += Up * velocity;
    }
    if (Input::KeyPressed(Keybinds::FLY_DOWN)) {
        Position -= Up * velocity;
    }
}

void Player::ProcessMouseMovement() {

    float xoffset = (float)Input::GetMouseOffsetX() * MouseSensitivity;
    float yoffset = (float)Input::GetMouseOffsetY() * MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Player::updateCameraVectors() {

    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}