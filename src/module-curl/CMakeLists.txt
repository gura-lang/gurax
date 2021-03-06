#===============================================================================
# CMakeLists for module: curl
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_curl)

add_library(curl.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(curl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/curl-7.73.0/include>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(curl.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/curl-7.73.0/builds/libcurl-vc-x64-release-static-ipv6-sspi-schannel/lib>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(curl.gurd PRIVATE cxx_std_17)
target_precompile_headers(curl.gurd PRIVATE stdafx.h)
target_compile_options(curl.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(curl.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:CURL_STATICLIB>)
target_sources(curl.gurd PRIVATE
	module-curl.cpp
	Util.cpp
	Consts.cpp
	Info.cpp
	Opt.cpp
	PathExtension.cpp
	Functions.cpp
	VTYPE_CURL.cpp
	VTYPE_CURLU.cpp
	VTYPE_curl_mime.cpp
	VTYPE_curl_mimepart.cpp
	VTYPE_curl_slist.cpp
	VTYPE_Info.cpp
	VTYPE_Opt.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(curl.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:/NODEFAULTLIB:msvcrt>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(curl.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libcurl_a.lib>
	$<$<PLATFORM_ID:Windows>:ws2_32.lib>
	$<$<PLATFORM_ID:Windows>:crypt32.lib>
	$<$<PLATFORM_ID:Windows>:wldap32.lib>
	$<$<PLATFORM_ID:Windows>:normaliz.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS curl.gurd RUNTIME DESTINATION module/site)
