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

            template<typename T>
			void attachComponent(Entity entity, std::shared_ptr<T> component){
            }
            void addComponent(Entity ent, std::shared_ptr<Component> comp){
                _ecsMap[ent][comp->getID()] = comp;
            }

            std::shared_ptr<Component> getComponent(Entity ent, ComponentID comp){
                    return _ecsMap[ent][comp];
            }

    };

}