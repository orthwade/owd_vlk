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
#include "glfw_init.h"

namespace owd
{
    /// <summary>
    /// Monitor video mode.
    /// </summary>
    class c_video_mode
    {
    public:

        using ptr = ptr_t<c_video_mode>;

        /// <summary>
        /// Construct object of this class with given name and mode, 
        /// make shared_ptr of this object class and get this shared_ptr. 
        /// </summary>
        inline static ptr make(const GLFWvidmode* _glfw_vid_mode) 
        { return std::make_shared<c_video_mode>(_glfw_vid_mode); }

        /// <summary>
        /// Create object.
        /// </summary>
        c_video_mode(const GLFWvidmode* _glfw_vid_mode);

        int32_t get_width()         const { return m_width; }
        int32_t get_height()        const { return m_height; }
        int32_t get_red_bits()      const { return m_red_bits; }
        int32_t get_green_bits()    const { return m_green_bits; }
        int32_t get_blue_bits()     const { return m_blue_bits; }
        int32_t get_refresh_rate()  const { return m_refresh_rate; }

    protected:
        const int32_t m_width;
        const int32_t m_height;
        const int32_t m_red_bits;
        const int32_t m_green_bits;
        const int32_t m_blue_bits;
        const int32_t m_refresh_rate;
    };

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
        inline static ptr make(GLFWmonitor* _glfw_monitor) { return std::make_shared<c_monitor>(_glfw_monitor); }

        /// <summary>
        /// Create object.
        /// </summary>
        /// <param name="_glfw_monitor"></param>
        c_monitor(GLFWmonitor* _glfw_monitor);

        /// <summary>
        /// Get vector of this monitor's video modes.
        /// </summary>
        inline const vec_t<c_video_mode::ptr>& get_vec_vid_mode() const { return m_vec_vid_mode; }

        /// <summary>
        /// Get current video mode.
        /// </summary>
        /// <returns></returns>
        inline const c_video_mode::ptr& get_vid_mode_current() const { return m_vid_mode_current; }

    protected:
        vec_t<c_video_mode::ptr> m_vec_vid_mode;

        c_video_mode::ptr m_vid_mode_current;
    };

    /// <summary>
    /// Monitors manager class.
    /// </summary>
    class c_monitors
    {
    public:
        /// <summary>
        /// Create singleton object, if not created already. 
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_monitors& get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_monitors)); }

        /// <summary>
        /// Create singleton object, if not created already. 
        /// Get pointer to single instance of this class object. 
        /// </summary>
        /// <returns></returns>
        inline static c_monitors* const get_ptr() 
        { return m_singleton ? m_singleton : (m_singleton = new c_monitors); }

        /// <summary>
        /// Get vector of monitor pointers.
        /// </summary>
        /// <returns></returns>
        inline vec_t<c_monitor::ptr>& get_vec_monitor() { return m_vec_monitor; }

        /// <summary>
        /// Get primary monitor.
        /// </summary>
        /// <returns></returns>
        inline c_monitor::ptr& get_primary() { return m_primary; }

        /// <summary>
        /// Update monitor info.
        /// </summary>
        void update();

    protected:
        vec_t<c_monitor::ptr> m_vec_monitor;

        c_monitor::ptr m_primary;

        static c_monitors* m_singleton;

        c_monitors();

        c_monitors(const c_monitors&) = delete;
        c_monitors& operator=(const c_monitors&) = delete;
    };
} // namespace owd