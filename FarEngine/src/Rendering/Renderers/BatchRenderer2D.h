#pragma once
#include <EntityComponentSystem/EntityManager.h>
#include <EntityComponentSystem/Components/Component.h>
namespace far{

    class BatchRenderer2D{


        public:
        BatchRenderer2D() = default;
        //Trans ^ (Text v Renderbale)
        void submit(std::shared_ptr<far::EntityManager> manager);


    };


}