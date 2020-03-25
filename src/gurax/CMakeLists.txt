#===============================================================================
# CMakeLists for gurax executable
#===============================================================================
add_executable(gurax gurax.cpp)

#find_library(LIBREADLINE readline REQUIRED)

#target_link_libraries(gurax guraxcore ${LIBREADLINE})

target_link_libraries(gurax guraxcore)

install(TARGETS gurax) # DESTINATION ${GURAX_RELDIR_BINARY}
