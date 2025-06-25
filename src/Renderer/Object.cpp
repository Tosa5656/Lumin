#include "Renderer/Object.h"
#include "Renderer/Renderer.h"

// Implementation of 3D Object for Lumin Engine
Object::Object(const std::string& name, const float* vertices, size_t vertexCount, const float* colors, size_t colorCount, const unsigned int* indices, size_t indexCount, const float* uvs, size_t uvCount, const float* normals, size_t normalCount, ObjectShaderProgram objectShaderProgram)
    : name(name), vertexCount(vertexCount), colorCount(colorCount), indexCount(indexCount), uvCount(uvCount), normalCount(normalCount), objectShaderProgram(objectShaderProgram), texture(nullptr)
{
    this->vertices = new float[vertexCount];
    std::memcpy(this->vertices, vertices, vertexCount * sizeof(float));
    this->colors = new float[colorCount];
    std::memcpy(this->colors, colors, colorCount * sizeof(float));
    this->indices = new unsigned int[indexCount];
    std::memcpy(this->indices, indices, indexCount * sizeof(unsigned int));
    this->uvs = new float[uvCount];
    std::memcpy(this->uvs, uvs, uvCount * sizeof(float));
    this->normals = new float[normalCount];
    std::memcpy(this->normals, normals, normalCount * sizeof(float));
    Init();
}

Object::~Object()
{
    delete[] vertices;
    delete[] colors;
    delete[] indices;
    delete[] uvs;
    delete[] normals;
}

GLuint Object::GetVAO()
{
    return VAO;
}

void Object::Init()
{
    shaderProgram = CreateShaderProgram(objectShaderProgram.vertexShader, objectShaderProgram.fragmentShader);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(4, VBO); // 0: vertices, 1: colors, 2: uvs, 3: normals
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // VBO 0: vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // VBO 1: colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorCount * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    // VBO 2: uvs
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, uvCount * sizeof(float), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    // VBO 3: normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, normalCount * sizeof(float), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Draw()
{
    UpdateMVP();
    glUseProgram(shaderProgram.getId());
    SetLightsUniforms(shaderProgram);
    GLuint mvpLoc = glGetUniformLocation(shaderProgram.getId(), "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &MVP[0][0]);
    GLuint useTextureLoc = glGetUniformLocation(shaderProgram.getId(), "useTexture");
    glUniform1i(useTextureLoc, texture ? 1 : 0);
    if (texture) {
        texture->Bind(0);
        glUniform1i(glGetUniformLocation(shaderProgram.getId(), "texture1"), 0);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Object::SetTexture(Texture* texture) {
    this->texture = texture;
}