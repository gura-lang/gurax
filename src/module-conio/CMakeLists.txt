#===============================================================================
# CMakeLists for module: conio
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_conio)

add_library(conio.gurd MODULE)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(conio.gurd PRIVATE ${GURAX_BASEDIR}/include)
target_link_directories(conio.gurd PRIVATE ${GURAX_BASEDIR}/lib)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(conio.gurd PRIVATE cxx_std_17)
target_precompile_headers(conio.gurd PRIVATE stdafx.h)
target_compile_options(conio.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(conio.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(conio.gurd PRIVATE
	module-conio.cpp
	Util.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_MODULE_PREFIX)
set(CMAKE_SHARED_MODULE_SUFFIX)
target_link_libraries(conio.gurd PRIVATE guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS conio.gurd LIBRARY DESTINATION module/site)
install(PROGRAMS
	script/conio.progress.gura
	DESTINATION module/site)
