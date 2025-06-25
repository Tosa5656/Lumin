#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Shaders/Shaders.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "stb_image.h"

// Window management for Lumin Engine
class Window
{
public:
    Window(int width, int height, const std::string& title, const std::function<void()>& onAwake, const std::function<void()>& onStart);
    ~Window();

    void run(const std::function<void()>& onFrame);
    GLFWwindow* GetGLFWwindow() const { return window; }

private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;
};