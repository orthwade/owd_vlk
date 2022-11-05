#pragma once 
#include <vector>
#include <string_view>
#include <unordered_map>
#include <memory>

namespace owd
{
	template<class T>
	using vec_t = std::vector<T>;

	template<class T1, class T2>
	using umap_t = std::unordered_map<T1, T2>;

	template<class T>
	using ptr_t = std::shared_ptr<T>;

	typedef uint8_t byte_t;

	typedef vec_t<byte_t> vec_byte_t;

	typedef std::wstring_view wsv_t;
} // namespace owd
