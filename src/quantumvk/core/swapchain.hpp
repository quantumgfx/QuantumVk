#pragma once

#include "device.hpp"
#include "queue.hpp"

namespace vkq
{
#ifdef VK_KHR_SWAPCHAIN_EXTENSION_NAME

	class SwapchainKHR
	{
	public:
		SwapchainKHR() = default;
		~SwapchainKHR() = default;

		static SwapchainKHR create(Device device, const vk::SwapchainCreateInfoKHR& createInfo);

		void destroy();

		vk::Result acquireNextImage(uint64_t timeout, vk::Semaphore semaphore, vk::Fence fence, uint32_t* pImageIndex) const;

		vk::Result present(const Queue& queue, uint32_t image, const vk::ArrayProxy<const vk::Semaphore>& waitSemaphores = {}) const;

		uint32_t imageCount() const;
		std::vector<vk::Image> images() const { return device_.vkDevice().getSwapchainImagesKHR(swapchain_, device_.dispatch()); }

		vk::SwapchainKHR vkSwapchain() const { return swapchain_; }
		vk::SwapchainKHR vkHandle() const { return swapchain_; }
		operator vk::SwapchainKHR() const { return swapchain_; }
		explicit operator bool() const noexcept { return static_cast<bool>(swapchain_); }
		bool operator!() const noexcept { return !swapchain_; }

	private:

		explicit SwapchainKHR(Device device, vk::SwapchainKHR swapchain);

		Device device_;
		vk::SwapchainKHR swapchain_;
	};

#endif
}