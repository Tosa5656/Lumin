#pragma once

#include <iostream>
#include <vector>
#include "Lumin/Core/Window/Window.h"

using namespace Lumin::Windowing;

class Engine
{
public:
    Engine() {};
    void AddWindow(Window* window);
    bool Update();
private:
    std::vector<Window*> _windows;
};