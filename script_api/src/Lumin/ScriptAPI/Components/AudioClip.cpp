#include "Lumin/ScriptAPI/Components/AudioClip.h"
#include <string>

AudioClip::AudioClip(std::string audioPath, bool loop, float gain, Vector3 position, Vector3 velocity)
{
    this->audioPath = audioPath;
    this->loop = loop;
    this->gain = gain;
    this->position = position;
    this->velocity = velocity;
}

void AudioClip::Play()
{
    Lumin::Audio::AudioManager::PlaySound(audioPath, gain, loop, ToGlmVec3(position), ToGlmVec3(velocity));
}

void AudioClip::SetAudioPath(std::string audioPath) { this->audioPath = audioPath; }
void AudioClip::SetLoop(bool loop) { this->loop = loop; }
void AudioClip::SetGain(float gain) { this->gain = gain; }
void AudioClip::SetPosition(Vector3 position) { this->position = position; }
void AudioClip::SetVelocity(Vector3 velocity) { this->velocity = velocity; }

std::string AudioClip::GetAudioPath() { return audioPath; }
bool AudioClip::GetLoop() { return loop; }
float AudioClip::GetGain() { return gain; }
Vector3 AudioClip::GetPosition() { return position; }
Vector3 AudioClip::GetVelocity() { return velocity; }