#===============================================================================
# CMakeLists for source basement
#===============================================================================
add_subdirectory(lib)
add_subdirectory(gurax)
add_subdirectory(unittest)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
add_subdirectory(module-bmp)
add_subdirectory(module-bzip2)
add_subdirectory(module-conio)
add_subdirectory(module-diff)
add_subdirectory(module-gzip)
add_subdirectory(module-hash)
add_subdirectory(module-jpeg)
add_subdirectory(module-markdown)
add_subdirectory(module-png)
add_subdirectory(module-re)
add_subdirectory(module-zip)
endif ()
