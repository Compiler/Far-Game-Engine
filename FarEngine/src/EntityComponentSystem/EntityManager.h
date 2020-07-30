#pragma once 
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <EntityComponentSystem/Components/Component.h>
#include <iostream>
#include <Tools/Logging/TmpLog.h>
namespace far{
    typedef uint64_t Entity;
    class EntityManager{
        private:

            std::unordered_map<uint64_t, const char*> __dbg_compIDToName;
        private:
            static uint64_t _ENTITY_COUNT;
            std::vector<Entity> _entities;
            std::unordered_map<ComponentID, std::vector<std::shared_ptr<Component>>> _components;
            std::vector<ComponentID> _componentIDs;
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> _ecsMap;


        public:

            Entity createEntity(){
                Entity entity = _ENTITY_COUNT++;
                FAR_DEBUG("Entity #" << entity << " created!");
                _ecsMap[entity] = std::unordered_map<ComponentID, std::shared_ptr<Component>>();
                _entities.push_back(entity);
                return entity;
            }
            
            std::unordered_map<Entity, std::unordered_map<ComponentID, std::shared_ptr<Component>>> getECSMap(){return _ecsMap;};

            template <typename CompType>
            void addComponent(Entity ent, std::shared_ptr<CompType> comp){
                auto id = comp->getID();
               auto name = CompType().name;
               FAR_LOG("'addComponent<type>'\n\tCompType id: \t" << CompType().name << " added to entity #" << ent);
                _ecsMap[ent][id] = comp;
                if(_components.find(id) == _components.end() ){
                    _components[id].push_back(comp);
                }//else _components[id] = st/d::vector<std::shared_ptr<Component>>();

            }

            template <typename CompType, typename... Types>
            void addComponent(Entity ent, std::shared_ptr<CompType> comp, std::shared_ptr<Types> ... types){
                auto id = comp->getID();
                 FAR_LOG("'addComponent<type>'\n\tCompType id: \t" << CompType().name << " added to entity #" << ent);
                _ecsMap[ent][id] = comp;
                if(_components.find(id) == _components.end() ){
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
                std::vector<std::shared_ptr<CompType>> finalList;
                FAR_LOG("'getComponentsList'\n\tCompType id: \t" << CompType().name);
                auto baseList = _components[CompType().getID()];
                std::cout << "\tBase list size: " << baseList.size() << "\n";
                
                for(auto i : baseList){
                    finalList.push_back(std::dynamic_pointer_cast<CompType>(i));
                }
                return finalList;
            }


            // template <typename CompType>
            // std::vector<std::shared_ptr<CompType>> getComponents2DList(){
            //     auto list = getComponentsList<CompType>();
            // }
            // template <typename CompType1, typename CompType2>
            // void getComponents2DList(std::vector<std::vector<std::shared_ptr<Component>>>& list, int placement = 0){
            //     //list[placement++].push_back(getComponentsList<CompType1>());
            //     //list[placement++].push_back(getComponentsList<CompType2>());
            // }


    };

}