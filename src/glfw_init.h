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
    class c_glfw_init
    {
    public:
        /// <summary>
        /// Create singleton object and init GLFW, if not created already. 
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_glfw_init& get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_glfw_init)); }

        /// <summary>
        /// Create singleton object and init GLFW, if not created already. 
        /// Get pointer to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_glfw_init* const get_ptr() 
        { return m_singleton ? m_singleton : (m_singleton = new c_glfw_init); }

        /// <summary>
        /// Get GLFW init result int code.
        /// </summary>
        /// <returns></returns>
        inline int32_t get_init_result_int() const { return m_glfw_init_result; }

        /// @brief Terminate GLFW. Delete singleton. 
        /// get() will be required to use this class further.
        void terminate();

    protected:
        /// <summary>
        /// Create object and init GLFW.
        /// </summary>
        c_glfw_init();

        int32_t m_glfw_init_result;

        static c_glfw_init* m_singleton;
    };

   
} // namespace owd