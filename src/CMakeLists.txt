cmake_minimum_required(VERSION 3.7...3.20 FATAL_ERROR)

set(${BUILD_DIR} ../out/build )

set(CMAKE_CXX_STANDARD 17)

project(owd_vlk)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logger)

find_package(Vulkan REQUIRED)

SET(GCC_COVERAGE_LINK_FLAGS 
"-lglfw"
"-lvulkan"
"-ldl"
"-lpthread"
"-lX11"
"-lXxf86vm"
"-lXrandr"
"-lXi")

if (MSVC)
    add_compile_definitions(_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
else()

endif()

message(STATUS ${Vulkan_INCLUDE_DIR})
message(STATUS ${VULKAN_LIB_LIST})
message(STATUS ${Vulkan_LIBRARIES})

set(VULKAN_LIB_LIST "vulkan-1")

add_executable(${PROJECT_NAME}
glfw_error.h		glfw_error.cpp
glfw_init.h			glfw_init.cpp  
window.h			window.cpp
monitor.h			monitor.cpp
vulkan_debug.h      vulkan_debug.cpp
vulkan_surface.h    vulkan_surface.cpp
vulkan_instance.h   vulkan_instance.cpp
app.h				app.cpp
main.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(shader)
add_subdirectory(owd_lib)

target_include_directories(${PROJECT_NAME} 
PUBLIC external/glfw/include
PUBLIC external/glm/include
PUBLIC ${Vulkan_INCLUDE_DIR}
PUBLIC shader
PUBLIC owd_lib
)

target_link_directories(${PROJECT_NAME} 
PRIVATE external/glfw/src
PRIVATE external/glfw/src/Debug
PRIVATE external/glfw/src/Release
PRIVATE external/glm/src
PRIVATE external/glm/src/Debug
PRIVATE external/glm/src/Release
PRIVATE owd_lib
PRIVATE ${Vulkan_LIBRARIES}
PRIVATE shader
)

target_link_libraries(${PROJECT_NAME} 
glfw
glm
owd_lib
${Vulkan_LIBRARIES}
shader
)

#add_custom_command(TARGET ${PROJECT_NAME}
#    PRE_BUILD
#    COMMAND odb -o /home/david/dev/ --std c++11 -I/home/david/dev/ -d sqlite --generate-    query --generate-schema ${PROMOTER_LIB_PREFIX}/entities/person.hpp
#)	

configure_file(shader/vertex.spv ${CMAKE_BINARY_DIR}/shader/vertex.spv COPYONLY)
configure_file(shader/fragment.spv ${CMAKE_BINARY_DIR}/shader/fragment.spv  COPYONLY)