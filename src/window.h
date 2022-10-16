#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace owd
{
    struct s_wnd_hint
    {
        s_wnd_hint(int32_t _hint_id, int32_t _value) : hint_id(_hint_id), value(_value) {}
        int32_t hint_id{};
        int32_t value{};
    };

    /// @brief Singleton GLFW Window class used to handle window options.
    class c_window
    {
    public:
        /// @brief Get reference to single instance of this class object.
        inline static c_window &get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_window)); }

        /// @brief Open window with given width, height and GLFW hints.
        /// @param _w Window width.
        /// @param _h Window height.
        /// @param _name Window name.
        /// @param _vec_hint Vector of window hints.
        void init(int32_t _w = 500, int32_t _h = 500, std::string_view _name = "Default window",
                  const std::vector<s_wnd_hint> &_vec_hint =
                    {
                        { GLFW_CLIENT_API, GLFW_NO_API },
                        { GLFW_RESIZABLE, GLFW_FALSE }
                    });

        /// @brief Start updating window.
        void process();

        /// @brief Close window.
        inline void close() { glfwDestroyWindow(m_glfw_wnd); }

        /// @brief Close window, terminate GLFW and delete singleton. 
        /// get() will be required to use this class further.
        void terminate();

        /// @brief Get GLFW window raw pointer.
        /// @return
        inline GLFWwindow *get_glfw_wnd_ptr() { return m_glfw_wnd; }

        c_window(const c_window &) = delete;
        c_window &operator=(const c_window &) = delete;

    protected:
        c_window() {}

        int32_t m_glfw_init_result{};

        GLFWwindow *m_glfw_wnd{};

        static c_window *m_singleton;
    };
} // namespace owd
