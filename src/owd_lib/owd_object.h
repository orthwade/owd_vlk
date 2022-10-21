#pragma once 
#include <memory>
#include <string>

/// <summary>
/// Basic named object class.
/// </summary>
class c_object
{
public:
	using ptr = std::shared_ptr<c_object>;

	/// <summary>
	/// Construct object with given name, 
	/// make shared_ptr of this object class and get this shared_ptr.	
	/// </summary>
	/// <returns></returns>
	inline static ptr make(std::wstring_view _name = L"object_name") 
	{ return std::make_shared<c_object>(_name); }

	/// <summary>
	/// Construct object with given name.
	/// </summary>
	/// <param name="_name"></param>
	c_object(std::wstring_view _name = L"object_name") : m_name(_name) {}

	/// <summary>
	/// Get object name.
	/// </summary>
	/// <returns></returns>
	inline virtual std::wstring_view get_name() const { return m_name; }
	
	/// <summary>
	/// Set object name.
	/// </summary>
	/// <param name="_name"></param>
	inline virtual void set_name(std::wstring_view _name) { m_name = _name; }

protected:
	std::wstring m_name;
};