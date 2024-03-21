#===============================================================================
# CMakeLists for module: markdown
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_markdown)

add_library(markdown.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(markdown.gurd PRIVATE ${GURAX_BASEDIR}/include)
target_link_directories(markdown.gurd PRIVATE ${GURAX_BASEDIR}/lib)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(markdown.gurd PRIVATE cxx_std_17)
target_precompile_headers(markdown.gurd PRIVATE stdafx.h)
target_compile_options(markdown.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
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
