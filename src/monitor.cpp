#include "monitor.h"

namespace owd
{
	static int monitor_count_;

	c_monitor::c_monitor()
		
	{
	}


	c_monitors::c_monitors()
		:
		m_count(),
		m_ptr_ptr_glfw_monitor(glfwGetMonitors(&m_count))
	{
	}

} // namespace owd