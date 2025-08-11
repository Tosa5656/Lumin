#include "Lumin/Core/Audio/AudioManager.h"
#include <algorithm>

namespace Lumin {
namespace Audio {
// Define static members
std::vector<std::unique_ptr<SoundSource>> AudioManager::m_sources;
std::vector<std::unique_ptr<SoundBuffer>> AudioManager::m_buffers;
void AudioManager::PlaySound(const std::string& wavPath, float gain, bool loop, glm::vec3 position, glm::vec3 velocity) {
    auto buffer = std::make_unique<SoundBuffer>();
    if (!buffer->LoadWav(wavPath)) return;

    auto source = std::make_unique<SoundSource>();
    source->SetBuffer(buffer->Id());
    source->SetGain(gain);
    source->SetLooping(loop);
    source->SetPosition(position);
    source->SetVelocity(velocity);
    source->Play();

    m_buffers.push_back(std::move(buffer));
    m_sources.push_back(std::move(source));
}

void AudioManager::Update() {
    m_sources.erase(
        std::remove_if(m_sources.begin(), m_sources.end(),
            [](const std::unique_ptr<SoundSource>& src) {
                return !src->IsPlaying();
            }),
        m_sources.end()
    );
}

void AudioManager::StopAll() {
    for (auto& src : m_sources) src->Stop();
    m_sources.clear();
    m_buffers.clear();
}
}
}