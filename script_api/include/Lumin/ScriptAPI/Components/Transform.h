#pragma once

#include <iostream>
#include <Lumin.h>
#include "Lumin/ScriptAPI/Utils/Vectors.h"

using namespace Lumin::Object;

class Transform
{
public:
    Transform() {};
    Transform(Object* object);

    void SetPosition(Vector3 position);
    void SetRotation(Vector3 rotation);
    void SetScale(Vector3 scale);

    Vector3 GetPosition();
    Vector3 GetRotation();
    Vector3 GetScale();
private:
    Object* root;

    Vector3 position = Vector3(1, 1, 1);
    Vector3 rotation = Vector3(0, 0, 0);
    Vector3 scale = Vector3(1, 1, 1);

    void Update();
};