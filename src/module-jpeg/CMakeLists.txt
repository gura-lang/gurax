#===============================================================================
# CMakeLists for module: jpeg
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_jpeg)

add_library(jpeg SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(jpeg PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/guest/include/libjpeg>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/guest/include/libjpeg>)
target_link_directories(jpeg PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/guest/lib>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/guest/lib>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(jpeg PRIVATE stdafx.h)
target_compile_definitions(jpeg PRIVATE GURAX_MODULE_SEPARATED)
target_sources(jpeg PRIVATE
	module-jpeg.cpp
	DataType.cpp
	Symbol.cpp
	Util.cpp
	ImageExtension.cpp
	Content.cpp
	Exif.cpp
	IFD.cpp
	JFIF.cpp
	Segment.cpp
	Tag.cpp
	VType_Content.cpp
	VType_Exif.cpp
	VType_IFD.cpp
	VType_JFIF.cpp
	VType_Segment.cpp
	VType_Tag.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
target_link_options(jpeg PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT>)
target_link_libraries(jpeg PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libjpeg>
	$<$<PLATFORM_ID:Linx>:jpeg>
	$<$<PLATFORM_ID:Darwin>:jpeg>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS jpeg RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/print-exif.gura
	DESTINATION script)
