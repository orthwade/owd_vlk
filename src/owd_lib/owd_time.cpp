#include "owd_time.h"
#include "owd_time.h"

std::string owd::current_time_date_str()
{
    auto now = std::chrono::system_clock::now();

    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss{};

    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    return ss.str();
}

std::wstring owd::current_time_date_wstr()
{
    auto now = std::chrono::system_clock::now();

    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss{};

    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    return convert_utf8_to_utf16(ss.str());
}

std::string owd::current_date_str()
{
    std::string result{ owd::current_time_date_str() };

    size_t space_pos_ = result.find(' ');

    result.resize(space_pos_);

    return result;
}

std::wstring owd::current_date_wstr()
{
    std::wstring result{ owd::current_time_date_wstr() };

    size_t space_pos_ = result.find(L' ');

    result.resize(space_pos_);

    return result;
}
