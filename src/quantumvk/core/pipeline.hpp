#pragma once

#include "../base/vk.hpp"
#include "spirv_cross.hpp"

#include "device.hpp"

namespace vkq
{

    class ShaderModule
    {
    public:
        static ShaderModule create(const Device& device, const vk::ShaderModuleCreateInfo& createInfo);
        static ShaderModule create(size_t codeSize, uint32_t* pCode, vk::ShaderModuleCreateFlags flags = {}, VkNextProxy<vk::ShaderModuleCreateInfo> next = nullptr);
        static void destroy();

    private:
    };

} // namespace vkq
