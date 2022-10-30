#include "owd_output.h"

std::wostream& owd::operator<<(std::wostream& _wostream, std::string_view _output)
{
    _wostream << convert_utf8_to_utf16(_output);
    return _wostream;
}
