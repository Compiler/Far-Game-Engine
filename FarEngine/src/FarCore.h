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
#include <EntityComponentSystem/Components/Component.h>

namespace far{

    class FarCore{

        private:
            far::Window* _windowRef;
            glm::vec3 thing;

            std::unique_ptr<EntityManager> _entityManager;
            
        public:

            void initForPep(){
                _entityManager = std::make_unique<EntityManager>();
                far::Entity entity1 = _entityManager->createEntity();
                std::shared_ptr<far::TransformComponent> trans = std::make_shared<TransformComponent>();
                trans->position = glm::vec3(2,4,5);
                _entityManager->addComponent(entity1, trans);
                std::shared_ptr<far::TransformComponent> type = _entityManager->getComponent<TransformComponent>(entity1);

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