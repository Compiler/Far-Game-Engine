// NOT IN MAKE
// NOT INCLUDED ANYWHERE

#include "MovementSystem.h"

namespace far{
    void MovementSystem::move(Entity ent, std::shared_ptr<EntityManager> manager, const glm::vec3& movement){
        manager->getComponent<TransformComponent>(ent)->position += movement;
    };
}