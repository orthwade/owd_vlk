#include "owd_logger.h"

namespace owd
{
    const std::wstring c_logger::logger_folder_path{ current_path_str_ + L"/logger/" };

    c_logger::c_logger(std::wstring_view _name, enm_mode _mode)
        :
        c_object(_name),
        m_mode(_mode),
        m_new_line(true),
        m_filepath(logger_folder_path + std::wstring(_name) + L".txt"),
        m_wstr_buffer()
    {
    }

    c_logger& c_logger::operator<<(std::wstring_view _output)
    {
        if (!_output.empty())
        {
            switch (m_mode)
            {
            case none:
                break;

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
        }

        return *this;
    }

    void c_logger::update_new_line(std::wstring_view _output)
    {
        if (_output.back() == '\n')
        {
            m_new_line = true;
        }
    }
    void c_logger::print_to_console(std::wstring_view _output)
    {
        if (m_new_line)
        {
            std::wcout << '[' << current_time_date_wstr() << L"]; " << _output;
            m_new_line = false;
        }
        else
        {
            std::wcout << _output;
        }
        update_new_line(_output);
    }
    void c_logger::print_to_file(std::wstring_view _output)
    {
        if (m_new_line)
        {
            append_to_file_('[');
            append_to_file_(current_time_date_wstr());
            append_to_file_(L"]; ");
            append_to_file_(_output);
            m_new_line = false;
        }
        else
        {
            append_to_file_(_output);
        }
        update_new_line(_output);
    }
    void c_logger::print_to_both(std::wstring_view _output)
    {
        if (m_new_line)
        {
            std::wcout << '[' << current_time_date_wstr() << L"]; " << _output;
            append_to_file_('[');
            append_to_file_(current_time_date_wstr());
            append_to_file_(L"]; ");
            append_to_file_(_output);
            m_new_line = false;
        }
        else
        {
            std::wcout << _output;
            append_to_file_(_output);
        }
        update_new_line(_output);
    }
} // namespace owd
