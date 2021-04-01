#include "physical_device.hpp"

namespace vkq
{
    PhysicalDevice::PhysicalDevice(Instance instance_, vk::PhysicalDevice phdev_)
        : instance_(instance_), phdev_(phdev_)
    {
    }

    PhysicalDevice PhysicalDevice::create(const Instance& instance, vk::PhysicalDevice phdev)
    {
        return PhysicalDevice{instance, phdev};
    }

    void PhysicalDevice::reset()
    {
        instance_ = {};
        phdev_ = nullptr;
    }

    std::vector<vk::ExtensionProperties> PhysicalDevice::enumerateDeviceExtensionProperties(vk::Optional<const std::string> layerName)
    {
        return phdev_.enumerateDeviceExtensionProperties(layerName, instance_.dispatch());
    }

    vk::PhysicalDeviceProperties PhysicalDevice::getProperties()
    {
        return phdev_.getProperties(instance_.dispatch());
    }

    vk::PhysicalDeviceFeatures PhysicalDevice::getFeatures()
    {
        return phdev_.getFeatures(instance_.dispatch());
    }

    std::vector<vk::QueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties()
    {
        return phdev_.getQueueFamilyProperties(instance_.dispatch());
    }

#ifdef VK_KHR_SURFACE_EXTENSION_NAME
    vk::Bool32 PhysicalDevice::getSurfaceSupportKHR(uint32_t queueFamilyIndex, vk::SurfaceKHR surface)
    {
        return phdev_.getSurfaceSupportKHR(queueFamilyIndex, surface, instance_.dispatch());
    }
#endif

#ifdef VK_VERSION_1_1

    void PhysicalDevice::getFeatures2(vk::PhysicalDeviceFeatures2* features)
    {
        phdev_.getFeatures2(features, instance_.dispatch());
    }

#endif
}