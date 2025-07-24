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