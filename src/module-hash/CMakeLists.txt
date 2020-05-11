#===============================================================================
# CMakeLists for module: hash
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_hash)

add_library(hash SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(hash PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	${PROJECT_SOURCE_DIR}/guest/md5
	${PROJECT_SOURCE_DIR}/guest/sha1)
target_link_directories(hash PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(hash PRIVATE stdafx.h)
target_compile_definitions(hash PRIVATE GURAX_MODULE_SEPARATED)
target_sources(hash PRIVATE
	module-hash.cpp
	Util.cpp
	Accumulator.cpp
	VType_Accumulator.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_libraries(hash guraxcore guest)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS hash RUNTIME DESTINATION module/site)
#-------------------------------------------------------------------------------
# Dependency
#-------------------------------------------------------------------------------
add_subdirectory(guest)
