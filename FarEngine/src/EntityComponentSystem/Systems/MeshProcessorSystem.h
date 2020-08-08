#pragma once
#include "System.h"
#include <algorithm>
namespace far{

    class MeshProcessorSystem : public System{
    public:
        MeshProcessorSystem(std::shared_ptr<far::EntityManager> manager) : System(manager){};
        MeshProcessorSystem() = default;
        virtual void update(float deltaTime) override{
            std::vector<Entity> meshEntities = _manager->getAssociatedEntities<MeshComponent>();
            for(auto entity : meshEntities) this->_sortVertices(entity);
        }
    
    private:
        void _sortVertices(Entity ent);
    };

}