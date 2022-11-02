#pragma once
#include <unordered_map>
#include <mutex>

#include "owd_lib/owd_lib.h"
#include "glfw_init.h"

namespace owd
{
    struct s_glfw_error
    {
        s_glfw_error(wsv_t _name, wsv_t _info, wsv_t _analysis) : m_name(_name), m_info(_info), m_analysis(_analysis) 
        {}
        std::wstring m_name;
        std::wstring m_info;
        std::wstring m_analysis;
    };

    /// <summary>
    /// Class of GLFW error.
    /// </summary>
    class c_glfw_error : public c_object
    {
    public:
        using ptr = std::shared_ptr<c_glfw_error>;

        /// <summary>
        /// Construct object with given name, 
        /// make shared_ptr of this object class and get this shared_ptr.	
        /// </summary>
        /// <returns></returns>
        inline static ptr make(int32_t _code)
        { return std::make_shared<c_glfw_error>(_code); };

        /// <summary>
        /// Create object.
        /// </summary>
        /// <param name="_code"></param>
        c_glfw_error(int32_t _code);
        
        /// <summary>
        /// Get numeric code of this error.
        /// </summary>
        /// <returns></returns>
        inline int32_t get_code() const { return m_code; }

        /// <summary>
        /// Get brief description of this error.
        /// </summary>
        /// <returns></returns>
        inline wsv_t get_info() const { return m_info; }

        /// <summary>
        /// Get brief explanation of this error source and advice about fixing this error.
        /// </summary>
        /// <returns></returns>
        inline wsv_t get_analysis() const { return m_analysis; }

    protected:
        int32_t m_code;
        std::wstring m_info;
        std::wstring m_analysis;
    };

    /// <summary>
    /// Class of GLFW error manager.
    /// </summary>
    class c_glfw_errors : public c_singleton
    {
    public:
        /// <summary>
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_glfw_errors& get() 
        { return m_singleton ? *m_singleton : (*(m_singleton = new c_glfw_errors)); }

        /// <summary>
        /// Get pointer to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_glfw_errors* const get_ptr() 
        { return m_singleton ? m_singleton : (m_singleton = new c_glfw_errors); }

        const umap_t<int32_t, c_glfw_error>& get_map_error() const { return m_map_error; }

        /// <summary>
        /// Error callback.
        /// </summary>
        void error_callback(int32_t _error_code);

        /// <summary>
        /// Print full error info with given error integer code.
        /// </summary>
        void print_error(int32_t _error_code);

        /// <summary>
        /// Print full error info of the last error.
        /// </summary>
        void print_last_error();

        /// <summary>
        /// Delete this class singleton object.
        /// get() will be required to use this class further.
        /// </summary>
        void terminate() override;

    protected:
        c_logger m_logger;

        c_glfw_errors();

        static c_glfw_errors* m_singleton;

        c_glfw_errors(const c_glfw_errors&) = delete;
        c_glfw_errors& operator=(const c_glfw_errors&) = delete;

        const umap_t<int32_t, c_glfw_error> m_map_error;
    };

   
} // namespace owd