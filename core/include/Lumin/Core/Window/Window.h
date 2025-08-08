/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Lumin/Core/Shaders/Shaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lumin/Core/stb_image.h"

namespace Lumin {
namespace Windowing {
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

}
}