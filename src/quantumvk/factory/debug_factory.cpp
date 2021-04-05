#include "debug_factory.hpp"

namespace vkq
{

    DebugUtilsMessengerEXTFactory::DebugUtilsMessengerEXTFactory(Instance instance)
        : instance(instance)
    {
    }

    vk::DebugUtilsMessengerEXT DebugUtilsMessengerEXTFactory::build()
    {
        vk::DebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.messageSeverity = severityFlags;
        createInfo.messageType = typeFlags;
        createInfo.pUserData = nullptr;
        createInfo.pfnUserCallback = messengerCallback;

        return instance.vkInstance().createDebugUtilsMessengerEXT(createInfo, nullptr, instance.dispatch());
    }
} // namespace vkq