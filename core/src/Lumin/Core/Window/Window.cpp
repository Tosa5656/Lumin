#include "Lumin/Core/Window/Window.h"

namespace Lumin {
namespace Windowing {

Window::Window(int width, int height, const std::string& title, const std::function<void()>& onAwake, const std::function<void()>& onStart)
{
    this->width = width;
    this->height = height;
    this->title = title;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        window = nullptr;
        return;
    }

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

void Window::run(const std::function<void()>& onFrame)
{
    if (!window) return;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (onFrame) onFrame();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

Window::~Window()
{
    if (window)
        glfwDestroyWindow(window);
}

} // namespace Windowing
} // namespace Lumin