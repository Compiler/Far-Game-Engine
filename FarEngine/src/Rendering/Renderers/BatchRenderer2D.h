#pragma once
#include <EntityComponentSystem/EntityManager.h>
namespace far{

    class BatchRenderer2D{


        public:
        //Trans ^ (Text v Renderbale)
        void submit(const far::EntityManager& manager);


    };


}