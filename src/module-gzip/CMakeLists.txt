#===============================================================================
# CMakeLists for module: gzip
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_gzip)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    include_directories(${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11)
    link_directories(${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11)
    set(GUEST_LIBRARY zlib)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(GUEST_LIBRARY z)
else ()
    set(GUEST_LIBRARY z)
endif ()
add_library(gzip SHARED
    module-gzip.cpp
    Util.cpp
)
target_link_libraries(gzip guraxcore ${GUEST_LIBRARY})
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
target_precompile_headers(gzip PUBLIC stdafx.h)
install(TARGETS gzip RUNTIME DESTINATION module/site)
