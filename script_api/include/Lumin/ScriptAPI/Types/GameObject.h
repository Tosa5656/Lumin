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
class GameObject
{
public:
    GameObject() {};
    GameObject(std::string gameObjectName, Lumin::Object::Object* gameObject);
    GameObject(std::string gameObjectName, std::string modelPath, Lumin::Object::ObjectShaderProgram* shader_program);
    
    ~GameObject() {};

    Transform transform;
private:
    Lumin::Object::Object* object = nullptr;
    Lumin::Renderer::Texture* texture = nullptr;
    Lumin::Object::ObjectShaderProgram* shader_program = nullptr;
    std::string name;

    void UpdateTransformInfo();
};