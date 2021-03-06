#pragma once

#include "../base/vk.hpp"
#include "instance.hpp"
#include "loader.hpp"
#include "physical_device.hpp"

namespace vkq
{

    /**
     * @brief A handle representing a vk::Device and a dynamic dispatcher
     * 
     */
    class Device
    {
    public:
        struct ExtensionSupport
        {
#ifdef VK_KHR_BIND_MEMORY_2_EXTENSION_NAME
            bool bindMemory2KHR = false;
#endif
#ifdef VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME
            bool bufferDeviceAddressKHR = false;
#endif
#ifdef VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME
            bool dedicatedAllocationKHR = false;
#endif
#ifdef VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME
            bool deviceCoherentMemoryAMD = false;
#endif
#ifdef VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME
            bool getMemoryRequirements2KHR = false;
#endif
#ifdef VK_EXT_MEMORY_BUDGET_EXTENSION_NAME
            bool memoryBudgetEXT = false;
#endif
#ifdef VK_KHR_SWAPCHAIN_EXTENSION_NAME
            bool swapchainKHR = false;
#endif
        };

    public:
        Device() = default;
        ~Device() = default;

    public:
        /**
         * @brief Creates a new device given a vkq::Instance, a vk::PhysicalDevice, and vk::DeviceCreateInfo
         * 
         * @param instance Parent instance of device
         * @param phdev Physical Device that the logical device will interface with.
         * @param createInfo Info to be passed into vk:: createDevice() that creates the vk::Device handle
         * @return Newly created device 
         */
        static Device create(const Instance& instance, vk::PhysicalDevice phdev, const vk::DeviceCreateInfo& createInfo);

        /**
         * @brief Creates a new device given a vkq::PhysicalDevice, and vk::DeviceCreateInfo.
         * 
         * @param phdev Physical Device that the logical device will interface with.
         * @param createInfo Info to be passed into vk:: createDevice() that creates the vk::Device handle
         * @return Newly created device 
         */
        static Device create(const PhysicalDevice& phdev, const vk::DeviceCreateInfo& createInfo) { return create(phdev.instance(), phdev.vkPhysicalDevice(), createInfo); }

        /**
         * @brief Destroys device object and invalidates all references to it
         * 
         */
        void destroy();

        //////////////////////////////////
        // Core Alias functions //////////
        //////////////////////////////////

        std::vector<vk::CommandBuffer> allocateCommandBuffers(const vk::CommandBufferAllocateInfo& allocateInfo) const
        {
            return vkDevice().allocateCommandBuffers(allocateInfo, dispatch());
        }

        vk::BufferView createBufferView(const vk::BufferViewCreateInfo& createInfo) const
        {
            return vkDevice().createBufferView(createInfo, nullptr, dispatch());
        }

        vk::CommandPool createCommandPool(const vk::CommandPoolCreateInfo& createInfo) const
        {
            return vkDevice().createCommandPool(createInfo, nullptr, dispatch());
        }

        vk::Fence createFence(const vk::FenceCreateInfo& createInfo) const
        {
            return vkDevice().createFence(createInfo, nullptr, dispatch());
        }

        vk::ImageView createImageView(const vk::ImageViewCreateInfo& createInfo) const
        {
            return vkDevice().createImageView(createInfo, nullptr, dispatch());
        }

        vk::Semaphore createSemaphore(const vk::SemaphoreCreateInfo& createInfo) const
        {
            return vkDevice().createSemaphore(createInfo, nullptr, dispatch());
        }

        void destroyBufferView(vk::BufferView bufferView)
        {
            vkDevice().destroyBufferView(bufferView, nullptr, dispatch());
        }

        void destroyCommandPool(vk::CommandPool commandPool) const
        {
            vkDevice().destroyCommandPool(commandPool, nullptr, dispatch());
        }

        void destroyFence(vk::Fence fence) const
        {
            return vkDevice().destroyFence(fence, nullptr, dispatch());
        }

        void destroyImageView(vk::ImageView imageView) const
        {
            return vkDevice().destroyImageView(imageView, nullptr, dispatch());
        }

        void destroySemaphore(vk::Semaphore semaphore) const
        {
            return vkDevice().destroySemaphore(semaphore, nullptr, dispatch());
        }

        void freeCommandBuffers(vk::CommandPool commandPool, const vk::ArrayProxy<const vk::CommandBuffer>& commandBuffers) const
        {
            vkDevice().freeCommandBuffers(commandPool, commandBuffers, dispatch());
        }

