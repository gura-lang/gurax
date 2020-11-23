#===============================================================================
# CMakeLists for module: tar
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_tar)

add_library(tar.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(tar.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:
		${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
		${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(tar.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:
		${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
		${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(tar.gurd PRIVATE cxx_std_17)
target_precompile_headers(tar.gurd PRIVATE stdafx.h)
target_compile_options(tar.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(tar.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(tar.gurd PRIVATE
	module-tar.cpp
	Util.cpp
	PathExtension.cpp
	Reader.cpp
	TARFormat.cpp
	Writer.cpp
	VType_Reader.cpp
	VType_StatEx.cpp
	VType_Writer.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(tar.gurd PRIVATE
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:-NODEFAULTLIB:MSVCRT>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(tar.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Windows>:libbz2>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Linx>:bz2>
	$<$<PLATFORM_ID:Darwin>:z>
	$<$<PLATFORM_ID:Darwin>:bz2>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS tar.gurd RUNTIME DESTINATION module/site)
