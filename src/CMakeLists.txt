cmake_minimum_required(VERSION 3.7...3.20 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

project(owd_vlk)

find_package(Vulkan REQUIRED)

message(STATUS ${Vulkan_INCLUDE_DIR})
message(STATUS ${VULKAN_LIB_LIST})
message(STATUS ${Vulkan_LIBRARIES})


set(VULKAN_LIB_LIST "vulkan-1")

add_executable(${PROJECT_NAME} main.cpp app.cpp window.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

target_include_directories(${PROJECT_NAME} 
PUBLIC external/glfw/include
PUBLIC external/glm/include)



target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR})

target_link_directories(${PROJECT_NAME} 
PRIVATE external/glfw/src
PRIVATE external/glfw/src/Debug
PRIVATE external/glfw/src/Release
PRIVATE external/glm/src
PRIVATE external/glm/src/Debug
PRIVATE external/glm/src/Release
PRIVATE ${Vulkan_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} 
glfw
glm
${Vulkan_LIBRARIES})	