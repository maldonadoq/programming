#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    reset();
}

void Camera::reset()
{
    position = glm::vec3(
        0.0f,
        2.0f,
        10.0f
    );

    worldUp = glm::vec3(
        0.0f,
        1.0f,
        0.0f
    );

    yaw = -90.0f;
    pitch = 0.0f;

    speed = 5.0f;
    rotationSpeed = 60.0f;

    updateVectors();
}

void Camera::updateVectors()
{
    glm::vec3 direction;

    direction.x =
        cos(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    direction.y =
        sin(glm::radians(pitch));

    direction.z =
        sin(glm::radians(yaw)) *
        cos(glm::radians(pitch));

    front = glm::normalize(direction);

    right = glm::normalize(
        glm::cross(
            front,
            worldUp
        )
    );

    up = glm::normalize(
        glm::cross(
            right,
            front
        )
    );
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(
        position,
        position + front,
        up
    );
}

void Camera::moveForward(float deltaTime)
{
    position +=
        front *
        speed *
        deltaTime;
}

void Camera::moveBackward(float deltaTime)
{
    position -=
        front *
        speed *
        deltaTime;
}

void Camera::moveLeft(float deltaTime)
{
    position -=
        right *
        speed *
        deltaTime;
}

void Camera::moveRight(float deltaTime)
{
    position +=
        right *
        speed *
        deltaTime;
}

void Camera::moveUp(float deltaTime)
{
    position +=
        worldUp *
        speed *
        deltaTime;
}

void Camera::moveDown(float deltaTime)
{
    position -=
        worldUp *
        speed *
        deltaTime;
}

void Camera::turnLeft(float deltaTime)
{
    yaw -=
        rotationSpeed *
        deltaTime;

    updateVectors();
}

void Camera::turnRight(float deltaTime)
{
    yaw +=
        rotationSpeed *
        deltaTime;

    updateVectors();
}

void Camera::lookUp(float deltaTime)
{
    pitch +=
        rotationSpeed *
        deltaTime;

    if (pitch > 85.0f)
        pitch = 85.0f;

    updateVectors();
}

void Camera::lookDown(float deltaTime)
{
    pitch -=
        rotationSpeed *
        deltaTime;

    if (pitch < -85.0f)
        pitch = -85.0f;

    updateVectors();
}

glm::vec3 Camera::getPosition() const
{
    return position;
}