#pragma once

#include <iostream>
#include <Lumin.h>

class ShadersManager
{
public:
    static inline Lumin::Object::ObjectShaderProgram BasicObjectSP;
    static inline Lumin::Shaders::ShaderProgram DebugShaderProgram;
    static inline Lumin::Shaders::ShaderProgram DebugColorShaderProgram;

    static void InitBasicShaderProgramms()
    {
        Lumin::Shaders::Shader dbgVert("resources/shaders/debug_color_vertex.glsl", GL_VERTEX_SHADER);
        Lumin::Shaders::Shader dbgFrag("resources/shaders/debug_color_fragment.glsl", GL_FRAGMENT_SHADER);
        DebugColorShaderProgram = Lumin::Shaders::ShaderProgram(dbgVert, dbgFrag);
        DebugColorShaderProgram.LinkShaders();
        Lumin::Shaders::Shader vertexShader("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
        Lumin::Shaders::Shader fragmentShader("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
        BasicObjectSP = Lumin::Object::ObjectShaderProgram(vertexShader, fragmentShader);
        DebugShaderProgram = Lumin::Shaders::ShaderProgram(vertexShader, fragmentShader);
        DebugShaderProgram.LinkShaders();
    }
};