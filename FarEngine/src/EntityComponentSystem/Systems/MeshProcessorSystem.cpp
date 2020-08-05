#include "MeshProcessorSystem.h"

namespace far{

    void MeshProcessorSystem::_sortVertices(Entity ent, std::shared_ptr<far::EntityManager> manager) const{
            glm::vec3 center = glm::vec3(0.f, 0.f, 0.f);
            std::shared_ptr<MeshComponent> meshEnts = manager->getComponent<MeshComponent>(ent);
            for(auto vertex : meshEnts->vertices) center += vertex;
            center /= meshEnts->vertices.size();
            center.z = 1.f;
            for(auto& vertex : meshEnts->vertices){
                vertex -= center;
                vertex.z = 1.f;
            }
            std::sort(meshEnts->vertices.begin(), meshEnts->vertices.end(), [](glm::vec3 a, glm::vec3 b) {return std::atan2(a.x, a.y) > std::atan2(b.x, b.y);});
            for(auto& vertex : meshEnts->vertices){
                vertex += center;
                vertex.z = 1.f;
            }
        }
}