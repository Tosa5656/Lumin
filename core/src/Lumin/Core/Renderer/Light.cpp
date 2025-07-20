// Implementation of Light system for Lumin Engine (single sunlight)

#include "Lumin/Core/Renderer/Light.h"
#include "Lumin/Core/Renderer/Renderer.h"

namespace Lumin {
namespace Renderer {

Light sunLight;

Light::Light()
    : position(0.0f), rotation(0.0f), color(glm::vec3(1.0f)), intensity(1.0f), enabled(true), type(LightType::Directional)
{
    UpdateDirectionFromRotation();
}

void Light::SetLight(bool en) {
    enabled = en;
}

bool Light::IsEnabled() const {
    return enabled;
}

void Light::UpdateDirectionFromRotation() {
    // Yaw (y), Pitch (x), Roll (z) — как у камеры
    float yaw = glm::radians(rotation.y);
    float pitch = glm::radians(rotation.x);
    // По умолчанию свет направлен вдоль -Z
    glm::vec3 dir;
    dir.x = cos(pitch) * sin(yaw);
    dir.y = sin(pitch);
    dir.z = -cos(pitch) * cos(yaw);
    direction = glm::normalize(dir);
}

void Light::DrawDebug(Lumin::Shaders::ShaderProgram& shader) const {
    glm::vec3 lightPos = -direction * 2.0f;
    DrawPoint(lightPos, color, shader);
    DrawLine(lightPos, glm::vec3(0.0f), color, shader);
}

} // namespace Renderer
} // namespace Lumin 