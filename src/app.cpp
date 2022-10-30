#include "app.h"

namespace owd
{
    c_app *c_app::m_singleton{};

    /// <summary>
    /// Terminate the app. Close the window, terminate GLFW and delete this class singleton object.
    /// </summary>
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
        m_shaders(c_shaders::get_ptr()),
        m_window(c_window::get_ptr())
    {
        m_window->init();
    }

    c_app::~c_app()
    {
        m_window->terminate();
    }

} //namespace owd