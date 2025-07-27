# Сборка проекта Lumin Engine

## Быстрая сборка

```bash
cmake . -B build
cmake --build build
```

## Опции сборки

Вы можете контролировать, какие компоненты собирать:

```bash
# Сборка только core
cmake -DBUILD_EDITOR=OFF -DBUILD_SCRIPT_API=OFF . -B build

# Сборка core + editor (без script_api)
cmake -DBUILD_SCRIPT_API=OFF . -B build

# Сборка core + script_api (без editor)
cmake -DBUILD_EDITOR=OFF . -B build

# Сборка всего (по умолчанию)
cmake . -B build
```

## Структура сборки

После сборки в папке проекта будут созданы:

- `bin/` - исполняемые файлы (LuminEditor.exe)
- `lib/` - библиотеки (LuminCore.lib, ScriptAPI.lib)
- `install/` - установленные файлы (если выполнить `cmake --install .`)

## Компоненты

- **core** - основная библиотека движка (всегда собирается)
- **script_api** - API для скриптов
- **editor** - редактор сцены
- **project_manager** - менеджер проектов (пока не реализован)

## Требования

- CMake 3.27+
- C++17 компилятор
- OpenGL совместимая видеокарта 