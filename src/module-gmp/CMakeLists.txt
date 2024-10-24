#===============================================================================
# CMakeLists for module: gmp
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_gmp)

add_library(gmp.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(gmp.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/mpir-3.0.0/lib/x64/Release>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
target_link_directories(gmp.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/mpir-3.0.0/lib/x64/Release>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(gmp.gurd PRIVATE cxx_std_17)
target_precompile_headers(gmp.gurd PRIVATE stdafx.h)
target_compile_options(gmp.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(gmp.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(gmp.gurd PRIVATE
	module-gmp.cpp
	Util.cpp
	Operators.cpp
	Random.cpp
	VType_Float.cpp
	VType_Int.cpp
	VType_Random.cpp
	VType_Rational.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(gmp.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:/NODEFAULTLIB:LIBCMT>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(gmp.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:mpir.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gmp.gurd RUNTIME DESTINATION module/site)
