#include <codecvt>
#include "owd_string.h"

namespace owd
{
	/// <summary>
	/// Compare two strings.
	/// </summary>
	/// <param name="_str_1"></param>
	/// <param name="_str_2"></param>
	/// <returns>Return true if strings are equal, else return false. </returns>
	bool compare_strings(std::string_view _str_1, std::string_view _str_2)
	{
		bool result = false;

		if (_str_1 == _str_2)
		{
			result = true;
		}

		return result;
	}

	/// <summary>
	/// Compare two strings.
	/// </summary>
	/// <param name="_str_1"></param>
	/// <param name="_str_2"></param>
	/// <returns>Return true if strings are equal, else return false. </returns>
	bool compare_strings(std::wstring_view _str_1, std::wstring_view _str_2)
	{
		bool result = false;

		if (_str_1 == _str_2)
		{
			result = true;
		}

		return result;
	}

	/// <summary>
	/// Compare two strings.
	/// </summary>
	/// <param name="_str_1"></param>
	/// <param name="_str_2"></param>
	/// <returns>Return true if strings are equal, else return false.</returns>
	bool compare_strings(std::string_view _str_1, std::wstring_view _str_2)
	{
		std::wstring string_to_convert{ _str_2 };

		using convert_type = std::codecvt_utf8<wchar_t>;

		std::wstring_convert<convert_type, wchar_t> converter;

		std::string converted_str = converter.to_bytes(string_to_convert);

		return compare_strings(_str_1, converted_str);
	}

	/// <summary>
	/// Compare two strings.
	/// </summary>
	/// <param name="_str_1"></param>
	/// <param name="_str_2"></param>
	/// <returns>Return true if strings are equal, else return false.</returns>
	bool compare_strings(std::wstring_view _str_1, std::string_view _str_2)
	{
		std::wstring string_to_convert{ _str_1 };

		using convert_type = std::codecvt_utf8<wchar_t>;

		std::wstring_convert<convert_type, wchar_t> converter;

		std::string converted_str = converter.to_bytes(string_to_convert);

		return compare_strings(converted_str, _str_2);
	}
} // namespace owd