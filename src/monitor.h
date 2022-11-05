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
    class c_monitor : public c_object
    {
    public:
        /// <summary>
        /// Monitor physical size in millimitres.
        /// </summary>
        struct s_phys_size
        {
            int32_t w; // Width.
            int32_t h; // Height.
        };

        /// <summary>
        /// Monitor content scale.
        /// The content scale is the ratio between the current DPI and the platform's default DPI. 
        /// This is especially important for text and any UI elements. 
        /// If the pixel dimensions of your UI scaled by this look appropriate on your machine 
        /// then it should appear at a reasonable size on other machines regardless of their DPI and scaling settings. 
        /// This relies on the system DPI and scaling settings being somewhat correct.
        /// The content scale may depend on both the monitor resolutionand pixel densityand on user settings.
        /// It may be very different from the raw DPI calculated from the physical sizeand current resolution.
        /// </summary>
        struct s_scale
        {
            float x; // Horizontal scale.
            float y; // Vertical scael.
        };

        /// <summary>
        /// The position of the monitor on the virtual desktop, in screen coordinates.
        /// </summary>
        struct s_pos
        {
            int32_t x; // Horizontal coordinate.
            int32_t y; // Vertical coordinate.
        };
        
        /// <summary>
        /// The area of a monitor not occupied by global task bars or menu bars is the work area. 
        /// This is specified in screen coordinates.
        /// </summary>
        struct s_work_area
        {
            int32_t x; // Horizontal coordinate.
            int32_t y; // Vertical coordinate.
            int32_t w; // Width.
            int32_t h; // Height.
        };

        /// <summary>
        /// Monitor gamma ramp.
        /// </summary>
        struct s_gamma_ramp
        {
            s_gamma_ramp(const GLFWgammaramp* _glfw_ramp);
            s_gamma_ramp() : size(), r(), g(), b() {};
            uint32_t size; // The number of elements in each vector.
            vec_t<uint32_t> r; // A vector of value of the response of the red channel.
            vec_t<uint32_t> g; // A vector of value of the response of the green channel.
            vec_t<uint32_t> b; // A vector of value of the response of the blue channel.
        };

        using ptr = ptr_t<c_monitor>;

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

        GLFWmonitor* const get_glfw_monitor() const { return m_glfw_monitor; }

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
        GLFWmonitor* m_glfw_monitor;

        vec_t<c_video_mode::ptr> m_vec_vid_mode;

        c_video_mode::ptr m_vid_mode_current;

        s_phys_size m_phys_size;

        s_scale m_scale;

        s_pos m_pos;

        s_work_area m_work_area;

        s_gamma_ramp m_initial_gamma_ramp;
        s_gamma_ramp m_gamma_ramp;

        inline virtual void set_name(wsv_t) override {};
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
        inline list_t<c_monitor::ptr>& get_list_monitor() { return m_list_monitor; }

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
        list_t<c_monitor::ptr> m_list_monitor;

        c_monitor::ptr m_primary;

        static c_monitors* m_singleton;

        c_monitors();

        c_monitors(const c_monitors&) = delete;
        c_monitors& operator=(const c_monitors&) = delete;
    };
} // namespace owd