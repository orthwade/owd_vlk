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

    /// @brief GLFW Window class used to handle window options.
    class c_window
    {
    public:
        using ptr = std::shared_ptr<c_window>;

        /// @brief Constructs window object.
        c_window() {}

        /// @brief Make shared_ptr of this class object.
        inline static ptr make() { return std::make_shared<c_window>(); }

        /// @brief Initialize window with given width and height.
        /// @param _w Window width.
        /// @param _h Window height.
        /// @param _name Window name.
        /// @param _vec_hint Vector of window hints.
        void init(int32_t _w = 500, int32_t _h = 500, std::string_view _name = "Vulkan window",
                  const std::vector<s_wnd_hint> &_vec_hint = {});
        
        /// @brief Start updating window.
        void process();

        /// @brief Destroy window.
        inline void close() { glfwDestroyWindow(m_glfw_wnd); }

        /// @brief Close window and terminate GLFW.
        inline void terminate() { close(); glfwTerminate(); }

        /// @brief Get GLFW window raw pointer.
        /// @return
        inline GLFWwindow *get_glfw_wnd_ptr() { return m_glfw_wnd; }

    protected:
        int32_t m_glfw_init_result{};

        GLFWwindow *m_glfw_wnd{};
    };
} // namespace owd
