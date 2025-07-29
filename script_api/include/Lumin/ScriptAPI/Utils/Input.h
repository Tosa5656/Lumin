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
#include <unordered_map>
#include <Lumin.h>

class Input
{
public:
    Input() {};
    ~Input() {};

    static void SetWindow(GLFWwindow* glwindow);

    static bool GetKey(int key);
    static bool GetKeyUp(int key);
    static bool GetKeyDown(int key);
    static bool GetMouseButton(int button);
    static bool GetMouseButtonDown(int button);
    static bool GetMouseButtonUp(int button);
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseDelta();
private:
    static GLFWwindow* window;
    static std::unordered_map<int, bool> keyLast;
    static std::unordered_map<int, bool> mouseLast;
    static double lastX, lastY;
    static bool firstMouse;
    static glm::vec2 mouseDelta;
};