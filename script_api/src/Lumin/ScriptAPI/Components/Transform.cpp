#include "Lumin/ScriptAPI/Components/Transform.h"

Transform::Transform(Object* object)
{
    root = object;
}

void Transform::SetPosition(Vector3 pos)
{
    position = pos;
    Update();
}

void Transform::SetRotation(Vector3 rot)
{
    rotation = rot;
    Update();
}

void Transform::SetScale(Vector3 scl)
{
    scale = scl;
    Update();
}

Vector3 Transform::GetPosition()
{
    return position;
}

Vector3 Transform::GetRotation()
{
    return rotation;
}

Vector3 Transform::GetScale()
{
    return scale;
}

void Transform::Update()
{
    root->SetPosition(glm::vec3(position.x, position.y, position.z));
    root->SetRotation(glm::vec3(rotation.x, rotation.y, rotation.z));
    root->SetScale(glm::vec3(scale.x, scale.y, scale.z));
}