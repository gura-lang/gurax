#===============================================================================
# CMakeLists for module: zip
# debFiles = ['zlib1g', 'libbz2']
# rpmFiles = ['zlib', 'bzip2']
# debFilesDevel = ['zlib1g-dev', 'libbz2-dev']
# rpmFilesDevel = ['zlib-devel', 'bzip2-devel']
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_zip)

add_library(zip.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if (PROJECT_IS_TOP_LEVEL)
	execute_process(COMMAND gurax --naked -p "sys.dirModule.Chop()" OUTPUT_VARIABLE GURAX_MODULEDIR)
	execute_process(COMMAND gurax --naked -p "sys.version" OUTPUT_VARIABLE GURAX_VERSION)
else()
	set(GURAX_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(GURAX_MODULEDIR ${GURAX_BASEDIR}/module/site)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(GURAX_MODULEDIR ${CMAKE_INSTALL_PREFIX}/lib/gurax/${GURAX_VERSION}/module/site)
endif()
target_include_directories(zip.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:
		${GURAX_BASEDIR}/guest/zlib-1.2.11
		${GURAX_BASEDIR}/guest/bzip2-1.0.8>)
target_link_directories(zip.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:
		${GURAX_BASEDIR}/guest/zlib-1.2.11
		${GURAX_BASEDIR}/guest/bzip2-1.0.8>)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(zip.gurd PRIVATE cxx_std_17)
target_precompile_headers(zip.gurd PRIVATE stdafx.h)
target_compile_options(zip.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(zip.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(zip.gurd PRIVATE
	module-zip.cpp
	Util.cpp
	ZIPFormat.cpp
	Reader.cpp
	Writer.cpp
	PathExtension.cpp
	VType_Reader.cpp
	VType_Writer.cpp
	VType_StatEx.cpp
	VType_bzip2.cpp
	VType_gzip.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(zip.gurd PRIVATE
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:-NODEFAULTLIB:MSVCRT>)
target_link_libraries(zip.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Windows>:libbz2>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Linx>:bz2>
	$<$<PLATFORM_ID:Darwin>:z>
	$<$<PLATFORM_ID:Darwin>:bz2>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS zip.gurd LIBRARY DESTINATION ${GURAX_MODULEDIR})
