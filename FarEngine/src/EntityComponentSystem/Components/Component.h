#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>


   






namespace far{

    extern uint32_t hash_name(const char* str);
    #define DEFINE_COMPONENT(component_name) \
	struct component_name : public Component { \
		virtual ComponentID getID(){\
            static int hashed = 0;\
            if(!hashed) hashed = hash_name(#component_name);                        \
            return hashed;\
        }\
        const char* name = #component_name;


    typedef uint32_t ComponentID;
   
    struct Component{
        const char* name = "Component";
        virtual ComponentID getID() = 0;
    };

    DEFINE_COMPONENT(TransformComponent)
        glm::vec3 position;
        glm::vec3 size;
    };

    DEFINE_COMPONENT(TextureComponent)    
        const char* fileName;
    };


    DEFINE_COMPONENT(RenderableComponent)    
        glm::vec4 color;
    };

    DEFINE_COMPONENT(MeshComponent)
        unsigned int* indices;
    };

}