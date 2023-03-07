#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <optional>

namespace PositronGraphics
{
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };

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

    //initial member methods
    private:
        //function that initializes vulkan within the graphics object
        void init();

        //function that cleans up memory on death
        void clean();

        //function that creates a vulkan instance
        void createInstance();

        //checks if validation layers are available
        bool checkValidationLayerSupport();

        //get required extensions for instance
        std::vector<const char*> getRequiredExtensions();

    //debug member methods
    private:
        //sets up debug messenger
        void setupDebugMessenger();

        //create debug vulkan function
        VkResult CreateDebugUtilsMessengerEXT(
            VkInstance instance, 
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger
        );

        //destroy debug vulkan function
        void DestroyDebugUtilsMessengerEXT(
            VkInstance instance, 
            VkDebugUtilsMessengerEXT debugMessenger, 
            const VkAllocationCallbacks* pAllocator
        );

        //this populates the debug create info
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    //device member methods
    private:
        //picks the vk physical device
        void pickPhysicalDevice();

        //checks if the device is suitable
        bool isDeviceSuitable(VkPhysicalDevice device);

        //gives a vulkan device a score based on its aspects
        int rateDeviceSuitability(VkPhysicalDevice device);

        //finds que families for device
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    //private member variables
    private:
        //GLFW's window
        GLFWwindow* window;
        int windowWidth = 1280;
        int windowHeight = 720;

        //vulkan instance
        VkInstance instance;
        //debug messenger
        VkDebugUtilsMessengerEXT debugMessenger;
        //this is vulkans physical device
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif
    };
}