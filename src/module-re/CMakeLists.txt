#===============================================================================
# CMakeLists for module: re
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_re)

add_library(re.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(re.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/onigmo-6.2.0>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/include/onigmo>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest/include/onigmo>)
target_link_directories(re.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/onigmo-6.2.0/build_x86>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest/lib>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest/lib>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(re.gurd PRIVATE cxx_std_17)
target_precompile_headers(re.gurd PRIVATE stdafx.h)
target_compile_options(re.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(re.gurd PRIVATE GURAX_MODULE_SEPARATED
    $<$<PLATFORM_ID:Windows>:ONIG_EXTERN=extern>)
target_sources(re.gurd PRIVATE
    module-re.cpp
    Util.cpp
    Group.cpp
    Iterators.cpp
    Match.cpp
    Pattern.cpp
    VType_Group.cpp
    VType_Match.cpp
    VType_Pattern.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(re.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT -LTCG -INCREMENTAL:NO>)
target_link_libraries(re.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:onigmo_s>
	$<$<PLATFORM_ID:Linx>:onigmo>
	$<$<PLATFORM_ID:Darwin>:onigmo>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS re.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
    script/sed.doc.gura
    script/sed.gura
    script/tokenizer.doc.gura
    script/tokenizer.gura
    DESTINATION module/site)
