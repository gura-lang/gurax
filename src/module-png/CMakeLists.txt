#===============================================================================
# CMakeLists for module: png
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_png)

add_library(png SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(png PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/guest/include/libpng>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/guest/include/libpng>)
target_link_directories(png PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37/projects/vstudio/x64/Release\ Library>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/guest/lib>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/guest/lib>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(png PRIVATE stdafx.h)
target_compile_definitions(png PRIVATE GURAX_MODULE_SEPARATED)
target_sources(png PRIVATE
	module-png.cpp
	Util.cpp
	ImageExtension.cpp
	Content.cpp
	VType_Content.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_options(png PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT -LTCG>)
target_link_libraries(png PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libpng16>
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Linx>:png16>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Darwin>:png16>
	$<$<PLATFORM_ID:Darwin>:z>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS png RUNTIME DESTINATION module/site)
