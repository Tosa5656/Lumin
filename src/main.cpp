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

using namespace glm;

Object* object = nullptr;
float lastX = 400, lastY = 300;
bool firstMouse = true;
GLFWwindow* g_window = nullptr;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Texture* texture = nullptr;
bool uiMode = true; // true — UI (мышь видима), false — игра (мышь скрыта)
ObjectShaderProgram objectSP;
ShaderProgram debugShaderProgram;
ShaderProgram debugColorShaderProgram;

void Awake()
{

}

void Start()
{
    InitDefaultLights();
    // Инициализация всех lights для релиза и debug
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        lights[i].enabled = true;
        float angle = glm::radians(360.0f * i / MAX_LIGHTS);
        lights[i].direction = glm::normalize(glm::vec3(cos(angle), -1.0f, sin(angle)));
        switch (i) {
            case 0: lights[i].color = glm::vec3(1,0,0); break;
            case 1: lights[i].color = glm::vec3(0,1,0); break;
            case 2: lights[i].color = glm::vec3(0,0,1); break;
            case 3: lights[i].color = glm::vec3(1,1,0); break;
        }
        lights[i].intensity = 1.0f;
    }
    Shader dbgVert("resources/shaders/debug_color_vertex.glsl", GL_VERTEX_SHADER);
    Shader dbgFrag("resources/shaders/debug_color_fragment.glsl", GL_FRAGMENT_SHADER);
    debugColorShaderProgram = ShaderProgram(dbgVert, dbgFrag);
    debugColorShaderProgram.LinkShaders();
    Shader vertexShader("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    objectSP = ObjectShaderProgram(vertexShader, fragmentShader);
    debugShaderProgram = ShaderProgram(vertexShader, fragmentShader);
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
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,
        0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f,  0.5f, 0.32f, 0.55f
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
    texture = new Texture("resources/textures/texture.png");
    object = new Object("Cube", vertices, 72, colors, 72, indices, 36, uvs, 48, normals, 72, objectSP);
    //object->SetTexture(texture);
}

void ShowLightSettingsImGui(Light* lights, int count) {
    ImGui::SetWindowSize("Lights Settings", ImVec2(400, 0), ImGuiCond_Once);
    ImGui::Begin("Lights Settings");
    for (int i = 0; i < count; ++i) {
        ImGui::PushID(i);
        if (ImGui::CollapsingHeader((std::string("Light ") + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Checkbox("Enabled", &lights[i].enabled);
            ImGui::SliderFloat3("Direction", &lights[i].direction[0], -1.0f, 1.0f);
            ImGui::ColorEdit3("Color", &lights[i].color[0]);
            ImGui::SliderFloat("Intensity", &lights[i].intensity, 0.0f, 5.0f);
        }
        ImGui::PopID();
    }
    ImGui::End();
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
    #ifdef RELEASE_BUILD
    #else
        ShowLightSettingsImGui(lights, MAX_LIGHTS);
    #endif

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

    if (object) object->Draw();

    #ifndef RELEASE_BUILD
        for (int i = 0; i < MAX_LIGHTS; ++i) {
            if (lights[i].enabled)
                lights[i].DrawDebug(debugColorShaderProgram);
        }
    #endif

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
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

    Window window(800, 600, "Lumin", Awake, Start);
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