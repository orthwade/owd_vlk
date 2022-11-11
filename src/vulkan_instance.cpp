#include "vulkan_instance.h"

namespace owd
{
    c_vulkan_instance* c_vulkan_instance::m_singleton{};

    c_vulkan_instance::c_vulkan_instance()
        :
        m_logger(L"Vulkan"),
        m_instance(),
        m_glfw_init_result(),
        m_glfw_ext_count(),
        m_glfw_ext_names(),
        m_vec_glfw_ext_name(),
        m_app_info(),
        m_create_info(),
        m_create_result(),
        m_vec_supported_ext(),
        m_vec_instance_ext_name
        ({
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME
        }),
        m_vec_layer_name
        ({
            "VK_LAYER_KHRONOS_validation"
        })
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

    }

    void c_vulkan_instance::get_required_extensions()
    {
        GLFW_CALL(m_glfw_ext_names = glfwGetRequiredInstanceExtensions(&m_glfw_ext_count));

        for (size_t i_ = 0; i_ < m_glfw_ext_count; ++i_)
        {
            m_vec_glfw_ext_name.push_back((m_glfw_ext_names[i_]));
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
            for (const std::string& ext_ : m_vec_glfw_ext_name)
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
            m_vec_glfw_ext_name.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

            m_create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        }
    }

    void c_vulkan_instance::set_create_info()
    {
        m_create_info.enabledExtensionCount = static_cast<uint32_t>(m_vec_glfw_ext_name.size());
        m_create_info.ppEnabledExtensionNames = m_vec_glfw_ext_name.data();
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

    void c_vulkan_instance::terminate()
    {
        if (m_singleton)
        {
            m_list_singleton.remove(m_singleton);

            delete m_singleton;
            m_singleton = nullptr;
        }
    }
} // namespace owd