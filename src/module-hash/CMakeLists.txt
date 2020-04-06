#===============================================================================
# CMakeLists for module: hash
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_hash)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
include_directories(md5 sha1)
add_library(hash SHARED
    module-hash.cpp
    Util.cpp
    md5/md5.c
    sha1/sha1.c
    Accumulator.cpp
    VType_Accumulator.cpp
)
target_link_libraries(hash guraxcore)
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS hash RUNTIME DESTINATION module/site)