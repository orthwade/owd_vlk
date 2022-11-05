#include "monitor.h"

namespace owd
{
	static void monitor_callback(GLFWmonitor* _glfw_monitor, int event)
	{
		c_monitors& monitors_ = c_monitors::get();

		list_t<c_monitor::ptr>& list_monitor = monitors_.get_list_monitor();

		if (event == GLFW_CONNECTED)
		{
			list_monitor.push_back(c_monitor::make(_glfw_monitor));
		}
		else if (event == GLFW_DISCONNECTED)
		{
			for (c_monitor::ptr& monitor : monitors_.get_list_monitor())
			{
				if (monitor->get_glfw_monitor() == _glfw_monitor)
				{
					list_monitor.remove(monitor);
					break;
				}
			}
		}
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

	c_monitor::s_gamma_ramp::s_gamma_ramp(const GLFWgammaramp* _glfw_ramp)
		:
		size(_glfw_ramp->size),
		r(_glfw_ramp->red,   _glfw_ramp->red   + _glfw_ramp->size),
		g(_glfw_ramp->green, _glfw_ramp->green + _glfw_ramp->size),
		b(_glfw_ramp->blue,  _glfw_ramp->blue  + _glfw_ramp->size)
	{

	}
	c_monitor::c_monitor(GLFWmonitor* _glfw_monitor)
		:
		m_glfw_monitor(_glfw_monitor),
		m_vec_vid_mode(),
		m_vid_mode_current(),
		m_phys_size(),
		m_scale(),
		m_pos(),
		m_work_area(),
		m_initial_gamma_ramp(),
		m_gamma_ramp()
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

		GLFW_CALL(glfwGetMonitorPhysicalSize(_glfw_monitor, &m_phys_size.w, &m_phys_size.h));

		GLFW_CALL(glfwGetMonitorContentScale(_glfw_monitor, &m_scale.x, &m_scale.y));

		GLFW_CALL(glfwGetMonitorPos(_glfw_monitor, &m_pos.x, &m_pos.y));

		const char* name_c_str_{};

		GLFW_CALL(name_c_str_ = glfwGetMonitorName(m_glfw_monitor));

		m_name = convert_utf8_to_utf16(name_c_str_);

		const GLFWgammaramp* ramp_{};

		GLFW_CALL(ramp_ = glfwGetGammaRamp(m_glfw_monitor));

		m_initial_gamma_ramp = s_gamma_ramp(ramp_);
		m_gamma_ramp = m_initial_gamma_ramp;
	}

	void c_monitors::update()
	{

	}

	c_monitors::c_monitors()
		:
		m_list_monitor(),
		m_primary()
	{
		bool glfw_init_ = c_glfw_init::init();

		GLFWmonitor** ptr_ptr_monitor{};

		int32_t count_{};

		GLFW_CALL(ptr_ptr_monitor = (glfwGetMonitors(&count_)));

		for (size_t i_ = 0; i_ < count_; ++i_)
		{
			m_list_monitor.push_back(c_monitor::make(*ptr_ptr_monitor));
			++ptr_ptr_monitor;
		}

		if (!m_list_monitor.empty())
		{
			m_primary = m_list_monitor.front();
		}

		GLFW_CALL(glfwSetMonitorCallback(monitor_callback));
	}

} // namespace owd