#include "owd_logger.h"

namespace owd
{
	static const std::filesystem::path current_path_{ std::filesystem::current_path() };
	static const std::wstring current_path_str_{ current_path_.wstring() };

    const std::wstring c_logger::logger_folder_path{ current_path_str_ + L"/logger/" };

	static const std::locale utf8_locale_ = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

    c_logger::enm_mode c_logger::m_global_mode{ c_logger::none };

    c_logger::c_logger(std::wstring_view _name, enm_mode _mode, bool _use_global_mode)
        :
        m_name(_name),
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

	std::wstring c_logger::line(std::wstring_view _output)
	{
		std::wstring result{};

		if (m_new_line)
		{
			result.append(new_line_prompt());
			result.append(_output);

			m_new_line = false;
		}
		else
		{
			result = _output;
		}

		return result;
	}

	bool c_logger::append_to_file(std::wstring_view _text, std::wstring_view _filepath)
	{
		bool result = false;

		std::wofstream ofstream_{ _filepath.data(), std::ios_base::app };

		ofstream_.imbue(utf8_locale_);

		if (ofstream_)
		{
			ofstream_ << _text;

			if (!ofstream_.bad())
			{
				result = true;
			}
		}

		return result;
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
