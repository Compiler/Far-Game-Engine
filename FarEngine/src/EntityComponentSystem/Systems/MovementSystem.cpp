#include "MovementSystem.h"

namespace far{
    void MovementSystem::move(Entity ent, const glm::vec3& movement){
        this->_movementQueue[_manager->getComponent<TransformComponent>(ent)] = movement;
    };
    MovementSystem::MovementSystem(far::EntityManager& manager) : _movementQueue(std::unordered_map<std::shared_ptr<TransformComponent>, glm::vec2>()), System(manager) {};
}