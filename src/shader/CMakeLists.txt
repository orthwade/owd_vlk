set(CMAKE_CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_SOURCE_DIR}/owd_lib
)
message(${CMAKE_SOURCE_DIR}/owd_lib/)

target_link_directories(${PROJECT_NAME} 
PRIVATE owd_lib
)

target_link_libraries(${PROJECT_NAME} 
owd_lib
)	

add_library(shader shader.h shader.cpp)