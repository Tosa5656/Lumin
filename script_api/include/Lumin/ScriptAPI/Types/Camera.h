#pragma once

#include <Lumin.h>
#include "Lumin/ScriptAPI/Components/CameraTransform.h"

class Camera
{
public:
    Camera();

    CameraTransform transform;
private:
    Lumin::Renderer::RendererCamera* camera;
};
