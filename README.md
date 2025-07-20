# Lumin Engine

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
[![Build](https://img.shields.io/github/actions/workflow/status/Tosa5656/Lumin/cmake.yml?branch=main)](https://github.com/Tosa5656/Lumin/actions)
[![Issues](https://img.shields.io/github/issues/Tosa5656/Lumin)](https://github.com/Tosa5656/Lumin/issues)
[![Stars](https://img.shields.io/github/stars/Tosa5656/Lumin?style=social)](https://github.com/Tosa5656/Lumin)

---

## Описание
**Lumin** — кроссплатформенный 3D-движок на C++ с использованием OpenGL, GLFW и GLM. Проект ориентирован на простоту, модульность и расширяемость, подходит для обучения и создания собственных 3D-приложений.

---

## Пользовательский код
На данный момент ScriptAPI находится в **активной разработке.**

## Использовано
- **C++18**
- [GLFW](https://www.glfw.org/) — управление окном и вводом
- [GLAD](https://glad.dav1d.de/) — загрузка OpenGL-функций
- [GLM](https://github.com/g-truc/glm) — математика для 3D
- [stb_image](https://github.com/nothings/stb) — загрузка изображений
- [CMake](https://github.com/Kitware/CMake) — сборка проекта

## Планы
- Перемещение и вращение камеры с помощью клавиатуры и мыши ✅
- Импорт моделей (OBJ) ✅
- Поддержка текстурирования ✅
- Реализация освещения (Phong, Blinn-Phong) ❌
- Система сцены и менеджер объектов ❌
- UI/отладка через ImGui ✅
- Система событий и ввода ✅
- Документация и примеры ❌

---

## Сборка
```bash
# Клонируйте репозиторий
$ git clone https://github.com/Tosa5656/Lumin.git
$ cd Lumin/editor

# Генерируйте проект через CMake
$ cmake . -B build

# Соберите проект
$ cmake --build build
```

---

## Запуск
- После сборки исполняемый файл и ресурсы будут в папке `bin/`.
- Убедитесь, что рядом с EXE лежат все ресурсы (шэйдеры, иконки, т.д.).

---

## Контакты
- Автор: [Tosa5656](https://github.com/Tosa5656)
- Issues и предложения: [https://github.com/Tosa5656/Lumin/issues](https://github.com/Tosa5656/Lumin/issues)

---

## Лицензия
Проект распространяется под лицензией [GNU GPL v3.0](LICENSE). 