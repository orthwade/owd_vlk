#pragma once
#include <string_view>

namespace owd
{
	bool compare_strings(std::string_view _str_1, std::string_view _str_2);
	bool compare_strings(std::wstring_view _str_1, std::wstring_view _str_2);
	bool compare_strings(std::string_view _str_1, std::wstring_view _str_2);
	bool compare_strings(std::wstring_view _str_1, std::string_view _str_2);

		
} // namespace owd