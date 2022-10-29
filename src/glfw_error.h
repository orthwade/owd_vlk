#pragma once
#include <GLFW/glfw3.h>

#include "owd_lib/owd_lib.h"

namespace owd
{
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
        inline static ptr make(std::wstring_view _name = L"object_name") 
        { return std::make_shared<c_glfw_error>(_name); };

        /// <summary>
        /// Create object.
        /// </summary>
        /// <param name="_name"></param>
        /// <param name="_code"></param>
        /// <param name="_info"></param>
        /// <param name="_analysis"></param>
        c_glfw_error(std::wstring_view _name, int32_t _code, std::wstring_view _info, std::wstring_view _analysis);
        
        /// <summary>
        /// Get numeric code of this error.
        /// </summary>
        /// <returns></returns>
        inline int32_t get_code() const { return m_code; }

        /// <summary>
        /// Get brief description of this error.
        /// </summary>
        /// <returns></returns>
        inline std::wstring_view get_info() const { return m_info; }

        /// <summary>
        /// Get brief explanation of this error source and advice about fixing this error.
        /// </summary>
        /// <returns></returns>
        inline std::wstring_view get_analysis() const { return m_analysis; }

    protected:
        int32_t m_code;
        std::wstring m_info;
        std::wstring m_analysis;
    };

   
} // namespace owd