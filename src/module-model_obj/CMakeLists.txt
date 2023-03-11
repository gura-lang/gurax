#===============================================================================
# CMakeLists for module: model.obj
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_model_obj)

add_library(model.obj.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(model.obj.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(model.obj.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../lib
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(model.obj.gurd PRIVATE cxx_std_17)
target_precompile_headers(model.obj.gurd PRIVATE stdafx.h)
target_compile_options(model.obj.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(model.obj.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(model.obj.gurd PRIVATE
	module-model_obj.cpp
	Util.cpp
	Beval.cpp
	Bmat.cpp
	CallObj.cpp
	Connect.cpp
	Content.cpp
	Csh.cpp
	Cstype.cpp
	Ctech.cpp
	Curv.cpp
	Curv2.cpp
	C_interp.cpp
	Deg.cpp
	D_interp.cpp
	Face.cpp
	GroupName.cpp
	Hole.cpp
	Index.cpp
	Line.cpp
	Lod.cpp
	Maplib.cpp
	MergingGroup.cpp
	Mtllib.cpp
	ObjectName.cpp
	Parm.cpp
	Point.cpp
	Scrv.cpp
	Shadow_obj.cpp
	SmoothingGroup.cpp
	Spoint.cpp
	Stech.cpp
	Step.cpp
	Surf.cpp
	Trace_obj.cpp
	Trim.cpp
	Usemap.cpp
	Usemtl.cpp
	Vertex3.cpp
	Vertex4.cpp
	VType_Beval.cpp
	VType_Bmat.cpp
	VType_CallObj.cpp
	VType_Connect.cpp
	VType_Content.cpp
	VType_Csh.cpp
	VType_Cstype.cpp
	VType_Ctech.cpp
	VType_Curv.cpp
	VType_Curv2.cpp
	VType_C_interp.cpp
	VType_Deg.cpp
	VType_D_interp.cpp
	VType_Face.cpp
	VType_GroupName.cpp
	VType_Hole.cpp
	VType_Line.cpp
	VType_Lod.cpp
	VType_Maplib.cpp
	VType_MergingGroup.cpp
	VType_Mtllib.cpp
	VType_ObjectName.cpp
	VType_Parm.cpp
	VType_Point.cpp
	VType_Scrv.cpp
	VType_Shadow_obj.cpp
	VType_SmoothingGroup.cpp
	VType_Spoint.cpp
	VType_Stech.cpp
	VType_Step.cpp
	VType_Surf.cpp
	VType_Trace_obj.cpp
	VType_Trim.cpp
	VType_Usemap.cpp
	VType_Usemtl.cpp
	VType_Vertex3.cpp
	VType_Vertex4.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(model.obj.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(model.obj.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS model.obj.gurd RUNTIME DESTINATION module/site)
