#include "glfw_error.h"

namespace owd
{
	static const std::unordered_map<int32_t, s_glfw_error> map_int_info_glfw_error
	{
{ 
GLFW_NO_ERROR, 
s_glfw_error
{	
L"GLFW_NO_ERROR",
L"No error has occurred.",
L"Yay."
}
},
{
GLFW_NOT_INITIALIZED,
s_glfw_error
{
L"GLFW_NOT_INITIALIZED",
L"This occurs if a GLFW function was called that must not be called \
unless the library is initialized.",
L"Application programmer error. \
Initialize GLFW before calling any function that requires initialization."
}
},
{
GLFW_NO_CURRENT_CONTEXT,
s_glfw_error
{
L"GLFW_NO_CURRENT_CONTEXT",
L"This occurs if a GLFW function was called that needs and operates on the current OpenGL \
or OpenGL ES context but no context is current on the calling thread. \
One such function is glfwSwapInterval.",
L"Application programmer error. \
Ensure a context is current before calling functions that require a current context."
}
},
{
GLFW_INVALID_ENUM,
s_glfw_error
{
L"GLFW_INVALID_ENUM",
L"One of the arguments to the function was an invalid enum value, \
for example requesting GLFW_RED_BITS with glfwGetWindowAttrib.",
L"Application programmer error. Fix the offending call."
}
},
{
GLFW_INVALID_VALUE,
s_glfw_error
{
L"GLFW_INVALID_VALUE",
L"One of the arguments to the function was an invalid value, \
for example requesting a non-existent OpenGL or OpenGL ES version like 2.7.\n\
Requesting a valid but unavailable OpenGL or OpenGL ES version \
will instead result in a GLFW_VERSION_UNAVAILABLE error.",
L"Application programmer error. Fix the offending call."
}
},
{
GLFW_OUT_OF_MEMORY,
s_glfw_error
{
L"GLFW_OUT_OF_MEMORY",
L"A memory allocation failed.",
L"A bug in GLFW or the underlying operating system. Report the bug to our issue tracker."
}
},
{
GLFW_API_UNAVAILABLE,
s_glfw_error
{
L"GLFW_API_UNAVAILABLE",
L"GLFW could not find support for the requested API on the system.",
L"The installed graphics driver does not support the requested API, \
or does not support it via the chosen context creation backend. Below are a few examples.\n\
Some pre - installed Windows graphics drivers do not support OpenGL. \
AMD only supports OpenGL ES via EGL, while Nvidiaand Intel only support it via a WGL \
or GLX extension.macOS does not provide OpenGL ES at all.The Mesa EGL, \
OpenGLand OpenGL ES libraries do not interface with the Nvidia binary driver. \
Older graphics drivers do not support Vulkan."
}
},
{
GLFW_VERSION_UNAVAILABLE,
s_glfw_error
{
L"GLFW_VERSION_UNAVAILABLE",
L"The requested OpenGL or OpenGL ES version (including any requested context or framebuffer hints) \
is not available on this machine.",
L"The machine does not support your requirements. \
If your application is sufficiently flexible, downgrade your requirements and try again. \
Otherwise, inform the user that their machine does not match your requirements.\n\
Future invalid OpenGL and OpenGL ES versions, \
for example OpenGL 4.8 if 5.0 comes out before the 4.x series gets that far, \
also fail with this error and not GLFW_INVALID_VALUE, \
because GLFW cannot know what future versions will exist."
}
},
{
GLFW_PLATFORM_ERROR,
s_glfw_error
{
L"GLFW_PLATFORM_ERROR",
L"A platform-specific error occurred that does not match any of the more specific categories.",
L"A bug or configuration error in GLFW, the underlying operating system or its drivers, \
or a lack of required resources. Report the issue to our issue tracker."
}
},
{
GLFW_FORMAT_UNAVAILABLE,
s_glfw_error
{
L"GLFW_FORMAT_UNAVAILABLE",
L"If emitted during window creation, the requested pixel format is not supported.\n\
If emitted when querying the clipboard, \
the contents of the clipboard could not be converted to the requested format.",
L"If emitted during window creation, \
one or more hard constraints did not match any of the available pixel formats. \
If your application is sufficiently flexible, downgrade your requirements and try again. \
Otherwise, inform the user that their machine does not match your requirements.\n\
If emitted when querying the clipboard, ignore the error or report it to the user, as appropriate."
}
},
{
GLFW_NO_WINDOW_CONTEXT,
s_glfw_error
{
L"GLFW_NO_WINDOW_CONTEXT",
L"A window that does not have an OpenGL or OpenGL ES context was passed to a function \
that requires it to have one.",
L"Application programmer error. Fix the offending call."
}
},
{
GLFW_CURSOR_UNAVAILABLE,
s_glfw_error
{
L"GLFW_CURSOR_UNAVAILABLE",
L"",
L""
}
},
{
GLFW_FEATURE_UNAVAILABLE,
s_glfw_error
{
L"GLFW_FEATURE_UNAVAILABLE",
L"The requested feature is not provided by the platform.\n\
The requested feature is not provided by the platform, so GLFW is unable to\
implement it.The documentation for each function notes if it could emit\
this error.",
L"Platform or platform version limitation. \
The error can be ignored unless the feature is critical to the application."
}
},
{
GLFW_FEATURE_UNIMPLEMENTED,
s_glfw_error
{
L"GLFW_FEATURE_UNIMPLEMENTED",
L"The requested feature is not implemented for the platform.\n\
	The requested feature has not yet been implemented in GLFW for this platform.",
L"An incomplete implementation of GLFW for this platform, hopefully\
fixed in a future release.The error can be ignored unless the feature is \
critical to the application."
}
},
{
GLFW_PLATFORM_UNAVAILABLE,
s_glfw_error
{
L"GLFW_PLATFORM_UNAVAILABLE",
L"Platform unavailable or no matching platform was found.\n\
If emitted during initialization, no matching platform was found.If @ref\
GLFW_PLATFORM is set to `GLFW_ANY_PLATFORM`, GLFW could not detect any of the\
platforms supported by this library binary, except for the Null platform.If set to\
a specific platform, it is either not supported by this library binary or GLFW was not\
able to detect it.\n\
If emitted by a native access function, GLFW was initialized for a different platform\
than the function is for.",
L"Failure to detect any platform usually only happens on non-macOS Unix\
systems, either when no window system is running or the program was run from\
a terminal that does not have the necessary environment variables.Fall back to\
a different platform if possible or notify the user that no usable platform was\
detected.\n\
Failure to detect a specific platform may have the same cause as above or be because\
support for that platform was not compiled in.Call @ref glfwPlatformSupported to\
check whether a specific platform is supported by a library binary."
}
}
		
	};

