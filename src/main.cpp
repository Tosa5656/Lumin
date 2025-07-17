// Lumin Engine main application file
// Handles window creation, OpenGL context, main loop, and UI

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
#include "Renderer/Texture.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#ifndef RELEASE_BUILD
#include <glad/glad.h>
#endif

using namespace Lumin::Renderer;
using namespace Lumin::Shaders;
using namespace Lumin::Windowing;

Lumin::Renderer::Object* object = nullptr;
float lastX = 400, lastY = 300;
bool firstMouse = true;
GLFWwindow* g_window = nullptr;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Lumin::Renderer::Texture* texture = nullptr;
bool uiMode = true; // true — UI (мышь видима), false — игра (мышь скрыта)
Lumin::Renderer::ObjectShaderProgram objectSP;
Lumin::Shaders::ShaderProgram debugShaderProgram;
Lumin::Shaders::ShaderProgram debugColorShaderProgram;

int anim_time = 0;

void Awake() {}

void Start()
{
    // Яркое солнце: белый цвет, интенсивность 3.0, светит под углом сверху сбоку (визуально "дальше")
    sunLight.enabled = true;
    sunLight.direction = glm::normalize(glm::vec3(0.5f, -1.0f, 0.5f)); // под углом сверху сбоку
    sunLight.color = glm::vec3(1.0f, 1.0f, 1.0f); // белый свет
    sunLight.intensity = 2.0f;
    sunLight.type = LightType::Directional;

    Lumin::Shaders::Shader dbgVert("resources/shaders/debug_color_vertex.glsl", GL_VERTEX_SHADER);
    Lumin::Shaders::Shader dbgFrag("resources/shaders/debug_color_fragment.glsl", GL_FRAGMENT_SHADER);
    debugColorShaderProgram = Lumin::Shaders::ShaderProgram(dbgVert, dbgFrag);
    debugColorShaderProgram.LinkShaders();
    Lumin::Shaders::Shader vertexShader("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Lumin::Shaders::Shader fragmentShader("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    objectSP = Lumin::Renderer::ObjectShaderProgram(vertexShader, fragmentShader);
    debugShaderProgram = Lumin::Shaders::ShaderProgram(vertexShader, fragmentShader);
    debugShaderProgram.LinkShaders();

    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // Back face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        // Left face
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        // Right face
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        // Top face
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        // Bottom face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
    };
    float colors[] = {
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f
    };
    float uvs[] = {
        // Front
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        // Back
        1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
        // Left
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        // Right
        1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
        // Top
        0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 1.0f,
        // Bottom
        1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f
    };
    float normals[] = {
        // Front face
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        // Back face
        0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
        // Left face
        -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        // Right face
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        // Top face
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        // Bottom face
        0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,         // front
        4, 5, 6, 6, 7, 4,         // back
        8, 9,10,10,11, 8,         // left
       12,13,14,14,15,12,         // right
       16,17,18,18,19,16,         // top
       20,21,22,22,23,20          // bottom
    };
    texture = new Lumin::Renderer::Texture("resources/textures/texture.png");
    object = Lumin::Renderer::Object::FromOBJ("resources/model.obj", objectSP);
    //object->SetTexture(texture);
}

void ProcessInput(GLFWwindow* window)
{
    using namespace Lumin::Renderer;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        object->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));

    glm::vec3 rot = sunLight.GetRotation();
    float lightSpeed = 60.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot.y += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot.y -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rot.x -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rot.x += lightSpeed;

    sunLight.SetRotation(rot);
}

void Update()
{
    using namespace Lumin::Renderer;
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // --- Change mode by ESC ---
    static bool escPressed = false;
    if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !escPressed) {
        uiMode = !uiMode;
        escPressed = true;
    }
    if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
        escPressed = false;
    }

    // --- Camera move ---
    if (uiMode) {
        glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // ImGui frame start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Mode Info");
    ImGui::Text("Current mode: %s", uiMode ? "UI (ESC to switch)" : "Game (ESC to switch)");
    ImGui::End();

    if (!uiMode) {
        ProcessInput(g_window);
        double xpos, ypos;
        glfwGetCursorPos(g_window, &xpos, &ypos);
        static bool firstMouse = true;
        static double lastX = 0.0, lastY = 0.0;
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = static_cast<float>(xpos - lastX);
        float yoffset = static_cast<float>(lastY - ypos);
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouseMovement(xoffset, yoffset);
    } else {
        static bool firstMouse = true;
        firstMouse = true;
    }

    anim_time += 1;
    object->SetRotation(glm::vec3(anim_time, 0, 0));
    if (object) object->Draw();

#ifndef RELEASE_BUILD
    // Debug: рисуем только один источник света (солнце)
    if (sunLight.enabled)
        sunLight.DrawDebug(debugColorShaderProgram);
#endif

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    using namespace Lumin::Renderer;
    glViewport(0, 0, width, height);
    Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
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

    Lumin::Windowing::Window window(800, 600, "Lumin", Awake, Start);
    g_window = window.GetGLFWwindow();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(g_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(g_window, framebuffer_size_callback);
    window.run(Update);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (object) delete object;
    if (texture) delete texture;
    return 0;
}