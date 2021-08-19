#===============================================================================
# CMakeLists for module: wx
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_wx)

include(VTypes.cmake)

add_library(wx.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(wx.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.4/include>
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.4/lib/vc_x64_dll/mswu>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(wx.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.4/lib/vc_x64_dll>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(wx.gurd PRIVATE cxx_std_17)
target_precompile_headers(wx.gurd PRIVATE stdafx.h)
target_compile_options(wx.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(wx.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:WXUSINGDLL>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(wx.gurd PRIVATE
	module-wx.cpp
	Consts.cpp
	Events.cpp
	Functions.cpp
	MultiEvents.cpp
	Objects.cpp
	Util.cpp
	VTypes.cpp
	${SRCFILES_VTYPE})
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(wx.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(wx.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:wxbase31ud>
	$<$<PLATFORM_ID:Windows>:wxbase31ud_net>
	$<$<PLATFORM_ID:Windows>:wxbase31ud_xml>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_adv>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_aui>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_core>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_gl>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_html>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_media>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_propgrid>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_qa>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_ribbon>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_richtext>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_stc>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_webview>
	$<$<PLATFORM_ID:Windows>:wxmsw31ud_xrc>
	$<$<PLATFORM_ID:Windows>:wxexpatd>
	$<$<PLATFORM_ID:Windows>:wxjpegd>
	$<$<PLATFORM_ID:Windows>:wxpngd>
	$<$<PLATFORM_ID:Windows>:wxregexud>
	$<$<PLATFORM_ID:Windows>:wxscintillad>
	$<$<PLATFORM_ID:Windows>:wxtiffd>
	$<$<PLATFORM_ID:Windows>:wxzlibd>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS wx.gurd RUNTIME DESTINATION module/site)
