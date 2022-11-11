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

		uint32_t m_glfw_ext_count;

		const char** m_glfw_ext_names;

		vec_t<const char*> m_vec_glfw_ext_name;

		VkApplicationInfo m_app_info;

		VkInstanceCreateInfo m_create_info;

		VkResult m_create_result;

		std::vector<VkExtensionProperties> m_vec_supported_ext;

		vec_t<std::string> m_vec_instance_ext_name;

		vec_t<const char*> m_vec_layer_name;

		#ifdef NDEBUG
				const bool m_should_enable_validation_layers = false;
		#else
				const bool m_should_enable_validation_layers = true;
		#endif
				
		static c_vulkan_instance* m_singleton;

		c_vulkan_instance();

		/// <summary>
		/// Get required extensions.
		/// </summary>
		void get_required_extensions();

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

		/// <summary>
		/// Check stored member validation layers support.
		/// </summary>
		bool check_validation_layer_support();

		/// <summary>
		/// Set validation layers
		/// </summary>
		void set_validation_layers();


	};
  
   
} // namespace owd