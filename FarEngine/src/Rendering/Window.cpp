#include <src/Rendering/Window.h>


namespace far{

    float far::Window::SCREEN_WIDTH;
    float far::Window::SCREEN_HEIGHT;
    Window::Window(float width, float height, const char name[], bool fullscreen = false){
        Window::SCREEN_HEIGHT = height; Window::SCREEN_WIDTH = width; _windowName = name;
        _window = glfwCreateWindow(width, height, name, NULL, NULL);
    }


}