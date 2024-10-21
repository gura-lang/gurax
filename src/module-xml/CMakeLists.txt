#===============================================================================
# CMakeLists for module: xml
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_xml)

add_library(xml.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax --naked -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(xml.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/expat-2.4.9/lib>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
target_link_directories(xml.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest/expat-2.4.9/build/Release>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(xml.gurd PRIVATE cxx_std_17)
target_precompile_headers(xml.gurd PRIVATE stdafx.h)
target_compile_options(xml.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(xml.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:XML_STATIC>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(xml.gurd PRIVATE
	module-xml.cpp
	Attr.cpp
	CData.cpp
	Comment.cpp
	CP932.cpp
	Document.cpp
	Element.cpp
	Node.cpp
	Parser.cpp
	Symbols.cpp
	Text.cpp
	Util.cpp
	XmlDecl.cpp
	VType_Attr.cpp
	VType_Attrs.cpp
	VType_CData.cpp
	VType_Comment.cpp
	VType_Document.cpp
	VType_Element.cpp
	VType_Node.cpp
	VType_Nodes.cpp
	VType_Text.cpp
	VType_XmlDecl.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(xml.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-NODEFAULTLIB:LIBCMT>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(xml.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:libexpatMT.lib>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS xml.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS
	script/xml.gura
	DESTINATION module/site)
