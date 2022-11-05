#include "monitor.h"

namespace owd
{
	static void monitor_callback(GLFWmonitor* monitor, int event)
	{
		c_monitors::get().update();
	}
	c_video_mode::c_video_mode(const GLFWvidmode* _glfw_vid_mode)
		:
		m_width		  (_glfw_vid_mode->width),
		m_height	  (_glfw_vid_mode->height),
		m_red_bits	  (_glfw_vid_mode->redBits),
		m_green_bits  (_glfw_vid_mode->greenBits),
		m_blue_bits	  (_glfw_vid_mode->blueBits),
		m_refresh_rate(_glfw_vid_mode->refreshRate)
	{
	}

	c_monitors* c_monitors::m_singleton{};

	c_monitor::c_monitor(GLFWmonitor* _glfw_monitor)
		:
		m_vec_vid_mode(),
		m_vid_mode_current()
	{
		bool glfw_init_ = c_glfw_init::init();

		int32_t vid_mode_count_{};

		const GLFWvidmode* ptr_glfw_vid_mode_{};

		GLFW_CALL(ptr_glfw_vid_mode_ = glfwGetVideoModes(_glfw_monitor, &vid_mode_count_));

		for (size_t i_ = 0; i_ < vid_mode_count_; ++i_)
		{
			m_vec_vid_mode.push_back(c_video_mode::make(ptr_glfw_vid_mode_));
			++ptr_glfw_vid_mode_;
		}

		ptr_glfw_vid_mode_ = glfwGetVideoMode(_glfw_monitor);

		m_vid_mode_current = c_video_mode::make(ptr_glfw_vid_mode_);
	}

	void c_monitors::update()
	{
		bool glfw_init_ = c_glfw_init::init();

		m_vec_monitor.clear();

		GLFWmonitor** ptr_ptr_monitor{};

		int32_t count_{};

		GLFW_CALL(ptr_ptr_monitor = (glfwGetMonitors(&count_)));

		for (size_t i_ = 0; i_ < count_; ++i_)
		{
			m_vec_monitor.push_back(c_monitor::make(*ptr_ptr_monitor));
			++ptr_ptr_monitor;
		}

		if (!m_vec_monitor.empty())
		{
			m_primary = m_vec_monitor.front();
		}
	}

	c_monitors::c_monitors()
		:
		m_vec_monitor(),
		m_primary()
	{
		update();
		GLFW_CALL(glfwSetMonitorCallback(monitor_callback));
	}

} // namespace owd