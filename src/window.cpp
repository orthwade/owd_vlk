#include "window.h"

namespace owd
{
    void c_window::init(int32_t _w, int32_t _h, std::string_view _name,
                        const std::vector<s_wnd_hint> &_vec_hint)
    {
        glfwDestroyWindow(m_glfw_wnd);
        m_glfw_init_result =  glfwInit();
        for (const s_wnd_hint &hint : _vec_hint)
            glfwWindowHint(hint.hint_id, hint.value);

        m_glfw_wnd = glfwCreateWindow(_w, _h, _name.data(), nullptr, nullptr);
    }

    void c_window::process()
    {
        while (!glfwWindowShouldClose(m_glfw_wnd))
        {
            glfwPollEvents();
        }
    }
} // namespace owd
