cmake_minimum_required(VERSION 3.27)

# Название проекта
project(Lumin VERSION 0.3.2 LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции сборки
option(BUILD_EDITOR "Build the editor" ON)
option(BUILD_SCRIPT_API "Build the script API" ON)
option(BUILD_PROJECT_MANAGER "Build the project manager" ON)

if(WIN32)
    set(WINDOWS_TARGET_PLATFORM "win64" CACHE STRING "Windows target platform (win32 or win64)")
    set_property(CACHE WINDOWS_TARGET_PLATFORM PROPERTY STRINGS "win32" "win64")
    
    # Проверка корректности выбора платформы
    if(NOT WINDOWS_TARGET_PLATFORM STREQUAL "win32" AND NOT WINDOWS_TARGET_PLATFORM STREQUAL "win64")
        message(FATAL_ERROR "WINDOWS_TARGET_PLATFORM must be either 'win32' or 'win64', got: ${WINDOWS_TARGET_PLATFORM}")
    endif()
    
    message(STATUS "Windows target platform: ${WINDOWS_TARGET_PLATFORM}")
endif()

# Глобальные настройки - убираем Debug из путей
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Отключаем конфигурационные папки в путях вывода
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/lib)

# Устанавливаем уникальные имена для целей
set(LUMIN_CORE_TARGET "LuminCore" CACHE STRING "Core library target name")
set(LUMIN_SCRIPT_API_TARGET "LuminScriptAPI" CACHE STRING "Script API target name")
set(LUMIN_EDITOR_TARGET "LuminEditor" CACHE STRING "Editor target name")
set(LUMIN_PROJECT_MANAGER_TARGET "LuminProjectManager" CACHE STRING "Project Manager target name")

# Добавление подпроектов
add_subdirectory(core)

if(BUILD_SCRIPT_API)
    add_subdirectory(script_api)
endif()

if(BUILD_EDITOR)
    add_subdirectory(editor)
endif()

if(BUILD_PROJECT_MANAGER)
    add_subdirectory(project_manager)
endif()

# Информация о сборке
message(STATUS "Lumin Engine ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build options:")
message(STATUS "  - Editor: ${BUILD_EDITOR}")
message(STATUS "  - Script API: ${BUILD_SCRIPT_API}")
message(STATUS "  - Project Manager: ${BUILD_PROJECT_MANAGER}")
if(WIN32)
    message(STATUS "  - Windows target platform: ${WINDOWS_TARGET_PLATFORM}")
endif()
message(STATUS "Target names:")
message(STATUS "  - Core: ${LUMIN_CORE_TARGET}")
message(STATUS "  - Script API: ${LUMIN_SCRIPT_API_TARGET}")
message(STATUS "  - Editor: ${LUMIN_EDITOR_TARGET}")
message(STATUS "  - Project Manager: ${LUMIN_PROJECT_MANAGER_TARGET}")

# Создание папок для выходных файлов
add_custom_target(CreateDirectories ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
    COMMENT "Creating output directories"
)

# Копирование исполняемых файлов
if(BUILD_EDITOR)
    add_custom_target(CopyEditor ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${LUMIN_EDITOR_TARGET}> ${CMAKE_SOURCE_DIR}/bin/
        COMMENT "Copying editor executable to bin directory"
    )
    add_dependencies(CopyEditor CreateDirectories)
endif()

if(BUILD_PROJECT_MANAGER)
    add_custom_target(CopyProjectManager ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${LUMIN_PROJECT_MANAGER_TARGET}> ${CMAKE_SOURCE_DIR}/bin/
        COMMENT "Copying project manager executable to bin directory"
    )
    add_dependencies(CopyProjectManager CreateDirectories)
endif()

# Копирование библиотек
add_custom_target(CopyLibraries ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${LUMIN_CORE_TARGET}> ${CMAKE_SOURCE_DIR}/lib/
    COMMENT "Copying core library to lib directory"
)
add_dependencies(CopyLibraries CreateDirectories)

if(BUILD_SCRIPT_API)
    add_custom_target(CopyScriptAPI ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${LUMIN_SCRIPT_API_TARGET}> ${CMAKE_SOURCE_DIR}/lib/
        COMMENT "Copying script API library to lib directory"
    )
    add_dependencies(CopyScriptAPI CreateDirectories)
endif()

# Копирование зависимостей
add_custom_target(CopyDependencies ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glad> ${CMAKE_SOURCE_DIR}/lib/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glfw> ${CMAKE_SOURCE_DIR}/lib/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glm> ${CMAKE_SOURCE_DIR}/lib/
    COMMENT "Copying dependencies to lib directory"
)
add_dependencies(CopyDependencies CreateDirectories)

# Копирование ресурсов редактора
if(BUILD_EDITOR AND EXISTS "${CMAKE_SOURCE_DIR}/editor/resources")
    add_custom_target(CopyEditorResources ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/editor/resources ${CMAKE_SOURCE_DIR}/bin/resources
        COMMENT "Copying editor resources to bin directory"
    )
    add_dependencies(CopyEditorResources CreateDirectories)
endif()

# Копирование ресурсов core
if(EXISTS "${CMAKE_SOURCE_DIR}/core/resources")
    add_custom_target(CopyCoreResources ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/core/resources ${CMAKE_SOURCE_DIR}/bin/resources
        COMMENT "Copying core resources to bin directory"
    )
    add_dependencies(CopyCoreResources CreateDirectories)
endif()

# Копирование ресурсов project manager в корень bin
if(BUILD_PROJECT_MANAGER AND EXISTS "${CMAKE_SOURCE_DIR}/project_manager/resources")
    add_custom_target(CopyProjectManagerResources ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/project_manager/resources ${CMAKE_SOURCE_DIR}/bin/
        COMMENT "Copying project manager resources to bin root directory"
    )
    add_dependencies(CopyProjectManagerResources CreateDirectories)
endif() 

if(BUILD_PROJECT_MANAGER)
    add_custom_target(CopyProjectManagerLibraries ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/templates/project/library
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/core ${CMAKE_SOURCE_DIR}/bin/templates/project/library/core
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/script_api ${CMAKE_SOURCE_DIR}/bin/templates/project/library/script_api
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/dll ${CMAKE_SOURCE_DIR}/bin/templates/project/library/dll
        COMMENT "Copying core and script api libraries to project templates"
    )
    add_dependencies(CopyProjectManagerLibraries CreateDirectories)
endif()

if(WIN32)
    set(WINDOWS_TARGET_PLATFORM "win64" CACHE STRING "Windows target platform (win32 or win64)")
    message(STATUS "Windows target platform: ${WINDOWS_TARGET_PLATFORM}")
    add_custom_target(CopyWindowsDependencies ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/templates/project/library/dll
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/dll/${WINDOWS_TARGET_PLATFORM} ${CMAKE_SOURCE_DIR}/bin/
        COMMENT "Copying Windows dependencies to project templates"
    )
    add_dependencies(CopyWindowsDependencies CreateDirectories)
endif()