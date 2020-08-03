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
	        
           // ikAudio* audio;

        public:

            void initForPep(){

                _entityManager = std::make_shared<far::EntityManager>();
                far::Entity entity1 = _entityManager->createEntity();
                far::Entity entity2 = _entityManager->createEntity();
                far::Entity entity3 = _entityManager->createEntity();
                
                // far::TransformComponent trans;
                // std::shared_ptr<far::TextureComponent> tex = std::make_shared<TextureComponent>();
                // far::RenderableComponent rend;
                // tex->fileName = "SomeTexture.png";
                // _entityManager->addComponent(entity1, tex);
                // _entityManager->addComponent(entity1, trans);


                // trans.position = glm::vec3(-0.75f,-0.5f,1);
                // trans.size = glm::vec3(0.25f,0.25f,0.25f);
                // rend.color = glm::vec4(0,0,1,1);
                // _entityManager->addComponent(entity2, rend);
                // _entityManager->addComponent(entity2, trans);
                // trans.position = glm::vec3(0.45f,0.5f,1);
                // trans.size = glm::vec3(0.15f,0.35f,0.25f);
                // rend.color = glm::vec4(0,1,0,1);
                // _entityManager->addComponent(entity3, rend);
                // _entityManager->addComponent(entity3, tex);
                // _entityManager->addComponent(entity3, trans);

                far::TransformComponent trans;
                far::RenderableComponent rend;
                far::MeshComponent mesh;
                far::RenderableComponent rend2;
                far::MeshComponent mesh2;
                mesh.vertices = { glm::vec3(0.0f, 0.5f, 1.f), glm::vec3(0.5f, 0.0f, 1.f), glm::vec3(0.25f, -0.5f, 1.f), glm::vec3(-0.25f, -0.5f, 1.f), glm::vec3(-0.5f, 0.0f, 1.f) };
                rend.color = glm::vec4(0.5f, 0.2f, 0.7f, 1.0f);
                _entityManager->addComponent(entity1, mesh);
                _entityManager->addComponent(entity1, rend);
                _entityManager->addComponent(entity1, trans);
                mesh2.vertices = { glm::vec3(0.75f, 0.75f, 1.f), glm::vec3(0.75f, 0.5f, 1.f), glm::vec3(0.5f, 0.5f, 1.f), glm::vec3(0.75f, 0.5f, 1.f) };
                rend2.color = glm::vec4(1.0f, 0.f, 1.0f, 1.0f);
                _entityManager->addComponent(entity2, mesh2);
                _entityManager->addComponent(entity2, rend2);
                _entityManager->addComponent(entity2, trans);


                
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