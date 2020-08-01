#include "BatchRenderer2D.h"
#include <cassert>
namespace far{



        void far::BatchRenderer2D::init(){
                FAR_LOG("BatchRenderer init()");
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

                glBindVertexArray(0);
                assert(FAR_BUFFER_SIZE % 9 == 0);

        }
        
        void far::BatchRenderer2D::begin(){
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                _buffer = (far::VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        }

        void far::BatchRenderer2D::_setBuffer(VertexData data){
                _buffer->position =     data.position;
                _buffer->color =        data.color;
                _buffer->texCoords =    data.texCoords;
                _buffer++;
        }
        void far::BatchRenderer2D::_setBuffer(glm::vec3 pos, glm::vec4 col, glm::vec2 tex){
                _buffer->position =     pos;
                _buffer->color =        col;
                _buffer->texCoords =    tex;
                _buffer++;
        }


        void far::BatchRenderer2D::submit(std::shared_ptr<far::EntityManager> manager){
                std::vector<Entity> entitiesToSubmit;
                std::vector<std::vector<std::shared_ptr<Component>>> list = std::vector<std::vector<std::shared_ptr<Component>>>();
                
                
                auto ids = manager->getAssociatedEntities<TransformComponent, RenderableComponent>();

                for(int i = 0; i < ids.size(); i++){
                        
                        auto currentTransform = manager->getComponent<TransformComponent>(ids[i]);
                        auto currentRenderable = manager->getComponent<RenderableComponent>(ids[i]);

                        FAR_LOG("Entity#" << ids[i] << ": transform->position:   (" << currentTransform->position.x << ", "  << currentTransform->position.y << ", "  << currentTransform->position.z << ")");
                        FAR_LOG("Entity#" << ids[i] << ":     transform->size:   (" << currentTransform->size.x << ", "  << currentTransform->size.y << ", "  << currentTransform->size.z << ")");
                        FAR_LOG("Entity#" << ids[i] << ":   renderable->color:   (" << currentRenderable->color.x << ", "  << currentRenderable->color.y << ", "  << currentRenderable->color.z << ")");

                        this->_setBuffer(currentTransform->position, currentRenderable->color, glm::vec2(0.f, 0.f));
                        this->_setBuffer(glm::vec3(currentTransform->position.x + currentTransform->size.x, currentTransform->position.y, currentTransform->position.z), currentRenderable->color, glm::vec2(0.f, 0.f));
                        this->_setBuffer(glm::vec3(currentTransform->position.x, currentTransform->position.y+currentTransform->size.y, currentTransform->position.z), currentRenderable->color, glm::vec2(0.f, 0.f));

                        _amountSubmitted++;

                        FAR_LOG("Amount submitted: " << _amountSubmitted);
                
                }

        }




        void far::BatchRenderer2D::end(){
                glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        void far::BatchRenderer2D::flush(){
                glBindVertexArray(_vertexArrayID);
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                glDrawArrays(GL_TRIANGLES, 0, _amountSubmitted*3);
                _amountSubmitted = 0;
        }


}