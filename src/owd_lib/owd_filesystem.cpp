#include "owd_filesystem.h"

namespace owd
{
	c_file::c_file(std::wstring_view _filepath, std::wstring_view _filename)
		:
		c_object(_filename),
		m_filepath(_filepath),
		m_vec_byte(std::istreambuf_iterator<char>(std::ifstream(_filepath.data(), std::ios::binary)), {})
	{
	}
	c_file::c_file()
		:
		c_object(),
		m_filepath(),
		m_vec_byte()
	{
	}

	void c_file::load(std::wstring_view _filepath)
	{
		clear();

		std::ifstream ifstream_(_filepath.data(), std::ios::binary);
		
		std::copy
		(
			std::istream_iterator<char>(ifstream_),
			std::istream_iterator<char>(),
			m_vec_byte.begin()
		);
	}

	void c_file::save(std::wstring_view _filepath)
	{
		std::ofstream ofstream_(_filepath.data(), std::ios::binary);

		ofstream_.write(reinterpret_cast<const char*>(m_vec_byte.data()), m_vec_byte.size());
	}

	void c_file::load()
	{
		clear();

		std::ifstream ifstream_(m_filepath, std::ios::binary);

		std::copy
		(
			std::istream_iterator<char>(ifstream_),
			std::istream_iterator<char>(),
			m_vec_byte.begin()
		);
	}

	void c_file::save()
	{
		std::ofstream ofstream_(m_filepath, std::ios::binary);

		ofstream_.write(reinterpret_cast<const char*>(m_vec_byte.data()), m_vec_byte.size());
	}
	
} // namespace owd
