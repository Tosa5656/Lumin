#include "Renderer/Renderer.h"

Camera camera;

glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 MVP = glm::mat4(1.0f);

void UpdateMVP()
{
    static float orbitAngle = 0.0f;
    orbitAngle += 0.01f; // скорость вращения
    float radius = 3.0f;
    float camX = sin(orbitAngle) * radius;
    float camZ = cos(orbitAngle) * radius;
    glm::vec3 cameraPos = glm::vec3(camX, 0.0f, camZ);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f); // центр куба
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    Model = glm::mat4(1.0f);
    View = glm::lookAt(cameraPos, target, up);
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
