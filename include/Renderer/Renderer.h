#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer/Object.h"
#include "Shaders/Shaders.h"
#include "Renderer/Camera.h"

using namespace glm;

extern glm::mat4 Projection;
extern glm::mat4 View;
extern glm::mat4 Model;
extern glm::mat4 MVP;

extern Camera camera;

ShaderProgram CreateShaderProgram(Shader vertexShader, Shader fragmentShader);
void UpdateBuffers(unsigned int VBO[2], unsigned int VAO, float* vertices, size_t vertexCount, float* colors, size_t colorCount);
void InitBuffers(unsigned int VBO[2], unsigned int* VAO);
void DrawObject(ShaderProgram shaderProgram, unsigned int VAO, int vertexCount);