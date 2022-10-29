#pragma once 
#include "owd_filesystem.h"

namespace owd
{
	/// <summary>
	/// Class of logger. This logger able is able to output text to console and file.
	/// </summary>
	class c_logger : public c_object
	{
	public:
		using ptr = std::shared_ptr<c_logger>;
		
		/// <summary>
		/// Logger mode
		/// </summary>
		enum class enm_mode
		{
			none,
			console,
			file,
			both
		};

		static const enm_mode none	 { enm_mode::none };
		static const enm_mode console{ enm_mode::console };
		static const enm_mode file	 { enm_mode::file };
		static const enm_mode both	 { enm_mode::both };

		/// <summary>
		/// Construct logger with given name and mode.
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_mode"></param>
		c_logger(std::wstring_view _name = L"logger", enm_mode _mode = none);

		/// <summary>
		/// Construct object of this class with given name and mode, 
		/// make shared_ptr of this object class and get this shared_ptr. 
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_mode"></param>
		/// <returns></returns>
		inline static ptr make(std::wstring_view _name = L"logger", enm_mode _mode = none)
		{
			return std::make_shared<c_logger>(_name, _mode);
		}
		
		inline enm_mode get_mode() const { return m_mode; }

	protected:
		enm_mode m_mode;
		std::wstring m_filepath;
	};
} // namespace owd

