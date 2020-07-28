#pragma once
#include <stdint.h>

namespace far{


#define DEFINE_COMPONENT(component_name) \
	struct component_name : public Component { \
		virtual uint32_t getID(){return hash_name(#component_name);}\
        const char* name = #component_name;


    typedef uint32_t ComponentID;
   
    struct Component{
        std::string name = "Component";
        virtual ComponentID getID() = 0;



    };

}