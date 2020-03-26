#===============================================================================
# CMakeLists for unittest executable
#===============================================================================
add_executable(unittest
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
	test-PropHandler.cpp
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

#find_library(LIBREADLINE readline REQUIRED)

#target_link_libraries(unittest guraxcore ${LIBREADLINE})

target_link_libraries(unittest guraxcore)
