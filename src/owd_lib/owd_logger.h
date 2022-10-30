#pragma once 
#include <iostream>

#include "owd_filesystem.h"
#include "owd_time.h"
#include "owd_output.h"

namespace owd
{
	/// <summary>
	/// Class of logger. This logger uses operator<< to output to console and/or file.
	/// Every new line will have time, date and logger name in the beggining.
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
			none,	// operator<< will cause no output.
			console,// operator<< will cause output to console.
			file,	// operator<< will cause output to file.
			both	// operator<< will cause output to console and file.
		};

		static const enm_mode none	 { enm_mode::none };
		static const enm_mode console{ enm_mode::console };
		static const enm_mode file	 { enm_mode::file };
		static const enm_mode both	 { enm_mode::both };

		static const std::wstring logger_folder_path;

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
		
		/// <summary>
		/// Get logger mode.
		/// </summary>
		/// <returns></returns>
		inline enm_mode get_mode() const { return m_mode; }

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

		template<class T>
		c_logger& operator<<(const T& _output);

		c_logger& operator<<(std::wstring_view _output);
		
		std::wstring m_wstr_buffer;

		inline c_logger& operator<<(std::string_view _output)
		{
			return this->operator<<(std::wstring_view(convert_utf8_to_utf16(_output)));
		}
		inline c_logger& operator<<(wchar_t _output)
		{
			return (*this) << std::wstring_view{ &_output };
		}
		inline c_logger& operator<<(const wchar_t* _output)
		{
			return (*this) << std::wstring_view{ _output };
		}
		inline c_logger& operator<<(char _output)
		{
			return (*this) << std::string_view{ &_output };
		}
		inline c_logger& operator<<(const char* _output)
		{
			return (*this) << std::string_view{ _output };
		}

	protected:
		enm_mode m_mode;
		
		std::wstring m_filepath;

		bool m_new_line;

		void update_new_line(std::wstring_view _output);

		template<class T>
		void print_to_console(const T& _output);

		template<class T>
		void print_to_file(const T& _output);

		template<class T>
		void print_to_both(const T& _output);

		template<class T>
		inline void append_to_file_(const T& _output) { append_to_file(_output, m_filepath); }

		void print_to_console(std::wstring_view _output);

		void print_to_file(std::wstring_view _output);
		
		void print_to_both(std::wstring_view _output);

		inline void append_to_file_(std::wstring_view _output) { append_to_file(_output, m_filepath); }

		inline void print_to_console(std::string_view _output) { print_to_console(convert_utf8_to_utf16(_output)); }

		inline void print_to_file(std::string_view _output) { print_to_file(convert_utf8_to_utf16(_output)); }

		inline void print_to_both(std::string_view _output) { print_to_both(convert_utf8_to_utf16(_output)); }

		inline void append_to_file_(std::string_view _output) { append_to_file_(convert_utf8_to_utf16(_output)); }
	};

	template<class T>
	c_logger& c_logger::operator<<(const T& _output)
	{
		switch (m_mode)
		{
		case console:
			print_to_console(_output);
			break;

		case file:
			print_to_file(_output);
			break;

		case both:
			print_to_both(_output);
			break;

		case none:
		default:
			break;
		}

		return *this;
	}
	template<class T>
	void c_logger::print_to_console(const T& _output)
	{
		if (m_new_line)
		{
			std::wcout << '[' << current_time_date_wstr() << L"]; " << _output;
		}
		else
		{
			std::wcout << _output;
		}
	}
	template<class T>
	void c_logger::print_to_file(const T& _output)
	{
		if (m_new_line)
		{
			append_to_file_('[');
			append_to_file_(current_time_date_wstr());
			append_to_file_(L"]; ");
			append_to_file_(_output);
		}
		else
		{
			append_to_file_(_output);
		}
	}
	template<class T>
	void c_logger::print_to_both(const T& _output)
	{
		if (m_new_line)
		{
			std::wcout << '[' << current_time_date_wstr() << L"]; " << _output;
			append_to_file_('[');
			append_to_file_(current_time_date_wstr());
			append_to_file_(L"]; ");
			append_to_file_(_output);
		}
		else
		{
			std::wcout << _output;
			append_to_file_(_output);
		}
	}
} // namespace owd

