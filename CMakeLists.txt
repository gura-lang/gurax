#===============================================================================
# CMakeLists for gurax project
#===============================================================================
cmake_minimum_required(VERSION 3.16) # 3.16 or newer supports handling of precompiled header
project(GURAX
	VERSION			0.0.1
	DESCRIPTION 	"Gurax Programming Language"
	HOMEPAGE_URL	http://www.gura-lang.org/
	LANGUAGES		CXX)

set(GURAX_COPYRIGHT "Copyright (C) 2011-2024 ypsitau")

configure_file(
	${PROJECT_SOURCE_DIR}/include/gurax/Version.h.in
	${PROJECT_SOURCE_DIR}/include/gurax/Version.h)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
elseif (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	set(CMAKE_INSTALL_PREFIX /usr)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
	set(CMAKE_INSTALL_PREFIX /Applications/GURAX.app/Contents/Resources)
else ()
	set(CMAKE_INSTALL_PREFIX /usr)
endif ()

add_subdirectory(src)
