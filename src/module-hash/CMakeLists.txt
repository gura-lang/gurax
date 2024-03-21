#===============================================================================
# CMakeLists for module: hash
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_hash)

add_library(hash.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(hash.gurd PRIVATE
	${GURAX_BASEDIR}/include
	${PROJECT_SOURCE_DIR}/guest/md5
	${PROJECT_SOURCE_DIR}/guest/sha1)
target_link_directories(hash.gurd PRIVATE
	${GURAX_BASEDIR}/lib)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(hash.gurd PRIVATE cxx_std_17)
target_precompile_headers(hash.gurd PRIVATE stdafx.h)
target_compile_options(hash.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(hash.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(hash.gurd PRIVATE
	module-hash.cpp
	Util.cpp
	Accumulator.cpp
	VType_Accumulator.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(hash.gurd PRIVATE guraxcore guest)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS hash.gurd RUNTIME DESTINATION module/site)
#-------------------------------------------------------------------------------
# Dependency
#-------------------------------------------------------------------------------
add_subdirectory(guest)
