cmake_minimum_required(VERSION 3.27)

# Используем имя цели из родительского проекта, если оно определено
if(DEFINED LUMIN_EDITOR_TARGET)
    set(PROJECT_NAME ${LUMIN_EDITOR_TARGET})
else()
    set(PROJECT_NAME LuminEditor)
endif()

project(${PROJECT_NAME})

set(CXX_STANDARD 18)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp)
file(GLOB_RECURSE EDITOR_HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES} ${EDITOR_HEADERS})

# Подключаем библиотеки core и script_api (используем имена из родительского проекта)
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

# Используем относительные пути для include директорий
target_include_directories(${PROJECT_NAME} PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../script_api/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui/backends>
)