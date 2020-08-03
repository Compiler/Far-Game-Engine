#include "BatchRenderer2D.h"
#include <cassert>
#include <vector>
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
                // for(int i = 0; i < FAR_INDEX_BUFFER_SIZE; i++) _ind[i] = i;
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_ind), _ind, GL_STATIC_DRAW);

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
                std::vector<VertexData> vertices;
                std::vector<std::vector<std::shared_ptr<Component>>> list = std::vector<std::vector<std::shared_ptr<Component>>>();
                auto ids = manager->getAssociatedEntities<TransformComponent, RenderableComponent, MeshComponent>();
                for(int i = 0; i < ids.size(); i++){
                        
                        auto currentTransform = manager->getComponent<TransformComponent>(ids[i]);
                        auto currentRenderable = manager->getComponent<RenderableComponent>(ids[i]);
                        auto currentMesh = manager->getComponent<MeshComponent>(ids[i]);

                        for(auto v : currentMesh->vertices){
                                this->_setBuffer(VertexData(v, currentRenderable->color));
                        }
                        // n-2 triangles, 3 indices per triangle
                        unsigned short currentInd = 2;
                        bool prevFlag = false;
                        for(i = 0; i < 3*(currentMesh->vertices.size()-2); i++){
                                if(prevFlag){ // replaced !((i+1)%3); means that modulo doesnt have to be calculated twice
                                        currentInd-=2;
                                        prevFlag = false;
                                }
                                if(!(i%3)){
                                        _ind[i] = 0;
                                        FAR_DEBUG(0);
                                        prevFlag = true;
                                        currentInd++;

                                }
                                else{
                                        _ind[i] = currentInd;
                                        FAR_DEBUG(currentInd);
                                        currentInd++;

                                }
                        };


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
                glDrawElements(GL_TRIANGLES, _amountSubmitted*3, GL_UNSIGNED_SHORT, 0);
                _amountSubmitted = 0;

        }

        far::BatchRenderer2D::~BatchRenderer2D(){ };

}