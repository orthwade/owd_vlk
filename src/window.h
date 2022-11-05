#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>
#include <functional>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "owd_lib/owd_lib.h"
#include "glfw_error.h"

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
        /// <summary>
        /// Create singleton object, if not created already. 
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_window& get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_window)); }

        /// <summary>
        /// Create singleton object, if not created already. 
        /// Get pointer to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_window* const get_ptr() 
        { return m_singleton ? m_singleton : (m_singleton = new c_window); }

        /// @brief Open window with given width, height and GLFW hints.
        /// @param _w Window width.
        /// @param _h Window height.
        /// @param _name Window name.
        /// @param _vec_hint Vector of window hints.
        void init(int32_t _w = 500, int32_t _h = 500, std::string_view _name = "Default window",
                  const std::vector<s_wnd_hint>& _vec_hint =
                    {
                        { GLFW_CLIENT_API, GLFW_NO_API },
                        { GLFW_RESIZABLE, GLFW_FALSE }
                    });

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

        /// @brief Close window.
        inline void close() { GLFW_CALL(glfwDestroyWindow(m_glfw_wnd)); }

        /// @brief Close window, terminate GLFW and delete singleton. 
        /// get() will be required to use this class further.
        void terminate() override;

        /// @brief Get GLFW window raw pointer.
        /// @return
        inline GLFWwindow const* const get_glfw_wnd_ptr() const { return m_glfw_wnd; }

    protected:
        c_window();

        std::function<void()> m_func_update_window;

        GLFWwindow* m_glfw_wnd;

        void default_func_update_window();

        //std::vector<c_monitor::ptr> m_vec_monitor;

        static c_window* m_singleton;

        c_window(const c_window&) = delete;
        c_window& operator=(const c_window&) = delete;
    };
} // namespace owd
