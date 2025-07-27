# Project Manager CMakeLists.txt
# Пока что это заглушка для будущего менеджера проектов

cmake_minimum_required(VERSION 3.27)

# Используем имя цели из родительского проекта, если оно определено
if(DEFINED LUMIN_PROJECT_MANAGER_TARGET)
    set(PROJECT_NAME ${LUMIN_PROJECT_MANAGER_TARGET})
else()
    set(PROJECT_NAME ProjectManager)
endif()

# Создаём заглушку для ProjectManager
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Пока что main.cpp не существует, поэтому комментируем
# Когда будет готов project_manager, раскомментировать

# target_link_libraries(${PROJECT_NAME} PRIVATE LuminCore) 