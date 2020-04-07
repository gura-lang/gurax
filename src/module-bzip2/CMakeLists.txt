#===============================================================================
# CMakeLists for module: bzip2
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_bzip2)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    include_directories(${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8)
    link_directories(${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8)
	#add_link_options(-NODEFAULTLIB:MSVCRT)
    set(GUEST_LIBRARY libbz2)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(GUEST_LIBRARY bz2)
else ()
    set(GUEST_LIBRARY bz2)
endif ()
add_library(bzip2 SHARED
    module-bzip2.cpp
    Util.cpp
)
target_link_libraries(bzip2 guraxcore ${GUEST_LIBRARY})
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
target_precompile_headers(bzip2 PUBLIC stdafx.h)
install(TARGETS bzip2 RUNTIME DESTINATION module/site)
