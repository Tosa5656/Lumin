// 3D Object representation for Lumin Engine
#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Renderer.h"
#include "Shaders/Shaders.h"
#include "Renderer/Texture.h"
#include <map>

namespace Lumin {
namespace Shaders {
    class Shader;
    class ShaderProgram;
}
namespace Renderer {

/**
 * @class ObjectShaderProgram
 * @brief Структура для хранения вершинного и фрагментного шейдеров объекта.
 */
class ObjectShaderProgram
{
public:
    /**
     * @brief Конструктор с параметрами.
     * @param vertexShader Вершинный шейдер
     * @param fragmentShader Фрагментный шейдер
     */
    ObjectShaderProgram(Lumin::Shaders::Shader vertexShader, Lumin::Shaders::Shader fragmentShader)
        : vertexShader(vertexShader), fragmentShader(fragmentShader) {}
    ObjectShaderProgram() = default;

    Lumin::Shaders::Shader vertexShader;   ///< Вершинный шейдер
    Lumin::Shaders::Shader fragmentShader; ///< Фрагментный шейдер
};

struct OBJMaterial {
    std::string name;
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    std::string diffuseTexPath;
    Texture* texture = nullptr;
};

/**
 * @class Object
 * @brief Класс 3D-объекта для Lumin Engine.
 *
 * Содержит данные о геометрии, цвете, текстуре и методы для инициализации и отрисовки.
 */
class Object
{
public:
    Object(const std::string& name, const float* vertices, size_t vertexCount, const float* colors, size_t colorCount, const unsigned int* indices, size_t indexCount, const float* uvs, size_t uvCount, const float* normals, size_t normalCount, ObjectShaderProgram objectShaderProgram);
    ~Object();

    GLuint GetVAO();
    void Init();
    void Draw();
    void SetTexture(Texture* texture);

    /**
     * @brief Загружает 3D-модель из OBJ-файла и создаёт объект.
     * @param path Путь к OBJ-файлу
     * @param objectShaderProgram Шейдерная программа для объекта
     * @return Указатель на созданный Object (или nullptr при ошибке)
     */
    static Object* FromOBJ(const std::string& path, ObjectShaderProgram objectShaderProgram);

    // Transform
    void SetPosition(const glm::vec3& pos) { position = pos; }
    void SetRotation(const glm::vec3& rot) { rotation = rot; }
    void SetScale(const glm::vec3& scl) { scale = scl; }
    glm::vec3 GetPosition() const { return position; }
    glm::vec3 GetRotation() const { return rotation; }
    glm::vec3 GetScale() const { return scale; }
    glm::mat4 GetModelMatrix() const;

private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f); // в градусах
    glm::vec3 scale    = glm::vec3(1.0f);
    void SetMaterialUniforms(int materialIdx);
    std::vector<OBJMaterial> materials;
    std::vector<int> materialIndices; // per-face/triangle
    std::string name; ///< Имя объекта

    unsigned int VBO[4], VAO, EBO;
    float* vertices;
    size_t vertexCount;
    float* colors;
    size_t colorCount;
    float* uvs;
    size_t uvCount;
    float* normals;
    size_t normalCount;
    unsigned int* indices;
    size_t indexCount;
    Texture* texture;
    Lumin::Shaders::ShaderProgram shaderProgram;
    ObjectShaderProgram objectShaderProgram;
};

}
}