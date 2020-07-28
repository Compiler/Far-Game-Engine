#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
namespace far{
    //static class
    class StartupSystems{
        public:
            static void _initGLFW();
            static void _initGlad();
            StartupSystems() = delete;
            StartupSystems operator=(const StartupSystems&) = delete;
            static void initSubSystems();
    };
}