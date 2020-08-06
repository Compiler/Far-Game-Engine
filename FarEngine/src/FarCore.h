#pragma once
#include <far.h>
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <Rendering/Window.h>
#include <Tools/Files/FileLoaderFactory.h>
#include <Startup/StartupSystems.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <EntityComponentSystem/EntityManager.h>
#include <EntityComponentSystem/Components/Component.h>
#include <EntityComponentSystem/Systems/MeshProcessorSystem.h>
#include <EntityComponentSystem/Systems/MovementSystem.h>
#include <Rendering/Renderers/BatchRenderer2D.h>
#include <Tools/Files/FileLoaderFactory.h>
#include <Tools/Logging/TmpLog.h>

//#include <Audio/ikAudio.h> ///TODO: include audio in makefile and test dll/.exp



namespace far{

    class FarCore{

        private:
            far::Window* _windowRef;
            glm::vec3 thing;

            std::shared_ptr<far::EntityManager> _entityManager;
            far::BatchRenderer2D _batchRenderer;
            far::MeshProcessorSystem _mps;
	        far::MovementSystem _ms;
           // ikAudio* audio;

        public:

            void initForPep(){

                _entityManager = std::make_shared<far::EntityManager>();
                far::Entity entity1 = _entityManager->createEntity();
                far::Entity entity2 = _entityManager->createEntity();
                far::Entity entity3 = _entityManager->createEntity();

                far::TransformComponent trans;
                far::RenderableComponent rend;
                far::MeshComponent mesh;
                
                trans.position = glm::vec3(0.f);
                trans.size = glm::vec3(1.f, 1.f, 1.f);

                mesh.vertices = { glm::vec3(0.0f, 0.5f, 1.f), glm::vec3(0.5f, 0.0f, 1.f), glm::vec3(0.25f, -0.5f, 1.f), glm::vec3(-0.25f, -0.5f, 1.f), glm::vec3(-0.5f, 0.0f, 1.f) };
                rend.color = glm::vec4(0.5f, 0.2f, 0.7f, 1.f);
                _entityManager->addComponent(entity1, mesh);
                _entityManager->addComponent(entity1, rend);
                _entityManager->addComponent(entity1, trans);

                mesh.vertices = { glm::vec3(0.75f, 0.5f, 1.f), glm::vec3(0.75f, 0.75f, 1.f), glm::vec3(0.5f, 0.5f, 1.f), glm::vec3(0.5f, 0.75f, 1.f) };
                rend.color = glm::vec4(1.f, 0.f, 1.f, 1.f);
                _entityManager->addComponent(entity2, mesh);
                _entityManager->addComponent(entity2, rend);
                _entityManager->addComponent(entity2, trans);

                mesh.vertices = { glm::vec3(-0.4f, 0.4f, 1.f), glm::vec3(-0.6f, 0.6f, 1.f), glm::vec3(-0.5f, 0.8f, 1.f), glm::vec3(-0.475f, 0.7f, 1.f), glm::vec3(-0.325f, 0.7f, 1.f), glm::vec3(-0.3f, 0.8f, 1.f), glm::vec3(-0.2f, 0.6f, 1.f) };
                rend.color = glm::vec4(static_cast<float>(83)/85.f, static_cast<float>(7)/17.f, static_cast<float>(14)/255.f, 1.f);
                _entityManager->addComponent(entity3, mesh);                
                _entityManager->addComponent(entity3, rend);                
                _entityManager->addComponent(entity3, trans);                
            }
            void load();
            void update();
            void render();
            void unload();
            const bool isRunning()const{return !glfwWindowShouldClose(_windowRef->getWindow());}

        //tmp
        private:
            unsigned int shaderProgram;
            unsigned int bufferID, arrayID;

            double startFrameTime, deltaTime, lastFrameTime, elapsedTime, frames;

            void init();
            void loadShaders(const char*, const char*);
    };




}