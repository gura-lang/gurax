#===============================================================================
# CMakeLists for module: ml
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_ml)

add_library(ml.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
if(EXISTS ${PROJECT_SOURCE_DIR}/../gurax/gurax.cpp)
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
else()
execute_process(COMMAND gurax -p "sys.dirBase.Chop()" OUTPUT_VARIABLE GURAX_BASEDIR)
endif()
target_include_directories(ml.gurd PRIVATE
	${GURAX_BASEDIR}/include
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
target_link_directories(ml.gurd PRIVATE
	${GURAX_BASEDIR}/lib
	$<$<PLATFORM_ID:Windows>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Linux>:${GURAX_BASEDIR}/guest>
	$<$<PLATFORM_ID:Darwin>:${GURAX_BASEDIR}/guest>)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(ml.gurd PRIVATE cxx_std_17)
target_precompile_headers(ml.gurd PRIVATE stdafx.h)
target_compile_options(ml.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(ml.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(ml.gurd PRIVATE
	module-ml.cpp
	Util.cpp
	Symbols.cpp
	Trainer.cpp
	Node.cpp
	NodeMap.cpp
	Optimizers.cpp
	Conv1d.cpp
	Conv2d.cpp
	Conv3d.cpp
	Dropout.cpp
	Flatten.cpp
	Linear.cpp
	MaxPool1d.cpp
	MaxPool2d.cpp
	MaxPool3d.cpp
	ReLU.cpp
	Reshape.cpp
	Sigmoid.cpp
	Softmax.cpp
	Tanh.cpp
	VType_Trainer.cpp
	VType_Node.cpp
	VType_NodeMap.cpp
	VType_Optimizer.cpp
	VType_Conv1d.cpp
	VType_Conv2d.cpp
	VType_Conv3d.cpp
	VType_Dropout.cpp
	VType_Flatten.cpp
	VType_Linear.cpp
	VType_MaxPool1d.cpp
	VType_MaxPool2d.cpp
	VType_MaxPool3d.cpp
	VType_ReLU.cpp
	VType_Reshape.cpp
	VType_Sigmoid.cpp
	VType_Softmax.cpp
	VType_Tanh.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(ml.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(ml.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS ml.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS script/ml.gura DESTINATION module/site)
