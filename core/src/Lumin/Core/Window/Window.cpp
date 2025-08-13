/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#include "Lumin/Core/Window/Window.h"
#include <GLFW/glfw3.h>
#include <assert.h>


namespace Lumin {
namespace Windowing {

Window::Window(int width, int height, const std::string& title, const std::function<void()> onAwake, const std::function<void()> onStart, std::function<bool()> onFrame)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->onFrame = onFrame;

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    int iconWidth, iconHeight, iconChannels;
    unsigned char* iconPixels = stbi_load("resources/icon.png", &iconWidth, &iconHeight, &iconChannels, 4);
    if (iconPixels) {
        GLFWimage images[1];
        images[0].width = iconWidth;
        images[0].height = iconHeight;
        images[0].pixels = iconPixels;
        glfwSetWindowIcon(window, 1, images);
        stbi_image_free(iconPixels);
    }

    onAwake();

    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
        return;
    }
    glEnable(GL_DEPTH_TEST);
    onStart();
}

void Window::update()
{
    if (onFrame)
    {
        if(onFrame() == true)
            glfwDestroyWindow(window);
    }
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::SetWindowSize(glm::vec2 size)
{
    this->width = size.x;
    this->height = size.y;
    glfwSetWindowSize(window, size.x, size.y);
}

void Window::SetWindowTitle(std::string title)
{
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
}

glm::vec2 Window::GetWindowSize()
{
    return glm::vec2(width, height);
}

std::string Window::GetWindowTitle()
{
    return title;
}

bool Window::IsClosed()
{
    return glfwWindowShouldClose(window);
}

Window::~Window()
{
    assert(window);
    glfwDestroyWindow(window);
    glfwTerminate();
}
}
}