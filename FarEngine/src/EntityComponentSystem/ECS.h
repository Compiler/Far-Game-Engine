#pragma once
#include <Tools/Logging/TmpLog.h>
#include <unordered_map>
#include <EntityComponentSystem/Components/Component.h>


namespace far{

    typedef uint64_t Entity;


    class ECS{

        private:
            std::unordered_map<ComponentID, std::vector<Entity>> _compToEnt;
            std::vector<Entity> _entities;
            static uint64_t _ENTITY_COUNT;

            std::vector<std::vector<std::shared_ptr<Component>>> _compMat;


        public:



            Entity createEntity(){
                Entity entity = _ENTITY_COUNT++;
                FAR_DEBUG("Entity #" << entity << " created!");
                _entities.push_back(entity);
                return entity;
            }
            template<typename CompType>
            void registerComponent(Entity id){
                _compToEnt[CompType().getID()] = std::push_back(id);
                _compMat[CompType().getID()]
            }


            template <typename CompType> 
            std::vector<Entity> getAssociatedEntities(){ return _compToEnt[CompType().getID()];}





    };


}