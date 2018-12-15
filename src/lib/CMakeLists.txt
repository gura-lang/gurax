add_library(guraxcore SHARED
	guraxcore.cpp
	Common.cpp
	Error.cpp
	Expr.cpp
	Function.cpp
	MemoryPool.cpp
	Object.cpp
	Object_function.cpp
	Object_nil.cpp
	Object_number.cpp
	Object_undefined.cpp
	Operator.cpp
	Referable.cpp
	String.cpp
	Symbol.cpp
	Token.cpp
	Tokenizer.cpp
)

target_link_libraries(guraxcore dl pthread)

set_target_properties(guraxcore PROPERTIES
	VERSION						${GURAX_VERSION}
	SOVERSION					${GURAX_VERSION_SO}
	BUILD_WITH_INSTALL_RPATH	1
	INSTALL_NAME_DIR			"@executable_path/../lib")

install(TARGETS guraxcore DESTINATION ${GURAX_RELDIR_LIBRARY})
