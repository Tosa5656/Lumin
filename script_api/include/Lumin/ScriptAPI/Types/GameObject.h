/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <iostream>
#include <Lumin.h>
#include "Lumin/ScriptAPI/Components/Transform.h"
#include "Lumin/ScriptAPI/Utils/Vectors.h"
/////////////////////////////////////////////////
/// \class GameObject
/// \brief Класс-обёртка для объектов ScriptAPI.
/// \authors  Tosa
/// \version  0.3.2
/// \date     2024-07-20
/// \warning  Использовать только с поддержкой LuminCore
/// \copyright GPL v3.0
/////////////////////////////////////////////////
class GameObject
{
public:
    /////////////////////////////////////////////////////////////////
    /// \brief Конструктор по умолчанию.
    /// \authors  Tosa
    /// \date     2024-07-20
    /////////////////////////////////////////////////////////////////
    GameObject() {};
    /////////////////////////////////////////////////////////////////
    /// \brief Конструктор с объектом.
    /// \param[in] object Указатель на объект Lumin::Object::Object
    /// \authors  Tosa
    /// \date     2024-07-20
    /////////////////////////////////////////////////////////////////
    GameObject(std::string gameObjectName, Lumin::Object::Object* gameObject);
    /////////////////////////////////////////////////////////////////
    /// \brief Конструктор с путём к модели и шейдером.
    /// \param[in] modelPath Путь к модели
    /// \param[in] shader_program Указатель на шейдерную программу
    /// \authors  Tosa
    /// \date     2024-07-20
    /////////////////////////////////////////////////////////////////
    GameObject(std::string gameObjectName, std::string modelPath, Lumin::Object::ObjectShaderProgram* shader_program);
    /////////////////////////////////////////////////////////////////
    /// \brief Деструктор.
    /// \authors  Tosa
    /// \date     2024-07-20
    /////////////////////////////////////////////////////////////////
    ~GameObject() {};

    Transform transform;
private:
    Lumin::Object::Object* object = nullptr;
    Lumin::Renderer::Texture* texture = nullptr;
    Lumin::Object::ObjectShaderProgram* shader_program = nullptr;
    std::string name;

    void UpdateTransformInfo();
};