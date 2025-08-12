# Lumin Engine

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
[![Build](https://img.shields.io/github/actions/workflow/status/Tosa5656/Lumin/cmake.yml?branch=main)](https://github.com/Tosa5656/Lumin/actions)
[![Issues](https://img.shields.io/github/issues/Tosa5656/Lumin)](https://github.com/Tosa5656/Lumin/issues)
[![Stars](https://img.shields.io/github/stars/Tosa5656/Lumin?style=social)](https://github.com/Tosa5656/Lumin)

---

## Описание
**Lumin** — кроссплатформенный 3D-движок на C++ с использованием OpenGL, GLFW и GLM. Проект ориентирован на простоту, модульность и расширяемость, подходит для обучения и создания собственных 3D-приложений.

Lumin состоит из нескольких модулей:
- **Core** — основная библиотека.
- **ScriptAPI** — API для создания пользовательских скриптов.
- **Editor** — редактор сцены с UI (в разработке).
- **Project Manager** — менеджер проектов (в разработке).

---

## Использованные технологии
- **C++18**
- [GLFW](https://www.glfw.org/) — управление окном и вводом
- [GLAD](https://glad.dav1d.de/) — загрузка OpenGL-функций
- [GLM](https://github.com/g-truc/glm) — математика для 3D
- [stb_image](https://github.com/nothings/stb) — загрузка изображений
- [ImGui](https://github.com/ocornut/imgui) — UI и отладка
- [CMake](https://github.com/Kitware/CMake) — сборка проекта

## Реализованные возможности
- ✅ Камера и полное взаимодействие с ней
- ✅ Управление освещением
- ✅ Импорт моделей (OBJ формат)
- ✅ Поддержка текстурирования
- ✅ Базовое освещение (directional light)
- ✅ Система объектов и менеджер объектов
- ✅ UI/отладка через ImGui
- ✅ Система событий и ввода
- ✅ Модульная архитектура
- ✅ Поддержка аудио

## Планы развития
- ❌ Project Manager
- ❌ ScriptAPI (в разработке)
- ❌ Расширенное освещение (Phong, Blinn-Phong, PBR)
- ❌ Физика и коллизии
- ❌ Анимации и скелеты
- ❌ Система частиц
- ❌ Поддержка других форматов моделей

---

## Быстрый старт

### Требования
- CMake 3.27+
- C++17 компилятор
- OpenGL совместимая видеокарта

### Сборка
```bash
# Клонируйте репозиторий
git clone https://github.com/Tosa5656/Lumin.git
cd Lumin

# Сконфигурируйте проект
cmake . -B build

# Соберите проект
cmake --build build
```

После сборки все файлы будут скопированы в корень проекта:
- `bin/` — исполняемые файлы и ресурсы
- `lib/` — библиотеки

Подробнее о системе сборки вы можете прочитать в [BUILD.md](https://github.com/Tosa5656/Lumin/blob/master/BUILD.md)

### Запуск
```bash
# Из корня проекта
./bin/LuminEditor.exe
```

### Управление
- **WASD** — перемещение камеры
- **Мышь** — поворот камеры
- **Стрелки** — управление направлением света
- **Q/E** — подъём/спуск камеры
- **Space** - воспроизвести звук

---

## Структура проекта
```
Lumin/
├── core/                   # Основная библиотека
│   ├── include/           # Заголовочные файлы
│   ├── src/              # Исходный код
│   ├── dependencies/     # Внешние зависимости
├── script_api/           # API для скриптов
│   ├── include/          # Заголовочные файлы
│   └── src/             # Исходный код
├── editor/               # Редактор сцены
│   ├── src/             # Исходный код
│   └── resources/       # Ресурсы редактора
├── bin/                  # Исполняемые файлы (после сборки)
├── lib/                  # Библиотеки (после сборки)
├── build/                # Файлы сборки
├── CMakeLists.txt        # Корневой файл сборки
└── BUILD.md             # Подробные инструкции по сборке
```

---

## Контакты
- Автор: [Tosa5656](https://github.com/Tosa5656)
- Issues и предложения: [Issues](https://github.com/Tosa5656/Lumin/issues)

---

## Лицензия
Проект распространяется под лицензией [GNU GPL v3.0](LICENSE). 
