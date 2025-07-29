/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#include "Lumin/ScriptAPI/Utils/Input.h"

GLFWwindow* Input::window = nullptr;
std::unordered_map<int, bool> Input::keyLast;
std::unordered_map<int, bool> Input::mouseLast;
double Input::lastX = 0, Input::lastY = 0;
bool Input::firstMouse = true;
glm::vec2 Input::mouseDelta(0, 0);

void Input::SetWindow(GLFWwindow* glwindow)
{
    window = glwindow;
}

bool Input::GetKey(int key) {
    if (!window) return false;
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::GetKeyDown(int key) {
    if (!window) return false;
    int state = glfwGetKey(window, key);
    bool last = keyLast[key];
    keyLast[key] = (state == GLFW_PRESS);
    return (state == GLFW_PRESS && !last);
}

bool Input::GetKeyUp(int key) {
    if (!window) return false;
    int state = glfwGetKey(window, key);
    bool last = keyLast[key];
    keyLast[key] = (state == GLFW_PRESS);
    return (state == GLFW_RELEASE && last);
}

bool Input::GetMouseButton(int button) {
    if (!window) return false;
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool Input::GetMouseButtonDown(int button) {
    if (!window) return false;
    int state = glfwGetMouseButton(window, button);
    bool last = mouseLast[button];
    mouseLast[button] = (state == GLFW_PRESS);
    return (state == GLFW_PRESS && !last);
}

bool Input::GetMouseButtonUp(int button) {
    if (!window) return false;
    int state = glfwGetMouseButton(window, button);
    bool last = mouseLast[button];
    mouseLast[button] = (state == GLFW_PRESS);
    return (state == GLFW_RELEASE && last);
}

glm::vec2 Input::GetMousePosition() {
    if (!window) return glm::vec2(0.0f);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return glm::vec2((float)xpos, (float)ypos);
}

glm::vec2 Input::GetMouseDelta() {
    if (!window) return glm::vec2(0.0f);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    mouseDelta = glm::vec2((float)(xpos - lastX), (float)(ypos - lastY));
    lastX = xpos;
    lastY = ypos;
    return mouseDelta;
}