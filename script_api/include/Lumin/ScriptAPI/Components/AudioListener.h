#pragma once

#include <iostream>
#include <Lumin.h>
#include "Lumin/ScriptAPI/ScriptAPI.h"



class ListenerTransform
{
public:
    ListenerTransform() {};
    ListenerTransform(Vector3 position, Vector3 lookat, Vector3 up, Vector3 velocity)
    {
        this->position = position;
        this->lookAt = lookat;
        this->up= up;
        this->velocity = velocity;
    };

    void SetPosition(Vector3 position);
    void SetLookAt(Vector3 lookAt);
    void SetUp(Vector3 up);
    void SetVelocity(Vector3 velocity);

    Vector3 GetPosition();
    Vector3 GetLookAt();
    Vector3 GetUp();
    Vector3 GetVelocity();
private:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 lookAt = Vector3(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0);
    Vector3 velocity = Vector3(0, 0, 0);
};

class AudioListener
{
public:
    AudioListener() {};
    ~AudioListener() {};

    static void SetCamera(Camera camera);
    static void Update();

    static ListenerTransform transform;
private:
    static Camera rootCamera;
};