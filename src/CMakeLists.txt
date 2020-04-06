#===============================================================================
# CMakeLists for source basement
#===============================================================================
#add_definitions("-Wall -std=c++14")
#add_definitions("-O2")

add_subdirectory(lib)
add_subdirectory(gurax)
add_subdirectory(unittest)

add_subdirectory(module-bzip2)
add_subdirectory(module-conio)
add_subdirectory(module-gzip)
#add_subdirectory(module-hash)
add_subdirectory(module-jpeg)
add_subdirectory(module-markdown)
add_subdirectory(module-png)
add_subdirectory(module-re)
add_subdirectory(module-zip)
