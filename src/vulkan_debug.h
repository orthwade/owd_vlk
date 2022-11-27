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

namespace owd
{
	/// <summary>
	/// Class of Vulkan debug.
	/// </summary>
	class c_vulkan_debug : c_singleton
	{
	public:
		/// <summary>
		/// Create singleton object, if not created already. 
		/// Get reference to single instance of this class object.
		/// </summary>
		/// <returns></returns>
		inline static c_vulkan_debug& get()
		{ return m_singleton ? *m_singleton : *(m_singleton = new c_vulkan_debug()); }

		/// <summary>
		/// Create singleton object, if not created already. 
		/// Get pointer to single instance of this class object.
		/// </summary>
		/// <returns></returns>
		inline static c_vulkan_debug* const get_ptr()
		{ return &get(); }

		/// <summary>
		/// Check if validation layers should be enabled.
		/// </summary>
		inline bool should_enable_validation_layers() const { return m_should_enable_validation_layers; }
		
		/// <summary>
		/// Get vector of validation layer names.
		/// </summary>
		inline const vec_t<const char*>& get_vec_validation_layer_name() const { return m_vec_layer_name; }

		/// <summary>
		/// Set validation layers info to instance create info.
		/// </summary>
		bool set_validation_layers(VkInstanceCreateInfo& _instance_create_info);

		/// <summary>
		/// Set validation layer support if neccessary.
		/// </summary>
		bool setup(VkInstance* _instance, VkInstanceCreateInfo& _instance_create_info);

		/// <summary>
		/// Create debugger if necessary.
		/// </summary>
		bool create(VkInstance* _instance);

		inline VkDebugUtilsMessengerEXT& get_debug_messenger() { return m_debug_messenger; }

		/// <summary>
		/// Terminate the object.
		/// </summary>
		void terminate(VkInstance* _instance, const VkDebugUtilsMessengerEXT& _debug_messenger);

	protected:
		c_vulkan_debug();
		
		vec_t<const char*> m_vec_layer_name;

		const bool m_should_enable_validation_layers;

		VkDebugUtilsMessengerCreateInfoEXT m_debug_create_info;

		VkDebugUtilsMessengerEXT m_debug_messenger;

		bool check_validation_layer_support();

		void terminate();

		static c_vulkan_debug* m_singleton;
	};
} // namespace owd