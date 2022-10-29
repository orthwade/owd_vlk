#include "owd_logger.h"

namespace owd
{
    c_logger::c_logger(std::wstring_view _name, enm_mode _mode)
        :
        c_object(_name),
        m_mode(_mode)
    {
    }
} // namespace owd
