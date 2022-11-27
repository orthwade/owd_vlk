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
#include <map>
#include <optional>
#include <set>

#include "owd_lib.h"
#include "glfw_init.h"
#include "window.h"

#include "vulkan_debug.h"

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

		struct s_swapchain_and_khr_surface_details 
		{
			VkSurfaceCapabilitiesKHR capabilities;
		
			vec_t<VkSurfaceFormatKHR> vec_format;
			
			vec_t<VkPresentModeKHR> vec_present_mode;
		};

		struct s_phys_device_info
		{
			std::string name;
			uint32_t	id;
			idx_t		index;
		};

		using s_sc_khr_t = s_swapchain_and_khr_surface_details;

		using surface_format_t = VkSurfaceFormatKHR;

		/// <summary>
		/// If not created already: create singleton and initialize Vulkan.
		/// Get reference to singleton.
		/// </summary>
		static c_vulkan_instance& init() { return m_singleton ? *m_singleton : *(m_singleton = new c_vulkan_instance); }

		/// <summary>
		/// Terminate vulkan and delete singleton.
		/// </summary>
		void terminate() override;

		/// <summary>
		/// Automatically select and set up best device.
		/// </summary>
		/// <returns>true if succesfull; false, if no suitable device was found.</returns>
		bool select_best_device();

		/// <summary>
		/// Select physical device with index. 
		/// Index can be retrieved with print_all_phys_devices_info or get_vec_phys_device_info.
		/// </summary>
		bool select_device(idx_t _device_index);

		/// <summary>
		/// Print physical device name and ID.
		/// </summary>
		/// <param name="_phys_device"></param>
		/// <returns></returns>
		bool print_phys_device_info(const VkPhysicalDevice& _phys_device);

		/// <summary>
		/// Print all physical devices name, ID and index.
		/// </summary>
		bool print_all_phys_devices_info();

		/// <summary>
		/// Get vector of physical device info.
		/// </summary>
		inline const vec_t<s_phys_device_info>& get_vec_phys_device_info() const { return m_vec_phys_device_info; }

		/// <summary>
		/// Get vector of swapchain image handles.
		/// </summary>
		inline const vec_t<VkImage>& get_vec_swapchain_image() const { return m_vec_swapchain_image; }

	protected:
		c_logger m_logger;
		
		VkInstance m_instance;
		
		bool m_glfw_init_result;

		uint32_t m_glfw_ext_count;

		const char** m_glfw_ext_names;

		vec_t<const char*> m_vec_instance_ext_name;

		VkApplicationInfo m_app_info;

		VkInstanceCreateInfo m_instance_create_info;

		VkResult m_instance_create_result;

		std::vector<VkExtensionProperties> m_vec_supported_instance_ext;

		c_vulkan_debug* m_debug;

		VkSurfaceKHR m_surface;

		VkQueue m_present_queue;

		vec_t<VkPhysicalDevice> m_vec_physical_device;

		mmap_t<size_t, VkPhysicalDevice> m_mmap_phys_device_candidate;
		
		VkPhysicalDevice m_physical_device;

		vec_t<s_phys_device_info> m_vec_phys_device_info;

		s_queue_indices m_queue_indices;

		VkDeviceQueueCreateInfo m_device_queue_create_info;

		VkDeviceCreateInfo m_logical_device_create_info;

		vec_t<const char*> m_vec_logical_device_ext_name;

		VkDevice m_logical_device;

		VkQueue m_graphics_queue;

		s_sc_khr_t m_sc_khr;

		VkSwapchainKHR m_swapchain;

		vec_t<VkImage> m_vec_swapchain_image;

		VkFormat m_swapchain_image_format;
		
		VkExtent2D m_swapchain_extent;

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

		void terminate_debug_callback();

		void create_surface();

		void destroy_surface();

		void create_presentation_queue();
		
		size_t rate_device_suitability(const VkPhysicalDevice& _device);

		void list_physical_devices();

		bool select_physical_device(const std::pair<size_t, VkPhysicalDevice>& _candidate);

		s_queue_indices find_queue_families(const VkPhysicalDevice& _device);

		bool add_swapchain_support();

		bool create_logical_device();

		void destroy_logical_device();

		void retrieve_queue_handles();

		s_sc_khr_t get_swapchain_and_khr_surface_details();

		bool check_swapchain_support();

		VkSurfaceFormatKHR	choose_surface_format(const vec_t<VkSurfaceFormatKHR>& _vec_format);
		VkPresentModeKHR	choose_swap_present_mode(const std::vector<VkPresentModeKHR>& _vec_mode);
		VkExtent2D			choose_swap_extent(const VkSurfaceCapabilitiesKHR& _capabilities);

		bool create_swapchain();

		void destroy_swapchain();
	};
} // namespace owd