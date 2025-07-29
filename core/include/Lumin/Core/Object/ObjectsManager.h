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
#include <vector>
#include "Lumin/Core/Object/Object.h"

namespace Lumin {
    namespace Object {
        class Object;
        
        class ObjectsManager
        {
        public:
            ObjectsManager() {};

            static void AddObject(Object* object);
            static void RemoveObject(int index);

            static Object* GetObject(int index);

            static void DrawObjects();
        private:
            static std::vector<Object*> objects;
        };
    }
}