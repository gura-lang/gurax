#===============================================================================
# CMakeLists for module: conio
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_conio)

add_library(conio SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(conio PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(conio PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(conio PRIVATE stdafx.h)
target_compile_definitions(conio PRIVATE GURAX_MODULE_SEPARATED)
target_sources(conio PRIVATE
	module-conio.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_libraries(conio PRIVATE guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS conio RUNTIME DESTINATION module/site)
