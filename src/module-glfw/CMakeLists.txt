#===============================================================================
# CMakeLists for module: glfw
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_glfw)

add_library(glfw.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(glfw.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/glfw-3.3.2/include>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/include>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest/include>)
target_link_directories(glfw.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/glfw-3.3.2/build/src>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/lib>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>/lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(glfw.gurd PRIVATE cxx_std_17)
target_precompile_headers(glfw.gurd PRIVATE stdafx.h)
target_compile_options(glfw.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(glfw.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(glfw.gurd PRIVATE
	module-glfw.cpp
	Util.cpp
	Consts.cpp
	Functions.cpp
	VType_GLFWcursor.cpp
	VType_GLFWgammaramp.cpp
	VType_GLFWimage.cpp
	VType_GLFWmonitor.cpp
	VType_GLFWvidmode.cpp
	VType_GLFWwindow.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(glfw.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:glfw3>
	$<$<PLATFORM_ID:Linux>:glfw3>
	$<$<PLATFORM_ID:Darwin>:glfw3>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS glfw.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/glfw.gura
	DESTINATION module/site)
