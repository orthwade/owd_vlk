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
        m_glfw_ext_names(),
        m_app_info(),
        m_create_info(),
        m_result(vkCreateInstance(&m_create_info, nullptr, &m_instance))
    {
        GLFW_CALL(m_glfw_ext_names = glfwGetRequiredInstanceExtensions(&m_glfw_ext));
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