#include "vulkan_instance.h"

namespace owd
{
    c_vulkan_instance* c_vulkan_instance::m_singleton{};

    static VKAPI_ATTR VkBool32 VKAPI_CALL vulkan_debug_callback
    (
        VkDebugUtilsMessageSeverityFlagBitsEXT _severity,
        VkDebugUtilsMessageTypeFlagsEXT _type,
        const VkDebugUtilsMessengerCallbackDataEXT* _callback_data,
        void* _user_data
    ) 
    {
        VkBool32 result_ = VK_FALSE;

        if (_severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        {
            c_logger::ptr ptr_logger_ = c_logger::make(L"Vulkan debug");
            c_logger& logger_ = *ptr_logger_;

            logger_ << L"ERROR: Vulkan debug error: " << _callback_data->pMessage << L"\n";
            ASSERT(false);
        }
        else
        {
            result_ = VK_TRUE;
        }

        return result_;
    }

    c_vulkan_instance::c_vulkan_instance()
        :
        m_logger(L"Vulkan"),
        m_instance(),
        m_glfw_init_result(),
        m_glfw_ext_count(),
        m_glfw_ext_names(),
        m_vec_instance_ext_name(),
        m_app_info(),
        m_instance_create_info(),
        m_instance_create_result(),
        m_vec_supported_instance_ext(),
        m_vec_layer_name
        ({
            "VK_LAYER_KHRONOS_validation"
        }),
        #ifdef NDEBUG
            m_should_enable_validation_layers(false),
        #else
            m_should_enable_validation_layers(true),
        #endif
        m_debug_messenger(),
        m_surface(),
        m_present_queue(),
        m_vec_physical_device(),
        m_physical_device(),
        m_queue_indices(),
        m_device_queue_create_info(),
        m_logical_device_create_info(),
        m_vec_logical_device_ext_name(),
        m_logical_device(),
        m_graphics_queue(),
        m_sc_khr()
    {
        m_glfw_init_result = c_glfw_init::init();

        get_required_instance_ext();

        get_supported_extensions();

        provide_mac_compatibility();

        set_create_info();

        if (m_should_enable_validation_layers)
        {
            if (check_validation_layer_support())
            {
                set_validation_layers();
            }
        }

        create_instance();

        set_debug_callback();

        create_surface();

        list_physical_devices();
    }

    void c_vulkan_instance::get_required_instance_ext()
    {
        GLFW_CALL(m_glfw_ext_names = glfwGetRequiredInstanceExtensions(&m_glfw_ext_count));

        for (size_t i_ = 0; i_ < m_glfw_ext_count; ++i_)
        {
            m_vec_instance_ext_name.push_back((m_glfw_ext_names[i_]));
        }

        if (m_should_enable_validation_layers)
        {
            m_vec_instance_ext_name.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
    }

    void c_vulkan_instance::get_supported_extensions()
    {
        uint32_t supported_ext_count_ = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, nullptr);

        m_vec_supported_instance_ext.resize(supported_ext_count_);

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, m_vec_supported_instance_ext.data());
    }

