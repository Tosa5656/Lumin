cmake_minimum_required(VERSION 3.27)

# Используем имя цели из родительского проекта, если оно определено
if(DEFINED LUMIN_SCRIPT_API_TARGET)
    set(PROJECT_NAME ${LUMIN_SCRIPT_API_TARGET})
else()
    set(PROJECT_NAME ScriptAPI)
endif()

project(${PROJECT_NAME})

set(CXX_STANDARD 18)

file(GLOB_RECURSE SCRIPT_API_SOURCES src/*.cpp)
file(GLOB_RECURSE SCRIPT_API_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${SCRIPT_API_SOURCES} ${SCRIPT_API_HEADERS})

# Используем имя цели core из родительского проекта
if(DEFINED LUMIN_CORE_TARGET)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LUMIN_CORE_TARGET})
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC LuminCore)
endif()

# Используем относительные пути для include директорий
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../core/dependencies/imgui/backends>
)