#pragma once 
#include <fstream>
#include <filesystem>
#include <locale>

#include "owd_define.h"
#include "owd_object.h"
#include "owd_string.h"

namespace owd
{
	static const std::filesystem::path current_path_{ std::filesystem::current_path() };
	static const std::wstring current_path_str_{ current_path_.wstring() };

	const std::locale utf8_locale_ = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());

	/// <summary>
	/// Append text to textfile.
	/// </summary>
	/// <param name="_text"></param>
	/// <param name="_filepath"></param>
	/// <returns></returns>
	bool append_to_file(std::wstring_view _text, std::wstring_view _filepath);

	///// <summary>
	///// Append output to textfile.
	///// </summary>
	///// <typeparam name="T"></typeparam>
	///// <param name="_output"></param>
	///// <param name="_filepath"></param>
	///// <returns></returns>
	//template<class T>
	//bool append_to_file(const T& _output, std::wstring_view _filepath)
	//{
	//	bool result = false;

	//	std::wofstream ofstream_{ _filepath.data(), std::ios_base::app };

	//	if (ofstream_)
	//	{
	//		ofstream_ << _output;

	//		if (!ofstream_.bad())
	//		{
	//			result = true;
	//		}
	//	}

	//	return result;
	//}

	/// <summary>
	/// Class of binary file.
	/// </summary>
	class c_file : public c_object
	{
	public:
		using ptr = std::shared_ptr<c_file>;

		/// <summary>
		/// Construct object and store data from file with given filepath and name, 
		/// make shared_ptr of this object class and get this shared_ptr.		
		/// </summary>
		/// <param name="_filepath"></param>
		/// <param name="_filename">Name of this object. 
		/// Not related to the filepath or name of the file in the filesystem</param>
		/// <returns></returns>
		inline static ptr make(std::wstring_view _filepath, std::wstring_view _filename = L"file_name")
		{
			return std::make_shared<c_file>(_filepath, _filename);
		}

		/// <summary>
		/// Construct object of this class, 
		/// make shared_ptr of this object class and get this shared_ptr. 
		/// </summary>
		/// <returns></returns>
		inline static ptr make()
		{
			return std::make_shared<c_file>();
		}

		/// <summary>
		/// Construct object and store data from file.
		/// </summary>
		/// <param name="_filepath"></param>
		/// <param name="_filename">Name of this object. 
		/// Not related to the filepath or name of the file in the filesystem</param>
		c_file(std::wstring_view _filepath, std::wstring_view _filename = L"file_name");

		/// <summary>
		/// Construct object.
		/// </summary>
		c_file();
		
		/// <summary>
		/// Clea stored data.
		/// </summary>
		inline void clear() { m_vec_byte.clear(); }

		/// <summary>
		/// Store data from file.
		/// </summary>
		/// <param name="_filepath"></param>
		virtual void load(std::wstring_view _filepath);

		/// <summary>
		/// Store data to file.
		/// </summary>
		/// <param name="_filepath"></param>
		virtual void save(std::wstring_view _filepath);

		/// <summary>
		/// Store data from last loaded file.
		/// </summary>
		/// <param name="_filepath"></param>
		virtual void load();

		/// <summary>
		/// Update last loaded file with stored data.
		/// </summary>
		/// <param name="_filepath"></param>
		virtual void save();

		/// <summary>
		/// Get stored data.
		/// </summary>
		/// <returns></returns>
		virtual vec_byte_t& get_data() { return m_vec_byte; }

	protected:
		vec_byte_t m_vec_byte;
		std::wstring m_filepath;
	};
} // namespace owd

