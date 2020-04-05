#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
add_executable(gurax gurax.cpp)
#find_library(LIBREADLINE readline REQUIRED)
target_link_libraries(gurax guraxcore) # ${LIBREADLINE}
install(TARGETS gurax RUNTIME DESTINATION bin)
