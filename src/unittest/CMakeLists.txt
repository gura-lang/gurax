#===============================================================================
# CMakeLists for unittest executable
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(unittest)

add_executable(unittest)
#-------------------------------------------------------------------------------
# Directory Information
#-------------------------------------------------------------------------------
target_include_directories(unittest PRIVATE
	${PROJECT_SOURCE_DIR}/../../include ${PROJECT_SOURCE_DIR})
target_link_directories(unittest PRIVATE ${PROJECT_SOURCE_DIR}/../../lib)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
#-------------------------------------------------------------------------------
# Compile
#-------------------------------------------------------------------------------
target_precompile_headers(unittest PRIVATE stdafx.h)
target_sources(unittest PRIVATE
	unittest.cpp
	SampleRecord.cpp
	test-Argument.cpp
	test-CommandLine.cpp
	test-DateTime.cpp
	test-DeclCallable.cpp
	test-Directory.cpp
	test-Error.cpp
	test-Formatter.cpp
	test-Function.cpp
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
