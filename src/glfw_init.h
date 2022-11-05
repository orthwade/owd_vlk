#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "owd_lib/owd_lib.h"
#include "glfw_error.h"

namespace owd
{
    /// <summary>
    /// Static method only class to init or terminate GLFW.
    /// </summary>
    class c_glfw_init : public c_singleton
    {
    public:
        /// <summary>
        /// Init GLFW. Get true if initialized succesfully, get false otherwise.
        /// </summary>
        /// <returns></returns>
        static bool init();

        /// <summary>
        /// Get GLFW init result int code.
        /// </summary>
        /// <returns></returns>
        inline static bool is_initialized() { return m_is_initialzed; }

        /// <summary>
        /// Terminate GLFW.
        /// </summary>
        static void terminate();

    protected:
        c_glfw_init() = delete;

        static bool m_is_initialzed;
    };

   
} // namespace owd