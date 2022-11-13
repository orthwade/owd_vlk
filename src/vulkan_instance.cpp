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
        m_vec_ext_name(),
        m_app_info(),
        m_create_info(),
        m_create_result(),
        m_vec_supported_ext(),
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
        m_vec_device(),
        m_device(),
        m_queue_indices()
    {
        m_glfw_init_result = c_glfw_init::init();

        get_required_extensions();

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

        select_device();

    }

    void c_vulkan_instance::get_required_extensions()
    {
        GLFW_CALL(m_glfw_ext_names = glfwGetRequiredInstanceExtensions(&m_glfw_ext_count));

        for (size_t i_ = 0; i_ < m_glfw_ext_count; ++i_)
        {
            m_vec_ext_name.push_back((m_glfw_ext_names[i_]));
        }

        if (m_should_enable_validation_layers)
        {
            m_vec_ext_name.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
    }

    void c_vulkan_instance::get_supported_extensions()
    {
        uint32_t supported_ext_count_ = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, nullptr);

        std::vector<VkExtensionProperties> m_vec_supported_ext(supported_ext_count_);

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, m_vec_supported_ext.data());
    }

    void c_vulkan_instance::provide_mac_compatibility()
    {
        bool mac_ext_supported_ = false;

        bool mac_ext_already_added_ = false;

        bool add_mac_ext_manually_ = false;

        for (const VkExtensionProperties& supported_ext_ : m_vec_supported_ext)
        {
            if (supported_ext_.extensionName == VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)
            {
                mac_ext_supported_ = true;
                break;
            }
        }

        if (mac_ext_supported_)
        {
            for (const std::string& ext_ : m_vec_ext_name)
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
            m_vec_ext_name.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

            m_create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
    }

    void c_vulkan_instance::set_create_info()
    {
        m_create_info.enabledExtensionCount = static_cast<uint32_t>(m_vec_ext_name.size());
        m_create_info.ppEnabledExtensionNames = m_vec_ext_name.data();
    }

    void c_vulkan_instance::create_instance()
    {
        m_create_result = vkCreateInstance(&m_create_info, nullptr, &m_instance);

        if (m_create_result != VK_SUCCESS)
        {
            m_logger << L"ERROR: failed to create instance!\n";
            throw std::runtime_error("");
        }
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
        m_create_info.enabledLayerCount = static_cast<uint32_t>(m_vec_layer_name.size());
        m_create_info.ppEnabledLayerNames = m_vec_layer_name.data();
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
            //ASSERT(false);
        }

        return result;
    }

    void c_vulkan_instance::select_device()
    {
        uint32_t device_count_ = 0;

        vkEnumeratePhysicalDevices(m_instance, &device_count_, nullptr);

        m_vec_device.resize(static_cast<size_t>(device_count_));

        vkEnumeratePhysicalDevices(m_instance, &device_count_, m_vec_device.data());

        std::multimap<size_t, VkPhysicalDevice> candidates_;

        for (const VkPhysicalDevice& device_ : m_vec_device) 
        {
            size_t score_ = rate_device_suitability(device_);

            candidates_.insert(std::make_pair(score_, device_));
        }

        if (candidates_.rbegin()->first > 0)
        {
            m_device = candidates_.rbegin()->second;
        }
        else
        {
            m_logger << L"ERROR: failed to find a suitable GPU!\n";
            ASSERT(false);
        }

        m_queue_indices = find_queue_families(m_device);

        if(!m_queue_indices.graphics_familiy.has_value())
        {
            m_logger << L"ERROR: not found suitable queue family.\n";
            ASSERT(false);

        }

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
            if (result_.graphics_familiy.has_value())
            {
                break;
            }

            if (queue_family_.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
            {
                result_.graphics_familiy = i_;
            }

            ++i_;
        }

        return result_;
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
            terminate_debug_callback();

            m_list_singleton.remove(m_singleton);

            delete m_singleton;
            m_singleton = nullptr;
        }
    }
} // namespace owd