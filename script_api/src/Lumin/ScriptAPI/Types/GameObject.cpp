/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#include "Lumin/ScriptAPI/Types/GameObject.h"

GameObject::GameObject(std::string gameObjectName, Lumin::Object::Object* gameObject)
{
    name = gameObjectName;
    object = gameObject;
    transform = Transform(object);
}

GameObject::GameObject(std::string gameObjectName, std::string modelPath, Lumin::Object::ObjectShaderProgram* shaderProgram)
{
    name = gameObjectName;
    object = Lumin::Object::Object::FromOBJ(modelPath, *shaderProgram);
    transform = Transform(object);
}