    void c_vulkan_instance::provide_mac_compatibility()
    {
        bool mac_ext_supported_ = false;

        bool mac_ext_already_added_ = false;

        bool add_mac_ext_manually_ = false;

        for (const VkExtensionProperties& supported_ext_ : m_vec_supported_instance_ext)
        {
            if (supported_ext_.extensionName == VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)
            {
                mac_ext_supported_ = true;
                break;
            }
        }

        if (mac_ext_supported_)
        {
            for (const std::string& ext_ : m_vec_instance_ext_name)
            {
                if (ext_ == VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)
                {
                    mac_ext_already_added_ = true;
                    break;
                }
            }
        }

        if (!mac_ext_already_added_ && mac_ext_supported_)
        {
            add_mac_ext_manually_ = true;
        }

        if (add_mac_ext_manually_)
        {
            m_vec_instance_ext_name.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

            m_instance_create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
    }

    void c_vulkan_instance::set_create_info()
    {
        m_instance_create_info.enabledExtensionCount = static_cast<uint32_t>(m_vec_instance_ext_name.size());
        m_instance_create_info.ppEnabledExtensionNames = m_vec_instance_ext_name.data();
    }

    void c_vulkan_instance::create_instance()
    {
        m_instance_create_result = vkCreateInstance(&m_instance_create_info, nullptr, &m_instance);

        if (m_instance_create_result != VK_SUCCESS)
        {
            m_logger << L"ERROR: failed to create instance!\n";
            throw std::runtime_error("");
        }
    }

    void c_vulkan_instance::destroy_instance()
    {
        vkDestroyInstance(m_instance, nullptr);
    }

    bool c_vulkan_instance::check_validation_layer_support()
    {
        bool result = true;

        uint32_t layer_count_;
        
        vkEnumerateInstanceLayerProperties(&layer_count_, nullptr);

        vec_t<VkLayerProperties> vec_available_layers_(layer_count_);
        
        vkEnumerateInstanceLayerProperties(&layer_count_, vec_available_layers_.data());

        for (std::string_view layer_ : m_vec_layer_name)
        {
            bool layer_found_ = false;

            for (const VkLayerProperties& available_layer : vec_available_layers_)
            {
                if (layer_ == available_layer.layerName)
                {
                    layer_found_ = true;
                    break;
                }
            }

            if (!layer_found_) 
            {
                m_logger << L"ERROR: " << layer_ << "not supported\n";
                ASSERT(false);
                result = false;
            }
        }

        return result;
    }

    void c_vulkan_instance::set_validation_layers()
    {
        m_instance_create_info.enabledLayerCount = static_cast<uint32_t>(m_vec_layer_name.size());
        m_instance_create_info.ppEnabledLayerNames = m_vec_layer_name.data();
    }

    void c_vulkan_instance::set_debug_callback()
    {
        if (m_should_enable_validation_layers)
        {
            m_debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

            m_debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

            m_debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

            m_debug_create_info.pfnUserCallback = vulkan_debug_callback;

            m_debug_create_info.pUserData = nullptr;

            auto func_ = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");

            if (func_ != nullptr) 
            {
                if (func_(m_instance, &m_debug_create_info, nullptr, &m_debug_messenger) != VK_SUCCESS)
                {
                    m_logger << L"ERROR: failed to set up debug messenger\n";
                    ASSERT(false);
                }
            }
            else 
            {
                m_logger << L"ERROR: failed to set up debug messenger\n";
                ASSERT(false);
            }
        }
        
    }

    void c_vulkan_instance::create_surface()
    {
        #ifdef WIN32
        {
            //VkWin32SurfaceCreateInfoKHR surface_create_info_{};

            //surface_create_info_.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

            //c_window& window_ = c_window::get();
            //
            //if (!window_.get_glfw_wnd_ptr())
            //{
            //    window_.init();
            //}

            //surface_create_info_.hwnd = glfwGetWin32Window(window_.get_glfw_wnd_ptr());

            //surface_create_info_.hinstance = GetModuleHandle(nullptr);

            //if (vkCreateWin32SurfaceKHR(m_instance, &surface_create_info_, nullptr, &m_surface) != VK_SUCCESS) 
            //{
            //    m_logger << L"ERROR: failed to create window surface!\n";
            //    ASSERT(false);
            //}
        }
        #else
        {
            //m_logger << L"ERROR: only WIN32 is implemented!\n";
            //ASSERT(false);
        }
        #endif // WIN32

        c_window& window_ = c_window::init();

        GLFWwindow* ptr_glfw_window_ = window_.get_glfw_wnd_ptr();

        if (glfwCreateWindowSurface(m_instance, ptr_glfw_window_, nullptr, &m_surface) != VK_SUCCESS)
        {
            m_logger << L"ERROR: failed to create window surface!\n";
            ASSERT(false);
        }
    }

    void c_vulkan_instance::destroy_surface()
    {
        vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
    }

    void c_vulkan_instance::create_presentation_queue()
    {
        std::vector<VkDeviceQueueCreateInfo> vec_queue_create_info;

        vec_t<uint32_t> vec_unique_queue_families_ 
            = { m_queue_indices.graphics_familiy.value(), m_queue_indices.present_familiy.value() };

        float queuePriority = 1.0f;

        for (uint32_t queueFamily : vec_unique_queue_families_) 
        {
            VkDeviceQueueCreateInfo queue_create_info_{};

            queue_create_info_.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queue_create_info_.queueFamilyIndex = queueFamily;
            queue_create_info_.queueCount = 1;
            queue_create_info_.pQueuePriorities = &queuePriority;

            vec_queue_create_info.push_back(queue_create_info_);
        }

        m_logical_device_create_info.queueCreateInfoCount = static_cast<uint32_t>(vec_queue_create_info.size());
        m_logical_device_create_info.pQueueCreateInfos = vec_queue_create_info.data();

    }

    size_t c_vulkan_instance::rate_device_suitability(const VkPhysicalDevice& _device)
    {
        size_t result = 0;

        VkPhysicalDeviceProperties device_properties_;
        VkPhysicalDeviceFeatures device_features_;

        vkGetPhysicalDeviceProperties(_device, &device_properties_);
        vkGetPhysicalDeviceFeatures(_device, &device_features_);

        if (device_properties_.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            result += 1000;
        }

        result += static_cast<size_t>(device_properties_.limits.maxImageDimension2D);

        if (!device_features_.geometryShader)
        {
            m_logger << L"WARNING: the device doesn't have geometry shaders\n";
            result = 0;
            ASSERT(false);
        }

        return result;
    }

    void c_vulkan_instance::list_physical_devices()
    {
        uint32_t device_count_ = 0;

        vkEnumeratePhysicalDevices(m_instance, &device_count_, nullptr);

        m_vec_physical_device.resize(static_cast<size_t>(device_count_));

        vkEnumeratePhysicalDevices(m_instance, &device_count_, m_vec_physical_device.data());

        for (const VkPhysicalDevice& device_ : m_vec_physical_device)
        {
            size_t score_ = rate_device_suitability(device_);

            m_mmap_phys_device_candidate.insert(std::make_pair(score_, device_));
        }
    }


    bool c_vulkan_instance::select_physical_device(const std::pair<size_t, VkPhysicalDevice>& _candidate)
    {
        bool result = false;

        if (_candidate.first > 0)
        {
            m_physical_device = _candidate.second;

            m_queue_indices = find_queue_families(m_physical_device);

            if (!m_queue_indices.is_complete())
            {
                m_logger << L"ERROR: not found suitable queue family.\n";
                //ASSERT(false);
            }
            else
            {
                result = true;
            }
        }
        else
        {
            m_logger << L"ERROR: failed to find a suitable GPU!\n";
            //ASSERT(false);
        }
        
        return result;
    }

    c_vulkan_instance::s_queue_indices c_vulkan_instance::find_queue_families(const VkPhysicalDevice& _device)
    {
        c_vulkan_instance::s_queue_indices result_;

        uint32_t queue_family_count_ = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(_device, &queue_family_count_, nullptr);

        std::vector<VkQueueFamilyProperties> vec_queue_family_(queue_family_count_);
        vkGetPhysicalDeviceQueueFamilyProperties(_device, &queue_family_count_, vec_queue_family_.data());

        uint32_t i_ = 0;

        for (const VkQueueFamilyProperties& queue_family_ : vec_queue_family_) 
        {

            if (result_.is_complete())
            {
                break;
            }

            if (queue_family_.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
            {
                result_.graphics_familiy = i_;

                VkBool32 present_support_ = false;

                vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, i_, m_surface, &present_support_);

                if (present_support_)
                {
                    result_.present_familiy = i_;
                }
            }

            ++i_;
        }

        return result_;
    }

    bool c_vulkan_instance::add_swap_chain_support()
    {
        bool result = false;

        m_vec_logical_device_ext_name.push_back("VK_KHR_swapchain");

        uint32_t extension_count_;
        vkEnumerateDeviceExtensionProperties(m_physical_device, nullptr, &extension_count_, nullptr);

        std::vector<VkExtensionProperties> vec_available_ext_(extension_count_);
        vkEnumerateDeviceExtensionProperties(m_physical_device, nullptr, &extension_count_, vec_available_ext_.data());

        bool found = false;

        for (const VkExtensionProperties& ext : vec_available_ext_)
        {
            if (sv_t(ext.extensionName) == sv_t(m_vec_logical_device_ext_name.back()))
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            m_logger << L"ERROR: swapchain is not supported.\n";
            ASSERT(false);
        }
        else
        {
            result = true;
        }

        m_logical_device_create_info.enabledExtensionCount 
            = static_cast<uint32_t>(m_vec_logical_device_ext_name.size());
        
        m_logical_device_create_info.ppEnabledExtensionNames = m_vec_logical_device_ext_name.data();

        return result;
    }

    bool c_vulkan_instance::create_logical_device()
    {
        bool result = false;

        float queue_priority_ = 1.0f;

        m_device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        m_device_queue_create_info.queueFamilyIndex = m_queue_indices.graphics_familiy.value();
        m_device_queue_create_info.queueCount = 1;
        m_device_queue_create_info.pQueuePriorities = &queue_priority_;

        VkPhysicalDeviceFeatures device_features_{};

        m_logical_device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        m_logical_device_create_info.pQueueCreateInfos = &m_device_queue_create_info;
        m_logical_device_create_info.queueCreateInfoCount = 1;

        m_logical_device_create_info.pEnabledFeatures = &device_features_;

        m_logical_device_create_info.enabledExtensionCount = 0;

        if (m_should_enable_validation_layers) 
        {
            m_logical_device_create_info.enabledLayerCount = static_cast<uint32_t>(m_vec_layer_name.size());
            m_logical_device_create_info.ppEnabledLayerNames = m_vec_layer_name.data();
        }
        else 
        {
            m_logical_device_create_info.enabledLayerCount = 0;
        }

        if (add_swap_chain_support())
        {
            if (vkCreateDevice(m_physical_device, &m_logical_device_create_info, nullptr, &m_logical_device) != VK_SUCCESS)
            {
                m_logger << L"ERROR: failed to create logical device!\n";
                //ASSERT(false);
            }
            else
            {
                result = true;
            }
        }

        return result;
    }

    void c_vulkan_instance::destroy_logical_device()
    {
        vkDestroyDevice(m_logical_device, nullptr);
    }

    void c_vulkan_instance::retrieve_queue_handles()
    {
        vkGetDeviceQueue(m_logical_device, m_queue_indices.graphics_familiy.value(), 0, &m_graphics_queue);
    }

    c_vulkan_instance::s_sc_khr_t c_vulkan_instance::get_swap_chain_and_khr_surface_details()
    {
        c_vulkan_instance::s_sc_khr_t result{};

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, m_surface, &result.capabilities);

        uint32_t format_count_ = 0;

        vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface, &format_count_, nullptr);

