#===============================================================================
# CMakeLists for module: jpeg
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_jpeg)

add_library(jpeg.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(jpeg.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/include/libjpeg>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest/include/libjpeg>)
target_link_directories(jpeg.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/lib>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest/lib>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(jpeg.gurd PRIVATE cxx_std_17)
target_precompile_headers(jpeg.gurd PRIVATE stdafx.h)
target_compile_options(jpeg.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(jpeg.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(jpeg.gurd PRIVATE
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
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(jpeg.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT>)
target_link_libraries(jpeg.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libjpeg>
	$<$<PLATFORM_ID:Linx>:jpeg>
	$<$<PLATFORM_ID:Darwin>:jpeg>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS jpeg.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS script/jpeg.gura DESTINATION module/site)
install(PROGRAMS script/jpeg-editexif.gura script/jpeg-printexif.gura DESTINATION script)
