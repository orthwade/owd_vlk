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
        m_vec_instance_ext_name
        ({
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME
        }),
        m_vec_layer_name
        ({
            "VK_LAYER_GOOGLE_threading",
            "VK_LAYER_LUNARG_parameter_validation",
            "VK_LAYER_LUNARG_device_limits",
            "VK_LAYER_LUNARG_object_tracker",
            "VK_LAYER_LUNARG_image",
            "VK_LAYER_LUNARG_core_validation",
            "VK_LAYER_LUNARG_swapchain",
            "VK_LAYER_GOOGLE_unique_objects"
        })
    {
        m_glfw_init_result = c_glfw_init::init();

        GLFW_CALL(m_glfw_ext_names = glfwGetRequiredInstanceExtensions(&m_glfw_ext_count));

        for (size_t i_ = 0; i_ < m_glfw_ext_count; ++i_)
        {
            m_vec_glfw_ext_name.push_back(std::string(m_glfw_ext_names[i_]));
        }

        m_create_info.enabledExtensionCount = m_glfw_ext_count;
        m_create_info.ppEnabledExtensionNames = m_glfw_ext_names;
        m_create_info.enabledLayerCount = 0;

        uint32_t supported_ext_count_ = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, nullptr);

        std::vector<VkExtensionProperties> vec_supported_ext_(supported_ext_count_);

        vkEnumerateInstanceExtensionProperties(nullptr, &supported_ext_count_, vec_supported_ext_.data());

        for (const VkExtensionProperties& supported_ext_ : vec_supported_ext_)
        {
            if (supported_ext_.extensionName == VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)
            {
                m_vec_glfw_ext_name.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

                m_create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

                break;
            }
        }

        std::vector<const char*> vec_ext_name_{};

        for (const std::string& str_ext_name_ : m_vec_glfw_ext_name)
        {
            vec_ext_name_.push_back(str_ext_name_.c_str());
        }

        m_create_info.enabledExtensionCount = static_cast<uint32_t>(vec_ext_name_.size());
        m_create_info.ppEnabledExtensionNames = vec_ext_name_.data();

        m_create_result = vkCreateInstance(&m_create_info, nullptr, &m_instance);

        if (m_create_result != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create instance!");
        }

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