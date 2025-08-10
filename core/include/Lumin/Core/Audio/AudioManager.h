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
    void PlaySound(const std::string& wavPath, float gain = 1.0f, bool loop = false);
    void Update();
    void StopAll();

private:
    std::vector<std::unique_ptr<SoundSource>> m_sources;
    std::vector<std::unique_ptr<SoundBuffer>> m_buffers;
};
}
}