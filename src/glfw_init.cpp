#include "glfw_init.h"

namespace owd
{
	bool c_glfw_init::m_is_initialzed{ false };

	void c_glfw_init::terminate()
	{
		glfwTerminate;
		m_is_initialzed = false;
	}
} // namespace owd