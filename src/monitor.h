#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <vector>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

namespace owd
{
    /// <summary>
/// Class of monitor info.
/// </summary>
    class c_monitor
    {
    public:
        using ptr = std::shared_ptr<c_monitor>;

        /// <summary>
        /// Construct object of this class, 
        /// Make shared_ptr of this object class and get this shared_ptr. 
        /// </summary>
        /// <returns></returns>
        inline static ptr make() { return std::make_shared<c_monitor>(); }

        c_monitor();

    protected:
    };

    /// <summary>
    /// Monitors manager class.
    /// </summary>
    class c_monitors
    {
    public:
        c_monitors();

    protected:
        int m_count;
        GLFWmonitor** m_ptr_ptr_glfw_monitor;
    };
} // namespace owd