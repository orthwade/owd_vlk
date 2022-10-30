#include "owd_object.h"

namespace owd
{
	c_object::c_object(std::wstring_view _name)
		:
		m_name(_name),
		m_logger(_name)
	{

	}

} // namespace owd