#===============================================================================
# CMakeLists for module: diff
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_diff)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
include_directories(${PROJECT_SOURCE_DIR}/dtl-1.19-gurax)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
add_library(diff SHARED
    module-diff.cpp
    Util.cpp
    DiffLine.cpp
    EditLine.cpp
    VType_DiffLine.cpp
    VType_EditLine.cpp
    VType_HunkLine.cpp
)
target_link_libraries(diff guraxcore)
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
target_precompile_headers(diff PUBLIC stdafx.h)
install(TARGETS diff RUNTIME DESTINATION module/site)
