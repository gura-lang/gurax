#===============================================================================
# CMakeLists for module: diff
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_diff)

add_library(diff.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(diff.gurd PRIVATE
	${GURAX_BASEDIR}/include
	${PROJECT_SOURCE_DIR}/dtl-1.19-gurax)
target_link_directories(diff.gurd PRIVATE ${GURAX_BASEDIR}/lib)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(diff.gurd PRIVATE cxx_std_17)
target_precompile_headers(diff.gurd PRIVATE stdafx.h)
target_compile_options(diff.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(diff.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(diff.gurd PRIVATE
	module-diff.cpp
	Util.cpp
	Diff.cpp
	Hunk.cpp
	VType_Diff.cpp
	VType_Edit.cpp
	VType_Hunk.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(diff.gurd PRIVATE guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS diff.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
    script/diff.gura
    DESTINATION module/site)
