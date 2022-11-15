#include "window.h"

namespace owd
{
    c_window *c_window::m_singleton{};

    c_window& c_window::init(int32_t _w, int32_t _h, wsv_t _name,
                        const std::vector<s_wnd_hint> &_vec_hint)
    {
        if (!m_singleton)
        {
            m_singleton = new c_window(_w, _h, _name, _vec_hint);
        }
        
        return *m_singleton;
    }

    void c_window::set_func_update_window(const std::function<void()>& _func)
    {
        m_func_update_window = _func;
    }

    void c_window::default_func_update_window()
    {
        GLFW_CALL_NO_PRINT(glfwPollEvents());
    }

    void c_window::run()
    {
        int32_t window_should_close_{};

        while (true)
        {
            GLFW_CALL_NO_PRINT(window_should_close_ = glfwWindowShouldClose(m_glfw_wnd));

            if (window_should_close_)
            {
                break;
            }

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

            delete m_singleton;
            m_singleton = nullptr;
        }
    }

    c_window::c_window(int32_t _w, int32_t _h, wsv_t _name,
        const std::vector<s_wnd_hint>& _vec_hint)
        :
        c_singleton(_name),
        m_func_update_window(std::bind(&c_window::default_func_update_window, this)),
        m_glfw_wnd(nullptr)
    {
        c_glfw_init::init();

        for (const s_wnd_hint& hint_ : _vec_hint)
            GLFW_CALL(glfwWindowHint(hint_.hint_id, hint_.value));

        std::string str_name_{ convert_utf16_to_utf8(_name) };

        GLFW_CALL(m_glfw_wnd = glfwCreateWindow(_w, _h, str_name_.data(), nullptr, nullptr));
    }
} // namespace owd
