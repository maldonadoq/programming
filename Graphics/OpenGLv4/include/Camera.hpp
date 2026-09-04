#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float speed;
    float rotationSpeed;

    void updateVectors();

public:
    Camera();

    glm::mat4 getViewMatrix() const;

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void moveUp(float deltaTime);
    void moveDown(float deltaTime);

    void turnLeft(float deltaTime);
    void turnRight(float deltaTime);

    void lookUp(float deltaTime);
    void lookDown(float deltaTime);

    void reset();

    glm::vec3 getPosition() const;
};

#endif // __CAMERA_HPP__