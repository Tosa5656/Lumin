#pragma once

#include <string>
#include <glad/glad.h>

#include "stb_image.h"

namespace Lumin {
namespace Renderer {

/**
 * @class Texture
 * @brief Класс для загрузки и управления текстурами в Lumin Engine.
 */
class Texture {
public:
    /**
     * @brief Загружает текстуру из файла.
     * @param path Путь к файлу текстуры
     */
    Texture(const std::string& path);
    /**
     * @brief Деструктор. Освобождает ресурсы OpenGL.
     */
    ~Texture();
    /**
     * @brief Привязывает текстуру к указанному слоту.
     * @param unit Слот текстуры (по умолчанию 0)
     */
    void Bind(unsigned int unit = 0) const;
    /**
     * @brief Получить OpenGL ID текстуры.
     * @return GLuint идентификатор
     */
    GLuint GetID() const { return m_ID; }
private:
    GLuint m_ID; ///< OpenGL ID текстуры
};

} // namespace Renderer
} // namespace Lumin 