        vk::Queue getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const
        {
            return vkDevice().getQueue(queueFamilyIndex, queueIndex, dispatch());
        }

        void resetCommandPool(vk::CommandPool commandPool, vk::CommandPoolResetFlags flags = {}) const
        {
            vkDevice().resetCommandPool(commandPool, flags, dispatch());
        }

        void waitIdle() const
        {
            vkDevice().waitIdle(dispatch());
        }

        vk::Result getFenceStatus(vk::Fence fence) const
        {
            return vkDevice().getFenceStatus(fence, dispatch());
        }

        vk::Result waitForFences(const vk::ArrayProxy<const vk::Fence>& fences, vk::Bool32 waitAll, uint64_t timeout) const
        {
            return vkDevice().waitForFences(fences, waitAll, timeout, dispatch());
        }

        void resetFence(const vk::ArrayProxy<const vk::Fence>& fences) const
        {
            vkDevice().resetFences(fences, dispatch());
        }

        ////////////////////////////////
        // Version 1.1 /////////////////
        ////////////////////////////////

        ///////////////////////////////
        // Version 1.2 ////////////////
        ///////////////////////////////


#ifdef VK_VERSION_1_2
        uint64_t getSemaphoreCounterValue(vk::Semaphore semaphore)
        {
            return vkDevice().getSemaphoreCounterValue(semaphore, dispatch());
        }

        void signalSemaphore(const vk::SemaphoreSignalInfo& signalInfo)
        {
            vkDevice().signalSemaphore(signalInfo, dispatch());
        }

        vk::Result waitSemaphore(const vk::SemaphoreWaitInfo& waitInfo, uint64_t timeout)
        {
            return vkDevice().waitSemaphores(waitInfo, timeout, dispatch());
        }

#endif


        ///////////////////////////////
        // Helper Functions ///////////
        ///////////////////////////////

        void allocateCommandBuffers(vk::CommandPool commandPool, uint32_t commandBufferCount, vk::CommandBuffer* commandBuffers, vk::CommandBufferLevel level, const VkNextProxy<vk::CommandBufferAllocateInfo>& next = {}) const;

        ///////////////////////////////
        // Properties helpers /////////
        ///////////////////////////////

        /**
         * @brief Gets the device api version. This is essentially just min(instanceApiVersion, physicalDeviceApiVersion)
         * 
         * @return uint32_t containing the device api version
         */
        uint32_t apiVersion() const;

        const vk::PhysicalDeviceProperties& properties() const;
        const vk::PhysicalDeviceMemoryProperties& memoryProperties() const;
        vk::MemoryType memoryTypeProperties(uint32_t memoryTypeIndex) const;
        vk::MemoryHeap memoryHeapProperties(uint32_t memoryHeapIndex) const;

        /**
         * @brief Returns whether a particular device extension is enabled
         * 
         * @param extensionName 
         * @return true 
         * @return false 
         */
        bool isDeviceExtensionEnabled(const char* extensionName) const;

        const ExtensionSupport& extensionSupport() const;

        
        ///////////////////////////////
        // Native Objects /////////////
        ///////////////////////////////

        /**
         * @brief Get the device dispatcher
         * 
         * @return A vk::DispatchLoaderDynamic capable of running all global, instance, and device level functions
         * (associated with this device or the parent instance).
         */
        const vk::DispatchLoaderDynamic& dispatch() const;

        /**
         * @brief Get the PFN_vkGetDeviceProcAddr used to load device level function pointers.
         * 
         * @return The PFN_vkGetDeviceProcAddr used to load device level function pointers.
         */
        PFN_vkGetDeviceProcAddr deviceProcAddrLoader() const { return dispatch().vkGetDeviceProcAddr; }

        /**
         * @brief Get the parent instance of device. 
         * 
         * @return The vkq::Instance used to create the device.
         */
        Instance instance() const;

        vk::Instance vkInstance() const;
        vk::PhysicalDevice vkPhysicalDevice() const;
        vk::Device vkDevice() const;
        vk::Device vkHandle() const;
        operator vk::Device() const;

    private:
        struct Impl
        {
            Instance instance;
            vk::PhysicalDevice phdev;
            vk::Device device;
            vk::DispatchLoaderDynamic dispatch;

            // Properties
            vk::PhysicalDeviceProperties props;
            vk::PhysicalDeviceMemoryProperties memProps;
            std::vector<const char*> enabledExtensions;
            Device::ExtensionSupport extensionSupport;
        };

        explicit Device(Impl* impl);

        Impl* impl = nullptr;
    };
} // namespace vkq