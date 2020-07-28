#pragma once
#include <stdint.h>

namespace far{
    typedef uint32_t ComponentID;

    struct Component{

        virtual ComponentID getID();



    };

}