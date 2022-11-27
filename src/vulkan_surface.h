#pragma once
#define NOMINMAX 

#ifdef WIN32
#ifndef VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_PLATFORM_WIN32_KHR
#endif // !VK_USE_PLATFORM_WIN32_KHR
#endif // WIN32

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif // !GLFW_INCLUDE_VULKAN

#ifdef WIN32
#ifndef GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif // !GLFW_EXPOSE_NATIVE_WIN32
#endif // WIN32

#include <vulkan/vulkan.h>

#include "owd_lib/owd_lib.h"
#include "window.h"

namespace owd
{
	/// <summary>
	/// Class of Vulkan surface.
	/// </summary>
	class c_vulkan_surface : c_object
	{
	public:
		using ptr = ptr_t<c_vulkan_surface>;
		
		/// <summary>
		/// Crete object.
		/// </summary>
		/// <param name="_vk_instance"></param>
		c_vulkan_surface(const VkInstance& _vk_instance);

		/// <summary>
		/// Construct object with given Vulkan instance. 
		/// Make shared_ptr of this object class and get this shared_ptr.	
		/// </summary>
		/// <param name="_vk_instance"></param>
		inline static ptr make(const VkInstance& _vk_instance) 
		{ return std::make_shared<c_vulkan_surface>(_vk_instance); }
		
		/// <summary>
		/// Create Vulkan surface.
		/// </summary>
		/// <returns></returns>
		bool create();

		/// <summary>
		/// Get member of VkSurfaceKHR type.
		/// </summary>
		/// <returns></returns>
		inline const VkSurfaceKHR& get_surface() const { return m_surface; }

		/// <summary>
		/// Destroy Vulkan surface.
		/// </summary>
		inline void destroy() { vkDestroySurfaceKHR(m_vk_instance, m_surface, nullptr); }

	protected:
		VkSurfaceKHR m_surface;

		VkInstance m_vk_instance;

	};
} // namespace owd