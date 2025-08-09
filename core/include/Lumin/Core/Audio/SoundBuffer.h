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
#include <vector>
#include <string>

namespace Lumin {
namespace Audio {
class SoundBuffer {
public:
    SoundBuffer() = default;
    ~SoundBuffer();
    bool LoadWav(const std::string& path);
    ALuint Id() const { return m_buffer; }
private:
    ALuint m_buffer = 0;
};
}
}