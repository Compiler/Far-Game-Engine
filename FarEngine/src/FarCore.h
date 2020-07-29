#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Rendering/Window.h>
#include <Tools/Files/TextLoader.h>
#include <Startup/StartupSystems.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <EntityComponentSystem/EntityManager.h>
#include <EntityComponentSystem/Components/TransformComponent.h>
#include <EntityComponentSystem/Components/TextureComponent.h>
#include <EntityComponentSystem/Components/Component.h>
#include <Rendering/Renderers/BatchRenderer2D.h>

namespace far{

    class FarCore{

        private:
            far::Window* _windowRef;
            glm::vec3 thing;

            std::unique_ptr<far::EntityManager> _entityManager;
            far::BatchRenderer2D _batchRenderer;

        public:

            void initForPep(){

                _batchRenderer = far::BatchRenderer2D();
                _entityManager = std::make_unique<far::EntityManager>();
                far::Entity entity1 = _entityManager->createEntity();
                std::cout << entity1 << std::endl;
                std::shared_ptr<far::TransformComponent> trans = std::make_shared<TransformComponent>();
                std::shared_ptr<far::TextureComponent> tex = std::make_shared<TextureComponent>();
                tex->fileName = "SomeTexture.png";
                trans->position = glm::vec3(2,4,5);
                _entityManager->addComponent(entity1, trans, tex);
                std::shared_ptr<far::TransformComponent> type = _entityManager->getComponent<TransformComponent>(entity1);
                std::shared_ptr<far::TextureComponent> texRet = _entityManager->getComponent<TextureComponent>(entity1);
                std::cout << type->position.x << "\n";
                std::cout << texRet->fileName << "\n";
                _batchRenderer.submit(*_entityManager);

            }

            void load();
            void update();
            void render();
            void unload();
            const bool isRunning()const{return !glfwWindowShouldClose(_windowRef->getWindow());}

        //tmp
        private:
            uint16_t shaderProgram, arrayID;
            double startFrameTime, deltaTime, lastFrameTime, elapsedTime, frames;

            void init();
            void loadShaders(const char*, const char*);
    };




}