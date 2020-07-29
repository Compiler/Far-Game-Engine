#pragma once
#include <EntityComponentSystem/EntityManager.h>
namespace far{

    class BatchRenderer2D{


        public:
        BatchRenderer2D() = default;
        //Trans ^ (Text v Renderbale)
        void submit(far::EntityManager manager);


    };


}