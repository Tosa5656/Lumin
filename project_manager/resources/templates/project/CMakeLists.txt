cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Project)
set(PROJECT_VERSION 0.0.1)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})

set(LUMIN_CORE_TARGET "LuminCore" CACHE STRING "Core library target name")
set(LUMIN_SCRIPT_API_TARGET "LuminScriptAPI" CACHE STRING "Script API target name")

# Проверяем, есть ли библиотеки в папке library
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/library/core/CMakeLists.txt")
    add_subdirectory(library/core)
    add_subdirectory(library/script_api)
else()
    message(FATAL_ERROR "Library files not found. Please copy core and script_api to library folder.")
endif()

# Подключаем библиотеки Lumin Engine
target_link_libraries(${PROJECT_NAME} 
    ${LUMIN_CORE_TARGET}
    ${LUMIN_SCRIPT_API_TARGET}
)

# Настройка include директорий
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/library/core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/library/script_api/include
    ${CMAKE_CURRENT_SOURCE_DIR}/library/core/dependencies/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/library/core/dependencies/imgui/backends
)

add_custom_target(CreateDirectories ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
    COMMENT "Creating output directories"
)
add_custom_target(CopyProject ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR}/bin/
    COMMENT "Copying project manager executable to bin directory"
)
add_dependencies(CopyProject CreateDirectories)

if(WIN32)
    set(WINDOWS_TARGET_PLATFORM "win64" CACHE STRING "Windows target platform (win32 or win64)")
    message(STATUS "Windows target platform: ${WINDOWS_TARGET_PLATFORM}")
    add_custom_target(CopyWindowsDependencies ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/library/dll/${WINDOWS_TARGET_PLATFORM} ${CMAKE_SOURCE_DIR}/bin/
        COMMENT "Copying Windows dependencies to project templates"
    )
    add_dependencies(CopyWindowsDependencies CreateDirectories)
endif()