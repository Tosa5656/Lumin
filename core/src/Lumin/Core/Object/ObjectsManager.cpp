/*
  _                            _              _____   _                 _   _         
 | |                          (_)            / ____| | |               | | (_)        
 | |       _   _   _ __ ___    _   _ __     | (___   | |_   _   _    __| |  _    ___  
 | |      | | | | | '_  _ \  | | | '_ \     \___ \  | __| | | | |  / _ | | |  / _ \ 
 | |____  | |_| | | | | | | | | | | | | |    ____) | | |_  | |_| | | (_| | | | | (_) |
 |______|  \__,_| |_| |_| |_| |_| |_| |_|   |_____/   \__|  \__,_|  \__,_| |_|  \___/ 
                                                                                      
*/
#include "Lumin/Core/Object/ObjectsManager.h"

namespace Lumin {
    namespace Object {
        void ObjectsManager::AddObject(Object* object)
        {
            objects.push_back(object);
        }

        void ObjectsManager::RemoveObject(int index)
        {
            if (index >= 0 && index < objects.size())
                objects.erase(objects.begin() + index);
        }

        Object* ObjectsManager::GetObject(int index)
        {
            if (index >= 0 && index < objects.size())
                return objects[index];
            return nullptr;
        }

        void ObjectsManager::DrawObjects()
        {
            for (auto object : objects)
                if (object) object->Draw();
        }

        std::vector<Object*> ObjectsManager::objects;
    }
}