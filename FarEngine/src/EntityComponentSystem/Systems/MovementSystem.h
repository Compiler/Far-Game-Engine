// NOT IN MAKE
// NOT INCLUDED ANYWHERE

#pragma once
#include "System.h"
#include <unordered_map>
namespace far{

    class MovementSystem : public System{
    public:
        virtual void update(std::shared_ptr<EntityManager> manager) override{
            std::vector<Entity> ents = manager->getAssociatedEntities<TransformComponent>();
        };
    
        void move(Entity ent, std::shared_ptr<EntityManager> manager, const glm::vec3& movement);
  
    };

}