#===============================================================================
# CMakeLists for unittest executable
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(unittest)

add_executable(unittest)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
set(GURAX_BASEDIR ${PROJECT_SOURCE_DIR}/../..)
target_include_directories(unittest PRIVATE ${GURAX_BASEDIR}/include ${PROJECT_SOURCE_DIR})
target_link_directories(unittest PRIVATE ${GURAX_BASEDIR}/lib)
set(CMAKE_INSTALL_PREFIX ${GURAX_BASEDIR})
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(unittest PRIVATE cxx_std_17)
target_precompile_headers(unittest PRIVATE stdafx.h)
target_compile_options(unittest PRIVATE
	$<$<PLATFORM_ID:Windows>:-W3>
	$<$<PLATFORM_ID:Linux>:-Wall -O2>
	$<$<PLATFORM_ID:Darwin>:-Wall -O2>)
target_sources(unittest PRIVATE
	unittest.cpp
	SampleRecord.cpp
	test-Argument.cpp
	test-CommandLine.cpp
	test-DateTime.cpp
	test-DeclCallable.cpp
	test-Directory.cpp
	test-Error.cpp
	test-FIFO.cpp
	test-Formatter.cpp
	test-Function.cpp
	test-Half.cpp
	test-Help.cpp
	test-Iterator.cpp
	test-MemoryPool.cpp
	test-Number.cpp
	test-OAL.cpp
	test-Parser.cpp
	test-PathName.cpp
	test-PropSlot.cpp
	test-PUnit.cpp
	test-Random.cpp
	test-Referable.cpp
	test-SizeOf.cpp
	test-Stream.cpp
	test-String.cpp
	test-Symbol.cpp
	test-Tokenizer.cpp
	test-Value.cpp
)
#-------------------------------------------------------------------------------
# Link
#-------------------------------------------------------------------------------
target_link_libraries(unittest guraxcore)
#-------------------------------------------------------------------------------
# Install
#-------------------------------------------------------------------------------
install(TARGETS unittest RUNTIME DESTINATION bin)
