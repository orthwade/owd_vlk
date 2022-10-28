#pragma once

#include <io.h>
#include <fcntl.h>

namespace owd
{
	static int __cdecl setmode_result = _setmode(_fileno(stdout), _O_WTEXT);
} // namespace