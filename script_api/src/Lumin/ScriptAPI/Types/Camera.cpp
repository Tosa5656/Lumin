#include "Lumin/ScriptAPI/Types/Camera.h"

Camera::Camera()
{
    // Используем указатель на глобальную переменную camera
    this->camera = &Lumin::Renderer::camera;
    this->transform = CameraTransform(this->camera);
}