#include "glfw_init.h"

namespace owd
{
	c_glfw_init* c_glfw_init::m_singleton{};

	void c_glfw_init::terminate()
	{
		if (m_singleton)
		{
			m_list_singleton.remove(m_singleton);

			glfwTerminate();

			delete m_singleton;
			m_singleton = nullptr;
		}
	}

	c_glfw_init::c_glfw_init()
		:
		c_singleton(),
		m_glfw_init_result(glfwInit())
	{
	}

} // namespace owd