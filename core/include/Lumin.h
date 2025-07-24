#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Lumin/Core/Colors/Colors.h"
#include "Lumin/Core/Window/Window.h"
#include "Lumin/Core/Renderer/Renderer.h"
#include "Lumin/Core/Object/Object.h"
#include "Lumin/Core/Object/ObjectsManager.h"
#include "Lumin/Core/Shaders/Shaders.h"
#include <glm/glm.hpp>
#include "Lumin/Core/Renderer/Camera.h"
#include "Lumin/Core/Renderer/Texture.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#ifndef RELEASE_BUILD
#include <glad/glad.h>
#endif