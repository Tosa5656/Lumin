cmake_minimum_required(VERSION 3.10)
project(GLAD)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)