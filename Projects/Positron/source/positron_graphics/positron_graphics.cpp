#include "../../include/positron_graphics/positron_graphics.h"

namespace PositronGraphics
{
    PositronGraphics::PositronGraphics()
    {
        init();
    }

    PositronGraphics::~PositronGraphics()
    {

    }

    void PositronGraphics::Run()
    {
        while(!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }

        clean();
    }

    void PositronGraphics::init()
    {   
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(windowWidth, windowHeight, "Positron", nullptr, nullptr);
    }

    void PositronGraphics::clean()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}