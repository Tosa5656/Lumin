cmake_minimum_required(VERSION 3.27)

# Use the project name from the variable if it is defined, otherwise use a default name
if(DEFINED LUMIN_CORE_TARGET)
    set(PROJECT_NAME ${LUMIN_CORE_TARGET})
else()
    set(PROJECT_NAME LuminCore)
endif()

set(CORE_VERSION 0.4)

project(${PROJECT_NAME} VERSION ${CORE_VERSION} LANGUAGES CXX)

# C++ standard settings
set(CXX_STANDARD 18)

# Set base paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE CORE_SOURCES src/*.cpp)

# Create the project library
add_library(${PROJECT_NAME} STATIC ${CORE_SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Add dependencies
add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(dependencies/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(dependencies/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

add_subdirectory(dependencies/openal)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenAL)

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

target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/backends>
)