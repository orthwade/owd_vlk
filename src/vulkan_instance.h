#pragma once
#include <vulkan/vulkan.h>
#include "owd_lib.h"
#include "glfw_init.h"

namespace owd
{
	/// <summary>
	/// Singleton class of Vulkan instance.
	/// </summary>
	class c_vulkan_instance : public c_singleton
	{
	public:

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

		uint32_t m_glfw_ext;

		const char** m_glfw_ext_names;

		VkApplicationInfo m_app_info;

		VkInstanceCreateInfo m_create_info;

		VkResult m_result;

		static c_vulkan_instance* m_singleton;

		c_vulkan_instance();
	};
  
   
} // namespace owd