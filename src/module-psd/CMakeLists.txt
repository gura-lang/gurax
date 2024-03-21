#===============================================================================
# CMakeLists for module: psd
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_psd)

add_library(psd.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(psd.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
target_link_directories(psd.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(psd.gurd PRIVATE cxx_std_17)
target_precompile_headers(psd.gurd PRIVATE stdafx.h)
target_compile_options(psd.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(psd.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(psd.gurd PRIVATE
	module-psd.cpp
	Util.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(psd.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(psd.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS psd.gurd RUNTIME DESTINATION module/site)
