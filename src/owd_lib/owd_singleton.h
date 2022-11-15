#pragma once 
#include <list>

#include "owd_object.h"

namespace owd
{
	/// <summary>
	/// Singleton object class
	/// </summary>
	class c_singleton : public c_object
	{
	public:
		/// <summary>
		/// Delete object.
		/// </summary>
		virtual void terminate() = 0;

		/// <summary>
		/// Delete all singletons.
		/// </summary>
		static void terminate_all_singletons();

	protected:
		c_singleton();
		c_singleton(wsv_t _name);

		static std::list<c_singleton*> m_list_singleton;
	};

}

