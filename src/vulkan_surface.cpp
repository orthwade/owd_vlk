#include "vulkan_surface.h"

namespace owd
{
	c_vulkan_surface::c_vulkan_surface(const VkInstance& _vk_instance)
		:
		c_object(L"Vulkan surface"),
		m_surface(),
		m_vk_instance(_vk_instance)
	{
	}
	bool c_vulkan_surface::create()
	{
		bool result_ = false;

		c_window& window_ = c_window::init();

		GLFWwindow* ptr_glfw_window_ = window_.get_glfw_wnd_ptr();

		if (glfwCreateWindowSurface(m_vk_instance, ptr_glfw_window_, nullptr, &m_surface) != VK_SUCCESS)
		{
			m_logger << L"ERROR: failed to create window surface!\n";
			ASSERT(false);
		}
		else
		{
			result_ = true;
		}

		return result_;
	}
} // namespace owd