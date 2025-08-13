#include "Lumin/Core/Engine.h"

void Engine::AddWindow(Window* window)
{
    _windows.push_back(window);
}

bool Engine::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bool updateWindows = false;

    for(Window* &window : _windows)
    {
        if (!window->IsClosed())
        {
            window->update();
            window->SwapBuffers();
            updateWindows = true;
        }
    }
    glfwPollEvents();

    return updateWindows;
}