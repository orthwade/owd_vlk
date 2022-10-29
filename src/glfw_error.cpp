#include "glfw_init.h"
#include "glfw_error.h"

namespace owd
{
	c_glfw_error::c_glfw_error
	(std::wstring_view _name, int32_t _code, std::wstring_view _info, std::wstring_view _analysis)
		:
		c_object(_name),
		m_code(_code),
		m_info(_info),
		m_analysis(_analysis)
	{
	}
} // namespace owd