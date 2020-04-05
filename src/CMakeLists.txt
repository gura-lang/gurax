#===============================================================================
# CMakeLists for source basement
#===============================================================================
#add_definitions("-Wall -std=c++14")
#add_definitions("-O2")

add_subdirectory(lib)
add_subdirectory(gurax)
add_subdirectory(unittest)

add_subdirectory(module-png)
