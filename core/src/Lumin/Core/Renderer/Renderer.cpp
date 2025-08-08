/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#include "Lumin/Core/Renderer/Renderer.h"
#include <string>

namespace Lumin {
namespace Renderer {
RendererCamera camera;
Light light;

glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 MVP = glm::mat4(1.0f);

void UpdateMVP()
{
    Model = glm::mat4(1.0f);
    View = camera.GetViewMatrix();
    MVP = Projection * View * Model;
}

Lumin::Shaders::ShaderProgram CreateShaderProgram(Lumin::Shaders::Shader vertexShader, Lumin::Shaders::Shader fragmentShader)
{
    Lumin::Shaders::ShaderProgram shaderProgram = Lumin::Shaders::ShaderProgram(vertexShader, fragmentShader);
    shaderProgram.LinkShaders();
    return shaderProgram;
}

void UpdateBuffers(unsigned int VBO[2], unsigned int VAO, float* vertices, size_t vertexCount, float* colors, size_t colorCount)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorCount * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void InitBuffers(unsigned int VBO[2], unsigned int* VAO)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(2, VBO);
}

void DrawObject(Lumin::Shaders::ShaderProgram shaderProgram, unsigned int VAO, int indexCount)
{
    UpdateMVP();
    glUseProgram(shaderProgram.getId());
    GLuint mvpLoc = glGetUniformLocation(shaderProgram.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DrawPoint(const glm::vec3& pos, const glm::vec3& color, Lumin::Shaders::ShaderProgram& shader) {
    UpdateMVP();
    float vertices[] = { pos.x, pos.y, pos.z };
    float colors[] = { color.r, color.g, color.b };
    unsigned int VAO, VBO[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(shader.getId());
    GLuint mvpLoc = glGetUniformLocation(shader.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &MVP[0][0]);
    glPointSize(10.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}

void DrawLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color, Lumin::Shaders::ShaderProgram& shader) {
    UpdateMVP();
    float vertices[] = { from.x, from.y, from.z, to.x, to.y, to.z };
    float colors[] = { color.r, color.g, color.b, color.r, color.g, color.b };
    unsigned int VAO, VBO[2];
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(shader.getId());
    GLuint mvpLoc = glGetUniformLocation(shader.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}

void SetLightsUniforms(Lumin::Shaders::ShaderProgram& shader) {
    GLint dirLoc = glGetUniformLocation(shader.getId(), "sunLight.direction");
    GLint colorLoc = glGetUniformLocation(shader.getId(), "sunLight.color");
    GLint intLoc = glGetUniformLocation(shader.getId(), "sunLight.intensity");
    GLint enLoc = glGetUniformLocation(shader.getId(), "sunLight.enabled");
    if (dirLoc == -1) printf("[SetLightsUniforms] dirLoc not found\n");
    if (colorLoc == -1) printf("[SetLightsUniforms] colorLoc not found\n");
    if (intLoc == -1) printf("[SetLightsUniforms] intLoc not found\n");
    if (enLoc == -1) printf("[SetLightsUniforms] enLoc not found\n");
    glUniform3fv(dirLoc, 1, &sunLight.direction[0]);
    glUniform3fv(colorLoc, 1, &sunLight.color[0]);
    glUniform1f(intLoc, sunLight.intensity);
    glUniform1i(enLoc, sunLight.enabled ? 1 : 0);
}

}
}
