#===============================================================================
# CMakeLists for module: zip
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_zip)

add_library(zip.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(zip.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:
		${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
		${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8>)
target_link_directories(zip.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:
		${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
		${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(zip.gurd PRIVATE stdafx.h)
target_compile_definitions(zip.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(zip.gurd PRIVATE
	module-zip.cpp
	Util.cpp
	ZIPFormat.cpp
	Reader.cpp
	Writer.cpp
	PathExtension.cpp
	VType_Reader.cpp
	VType_Writer.cpp
	VType_StatEx.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(zip.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:MSVCRT>)
target_link_libraries(zip.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Windows>:libbz2>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Linx>:bz2>
	$<$<PLATFORM_ID:Darwin>:z>
	$<$<PLATFORM_ID:Darwin>:bz2>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS zip.gurd RUNTIME DESTINATION module/site)
