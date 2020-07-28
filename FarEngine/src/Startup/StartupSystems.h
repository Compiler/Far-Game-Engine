#pragma once
#include <glad/glad.h>
namespace far{


    class StartupSystems{

        public:

        void initGLFW(){

            if(!glfwInit()) printf("Failed to init glfw");
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//version 4.6 Core profile
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        }


    };


}