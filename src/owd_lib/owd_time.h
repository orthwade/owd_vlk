#pragma once 
#include <chrono>  
#include <ctime>   
#include <sstream> 
#include <iomanip> 
#include <string>  

#include "owd_string.h"

namespace owd
{
	/// <summary>
	/// Get current time and date string in format YYYY-MM-DD HH:MM:SS.
	/// </summary>
	/// <returns></returns>
	std::string  current_time_date_str();

	/// <summary>
	/// Get current time and date wide string in format YYYY-MM-DD HH:MM:SS.
	/// </summary>
	/// <returns></returns>
	std::wstring current_time_date_wstr();

} // namespace owd
