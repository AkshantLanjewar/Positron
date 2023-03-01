#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace PositronGraphics
{
    class PositronGraphics 
    {
    public:
        /*
        *   This is the initializer for the graphics class
        *   Runs any initalizer functions to set up graphics
        */
        PositronGraphics();

        /*
        *   Default deconstructor
        */
        ~PositronGraphics();

        /*
        *   This runs the event loop for the engine
        */
        void Run();

    private:
        //function that initializes vulkan within the graphics object
        void init();

        //function that cleans up memory on death
        void clean();

    //private member variables
    private:
        GLFWwindow* window;
        int windowWidth = 1280;
        int windowHeight = 720;
    };
}