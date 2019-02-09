add_executable(unittest
	unittest.cpp
	SampleRecord.cpp
	test-DateTime.cpp
	test-DeclCaller.cpp
	test-Function.cpp
	test-Help.cpp
	test-Iterator.cpp
	test-MemoryPool.cpp
	test-Parser.cpp
	test-Random.cpp
	test-Referable.cpp
	test-SizeOf.cpp
	test-Stream.cpp
	test-String.cpp
	test-Symbol.cpp
	test-Tokenizer.cpp
	test-Value.cpp
)

find_library(LIBREADLINE readline REQUIRED)

target_link_libraries(unittest guraxcore ${LIBREADLINE})
