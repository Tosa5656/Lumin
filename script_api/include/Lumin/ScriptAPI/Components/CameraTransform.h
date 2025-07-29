/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#pragma once

#include <iostream>
#include <Lumin.h>
#include "Lumin/ScriptAPI/Utils/Vectors.h"

using namespace Lumin::Renderer;

class CameraTransform
{
public:
    CameraTransform() {};
    CameraTransform(RendererCamera* camera);

    void SetPosition(Vector3 position);
    void SetLookAt(Vector3 lookAt);
    void SetUp(Vector3 up);

    Vector3 GetPosition();
    Vector3 GetLookAt();
    Vector3 GetUp();
private:
    RendererCamera* camera;

    Vector3 position = Vector3(0, 0, 0);
    Vector3 lookAt = Vector3(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0);
};