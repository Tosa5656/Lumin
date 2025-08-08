cmake_minimum_required(VERSION 3.27)

# Use the project name from the variable if it is defined, otherwise use a default name
if(DEFINED LUMIN_SCRIPT_API_TARGET)
    set(PROJECT_NAME ${LUMIN_SCRIPT_API_TARGET})
else()
    set(PROJECT_NAME ScriptAPI)
endif()

set(SCRIPTAPI_VERSION 0.4)

project(${PROJECT_NAME} VERSION ${SCRIPTAPI_VERSION} LANGUAGES CXX)

# C++ standard settings
set(CXX_STANDARD 18)

# Find all source files and add executable for target
file(GLOB_RECURSE SCRIPT_API_SOURCES src/*.cpp)
file(GLOB_RECURSE SCRIPT_API_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${SCRIPT_API_SOURCES} ${SCRIPT_API_HEADERS})

# Add core dependency
if(DEFINED LUMIN_CORE_TARGET)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LUMIN_CORE_TARGET})
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC LuminCore)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui/backends>
)