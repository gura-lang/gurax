add_executable(unittest
	unittest.cpp)

find_library(LIBREADLINE readline REQUIRED)

target_link_libraries(unittest guraxcore ${LIBREADLINE})
