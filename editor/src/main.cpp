#include <iostream>
#include <Lumin.h>
#include "Lumin/ScriptAPI/ScriptAPI.h"

using namespace Lumin::Object;
using namespace Lumin::Shaders;
using namespace Lumin::Windowing;
using namespace Lumin::Renderer;

Camera mainCamera = Camera();
GLFWwindow* g_window = nullptr;
Lumin::Renderer::Texture* texture = nullptr;
Lumin::Object::ObjectShaderProgram objectSP;
Lumin::Shaders::ShaderProgram debugShaderProgram;
Lumin::Shaders::ShaderProgram debugColorShaderProgram;

// --- FPS Camera globals ---
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;
float cameraDistance = 1.0f; // расстояние до look-at
float lastX = 400, lastY = 300;
bool firstMouse = true;

void Awake() {}

void UpdateCameraLookAtFromAngles() {
    glm::vec3 pos = glm::vec3(mainCamera.transform.GetPosition().x, mainCamera.transform.GetPosition().y, mainCamera.transform.GetPosition().z);
    float yawRad = glm::radians(cameraYaw);
    float pitchRad = glm::radians(cameraPitch);
    glm::vec3 front;
    front.x = cos(pitchRad) * cos(yawRad);
    front.y = sin(pitchRad);
    front.z = cos(pitchRad) * sin(yawRad);
    mainCamera.transform.SetLookAt(Vector3(pos.x + glm::normalize(front).x * cameraDistance, pos.y + glm::normalize(front).y * cameraDistance, pos.z + glm::normalize(front).z * cameraDistance));
}

void Start()
{
    sunLight.enabled = true;
    sunLight.direction = glm::normalize(glm::vec3(0.5f, -1.0f, 0.5f));
    sunLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
    sunLight.intensity = 2.0f;
    sunLight.type = Lumin::Renderer::LightType::Directional;
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
    GameObject object = GameObject("test", "resources/model.obj", &objectSP);
    //object->SetTexture(texture);


    // FPS camera init
    glm::vec3 pos = glm::vec3(0.0f, 2.0f, 5.0f);
    glm::vec3 look = glm::vec3(0.0f, 0.0f, 0.0f);
    mainCamera.transform.SetPosition(Vector3(pos.x, pos.y, pos.z));
    mainCamera.transform.SetLookAt(Vector3(look.x, look.y, look.z));
    glm::vec3 front = glm::normalize(look - pos);
    cameraYaw = glm::degrees(atan2(front.z, front.x));
    cameraPitch = glm::degrees(asin(front.y));
    cameraDistance = glm::length(look - pos);
}

void Update()
{
    // --- FPS Camera movement ---
    float moveSpeed = 0.1f;
    float lightSpeed = 1.0f; // скорость вращения света
    glm::vec3 pos = glm::vec3(mainCamera.transform.GetPosition().x, mainCamera.transform.GetPosition().y, mainCamera.transform.GetPosition().z);
    glm::vec3 look = glm::vec3(mainCamera.transform.GetLookAt().x, mainCamera.transform.GetLookAt().y, mainCamera.transform.GetLookAt().z);
    glm::vec3 front = glm::normalize(look - pos);
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(mainCamera.transform.GetUp().x, mainCamera.transform.GetUp().y, mainCamera.transform.GetUp().z)));
    glm::vec3 up = glm::vec3(mainCamera.transform.GetUp().x, mainCamera.transform.GetUp().y, mainCamera.transform.GetUp().z);
    // Движение позиции камеры (WASD/QE)
    if (glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS)
        pos += front * moveSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_S) == GLFW_PRESS)
        pos -= front * moveSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_A) == GLFW_PRESS)
        pos -= right * moveSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_D) == GLFW_PRESS)
        pos += right * moveSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_Q) == GLFW_PRESS)
        pos += up * moveSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_E) == GLFW_PRESS)
        pos -= up * moveSpeed;
    mainCamera.transform.SetPosition(Vector3(pos.x, pos.y, pos.z));
    // --- Управление направлением солнца (стрелки) ---
    glm::vec3 rot = sunLight.GetRotation();
    if (glfwGetKey(g_window, GLFW_KEY_UP) == GLFW_PRESS)
        rot.x -= lightSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rot.x += lightSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot.y += lightSpeed;
    if (glfwGetKey(g_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot.y -= lightSpeed;
    sunLight.SetRotation(rot);
    // --- Mouse look ---
    double xpos, ypos;
    glfwGetCursorPos(g_window, &xpos, &ypos);
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }
    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // y inverted
    lastX = (float)xpos;
    lastY = (float)ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    cameraYaw += xoffset;
    cameraPitch += yoffset;
    if (cameraPitch > 89.0f) cameraPitch = 89.0f;
    if (cameraPitch < -89.0f) cameraPitch = -89.0f;
    UpdateCameraLookAtFromAngles();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Camera & Light Info");
    ImGui::Text("Camera position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Camera yaw: %.2f, pitch: %.2f", cameraYaw, cameraPitch);
    glm::vec3 lookat = glm::vec3(mainCamera.transform.GetLookAt().x, mainCamera.transform.GetLookAt().y, mainCamera.transform.GetLookAt().z);
    ImGui::Text("Camera look at: (%.2f, %.2f, %.2f)", lookat.x, lookat.y, lookat.z);
    glm::vec3 lightDir = sunLight.direction;
    ImGui::Text("Sun direction: (%.2f, %.2f, %.2f)", lightDir.x, lightDir.y, lightDir.z);
    ImGui::End();

    ObjectsManager::DrawObjects();
#ifndef RELEASE_BUILD
    if (sunLight.enabled)
        sunLight.DrawDebug(debugColorShaderProgram);
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
    if (texture) delete texture;
    return 0;
}