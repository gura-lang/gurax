#===============================================================================
# CMakeLists for module: opengl
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_opengl)

add_library(opengl.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(opengl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/glew-2.1.0/include>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(opengl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/glew-2.1.0/build_work/lib>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(opengl.gurd PRIVATE cxx_std_17)
target_precompile_headers(opengl.gurd PRIVATE stdafx.h)
target_compile_options(opengl.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(opengl.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(opengl.gurd PRIVATE
	module-opengl.cpp
	Util.cpp
	Consts.cpp
	Functions.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(opengl.gurd PRIVATE
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:-NODEFAULTLIB:MSVCRT>)
target_link_libraries(opengl.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libglew32.lib>
	$<$<PLATFORM_ID:Windows>:opengl32.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS opengl.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/opengl.teapot.gura
	script/opengl.stl.gura
	DESTINATION module/site)
