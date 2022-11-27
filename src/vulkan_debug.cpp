#include "vulkan_debug.h"

namespace owd
{
	#ifdef NDEBUG
		static constexpr bool should_enable_validation_layers_{ false };
	#else
		static constexpr bool should_enable_validation_layers_{ true };
	#endif

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

    c_vulkan_debug* c_vulkan_debug::m_singleton{};

    bool c_vulkan_debug::setup(VkInstance* _instance, VkInstanceCreateInfo& _instance_create_info)
    {
        bool result_ = true;
        
        VkInstance instance_ = *_instance;

        if (m_should_enable_validation_layers)
        {
            m_debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

            m_debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

            m_debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

            m_debug_create_info.pfnUserCallback = vulkan_debug_callback;

            m_debug_create_info.pUserData = nullptr;

            auto func_ = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT");

            if (func_ != nullptr)
            {
                if (func_(instance_, &m_debug_create_info, nullptr, &m_debug_messenger) != VK_SUCCESS)
                {
                    m_logger << L"ERROR: failed to set up debug messenger\n";
                    result_ = false;
                    ASSERT(false);
                }
            }
            else
            {
                m_logger << L"ERROR: failed to set up debug messenger\n";
                result_ = false;
                ASSERT(false);
            }
        }

        if (m_should_enable_validation_layers)
        {
            if (check_validation_layer_support())
            {
            }
            else
            {
                result_ = false;
            }
        }

        *_instance = instance_;

        return result_;
    }

    void c_vulkan_debug::terminate(VkInstance* _instance, const VkDebugUtilsMessengerEXT& _debug_messenger)
    {
        if (m_singleton)
        {
            auto func_ = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr
            (*_instance, "vkDestroyDebugUtilsMessengerEXT");

            if (func_ != nullptr)
            {
                func_(*_instance, _debug_messenger, nullptr);
            }
            terminate();
        }
    }

    void c_vulkan_debug::terminate()
    {
        if (m_singleton)
        {
            m_list_singleton.remove(m_singleton);

            delete m_singleton;
            m_singleton = nullptr;
        }
    }

    c_vulkan_debug::c_vulkan_debug()
		:
		c_singleton(L"Vulkan debug"),
        m_vec_layer_name
        ({
            "VK_LAYER_KHRONOS_validation"
        }),
		m_should_enable_validation_layers(should_enable_validation_layers_),
		m_debug_create_info(),
		m_debug_messenger()
	{
       
	}

    bool c_vulkan_debug::check_validation_layer_support()
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

    bool c_vulkan_debug::set_validation_layers(VkInstanceCreateInfo& _instance_create_info)
    {
        bool result_ = true;

        _instance_create_info.enabledLayerCount = static_cast<uint32_t>(m_vec_layer_name.size());
        _instance_create_info.ppEnabledLayerNames = m_vec_layer_name.data();
        
        return result_;
    }

    bool c_vulkan_debug::create(VkInstance* _instance)
    {
        bool result_ = false;

        VkInstance instance_ = *_instance;

        if (m_should_enable_validation_layers)
        {
            m_debug_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

            m_debug_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

            m_debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

            m_debug_create_info.pfnUserCallback = vulkan_debug_callback;

            m_debug_create_info.pUserData = nullptr;

            auto func_ = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT");

            if (func_ != nullptr)
            {
                if (func_(instance_, &m_debug_create_info, nullptr, &m_debug_messenger) != VK_SUCCESS)
                {
                    m_logger << L"ERROR: failed to set up debug messenger\n";
                    ASSERT(false);
                }
                else
                {
                    result_ = true;
                }
            }
            else
            {
                m_logger << L"ERROR: failed to set up debug messenger\n";
                ASSERT(false);
            }
        }
        *_instance = instance_;
        return result_;
    }


} // namespace owd