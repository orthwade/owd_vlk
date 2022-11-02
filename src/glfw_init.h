#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "owd_lib/owd_lib.h"

namespace owd
{
    /// <summary>
    /// Static method only class to init or terminate GLFW.
    /// </summary>
    class c_glfw_init : public c_singleton
    {
    public:
        /// <summary>
        /// Init GLFW and get
        /// </summary>
        /// <returns></returns>
        inline static bool init() { return m_glfw_init_result = (glfwInit() == GLFW_TRUE) ? true : false; }

        /// <summary>
        /// Get GLFW init result int code.
        /// </summary>
        /// <returns></returns>
        inline static bool get_init_result_int() { return m_glfw_init_result; }

        /// <summary>
        /// Terminate GLFW.
        /// </summary>
        static void terminate();

    protected:
        c_glfw_init() = delete;

        static bool m_glfw_init_result;
    };

   
} // namespace owd