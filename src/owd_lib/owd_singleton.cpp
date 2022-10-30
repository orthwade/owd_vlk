#include "owd_singleton.h"

namespace owd
{
	std::list<c_singleton*> c_singleton::m_list_singleton{};

	void c_singleton::terminate_all_singletons()
	{
		if (m_list_singleton.size() > 0)
		{

			for (c_singleton* singleton : m_list_singleton)
			{
				if (singleton)
					singleton->terminate();

				if (m_list_singleton.empty())
				{
					break;
				}
			}
		}
		
	}
	c_singleton::c_singleton()
	{
		m_list_singleton.push_back(this);
	}
} // namespace owd