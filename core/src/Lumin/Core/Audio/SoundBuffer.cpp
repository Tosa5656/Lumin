/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#define DR_WAV_IMPLEMENTATION

#include <cstdint>

#include "Lumin/Core/Audio/SoundBuffer.h"
#include "third_party/dr_wav.h"

namespace Lumin {
namespace Audio {
SoundBuffer::~SoundBuffer() {
    if (m_buffer) alDeleteBuffers(1, &m_buffer);
}

bool SoundBuffer::LoadWav(const std::string& path) {
    drwav wav{};
    if (!drwav_init_file(&wav, path.c_str(), nullptr)) return false;

    const uint64_t frames = wav.totalPCMFrameCount;
    const uint32_t channels = wav.channels;
    const uint32_t sampleRate = wav.sampleRate;

    std::vector<int16_t> pcm(frames * channels);
    const drwav_uint64 readFrames = drwav_read_pcm_frames_s16(&wav, frames, pcm.data());
    drwav_uninit(&wav);
    if (readFrames == 0) return false;

    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 :
                    (channels == 2) ? AL_FORMAT_STEREO16 : 0;
    if (!format) return false;

    if (!m_buffer) alGenBuffers(1, &m_buffer);
    alBufferData(m_buffer, format, pcm.data(),
                 static_cast<ALsizei>(readFrames * channels * sizeof(int16_t)),
                 static_cast<ALsizei>(sampleRate));
    return true;
}
}
}