#include "BatchRenderer2D.h"
#include <iostream>
namespace far{


        void far::BatchRenderer2D::submit(far::EntityManager manager){
                std::vector<Entity> entitiesToSubmit;
                for(auto entityid : manager.getECSMap()) if((entityid.second.find(hash_name("TransformComponent")) != entityid.second.end()) && (entityid.second.find(hash_name("RenderableComponent")) != entityid.second.end() || entityid.second.find(hash_name("TextureComponent")) != entityid.second.end())) entitiesToSubmit.push_back(entityid.first);
                for(auto entity : entitiesToSubmit) std::cout << entity << std::endl;
        }



}