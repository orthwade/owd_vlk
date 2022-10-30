#include "owd_logger.h"

namespace owd
{
    const std::wstring c_logger::logger_folder_path{ current_path_str_ + L"/logger/" };

    c_logger::enm_mode c_logger::m_global_mode{ c_logger::none };

    c_logger::c_logger(std::wstring_view _name, enm_mode _mode, bool _use_global_mode)
        :
        c_object(_name),
        m_use_global_mode(_use_global_mode),
        m_mode(_mode),
        m_new_line(true),
        m_filepath(logger_folder_path + std::wstring(_name) + L".txt"),
		m_line()
    {
    }

	std::wstring c_logger::new_line_prompt()
	{
		std::wstring result{};

		result.push_back(L'[');
		result.append(current_time_date_wstr());
		result.append(L"; ");
		result.append(m_name);
		result.append(L"]: ");

		return result;
	}

	void c_logger::update_new_line(std::wstring_view _output)
	{
		if (!_output.empty())
		{
			if (_output.back() == L'\n')
			{
				m_new_line = true;
			}
		}
	}

	void c_logger::print_to_both(std::wstring_view _output)
	{
		std::wstring line_{ line(_output) };

		std::wcout << line_;
		append_to_file(line_, m_filepath);
	}

	c_logger& c_logger::operator<<(std::wstring_view _output)
	{
		enm_mode mode{ m_use_global_mode ? m_global_mode : m_mode };

		if (mode != none)
		{
			switch (mode)
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

			default:
				break;
			}
			update_new_line(_output);
		}

		return *this;
	}

	c_logger& c_logger::operator<<(char _output)
	{
		enm_mode mode{ m_use_global_mode ? m_global_mode : m_mode };

		if (mode != none)
		{
			std::string  str_ { _output };
			std::wstring wstr_{ convert_utf8_to_utf16(str_) };
			switch (mode)
			{
			case console:
				print_to_console(wstr_);
				break;

			case file:
				print_to_file(wstr_);
				break;

			case both:
				print_to_both(wstr_);
				break;

			default:
				break;
			}
			update_new_line(wstr_);
		}

		return *this;
	}
	
	c_logger& c_logger::operator<<(wchar_t _output)
	{
		enm_mode mode{ m_use_global_mode ? m_global_mode : m_mode };

		if (mode != none)
		{
			std::wstring wstr_{ _output };

			switch (mode)
			{
			case console:
				print_to_console(wstr_);
				break;

			case file:
				print_to_file(wstr_);
				break;

			case both:
				print_to_both(wstr_);
				break;

			default:
				break;
			}
			update_new_line(wstr_);
		}

		return *this;
	}

	c_logger& c_logger::operator<<(const char* _output)
	{
		enm_mode mode{ m_use_global_mode ? m_global_mode : m_mode };

		if (mode != none)
		{
			std::string  str_{ _output };
			std::wstring wstr_{ convert_utf8_to_utf16(str_) };

			switch (mode)
			{
			case console:
				print_to_console(wstr_);
				break;

			case file:
				print_to_file(wstr_);
				break;

			case both:
				print_to_both(wstr_);
				break;

			default:
				break;
			}
			update_new_line(wstr_);
		}

		return *this;
	}

	c_logger& c_logger::operator<<(const wchar_t* _output)
	{
		enm_mode mode{ m_use_global_mode ? m_global_mode : m_mode };

		if (mode != none)
		{
			std::wstring wstr_{ _output };

			switch (mode)
			{
			case console:
				print_to_console(wstr_);
				break;

			case file:
				print_to_file(wstr_);
				break;

			case both:
				print_to_both(wstr_);
				break;

			default:
				break;
			}
			update_new_line(wstr_);
		}

		return *this;
	}

} // namespace owd
