set(CMAKE_CXX_STANDARD 17)
	
add_library(owd_lib 
owd_define.h		owd_define.cpp
owd_string.h		owd_string.cpp
owd_logger.h		owd_logger.cpp
owd_object.h		owd_object.cpp
owd_singleton.h		owd_singleton.cpp
owd_filesystem.h	owd_filesystem.cpp
owd_output.h		owd_output.cpp
owd_time.h			owd_time.cpp
owd_lib.h			owd_lib.cpp)
