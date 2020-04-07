#===============================================================================
# CMakeLists for module: jpeg
#===============================================================================
cmake_minimum_required(VERSION 3.16)
project(gurax_module_jpeg)

include_directories(${PROJECT_SOURCE_DIR}/../../include)
link_directories(${PROJECT_SOURCE_DIR}/../../lib)
if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
    include_directories(${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d)
    link_directories(${PROJECT_SOURCE_DIR}/../../guest/jpeg-9d)
    set(GUEST_LIBRARY libjpeg)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    include_directories(${PROJECT_SOURCE_DIR}/guest/include/libjpeg)
    link_directories(${PROJECT_SOURCE_DIR}/guest/lib)
	add_link_options(-NODEFAULTLIB:LIBCMT)
    set(GUEST_LIBRARY jpeg)
else ()
    set(GUEST_LIBRARY jpeg)
endif ()
add_library(jpeg SHARED
    module-jpeg.cpp
    DataType.cpp
    Symbol.cpp
    Util.cpp
    ImageExtension.cpp
    Content.cpp
    Exif.cpp
    IFD.cpp
    Segment.cpp
    Tag.cpp
    VType_Content.cpp
    VType_Exif.cpp
    VType_IFD.cpp
    VType_Segment.cpp
    VType_Tag.cpp
)
target_link_libraries(jpeg guraxcore ${GUEST_LIBRARY})
add_definitions(-DGURAX_MODULE_SEPARATED)
set(CMAKE_SHARED_LIBRARY_SUFFIX .gurd)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../..)
target_precompile_headers(jpeg PUBLIC stdafx.h)
install(TARGETS jpeg RUNTIME DESTINATION module/site)
