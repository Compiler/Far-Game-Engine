#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Rendering/Window.h>
#include <Files/TextLoader.h>
#include <Startup/StartupSystems.h>

namespace far{

    class FarCore{

        private:
            far::Window* _windowRef;
            

            
        public:

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