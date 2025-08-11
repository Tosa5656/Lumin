#include "Lumin/ScriptAPI/Components/AudioListener.h"
#include <glm/glm.hpp>
#include <Lumin/Core/Audio/AudioEngine.h>

// Define static members
Camera AudioListener::rootCamera;
ListenerTransform AudioListener::transform;

void AudioListener::SetCamera(Camera camera)
{
    rootCamera = camera;
}

void AudioListener::Update()
{
    const glm::vec3 pos = ToGlmVec3(rootCamera.transform.GetPosition());
    const glm::vec3 lookAt = ToGlmVec3(rootCamera.transform.GetLookAt());
    const glm::vec3 up = ToGlmVec3(rootCamera.transform.GetUp());
    const glm::vec3 forward = glm::normalize(lookAt - pos);
    Lumin::Audio::AudioEngine::Instance().SetListener(pos, forward, up);
}

// ListenerTransform method implementations
void ListenerTransform::SetPosition(Vector3 position)
{
    this->position = position;
}

void ListenerTransform::SetLookAt(Vector3 lookAt)
{
    this->lookAt = lookAt;
}

void ListenerTransform::SetUp(Vector3 up)
{
    this->up = up;
}

void ListenerTransform::SetVelocity(Vector3 velocity)
{
    this->velocity = velocity;
}

Vector3 ListenerTransform::GetPosition()
{
    return position;
}

Vector3 ListenerTransform::GetLookAt()
{
    return lookAt;
}

Vector3 ListenerTransform::GetUp()
{
    return up;
}

Vector3 ListenerTransform::GetVelocity()
{
    return velocity;
}