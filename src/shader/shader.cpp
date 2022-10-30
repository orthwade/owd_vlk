#include "shader.h"

namespace owd
{
	c_shader::c_shader(std::wstring_view _filepath, std::wstring_view _shadername)
		:
		c_file(_filepath, _shadername)
	{
	}

	c_shader::c_shader()
	{
	}

	c_shaders* c_shaders::m_singleton{};

	void c_shaders::set_shader_folder_path(std::wstring_view _shader_folder_path)
	{
	
	}

	void c_shaders::terminate()
	{
		if (m_singleton)
		{
			m_list_singleton.remove(m_singleton);

			delete m_singleton;
			m_singleton = nullptr;
		}
	}

	c_shaders::c_shaders()
		:
		c_singleton(),

		m_shader_folder_path(shader_folder_path_),

		m_vertex_shader_filename  (vertex_shader_filename_),
		m_fragment_shader_filename(fragment_shader_filename_),

		m_vertex_shader_filepath  (vertex_shader_filepath_),
		m_fragment_shader_filepath(fragment_shader_filepath_),

		m_vertex_shader  (c_shader::make(vertex_shader_filepath_,   L"vertex_shader")),
		m_fragment_shader(c_shader::make(fragment_shader_filepath_, L"fragment_shader"))
	{

	}
	
} // namespace owd