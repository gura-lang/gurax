#===============================================================================
# CMakeLists for module: gzip
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_gzip)

add_library(gzip.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(gzip.gurd PRIVATE
	${GURAX_BASEDIR}/include
	${GURAX_BASEDIR}/guest/zlib-1.2.11)
target_link_directories(gzip.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	${GURAX_BASEDIR}/guest/zlib-1.2.11)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(gzip.gurd PRIVATE cxx_std_17)
target_precompile_headers(gzip.gurd PRIVATE stdafx.h)
target_compile_options(gzip.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(gzip.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(gzip.gurd PRIVATE
	module-gzip.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(gzip.gurd PRIVATE
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:-NODEFAULTLIB:MSVCRT>)
target_link_libraries(gzip.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:zlib>
	$<$<PLATFORM_ID:Linx>:z>
	$<$<PLATFORM_ID:Darwin>:z>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gzip.gurd RUNTIME DESTINATION module/site)
