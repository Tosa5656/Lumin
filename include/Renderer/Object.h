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

class ObjectShaderProgram
{
public:
    ObjectShaderProgram() {};
    ObjectShaderProgram(Shader vertexShader, Shader fragmentShader)
    {
        this->vertexShader = vertexShader;
        this->fragmentShader = fragmentShader;
    }

    Shader vertexShader;
    Shader fragmentShader;
};

class Object
{
public:
    Object(const std::string& name, const float* vertices, size_t vertexCount, const float* colors, size_t colorCount, const unsigned int* indices, size_t indexCount, const float* uvs, size_t uvCount, const float* normals, size_t normalCount, ObjectShaderProgram objectShaderProgram);
    ~Object();

    GLuint GetVAO();

    void Init();
    void Draw();
    void SetTexture(Texture* texture);

private:
    std::string name;

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
    ShaderProgram shaderProgram;
    ObjectShaderProgram objectShaderProgram;
};