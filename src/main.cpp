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
GLFWwindow* g_window = nullptr;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f,
        0.5f, 0.33f, 0.27f
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

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Update()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    ProcessInput(g_window);
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
    g_window = window.GetGLFWwindow();
    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(g_window, mouse_callback);
    window.run(Update);
    if (object) delete object;
    return 0;
}