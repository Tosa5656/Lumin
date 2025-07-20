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
    /**
     * @brief Конструктор камеры.
     * @param position Начальная позиция камеры.
     * @param yaw Угол поворота по горизонтали.
     * @param pitch Угол поворота по вертикали.
     */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), float yaw = -90.0f, float pitch = 0.0f);

    /**
     * @brief Обработка движения мыши.
     * @param xoffset Смещение по X.
     * @param yoffset Смещение по Y.
     * @param constrainPitch Ограничивать ли pitch.
     */
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    /**
     * @brief Обработка нажатий клавиш.
     * @param direction Направление движения.
     * @param deltaTime Время между кадрами.
     */
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    /**
     * @brief Получить view-матрицу камеры.
     * @return View-матрица (glm::mat4).
     */
    glm::mat4 GetViewMatrix() const;

    /**
     * @brief Получить позицию камеры.
     * @return Позиция камеры (glm::vec3).
     */
    glm::vec3 GetPosition() const { return Position; }

    /**
     * @brief Получить направление взгляда камеры.
     * @return Вектор направления (glm::vec3).
     */
    glm::vec3 GetFront() const { return Front; }

    float Yaw;   ///< Угол по горизонтали
    float Pitch; ///< Угол по вертикали
    float MovementSpeed = 2.5f; ///< Скорость движения камеры

private:
    /**
     * @brief Пересчитывает векторы направления камеры на основе текущих углов.
     */
    void updateCameraVectors();
    glm::vec3 Position; ///< Позиция камеры
    glm::vec3 Front;    ///< Вектор направления
    glm::vec3 Up;       ///< Вектор "вверх"
    glm::vec3 Right;    ///< Вектор "вправо"
    glm::vec3 WorldUp;  ///< Мировой "вверх"
};

} // namespace Renderer
} // namespace Lumin
