#pragma once
#include "System.h"
#include <algorithm>
namespace far{

    class MeshProcessorSystem : public System{
    public:

        virtual void update(std::shared_ptr<far::EntityManager> manager) override{
            std::vector<Entity> meshEntities = manager->getAssociatedEntities<MeshComponent>();
            for(auto entity : meshEntities){
                this->_sortVertices(entity, manager);
            }
        }
    
    private:
        void _sortVertices(Entity ent, std::shared_ptr<far::EntityManager> manager);
    };

}