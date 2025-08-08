cmake_minimum_required(VERSION 3.27)

# Use the project name from the variable if it is defined, otherwise use a default name
if(DEFINED LUMIN_EDITOR_TARGET)
    set(PROJECT_NAME ${LUMIN_EDITOR_TARGET})
else()
    set(PROJECT_NAME LuminEditor)
endif()

set(EDITOR_VERSION 0.4)

project(${PROJECT_NAME} VERSION ${EDITOR_VERSION} LANGUAGES CXX)

# C++ standard settings
set(CXX_STANDARD 18)

# Set base paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Find all source files and add executable for target
file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp)
file(GLOB_RECURSE EDITOR_HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# Add dependencies
if(DEFINED LUMIN_CORE_TARGET)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LUMIN_CORE_TARGET})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE LuminCore)
endif()

if(DEFINED LUMIN_SCRIPT_API_TARGET)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LUMIN_SCRIPT_API_TARGET})
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ScriptAPI)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../script_api/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui/backends>
)