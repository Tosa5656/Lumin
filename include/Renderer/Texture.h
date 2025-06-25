#pragma once
#include <string>
#include <glad/glad.h>

class Texture {
public:
    Texture(const std::string& path);
    ~Texture();
    void Bind(unsigned int unit = 0) const;
    GLuint GetID() const { return m_ID; }
private:
    GLuint m_ID;
}; 