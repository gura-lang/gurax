#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax)

add_executable(gurax)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(gurax PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(gurax PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
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
target_link_libraries(gurax PRIVATE guraxcore) # ${LIBREADLINE}
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS gurax RUNTIME DESTINATION bin)
