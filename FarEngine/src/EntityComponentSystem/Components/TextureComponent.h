#pragma once
#include <EntityComponentSystem/Components/Component.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace far{

    DEFINE_COMPONENT(TextureComponent)    

        const char* fileName;

    };


    DEFINE_COMPONENT(RenderableComponent)    

        glm::vec4 color;

    };


}



