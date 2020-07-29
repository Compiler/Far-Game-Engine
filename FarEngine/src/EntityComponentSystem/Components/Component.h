#pragma once
#include <stdint.h>

namespace far{

    extern uint32_t hash_name(const char* str);
    #define DEFINE_COMPONENT(component_name) \
	struct component_name : public Component { \
		virtual ComponentID getID(){return hash_name(#component_name);}\
        const char* name = #component_name;


    typedef uint32_t ComponentID;
   
    struct Component{
        const char* name = "Component";
        virtual ComponentID getID() = 0;
    };

}