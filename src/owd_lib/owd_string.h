#pragma once
#include <string_view>
#include <codecvt>

namespace owd
{
	std::string  convert_utf16_to_utf8(std::wstring_view _str_1);
	std::wstring convert_utf8_to_utf16(std::string_view _str_1);

	bool compare_strings(std::string_view  _str_1, std::string_view  _str_2);
	bool compare_strings(std::wstring_view _str_1, std::wstring_view _str_2);
	bool compare_strings(std::string_view  _str_1, std::wstring_view _str_2);
	bool compare_strings(std::wstring_view _str_1, std::string_view  _str_2);
} // namespace owd