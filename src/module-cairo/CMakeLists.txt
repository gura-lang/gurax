#===============================================================================
# CMakeLists for module: cairo
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_cairo)

add_library(cairo.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(cairo.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/cairo-1.16.0/src>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(cairo.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/cairo-1.16.0/src/release>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37/projects/vstudio/x64/Release\ Library>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(cairo.gurd PRIVATE cxx_std_17)
target_precompile_headers(cairo.gurd PRIVATE stdafx.h)
target_compile_options(cairo.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(cairo.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(cairo.gurd PRIVATE
	module-cairo.cpp
	Util.cpp
	Consts.cpp
	Functions.cpp
	VType_cairo_t.cpp
	VType_cairo_device_t.cpp
	VType_cairo_font_extents_t.cpp
	VType_cairo_font_face_t.cpp
	VType_cairo_font_options_t.cpp
	VType_cairo_glyph_t.cpp
	VType_cairo_matrix_t.cpp
	VType_cairo_path_t.cpp
	VType_cairo_pattern_t.cpp
	VType_cairo_rectangle_t.cpp
	VType_cairo_rectangle_int_t.cpp
	VType_cairo_rectangle_list_t.cpp
	VType_cairo_region_t.cpp
	VType_cairo_scaled_font_t.cpp
	VType_cairo_surface_t.cpp
	VType_cairo_text_cluster_t.cpp
	VType_cairo_text_extents_t.cpp
	)

#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(cairo.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT -NODEFAULTLIB:MSVCRT -LTCG -INCREMENTAL:NO>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(cairo.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:cairo-static>
	$<$<PLATFORM_ID:Windows>:libpng16>
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS cairo.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/cairo.gura
	DESTINATION module/site)
