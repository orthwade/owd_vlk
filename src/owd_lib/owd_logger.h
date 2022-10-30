#pragma once 
#include <iostream>
#include <filesystem>

//#include "owd_filesystem.h"
#include "owd_time.h"
#include "owd_output.h"

namespace owd
{
	/// <summary>
	/// Class of logger. This logger uses operator<< to output to console and/or file.
	/// Every new line will have time, date and logger name in the beggining.
	/// </summary>
	class c_logger
	{
	public:
		using ptr = std::shared_ptr<c_logger>;
		
		/// <summary>
		/// Logger mode
		/// </summary>
		enum class enm_mode
		{
			none,	// operator<< will cause no output.
			console,// operator<< will cause output to console.
			file,	// operator<< will cause output to file.
			both	// operator<< will cause output to console and file.
		};

		static const enm_mode none	 { enm_mode::none };
		static const enm_mode console{ enm_mode::console };
		static const enm_mode file	 { enm_mode::file };
		static const enm_mode both	 { enm_mode::both };

		/// <summary>
		/// Get logger global_mode.
		/// </summary>
		/// <returns></returns>
		inline static enm_mode get_global_mode() { return m_global_mode; }

		/// <summary>
		/// Set logger global_mode.
		/// </summary>
		/// <param name="_global_mode"></param>
		inline void static set_global_mode(enm_mode _global_mode) { m_global_mode = _global_mode; }

		/// <summary>
		/// No output.
		/// </summary>
		inline void static set_global_mode_none() { m_global_mode = none; }

		/// <summary>
		/// Output to console.
		/// </summary>
		inline void static set_global_mode_console() { m_global_mode = console; }

		/// <summary>
		/// Output to file.
		/// </summary>
		inline void static set_global_mode_file() { m_global_mode = file; }

		/// <summary>
		/// Output to console and file.
		/// </summary>
		inline void static set_global_mode_both() { m_global_mode = both; }

		/// <summary>
		/// Check if the global_mode of this logger is none.
		/// </summary>
		/// <returns></returns>
		inline static bool global_mode_is_none() { return m_global_mode == none; }

		/// <summary>
		/// Check if the global_mode of this logger is console.
		/// </summary>
		/// <returns></returns>
		inline static bool global_mode_is_console() { return m_global_mode == console; }

		/// <summary>
		/// Check if the global_mode of this logger is file.
		/// </summary>
		/// <returns></returns>
		inline static bool global_mode_is_file() { return m_global_mode == file; }

		/// <summary>
		/// Check if the global_mode of this logger is both.
		/// </summary>
		/// <returns></returns>
		inline static bool global_mode_is_both() { return m_global_mode == both; }

		static const std::wstring logger_folder_path;

		/// <summary>
		/// Construct logger with given name and mode.
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_mode"></param>
		/// <param name="_use_global_mode"></param>
		c_logger(std::wstring_view _name = L"logger", enm_mode _mode = none, bool _use_global_mode = true);

		/// <summary>
		/// Construct object of this class with given name and mode, 
		/// make shared_ptr of this object class and get this shared_ptr. 
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_mode"></param>
		/// <returns></returns>
		inline static ptr make
		(std::wstring_view _name = L"logger", enm_mode _mode = none, bool _use_global_mode = true)
		{
			return std::make_shared<c_logger>(_name, _mode, _use_global_mode);
		}
		
		/// <summary>
		/// Get logger mode.
		/// </summary>
		/// <returns></returns>
		inline enm_mode get_mode() const { return m_mode; }

		/// <summary>
		/// If m_use_global_mode get global mode, else get personal mode.
		/// </summary>
		inline enm_mode check_mode() const
		{
			return m_use_global_mode ? m_global_mode : m_mode;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="_output">If m_use_global_mode: m_global_mode == none, else m_mode == none.</param>
		inline bool check_mode_none() const { return check_mode() == none; }

		/// <summary>
		/// Logger will use global mode instead of its personal mode.
		/// </summary>
		inline void use_global_mode() { m_use_global_mode = true; }

		/// <summary>
		/// Logger will use its personal mode instead of global mode.
		/// </summary>
		inline void ignore_global_mode() { m_use_global_mode = false; }

		/// <summary>
		/// Set logger mode.
		/// </summary>
		/// <param name="_mode"></param>
		inline void set_mode(enm_mode _mode) { m_mode = _mode; }

		/// <summary>
		/// No output.
		/// </summary>
		inline void set_mode_none() { m_mode = none; }

		/// <summary>
		/// Output to console.
		/// </summary>
		inline void set_mode_console() { m_mode = console; }

		/// <summary>
		/// Output to file.
		/// </summary>
		inline void set_mode_file() { m_mode = file; }

		/// <summary>
		/// Output to console and file.
		/// </summary>
		inline void set_mode_both() { m_mode = both; }

		/// <summary>
		/// Check if the mode of this logger is none.
		/// </summary>
		/// <returns></returns>
		inline bool mode_is_none() const { return m_mode == none; }

		/// <summary>
		/// Check if the mode of this logger is console.
		/// </summary>
		/// <returns></returns>
		inline bool mode_is_console() const { return m_mode == console; }

		/// <summary>
		/// Check if the mode of this logger is file.
		/// </summary>
		/// <returns></returns>
		inline bool mode_is_file() const { return m_mode == file; }

		/// <summary>
		/// Check if the mode of this logger is both.
		/// </summary>
		/// <returns></returns>
		inline bool mode_is_both() const { return m_mode == both; }

		/// <summary>
		/// Get filepath
		/// </summary>
		/// <returns></returns>
		inline std::wstring_view get_filepath() const { return m_filepath; }

		/// <summary>
		/// Set logger name.
		/// </summary>
		void set_name(std::wstring_view _name) { m_name = _name; }

		/// <summary>
		/// Get logger name.
		/// </summary>
		/// <param name="_output"></param>
		/// <returns></returns>
		std::wstring_view get_name() const { return m_name; }

		c_logger& operator<<(std::wstring_view _output);

		c_logger& operator<<(char _output);
		c_logger& operator<<(wchar_t _output);

		c_logger& operator<<(const char* _output);
		c_logger& operator<<(const wchar_t* _output);

		inline c_logger& operator<<(uint8_t  _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(uint16_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(uint32_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(uint64_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}

		inline c_logger& operator<<(int8_t  _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(int16_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(int32_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(int64_t _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}

		inline c_logger& operator<<(float _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}
		inline c_logger& operator<<(double _output)
		{
			return check_mode_none() ? *this : (*this) << std::to_wstring(_output);
		}

	protected:
		std::wstring m_name;

		bool m_use_global_mode;

		static enm_mode m_global_mode;

		enm_mode m_mode;
		
		std::wstring m_filepath;

		bool m_new_line;

		std::wstring m_line;

		std::wstring new_line_prompt();
		
		void update_new_line(std::wstring_view _output);
		
		std::wstring line(std::wstring_view _output);

		bool append_to_file(std::wstring_view _text, std::wstring_view _filepath);

		inline void print_to_console(std::wstring_view _output) { std::wcout << line(_output); }
		inline void print_to_file   (std::wstring_view _output) { append_to_file(line(_output), m_filepath); }
		void        print_to_both   (std::wstring_view _output);

	};

} // namespace owd

