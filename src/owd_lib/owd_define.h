#pragma once 
#include <vector>
#include <string_view>
#include <unordered_map>

namespace owd
{
	typedef uint8_t byte_t;
	typedef std::vector<byte_t> vec_byte_t;

	typedef std::wstring_view wsv_t;

	template<class T1, class T2>
	using umap_t = std::unordered_map<T1, T2>;
	
} // namespace owd
