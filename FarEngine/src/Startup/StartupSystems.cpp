#include "StartupSystems.h"



namespace far{


    void StartupSystems::_initGLFW(){
        if(!glfwInit()) printf("Failed to init glfw\n");
        else { printf("GLFW initialized.\n"); }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//version 4.6 Core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    }
    void StartupSystems::_initGlad(){
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  printf("Failed to init glad\n");
        else { printf("Glad initialized.\n"); }
	

    }
    void StartupSystems::initSubSystems(){
            _initGLFW();
            _initGlad();

    }

}