#pragma once
#include <far.h>
#include <EntityComponentSystem/EntityManager.h>
#include <EntityComponentSystem/Components/Component.h>

namespace far{

    #define MAX_RENDERABLES         65536
    #define FAR_VERTEX_SIZE         sizeof(far::VertexData)
    #define FAR_BUFFER_SIZE         MAX_RENDERABLES * FAR_VERTEX_SIZE
    #define FAR_INDEX_BUFFER_SIZE   3*65536

    struct VertexData{

        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoords;

        VertexData(glm::vec3 p, glm::vec4 c, glm::vec2 tc):position(p), color(c), texCoords(tc){}
        VertexData(){ color = glm::vec4(1.f, 1.f, 1.f, 1.f); texCoords = glm::vec2(1.f, 1.f);};

    };

    class BatchRenderer2D{

        private:

            unsigned int _vertexArrayID, _bufferID, _indexBufferID;
            VertexData* _buffer;
            unsigned int* _indices;
            void _setBuffer(VertexData data);
            void _setBuffer(glm::vec3 pos, glm::vec4 col, glm::vec2 tex);
            uint32_t _amountSubmitted;

        public:
            
            BatchRenderer2D() = default;
            void init();
            void begin();
            void submit(std::shared_ptr<far::EntityManager> manager);
            void end();
            void flush();
            ~BatchRenderer2D();

    };


}