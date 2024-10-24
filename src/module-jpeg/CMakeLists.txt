#===============================================================================
# CMakeLists for module: jpeg
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_jpeg)

add_library(jpeg.gurd MODULE)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(jpeg.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/include/libjpeg>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/include/libjpeg>)
target_link_directories(jpeg.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/jpeg-9d>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/lib>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/lib>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
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
set(CMAKE_SHARED_MODULE_PREFIX)
set(CMAKE_SHARED_MODULE_SUFFIX)
target_link_options(jpeg.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT>)
target_link_libraries(jpeg.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libjpeg>
	$<$<PLATFORM_ID:Linx>:jpeg>
	$<$<PLATFORM_ID:Darwin>:jpeg>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS jpeg.gurd LIBRARY DESTINATION module/site)
install(PROGRAMS script/jpeg.gura DESTINATION module/site)
install(PROGRAMS script/jpeg-editexif.gura script/jpeg-printexif.gura DESTINATION script)
