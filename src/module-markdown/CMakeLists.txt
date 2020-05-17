#===============================================================================
# CMakeLists for module: markdown
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_markdown)

add_library(markdown.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(markdown.gurd PRIVATE ${PROJECT_SOURCE_DIR}/../../include)
target_link_directories(markdown.gurd PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(markdown.gurd PRIVATE stdafx.h)
target_compile_definitions(markdown.gurd PRIVATE GURAX_MODULE_SEPARATED)
target_sources(markdown.gurd PRIVATE
	module-markdown.cpp
	Util.cpp
	Document.cpp
	Item.cpp
	VType_Document.cpp
	VType_Item.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_libraries(markdown.gurd PRIVATE guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS markdown.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script-module/markdown.composer.gura
	script-module/markdown.console.gura
	script-module/markdown.gura
	script-module/markdown.html.gura
	script-module/markdown.rtf.gura
	script-module/markdown.tex.gura
	script-module/markdown.toc.gura
	DESTINATION module/site)
