#pragma once
#include "System.h"
#include <unordered_map>
#include <glm\vec2.hpp>
#include <memory>
namespace far{

    class MovementSystem : public System{
    private:
        std::unordered_map<std::shared_ptr<TransformComponent>, glm::vec2> _movementQueue;
    public:
        MovementSystem(far::EntityManager& manager);
        virtual void update(float deltaTime) override{
            for(auto it = _movementQueue.begin(); it != _movementQueue.end(); it++) (it->first)->position += deltaTime*glm::vec3((it->second), 0.f);
            _movementQueue.clear();
        };
    
        void move(Entity ent, const glm::vec3& movement);
  
    };

}