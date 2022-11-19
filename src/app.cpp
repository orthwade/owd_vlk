#include "app.h"

namespace owd
{
    c_app *c_app::m_singleton{};

    void c_app::terminate() 
    { 
        if (m_singleton)
        {
            m_list_singleton.remove(m_singleton);

            delete m_singleton;
            m_singleton = nullptr;
        }
    }

    c_app::c_app()
        :
        c_singleton(),
        m_glfw_errors(c_glfw_errors::get_ptr()),
        m_monitors(&c_monitors::get()),
        m_shaders(c_shaders::get_ptr()),
        m_window(&c_window::init()),
        m_vulkan_instance(&c_vulkan_instance::init())
    {
    }

    c_app::~c_app()
    {
        m_window->terminate();
        c_glfw_init::terminate();
    }

} //namespace owd