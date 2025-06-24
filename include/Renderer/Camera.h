#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), float yaw = -90.0f, float pitch = 0.0f);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    glm::mat4 GetViewMatrix() const;
    glm::vec3 GetPosition() const { return Position; }
    glm::vec3 GetFront() const { return Front; }
    float Yaw, Pitch;
private:
    void updateCameraVectors();
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
};
