#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
namespace far{


    class StartupSystems{

        private:
            void _initGLFW();
            void _initGlad();
        public:

        void initSubSystems();


    };


}