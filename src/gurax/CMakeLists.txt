#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax)

add_executable(gurax)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
target_include_directories(gurax PRIVATE ${GURAX_BASEDIR}/include)
target_link_directories(gurax PRIVATE ${GURAX_BASEDIR}/lib)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(gurax PRIVATE cxx_std_17)
target_precompile_headers(gurax PRIVATE stdafx.h)
target_compile_options(gurax PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_sources(gurax PRIVATE gurax.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
target_link_libraries(gurax PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:readline>
	$<$<PLATFORM_ID:Darwin>:readline>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gurax
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION bin)
