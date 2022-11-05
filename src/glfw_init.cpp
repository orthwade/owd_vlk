#include "glfw_init.h"

namespace owd
{
	bool c_glfw_init::m_is_initialzed{ false };

    bool c_glfw_init::init()
    {
        GLFW_CALL(m_is_initialzed = (glfwInit() == GLFW_TRUE));
        return m_is_initialzed;
    }

    void c_glfw_init::terminate()
	{
		GLFW_CALL(glfwTerminate());
		m_is_initialzed = false;
	}
} // namespace owd