#pragma once
#include "EntityComponentSystem/EntityManager.h"

namespace far{
    class System{
    protected:
        std::shared_ptr<far::EntityManager> _manager;
    public:
        System(far::EntityManager& manager) : _manager(&manager){};
        System() = default;
        virtual void update(float deltaTime) = 0;
        
    };
}