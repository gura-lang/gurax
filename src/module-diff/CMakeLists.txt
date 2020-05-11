#===============================================================================
# CMakeLists for module: diff
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_diff)

add_library(diff SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(diff PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	${PROJECT_SOURCE_DIR}/dtl-1.19-gurax)
target_link_directories(diff PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(diff PRIVATE stdafx.h)
target_compile_definitions(diff PRIVATE GURAX_MODULE_SEPARATED)
target_sources(diff PRIVATE
	module-diff.cpp
	Util.cpp
	Diff.cpp
	Hunk.cpp
	VType_Diff.cpp
	VType_Edit.cpp
	VType_Hunk.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_libraries(diff guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS diff RUNTIME DESTINATION module/site)
