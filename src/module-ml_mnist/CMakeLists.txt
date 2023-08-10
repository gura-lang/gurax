#===============================================================================
# CMakeLists for module: ml.mnist
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_ml_mnist)

add_library(ml.mnist.gurd SHARED)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(ml.mnist.gurd PRIVATE
	${PROJECT_SOURCE_DIR}/../../include
	$<$<PLATFORM_ID:Windows>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Linux>:${PROJECT_SOURCE_DIR}/../../guest>
	$<$<PLATFORM_ID:Darwin>:${PROJECT_SOURCE_DIR}/../../guest>)
target_link_directories(ml.mnist.gurd PRIVATE
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
target_compile_features(ml.mnist.gurd PRIVATE cxx_std_17)
target_precompile_headers(ml.mnist.gurd PRIVATE stdafx.h)
target_compile_options(ml.mnist.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_compile_definitions(ml.mnist.gurd PRIVATE GURAX_MODULE_SEPARATED
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_sources(ml.mnist.gurd PRIVATE
	module-ml_mnist.cpp
	Util.cpp
	Sample.cpp
	ImageSet.cpp
	LabelSet.cpp
	SampleSet.cpp
	VType_Sample.cpp
	VType_ImageSet.cpp
	VType_LabelSet.cpp
	VType_SampleSet.cpp)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_SHARED_LIBRARY_SUFFIX)
target_link_options(ml.mnist.gurd PRIVATE
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
target_link_libraries(ml.mnist.gurd PRIVATE guraxcore
	$<$<PLATFORM_ID:Windows>:>
	$<$<PLATFORM_ID:Linux>:>
	$<$<PLATFORM_ID:Darwin>:>)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS ml.mnist.gurd RUNTIME DESTINATION module/site)
install(PROGRAMS script/ml.mnist_common.gura script/ml.mnist.gura script/ml.qmnist.gura DESTINATION module/site)
