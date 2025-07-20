cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME LuminEditor)
project(${PROJECT_NAME})

set(CXX_STANDARD 18)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

include_directories(include/)

file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp)
file(GLOB_RECURSE EDITOR_HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# Подключаем библиотеки core и script_api
add_subdirectory(../core core_build)
add_subdirectory(../script_api script_api_build)
target_link_libraries(${PROJECT_NAME} PRIVATE LuminCore ScriptAPI)

target_include_directories(${PROJECT_NAME} PRIVATE ../core/include ../script_api/include)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${RESOURCES_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:${PROJECT_NAME}> ${BIN_DIR}
)