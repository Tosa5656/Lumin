cmake_minimum_required(VERSION 3.27)

# Используем имя цели из родительского проекта, если оно определено
if(DEFINED LUMIN_CORE_TARGET)
    set(PROJECT_NAME ${LUMIN_CORE_TARGET})
else()
    set(PROJECT_NAME LuminCore)
endif()

project(${PROJECT_NAME})

set(CXX_STANDARD 18)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES
    src/Lumin/Core/Renderer/Camera.cpp
    src/Lumin/Core/Renderer/Light.cpp
    src/Lumin/Core/Object/Object.cpp
    src/Lumin/Core/Object/ObjectsManager.cpp
    src/Lumin/Core/Renderer/Renderer.cpp
    src/Lumin/Core/Renderer/Texture.cpp
    src/Lumin/Core/Shaders/Shaders.cpp
    src/Lumin/Core/Window/Window.cpp
    src/Lumin/Core/stb_image_impl.cpp
)

# Сначала создаём библиотеку
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Затем устанавливаем include директории
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(dependencies/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(dependencies/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

set(IMGUI_SRC
    dependencies/imgui/imgui.cpp
    dependencies/imgui/imgui_demo.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_tables.cpp
    dependencies/imgui/imgui_widgets.cpp
    dependencies/imgui/backends/imgui_impl_glfw.cpp
    dependencies/imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SRC})

# Используем относительные пути для ImGui
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/backends>
)