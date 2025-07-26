#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lumin {
namespace Renderer {

/**
 * @enum Camera_Movement
 * @brief Перечисление направлений движения камеры.
 */
enum Camera_Movement {
    FORWARD,   ///< Вперёд
    BACKWARD,  ///< Назад
    LEFT,      ///< Влево
    RIGHT      ///< Вправо
};

/**
 * @class Camera
 * @brief Класс камеры для управления положением и направлением обзора в 3D пространстве.
 *
 * Позволяет перемещать камеру, обрабатывать ввод с мыши и клавиатуры, получать view-матрицу.
 */
class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    void SetPosition(const glm::vec3& position);
    void SetLookAt(const glm::vec3& target);
    glm::mat4 GetViewMatrix() const;
    glm::vec3 GetPosition() const { return Position; }
    glm::vec3 GetLookAtTarget() const { return LookAtTarget; }
    glm::vec3 GetUp() const { return Up; }

private:
    glm::vec3 Position;
    glm::vec3 LookAtTarget;
    glm::vec3 Up;
};

} // namespace Renderer
} // namespace Lumin
