#pragma once 
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <EntityComponentSystem/Components/Component.h>

namespace far{
    typedef uint64_t Entity;
    class EntityManager{
        private:
            std::vector<Entity> _entities;
            std::vector<ComponentID> _componentIDs;
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> _ecsMap;


    };

}