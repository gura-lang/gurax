add_library(guraxcore SHARED
	guraxcore.cpp
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
