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