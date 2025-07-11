#pragma once

#include <string>
#include <glad/glad.h>

#include "stb_image.h"

// Texture loader/manager for Lumin Engine
class Texture {
public:
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int unit = 0) const;
    GLuint GetID() const { return m_ID; }
private:
    GLuint m_ID;
}; 