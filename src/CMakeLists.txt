project(gurax)

cmake_minimum_required(VERSION 2.8)

set(GURAX_VERSION_MAJOR		0)
set(GURAX_VERSION_MINOR		1)
set(GURAX_VERSION_PATCH		0)
set(GURAX_VERSION			${GURAX_VERSION_MAJOR}.${GURAX_VERSION_MINOR}.${GURAX_VERSION_PATCH})
set(GURAX_VERSION_SO		${GURAX_VERSION_MAJOR})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_INSTALL_PREFIX /Applications/GURAX.app/Contents/Resources)
else()
	set(CMAKE_INSTALL_PREFIX /usr)
endif()

add_definitions("-Wall -std=c++14")

set(GURAX_RELDIR_BINARY		bin)
set(GURAX_RELDIR_LIBRARY	lib)

set(GURAX_SRCDIR_ROOT		${PROJECT_SOURCE_DIR}/..)
set(GURAX_SRCDIR_INCLUDE	${GURAX_SRCDIR_ROOT}/include)

include_directories(
	${GURAX_SRCDIR_INCLUDE})

add_subdirectory(lib)
add_subdirectory(gurax)
