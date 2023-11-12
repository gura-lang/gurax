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
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.5/include>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.5/lib/vc_x64_dll/mswu>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.5/lib/vc_x64_dll/mswud>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(wx.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest/wxWidgets-3.1.5/lib/vc_x64_dll>
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
	$<$<PLATFORM_ID:Windows>:module-wx.rc>
	Consts.cpp
	Events.cpp
	Functions.cpp
	Operators.cpp
	MultiEvents.cpp
	Objects.cpp
	Util.cpp
	VTypes.cpp
	VType_wxAppConsole_HandCode.cpp
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
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxbase31u>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxbase31u_net>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxbase31u_xml>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_adv>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_aui>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_core>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_gl>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_html>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_media>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_propgrid>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_qa>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_ribbon>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_richtext>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_stc>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_webview>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxmsw31u_xrc>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxexpat>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxjpeg>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxpng>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxregexu>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxscintilla>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxtiff>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Release>>:wxzlib>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxbase31ud>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxbase31ud_net>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxbase31ud_xml>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_adv>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_aui>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_core>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_gl>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_html>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_media>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_propgrid>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_qa>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_ribbon>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_richtext>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_stc>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_webview>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxmsw31ud_xrc>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxexpatd>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxjpegd>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxpngd>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxregexud>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxscintillad>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxtiffd>
	$<$<AND:$<PLATFORM_ID:Windows>,$<CONFIG:Debug>>:wxzlibd>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS wx.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/wx.show.gura
	DESTINATION module/site)
