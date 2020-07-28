#pragma once
#include <EntityComponentSystem/Components/Component.h>
#include <glm/vec3.hpp>

namespace far{


struct TransformComponent : public Component{

    ComponentID getID()override{return 1;}

    glm::vec3 position;

};

}