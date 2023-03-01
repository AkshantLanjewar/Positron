#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

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

        //function that creates a vulkan instance
        void createInstance();

    //private member variables
    private:
        //GLFW's window
        GLFWwindow* window;
        int windowWidth = 1280;
        int windowHeight = 720;

        //vulkan instance
        VkInstance instance;
    };
}