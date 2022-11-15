#pragma once 
#include <memory>
#include <string>

#include "owd_logger.h"
#include "owd_define.h"

namespace owd
{
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
		{
			return std::make_shared<c_object>(_name);
		}

		/// <summary>
		/// Construct object with given name.
		/// </summary>
		/// <param name="_name"></param>
		c_object(std::wstring_view _name = L"object_name");

		/// <summary>
		/// Get object name.
		/// </summary>
		/// <returns></returns>
		inline virtual std::wstring_view get_name() const { return m_name; }

		/// <summary>
		/// Set object name.
		/// </summary>
		/// <param name="_name"></param>
		virtual void set_name(std::wstring_view _name);

	protected:
		std::wstring m_name;

		c_logger m_logger;
	};
}

