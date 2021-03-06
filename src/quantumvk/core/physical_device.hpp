#pragma once

#include "../base/vk.hpp"
#include "instance.hpp"

#include <string>

namespace vkq
{
    /**
     * @brief class representing a GPU (or "PhysicalDevice" in vulkan), 
     * and exposing the GPU's various features and properties
     */
    class PhysicalDevice
    {
    public:
        PhysicalDevice() = default;
        ~PhysicalDevice() = default;

    public:
        static PhysicalDevice create(const Instance& instance, vk::PhysicalDevice phdev);

        void reset();

        vk::PhysicalDeviceProperties getProperties();
        vk::PhysicalDeviceFeatures getFeatures();
        std::vector<vk::QueueFamilyProperties> getQueueFamilyProperties();
        std::vector<vk::ExtensionProperties> enumerateDeviceExtensionProperties(vk::Optional<const std::string> layerName = nullptr);

#ifdef VK_VERSION_1_1
        void getFeatures2(vk::PhysicalDeviceFeatures2* features);
#endif 

#ifdef VK_KHR_SURFACE_EXTENSION_NAME

        std::vector<vk::SurfaceFormatKHR> getSurfaceFormatsKHR(vk::SurfaceKHR surface);

        vk::SurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR(vk::SurfaceKHR surface);

        std::vector<vk::PresentModeKHR> getSurfacePresentModes(vk::SurfaceKHR surface);
#endif


        Instance instance() const
        {
            return instance_;
        }

        vk::DispatchLoaderDynamic dispatch() const
        {
            return instance_.dispatch();
        }

        vk::PhysicalDevice vkPhysicalDevice() const
        {
            return phdev_;
        }

        vk::PhysicalDevice vkHandle() const
        {
            return phdev_;
        }

        operator vk::PhysicalDevice() const
        {
            return phdev_;
        }

    private:
        explicit PhysicalDevice(Instance instance, vk::PhysicalDevice phdev);

        Instance instance_;
        vk::PhysicalDevice phdev_;
    };

} // namespace vkq