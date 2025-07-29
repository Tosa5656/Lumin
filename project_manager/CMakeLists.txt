# Project Manager CMakeLists.txt
# Исполняемый файл для управления проектами

cmake_minimum_required(VERSION 3.27)

# Используем имя цели из родительского проекта, если оно определено
if(DEFINED LUMIN_PROJECT_MANAGER_TARGET)
    set(PROJECT_NAME ${LUMIN_PROJECT_MANAGER_TARGET})
else()
    set(PROJECT_NAME ProjectManager)
endif()

# Проверяем наличие исходных файлов
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    # Создаём исполняемый файл ProjectManager
    add_executable(${PROJECT_NAME}
        src/main.cpp
    )
    
    # Подключаем библиотеки, если они доступны
    if(TARGET ${LUMIN_CORE_TARGET})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LUMIN_CORE_TARGET})
    endif()
    
    if(TARGET ${LUMIN_SCRIPT_API_TARGET})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LUMIN_SCRIPT_API_TARGET})
    endif()
    
    # Настройка include директорий
    target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
    
    message(STATUS "Project Manager executable configured: ${PROJECT_NAME}")
else()
    message(WARNING "Project Manager source files not found. Skipping executable creation.")
endif() 