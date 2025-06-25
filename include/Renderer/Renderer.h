#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer/Object.h"
#include "Shaders/Shaders.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"

using namespace glm;

extern glm::mat4 Projection;
extern glm::mat4 View;
extern glm::mat4 Model;
extern glm::mat4 MVP;

extern Camera camera;
extern Light light;

// Renderer module for Lumin Engine
void UpdateMVP();
ShaderProgram CreateShaderProgram(Shader vertexShader, Shader fragmentShader);
void UpdateBuffers(unsigned int VBO[2], unsigned int VAO, float* vertices, size_t vertexCount, float* colors, size_t colorCount);
void InitBuffers(unsigned int VBO[2], unsigned int* VAO);
void DrawObject(ShaderProgram shaderProgram, unsigned int VAO, int vertexCount);
// Debug rendering
void DrawPoint(const glm::vec3& pos, const glm::vec3& color, ShaderProgram& shader);
void DrawLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color, ShaderProgram& shader);
void SetLightsUniforms(ShaderProgram& shader);