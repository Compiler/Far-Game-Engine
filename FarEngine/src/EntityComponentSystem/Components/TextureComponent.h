#pragma once
#include <EntityComponentSystem/Components/Component.h>
#include <glm/vec3.hpp>

namespace far{

struct TextureComponent : public Component{
    
    ComponentID getID()override{return 2;}

    const char* fileName;

};


}



