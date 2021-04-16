#include "swapchain.hpp"

namespace vkq
{

#ifdef VK_KHR_SWAPCHAIN_EXTENSION_NAME

	SwapchainKHR::SwapchainKHR(Device device, vk::SwapchainKHR swapchain)
		: device_(device), swapchain_(swapchain)
	{
	}

	SwapchainKHR SwapchainKHR::create(Device device, const vk::SwapchainCreateInfoKHR& createInfo)
	{
		return SwapchainKHR{ device, device.vkDevice().createSwapchainKHR(createInfo, nullptr, device.dispatch()) };
	}

	void SwapchainKHR::destroy()
	{
		device_.vkHandle().destroySwapchainKHR(swapchain_, nullptr, device_.dispatch());
		swapchain_ = nullptr;
		device_ = {};
	}

	vk::Result SwapchainKHR::acquireNextImage(uint64_t timeout, vk::Semaphore semaphore, vk::Fence fence, uint32_t* pImageIndex) const
	{
		return device_.vkHandle().acquireNextImageKHR(swapchain_, timeout, semaphore, fence, pImageIndex, device_.dispatch());
	}

	vk::Result SwapchainKHR::present(const Queue& queue, uint32_t image, const vk::ArrayProxy<const vk::Semaphore>& waitSemaphores) const
	{
		// TODO
		return vk::Result();
	}

	uint32_t SwapchainKHR::imageCount() const
	{
		uint32_t count;
		vk::throwResultException(device_.vkHandle().getSwapchainImagesKHR(swapchain_, &count, nullptr, device_.dispatch()), "Failed to retrieve image count for swapchain");
		return count;
	}

#endif
}