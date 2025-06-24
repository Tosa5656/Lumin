#include "Shaders/Shaders.h"

Shader::Shader(const std::string& filePath, int type)
{
    m_Source = m_ReadShaderSource(filePath);
    m_Type = type;

    const GLchar* m_SourceCstr = m_Source.c_str();
    m_Shader = m_CreateShader(m_Type, m_SourceCstr);
}

std::string Shader::m_ReadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::m_CreateShader(int type, const GLchar* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader)
{
    m_ShaderProgram = glCreateProgram();
    m_VertexShader = vertexShader;
    m_FragmentShader = fragmentShader;
}

void ShaderProgram::LinkShaders()
{
    glAttachShader(m_ShaderProgram, m_VertexShader.getId());
    glAttachShader(m_ShaderProgram, m_FragmentShader.getId());
    glLinkProgram(m_ShaderProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}