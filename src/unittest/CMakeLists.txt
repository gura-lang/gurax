add_executable(unittest
	unittest.cpp
	test-DateTime.cpp
	test-Function.cpp
	test-Help.cpp
	test-Iterator.cpp
	test-MemoryPool.cpp
	test-Object.cpp
	test-Parser.cpp
	test-Random.cpp
	test-Referable.cpp
	test-SizeOf.cpp
	test-Stream.cpp
	test-Symbol.cpp
	test-Tokenizer.cpp
)

find_library(LIBREADLINE readline REQUIRED)

target_link_libraries(unittest guraxcore ${LIBREADLINE})
