#include "vulkan_instance.h"

namespace owd
{
    c_vulkan_instance* c_vulkan_instance::m_singleton{};

    c_vulkan_instance::c_vulkan_instance()
        :
        m_logger(L"Vulkan"),
        m_instance(),
        m_glfw_init_result(c_glfw_init::init()),
        m_glfw_ext(),
        m_glfw_ext_names(glfwGetRequiredInstanceExtensions(&m_glfw_ext)),
        m_app_info
        (
            {
                VK_STRUCTURE_TYPE_APPLICATION_INFO,
                nullptr,
                nullptr,
                0,
                nullptr,
                0

            }
        ),
        m_create_info
        (
            {
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, // VkStructureType             sType;
                nullptr,                                // const void*                 pNext;
                VkInstanceCreateFlags{},                // VkInstanceCreateFlags       flags;
                &m_app_info,                            // const VkApplicationInfo*    pApplicationInfo;
                0,                                      // uint32_t                    enabledLayerCount;
                nullptr,
                m_glfw_ext,
                m_glfw_ext_names
            }
        ),
        m_result(vkCreateInstance(&m_create_info, nullptr, &m_instance))
    {
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