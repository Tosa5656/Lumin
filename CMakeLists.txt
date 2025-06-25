cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME Lumin)
project(${PROJECT_NAME})

set(CXX_STANDARD 18)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp
                                ${SRC_DIR}/Window/Window.cpp
								${SRC_DIR}/Renderer/Renderer.cpp
                                ${SRC_DIR}/Renderer/Object.cpp
                                ${SRC_DIR}/Shaders/Shaders.cpp
                                ${SRC_DIR}/Renderer/Camera.cpp
                                ${SRC_DIR}/Renderer/Texture.cpp
                                ${SRC_DIR}/Renderer/Light.cpp

                                ${SRC_DIR}/stb_image_impl.cpp)

option(RELEASE_MODE "Build with console (OFF = Win32 GUI mode)" ON)

add_subdirectory(dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(dependencies/glm)
target_link_libraries(${PROJECT_NAME} glm)

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
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/imgui dependencies/imgui/backends)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCES_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}> ${BIN_DIR}
)

if (WIN32)
    if (RELEASE_MODE)
		set(APP_SUBSYSTEM "WINDOWS")
		set(APP_ENTRY "WinMainCRTStartup")
		target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
    else()
		set(APP_SUBSYSTEM "CONSOLE")
        set(APP_ENTRY "mainCRTStartup")
		target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
    endif()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:${APP_SUBSYSTEM} /ENTRY:${APP_ENTRY}"
    )
endif()