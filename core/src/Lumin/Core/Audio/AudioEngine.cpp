/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#include "Lumin/Core/Audio/AudioEngine.h"
#include <AL/al.h>

namespace Lumin {
namespace Audio {
AudioEngine& AudioEngine::Instance() {
    static AudioEngine inst;
    return inst;
}

bool AudioEngine::Initialize(const char* deviceName) {
    m_device = alcOpenDevice(deviceName);
    if (!m_device) return false;
    m_context = alcCreateContext(m_device, nullptr);
    if (!m_context || !alcMakeContextCurrent(m_context)) return false;

    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    return true;
}

void AudioEngine::Shutdown() {
    alcMakeContextCurrent(nullptr);
    if (m_context) alcDestroyContext(m_context), m_context = nullptr;
    if (m_device) alcCloseDevice(m_device), m_device = nullptr;
}

void AudioEngine::SetListener(const glm::vec3& pos,
                              const glm::vec3& forward,
                              const glm::vec3& up,
                              const glm::vec3& velocity) {
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
    const float ori[6] = { forward.x, forward.y, forward.z, up.x, up.y, up.z };
    alListenerfv(AL_ORIENTATION, ori);
}
}
}