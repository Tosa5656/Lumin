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