        result.vec_format.resize(format_count_);

        if (!result.vec_format.empty())
        {
            vkGetPhysicalDeviceSurfaceFormatsKHR
            (m_physical_device, m_surface, &format_count_, result.vec_format.data());
        }

        uint32_t present_mode_count_ = 0;

        vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface, &present_mode_count_, nullptr);

        result.vec_present_mode.resize(present_mode_count_);

        if (!result.vec_present_mode.empty())
        {
            vkGetPhysicalDeviceSurfacePresentModesKHR
            (m_physical_device, m_surface, &present_mode_count_, result.vec_present_mode.data());
        }

        return result;
    }

    bool c_vulkan_instance::check_swap_chain_support()
    {
        bool result = false;

        if (m_sc_khr.vec_format.empty())
        {
            m_logger << "ERROR: no supported surface formats\n";
            //ASSERT(false);
        }
        else if (m_sc_khr.vec_present_mode.empty())
        {
            m_logger << "ERROR: no supported present mode\n";
            //ASSERT(false);
        }
        else
        {
            result = true;
        }

        return result;

    }

    bool c_vulkan_instance::select_best_device()
    {
        bool result = false;

        for (auto iter = m_mmap_phys_device_candidate.rbegin(); iter != m_mmap_phys_device_candidate.rend(); ++iter)
        {
            if (!select_physical_device(*iter))
            {
                continue;
            }

            if (!create_logical_device())
            {
                continue;
            }

            create_presentation_queue();

            retrieve_queue_handles();

            m_sc_khr = get_swap_chain_and_khr_surface_details();
            
            if (check_swap_chain_support())
            {
                result = true;

                break;
            }
        }

        return result;
    }

    void c_vulkan_instance::terminate_debug_callback()
    {
        auto func_ = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr
        (m_instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func_ != nullptr) 
        {
            func_(m_instance, m_debug_messenger, nullptr);
        }
    }

    void c_vulkan_instance::terminate()
    {
        if (m_singleton)
        {
            destroy_surface();

            terminate_debug_callback();
            
            destroy_logical_device();

            destroy_instance();

            m_list_singleton.remove(m_singleton);

            delete m_singleton;
            m_singleton = nullptr;
        }
    }
} // namespace owd