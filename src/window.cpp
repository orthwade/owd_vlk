#include "window.h"

namespace owd
{
    c_window *c_window::m_singleton{};

    void c_window::init(int32_t _w, int32_t _h, std::string_view _name,
                        const std::vector<s_wnd_hint> &_vec_hint)
    {
        glfwDestroyWindow(m_glfw_wnd);

        m_glfw_init_result = glfwInit();

        for (const s_wnd_hint &hint_ : _vec_hint)
            glfwWindowHint(hint_.hint_id, hint_.value);

        m_glfw_wnd = glfwCreateWindow(_w, _h, _name.data(), nullptr, nullptr);
    }

    void c_window::run()
    {
        while (!glfwWindowShouldClose(m_glfw_wnd))
        {
            glfwPollEvents();
        }
    }

    void owd::c_window::set_fullscreen()
    {
    }

    void c_window::terminate()
    {
        close();
        glfwTerminate();
        if (m_singleton)
        {
            delete m_singleton;
            m_singleton = nullptr;
        }
    }

    c_window::c_window()
        :
        m_glfw_init_result(),
        m_glfw_wnd()
    {

    }

} // namespace owd