	c_glfw_errors* c_glfw_errors::m_singleton{};

	c_glfw_error::c_glfw_error(int32_t _code)
		:
		c_object(map_int_info_glfw_error.at(_code).m_name),
		m_code(_code),
		m_info(map_int_info_glfw_error.at(_code).m_info),
		m_analysis(map_int_info_glfw_error.at(_code).m_analysis)
	{
	}
	
	static void static_glfw_error_callback(int32_t _code, const char* _description)
	{
		c_glfw_errors* glfw_errors_ = c_glfw_errors::get_ptr();

		glfw_errors_->print_error(_code);
	}
	
	c_glfw_errors::c_glfw_errors()
		:
		c_singleton(),
		m_glfw_init(c_glfw_init::get_ptr()),
		m_logger(L"glfw_errors"),
		m_map_error
		(
			{
				{ GLFW_NO_ERROR,			  c_glfw_error{ GLFW_NO_ERROR				}},
				{ GLFW_NOT_INITIALIZED,		  c_glfw_error{ GLFW_NOT_INITIALIZED		}},
				{ GLFW_NO_CURRENT_CONTEXT,	  c_glfw_error{ GLFW_NO_CURRENT_CONTEXT		}},
				{ GLFW_INVALID_ENUM,		  c_glfw_error{ GLFW_INVALID_ENUM			}},
				{ GLFW_INVALID_VALUE,		  c_glfw_error{ GLFW_INVALID_VALUE			}},
				{ GLFW_OUT_OF_MEMORY,		  c_glfw_error{ GLFW_OUT_OF_MEMORY			}},
				{ GLFW_API_UNAVAILABLE,		  c_glfw_error{ GLFW_API_UNAVAILABLE		}},
				{ GLFW_VERSION_UNAVAILABLE,	  c_glfw_error{ GLFW_VERSION_UNAVAILABLE	}},
				{ GLFW_PLATFORM_ERROR,		  c_glfw_error{ GLFW_PLATFORM_ERROR			}},
				{ GLFW_FORMAT_UNAVAILABLE,	  c_glfw_error{ GLFW_FORMAT_UNAVAILABLE		}},
				{ GLFW_NO_WINDOW_CONTEXT,	  c_glfw_error{ GLFW_NO_WINDOW_CONTEXT		}},
				{ GLFW_CURSOR_UNAVAILABLE,	  c_glfw_error{ GLFW_CURSOR_UNAVAILABLE		}},
				{ GLFW_CURSOR_UNAVAILABLE,	  c_glfw_error{ GLFW_CURSOR_UNAVAILABLE		}},
				{ GLFW_FEATURE_UNIMPLEMENTED, c_glfw_error{ GLFW_FEATURE_UNIMPLEMENTED	}},
				{ GLFW_PLATFORM_UNAVAILABLE,  c_glfw_error{ GLFW_PLATFORM_UNAVAILABLE	}}
			}
		)
	{
		glfwSetErrorCallback(static_glfw_error_callback);
	}

	void c_glfw_errors::print_error(int32_t _error_code)
	{
		std::mutex mtx_{};
		std::lock_guard lg_{ mtx_ };
		
		const c_glfw_error& error_{ m_map_error.at(_error_code) };

		m_logger
			<< L"Last error:\n"
			<< L"Name: " << error_.get_name() << L";\n"
			<< L"Description: " << error_.get_info() << L";\n"
			<< L"Analysis: " << error_.get_analysis() << L'\n';
		glfwGetError(nullptr);
	}

	void c_glfw_errors::print_last_error()
	{
		print_error(glfwGetError(nullptr));
	}

	void c_glfw_errors::terminate()
	{
		if (m_singleton)
		{
			m_list_singleton.remove(m_singleton);

			delete m_singleton;
			m_singleton = nullptr;
		}
	}
} // namespace owd