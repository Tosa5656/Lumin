/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_ ` _ \  | | | '_ \     \___ \  | __| | | | |  / _` | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/

#include "Lumin/Core/Audio/SoundSource.h"

namespace Lumin {
namespace Audio {
SoundSource::SoundSource() { alGenSources(1, &m_source); }
SoundSource::~SoundSource() { if (m_source) alDeleteSources(1, &m_source); }

void SoundSource::SetBuffer(ALuint buffer) { alSourcei(m_source, AL_BUFFER, (ALint)buffer); }
void SoundSource::Play()  { alSourcePlay(m_source); }
void SoundSource::Pause() { alSourcePause(m_source); }
void SoundSource::Stop()  { alSourceStop(m_source); }

void SoundSource::SetLooping(bool loop) { alSourcei(m_source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE); }
void SoundSource::SetGain(float gain)   { alSourcef(m_source, AL_GAIN, gain); }
void SoundSource::SetPitch(float pitch) { alSourcef(m_source, AL_PITCH, pitch); }
void SoundSource::SetPosition(const glm::vec3& p) { alSource3f(m_source, AL_POSITION, p.x, p.y, p.z); }
void SoundSource::SetVelocity(const glm::vec3& v) { alSource3f(m_source, AL_VELOCITY, v.x, v.y, v.z); }

bool SoundSource::IsPlaying() const {
    ALint state;
    alGetSourcei(m_source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}
}
}