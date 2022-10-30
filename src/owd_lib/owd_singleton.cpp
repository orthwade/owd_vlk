#include "owd_singleton.h"

namespace owd
{
	std::list<c_singleton*> c_singleton::m_list_singleton{};

	void c_singleton::terminate_all_singletons()
	{
		if (!m_list_singleton.empty())
		{
			while (true)
			{
				if (m_list_singleton.empty())
				{
					break;
				}
				else
				{
					c_singleton* singleton = m_list_singleton.back();
					if (singleton)
					{
						singleton->terminate();
					}
				}
			}
		}
	}
	c_singleton::c_singleton()
	{
		m_list_singleton.push_back(this);
	}
} // namespace owd