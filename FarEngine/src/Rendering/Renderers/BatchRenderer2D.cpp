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

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*)  0                  ); // POSITION
                glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*) (3 * sizeof(float)) ); // COLOUR
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, FAR_VERTEX_SIZE, (const void*) (7 * sizeof(float)) ); // TEXTURE COORDINATES
                
                
                glGenBuffers(1, &_indexBufferID);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, FAR_INDEX_BUFFER_SIZE, this->_indices, GL_DYNAMIC_DRAW);

                glBindVertexArray(0);
                assert(FAR_BUFFER_SIZE % 9 == 0);

        }
        
        void far::BatchRenderer2D::begin(){

                FAR_LOG("BatchRenderer begin()");
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                _buffer = (far::VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        }

        void far::BatchRenderer2D::_setBuffer(VertexData data){

                _buffer->position  =    data.position;
                _buffer->color     =    data.color;
                _buffer->texCoords =    data.texCoords;
                _buffer++;
        
        }
        
        void far::BatchRenderer2D::_setBuffer(glm::vec3 pos, glm::vec4 col, glm::vec2 tex){
        
                _buffer->position  =    pos;
                _buffer->color     =    col;
                _buffer->texCoords =    tex;
                _buffer++;
        
        }

        void far::BatchRenderer2D::submit(std::shared_ptr<far::EntityManager> manager){
        
                std::vector<Entity> entitiesToSubmit;
                std::vector<std::vector<std::shared_ptr<Component>>> list = std::vector<std::vector<std::shared_ptr<Component>>>();
                auto ids = manager->getAssociatedEntities<TransformComponent, RenderableComponent>();
                _indices = new unsigned int[ids.size()*3];
                for(int i = 0; i < ids.size(); i++){
                        
                        auto currentTransform = manager->getComponent<TransformComponent>(ids[i]);
                        auto currentRenderable = manager->getComponent<RenderableComponent>(ids[i]);
                        auto currentIndexArray = manager->getComponent<MeshComponent>(ids[i]);

                        FAR_LOG("Entity#" << ids[i] << ": transform->position:   (" << currentTransform->position.x << ", "  << currentTransform->position.y << ", "  << currentTransform->position.z << ")");
                        FAR_LOG("Entity#" << ids[i] << ":     transform->size:   (" << currentTransform->size.x << ", "  << currentTransform->size.y << ", "  << currentTransform->size.z << ")");
                        FAR_LOG("Entity#" << ids[i] << ":   renderable->color:   (" << currentRenderable->color.x << ", "  << currentRenderable->color.y << ", "  << currentRenderable->color.z << ")");

                        VertexData datum1, datum2, datum3;

                        datum1.color = currentRenderable->color;
                        datum1.position = currentTransform->position;
                        
                        datum2.color = currentRenderable->color;
                        datum2.position = currentTransform->position;
                        datum2.position.x = datum2.position.x + currentTransform->size.x;
                        
                        datum3.color = currentRenderable->color;
                        datum3.position = currentTransform->position;
                        datum3.position.y = datum3.position.y + currentTransform->size.y;

                        this->_setBuffer(datum1);
                        _indices[_amountSubmitted*3] = _amountSubmitted*3;
                        FAR_DEBUG("Index:Vertex - " << _amountSubmitted*3 << ":(" << datum1.position.x << ", " << datum1.position.y << ", " << datum1.position.z << ")");

                        this->_setBuffer(datum2);
                        _indices[_amountSubmitted*3+1] = _amountSubmitted*3+1;
                        FAR_DEBUG("Index:Vertex - " << _amountSubmitted*3+1 << ":(" << datum2.position.x << ", " << datum2.position.y << ", " << datum2.position.z << ")");
                        
                        this->_setBuffer(datum3);
                        _indices[_amountSubmitted*3+2] = _amountSubmitted*3+2;
                        FAR_DEBUG("Index:Vertex - " << _amountSubmitted*3+2 << ":(" << datum3.position.x << ", " << datum3.position.y << ", " << datum3.position.z << ")");
                        
                        _amountSubmitted++;


                }


                

        }

        void far::BatchRenderer2D::end(){
        
                glUnmapBuffer(GL_ARRAY_BUFFER);
        
        }

        void far::BatchRenderer2D::flush(){
                
                glBindVertexArray(_vertexArrayID);
                glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
                FAR_DEBUG("Final amount submitted: " << _amountSubmitted);
                glDrawElements(GL_TRIANGLES, 3, _amountSubmitted*3, 0);
                _amountSubmitted = 0;
//              delete [] _indices;
        
        }

        far::BatchRenderer2D::~BatchRenderer2D(){ delete [] _indices; };

}