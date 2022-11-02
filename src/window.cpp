#include "window.h"

namespace owd
{
    c_window *c_window::m_singleton{};

    void c_window::init(int32_t _w, int32_t _h, std::string_view _name,
                        const std::vector<s_wnd_hint> &_vec_hint)
    {
        glfwDestroyWindow(m_glfw_wnd);

        for (const s_wnd_hint &hint_ : _vec_hint)
            glfwWindowHint(hint_.hint_id, hint_.value);

        glfwSwapInterval(1);

        m_glfw_wnd = glfwCreateWindow(_w, _h, _name.data(), nullptr, nullptr);
    }

    void c_window::set_func_update_window(const std::function<void()>& _func)
    {
        m_func_update_window = _func;
    }

    void c_window::default_func_update_window()
    {
        glfwPollEvents();
    }

    void c_window::run()
    {
        while (!glfwWindowShouldClose(m_glfw_wnd))
        {
            m_func_update_window();
        }
    }

    void owd::c_window::set_fullscreen()
    {
    }

    void c_window::terminate()
    {
        if (m_singleton)
        {
            m_list_singleton.remove(m_singleton);

            m_singleton->close();

            glfwTerminate();

            delete m_singleton;
            m_singleton = nullptr;
        }
    }

    c_window::c_window()
        :
        c_singleton(),
        m_func_update_window(std::bind(&c_window::default_func_update_window, this)),
        m_glfw_wnd()
    {

    }

} // namespace owd
