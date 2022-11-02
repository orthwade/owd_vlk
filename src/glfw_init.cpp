#include "glfw_init.h"

namespace owd
{
	bool c_glfw_init::m_glfw_init_result{ false };

	void c_glfw_init::terminate()
	{
		glfwTerminate;
		m_glfw_init_result = false;
	}
} // namespace owd