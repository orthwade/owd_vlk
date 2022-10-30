#pragma once
#include <io.h>
#include <fcntl.h>
#include <fstream>

#include "owd_string.h"

namespace owd
{
	static int __cdecl setmode_result = _setmode(_fileno(stdout), _O_U16TEXT);

    std::wostream& operator<<(std::wostream& _ostream, std::string_view _output);
    
} // namespace