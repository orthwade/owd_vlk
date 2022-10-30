#pragma once 
#include <list>

namespace owd
{
	/// <summary>
	/// Singleton object class
	/// </summary>
	class c_singleton
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

		static std::list<c_singleton*> m_list_singleton;
	};

}

