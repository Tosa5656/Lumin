#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Lumin/Core/Audio/SoundBuffer.h"
#include "Lumin/Core/Audio/SoundSource.h"

namespace Lumin {
namespace Audio {
class AudioManager {
public:
    static void PlaySound(const std::string& wavPath, float gain, bool loop = false, glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 velocity = glm::vec3(0, 0, 0));
    static void Update();
    static void StopAll();

private:
    static std::vector<std::unique_ptr<SoundSource>> m_sources;
    static std::vector<std::unique_ptr<SoundBuffer>> m_buffers;
};
}
}