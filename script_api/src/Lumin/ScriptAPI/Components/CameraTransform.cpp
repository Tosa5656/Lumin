#include "Lumin/ScriptAPI/Components/CameraTransform.h"

CameraTransform::CameraTransform(RendererCamera* camera)
{
    this->camera = camera;
}

void CameraTransform::SetPosition(Vector3 position)
{
    this->position = position;
    this->camera->SetPosition(glm::vec3(position.x, position.y, position.z));
}

void CameraTransform::SetLookAt(Vector3 lookAt)
{
    this->lookAt = lookAt;
    this->camera->SetLookAt(glm::vec3(lookAt.x, lookAt.y, lookAt.z));
}

void CameraTransform::SetUp(Vector3 up)
{
    this->up = up;
    this->camera->SetUp(glm::vec3(up.x, up.y, up.z));
}

Vector3 CameraTransform::GetPosition()
{
    glm::vec3 pos = this->camera->GetPosition();
    return Vector3(pos.x, pos.y, pos.z);
}

Vector3 CameraTransform::GetLookAt()
{
    glm::vec3 look = this->camera->GetLookAtTarget();
    return Vector3(look.x, look.y, look.z);
}

Vector3 CameraTransform::GetUp()
{
    glm::vec3 up = this->camera->GetUp();
    return Vector3(up.x, up.y, up.z);
}