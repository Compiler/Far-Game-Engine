#include "BatchRenderer2D.h"
#include <iostream>
namespace far{


        void far::BatchRenderer2D::submit(std::shared_ptr<far::EntityManager> manager){
                std::vector<Entity> entitiesToSubmit;
                std::vector<std::vector<std::shared_ptr<Component>>> list = std::vector<std::vector<std::shared_ptr<Component>>>();
                //manager.getComponents2DList<far::TransformComponent/*, far::RenderableComponent*/>(list);
                //auto renderList = manager.getComponentsList<RenderableComponent>();
                std::vector<std::shared_ptr<far::TransformComponent>> transList = manager->getComponentsList<TransformComponent>();
                std::vector<std::shared_ptr<far::RenderableComponent>> renderList = manager->getComponentsList<RenderableComponent>();
                
                int count = 0;
                for(const auto& i : transList  ) 
                       FAR_DEBUG("Transform #" << count++ << ":\t(" << i->position.x << ", "<< i->position.y << ", "<< i->position.z << ")");
                
                count = 0;
                for(const auto& i : renderList ) 
                        FAR_DEBUG("Renderable #" << count++ << ":\t(" << i->color.x << ", "<< i->color.y << ", "<< i->color.z << ")");

                //for(auto entityid : manager->getECSMap()) if((entityid.second.find(hash_name("TransformComponent")) != entityid.second.end()) && (entityid.second.find(hash_name("RenderableComponent")) != entityid.second.end() || entityid.second.find(hash_name("TextureComponent")) != entityid.second.end())) entitiesToSubmit.push_back(entityid.first);
                //for(auto entity : entitiesToSubmit) std::cout << "Entity to submit:\t" << entity << std::endl;
        }



}