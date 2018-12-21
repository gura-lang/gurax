add_executable(unittest
	unittest.cpp
	test-MemoryPool.cpp
	test-Object.cpp
	test-Parser.cpp
	test-Referable.cpp
	test-Symbol.cpp
	test-Tokenizer.cpp
)

find_library(LIBREADLINE readline REQUIRED)

target_link_libraries(unittest guraxcore ${LIBREADLINE})
