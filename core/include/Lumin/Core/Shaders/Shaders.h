/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <glad/glad.h>

namespace Lumin {
namespace Shaders {

/**
 * @class Shader
 * @brief Класс-обёртка для загрузки и компиляции шейдеров OpenGL.
 */
class Shader
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    Shader() {};
    /**
     * @brief Загружает и компилирует шейдер из файла.
     * @param filePath Путь к файлу шейдера
     * @param type Тип шейдера (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER и т.д.)
     */
    Shader(const std::string& filePath, int type);
    /**
     * @brief Получить OpenGL ID шейдера.
     * @return GLuint идентификатор
     */
    GLuint getId() { return m_Shader; }
    /**
     * @brief Получить тип шейдера.
     * @return int тип
     */
    int getType() { return m_Type; }
private:
    std::string m_ReadShaderSource(const std::string& filePath);
    GLuint m_CreateShader(int type, const GLchar* source);
    GLuint m_Shader; ///< OpenGL ID шейдера
    int m_Type;      ///< Тип шейдера
    std::string m_Source; ///< Исходный код шейдера
};

/**
 * @class ShaderProgram
 * @brief Класс-обёртка для линковки и управления программой шейдеров OpenGL.
 */
class ShaderProgram
{
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    ShaderProgram() {};
    /**
     * @brief Создаёт программу из вершинного и фрагментного шейдеров.
     * @param vertexShader Вершинный шейдер
     * @param fragmentShader Фрагментный шейдер
     */
    ShaderProgram(Shader vertexShader, Shader fragmentShader);
    /**
     * @brief Линкует шейдеры в программу.
     */
    void LinkShaders();
    /**
     * @brief Получить OpenGL ID программы.
     * @return GLuint идентификатор
     */
    GLuint getId() { return m_ShaderProgram; }
private:
    GLuint m_ShaderProgram; ///< OpenGL ID программы
    Shader m_VertexShader; ///< Вершинный шейдер
    Shader m_FragmentShader; ///< Фрагментный шейдер
};

} // namespace Shaders
} // namespace Lumin