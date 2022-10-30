#pragma once
#include <string_view>

#include "../owd_lib/owd_lib.h"

namespace owd
{
    static const std::wstring shader_folder_path_{ current_path_str_ + L"/shader/" };

    static const std::wstring vertex_shader_filename_{ L"vertex.spv" };
    static const std::wstring fragment_shader_filename_{ L"fragment.spv" };

    static const std::wstring vertex_shader_filepath_{ shader_folder_path_ + vertex_shader_filename_ };
    static const std::wstring fragment_shader_filepath_{ shader_folder_path_ + fragment_shader_filename_ };

    /// <summary>
    /// Shader object loaded from SPIR-V file.
    /// </summary>
    class c_shader : public c_file
    {
    public:
        using ptr = std::shared_ptr<c_shader>;

        /// <summary>
        /// Construct object and store data from file with given filepath and name, 
        /// make shared_ptr of this object class and get this shared_ptr.		
        /// </summary>
        /// <param name="_filepath"></param>
        /// <param name="_filename">Name of this object. 
        /// Not related to the filepath or name of the file in the filesystem</param>
        /// <returns></returns>
        inline static ptr make(std::wstring_view _filepath, std::wstring_view _filename = L"file_name")
        {
            return std::make_shared<c_shader>(_filepath, _filename);
        }

        /// <summary>
        /// Construct object of this class, 
        /// Make shared_ptr of this object class and get this shared_ptr. 
        /// </summary>
        /// <returns></returns>
        inline static ptr make() { return std::make_shared<c_shader>(); }

        /// <summary>
        /// Construct object and store data from file.
        /// </summary>
        /// <param name="_filepath"></param>
        /// <param name="_shadername">Name of this object. 
        /// Not related to the filepath or name of the file in the filesystem.</param>
        c_shader(std::wstring_view _filepath, std::wstring_view _shadername = L"shader_name");  

        /// <summary>
        /// construct object.
        /// </summary>
        c_shader();

    protected:

    };

    /// <summary>
    /// Singleton class used to handle GLSL shaders.
    /// set_shader_folder_path has to be called before other methods.
    /// </summary>
    class c_shaders
    {
    public:
        using ptr = std::shared_ptr<c_shader>;

        /// <summary>
        /// Set shader folder path.
        /// </summary>
        /// <param name="_shader_folder_path"></param>
        static void set_shader_folder_path(std::wstring_view _shader_folder_path);
        

        /// <summary>
        /// Create singleton object if not created already.
        /// Get reference to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_shaders& get() { return m_singleton ? *m_singleton : (*(m_singleton = new c_shaders)); }

        /// <summary>
        /// Create singleton object if not created already.
        /// Get pointer to single instance of this class object.
        /// </summary>
        /// <returns></returns>
        inline static c_shaders* const get_ptr()
        {
            return m_singleton ? m_singleton : (m_singleton = new c_shaders);
        }

        /// @brief Delete singleton.
        /// get() will be required to use this class further.
        void terminate();

    protected:
        c_shader::ptr m_vertex_shader;
        c_shader::ptr m_fragment_shader;

        const std::wstring m_shader_folder_path;

        const std::wstring m_vertex_shader_filename;
        const std::wstring m_fragment_shader_filename;

        const std::wstring m_vertex_shader_filepath;
        const std::wstring m_fragment_shader_filepath;

        c_shaders();

        static c_shaders* m_singleton;

        c_shaders(const c_shaders&) = delete;
        c_shaders& operator=(const c_shaders&) = delete;
    };
} // namespace owd
