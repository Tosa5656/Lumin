cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME LuminCore)
project(${PROJECT_NAME})

set(CXX_STANDARD 18)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(include/)

set(SOURCES
    src/Lumin/Core/Renderer/Camera.cpp
    src/Lumin/Core/Renderer/Light.cpp
    src/Lumin/Core/Renderer/Object.cpp
    src/Lumin/Core/Renderer/Renderer.cpp
    src/Lumin/Core/Renderer/Texture.cpp
    src/Lumin/Core/Shaders/Shaders.cpp
    src/Lumin/Core/Window/Window.cpp
    src/Lumin/Core/stb_image_impl.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

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
target_include_directories(${PROJECT_NAME} PUBLIC dependencies/imgui dependencies/imgui/backends)