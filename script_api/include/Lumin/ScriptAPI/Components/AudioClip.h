#pragma once

#include <iostream>
#include <string>
#include <Lumin/Core/Audio/AudioManager.h>
#include "Lumin/ScriptAPI/Utils/Vectors.h"

class AudioClip
{
public:
    AudioClip(std::string audioPath, bool loop=false, float gain=1.0f, Vector3 position=Vector3(0, 0, 0), Vector3 velocity=Vector3(0, 0, 0));
    
    void Play();
    
    void SetAudioPath(std::string audioPath);
    void SetLoop(bool loop);
    void SetGain(float gain);
    void SetPosition(Vector3 position);
    void SetVelocity(Vector3 velocity);

    std::string GetAudioPath();
    bool GetLoop();
    float GetGain();
    Vector3 GetPosition();
    Vector3 GetVelocity();
private:
    std::string audioPath = "";
    bool loop = false;
    float gain = 1.0f;
    Vector3 position = Vector3(0, 0, 0);
    Vector3 velocity = Vector3(0, 0, 0);
};