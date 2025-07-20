#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Lumin/Core/Shaders/Shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lumin/Core/stb_image.h"

namespace Lumin {
namespace Windowing {

/**
 * @class Window
 * @brief Класс для управления окном и главным циклом приложения Lumin Engine.
 */
class Window
{
public:
    /**
     * @brief Конструктор окна.
     * @param width Ширина окна
     * @param height Высота окна
     * @param title Заголовок окна
     * @param onAwake Функция инициализации (Awake)
     * @param onStart Функция запуска (Start)
     */
    Window(int width, int height, const std::string& title, const std::function<void()>& onAwake, const std::function<void()>& onStart);
    /**
     * @brief Деструктор. Освобождает ресурсы окна.
     */
    ~Window();

    /**
     * @brief Запускает главный цикл приложения.
     * @param onFrame Функция, вызываемая каждый кадр
     */
    void run(const std::function<void()>& onFrame);
    /**
     * @brief Получить указатель на GLFWwindow.
     * @return GLFWwindow*
     */
    GLFWwindow* GetGLFWwindow() const { return window; }

private:
    GLFWwindow* window; ///< Указатель на GLFW окно
    int width;          ///< Ширина окна
    int height;         ///< Высота окна
    std::string title;  ///< Заголовок окна
};

} // namespace Windowing
} // namespace Lumin