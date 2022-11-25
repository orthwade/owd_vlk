#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <functional>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "owd_lib/owd_lib.h"
#include "glfw_error.h"
#include "glfw_init.h"

namespace owd
{
    struct s_wnd_hint
    {
        int32_t hint_id{};
        int32_t value{};
    };

    /// @brief Singleton GLFW Window class used to handle window options.
    class c_window : public c_singleton
    {
    public:

        struct s_frame_buffer
        {
            int32_t w;
            int32_t h;
        };

        /// <summary>
        /// Create singleton object, if not created already. 
        /// Open window with given width, height and GLFW hints.
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <param name="_w"></param>
        /// <param name="_h"></param>
        /// <param name="_name"></param>
        /// <param name="_vec_hint"></param>
        static c_window& init(int32_t _w = 500, int32_t _h = 500, wsv_t _name = L"Default window",
                  const std::vector<s_wnd_hint>& _vec_hint =
                    {
                        { GLFW_CLIENT_API, GLFW_NO_API },
                        { GLFW_RESIZABLE, GLFW_FALSE }
                    });

        /// <summary>
        /// Same as c_window::init, but with default c_window::init parameters.
        /// </summary>
        inline static c_window& get() { return m_singleton ? *m_singleton : *(m_singleton = &init()); }

        /// <summary>
        /// Get true if window is created, false, otherwise.
        /// </summary>
        bool is_initialized() const { return static_cast<bool>(m_glfw_wnd); }

        /// <summary>
        /// Set window update function.
        /// </summary>
        void set_func_update_window(const std::function<void()>& _func);

        /// @brief Start updating window.
        void run();

        /// <summary>
        /// Set windows mode to fullscreen.
        /// </summary>
        void set_fullscreen();

        /// <summary>
        /// Get frame buffer.
        /// </summary>
        s_frame_buffer get_frame_buffer();

        /// @brief Close window.
        inline void close() { GLFW_CALL(glfwDestroyWindow(m_glfw_wnd)); }

        /// @brief Close window, terminate GLFW and delete singleton. 
        /// get() will be required to use this class further.
        void terminate() override;

        /// @brief Get GLFW window raw pointer.
        /// @return
        inline GLFWwindow* const get_glfw_wnd_ptr() const { return m_glfw_wnd; }

    protected:
        c_window(int32_t _w, int32_t _h, wsv_t _name,
            const std::vector<s_wnd_hint>& _vec_hint);

        std::function<void()> m_func_update_window;

        GLFWwindow* m_glfw_wnd;

        vec_t<s_wnd_hint> m_vec_hint;

        void default_func_update_window();

        //std::vector<c_monitor::ptr> m_vec_monitor;

        static c_window* m_singleton;

        c_window(const c_window&) = delete;
        c_window& operator=(const c_window&) = delete;
    };
} // namespace owd
