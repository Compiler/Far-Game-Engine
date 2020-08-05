#pragma once
#include "EntityComponentSystem/EntityManager.h"

namespace far{
    class System{
    public:
        virtual void update(std::shared_ptr<far::EntityManager>) = 0;
        
    };
}