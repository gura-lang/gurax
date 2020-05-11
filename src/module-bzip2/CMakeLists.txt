#===============================================================================
# CMakeLists for module: bzip2
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_bzip2)

add_library(bzip2 SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(bzip2 PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8)
target_link_directories(bzip2 PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(bzip2 PRIVATE stdafx.h)
target_compile_definitions(bzip2 PRIVATE GURAX_MODULE_SEPARATED)
target_sources(bzip2 PRIVATE
	module-bzip2.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_libraries(bzip2 PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libbz2>
	$<$<PLATFORM_ID:Linx>:bz2>
	$<$<PLATFORM_ID:Darwin>:bz2>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS bzip2 RUNTIME DESTINATION module/site)
