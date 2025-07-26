#include "Lumin/Core/Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace Lumin {
namespace Renderer {

RendererCamera::RendererCamera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up)
    : Position(position), LookAtTarget(lookAt), Up(up)
{
}

void RendererCamera::SetPosition(const glm::vec3& position) {
    Position = position;
}

void RendererCamera::SetLookAt(const glm::vec3& target) {
    LookAtTarget = target;
}

void RendererCamera::SetUp(const glm::vec3& up) {
    Up = up;
}

glm::mat4 RendererCamera::GetViewMatrix() const {
    return glm::lookAt(Position, LookAtTarget, Up);
}

} // namespace Renderer
} // namespace Lumin
