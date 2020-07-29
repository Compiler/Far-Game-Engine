#pragma once
#include <EntityComponentSystem/Components/Component.h>
#include <glm/vec3.hpp>

namespace far{


    DEFINE_COMPONENT(TransformComponent)

        glm::vec3 position;
        glm::vec3 size;

    };

}