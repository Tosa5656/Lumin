#include "Lumin/Core/Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

namespace Lumin {
namespace Renderer {

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up)
    : Position(position), LookAtTarget(lookAt), Up(up)
{
}

void Camera::SetPosition(const glm::vec3& position) {
    Position = position;
}

void Camera::SetLookAt(const glm::vec3& target) {
    LookAtTarget = target;
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, LookAtTarget, Up);
}

} // namespace Renderer
} // namespace Lumin
