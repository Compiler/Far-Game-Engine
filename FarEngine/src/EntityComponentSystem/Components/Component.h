#pragma once
#include <stdint.h>

namespace far{

    static uint32_t hash_name(const char* str){
        unsigned long hash = 5381;
        int c;

        while((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }
    #define DEFINE_COMPONENT(component_name) \
	struct component_name : public Component { \
		virtual uint32_t getID(){return hash_name(#component_name);}\
        const char* name = #component_name;


    typedef uint32_t ComponentID;
   
    struct Component{
        const char* name = "Component";
        virtual ComponentID getID() = 0;



    };

}