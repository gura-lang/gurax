#===============================================================================
# CMakeLists for module: zip
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_zip)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    include_directories(
        ${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
        ${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8
    )
    link_directories(
        ${PROJECT_SOURCE_DIR}/../../guest/zlib-1.2.11
        ${PROJECT_SOURCE_DIR}/../../guest/bzip2-1.0.8
    )
    set(GUEST_LIBRARY zlib libbz2)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(GUEST_LIBRARY z bz2)
else ()
    set(GUEST_LIBRARY z bz2)
endif ()
add_library(zip SHARED
    module-zip.cpp
    Util.cpp
    ZIPFormat.cpp
    Reader.cpp
    Writer.cpp
    PathExtension.cpp
    VType_Reader.cpp
    VType_Writer.cpp
    VType_StatEx.cpp
)
target_link_libraries(zip guraxcore ${GUEST_LIBRARY})
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
install(TARGETS zip RUNTIME DESTINATION module/site)
