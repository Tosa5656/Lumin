/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#pragma once

#include <AL/al.h>
#include <glm/vec3.hpp>

namespace Lumin {
namespace Audio {
class SoundSource {
public:
    SoundSource();
    ~SoundSource();

    void SetBuffer(ALuint buffer);
    void Play();
    void Pause();
    void Stop();

    void SetLooping(bool loop);
    void SetGain(float gain);
    void SetPitch(float pitch);
    void SetPosition(const glm::vec3& p);
    void SetVelocity(const glm::vec3& v);

    bool IsPlaying() const;
private:
    ALuint m_source = 0;
};
}
}