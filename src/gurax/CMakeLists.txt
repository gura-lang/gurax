add_executable(gurax
	gurax.cpp
	Tokenizer.cpp)

find_library(LIBREADLINE readline REQUIRED)

target_link_libraries(gurax guraxcore ${LIBREADLINE})

set(GURAX_SRCDIR_ROOT		${PROJECT_SOURCE_DIR}/..)
set(GURAX_SRCDIR_INCLUDE	${GURAX_SRCDIR_ROOT}/include)

include_directories(
	${GURAX_SRCDIR_INCLUDE})

install(TARGETS gurax DESTINATION ${GURAX_RELDIR_BINARY})
