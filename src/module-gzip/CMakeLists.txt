#===============================================================================
# CMakeLists for module: gzip
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_gzip)

add_library(gzip SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(gzip PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11)
target_link_directories(gzip PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(gzip PRIVATE stdafx.h)
target_compile_definitions(gzip PRIVATE GURAX_MODULE_SEPARATED)
target_sources(gzip PRIVATE
	module-gzip.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_options(gzip PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:MSVCRT>)
target_link_libraries(gzip PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Darwin>:z>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gzip RUNTIME DESTINATION module/site)
