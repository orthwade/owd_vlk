#include "owd_object.h"

namespace owd
{
	c_object::c_object(std::wstring_view _name)
		:
		m_name(_name),
		m_logger(_name)
	{

	}

	void c_object::set_name(std::wstring_view _name) 
	{
		m_name = _name;
		m_logger.set_name(_name);
	}

} // namespace owd