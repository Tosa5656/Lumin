#include "Renderer/Object.h"

Object::Object(const std::string& name, const float* vertices, size_t vertexCount, const float* colors, size_t colorCount, const unsigned int* indices, size_t indexCount, ObjectShaderProgram objectShaderProgram)
    : name(name), vertexCount(vertexCount), colorCount(colorCount), indexCount(indexCount), objectShaderProgram(objectShaderProgram)
{
    this->vertices = new float[vertexCount];
    std::memcpy(this->vertices, vertices, vertexCount * sizeof(float));
    this->colors = new float[colorCount];
    std::memcpy(this->colors, colors, colorCount * sizeof(float));
    this->indices = new unsigned int[indexCount];
    std::memcpy(this->indices, indices, indexCount * sizeof(unsigned int));
    Init();
}

Object::~Object()
{
    delete[] vertices;
    delete[] colors;
    delete[] indices;
}

GLuint Object::GetVAO()
{
    return VAO;
}

void Object::Init()
{
    shaderProgram = CreateShaderProgram(objectShaderProgram.vertexShader, objectShaderProgram.fragmentShader);
    InitBuffers(VBO, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorCount * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::Draw()
{
    UpdateBuffers(VBO, VAO, vertices, vertexCount, colors, colorCount);
    DrawObject(shaderProgram, VAO, indexCount);
}