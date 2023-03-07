#include "../../include/positron_graphics/positron_graphics.h"

namespace PositronGraphics
{
    void PositronGraphics::pickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if(deviceCount == 0)
            throw new std::runtime_error("Failed to find GPU with Vulkan Support");

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::multimap<int, VkPhysicalDevice> candidates;
        for(const auto& device : devices)
        {
            if(isDeviceSuitable(device))
            {
                int deviceScore = rateDeviceSuitability(device);
                candidates.insert(std::make_pair(deviceScore, device));
            }
        }

        if(candidates.rbegin()->first > 0)
            physicalDevice = candidates.rbegin()->second;
        else
            throw std::runtime_error("Failed to find GPU");
    }

    bool PositronGraphics::isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);
        return indices.isComplete();
    }

    int PositronGraphics::rateDeviceSuitability(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        int score = 0;
        if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            score += 1000;

        //texture handling capabilities
        score += deviceProperties.limits.maxImageDimension2D;

        //relies on geometry shaders
        if(!deviceFeatures.geometryShader)
            score = 0;

        return score;
    }

    QueueFamilyIndices PositronGraphics::findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int graphicsIndex = 0;
        for(const auto& queueFamily : queueFamilies)
        {
            if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.graphicsFamily = graphicsIndex;
            if(indices.isComplete())
                break;

            graphicsIndex++;
        }

        return indices;
    }
}