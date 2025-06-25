// Implementation of Renderer module for Lumin Engine

#include "Renderer/Renderer.h"
#include <string>

Camera camera;
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

ShaderProgram CreateShaderProgram(Shader vertexShader, Shader fragmentShader)
{
    ShaderProgram shaderProgram = ShaderProgram(vertexShader, fragmentShader);
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

void DrawObject(ShaderProgram shaderProgram, unsigned int VAO, int indexCount)
{
    UpdateMVP();
    glUseProgram(shaderProgram.getId());
    GLuint mvpLoc = glGetUniformLocation(shaderProgram.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &MVP[0][0]);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void DrawPoint(const glm::vec3& pos, const glm::vec3& color, ShaderProgram& shader) {
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

void DrawLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color, ShaderProgram& shader) {
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

void SetLightsUniforms(ShaderProgram& shader) {
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        std::string idx = std::to_string(i);
        GLint dirLoc = glGetUniformLocation(shader.getId(), ("lights[" + idx + "].direction").c_str());
        GLint colorLoc = glGetUniformLocation(shader.getId(), ("lights[" + idx + "].color").c_str());
        GLint intLoc = glGetUniformLocation(shader.getId(), ("lights[" + idx + "].intensity").c_str());
        GLint enLoc = glGetUniformLocation(shader.getId(), ("lights[" + idx + "].enabled").c_str());
        if (dirLoc == -1) printf("[SetLightsUniforms] dirLoc[%d] not found\n", i);
        if (colorLoc == -1) printf("[SetLightsUniforms] colorLoc[%d] not found\n", i);
        if (intLoc == -1) printf("[SetLightsUniforms] intLoc[%d] not found\n", i);
        if (enLoc == -1) printf("[SetLightsUniforms] enLoc[%d] not found\n", i);
        glUniform3fv(dirLoc, 1, &lights[i].direction[0]);
        glUniform3fv(colorLoc, 1, &lights[i].color[0]);
        glUniform1f(intLoc, lights[i].intensity);
        glUniform1i(enLoc, lights[i].enabled ? 1 : 0);
    }
}
