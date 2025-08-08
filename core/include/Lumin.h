/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Lumin/Core/Window/Window.h"
#include "Lumin/Core/Renderer/Renderer.h"
#include "Lumin/Core/Object/Object.h"
#include "Lumin/Core/Shaders/Shaders.h"
#include <glm/glm.hpp>
#include "Lumin/Core/Renderer/Camera.h"
#include "Lumin/Core/Renderer/Texture.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"