cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME ScriptAPI)
project(${PROJECT_NAME})

set(CXX_STANDARD 18)

file(GLOB_RECURSE SCRIPT_API_SOURCES src/*.cpp)
file(GLOB_RECURSE SCRIPT_API_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${SCRIPT_API_SOURCES} ${SCRIPT_API_HEADERS})

target_link_libraries(${PROJECT_NAME} PUBLIC LuminCore)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ../core/include
)