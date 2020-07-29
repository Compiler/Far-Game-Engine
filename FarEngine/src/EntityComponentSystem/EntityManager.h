#pragma once 
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <EntityComponentSystem/Components/Component.h>
#include <iostream>
namespace far{
    typedef uint64_t Entity;
    class EntityManager{
        private:
            static uint64_t _ENTITY_COUNT;
            std::vector<Entity> _entities;
            std::unordered_map<ComponentID, std::vector<std::shared_ptr<Component>>> _components;
            std::vector<ComponentID> _componentIDs;
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> _ecsMap;


        public:

            Entity createEntity(){
                Entity entity = _ENTITY_COUNT++;
                std::cout << "Entity #" << entity << " created!\n";
                _ecsMap[entity] = std::unordered_map<ComponentID, std::shared_ptr<Component>>();
                _entities.push_back(entity);
                return entity;
            }
            
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> getECSMap(){return _ecsMap;};

            template <typename CompType>
            void addComponent(Entity ent, std::shared_ptr<CompType> comp){
                auto id = comp->getID();
                _ecsMap[ent][id] = comp;
                if(_components.find(id) != _components.end() ){
                    _components[id].push_back(comp);
                }//else _components[id] = st/d::vector<std::shared_ptr<Component>>();

            }

            template <typename CompType, typename... Types>
            void addComponent(Entity ent, std::shared_ptr<CompType> comp, std::shared_ptr<Types> ... types){
                auto id = comp->getID();
                _ecsMap[ent][id] = comp;
                if(_components.find(id) != _components.end() ){
                    _components[id].push_back(comp);
                }//else _components[id] = std::vector<std::shared_ptr<Component>>();

                addComponent(ent, types...);
            }

            template <typename CompType>
            std::shared_ptr<CompType> getComponent(Entity ent){
				return std::dynamic_pointer_cast<CompType>(_ecsMap[ent][CompType().getID()]);
            }

            template <typename CompType>
            std::vector<std::shared_ptr<CompType>> getComponentsList(){
                return _components[CompType().getID()];
            }

    };

}