#===============================================================================
# CMakeLists for module: yaml
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_yaml)

add_library(yaml.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(yaml.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/yaml-0.2.5/include>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(yaml.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/yaml-0.2.5/build>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(yaml.gurd PRIVATE cxx_std_17)
target_precompile_headers(yaml.gurd PRIVATE stdafx.h)
target_compile_options(yaml.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(yaml.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:YAML_DECLARE_STATIC>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(yaml.gurd PRIVATE
	module-yaml.cpp
	Util.cpp
	Emitter.cpp
	Parser.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(yaml.gurd PRIVATE
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:-NODEFAULTLIB:MSVCRTD>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(yaml.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:yaml.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS yaml.gurd RUNTIME DESTINATION module/site)
