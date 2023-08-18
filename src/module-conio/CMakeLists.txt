#===============================================================================
# CMakeLists for module: conio
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_conio)

add_library(conio.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(conio.gurd PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(conio.gurd PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(conio.gurd PRIVATE cxx_std_17)
target_precompile_headers(conio.gurd PRIVATE stdafx.h)
target_compile_options(conio.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(conio.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(conio.gurd PRIVATE
	module-conio.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(conio.gurd PRIVATE guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS conio.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS script/conio.progress.gura DESTINATION module/site)
