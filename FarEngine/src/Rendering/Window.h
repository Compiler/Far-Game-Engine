#pragma once
#include <glfw/glfw3.h>
#include <glad/glad.h>
#include <string>

namespace far{

    class Window{


        private:
            std::string _windowName;
            GLFWwindow* _window;
        public:
            static float SCREEN_WIDTH;
            static float SCREEN_HEIGHT;

            Window(float width, float height, const char name[], bool fullscreen = false);
    

    };


}