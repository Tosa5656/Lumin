#include <iostream>
#include <Lumin.h>
#include <Lumin/ScriptAPI/ScriptAPI.h>

using namespace Lumin::Renderer;
using namespace Lumin::Shaders;
using namespace Lumin::Windowing;

float lastX = 400, lastY = 300;
bool firstMouse = true;
GLFWwindow* g_window = nullptr;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Lumin::Renderer::Texture* texture = nullptr;
bool uiMode = true; // true — UI (мышь видима), false — игра (мышь скрыта)
Lumin::Object::ObjectShaderProgram objectSP;
Lumin::Shaders::ShaderProgram debugShaderProgram;
Lumin::Shaders::ShaderProgram debugColorShaderProgram;

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
    objectSP = Lumin::Object::ObjectShaderProgram(vertexShader, fragmentShader);
    debugShaderProgram = Lumin::Shaders::ShaderProgram(vertexShader, fragmentShader);
    debugShaderProgram.LinkShaders();

    texture = new Lumin::Renderer::Texture("resources/textures/texture.png");
    GameObject object = GameObject("Object", "resources/model.obj", &objectSP);
    //object = Lumin::Renderer::Object::FromOBJ("resources/model.obj", objectSP);
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

    ObjectsManager::DrawObjects();


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
    return 0;
}