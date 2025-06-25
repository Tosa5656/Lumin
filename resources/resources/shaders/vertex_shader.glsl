// Vertex shader for Lumin Engine. Passes position, color, UV, and normal to fragment shader.
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
    Normal = aNormal;
}