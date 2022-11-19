#pragma once

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
#include <map>
#include <optional>
#include <set>

#include "owd_lib.h"
#include "glfw_init.h"
#include "window.h"

namespace owd
{
	/// <summary>
	/// Singleton class of Vulkan instance.
	/// </summary>
	class c_vulkan_instance : public c_singleton
	{
	public:
		struct s_queue_indices
		{
			std::optional<uint32_t> graphics_familiy;
			std::optional<uint32_t> present_familiy;

			inline bool is_complete() const { return graphics_familiy.has_value() && present_familiy.has_value(); }
		};
		/// <summary>
		/// If not created already: create singleton and initialize Vulkan.
		/// Get reference to singleton.
		/// </summary>
		static c_vulkan_instance& init() { return m_singleton ? *m_singleton : *(m_singleton = new c_vulkan_instance); }

		/// <summary>
		/// Terminate vulkan and delete singleton.
		/// </summary>
		void terminate() override;

	protected:
		c_logger m_logger;
		
		VkInstance m_instance;
		
		bool m_glfw_init_result;

		uint32_t m_glfw_ext_count;

		const char** m_glfw_ext_names;

		vec_t<const char*> m_vec_instance_ext_name;

		VkApplicationInfo m_app_info;

		VkInstanceCreateInfo m_create_info;

		VkResult m_create_result;

		std::vector<VkExtensionProperties> m_vec_supported_ext;

		vec_t<const char*> m_vec_layer_name;

		const bool m_should_enable_validation_layers;

		VkDebugUtilsMessengerCreateInfoEXT m_debug_create_info{};
		
		VkDebugUtilsMessengerEXT m_debug_messenger;

		VkSurfaceKHR m_surface;

		VkQueue m_present_queue;

		vec_t<VkPhysicalDevice> m_vec_physical_device;
		
		VkPhysicalDevice m_physical_device;

		s_queue_indices m_queue_indices;

		VkDeviceQueueCreateInfo m_device_queue_create_info;

		VkDeviceCreateInfo m_device_create_info;

		VkDevice m_logical_device;

		VkQueue m_graphics_queue;

		static c_vulkan_instance* m_singleton;

		c_vulkan_instance();

		/// <summary>
		/// Get required extensions.
		/// </summary>
		void get_required_instance_ext();

		/// <summary>
		/// Get all supported extensions.
		/// </summary>
		void get_supported_extensions();

		/// <summary>
		/// Provide Mac OS compatibility extensions if necessary and if not done automatically in get_required_extensions.
		/// </summary>
		void provide_mac_compatibility();

		/// <summary>
		/// Convert stored extension data to Vulkan supported format and set create info fields.
		/// </summary>
		void set_create_info();

		/// <summary>
		/// Create instance.
		/// </summary>
		void create_instance();

		void destroy_instance();

		/// <summary>
		/// Check stored member validation layers support.
		/// </summary>
		bool check_validation_layer_support();

		/// <summary>
		/// Set validation layers
		/// </summary>
		void set_validation_layers();

		void set_debug_callback();

		void terminate_debug_callback();

		void create_surface();

		void destroy_surface();

		void create_presentation_queue();
		
		size_t rate_device_suitability(const VkPhysicalDevice& _device);

		void select_device();

		s_queue_indices find_queue_families(const VkPhysicalDevice& _device);

		void create_logical_device();

		void destroy_logical_device();

		void retrieve_queue_handles();

		


	};
} // namespace owd