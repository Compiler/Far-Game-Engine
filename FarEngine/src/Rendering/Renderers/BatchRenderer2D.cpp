#include "BatchRenderer2D.h"
#include <iostream>
namespace far{



        void far::BatchRenderer2D::init(){
                glGenVertexArrays(1, &_vertexArrayID);
                glBindVertexArray(_vertexArrayID);

                glGenBuffers(1, &_bufferID);
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                glBufferData(GL_ARRAY_BUFFER, FAR_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glEnableVertexAttribArray(2);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*)  0                  );
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*) (3 * sizeof(float)) );
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*) (7 * sizeof(float)) );
        }
        
        void far::BatchRenderer2D::begin(){
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                _buffer = (far::VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
                

        }

        void far::BatchRenderer2D::_setBuffer(VertexData data){
                _buffer->position =     data.position;
                _buffer->color =        data.color;
                _buffer->texCoords =    data.texCoords;

        }

        void far::BatchRenderer2D::submit(std::shared_ptr<far::EntityManager> manager){
                std::vector<Entity> entitiesToSubmit;
                std::vector<std::vector<std::shared_ptr<Component>>> list = std::vector<std::vector<std::shared_ptr<Component>>>();
                
                
                auto ids = manager->getAssociatedEntities<TransformComponent, RenderableComponent>();

                for(int i = 0; i < ids.size(); i++){
                        
                        auto currentTransform = manager->getComponent<TransformComponent>(ids[i]);
                        auto currentRenderable = manager->getComponent<RenderableComponent>(ids[i]);

                        FAR_LOG("Entity#" << ids[i] << ": transform: (" << currentTransform->position.x << ", "  << currentTransform->position.y << ", "  << currentTransform->position.z << ")");
                        FAR_LOG("Entity#" << ids[i] << ": renderable: (" << currentRenderable->color.x << ", "  << currentRenderable->color.y << ", "  << currentRenderable->color.z << ")");
                        



                }       

                //for(auto entityid : manager->getECSMap()) if((entityid.second.find(hash_name("TransformComponent")) != entityid.second.end()) && (entityid.second.find(hash_name("RenderableComponent")) != entityid.second.end() || entityid.second.find(hash_name("TextureComponent")) != entityid.second.end())) entitiesToSubmit.push_back(entityid.first);
                //for(auto entity : entitiesToSubmit) std::cout << "Entity to submit:\t" << entity << std::endl;
        }




        void far::BatchRenderer2D::end(){
                glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        void far::BatchRenderer2D::flush(){
                glBindVertexArray(_vertexArrayID);
                glDrawArrays( GL_TRIANGLES, 0, _amountSubmitted);

        }


}