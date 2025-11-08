#===============================================================================
# CMakeLists for module: png
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_png)

add_library(png.gurd MODULE)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(png.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/libpng-1.6.50>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/include/libpng>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/include/libpng>)
target_link_directories(png.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/libpng-1.6.50>
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/zlib-1.2.11>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest/lib>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest/lib>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(png.gurd PRIVATE cxx_std_17)
target_precompile_headers(png.gurd PRIVATE stdafx.h)
target_compile_options(png.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(png.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(png.gurd PRIVATE
	module-png.cpp
	Util.cpp
	ImageExtension.cpp
	Content.cpp
	VType_Content.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_MODULE_PREFIX)
set(CMAKE_SHARED_MODULE_SUFFIX)
target_link_options(png.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT -INCREMENTAL:NO>)
target_link_libraries(png.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libpng>
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Linx>:png16>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Darwin>:png16>
	$<$<PLATFORM_ID:Darwin>:z>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS png.gurd LIBRARY DESTINATION module/site)
