#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Colors/Colors.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Object.h"
#include "Shaders/Shaders.h"
#include <glm/glm.hpp>
#include "Renderer/Camera.h"

using namespace glm;

Object* object = nullptr;
float lastX = 400, lastY = 300;
bool firstMouse = true;

void Awake()
{

}

void Start()
{
    Shader vertexShader("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ObjectShaderProgram objectSP(vertexShader, fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    float colors[] = {
        0.5f, 0.33f, 0.27f, // 0
        0.5f, 0.33f, 0.27f, // 1
        0.5f, 0.33f, 0.27f, // 2
        0.5f, 0.33f, 0.27f, // 3
        0.5f, 0.33f, 0.27f, // 4
        0.5f, 0.33f, 0.27f, // 5
        0.5f, 0.33f, 0.27f, // 6
        0.5f, 0.33f, 0.27f  // 7
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        0, 3, 7, 7, 4, 0,
        1, 5, 6, 6, 2, 1,
        0, 1, 5, 5, 4, 0,
        3, 2, 6, 6, 7, 3
    };
    object = new Object("Cube", vertices, 24, colors, 24, indices, 36, objectSP);
}

void Update()
{
    if (object) object->Draw();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

#ifdef _WIN32
    #ifdef RELEASE_BUILD
        #include <Windows.h>
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
    #else
        int main()
    #endif
#else
    int main()
#endif
{
    #ifdef RELEASE_BUILD
    #else
        std::cout << "Lumin started in debug mode." << std::endl;
    #endif

    Window window(800, 600, "Lumin", Awake, Start);
    glfwSetInputMode(window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.GetGLFWwindow(), mouse_callback);
    window.run(Update);
    if (object) delete object;
    return 0;
}