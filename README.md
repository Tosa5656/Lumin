# Lumin Engine

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
[![Build](https://img.shields.io/github/actions/workflow/status/Tosa5656/Lumin/cmake.yml?branch=main)](https://github.com/Tosa5656/Lumin/actions)
[![Issues](https://img.shields.io/github/issues/Tosa5656/Lumin)](https://github.com/Tosa5656/Lumin/issues)
[![Stars](https://img.shields.io/github/stars/Tosa5656/Lumin?style=social)](https://github.com/Tosa5656/Lumin)

---

## Описание
**Lumin** — кроссплатформенный 3D-движок на C++ с использованием OpenGL, GLFW и GLM. Проект ориентирован на простоту, модульность и расширяемость, подходит для обучения и создания собственных 3D-приложений.

---

## Структура пользовательского кода
Для удобства в Lumin реализованы три пользовательские функции:
- **Awake** — вызывается до инициализации графики (до создания окна и OpenGL).
- **Start** — вызывается сразу после инициализации GLAD и создания окна. Здесь удобно создавать шейдеры, объекты, загружать ресурсы.
- **Update** — вызывается каждый кадр, после очистки экрана и обработки событий. Здесь размещается логика рендера и обновления сцены.

### Пример использования:
```cpp
void Awake() {
    // Здесь можно подготовить данные, которые не требуют OpenGL
}

void Start() {
    Shader vertexShader("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
    ObjectShaderProgram objectSP(vertexShader, fragmentShader);
    float vertices[] = { ... };
    float colors[] = { ... };
    unsigned int indices[] = { ... };
    object = new Object("Cube", vertices, 24, colors, 24, indices, 36, objectSP);
}

void Update() {
    if (object) object->Draw();
}

int main() {
    Window window(800, 600, "Lumin", Awake, Start);
    window.run(Update);
    if (object) delete object;
    return 0;
}
```

---

## Использовано
- **C++18**
- [GLFW](https://www.glfw.org/) — управление окном и вводом
- [GLAD](https://glad.dav1d.de/) — загрузка OpenGL-функций
- [GLM](https://github.com/g-truc/glm) — математика для 3D
- [stb_image](https://github.com/nothings/stb) — загрузка изображений
- **CMake** — сборка проекта

---

## Реализовано
- Окно с поддержкой OpenGL и иконкой (EXE и окно)
- Рендеринг 3D-объектов (VAO, VBO, EBO)
- Класс Object для управления мешами
- Класс Camera (орбитальная и свободная)
- Передача матрицы MVP в шейдер
- Орбитальная камера вокруг куба
- Глубина (Depth Test)
- Модульная архитектура (Window, Renderer, Object, Camera, Shaders)
- Система пользовательских хуков: Awake, Start, Update

---

## Планы
- Перемещение и вращение камеры с помощью клавиатуры и мыши
- Импорт моделей (OBJ, glTF)
- Поддержка текстурирования
- Реализация освещения (Phong, Blinn-Phong)
- Система сцены и менеджер объектов
- UI/отладка через ImGui
- Система событий и ввода
- Документация и примеры

---

## Сборка
```bash
# Клонируйте репозиторий
$ git clone https://github.com/Tosa5656/Lumin.git
$ cd Lumin

# Создайте папку для сборки
$ mkdir build && cd build

# Генерируйте проект через CMake
$ cmake ..

# Соберите проект
$ cmake --build .
```

---

## Запуск
- После сборки исполняемый файл и ресурсы будут в папке `bin/`.
- Для Windows: убедитесь, что рядом с EXE лежат все ресурсы (шэйдеры, иконки, т.д.).

---

## Контакты
- Автор: [Tosa5656](https://github.com/Tosa5656)
- Issues и предложения: [https://github.com/Tosa5656/Lumin/issues](https://github.com/Tosa5656/Lumin/issues)

---

## Лицензия
Проект распространяется под лицензией [GNU GPL v3.0](LICENSE). 