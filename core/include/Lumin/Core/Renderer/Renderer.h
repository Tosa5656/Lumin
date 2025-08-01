/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Lumin/Core/Object/Object.h"
#include "Lumin/Core/Shaders/Shaders.h"
#include "Lumin/Core/Renderer/Camera.h"
#include "Lumin/Core/Renderer/Light.h"

namespace Lumin {
namespace Renderer {

using Lumin::Shaders::Shader;
using Lumin::Shaders::ShaderProgram;
using glm::mat4;

extern mat4 Projection;
extern mat4 View;
extern mat4 Model;
extern mat4 MVP;

extern RendererCamera camera;
extern Light light;

inline RendererCamera GetMainCamera() { return camera; }

void UpdateMVP();
ShaderProgram CreateShaderProgram(Shader vertexShader, Shader fragmentShader);
void UpdateBuffers(unsigned int VBO[2], unsigned int VAO, float* vertices, size_t vertexCount, float* colors, size_t colorCount);
void InitBuffers(unsigned int VBO[2], unsigned int* VAO);
void DrawObject(ShaderProgram shaderProgram, unsigned int VAO, int indexCount);
void DrawPoint(const glm::vec3& pos, const glm::vec3& color, ShaderProgram& shader);
void DrawLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color, ShaderProgram& shader);
void SetLightsUniforms(ShaderProgram& shader);

} // namespace Renderer
} // namespace Lumin