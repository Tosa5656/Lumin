/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#pragma once

#include <AL/alc.h>
#include <glm/vec3.hpp>

namespace Lumin {
namespace Audio {
class AudioEngine {
public:
    static AudioEngine& Instance();

    bool Initialize(const char* deviceName);
    void Shutdown();

    void SetListener(const glm::vec3& pos,
                     const glm::vec3& forward,
                     const glm::vec3& up,
                     const glm::vec3& velocity = {0,0,0});

private:
    ALCdevice*  m_device = nullptr;
    ALCcontext* m_context = nullptr;
};
}
}