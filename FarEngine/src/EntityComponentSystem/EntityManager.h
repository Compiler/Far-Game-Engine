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
            static uint64_t _ENTITY_COUNT;
            std::vector<Entity> _entities;
            std::vector<ComponentID> _componentIDs;
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> _ecsMap;


        public:

            Entity createEntity(){
                Entity entity = _ENTITY_COUNT++;
                _ecsMap[entity] = std::unordered_map<ComponentID, std::shared_ptr<Component>>();
                _entities.push_back(entity);

            }

            template <typename CompType>
            void addComponent(Entity ent, std::shared_ptr<CompType> comp){
                _ecsMap[ent][comp->getID()] = comp;
            }


            template <typename CompType>
            std::shared_ptr<CompType> getComponent(Entity ent){
                CompType comp;
				return std::dynamic_pointer_cast<CompType>(_ecsMap[ent][comp.getID()]);
            }

    };

}