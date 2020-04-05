cmake_minimum_required(VERSION 3.16)
project(gurax_module_png)

include_directories(
    ${PROJECT_SOURCE_DIR}/../../include
    ${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37
)
link_directories(
    ${PROJECT_SOURCE_DIR}/../../lib
    "${PROJECT_SOURCE_DIR}/../../guest/libpng-1.6.37/projects/vstudio/x64/Release Library"
)

add_definitions("-DGURAX_MODULE_SEPARATED")
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)

add_library(png SHARED
    module-png.cpp
    Util.cpp
)

target_link_libraries(png guraxcore libpng16)
install(TARGETS png RUNTIME DESTINATION module/site)
